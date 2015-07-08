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

#include "comms/Message.h"
#include "ublox/Message.h"

#include "ublox/field/nav.h"

namespace ublox
{

namespace message
{

using NavSolFields = std::tuple<
    field::nav::ITOW,
    field::nav::Frac,
    field::nav::week,
    field::nav::GPSfix,
    field::nav::Flags,
    field::nav::ECEF_X,
    field::nav::ECEF_Y,
    field::nav::ECEF_Z,
    field::nav::Pacc,
    field::nav::ECEFVX,
    field::nav::ECEFVY,
    field::nav::ECEFVZ,
    field::nav::Sacc,
    field::nav::PDOP,
    field::common::res1,
    field::nav::numSV,
    field::common::res4
>;


template <typename TMsgBase = Message>
class NavSol : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_SOL>,
        comms::option::FieldsImpl<NavSolFields>,
        comms::option::DispatchImpl<NavSol<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_SOL>,
        comms::option::FieldsImpl<NavSolFields>,
        comms::option::DispatchImpl<NavSol<TMsgBase> >
    > Base;
public:
    enum FieldIdx
    {
        FieldIdx_Itow,
        FieldIdx_Frac,
        FieldIdx_Week,
        FieldIdx_GpsFix,
        FieldIdx_Flags,
        FieldIdx_EcefX,
        FieldIdx_EcefY,
        FieldIdx_EcefZ,
        FieldIdx_Pacc,
        FieldIdx_EcefVX,
        FieldIdx_EcefVY,
        FieldIdx_EcefVZ,
        FieldIdx_Sacc,
        FieldIdx_Pdop,
        FieldIdx_Res1,
        FieldIdx_NumSV,
        FieldIdx_Res2,
        FieldIdx_NumOfValues
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_NumOfValues,
        "Number of fields is incorrect");

    NavSol() = default;
    NavSol(const NavSol&) = default;
    NavSol(NavSol&& other)
    {
    }
    virtual ~NavSol() = default;

    NavSol& operator=(const NavSol&) = default;
    NavSol& operator=(NavSol&&) = default;
};


}  // namespace message

}  // namespace ublox





