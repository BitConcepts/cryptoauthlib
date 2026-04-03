cmake_minimum_required(VERSION 3.20.0)

# Register CryptoAuthLib as an extra Zephyr module (three levels up from this test)
get_filename_component(CRYPTOAUTHLIB_MODULE_DIR
  "${CMAKE_CURRENT_SOURCE_DIR}/../../.." ABSOLUTE)
list(APPEND ZEPHYR_EXTRA_MODULES ${CRYPTOAUTHLIB_MODULE_DIR})

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(cryptoauthlib_build_verification)

target_sources(app PRIVATE src/main.c)
