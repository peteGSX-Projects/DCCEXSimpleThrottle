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
endif()

# Create as a library to run tests against
add_library(DCCEXSimpleThrottle STATIC DCCEXSimpleThrottle.ino)

# Include all .cpp files
file(GLOB_RECURSE SOURCE_FILES "*.cpp")
target_sources(DCCEXSimpleThrottle PRIVATE ${SOURCE_FILES})

# Set target compile options
target_compile_options(DCCEXSimpleThrottle PRIVATE -std=c++11)

# Include Arduino core API headers
target_include_directories(DCCEXSimpleThrottle PRIVATE ${ArduinoCore-API_SOURCE_DIR}/api)

# Link against the Arduino core API
target_link_libraries(DCCEXSimpleThrottle PUBLIC ArduinoCore-API)

# Enable testing
enable_testing()

# Add docs and tests
if(PROJECT_IS_TOP_LEVEL)
  add_subdirectory(docs)
  add_subdirectory(tests)
endif()
