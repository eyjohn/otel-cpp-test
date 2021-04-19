#include "example.h"

#include "opentelemetry/exporters/ostream/span_exporter.h"
#include "opentelemetry/sdk/trace/simple_processor.h"
#include "opentelemetry/sdk/trace/tracer_provider.h"
#include "opentelemetry/trace/provider.h"

#include <chrono>
#include <iostream>
#include <memory>

namespace {
void initTracer()
{
    auto exporter = std::unique_ptr<sdktrace::SpanExporter>(
        new opentelemetry::exporter::trace::OStreamSpanExporter);
    auto processor = std::unique_ptr<sdktrace::SpanProcessor>(
        new sdktrace::SimpleSpanProcessor(std::move(exporter)));
    auto provider = nostd::shared_ptr<opentelemetry::trace::TracerProvider>(
        new sdktrace::TracerProvider(std::move(processor),
            opentelemetry::sdk::resource::Resource::Create({}),
            std::unique_ptr<sdktrace::Sampler>(new sdktrace::AlwaysOnSampler())));
    // Set the global trace provider
    opentelemetry::trace::Provider::SetTracerProvider(provider);
}

opentelemetry::nostd::shared_ptr<opentelemetry::trace::Tracer> get_tracer()
{
    return opentelemetry::trace::Provider::GetTracerProvider()->GetTracer("main");
}

} // namespace

int main()
{
    initTracer();
    auto tracer = get_tracer();
    auto span = tracer->StartSpan("main", { { "key", "val" } });
    auto scope = tracer->WithActiveSpan(span);
    std::cout << "Hello World: " << example() << std::endl;
}