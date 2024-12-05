file(GLOB_RECURSE TEST_SRC ${arduinocore-api_SOURCE_DIR}/test/src/*.cpp)
add_library(ArduinoCore-Test STATIC ${TEST_SRC})

target_include_directories(
  ArduinoCore-Test PUBLIC ${arduinocore-api_BINARY_DIR}
                          ${arduinocore-api_SOURCE_DIR}/test/src
                          ${arduinocore-api_SOURCE_DIR}/test/include
                          ${arduinocore-api_SOURCE_DIR}/test/external/catch/v2.13.9/include
                          ${arduinocore-api_SOURCE_DIR}/api)
