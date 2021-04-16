#include "example.h"

#include "opentelemetry/exporters/ostream/span_exporter.h"
#include "opentelemetry/sdk/trace/simple_processor.h"
#include "opentelemetry/sdk/trace/tracer_provider.h"
#include "opentelemetry/trace/provider.h"

#include <chrono>
#include <iostream>

namespace {
void initTracer()
{
    auto exporter = std::unique_ptr<sdktrace::SpanExporter>(
        new opentelemetry::exporter::trace::OStreamSpanExporter);
    auto processor = std::shared_ptr<sdktrace::SpanProcessor>(
        new sdktrace::SimpleSpanProcessor(std::move(exporter)));
    auto provider = nostd::shared_ptr<opentelemetry::trace::TracerProvider>(
        new sdktrace::TracerProvider(processor, opentelemetry::sdk::resource::Resource::Create({}),
            std::make_shared<opentelemetry::sdk::trace::AlwaysOnSampler>()));

    // Set the global trace provider
    opentelemetry::trace::Provider::SetTracerProvider(provider);
}

auto get_tracer()
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