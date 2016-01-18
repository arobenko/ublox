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
    NavTimegpsField_valid_towValid,
    NavTimegpsField_valid_weekValid,
    NavTimegpsField_valid_leapSValid,
    NavTimegpsField_valid_numOfValues
};

using NavTimegpsField_iTOW = field::nav::iTOW;
using NavTimegpsField_fTOW = field::nav::fTOW;
using NavTimegpsField_week = field::nav::week;
using NavTimegpsField_leapS = field::common::I1;
using NavTimegpsField_valid = field::common::X1T<comms::option::BitmaskReservedBits<0xf8, 0> >;
using NavTimegpsField_tAcc = field::nav::tAcc;

using NavTimegpsFields = std::tuple<
    NavTimegpsField_iTOW,
    NavTimegpsField_fTOW,
    NavTimegpsField_week,
    NavTimegpsField_leapS,
    NavTimegpsField_valid,
    NavTimegpsField_tAcc
>;

template <typename TMsgBase = Message>
class NavTimegps : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_TIMEGPS>,
        comms::option::FieldsImpl<NavTimegpsFields>,
        comms::option::DispatchImpl<NavTimegps<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_TIMEGPS>,
        comms::option::FieldsImpl<NavTimegpsFields>,
        comms::option::DispatchImpl<NavTimegps<TMsgBase> >
    > Base;
public:

    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_iTOW,
        FieldIdx_fTOW,
        FieldIdx_week,
        FieldIdx_leapS,
        FieldIdx_valid,
        FieldIdx_tAcc,
        FieldIdx_numOfValues ///< number of available fields
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    /// @brief Default constructor
    NavTimegps() = default;

    /// @brief Copy constructor
    NavTimegps(const NavTimegps&) = default;

    /// @brief Move constructor
    NavTimegps(NavTimegps&& other) = default;

    /// @brief Destructor
    virtual ~NavTimegps() = default;

    /// @brief Copy assignment
    NavTimegps& operator=(const NavTimegps&) = default;

    /// @brief Move assignment
    NavTimegps& operator=(NavTimegps&&) = default;
};


}  // namespace message

}  // namespace ublox





