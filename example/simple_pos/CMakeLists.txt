function (cc_simple_pos_example)
    set (name "cc_ublox_simple_pos_example")

    set (src
        main.cpp
        Session.cpp
    )

    set (hdr
        Session.h
    )

    qt5_wrap_cpp(
        moc
        ${hdr}
    )

    add_executable(${name} ${src} ${moc})
    qt5_use_modules(${name} SerialPort Core)

    install (
        TARGETS ${name}
        DESTINATION ${BIN_INSTALL_DIR})

    if (CC_UBLOX_FULL_SOLUTION)
        add_dependencies(${name} ${CC_EXTERNAL_TGT})
    endif ()

endfunction()

######################################################################

find_package(Qt5SerialPort)

if (NOT Qt5SerialPort_FOUND)
    message (WARNING "Can NOT compile example application due to missing QT5 SerialPort library")
    return ()
endif ()

cc_simple_pos_example ()
