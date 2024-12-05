# Set version 3.11
cmake_minimum_required(VERSION 3.11 FATAL_ERROR)
# Include FetchContent so we can get libraries etc.
include(FetchContent)
# Add the cmake directory containing extra cmake files
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)

# Define the project name and language
project(DCCEXSimpleThrottle LANGUAGES CXX)

# Fetch ArduinoCore-API
if(NOT TARGET ArduinoCore-API)
  FetchContent_Declare(
    ArduinoCore-API
    GIT_REPOSITORY https://github.com/arduino/ArduinoCore-API
    GIT_TAG 1.4.0)
  FetchContent_Populate(ArduinoCore-API)
  find_package(ArduinoCore-API REQUIRED)
endif()

# Fetch U8g2 library
if(NOT TARGET U8g2lib)
  FetchContent_Declare(
    U8g2lib
    GIT_REPOSITORY https://github.com/olikraus/u8g2.git
    GIT_TAG master)
  FetchContent_MakeAvailable(U8g2lib)
endif()

# Fetch DCCEXProtocol library
if(NOT TARGET DCCEXProtocol)
  FetchContent_Declare(
    DCCEXProtocol
    GIT_REPOSITORY https://github.com/DCC-EX/DCCEXProtocol
    GIT_TAG v0.0.17-Devel)
  FetchContent_MakeAvailable(DCCEXProtocol)
endif()

# Create this application as a library to run tests against
add_library(DCCEXSimpleThrottle STATIC DCCEXSimpleThrottle.ino)

# Set target compile options
target_compile_options(DCCEXSimpleThrottle PRIVATE -std=c++11)

# Link against the Arduino core API and other required libraries
target_link_libraries(DCCEXSimpleThrottle PUBLIC
                      ArduinoCore-API
                      u8g2
                      DCCEXProtocol)

# Enable testing
enable_testing()

# Add docs and tests directories
if(PROJECT_IS_TOP_LEVEL)
  add_subdirectory(docs)
  add_subdirectory(tests)
endif()
