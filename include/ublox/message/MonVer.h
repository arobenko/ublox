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
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

using CfgVerField_swVersion = field::common::ZString<30>;
using CfgVerField_hwVersion = field::common::ZString<10>;
using CfgVerField_extensions =
    field::common::ListT<
        field::common::ZString<30>
    >;

using MonVerFields = std::tuple<
    CfgVerField_swVersion,
    CfgVerField_hwVersion,
    CfgVerField_extensions
>;


template <typename TMsgBase = Message>
class MonVer : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_MON_VER>,
        comms::option::FieldsImpl<MonVerFields>,
        comms::option::DispatchImpl<MonVer<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_MON_VER>,
        comms::option::FieldsImpl<MonVerFields>,
        comms::option::DispatchImpl<MonVer<TMsgBase> >
    > Base;
public:

    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_swVersion,
        FieldIdx_hwVersion,
        FieldIdx_extensions,
        FieldIdx_numOfValues ///< number of available fields
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    /// @brief Default constructor
    MonVer() = default;

    /// @brief Copy constructor
    MonVer(const MonVer&) = default;

    /// @brief Move constructor
    MonVer(MonVer&& other) = default;

    /// @brief Destructor
    virtual ~MonVer() = default;

    /// @brief Copy assignment
    MonVer& operator=(const MonVer&) = default;

    /// @brief Move assignment
    MonVer& operator=(MonVer&&) = default;
};


}  // namespace message

}  // namespace ublox

