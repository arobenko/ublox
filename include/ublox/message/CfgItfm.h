//
// Copyright 2015 - 2017 (C). Alex Robenko. All rights reserved.
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

/// @file
/// @brief Contains definition of CFG-ITFM message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the CFG-ITFM message fields.
/// @see CfgItfm
struct CfgItfmFields
{
    /// @brief Value enumeration for @ref antSetting member field in @ref config2 bitmask.
    enum class AntSetting : std::uint8_t
    {
        Unknown, ///< @b unknown
        Passive, ///< @b passive
        Active, ///< @b active
        NumOfValues ///< number of available values
    };

    /// @brief Definition of "bbThreshold" member field in @ref config bitmask.
    using bbThreshold =
        field::common::U1T<
            comms::option::FixedBitLength<4>,
            comms::option::ValidNumValueRange<0, 0xf>
        >;

    /// @brief Definition of "cwThreshold" member field in @ref config bitmask.
    using cwThreshold =
        field::common::U1T<
            comms::option::FixedBitLength<5>,
            comms::option::ValidNumValueRange<0, 0x1f>
        >;

    /// @brief Definition of "algorithmBits" member field in @ref config bitmask.
    using algorithmBits =
        field::common::U4T<
            comms::option::FixedBitLength<22>,
            comms::option::ValidNumValueRange<0x16b156, 0x16b156>,
            comms::option::DefaultNumValue<0x16b156>
        >;

    /// @brief Definition of the bitmask member field with single "enable" bit
    ///     in @ref config bitfield.
    struct enable : public
        field::common::X1T<
            comms::option::FixedBitLength<1>
        >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS_SEQ macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS_SEQ(bit);
    };

    /// @brief Definition of "generalBits" member field in @ref config2 bitmask.
    using generalBits =
        field::common::U2T<
            comms::option::FixedBitLength<12>,
            comms::option::ValidNumValueRange<0x31e, 0x31e>,
            comms::option::DefaultNumValue<0x31e>
        >;

    /// @brief Definition of "antSetting" member field in @ref config2 bitmask.
    using antSetting =
        field::common::EnumT<
            AntSetting,
            comms::option::FixedBitLength<2>,
            comms::option::ValidNumValueRange<0, (int)AntSetting::NumOfValues - 1>
        >;

    /// @brief Definition of the bitmask member field with single "enable2" bit
    ///     in @ref config2 bitfield.
    struct enable2 : public
        field::common::X1T<
            comms::option::FixedBitLength<1>
        >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS_SEQ macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS_SEQ(bit);
    };


    /// @brief Definition of "config" field.
    struct config : public
        field::common::BitfieldT<
            std::tuple<
                bbThreshold,
                cwThreshold,
                algorithmBits,
                enable
            >
        >
    {
        /// @brief Allow access to internal fields.
        /// @details See definition of @b COMMS_FIELD_MEMBERS_ACCESS macro
        ///     related to @b comms::field::Bitfield class from COMMS library
        ///     for details.
        COMMS_FIELD_MEMBERS_ACCESS(bbThreshold, cwThreshold, algorithmBits, enable);
    };

    /// @brief Definition of "config2" field.
    struct config2 : public
        field::common::BitfieldT<
            std::tuple<
                generalBits,
                antSetting,
                enable2,
                field::common::res4T<
                    comms::option::FixedBitLength<17>
                >
            >
        >
    {
        /// @brief Allow access to internal fields.
        /// @details See definition of @b COMMS_FIELD_MEMBERS_ACCESS macro
        ///     related to @b comms::field::Bitfield class from COMMS library
        ///     for details.
        COMMS_FIELD_MEMBERS_ACCESS(generalBits, antSetting, enable2, reserved);
    };

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        config,
        config2
    >;
};

/// @brief Definition of CFG-ITFM message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref CfgItfmFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class CfgItfm : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_ITFM>,
        comms::option::FieldsImpl<CfgItfmFields::All>,
        comms::option::MsgType<CfgItfm<TMsgBase> >
    >
{
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b config for @ref CfgItfmFields::config field
    ///     @li @b config2 for @ref CfgItfmFields::config2 field
    COMMS_MSG_FIELDS_ACCESS(config, config2);

    /// @brief Default constructor
    CfgItfm() = default;

    /// @brief Copy constructor
    CfgItfm(const CfgItfm&) = default;

    /// @brief Move constructor
    CfgItfm(CfgItfm&& other) = default;

    /// @brief Destructor
    ~CfgItfm() = default;

    /// @brief Copy assignment
    CfgItfm& operator=(const CfgItfm&) = default;

    /// @brief Move assignment
    CfgItfm& operator=(CfgItfm&&) = default;
};


}  // namespace message

}  // namespace ublox

