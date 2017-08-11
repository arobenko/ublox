set (ALL_MESSAGES_LIB "all_messages")

######################################################################

function (cc_plugin_ublox_all_messages)
    set (name "${ALL_MESSAGES_LIB}")

    set (src
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
        message/NavTimels.cpp
        message/NavTimelsPoll.cpp
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
        message/RxmSfrbx.cpp
        message/RxmMeasx.cpp
        message/RxmRawx.cpp
        message/RxmRawxPoll.cpp
        message/RxmSvsi.cpp
        message/RxmSvsiPoll.cpp
        message/RxmAlm.cpp
        message/RxmAlmPollSv.cpp
        message/RxmAlmPoll.cpp
        message/RxmEph.cpp
        message/RxmEphPollSv.cpp
        message/RxmEphPoll.cpp
        message/RxmPmreqV0.cpp
        message/RxmPmreq.cpp
        message/RxmRlmShort.cpp
        message/RxmRlmLong.cpp
        message/RxmImes.cpp
        message/RxmImesPoll.cpp
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
        message/CfgHnr.cpp
        message/CfgHnrPoll.cpp
        message/CfgEsrc.cpp
        message/CfgEsrcPoll.cpp
        message/CfgDosc.cpp
        message/CfgDoscPoll.cpp
        message/CfgSmgr.cpp
        message/CfgSmgrPoll.cpp
        message/CfgGeofence.cpp
        message/CfgGeofencePoll.cpp
        message/CfgDgnss.cpp
        message/CfgDgnssPoll.cpp
        message/CfgTmode3.cpp
        message/CfgTmode3Poll.cpp
        message/CfgFixseed.cpp
        message/CfgDynseed.cpp
        message/CfgPms.cpp
        message/CfgPmsPoll.cpp
        message/UpdSosRestored.cpp
        message/UpdSosAck.cpp
        message/UpdSosClear.cpp
        message/UpdSosCreate.cpp
        message/UpdSosPoll.cpp
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
        message/MonSmgr.cpp
        message/MonSmgrPoll.cpp
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
        message/TimDosc.cpp
        message/TimTos.cpp
        message/TimSmeas.cpp
        message/TimVcocal.cpp
        message/TimVcocalExt.cpp
        message/TimVcocalStop.cpp
        message/TimVcocalPoll.cpp
        message/TimFchg.cpp
        message/TimFchgPoll.cpp
        message/TimHoc.cpp
        message/EsfMeas.cpp
        message/EsfMeasPoll.cpp
        message/EsfStatus.cpp
        message/EsfStatusPoll.cpp
        message/EsfIns.cpp
        message/EsfInsPoll.cpp
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
        message/SecSign.cpp
        message/SecUniqid.cpp
        field/MsgId.cpp
        field/common.cpp
        field/nav.cpp
        field/rxm.cpp
        field/inf.cpp
        field/cfg.cpp
    )

    add_library (${name} STATIC ${src})
    target_link_libraries (${name} ${CC_PLUGIN_LIBRARIES})
    qt5_use_modules(${name} Core)

    # For some reason message/AidHui fails to compile in Release mode with g++
    if (CMAKE_COMPILER_IS_GNUCC AND ("${CMAKE_BUILD_TYPE}" STREQUAL "Release"))
        set_source_files_properties (message/AidHui.cpp PROPERTIES COMPILE_FLAGS "-O2")
    endif ()

endfunction()

######################################################################

function (cc_plugin_ublox idx)
    set (name "ublox${idx}")

    set (json_suffix)
    if (NOT "${idx}" STREQUAL "")
        set (json_suffix "-${idx}")
    endif ()

    set (meta_file "${CMAKE_CURRENT_SOURCE_DIR}/ublox${json_suffix}.json")
    set (stamp_file "${CMAKE_CURRENT_BINARY_DIR}/ublox${idx}_refresh_stamp.txt")

    if ((NOT EXISTS ${stamp_file}) OR (${meta_file} IS_NEWER_THAN ${stamp_file}))
        execute_process(
            COMMAND ${CMAKE_COMMAND} -E touch ${CMAKE_CURRENT_SOURCE_DIR}/Plugin.h)
        execute_process(
            COMMAND ${CMAKE_COMMAND} -E touch ${stamp_file})
    endif ()

    set (suffix)
    if (NOT "${idx}" STREQUAL "")
        set (suffix "_ublox${idx}")
    endif ()

    set (src
        Plugin${suffix}.cpp
        Protocol.cpp
    )

    set (hdr
        Plugin${suffix}.h
    )

    qt5_wrap_cpp(
        moc
        ${hdr}
    )

    add_library (${name} SHARED ${src} ${moc})
    target_link_libraries (${name} ${ALL_MESSAGES_LIB} ${CC_PLUGIN_LIBRARIES})
    qt5_use_modules(${name} Core)

    install (
        TARGETS ${name}
        DESTINATION ${PLUGIN_INSTALL_DIR})

    if (CC_UBLOX_FULL_SOLUTION)
        add_dependencies(${name} ${CC_EXTERNAL_TGT})
    endif ()

    if (NOT "${idx}" STREQUAL "")
        target_compile_definitions(${name} PRIVATE -DUBLOX${idx}_ONLY)
    endif ()

endfunction()

######################################################################

function (cc_plugin_install_config file)
    install (
        FILES ${file}
        DESTINATION ${CONFIG_INSTALL_DIR}
    )

    if (CC_UBLOX_FULL_SOLUTION)
        install (
            FILES ${file}
            DESTINATION ${CONFIG_INSTALL_DIR}
            RENAME "default.cfg"
        )
    endif()

endfunction ()

######################################################################

function (cc_plugin_config)
    set (config_file ${CMAKE_CURRENT_SOURCE_DIR}/config/ublox.cfg)
    if (WIN32)
        set (match_str "/dev/ttyACM0")
        set (replacement_str "COM1")
        set (output_file "${CMAKE_CURRENT_BINARY_DIR}/ublox.cfg")

        file (READ ${config_file} config_text)
        string (REGEX REPLACE "${match_str}" "${replacement_str}" modified_config_text "${config_text}")
        file (WRITE "${output_file}" "${modified_config_text}")

        set (config_file ${output_file})
    endif ()

    cc_plugin_install_config (${config_file})
endfunction ()

######################################################################

if (NOT Qt5Core_FOUND)
    message (WARNING "Can NOT compile ublox protocol plugin due to missing QT5 Core library")
    return ()
endif ()

if (CMAKE_COMPILER_IS_GNUCC)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ftemplate-backtrace-limit=0")
endif ()

cc_plugin_ublox_all_messages()

if (CC_UBLOX_PLUGIN_ALL)
    cc_plugin_ublox("")
    cc_plugin_config ()
endif ()

if (CC_UBLOX_PLUGIN_UBLOX8)
    cc_plugin_ublox("8")
endif ()

if (CC_UBLOX_PLUGIN_UBLOX7)
    cc_plugin_ublox("7")
endif ()

if (CC_UBLOX_PLUGIN_UBLOX6)
    cc_plugin_ublox("6")
endif ()

if (CC_UBLOX_PLUGIN_UBLOX5)
    cc_plugin_ublox("5")
endif ()


FILE(GLOB_RECURSE plugin.headers "*.h")
add_custom_target(cc_plugin.headers SOURCES ${plugin.headers})
