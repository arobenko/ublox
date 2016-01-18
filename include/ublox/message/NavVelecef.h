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

using NavVelecefField_iTOW = field::nav::iTOW;
using NavVelecefField_ecefVX = field::nav::ecefVX;
using NavVelecefField_ecefVY = field::nav::ecefVY;
using NavVelecefField_ecefVZ = field::nav::ecefVZ;
using NavVelecefField_sAcc = field::nav::sAcc;

using NavVelecefFields = std::tuple<
    NavVelecefField_iTOW,
    NavVelecefField_ecefVX,
    NavVelecefField_ecefVY,
    NavVelecefField_ecefVZ,
    NavVelecefField_sAcc
>;


template <typename TMsgBase = Message>
class NavVelecef : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_VELECEF>,
        comms::option::FieldsImpl<NavVelecefFields>,
        comms::option::DispatchImpl<NavVelecef<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_VELECEF>,
        comms::option::FieldsImpl<NavVelecefFields>,
        comms::option::DispatchImpl<NavVelecef<TMsgBase> >
    > Base;
public:

    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_iTOW,
        FieldIdx_ecefVX,
        FieldIdx_ecefVY,
        FieldIdx_ecefVZ,
        FieldIdx_sAcc,
        FieldIdx_numOfValues ///< number of available fields
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    /// @brief Default constructor
    NavVelecef() = default;

    /// @brief Copy constructor
    NavVelecef(const NavVelecef&) = default;

    /// @brief Move constructor
    NavVelecef(NavVelecef&& other) = default;

    /// @brief Destructor
    virtual ~NavVelecef() = default;

    /// @brief Copy assignment
    NavVelecef& operator=(const NavVelecef&) = default;

    /// @brief Move assignment
    NavVelecef& operator=(NavVelecef&&) = default;
};


}  // namespace message

}  // namespace ublox





