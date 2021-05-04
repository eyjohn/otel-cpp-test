set(BINARY ${CMAKE_PROJECT_NAME})

set(SOURCES example.cpp)
set(HELLO_LIB_PREFIX /home/john/git/otel-cpp-lib-test/install)

add_library(${BINARY}_lib STATIC ${SOURCES})
target_include_directories(${BINARY}_lib PUBLIC ${CMAKE_CURRENT_LIST_DIR})

add_executable(${BINARY} main.cpp)
target_include_directories(${BINARY} PUBLIC ${HELLO_LIB_PREFIX}/include)
target_link_directories(${BINARY} PUBLIC ${HELLO_LIB_PREFIX}/lib)
target_link_libraries(${BINARY}
                      ${BINARY}_lib
                      opentelemetry-cpp::api
                      opentelemetry-cpp::sdk
                      opentelemetry-cpp::trace
                      opentelemetry-cpp::ostream_span_exporter
                      otel-cpp-lib-test_hello
                      dl
                      )
