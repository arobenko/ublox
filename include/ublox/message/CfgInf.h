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
/// @brief Contains definition of CFG-INF message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/cfg.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the CFG-INF message fields.
/// @see CfgInf
struct CfgInfFields
{
    /// @brief Protocol ID enumeration.
    using ProtocolId = field::cfg::ProtocolId;

    /// @brief Use this enumeration to access right bitmask in @ref infMsgMask list field.
    enum
    {
        infMsgMask_ddc, ///< index of @b DDC bitmask field
        infMsgMask_uart, ///< index of @b UART bitmask field
        infMsgMask_uart2, ///< index of @b UART2 bitmask field
        infMsgMask_usb, ///< index of @b USB bitmask field
        infMsgMask_spi, ///< index of @b SPI bitmask field
        infMsgMask_reserved, ///< index of reserved bitmask field
        infMsgMask_numOfValues ///< number of available masks
    };

    /// @brief Definition of "protocolID" field.
    using protocolID = field::cfg::protocolID;

    /// @brief Definition of "reserved0" field.
    using reserved0 = field::common::res1;

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res2;

    /// @brief definition of single bitmask value field in @ref infMsgMask field
    struct mask : public
        field::common::X1T<comms::option::BitmaskReservedBits<0xe0, 0> >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS(ERROR, WARNING, NOTICE, DEBUG, TEST);
    };

    /// @brief Definition of "infMsgMask" field.
    /// @tparam TOpt Extra option(s)
    template <typename TOpt = comms::option::EmptyOption>
    using infMsgMask =
        field::common::ListT<
            mask,
            comms::option::SequenceFixedSize<infMsgMask_numOfValues>,
            TOpt
        >;

    /// @brief Definition of a single configuration bundle element in @ref list field.
    /// @tparam TOpt Extra option(s) for @ref infMsgMask field.
    template <typename TOpt = comms::option::EmptyOption>
    struct element : public
        field::common::BundleT<
            std::tuple<
                protocolID,
                reserved0,
                reserved1,
                infMsgMask<TOpt>
            >
        >
    {
        /// @brief Allow access to internal fields.
        /// @details See definition of @b COMMS_FIELD_MEMBERS_ACCESS macro
        ///     related to @b comms::field::Bundle class from COMMS library
        ///     for details.
        COMMS_FIELD_MEMBERS_ACCESS(protocolID, reserved0, reserved1, infMsgMask);
    };

    /// @brief @ref CfgInf message may contain multiple configuration elements
    ///     (see @ref element). This field defines a list of such elements.
    /// @tparam TListOpt Extra option(s) for @ref list field itself.
    /// @tparam TInfMsgMaskOpt Extra option(s) for @ref infMsgMask field.
    template <
        typename TListOpt = comms::option::EmptyOption,
        typename TInfMsgMaskOpt = comms::option::EmptyOption>
    using list = field::common::ListT<element<TInfMsgMaskOpt>, TListOpt>;

    /// @brief All the fields bundled in std::tuple.
    /// @tparam TListOpt Extra option(s) for @ref list field.
    /// @tparam TInfMsgMaskOpt Extra option(s) for @ref infMsgMask field.
    template <
        typename TListOpt = comms::option::EmptyOption,
        typename TInfMsgMaskOpt = comms::option::EmptyOption>
    using All = std::tuple<
        list<TListOpt, TInfMsgMaskOpt>
    >;
};

/// @brief Definition of CFG-INF message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref CfgInfFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
/// @tparam TListOpt Extra option(s) for @b list field.
/// @tparam TInfMsgMaskOpt Extra option(s) for @b infMsgMask field.
template <
    typename TMsgBase = Message,
    typename TListOpt = comms::option::EmptyOption,
    typename TInfMsgMaskOpt = comms::option::EmptyOption>
class CfgInf : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_INF>,
        comms::option::FieldsImpl<CfgInfFields::All<TListOpt, TInfMsgMaskOpt> >,
        comms::option::MsgType<CfgInf<TMsgBase, TListOpt, TInfMsgMaskOpt> >
    >
{
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b list for @ref CfgInfFields::list field
    COMMS_MSG_FIELDS_ACCESS(list);

    /// @brief Default constructor
    CfgInf() = default;

    /// @brief Copy constructor
    CfgInf(const CfgInf&) = default;

    /// @brief Move constructor
    CfgInf(CfgInf&& other) = default;

    /// @brief Destructor
    ~CfgInf() = default;

    /// @brief Copy assignment
    CfgInf& operator=(const CfgInf&) = default;

    /// @brief Move assignment
    CfgInf& operator=(CfgInf&&) = default;
};


}  // namespace message

}  // namespace ublox

