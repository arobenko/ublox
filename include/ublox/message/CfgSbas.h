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
    CfgSbasField_mode_enabled,
    CfgSbasField_mode_test,
    CfgSbasField_mode_numOfValues
};

enum
{
    CfgSbasField_usage_range,
    CfgSbasField_usage_diffCorr,
    CfgSbasField_usage_integrity,
    CfgSbasField_usage_numOfValues
};

enum
{
    CfgSbasField_scanmode2_PRN152,
    CfgSbasField_scanmode2_PRN153,
    CfgSbasField_scanmode2_PRN154,
    CfgSbasField_scanmode2_PRN155,
    CfgSbasField_scanmode2_PRN156,
    CfgSbasField_scanmode2_PRN157,
    CfgSbasField_scanmode2_PRN158,
    CfgSbasField_scanmode2_numOfValues
};

enum
{
    CfgSbasField_scanmode1_PRN120,
    CfgSbasField_scanmode1_PRN121,
    CfgSbasField_scanmode1_PRN122,
    CfgSbasField_scanmode1_PRN123,
    CfgSbasField_scanmode1_PRN124,
    CfgSbasField_scanmode1_PRN125,
    CfgSbasField_scanmode1_PRN126,
    CfgSbasField_scanmode1_PRN127,
    CfgSbasField_scanmode1_PRN128,
    CfgSbasField_scanmode1_PRN129,
    CfgSbasField_scanmode1_PRN130,
    CfgSbasField_scanmode1_PRN131,
    CfgSbasField_scanmode1_PRN132,
    CfgSbasField_scanmode1_PRN133,
    CfgSbasField_scanmode1_PRN134,
    CfgSbasField_scanmode1_PRN135,
    CfgSbasField_scanmode1_PRN136,
    CfgSbasField_scanmode1_PRN137,
    CfgSbasField_scanmode1_PRN138,
    CfgSbasField_scanmode1_PRN139,
    CfgSbasField_scanmode1_PRN140,
    CfgSbasField_scanmode1_PRN141,
    CfgSbasField_scanmode1_PRN142,
    CfgSbasField_scanmode1_PRN143,
    CfgSbasField_scanmode1_PRN144,
    CfgSbasField_scanmode1_PRN145,
    CfgSbasField_scanmode1_PRN146,
    CfgSbasField_scanmode1_PRN147,
    CfgSbasField_scanmode1_PRN148,
    CfgSbasField_scanmode1_PRN149,
    CfgSbasField_scanmode1_PRN150,
    CfgSbasField_scanmode1_PRN151,
    CfgSbasField_scanmode1_numOfValues
};

using CfgSbasField_mode =
    field::common::X1T<
        comms::option::BitmaskReservedBits<0xfc, 0>
    >;
using CfgSbasField_usage =
    field::common::X1T<
        comms::option::BitmaskReservedBits<0xf8, 0>
    >;
using CfgSbasField_maxSBAS =
    field::common::U1T<
        comms::option::ValidNumValueRange<0, 3>
    >;
using CfgSbasField_scanmode2 =
    field::common::X1T<
        comms::option::BitmaskReservedBits<0x80, 0>
    >;
using CfgSbasField_scanmode1 = field::common::X4;


using CfgSbasFields = std::tuple<
    CfgSbasField_mode,
    CfgSbasField_usage,
    CfgSbasField_maxSBAS,
    CfgSbasField_scanmode2,
    CfgSbasField_scanmode1
>;

template <typename TMsgBase = Message>
class CfgSbas : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_SBAS>,
        comms::option::FieldsImpl<CfgSbasFields>,
        comms::option::DispatchImpl<CfgSbas<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_SBAS>,
        comms::option::FieldsImpl<CfgSbasFields>,
        comms::option::DispatchImpl<CfgSbas<TMsgBase> >
    > Base;
public:

    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_mode,
        FieldIdx_usage,
        FieldIdx_maxSBAS,
        FieldIdx_scanmode2,
        FieldIdx_scanmode1,
        FieldIdx_numOfValues ///< number of available fields
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    /// @brief Default constructor
    CfgSbas() = default;

    /// @brief Copy constructor
    CfgSbas(const CfgSbas&) = default;

    /// @brief Move constructor
    CfgSbas(CfgSbas&& other) = default;

    /// @brief Destructor
    virtual ~CfgSbas() = default;

    /// @brief Copy assignment
    CfgSbas& operator=(const CfgSbas&) = default;

    /// @brief Move assignment
    CfgSbas& operator=(CfgSbas&&) = default;
};


}  // namespace message

}  // namespace ublox

