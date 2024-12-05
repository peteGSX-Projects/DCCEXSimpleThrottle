cmake_minimum_required(VERSION 3.11 FATAL_ERROR)
include(FetchContent)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)

project(DCCEXSimpleThrottle LANGUAGES CXX)

# Fetch ArduinoCore-API
if(NOT TARGET ArduinoCore-API)
  FetchContent_Declare(
    ArduinoCore-API
    GIT_REPOSITORY https://github.com/arduino/ArduinoCore-API
    GIT_TAG 1.4.0)
  FetchContent_Populate(ArduinoCore-API)
  find_package(ArduinoCore-API)
endif()

# Fetch U8g2 library
if(NOT TARGET U8g2lib)
FetchContent_Declare(
  U8g2lib
  GIT_REPOSITORY https://github.com/olikraus/u8g2.git
  GIT_TAG master)
FetchContent_Populate(U8g2lib)
endif()

# Fetch DCCEXProtocol library
if(NOT TARGET DCCEXProtocol)
FetchContent_Declare(
  DCCEXProtocol
  GIT_REPOSITORY https://github.com/DCC-EX/DCCEXProtocol
  GIT_TAG v0.0.17-Devel)
FetchContent_Populate(DCCEXProtocol)
endif()

#Find GoogleTest
if(NOT TARGET googletest)
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG main)
FetchContent_MakeAvailable(googletest)
endif()

# Create as a library to run tests against
add_library(DCCEXSimpleThrottle STATIC DCCEXSimpleThrottle.ino)

# Include all .cpp files
file(GLOB_RECURSE SOURCE_FILES "*.cpp")
target_sources(DCCEXSimpleThrottle PRIVATE ${SOURCE_FILES})

# Include all U8g2lib .cpp files
file(GLOB_RECURSE U8G2_SOURCE_FILES ${u8g2lib_SOURCE_DIR}/cppsrc/*.cpp)
target_sources(DCCEXSimpleThrottle PRIVATE ${U8G2_SOURCE_FILES})

# Set target compile options
target_compile_options(DCCEXSimpleThrottle PRIVATE -std=c++11)

# Include Arduino core API, library, and GoogleTest mock headers
target_include_directories(DCCEXSimpleThrottle PRIVATE ${ArduinoCore-API_SOURCE_DIR}/api)
target_include_directories(DCCEXSimpleThrottle PRIVATE ${u8g2lib_SOURCE_DIR}/cppsrc)
target_include_directories(DCCEXSimpleThrottle PRIVATE ${u8g2lib_SOURCE_DIR}/csrc)
target_include_directories(DCCEXSimpleThrottle PRIVATE ${dccexprotocol_SOURCE_DIR}/src)

# Link against the Arduino core API and other libraries
target_link_libraries(DCCEXSimpleThrottle PUBLIC ArduinoCore-API)
target_link_libraries(DCCEXSimpleThrottle PUBLIC ${dccexprotocol_SOURCE_DIR}/src/DCCEXProtocol.cpp)
target_link_libraries(DCCEXSimpleThrottle PRIVATE GTest::gtest_main)

# Include directories for tests to find StreamMock and other necessary headers
target_include_directories(DCCEXSimpleThrottle PRIVATE ${googletest_SOURCE_DIR}/googletest/include)
target_include_directories(DCCEXSimpleThrottle PRIVATE ${googletest_SOURCE_DIR}/googlemock/include)

# Override stream preprocessor definitions for mocking
target_compile_definitions(DCCEXSimpleThrottle PRIVATE CONSOLE=StreamMock)
target_compile_definitions(DCCEXSimpleThrottle PRIVATE COMMANDSTATION_CONNECTION=StreamMock)

# Enable testing
enable_testing()

# Add docs and tests
if(PROJECT_IS_TOP_LEVEL)
  add_subdirectory(docs)
  add_subdirectory(tests)
endif()
