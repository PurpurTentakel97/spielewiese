add_executable(tests
               Test_Optional.cpp
               Test_Result.cpp
)

target_link_libraries(tests
                      PRIVATE
                      spielewiese
                      GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(tests)