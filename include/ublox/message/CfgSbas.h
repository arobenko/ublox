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
    /// @brief Bits access enumeration for @ref mode bitmask field.
    enum
    {
        mode_enabled, ///< @b enabled bit index
        mode_test, ///< @b test bit index
        mode_numOfValues ///< number of available bits
    };

    /// @brief Bits access enumeration for @ref usage bitmask field.
    enum
    {
        usage_range, ///< @b range bit index
        usage_diffCorr, ///< @b diffCorr bit index
        usage_integrity, ///< @b integrity bit index
        usage_numOfValues ///< number of available bits
    };

    /// @brief Bits access enumeration for @ref scanmode2 bitmask field.
    enum
    {
        scanmode2_PRN152, ///< @b PRN152 bit index
        scanmode2_PRN153, ///< @b PRN153 bit index
        scanmode2_PRN154, ///< @b PRN154 bit index
        scanmode2_PRN155, ///< @b PRN155 bit index
        scanmode2_PRN156, ///< @b PRN156 bit index
        scanmode2_PRN157, ///< @b PRN157 bit index
        scanmode2_PRN158, ///< @b PRN158 bit index
        scanmode2_numOfValues ///< number of available bits
    };

    /// @brief Bits access enumeration for @ref scanmode1 bitmask field.
    enum
    {
        scanmode1_PRN120, ///< @b PRN120 bit index
        scanmode1_PRN121, ///< @b PRN121 bit index
        scanmode1_PRN122, ///< @b PRN122 bit index
        scanmode1_PRN123, ///< @b PRN123 bit index
        scanmode1_PRN124, ///< @b PRN124 bit index
        scanmode1_PRN125, ///< @b PRN125 bit index
        scanmode1_PRN126, ///< @b PRN126 bit index
        scanmode1_PRN127, ///< @b PRN127 bit index
        scanmode1_PRN128, ///< @b PRN128 bit index
        scanmode1_PRN129, ///< @b PRN129 bit index
        scanmode1_PRN130, ///< @b PRN130 bit index
        scanmode1_PRN131, ///< @b PRN131 bit index
        scanmode1_PRN132, ///< @b PRN132 bit index
        scanmode1_PRN133, ///< @b PRN133 bit index
        scanmode1_PRN134, ///< @b PRN134 bit index
        scanmode1_PRN135, ///< @b PRN135 bit index
        scanmode1_PRN136, ///< @b PRN136 bit index
        scanmode1_PRN137, ///< @b PRN137 bit index
        scanmode1_PRN138, ///< @b PRN138 bit index
        scanmode1_PRN139, ///< @b PRN139 bit index
        scanmode1_PRN140, ///< @b PRN140 bit index
        scanmode1_PRN141, ///< @b PRN141 bit index
        scanmode1_PRN142, ///< @b PRN142 bit index
        scanmode1_PRN143, ///< @b PRN143 bit index
        scanmode1_PRN144, ///< @b PRN144 bit index
        scanmode1_PRN145, ///< @b PRN145 bit index
        scanmode1_PRN146, ///< @b PRN146 bit index
        scanmode1_PRN147, ///< @b PRN147 bit index
        scanmode1_PRN148, ///< @b PRN148 bit index
        scanmode1_PRN149, ///< @b PRN149 bit index
        scanmode1_PRN150, ///< @b PRN150 bit index
        scanmode1_PRN151, ///< @b PRN151 bit index
        scanmode1_numOfValues ///< number of available bits
    };

    /// @brief Definition of "mode" field.
    using mode =
        field::common::X1T<
            comms::option::BitmaskReservedBits<0xfc, 0>
        >;

    /// @brief Definition of "usage" field.
    using usage =
        field::common::X1T<
            comms::option::BitmaskReservedBits<0xf8, 0>
        >;

    /// @brief Definition of "maxSBAS" field.
    using maxSBAS =
        field::common::U1T<
            comms::option::ValidNumValueRange<0, 3>
        >;

    /// @brief Definition of "scanmode2" field.
    using scanmode2 =
        field::common::X1T<
            comms::option::BitmaskReservedBits<0x80, 0>
        >;

    /// @brief Definition of "scanmode1" field.
    using scanmode1 = field::common::X4;

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
/// @details Inherits from
///     <a href="https://dl.dropboxusercontent.com/u/46999418/comms_champion/comms/html/classcomms_1_1MessageBase.html">comms::MessageBase</a>
///     while providing @b TMsgBase as common interface class as well as
///     @b comms::option::StaticNumIdImpl, @b comms::option::FieldsImpl, and
///     @b comms::option::DispatchImpl as options. @n
///     See @ref CfgSbasFields and for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class CfgSbas : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_SBAS>,
        comms::option::FieldsImpl<CfgSbasFields::All>,
        comms::option::DispatchImpl<CfgSbas<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_SBAS>,
        comms::option::FieldsImpl<CfgSbasFields::All>,
        comms::option::DispatchImpl<CfgSbas<TMsgBase> >
    > Base;
public:

    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_mode, ///< @b mode field, see @ref CfgSbasFields::mode
        FieldIdx_usage, ///< @b usage field, see @ref CfgSbasFields::usage
        FieldIdx_maxSBAS, ///< @b maxSBAS field, see @ref CfgSbasFields::maxSBAS
        FieldIdx_scanmode2, ///< @b scanmode2 field, see @ref CfgSbasFields::scanmode2
        FieldIdx_scanmode1, ///< @b scanmode1 field, see @ref CfgSbasFields::scanmode1
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

