//
// Copyright 2015 - 2016 (C). Alex Robenko. All rights reserved.
//

// This file is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

/// @file
/// @brief Definition of the field used to hold ID of the message.

#pragma once

#include <cstdint>
#include <limits>
#include <algorithm>
#include <utility>
#include "comms/comms.h"
#include "ublox/MsgId.h"

namespace ublox
{

namespace field
{

namespace details
{

struct MsgIdValueValidator
{
    template <typename TField>
    bool operator()(const TField& field) const
    {
        using ValidateFunc = bool (*)(ublox::MsgId);
        using FuncInfo = std::pair<std::uint8_t, ValidateFunc>;

        static const FuncInfo Funcs[] = {
            std::make_pair(classId(MsgId_NAV_POSECEF), &MsgIdValueValidator::validateNav),
            std::make_pair(classId(MsgId_RXM_RAW), &MsgIdValueValidator::validateRxm),
            std::make_pair(classId(MsgId_INF_ERROR), &MsgIdValueValidator::validateInf),
            std::make_pair(classId(MsgId_ACK_NAK), &MsgIdValueValidator::validateAck),
            std::make_pair(classId(MsgId_CFG_PRT), &MsgIdValueValidator::validateCfg),
            std::make_pair(classId(MsgId_UPD_SOS), &MsgIdValueValidator::validateUpd),
            std::make_pair(classId(MsgId_MON_IO), &MsgIdValueValidator::validateMon),
            std::make_pair(classId(MsgId_AID_REQ), &MsgIdValueValidator::validateAid),
            std::make_pair(classId(MsgId_TIM_TP), &MsgIdValueValidator::validateTim),
            std::make_pair(classId(MsgId_ESF_STATUS), &MsgIdValueValidator::validateEsf),
            std::make_pair(classId(MsgId_MGA_GPS), &MsgIdValueValidator::validateMga),
            std::make_pair(classId(MsgId_LOG_ERASE), &MsgIdValueValidator::validateLog),
            std::make_pair(classId(MsgId_SEC_SIGN), &MsgIdValueValidator::validateSec),
            std::make_pair(classId(MsgId_HNR_PVT), &MsgIdValueValidator::validateHnr),
        };

        ublox::MsgId id = field.value();
        auto cId = classId(id);
        auto iter =
            std::lower_bound(
                std::begin(Funcs), std::end(Funcs), cId,
                [](const FuncInfo& info, std::uint8_t cIdParam) -> bool
                {
                    return info.first < cIdParam;
                });
        if ((iter == std::end(Funcs)) || (iter->first != cId)) {
            return false;
        }

        return iter->second(id);
    }

private:
    static constexpr std::uint8_t classId(ublox::MsgId id)
    {
        return static_cast<std::uint8_t>(
            (unsigned)id >> std::numeric_limits<std::uint8_t>::digits);
    }

    static bool validateNav(ublox::MsgId id)
    {
        static const ublox::MsgId IDs[] = {
            MsgId_NAV_POSECEF,
            MsgId_NAV_POSLLH,
            MsgId_NAV_STATUS,
            MsgId_NAV_DOP,
            MsgId_NAV_SOL,
            MsgId_NAV_PVT,
            MsgId_NAV_ODO,
            MsgId_NAV_RESETODO,
            MsgId_NAV_VELECEF,
            MsgId_NAV_VELNED,
            MsgId_NAV_TIMEGPS,
            MsgId_NAV_TIMEUTC,
            MsgId_NAV_CLOCK,
            MsgId_NAV_TIMEGLO,
            MsgId_NAV_TIMEBDS,
            MsgId_NAV_TIMEGAL,
            MsgId_NAV_TIMELS,
            MsgId_NAV_SVINFO,
            MsgId_NAV_DGPS,
            MsgId_NAV_SBAS,
            MsgId_NAV_ORB,
            MsgId_NAV_SAT,
            MsgId_NAV_GEOFENCE,
            MsgId_NAV_EKFSTATUS,
            MsgId_NAV_AOPSTATUS,
            MsgId_NAV_EOE
        };

        auto iter = std::lower_bound(std::begin(IDs), std::end(IDs), id);
        return (iter != std::end(IDs)) && (*iter == id);
    }

    static bool validateRxm(ublox::MsgId id)
    {
        static const ublox::MsgId IDs[] = {
            MsgId_RXM_RAW,
            MsgId_RXM_SFRB,
            MsgId_RXM_SFRBX,
            MsgId_RXM_MEASX,
            MsgId_RXM_RAWX,
            MsgId_RXM_SVSI,
            MsgId_RXM_ALM,
            MsgId_RXM_EPH,
            MsgId_RXM_PMREQ,
            MsgId_RXM_RLM,
            MsgId_RXM_IMES,
        };

        auto iter = std::lower_bound(std::begin(IDs), std::end(IDs), id);
        return (iter != std::end(IDs)) && (*iter == id);
    }

    static bool validateInf(ublox::MsgId id)
    {
        static const ublox::MsgId IDs[] = {
            MsgId_INF_ERROR,
            MsgId_INF_WARNING,
            MsgId_INF_NOTICE,
            MsgId_INF_TEST,
            MsgId_INF_DEBUG
        };

        auto iter = std::lower_bound(std::begin(IDs), std::end(IDs), id);
        return (iter != std::end(IDs)) && (*iter == id);
    }

    static bool validateAck(ublox::MsgId id)
    {
        return (ublox::MsgId_ACK_NAK <= id) && (id <= MsgId_ACK_ACK);
    }

    static bool validateCfg(ublox::MsgId id)
    {
        static const ublox::MsgId IDs[] = {
            MsgId_CFG_PRT,
            MsgId_CFG_MSG,
            MsgId_CFG_INF,
            MsgId_CFG_RST,
            MsgId_CFG_DAT,
            MsgId_CFG_TP,
            MsgId_CFG_RATE,
            MsgId_CFG_CFG,
            MsgId_CFG_FXN,
            MsgId_CFG_RXM,
            MsgId_CFG_EKF,
            MsgId_CFG_ANT,
            MsgId_CFG_SBAS,
            MsgId_CFG_NMEA,
            MsgId_CFG_USB,
            MsgId_CFG_TMODE,
            MsgId_CFG_ODO,
            MsgId_CFG_NVS,
            MsgId_CFG_NAVX5,
            MsgId_CFG_NAV5,
            MsgId_CFG_ESFGWT,
            MsgId_CFG_TP5,
            MsgId_CFG_PM,
            MsgId_CFG_RINV,
            MsgId_CFG_ITFM,
            MsgId_CFG_PM2,
            MsgId_CFG_TMODE2,
            MsgId_CFG_GNSS,
            MsgId_CFG_LOGFILTER,
            MsgId_CFG_TXSLOT,
            MsgId_CFG_PWR,
            MsgId_CFG_HNR,
            MsgId_CFG_ESRC,
            MsgId_CFG_DOSC,
            MsgId_CFG_SMGR,
            MsgId_CFG_GEOFENCE,
            MsgId_CFG_DGNSS,
            MsgId_CFG_TMODE3,
            MsgId_CFG_FIXSEED,
            MsgId_CFG_DYNSEED,
            MsgId_CFG_PMS
        };

        auto iter = std::lower_bound(std::begin(IDs), std::end(IDs), id);
        return (iter != std::end(IDs)) && (*iter == id);
    }

    static bool validateUpd(ublox::MsgId id)
    {
        static const ublox::MsgId IDs[] = {
            MsgId_UPD_SOS,
        };

        auto iter = std::lower_bound(std::begin(IDs), std::end(IDs), id);
        return (iter != std::end(IDs)) && (*iter == id);
    }

    static bool validateMon(ublox::MsgId id)
    {
        static const ublox::MsgId IDs[] = {
            MsgId_MON_IO,
            MsgId_MON_VER,
            MsgId_MON_MSGPP,
            MsgId_MON_RXBUF,
            MsgId_MON_TXBUF,
            MsgId_MON_HW,
            MsgId_MON_HW2,
            MsgId_MON_RXR,
            MsgId_MON_PATCH,
            MsgId_MON_GNSS,
            MsgId_MON_SMGR,
        };

        auto iter = std::lower_bound(std::begin(IDs), std::end(IDs), id);
        return (iter != std::end(IDs)) && (*iter == id);
    }

    static bool validateAid(ublox::MsgId id)
    {
        static const ublox::MsgId IDs[] = {
            MsgId_AID_REQ,
            MsgId_AID_INI,
            MsgId_AID_HUI,
            MsgId_AID_DATA,
            MsgId_AID_ALM,
            MsgId_AID_EPH,
            MsgId_AID_ALPSRV,
            MsgId_AID_AOP,
            MsgId_AID_ALP
        };

        auto iter = std::lower_bound(std::begin(IDs), std::end(IDs), id);
        return (iter != std::end(IDs)) && (*iter == id);
    }

    static bool validateTim(ublox::MsgId id)
    {
        static const ublox::MsgId IDs[] = {
            MsgId_TIM_TP,
            MsgId_TIM_TM2,
            MsgId_TIM_SVIN,
            MsgId_TIM_VRFY,
            MsgId_TIM_DOSC,
            MsgId_TIM_TOS,
            MsgId_TIM_SMEAS,
            MsgId_TIM_VCOCAL,
            MsgId_TIM_FCHG,
            MsgId_TIM_HOC,
        };

        auto iter = std::lower_bound(std::begin(IDs), std::end(IDs), id);
        return (iter != std::end(IDs)) && (*iter == id);
    }

    static bool validateEsf(ublox::MsgId id)
    {
        static const ublox::MsgId IDs[] = {
            MsgId_ESF_MEAS,
            MsgId_ESF_RAW,
            MsgId_ESF_STATUS,
            MsgId_ESF_INS,
        };

        auto iter = std::lower_bound(std::begin(IDs), std::end(IDs), id);
        return (iter != std::end(IDs)) && (*iter == id);
    }

    static bool validateMga(ublox::MsgId id)
    {
        static const ublox::MsgId IDs[] = {
            MsgId_MGA_GPS,
            MsgId_MGA_GAL,
            MsgId_MGA_BDS,
            MsgId_MGA_QZSS,
            MsgId_MGA_GLO,
            MsgId_MGA_ANO,
            MsgId_MGA_FLASH,
            MsgId_MGA_INI,
            MsgId_MGA_ACK,
            MsgId_MGA_DBD,
        };

        auto iter = std::lower_bound(std::begin(IDs), std::end(IDs), id);
        return (iter != std::end(IDs)) && (*iter == id);
    }


    static bool validateLog(ublox::MsgId id)
    {
        static const ublox::MsgId IDs[] = {
            MsgId_LOG_ERASE,
            MsgId_LOG_STRING,
            MsgId_LOG_CREATE,
            MsgId_LOG_INFO,
            MsgId_LOG_RETRIEVE,
            MsgId_LOG_RETRIEVEPOS,
            MsgId_LOG_RETRIEVESTRING,
            MsgId_LOG_FINDTIME,
            MsgId_LOG_RETRIEVEPOSEXTRA,
        };

        auto iter = std::lower_bound(std::begin(IDs), std::end(IDs), id);
        return (iter != std::end(IDs)) && (*iter == id);
    }

    static bool validateSec(ublox::MsgId id)
    {
        static const ublox::MsgId IDs[] = {
            MsgId_SEC_SIGN,
            MsgId_SEC_UNIQID,
        };

        auto iter = std::lower_bound(std::begin(IDs), std::end(IDs), id);
        return (iter != std::end(IDs)) && (*iter == id);
    }

    static bool validateHnr(ublox::MsgId id)
    {
        static const ublox::MsgId IDs[] = {
            MsgId_HNR_PVT,
        };

        auto iter = std::lower_bound(std::begin(IDs), std::end(IDs), id);
        return (iter != std::end(IDs)) && (*iter == id);
    }
};

}  // namespace details

/// @brief Definition of the field that represents message ID.
/// @details See <a href="https://dl.dropboxusercontent.com/u/46999418/comms_champion/comms/html/classcomms_1_1field_1_1EnumValue.html">comms::field::EnumValue</a>
///     for details.
using MsgId =
    comms::field::EnumValue<
        comms::Field<comms::option::BigEndian>,
        ublox::MsgId,
        comms::option::ContentsValidator<details::MsgIdValueValidator>
    >;

}  // namespace field

}  // namespace ublox

