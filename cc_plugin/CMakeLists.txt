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
        message/NavPvt.cpp
        message/NavPvtPoll.cpp
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
        message/NavAopstatus.cpp
        message/NavAopstatusPoll.cpp
        message/RxmRaw.cpp
        message/RxmRawPoll.cpp
        message/RxmSfrb.cpp
        message/RxmSvsi.cpp
        message/RxmSvsiPoll.cpp
        message/RxmAlm.cpp
        message/RxmAlmPollSv.cpp
        message/RxmAlmPoll.cpp
        message/RxmEph.cpp
        message/RxmEphPollSv.cpp
        message/RxmEphPoll.cpp
        message/RxmPmreq.cpp
        message/InfError.cpp
        message/InfWarning.cpp
        message/InfNotice.cpp
        message/InfTest.cpp
        message/InfDebug.cpp
        message/AckNak.cpp
        message/AckAck.cpp
        message/CfgPrtUart.cpp
        message/CfgPrtUsb.cpp
        message/CfgPrtSpi.cpp
        message/CfgPrtDdc.cpp
        message/CfgPrtPollPort.cpp
        message/CfgPrtPoll.cpp
        message/CfgMsg.cpp
        message/CfgMsgCurrent.cpp
        message/CfgMsgPoll.cpp
        message/CfgInf.cpp
        message/CfgInfPoll.cpp
        message/CfgRst.cpp
        message/CfgDat.cpp
        message/CfgDatUser.cpp
        message/CfgDatStandard.cpp
        message/CfgDatPoll.cpp
        message/CfgTp.cpp
        message/CfgTpPoll.cpp
#        message/CfgRate.cpp        
#        message/CfgRatePoll.cpp
#        message/CfgCfg.cpp
#        message/CfgFxn.cpp
#        message/CfgFxnPoll.cpp
#        message/CfgTm.cpp
#        message/CfgTmPoll.cpp
#        message/CfgRxm.cpp
#        message/CfgRxmPoll.cpp
#        message/CfgEkf.cpp
#        message/CfgEkfPoll.cpp
        field/MsgId.cpp
        field/common.cpp
        field/nav.cpp
        field/rxm.cpp
        field/inf.cpp
        field/cfg.cpp
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
