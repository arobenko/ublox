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

enum
{
    NavSolField_flags_GPSfixOK,
    NavSolField_flags_DiffSoln,
    NavSolField_flags_WKNSET,
    NavSolField_flags_TOWSET,
    NavSolField_flags_numOfValues
};


using NavSolField_iTOW = field::nav::iTOW;
using NavSolField_fTOW = field::nav::fTOW;
using NavSolField_week = field::nav::week;
using NavSolField_gpsFix = field::nav::gpsFix;
using NavSolField_flags =
    field::common::X1T<
        comms::option::BitmaskReservedBits<0xf0, 0>
    >;
using NavSolField_ecefX = field::nav::ecefX;
using NavSolField_ecefY = field::nav::ecefY;
using NavSolField_ecefZ = field::nav::ecefZ;
using NavSolField_pAcc = field::nav::pAcc;
using NavSolField_ecefVX = field::nav::ecefVX;
using NavSolField_ecefVY = field::nav::ecefVY;
using NavSolField_ecefVZ = field::nav::ecefVZ;
using NavSolField_sAcc = field::nav::sAcc;
using NavSolField_pDOP = field::nav::pDOP;
using NavSolField_reserved1 = field::common::res1;
using NavSolField_numSV = field::nav::numSV;
using NavSolField_reserved2 = field::common::res4;


using NavSolFields = std::tuple<
    NavSolField_iTOW,
    NavSolField_fTOW,
    NavSolField_week,
    NavSolField_gpsFix,
    NavSolField_flags,
    NavSolField_ecefX,
    NavSolField_ecefY,
    NavSolField_ecefZ,
    NavSolField_pAcc,
    NavSolField_ecefVX,
    NavSolField_ecefVY,
    NavSolField_ecefVZ,
    NavSolField_sAcc,
    NavSolField_pDOP,
    NavSolField_reserved1,
    NavSolField_numSV,
    NavSolField_reserved2
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
        FieldIdx_iTOW,
        FieldIdx_fTOW,
        FieldIdx_week,
        FieldIdx_gpsFix,
        FieldIdx_flags,
        FieldIdx_ecefX,
        FieldIdx_ecefY,
        FieldIdx_ecefZ,
        FieldIdx_pAcc,
        FieldIdx_ecefVX,
        FieldIdx_ecefVY,
        FieldIdx_ecefVZ,
        FieldIdx_sAcc,
        FieldIdx_pDop,
        FieldIdx_reserved1,
        FieldIdx_numSV,
        FieldIdx_reserved2,
        FieldIdx_numOfValues
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    NavSol() = default;
    NavSol(const NavSol&) = default;
    NavSol(NavSol&& other) = default;
    virtual ~NavSol() = default;

    NavSol& operator=(const NavSol&) = default;
    NavSol& operator=(NavSol&&) = default;
};


}  // namespace message

}  // namespace ublox





