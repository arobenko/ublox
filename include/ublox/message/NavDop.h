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

using NavDopField_iTOW = field::nav::iTOW;
using NavDopField_gDOP = field::nav::xDOP;
using NavDopField_pDOP = field::nav::pDOP;
using NavDopField_tDOP = field::nav::xDOP;
using NavDopField_vDOP = field::nav::xDOP;
using NavDopField_hDOP = field::nav::xDOP;
using NavDopField_nDOP = field::nav::xDOP;
using NavDopField_eDOP = field::nav::xDOP;

using NavDopFields = std::tuple<
    NavDopField_iTOW,
    NavDopField_gDOP,
    NavDopField_pDOP,
    NavDopField_tDOP,
    NavDopField_vDOP,
    NavDopField_hDOP,
    NavDopField_nDOP,
    NavDopField_eDOP
>;

template <typename TMsgBase = Message>
class NavDop : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_DOP>,
        comms::option::FieldsImpl<NavDopFields>,
        comms::option::DispatchImpl<NavDop<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_DOP>,
        comms::option::FieldsImpl<NavDopFields>,
        comms::option::DispatchImpl<NavDop<TMsgBase> >
    > Base;
public:

    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_iTOW,
        FieldIdx_gDOP,
        FieldIdx_pDOP,
        FieldIdx_tDOP,
        FieldIdx_vDOP,
        FieldIdx_hDOP,
        FieldIdx_nDOP,
        FieldIdx_eDOP,
        FieldIdx_numOfValues ///< number of available fields
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    /// @brief Default constructor
    NavDop() = default;

    /// @brief Copy constructor
    NavDop(const NavDop&) = default;

    /// @brief Move constructor
    NavDop(NavDop&& other) = default;

    /// @brief Destructor
    virtual ~NavDop() = default;

    /// @brief Copy assignment
    NavDop& operator=(const NavDop&) = default;

    /// @brief Move assignment
    NavDop& operator=(NavDop&&) = default;
};


}  // namespace message

}  // namespace ublox





