
set(TEST_FILES
    test_main.cpp
    test_histogram.cpp
)

set(PROJECT_TEST_NAME ${PROJECT_NAME}_test)
add_executable(${PROJECT_TEST_NAME} ${TEST_FILES})
add_test(NAME ${PROJECT_TEST_NAME} COMMAND ${PROJECT_TEST_NAME} ${TEST_FILES})
