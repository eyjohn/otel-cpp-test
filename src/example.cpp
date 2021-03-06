#include "example.h"
#include <opentelemetry/trace/provider.h>
#include <opentelemetry/trace/tracer_provider.h>

namespace {
opentelemetry::nostd::shared_ptr<opentelemetry::trace::Tracer> get_tracer()
{
    return opentelemetry::trace::Provider::GetTracerProvider()->GetTracer("example");
}
}

int example()
{
    auto tracer = get_tracer();
    tracer->StartSpan("example", { { "answer", 42 } }, { { tracer->GetCurrentSpan()->GetContext(), { { "trueParent", true } } } });
    return 42;
}
