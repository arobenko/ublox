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

enum
{
    AidHuiField_flags_healthValid,
    AidHuiField_flags_utcValid,
    AidHuiField_flags_klobValid,
    AidHuiField_flags_numOfValues ///< number of available fields
};

using AidHuiField_health = field::common::X4;
using AidHuiField_utcA0 = field::common::R8;
using AidHuiField_utcA1 = field::common::R8;
using AidHuiField_utcTOW = field::common::I4;
using AidHuiField_utcWNT = field::common::I2;
using AidHuiField_utcLC = field::common::I2;
using AidHuiField_utcWNF = field::common::I2;
using AidHuiField_utcDN = field::common::I2;
using AidHuiField_utcLSF = field::common::I2;
using AidHuiField_utcSpare = field::common::I2;
using AidHuiField_klobA0 = field::common::R4;
using AidHuiField_klobA1 = field::common::R4;
using AidHuiField_klobA2 = field::common::R4;
using AidHuiField_klobA3 = field::common::R4;
using AidHuiField_klobB0 = field::common::R4;
using AidHuiField_klobB1 = field::common::R4;
using AidHuiField_klobB2 = field::common::R4;
using AidHuiField_klobB3 = field::common::R4;
using AidHuiField_flags =
    field::common::X4T<
        comms::option::BitmaskReservedBits<0xfffffff8, 0>
    >;


using AidHuiFields = std::tuple<
    AidHuiField_health,
    AidHuiField_utcA0,
    AidHuiField_utcA1,
    AidHuiField_utcTOW,
    AidHuiField_utcWNT,
    AidHuiField_utcLC,
    AidHuiField_utcWNF,
    AidHuiField_utcDN,
    AidHuiField_utcLSF,
    AidHuiField_utcSpare,
    AidHuiField_klobA0,
    AidHuiField_klobA1,
    AidHuiField_klobA2,
    AidHuiField_klobA3,
    AidHuiField_klobB0,
    AidHuiField_klobB1,
    AidHuiField_klobB2,
    AidHuiField_klobB3,
    AidHuiField_flags
>;


template <typename TMsgBase = Message>
class AidHui : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_AID_HUI>,
        comms::option::FieldsImpl<AidHuiFields>,
        comms::option::DispatchImpl<AidHui<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_AID_HUI>,
        comms::option::FieldsImpl<AidHuiFields>,
        comms::option::DispatchImpl<AidHui<TMsgBase> >
    > Base;
public:

    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_health,
        FieldIdx_utcA0,
        FieldIdx_utcA1,
        FieldIdx_utcTOW,
        FieldIdx_utcWNT,
        FieldIdx_utcLC,
        FieldIdx_utcWNF,
        FieldIdx_utcDN,
        FieldIdx_utcLSF,
        FieldIdx_utcSpare,
        FieldIdx_klobA0,
        FieldIdx_klobA1,
        FieldIdx_klobA2,
        FieldIdx_klobA3,
        FieldIdx_klobB0,
        FieldIdx_klobB1,
        FieldIdx_klobB2,
        FieldIdx_klobB3,
        FieldIdx_flags,
        FieldIdx_numOfValues
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    /// @brief Default constructor
    AidHui() = default;

    /// @brief Copy constructor
    AidHui(const AidHui&) = default;

    /// @brief Move constructor
    AidHui(AidHui&& other) = default;

    /// @brief Destructor
    virtual ~AidHui() = default;

    /// @brief Copy assignment
    AidHui& operator=(const AidHui&) = default;

    /// @brief Move assignment
    AidHui& operator=(AidHui&&) = default;
};


}  // namespace message

}  // namespace ublox

