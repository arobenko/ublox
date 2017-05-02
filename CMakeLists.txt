cmake_minimum_required (VERSION 3.1)
project ("ublox")

option (CC_UBLOX_LIB_ONLY "Install only UBLOX protocol library, no other applications/plugings are built." OFF)
option (CC_UBLOX_AND_COMMS_LIBS_ONLY "Install UBLOX protocol and COMMS libraries only, no other applications/plugings are built." OFF)
option (CC_UBLOX_FULL_SOLUTION "Build and install full solution, including CommsChampion sources." OFF)
option (CC_UBLOX_NO_WARN_AS_ERR "Do NOT treat warning as error" OFF)

if (NOT CMAKE_CXX_STANDARD)
    set (CMAKE_CXX_STANDARD 11)
endif()

set (INSTALL_DIR ${CMAKE_BINARY_DIR}/install)
if (NOT "${CC_UBLOX_INSTALL_DIR}" STREQUAL "")
    set (INSTALL_DIR "${CC_UBLOX_INSTALL_DIR}")
endif ()

include(GNUInstallDirs)
set (INSTALL_NAME "CC_Ublox")
set (LIB_INSTALL_DIR ${INSTALL_DIR}/${CMAKE_INSTALL_LIBDIR})
set (BIN_INSTALL_DIR ${INSTALL_DIR}/${CMAKE_INSTALL_BINDIR})
set (INC_INSTALL_DIR ${INSTALL_DIR}/${CMAKE_INSTALL_INCLUDEDIR})
set (CONFIG_INSTALL_DIR ${INSTALL_DIR}/config)
set (PLUGIN_INSTALL_DIR ${INSTALL_DIR}/${CMAKE_INSTALL_LIBDIR}/CommsChampion/plugin)
set (DOC_INSTALL_DIR ${INSTALL_DIR}/doc)

install (
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/ublox
    DESTINATION ${INC_INSTALL_DIR}
)

FILE(GLOB_RECURSE protocol.headers "include/*.h")
add_custom_target(ublox.headers SOURCES ${protocol.headers})

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


    set (doc_ublox_tgt "doc_ublox")
        add_custom_target ("${doc_ublox_tgt}"
            COMMAND ${DOXYGEN_EXECUTABLE} ${output_file}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
 endif ()

if (CC_UBLOX_LIB_ONLY)
    return ()
endif ()

######################################################################

set (CC_EXTERNAL_TGT "comms_champion_external")
macro (externals install_dir build_cc)
        include(ExternalProject)
        
        set (cc_tag "v0.17")
        set (cc_main_dir "${CMAKE_BINARY_DIR}/comms_champion")
        set (cc_src_dir "${cc_main_dir}/src")
        set (cc_bin_dir "${cc_main_dir}/build")
        
        if (NOT "${CC_UBLOX_QT_DIR}" STREQUAL "")
            set (cc_qt_dir_opt -DCC_QT_DIR=${CC_UBLOX_QT_DIR})
        endif ()
        
        if (${build_cc})
            set (CC_PLUGIN_LIBRARIES "comms_champion")
            set (CC_COMMS_CHAMPION_FOUND TRUE)
            set (CC_PLUGIN_LIBRARY_DIRS ${LIB_INSTALL_DIR})
        else ()
            set (ct_lib_only_opt -DCC_COMMS_LIB_ONLY=ON)
        endif ()
    
        ExternalProject_Add(
            "${CC_EXTERNAL_TGT}"
            PREFIX "${cc_bin_dir}"
            STAMP_DIR "${cc_bin_dir}"    
            GIT_REPOSITORY "https://github.com/arobenko/comms_champion.git"
            GIT_TAG "${cc_tag}"
            SOURCE_DIR "${cc_src_dir}"
            CMAKE_ARGS 
                -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -DCC_INSTALL_DIR=${install_dir} 
                -DCC_NO_UNIT_TESTS=ON -DCC_NO_WARN_AS_ERR=ON -DCMAKE_CXX_STANDARD=${CMAKE_CXX_STANDARD} 
                -DCMAKE_C_COMPILER=${CMAKE_C_COMPILER} -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER} 
                ${cc_qt_dir_opt} ${ct_lib_only_opt}
            BINARY_DIR "${cc_bin_dir}"
        )
        set (CC_EXTERNAL TRUE)
        set (CC_COMMS_FOUND TRUE)
        set (CC_CMAKE_DIR ${LIB_INSTALL_DIR}/cmake)
        
        include_directories("${install_dir}/${CMAKE_INSTALL_INCLUDEDIR}")
        link_directories("${install_dir}/${CMAKE_INSTALL_LIBDIR}")
        
endmacro()

######################################################################

if (CC_UBLOX_AND_COMMS_LIBS_ONLY)
    externals(${INSTALL_DIR} FALSE)
    return()
endif ()

while (TRUE)
    if (CC_UBLOX_FULL_SOLUTION)
        externals(${INSTALL_DIR} TRUE) 
        break()
    endif ()
    
    list (APPEND CMAKE_PREFIX_PATH "${INSTALL_DIR}")

    if (NOT "${CC_MAIN_INSTALL_DIR}" STREQUAL "")
        list (APPEND CMAKE_PREFIX_PATH "${CC_MAIN_INSTALL_DIR}")
    endif ()
    
    find_package(CommsChampion QUIET NO_MODULE)
    
    if (NOT CC_COMMS_FOUND)
        set (externals_install "${CMAKE_BINARY_DIR}/ext_install")
        set (build_cc FALSE)
        if ((NOT CC_UBLOX_LIB_ONLY) AND (NOT CC_UBLOX_AND_COMMS_LIBS_ONLY))
            set (build_cc TRUE)
        endif ()
        
        externals(${externals_install} ${build_cc})
        break()
    endif ()

    find_package(CommsChampion NO_MODULE)
    if (CC_COMMS_FOUND)
        include_directories(${CC_INCLUDE_DIRS})
    endif ()
        
    if (CC_COMMS_CHAMPION_FOUND)
        link_directories(${CC_PLUGIN_LIBRARY_DIRS})
        file (RELATIVE_PATH rel_plugin_install_path "${CC_ROOT_DIR}" "${CC_PLUGIN_DIR}")
        set (PLUGIN_INSTALL_DIR "${INSTALL_DIR}/${rel_plugin_install_path}")
    endif ()
    
    break()
endwhile()

if ((CMAKE_COMPILER_IS_GNUCC) OR ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang"))
    set (extra_flags_list
        "-Wall" "-Wextra" "-Wcast-align" "-Wcast-qual" "-Wctor-dtor-privacy"
        "-Wmissing-include-dirs"
        "-Woverloaded-virtual" "-Wredundant-decls" "-Wshadow" "-Wundef" "-Wunused"
        "-Wno-unknown-pragmas" "-fdiagnostics-show-option"
    )

    if (CMAKE_COMPILER_IS_GNUCC)
        list (APPEND extra_flags_list
            "-Wnoexcept" "-Wlogical-op" "-Wstrict-null-sentinel"
        )
    endif ()

    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        list (APPEND extra_flags_list "-Wno-dangling-field" "-ftemplate-depth=1024")
    endif ()

    if (NOT CC_UBLOX_NO_WARN_AS_ERR)
        list (APPEND extra_flags_list "-Werror")
    endif ()

        string(REPLACE ";" " " extra_flags "${extra_flags_list}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${extra_flags}")
elseif (MSVC)
    add_definitions( "/wd4503" "/wd4309" "/wd4267" "-D_SCL_SECURE_NO_WARNINGS")
    
    if (NOT CC_NO_WARN_AS_ERR)
        add_definitions("/WX")
    endif ()
endif ()

if ((UNIX) AND (NOT CC_UBLOX_NO_CCACHE))
    find_program(CCACHE_FOUND ccache)
    if(CCACHE_FOUND)
        set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
        set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
    endif(CCACHE_FOUND)
endif ()    

include_directories(
    BEFORE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/include
)

add_subdirectory(cc_plugin)
