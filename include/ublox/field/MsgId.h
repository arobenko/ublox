//
// Copyright 2015 (C). Alex Robenko. All rights reserved.
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


#pragma once

#include <cstdint>
#include <limits>
#include <algorithm>
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
        typedef bool (*ValidateFunc)(ublox::MsgId);

        static const ValidateFunc Funcs[] = {
            &MsgIdValueValidator::validateNav,
            &MsgIdValueValidator::validateRxm,
            &MsgIdValueValidator::validateInf,
            &MsgIdValueValidator::validateAck
        };

        ublox::MsgId id = field.value();
        return std::any_of(
            std::begin(Funcs), std::end(Funcs),
            [id](ValidateFunc func) -> bool
            {
                return func(id);
            });
    }

private:
    static constexpr std::uint8_t classId(ublox::MsgId id)
    {
        return static_cast<std::uint8_t>(
            (unsigned)id >> std::numeric_limits<std::uint8_t>::digits);
    }

    static bool validateNav(ublox::MsgId id)
    {
        static const auto NavClassId = classId(MsgId_NAV_POSECEF);

        if (classId(id) != NavClassId) {
            return false;
        }

        static const ublox::MsgId IDs[] = {
            MsgId_NAV_POSECEF,
            MsgId_NAV_POSLLH,
            MsgId_NAV_STATUS,
            MsgId_NAV_DOP,
            MsgId_NAV_SOL,
            MsgId_NAV_POSUTM,
            MsgId_NAV_VELECEF,
            MsgId_NAV_VELNED,
            MsgId_NAV_TIMEGPS,
            MsgId_NAV_TIMEUTC,
            MsgId_NAV_CLOCK,
            MsgId_NAV_SVINFO,
            MsgId_NAV_DGPS,
            MsgId_NAV_SBAS,
            MsgId_NAV_EKFSTATUS
        };

        auto iter = std::lower_bound(std::begin(IDs), std::end(IDs), id);
        return (iter != std::end(IDs)) && (*iter == id);
    }

    static bool validateRxm(ublox::MsgId id)
    {
        static const auto RxmClassId = classId(MsgId_RXM_RAW);

        if (classId(id) != RxmClassId) {
            return false;
        }

        static const ublox::MsgId IDs[] = {
            MsgId_RXM_RAW,
            MsgId_RXM_SFRB,
            MsgId_RXM_SVSI,
            MsgId_RXM_ALM,
            MsgId_RXM_EPH,
            MsgId_RXM_POSREQ,
        };

        auto iter = std::lower_bound(std::begin(IDs), std::end(IDs), id);
        return (iter != std::end(IDs)) && (*iter == id);
    }

    static bool validateInf(ublox::MsgId id)
    {
        static const auto InfClassId = classId(MsgId_INF_ERROR);

        if (classId(id) != InfClassId) {
            return false;
        }

        static const ublox::MsgId IDs[] = {
            MsgId_INF_ERROR,
            MsgId_INF_WARNING,
            MsgId_INF_NOTICE,
            MsgId_INF_TEST,
            MsgId_INF_DEBUG,
            MsgId_INF_USER
        };

        auto iter = std::lower_bound(std::begin(IDs), std::end(IDs), id);
        return (iter != std::end(IDs)) && (*iter == id);
    }

    static bool validateAck(ublox::MsgId id)
    {
        return (ublox::MsgId_ACK_NAK <= id) && (id <= MsgId_ACK_ACK);
    }
};

}  // namespace details

using MsgId =
    comms::field::EnumValue<
        comms::Field<comms::option::BigEndian>,
        ublox::MsgId,
        comms::option::ContentsValidator<details::MsgIdValueValidator>
    >;

}  // namespace field

}  // namespace ublox


