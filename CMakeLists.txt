cmake_minimum_required (VERSION 3.0)
project ("ublox")

option (CC_UBLOX_LIB_ONLY "Install only UBLOX protocol library, no other applications/plugings are built." OFF)
option (CC_UBLOX_FULL_SOLUTION "Build and install full solution, including CommsChampion sources." OFF)

set (INSTALL_DIR ${CMAKE_BINARY_DIR}/install)
if (NOT "${CC_UBLOX_INSTALL_DIR}" STREQUAL "")
    set (INSTALL_DIR "${CC_UBLOX_INSTALL_DIR}")
endif ()

set (LIB_INSTALL_DIR ${INSTALL_DIR}/lib)
set (BIN_INSTALL_DIR ${INSTALL_DIR}/bin)
set (INC_INSTALL_DIR ${INSTALL_DIR}/include)
set (PLUGIN_INSTALL_DIR ${INSTALL_DIR}/plugin)
set (DOC_INSTALL_DIR ${INSTALL_DIR}/doc)

install (
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/ublox
    DESTINATION ${INC_INSTALL_DIR}
)

find_package (Doxygen)
if (DOXYGEN_FOUND)
    set (doc_output_dir "${DOC_INSTALL_DIR}/ublox")
    make_directory (${doc_output_dir})
    
    set (match_str "OUTPUT_DIRECTORY[^\n]*")
    set (replacement_str "OUTPUT_DIRECTORY = ${doc_output_dir}")
    set (output_file "${CMAKE_CURRENT_BINARY_DIR}/doxygen.conf")

    set (config_file "${CMAKE_CURRENT_SOURCE_DIR}/doc/doxygen.conf")
    file (READ ${config_file} config_text)
    string (REGEX REPLACE "${match_str}" "${replacement_str}" modified_config_text "${config_text}")
    file (WRITE "${output_file}" "${modified_config_text}")
    
    set (doc_cleanup_script)
    if ((CC_UBLOX_FULL_SOLUTION) OR (EXISTS "${INSTALL_DIR}/cmake/DocCleanupScript.cmake"))
        set (doc_cleanup_script "${INSTALL_DIR}/cmake/DocCleanupScript.cmake")
    elseif (EXISTS "${CC_MAIN_INSTALL_DIR}/cmake/DocCleanupScript.cmake")
        set (doc_cleanup_script "${CC_MAIN_INSTALL_DIR}/cmake/DocCleanupScript.cmake")
    endif ()
    
    set (doc_ublox_tgt "doc_ublox")
    if ("${doc_cleanup_script}" STREQUAL "")
        add_custom_target ("${doc_ublox_tgt}"
            COMMAND ${DOXYGEN_EXECUTABLE} ${output_file}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
    else ()
        add_custom_target ("${doc_ublox_tgt}"
            COMMAND ${DOXYGEN_EXECUTABLE} ${output_file}
            COMMAND ${CMAKE_COMMAND} -DDOC_OUTPUT_DIR="${doc_output_dir}" -P
                "${doc_cleanup_script}"
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
    endif ()
    
    if (CC_UBLOX_FULL_SOLUTION)
        add_dependencies(${doc_ublox_tgt} ${CC_EXTERNAL_TGT})
    endif ()
endif ()

if (CC_UBLOX_LIB_ONLY)
    return ()
endif ()    

if (CMAKE_COMPILER_IS_GNUCC)
    set (extra_flags_list
        "--std=c++11"
        "-Wall" "-Wextra" "-Werror" "-Wcast-align" "-Wcast-qual" "-Wctor-dtor-privacy"
        "-Wmissing-include-dirs" "-Wnoexcept" "-Wlogical-op" "-Wstrict-null-sentinel"
        "-Woverloaded-virtual" "-Wredundant-decls" "-Wshadow" "-Wundef" "-Wunused"
        "-Wno-unknown-pragmas" "-fdiagnostics-show-option"
    )
    
    string(REPLACE ";" " " extra_flags "${extra_flags_list}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${extra_flags}")
elseif (MSVC)
    add_definitions( "/wd4503" "/wd4309" "/wd4267" "-D_SCL_SECURE_NO_WARNINGS")
endif ()

set (CC_EXTERNAL_TGT "comms_champion_external")
if (CC_UBLOX_FULL_SOLUTION)
    include(ExternalProject)
    
    set (cc_branch "master")
    set (cc_main_dir "${CMAKE_BINARY_DIR}/comms_champion")
    set (cc_src_dir "${cc_main_dir}/src")
    set (cc_bin_dir "${cc_main_dir}/build")
    
    if (NOT "${CC_UBLOX_QT_DIR}" STREQUAL "")
        set (extra_cc_args "-DCC_QT_DIR=${CC_UBLOX_QT_DIR}")
    endif ()

    ExternalProject_Add(
        "${CC_EXTERNAL_TGT}"
        PREFIX "${cc_bin_dir}"
        STAMP_DIR "${cc_bin_dir}"    
        GIT_REPOSITORY "https://github.com/arobenko/comms_champion.git"
        GIT_TAG "${cc_branch}"
        SOURCE_DIR "${cc_src_dir}"
        CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -DCC_INSTALL_DIR=${INSTALL_DIR} ${extra_cc_args}
        BINARY_DIR "${cc_bin_dir}"
    )
    
    include_directories("${INSTALL_DIR}/include")
    link_directories("${INSTALL_DIR}/lib")
    set (CC_PLUGIN_LIBRARIES "comms_champion")
endif ()


if ((UNIX) AND (NOT CC_UBLOX_NO_CCACHE))
    find_program(CCACHE_FOUND ccache)
    if(CCACHE_FOUND)
        set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
        set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
    endif(CCACHE_FOUND)
endif ()    

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/include)

add_subdirectory(cc_plugin)


