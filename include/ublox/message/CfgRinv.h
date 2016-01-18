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

#include <algorithm>

#include "comms/Message.h"
#include "ublox/Message.h"
#include "ublox/field/MsgId.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

enum
{
    CfgRinvField_data_dump,
    CfgRinvField_data_binary,
    CfgRinvField_data_numOfValues
};

using CfgRinvField_flags =
    field::common::X1T<
        comms::option::BitmaskReservedBits<0xfc, 0>
    >;

using CfgRinvField_data =
    field::common::ListT<std::uint8_t>;

using CfgRinvFields = std::tuple<
    CfgRinvField_flags,
    CfgRinvField_data
>;

template <typename TMsgBase = Message>
class CfgRinv : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_RINV>,
        comms::option::FieldsImpl<CfgRinvFields>,
        comms::option::DispatchImpl<CfgRinv<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_RINV>,
        comms::option::FieldsImpl<CfgRinvFields>,
        comms::option::DispatchImpl<CfgRinv<TMsgBase> >
    > Base;
public:

    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_flags,
        FieldIdx_data,
        FieldIdx_numOfValues ///< number of available fields
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    /// @brief Default constructor
    CfgRinv() = default;

    /// @brief Copy constructor
    CfgRinv(const CfgRinv&) = default;

    /// @brief Move constructor
    CfgRinv(CfgRinv&& other) = default;

    /// @brief Destructor
    virtual ~CfgRinv() = default;

    /// @brief Copy assignment
    CfgRinv& operator=(const CfgRinv&) = default;

    /// @brief Move assignment
    CfgRinv& operator=(CfgRinv&&) = default;
};


}  // namespace message

}  // namespace ublox

