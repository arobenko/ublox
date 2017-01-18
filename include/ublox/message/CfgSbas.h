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
/// @brief Contains definition of CFG-SBAS message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the CFG-SBAS message fields.
/// @see CfgSbas
struct CfgSbasFields
{

    /// @brief Definition of "mode" field.
    struct mode : public
        field::common::X1T<
            comms::option::BitmaskReservedBits<0xfc, 0>
        >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS(enabled, test);
    };

    /// @brief Definition of "usage" field.
    struct usage : public
        field::common::X1T<
            comms::option::BitmaskReservedBits<0xf8, 0>
        >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS(range, diffCorr, integrity);
    };

    /// @brief Definition of "maxSBAS" field.
    using maxSBAS =
        field::common::U1T<
            comms::option::ValidNumValueRange<0, 3>
        >;

    /// @brief Definition of "scanmode2" field.
    struct scanmode2 : public
        field::common::X1T<
            comms::option::BitmaskReservedBits<0x80, 0>
        >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS(PRN152, PRN153, PRN154, PRN155, PRN156, PRN157, PRN158);
    };

    /// @brief Definition of "scanmode1" field.
    struct scanmode1 : public field::common::X4
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS(
            PRN120,
            PRN121,
            PRN122,
            PRN123,
            PRN124,
            PRN125,
            PRN126,
            PRN127,
            PRN128,
            PRN129,
            PRN130,
            PRN131,
            PRN132,
            PRN133,
            PRN134,
            PRN135,
            PRN136,
            PRN137,
            PRN138,
            PRN139,
            PRN140,
            PRN141,
            PRN142,
            PRN143,
            PRN144,
            PRN145,
            PRN146,
            PRN147,
            PRN148,
            PRN149,
            PRN150,
            PRN151
        );
    };

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        mode,
        usage,
        maxSBAS,
        scanmode2,
        scanmode1
    >;
};

/// @brief Definition of CFG-SBAS message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref CfgSbasFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class CfgSbas : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_SBAS>,
        comms::option::FieldsImpl<CfgSbasFields::All>,
        comms::option::MsgType<CfgSbas<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_SBAS>,
        comms::option::FieldsImpl<CfgSbasFields::All>,
        comms::option::MsgType<CfgSbas<TMsgBase> >
    > Base;
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b mode for @ref CfgSbasFields::mode field
    ///     @li @b usage for @ref CfgSbasFields::usage field
    ///     @li @b maxSBAS for @ref CfgSbasFields::maxSBAS field
    ///     @li @b scanmode2 for @ref CfgSbasFields::scanmode2 field
    ///     @li @b scanmode1 for @ref CfgSbasFields::scanmode1 field
    COMMS_MSG_FIELDS_ACCESS(Base, mode, usage, maxSBAS, scanmode2, scanmode1);

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

