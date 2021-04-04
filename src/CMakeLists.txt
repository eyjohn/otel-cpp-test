set(BINARY ${CMAKE_PROJECT_NAME})

set(SOURCES example.cpp)

add_library(${BINARY}_lib STATIC ${SOURCES})
target_include_directories(${BINARY}_lib PUBLIC ${CMAKE_CURRENT_LIST_DIR})

add_executable(${BINARY} main.cpp)
target_link_libraries(${BINARY}
                      ${BINARY}_lib
                      opentelemetry-cpp::api
                      opentelemetry-cpp::sdk
                      opentelemetry-cpp::trace
                      opentelemetry-cpp::ostream_span_exporter
                      )
