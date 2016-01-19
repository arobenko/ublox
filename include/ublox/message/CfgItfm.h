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
    CfgItfmField_config_bbThreshold,
    CfgItfmField_config_cwThreshold,
    CfgItfmField_config_reserved1,
    CfgItfmField_config_enable,
    CfgItfmField_config_numOfValues
};

enum
{
    CfgItfmField_config_enable_enable,
    CfgItfmField_config_enable_numOfValues
};

enum class CfgItfm_AntSetting : std::uint8_t
{
    Unknown,
    Passive,
    Active,
    NumOfValues
};

enum
{
    CfgItfmField_config2_reserved2,
    CfgItfmField_config2_antSetting,
    CfgItfmField_config2_reserved3,
    CfgItfmField_config2_numOfValues
};

using CfgItfmField_config =
    field::common::BitfieldT<
        std::tuple<
            field::common::U1T<
                comms::option::FixedBitLength<4>,
                comms::option::ValidNumValueRange<0, 0xf>
            >,
            field::common::U1T<
                comms::option::FixedBitLength<5>,
                comms::option::ValidNumValueRange<0, 0x1f>
            >,
            field::common::U4T<
                comms::option::FixedBitLength<22>,
                comms::option::ValidNumValueRange<0x16b156, 0x16b156>,
                comms::option::DefaultNumValue<0x16b156>
            >,
            field::common::X1T<
                comms::option::FixedBitLength<1>
            >
        >
    >;

using CfgItfmField_config2 =
    field::common::BitfieldT<
        std::tuple<
            field::common::U2T<
                comms::option::FixedBitLength<12>,
                comms::option::ValidNumValueRange<0x31e, 0x31e>,
                comms::option::DefaultNumValue<0x31e>
            >,
            field::common::EnumT<
                CfgItfm_AntSetting,
                comms::option::FixedBitLength<2>,
                comms::option::ValidNumValueRange<0, (int)CfgItfm_AntSetting::NumOfValues - 1>
            >,
            field::common::res4T<
                comms::option::FixedBitLength<18>
            >
        >
    >;

using CfgItfmFields = std::tuple<
    CfgItfmField_config,
    CfgItfmField_config2
>;

template <typename TMsgBase = Message>
class CfgItfm : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_ITFM>,
        comms::option::FieldsImpl<CfgItfmFields>,
        comms::option::DispatchImpl<CfgItfm<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_ITFM>,
        comms::option::FieldsImpl<CfgItfmFields>,
        comms::option::DispatchImpl<CfgItfm<TMsgBase> >
    > Base;
public:

    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_config,
        FieldIdx_config2,
        FieldIdx_numOfValues ///< number of available fields
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    /// @brief Default constructor
    CfgItfm() = default;

    /// @brief Copy constructor
    CfgItfm(const CfgItfm&) = default;

    /// @brief Move constructor
    CfgItfm(CfgItfm&& other) = default;

    /// @brief Destructor
    virtual ~CfgItfm() = default;

    /// @brief Copy assignment
    CfgItfm& operator=(const CfgItfm&) = default;

    /// @brief Move assignment
    CfgItfm& operator=(CfgItfm&&) = default;
};


}  // namespace message

}  // namespace ublox

