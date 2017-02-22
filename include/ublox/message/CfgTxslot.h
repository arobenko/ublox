//
// Copyright 2017 (C). Alex Robenko. All rights reserved.
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
/// @brief Contains definition of CFG-TXSLOT message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the CFG-TXSLOT message fields.
/// @see CfgTxslot
struct CfgTxslotFields
{
    /// @brief Definition of "version" field.
    using version =
        field::common::U1T<
            comms::option::ValidNumValueRange<0, 0>
        >;

    /// @brief Definition of "enable" field.
    struct enable : public
        field::common::X1T<
            comms::option::BitmaskReservedBits<0xe0, 0>
        >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS(DDC, UART1, UART2, USB, SPI);
    };

    /// @brief Value enumeration for @ref refTp field.
    enum class RefTp : std::uint8_t
    {
        Timepulse, ///< Timepulse
        Timepulse2, ///< Timepulse 2
        NumOfValues /// number of available values
    };

    /// @brief Definition of "refTp" field.
    using refTp =
        field::common::EnumT<
            RefTp,
            comms::option::ValidNumValueRange<0, (int)RefTp::NumOfValues - 1>
        >;

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res1;

    /// @brief Common definition of "endX" fields
    using end = field::common::U4;

    /// @brief Definition of "end1" field.
    using end0 = end;

    /// @brief Definition of "end1" field.
    using end1 = end;

    /// @brief Definition of "end1" field.
    using end2 = end;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        version,
        enable,
        refTp,
        reserved1,
        end0,
        end1,
        end2
    >;
};

/// @brief Definition of CFG-TXSLOT message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref CfgTxslotFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class CfgTxslot : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_TXSLOT>,
        comms::option::FieldsImpl<CfgTxslotFields::All>,
        comms::option::MsgType<CfgTxslot<TMsgBase> >
    >
{
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b version for @ref CfgTxslotFields::version field
    ///     @li @b enable for @ref CfgTxslotFields::enable field
    ///     @li @b refTp for @ref CfgTxslotFields::refTp field
    ///     @li @b reserved1 for @ref CfgTxslotFields::reserved1 field
    ///     @li @b end0 for @ref CfgTxslotFields::end0 field
    ///     @li @b end1 for @ref CfgTxslotFields::end1 field
    ///     @li @b end2 for @ref CfgTxslotFields::end2 field
    COMMS_MSG_FIELDS_ACCESS(
            version,
            enable,
            refTp,
            reserved1,
            end0,
            end1,
            end2
    );

    /// @brief Default constructor
    CfgTxslot() = default;

    /// @brief Copy constructor
    CfgTxslot(const CfgTxslot&) = default;

    /// @brief Move constructor
    CfgTxslot(CfgTxslot&& other) = default;

    /// @brief Destructor
    virtual ~CfgTxslot() = default;

    /// @brief Copy assignment
    CfgTxslot& operator=(const CfgTxslot&) = default;

    /// @brief Move assignment
    CfgTxslot& operator=(CfgTxslot&&) = default;
};

}  // namespace message

}  // namespace ublox

