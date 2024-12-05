# Include sanitizer macro
include(${CMAKE_SOURCE_DIR}/cmake/sanitize.cmake)

# Include all source files and add the test executable
file(GLOB_RECURSE SRC *.cpp)
add_executable(DCCEXSimpleThrottleTests ${SRC})

# Reuse ArduinoCore-API fakes and mocks in our exe
target_sources(
  DCCEXSimpleThrottleTests
  PRIVATE ${arduinocore-api_SOURCE_DIR}/test/src/MillisFake.cpp
          ${arduinocore-api_SOURCE_DIR}/test/src/PrintMock.cpp
          ${arduinocore-api_SOURCE_DIR}/test/src/StreamMock.cpp)

# Include the Arduino Core headers, both API and tests/mocks
target_include_directories(DCCEXSimpleThrottleTests
                           PUBLIC ${arduinocore-api_SOURCE_DIR}/api)
target_include_directories(DCCEXSimpleThrottleTests
                           PUBLIC ${arduinocore-api_SOURCE_DIR}/test/include)

# Run the sanitizer
sanitize(address,undefined)

# Set compiler options for tests
target_compile_options(DCCEXSimpleThrottleTests PUBLIC -std=c++2a -Wall -Wextra
                                                 -Wconversion -Wsign-conversion)

# Fetch GoogleTest
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG main)
FetchContent_MakeAvailable(googletest)

# Link GoogleTest libraries
target_link_libraries(DCCEXSimpleThrottleTests PRIVATE
                      DCCEXSimpleThrottle
                      GTest::gtest_main
                      GTest::gmock)
