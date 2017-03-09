set (THIS_PLUGIN_NAME "ublox")

######################################################################

function (cc_plugin_ublox)
    set (name "${THIS_PLUGIN_NAME}")
    
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
        message/NavOdo.cpp
        message/NavOdoPoll.cpp
        message/NavResetodo.cpp
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
        message/NavTimeglo.cpp
        message/NavTimegloPoll.cpp
        message/NavTimebds.cpp
        message/NavTimebdsPoll.cpp
        message/NavTimegal.cpp
        message/NavTimegalPoll.cpp
        message/NavSvinfo.cpp
        message/NavSvinfoPoll.cpp
        message/NavDgps.cpp
        message/NavDgpsPoll.cpp
        message/NavSbas.cpp
        message/NavSbasPoll.cpp
        message/NavOrb.cpp
        message/NavOrbPoll.cpp
        message/NavSat.cpp
        message/NavSatPoll.cpp
        message/NavGeofence.cpp
        message/NavGeofencePoll.cpp
        message/NavEkfstatus.cpp
        message/NavEkfstatusPoll.cpp
        message/NavAopstatus.cpp
        message/NavAopstatusU8.cpp
        message/NavAopstatusPoll.cpp
        message/NavEoe.cpp
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
        message/CfgRate.cpp        
        message/CfgRatePoll.cpp
        message/CfgCfg.cpp
        message/CfgFxn.cpp
        message/CfgFxnPoll.cpp
        message/CfgRxm.cpp
        message/CfgRxmPoll.cpp
        message/CfgEkf.cpp
        message/CfgEkfPoll.cpp
        message/CfgAnt.cpp
        message/CfgAntPoll.cpp
        message/CfgSbas.cpp
        message/CfgSbasPoll.cpp
        message/CfgNmeaExtV1.cpp
        message/CfgNmeaExt.cpp
        message/CfgNmea.cpp
        message/CfgNmeaPoll.cpp
        message/CfgUsb.cpp
        message/CfgUsbPoll.cpp
        message/CfgTmode.cpp
        message/CfgTmodePoll.cpp
        message/CfgOdo.cpp
        message/CfgOdoPoll.cpp
        message/CfgNvs.cpp
        message/CfgNavx5.cpp
        message/CfgNavx5Poll.cpp
        message/CfgNav5.cpp
        message/CfgNav5Poll.cpp
        message/CfgEsfgwt.cpp
        message/CfgEsfgwtPoll.cpp
        message/CfgTp5.cpp
        message/CfgTp5PollSelect.cpp
        message/CfgTp5Poll.cpp
        message/CfgPm.cpp
        message/CfgPmPoll.cpp
        message/CfgRinv.cpp
        message/CfgRinvPoll.cpp
        message/CfgItfm.cpp
        message/CfgItfmPoll.cpp
        message/CfgPm2.cpp
        message/CfgPm2Poll.cpp
        message/CfgTmode2.cpp
        message/CfgTmode2Poll.cpp
        message/CfgGnss.cpp
        message/CfgGnssPoll.cpp
        message/CfgLogfilter.cpp
        message/CfgLogfilterPoll.cpp
        message/CfgTxslot.cpp
        message/CfgPwr.cpp
        message/CfgEsrc.cpp
        message/CfgEsrcPoll.cpp
        message/CfgDosc.cpp
        message/CfgDoscPoll.cpp
        message/CfgSmgr.cpp
        message/CfgSmgrPoll.cpp
        message/CfgGeofence.cpp
        message/CfgGeofencePoll.cpp
        message/CfgFixseed.cpp
        message/CfgDynseed.cpp
        message/CfgPms.cpp
        message/CfgPmsPoll.cpp
        message/MonIo.cpp
        message/MonIoPoll.cpp
        message/MonVer.cpp
        message/MonVerPoll.cpp
        message/MonMsgpp.cpp
        message/MonMsgppPoll.cpp
        message/MonRxbuf.cpp
        message/MonRxbufPoll.cpp
        message/MonTxbuf.cpp
        message/MonTxbufPoll.cpp
        message/MonHw.cpp
        message/MonHwPoll.cpp
        message/MonHw2.cpp
        message/MonHw2Poll.cpp
        message/MonRxr.cpp
        message/MonPatch.cpp
        message/MonPatchPoll.cpp
        message/MonGnss.cpp
        message/MonGnssPoll.cpp
        message/AidReq.cpp
        message/AidIni.cpp
        message/AidIniPoll.cpp
        message/AidHui.cpp        
        message/AidHuiPoll.cpp
        message/AidData.cpp
        message/AidAlm.cpp
        message/AidAlmPollSv.cpp
        message/AidAlmPoll.cpp
        message/AidEph.cpp
        message/AidEphPollSv.cpp
        message/AidEphPoll.cpp
        message/AidAlpsrv.cpp
        message/AidAlpsrvUpdate.cpp
        message/AidAopU8.cpp
        message/AidAop.cpp
        message/AidAopPollSv.cpp
        message/AidAopPoll.cpp
        message/AidAlp.cpp
        message/AidAlpStatus.cpp
        message/AidAlpData.cpp
        message/TimTp.cpp
        message/TimTpPoll.cpp
        message/TimTm2.cpp
        message/TimTm2Poll.cpp
        message/TimSvin.cpp
        message/TimSvinPoll.cpp
        message/TimVrfy.cpp        
        message/TimVrfyPoll.cpp
        message/EsfStatus.cpp
        message/EsfStatusPoll.cpp
        message/MgaGpsEph.cpp
        message/MgaGpsAlm.cpp
        message/MgaGpsHealth.cpp
        message/MgaGpsUtc.cpp
        message/MgaGpsIono.cpp
        message/MgaGalEph.cpp
        message/MgaGalAlm.cpp
        message/MgaGalTimeoffset.cpp
        message/MgaGalUtc.cpp
        message/MgaBdsEph.cpp
        message/MgaBdsAlm.cpp
        message/MgaBdsHealth.cpp
        message/MgaBdsUtc.cpp
        message/MgaBdsIono.cpp
        message/MgaQzssEph.cpp
        message/MgaQzssAlm.cpp
        message/MgaQzssHealth.cpp
        message/MgaGloEph.cpp
        message/MgaGloAlm.cpp
        message/MgaGloTimeoffset.cpp
        message/MgaAno.cpp
        message/MgaFlashData.cpp
        message/MgaFlashStop.cpp
        message/MgaFlashAck.cpp
        message/MgaIniPosXyz.cpp
        message/MgaIniPosLlh.cpp
        message/MgaIniTimeUtc.cpp
        message/MgaIniTimeGnss.cpp
        message/MgaIniClkd.cpp
        message/MgaIniFreq.cpp
        message/MgaIniEop.cpp
        message/MgaAck.cpp
        message/MgaDbd.cpp
        message/MgaDbdPoll.cpp
        message/LogErase.cpp
        message/LogString.cpp
        message/LogCreate.cpp
        message/LogInfo.cpp
        message/LogInfoPoll.cpp
        message/LogRetrieve.cpp
        message/LogRetrievepos.cpp
        message/LogRetrievestring.cpp
        message/LogFindtimeCmd.cpp
        message/LogFindtime.cpp
        message/LogRetrieveposextra.cpp
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
    target_link_libraries (${name} ${CC_PLUGIN_LIBRARIES})
    qt5_use_modules(${name} Core)
    
    # For some reason message/AidHui fails to compile in Release mode with g++
    if (CMAKE_COMPILER_IS_GNUCC AND ("${CMAKE_BUILD_TYPE}" STREQUAL "Release"))
        set_source_files_properties (message/AidHui.cpp PROPERTIES COMPILE_FLAGS "-O2")
    endif () 
    
    install (
        TARGETS ${name}
        DESTINATION ${PLUGIN_INSTALL_DIR})
    
endfunction()

######################################################################

if (NOT "${CC_UBLOX_QT_DIR}" STREQUAL "")
    list (APPEND CMAKE_PREFIX_PATH ${CC_UBLOX_QT_DIR})
endif ()

find_package(Qt5Core)

if (NOT Qt5Core_FOUND)
    message (WARNING "Can NOT compile ublox protocol plugin due to missing QT5 Core library")
    return ()
endif ()

if (NOT CC_UBLOX_FULL_SOLUTION)
    if (EXISTS "${INSTALL_DIR}/cmake/CommsChampionConfig.cmake")
        list (APPEND CMAKE_PREFIX_PATH "${INSTALL_DIR}/cmake")
        FILE(GLOB_RECURSE comms.headers "${INSTALL_DIR}/include/comms/*.h")
        add_custom_target(comms.headers SOURCES ${comms.headers})
        FILE(GLOB_RECURSE cc.headers "${INSTALL_DIR}/include/comms_champion/*.h")
        add_custom_target(cc.headers SOURCES ${cc.headers})
    endif ()
    
    if (NOT "${CC_MAIN_INSTALL_DIR}" STREQUAL "")
        list (APPEND CMAKE_PREFIX_PATH "${CC_MAIN_INSTALL_DIR}/cmake")
    endif ()
    
    
    find_package(CommsChampion)
    
    if (NOT CC_COMMS_CHAMPION_FOUND)
        message (WARNING "Can NOT compile mqtt protocol plugin due to missing CommsChampion library")
        return ()
    endif ()
    
    include_directories(${CC_INCLUDE_DIRS})
    link_directories(${CC_PLUGIN_LIBRARY_DIRS})
endif ()   

if (CMAKE_COMPILER_IS_GNUCC)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ftemplate-backtrace-limit=0")
endif ()
    
cc_plugin_ublox ()

if (CC_UBLOX_FULL_SOLUTION)
    add_dependencies(${THIS_PLUGIN_NAME} ${CC_EXTERNAL_TGT})
endif ()

FILE(GLOB_RECURSE plugin.headers "*.h")
add_custom_target(cc_plugin.headers SOURCES ${plugin.headers})
