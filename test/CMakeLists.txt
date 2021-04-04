include(GoogleTest)

set(BINARY ${CMAKE_PROJECT_NAME})

add_executable(${BINARY}.u.t test_example.u.t.cpp)
target_link_libraries(${BINARY}.u.t ${BINARY}_lib gtest_main gmock gtest pthread)

gtest_discover_tests(${BINARY}.u.t
    WORKING_DIRECTORY ${PROJECT_DIR}
    PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${PROJECT_DIR}"
)
