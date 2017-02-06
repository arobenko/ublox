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
/// @brief Contains definition of CFG-ANT message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the CFG-ANT message fields.
/// @see CfgAnt
struct CfgAntFields
{

    /// @brief Definition of "flags" field.
    struct flags : public
        field::common::X2T<
            comms::option::BitmaskReservedBits<0xffe0, 0>
        >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS(svcs, csd, ocd, pdwnOnSCD, recovery);
    };

    /// @brief Common definition of @b pinSwitch, @b pinSCD, and @b pinOCD member
    ///     fields of @ref pins bitfield field.
    using pinX =
        field::common::U1T<
            comms::option::FixedBitLength<5>,
            comms::option::ValidNumValueRange<0, 0x1f>
        >;

    /// @brief Definition of @b reconfig bit as single bit bitmask
    struct reconfig : public field::common::X1T<comms::option::FixedBitLength<1> >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS(bit);
    };

    /// @brief Definition of "pins" field.
    struct pins : public
        field::common::BitfieldT<
            std::tuple<
                pinX,
                pinX,
                pinX,
                reconfig
            >
        >
    {
        /// @brief Allow access to internal fields.
        /// @details See definition of @b COMMS_FIELD_MEMBERS_ACCESS macro
        ///     related to @b comms::field::Bitfield class from COMMS library
        ///     for details.
        COMMS_FIELD_MEMBERS_ACCESS(pinSwith, pinSCD, pinOCD, reconfig);
    };

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        flags,
        pins
    >;
};

/// @brief Definition of CFG-ANT message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref CfgAntFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class CfgAnt : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_ANT>,
        comms::option::FieldsImpl<CfgAntFields::All>,
        comms::option::MsgType<CfgAnt<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_ANT>,
        comms::option::FieldsImpl<CfgAntFields::All>,
        comms::option::MsgType<CfgAnt<TMsgBase> >
    > Base;
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b flags for @ref CfgAntFields::flags field
    ///     @li @b pins for @ref CfgAntFields::pins field
    COMMS_MSG_FIELDS_ACCESS(flags, pins);

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

