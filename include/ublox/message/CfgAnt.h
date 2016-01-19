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
#include "ublox/field/MsgId.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

enum
{
    CfgAntField_flags_svcs,
    CfgAntField_flags_csd,
    CfgAntField_flags_ocd,
    CfgAntField_flags_pdwnOnSCD,
    CfgAntField_flags_recovery,
    CfgAntField_flags_numOfValues
};

enum
{
    CfgAntField_pins_pinSwitch,
    CfgAntField_pins_pinSCD,
    CfgAntField_pins_pinOCD,
    CfgAntField_pins_reconfig,
    CfgAntField_pins_numOfValues
};

enum
{
    CfgAntField_pins_reconfig_reconfig,
    CfgAntField_pins_reconfig_numOfValues
};



using CfgAntField_flags =
    field::common::X2T<
        comms::option::BitmaskReservedBits<0xffe0, 0>
    >;

using CfgAntField_pinX =
    field::common::U1T<
        comms::option::FixedBitLength<5>,
        comms::option::ValidNumValueRange<0, 0x1f>
    >;

using CfgAntField_pins =
    field::common::BitfieldT<
        std::tuple<
            CfgAntField_pinX,
            CfgAntField_pinX,
            CfgAntField_pinX,
            field::common::X1T<
                comms::option::FixedBitLength<1>
            >
        >
    >;


using CfgAntFields = std::tuple<
    CfgAntField_flags,
    CfgAntField_pins
>;

template <typename TMsgBase = Message>
class CfgAnt : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_ANT>,
        comms::option::FieldsImpl<CfgAntFields>,
        comms::option::DispatchImpl<CfgAnt<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_ANT>,
        comms::option::FieldsImpl<CfgAntFields>,
        comms::option::DispatchImpl<CfgAnt<TMsgBase> >
    > Base;
public:

    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_flags,
        FieldIdx_pins,
        FieldIdx_numOfValues ///< number of available fields
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    /// @brief Default constructor
    CfgAnt() = default;

    /// @brief Copy constructor
    CfgAnt(const CfgAnt&) = default;

    /// @brief Move constructor
    CfgAnt(CfgAnt&& other) = default;

    /// @brief Destructor
    virtual ~CfgAnt() = default;

    /// @brief Copy assignment
    CfgAnt& operator=(const CfgAnt&) = default;

    /// @brief Move assignment
    CfgAnt& operator=(CfgAnt&&) = default;
};

}  // namespace message

}  // namespace ublox

