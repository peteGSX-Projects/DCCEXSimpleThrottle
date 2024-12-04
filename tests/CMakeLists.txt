cmake_minimum_required(VERSION 3.11 FATAL_ERROR)
include(${CMAKE_SOURCE_DIR}/cmake/sanitize.cmake)

#Find GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG main)
FetchContent_MakeAvailable(googletest)

# Create test executable
add_executable(DCCEXSimpleThrottleTest DCCEXSimpleThrottleTest.cpp)

# Include all test files
file(GLOB_RECURSE TEST_SOURCE_FILES "*.cpp")
target_sources(DCCEXSimpleThrottleTest PRIVATE ${TEST_SOURCE_FILES})

# Reuse ArduinoCore-API fakes and mocks
target_sources(
  DCCEXSimpleThrottleTest PRIVATE
    ${arduinocore-api_SOURCE_DIR}/test/src/MillisFake.cpp
    ${arduinocore-api_SOURCE_DIR}/test/src/PrintMock.cpp
    ${arduinocore-api_SOURCE_DIR}/test/src/StreamMock.cpp)

# Sanitise
sanitize(address,undefined)

# Link against GoogleTest libraries
target_link_libraries(DCCEXSimpleThrottleTest PRIVATE GTest::gtest GTest::gtest_main GTest::gmock)

# Link against executable
target_link_libraries(DCCEXSimpleThrottleTest PRIVATE DCCEXSimpleThrottle)

# Enable tests
add_test(DCCEXSimpleThrottleTest COMMAND DCCEXSimpleThrottleTest)
