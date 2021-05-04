#include "example.h"

#include "opentelemetry/exporters/ostream/span_exporter.h"
#include "opentelemetry/sdk/trace/simple_processor.h"
#include "opentelemetry/sdk/trace/tracer_provider.h"
#include "opentelemetry/trace/provider.h"

#include <otel-cpp-lib-test/hello.h>

#include <dlfcn.h>

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

int main(int argc, char* argv[])
{
    initTracer();
    auto tracer = get_tracer();
    auto span = tracer->StartSpan("main", { { "key", "val" } });
    auto scope = tracer->WithActiveSpan(span);
    std::cout << "Hello World: " << example() << std::endl;
    hello();

    if (argc < 2) {
        return 0;
    }

    void* handle = dlopen(argv[1], RTLD_LAZY);
    if (!handle) {
        std::cerr << "Cannot open library: " << dlerror() << std::endl;
        return 1;
    }

    dlerror(); // reset errors

    // load the symbol
    typedef void (*world_t)();
    world_t world = (world_t)dlsym(handle, "world");
    const char* dlsym_error = dlerror();
    if (dlsym_error) {
        std::cerr << "Cannot load symbol 'world': " << dlsym_error << std::endl;
        return 1;
    }

    world();

    // close the library
    dlclose(handle);
}