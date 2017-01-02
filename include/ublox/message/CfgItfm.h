//
// Copyright 2015 - 2016 (C). Alex Robenko. All rights reserved.
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

    /// @brief Use this enumeration to access member fields of @ref config bitfield.
    enum
    {
        config_bbThreshold, ///< @b index of @ref bbThreshold member field
        config_cwThreshold, ///< @b index of @ref cwThreshold member field
        config_reserved1, ///< @b index of @ref reserved1 member field
        config_enable, ///< @b index of @ref enable member field
        config_numOfValues ///< number of member fields
    };

    /// @brief Bits access enumeration for @ref enable bitmask member field in @ref config bitfield.
    enum
    {
        config_enable_enable, ///< @b enable bit index
        config_enable_numOfValues ///< number of available bits
    };

    /// @brief Value enumeration for @ref antSetting member field in @ref config2 bitmask.
    enum class AntSetting : std::uint8_t
    {
        Unknown, ///< @b unknown
        Passive, ///< @b passive
        Active, ///< @b active
        NumOfValues ///< number of available values
    };

    /// @brief Use this enumeration to access member fields of @ref config2 bitfield.
    enum
    {
        config2_reserved2, ///< @b index of @ref reserved2 member field
        config2_antSetting, ///< @b index of @ref antSetting member field
        config2_reserved3, ///< @b index of @ref reserved3 member field
        config2_numOfValues ///< number of member fields
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

    /// @brief Definition of "reserved1" member field in @ref config bitmask.
    using reserved1 =
        field::common::U4T<
            comms::option::FixedBitLength<22>,
            comms::option::ValidNumValueRange<0x16b156, 0x16b156>,
            comms::option::DefaultNumValue<0x16b156>
        >;

    /// @brief Definition of the bitmask member field with single "enable" bit
    ///     in @ref config bitmask.
    using enable =
        field::common::X1T<
            comms::option::FixedBitLength<1>
        >;

    /// @brief Definition of "reserved2" member field in @ref config2 bitmask.
    using reserved2 =
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

    /// @brief Definition of "reserved3" member field in @ref config2 bitmask.
    using reserved3 =
        field::common::res4T<
            comms::option::FixedBitLength<18>
        >;

    /// @brief Definition of "config" field.
    using config =
        field::common::BitfieldT<
            std::tuple<
                bbThreshold,
                cwThreshold,
                reserved1,
                enable
            >
        >;

    /// @brief Definition of "config2" field.
    using config2 =
        field::common::BitfieldT<
            std::tuple<
                reserved2,
                antSetting,
                reserved3
            >
        >;

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
///     See @ref CfgItfmFields and for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class CfgItfm : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_ITFM>,
        comms::option::FieldsImpl<CfgItfmFields::All>,
        comms::option::MsgType<CfgItfm<TMsgBase> >,
        comms::option::DispatchImpl
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_ITFM>,
        comms::option::FieldsImpl<CfgItfmFields::All>,
        comms::option::MsgType<CfgItfm<TMsgBase> >,
        comms::option::DispatchImpl
    > Base;
public:

#ifdef FOR_DOXYGEN_DOC_ONLY
    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_config, ///< @b config field, see @ref CfgItfmFields::config
        FieldIdx_config2, ///< @b config2 field, see @ref CfgItfmFields::config2
        FieldIdx_numOfValues ///< number of available fields
    };

    /// @brief Access to fields bundled as a struct
    struct FieldsAsStruct
    {
        CfgItfmFields::config& config; ///< @b config field, see @ref CfgItfmFields::config
        CfgItfmFields::config2& config2; ///< @b config2 field, see @ref CfgItfmFields::config2
    };

    /// @brief Access to @b const fields bundled as a struct
    struct ConstFieldsAsStruct
    {
        const CfgItfmFields::config& config; ///< @b config field, see @ref CfgItfmFields::config
        const CfgItfmFields::config2& config2; ///< @b config2 field, see @ref CfgItfmFields::config2
    };

    /// @brief Get access to fields bundled into a struct
    FieldsAsStruct fieldsAsStruct();

    /// @brief Get access to @b const fields bundled into a struct
    ConstFieldsAsStruct fieldsAsStruct() const;

#else
    COMMS_MSG_FIELDS_ACCESS(Base, config, config2);
#endif // #ifdef FOR_DOXYGEN_DOC_ONLY

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

