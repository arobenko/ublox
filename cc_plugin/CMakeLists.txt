function (cc_plugin_ublox)
    set (name "ublox")
    
    set (meta_file "${CMAKE_CURRENT_SOURCE_DIR}/ublox.json")
    set (stamp_file "${CMAKE_CURRENT_BINARY_DIR}/ublox_refresh_stamp.txt")
    
    set (refresh_plugin_header TRUE)
    if ((NOT EXISTS ${stamp_file}) OR (${meta_file} IS_NEWER_THAN ${stamp_file}))
        execute_process(
            COMMAND ${CMAKE_COMMAND} -E touch ${CMAKE_CURRENT_SOURCE_DIR}/Plugin.h)
        execute_process(
            COMMAND ${CMAKE_COMMAND} -E touch ${stamp_file})
    endif ()
    
    
    set (src
        Plugin.cpp
        Protocol.cpp
        TransportMessage.cpp
        message/NavPosecef.cpp
        message/NavPosecefPoll.cpp
        message/NavPosllh.cpp
        message/NavPosllhPoll.cpp
        message/NavStatus.cpp
        message/NavStatusPoll.cpp
        message/NavDop.cpp
        message/NavDopPoll.cpp
        message/NavSol.cpp
        message/NavSolPoll.cpp
        message/NavPosutm.cpp
        message/NavPosutmPoll.cpp
        message/NavVelecef.cpp
        message/NavVelecefPoll.cpp
        message/NavVelned.cpp
        message/NavVelnedPoll.cpp
        message/NavTimegps.cpp
        message/NavTimegpsPoll.cpp
        message/NavTimeutc.cpp
        message/NavTimeutcPoll.cpp
        message/NavClock.cpp
        message/NavClockPoll.cpp
        message/NavSvinfo.cpp
        message/NavSvinfoPoll.cpp
        message/NavDgps.cpp
        message/NavDgpsPoll.cpp
        message/NavSbas.cpp
        message/NavSbasPoll.cpp
        message/NavEkfstatus.cpp
        message/NavEkfstatusPoll.cpp
        message/RxmRaw.cpp
        message/RxmRawPoll.cpp
        message/AckNak.cpp
        message/AckAck.cpp
        field/MsgId.cpp
        field/common.cpp
        field/nav.cpp
        field/rxm.cpp
    )
    
    set (hdr
        Plugin.h
    )
    
    qt5_wrap_cpp(
        moc
        ${hdr}
    )
    
    add_library (${name} SHARED ${src} ${moc})
    
    install (
        TARGETS ${name}
        DESTINATION ${PLUGIN_INSTALL_DIR})
        
    install (
        TARGETS ${name}
        DESTINATION ${CC_INSTALL_PATH}/plugin)
    
endfunction()

######################################################################

find_package(Qt5Core REQUIRED)

include_directories(
    ${Qt5Core_INCLUDE_DIRS})

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ftemplate-backtrace-limit=0")
cc_plugin_ublox ()
