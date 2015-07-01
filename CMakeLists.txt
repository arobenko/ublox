cmake_minimum_required (VERSION 2.8.11)
project ("ublox")

if ("${CC_INSTALL_PATH}" STREQUAL "")
    message (FATAL_ERROR "Please set CC_INSTALL_PATH with \"comms_champion\" installation path.")
endif ()

include_directories("${CC_INSTALL_PATH}/include")

if (CMAKE_COMPILER_IS_GNUCC)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror --std=c++0x")
endif ()

set (INSTALL_DIR ${CMAKE_BINARY_DIR}/install)
set (LIB_INSTALL_DIR ${INSTALL_DIR}/lib)
set (BIN_INSTALL_DIR ${INSTALL_DIR}/bin)
set (INC_INSTALL_DIR ${INSTALL_DIR}/include)
set (PLUGIN_INSTALL_DIR ${INSTALL_DIR}/plugin)

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/include)

add_subdirectory(cc_plugin)

