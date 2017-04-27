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
/// @brief Contains definition of CFG-ODO message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the CFG-ODO message fields.
/// @see CfgOdo
struct CfgOdoFields
{
    /// @brief Definition of "version" field.
    using version =
        field::common::U1T<
            comms::option::ValidNumValueRange<0, 0>
        >;

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res3;

    /// @brief Definition of "flags" field.
    struct flags : public
        field::common::X1T<
            comms::option::FixedLength<1>,
            comms::option::BitmaskReservedBits<0xf0, 0>
        >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS(useODO, useCOG, outLPVel, outLPCog);
    };

    /// @brief Value enumeration for @ref profile field.
    enum class Profile : std::uint8_t
    {
        Running, ///< running
        Cycling, ///< cycling
        Swimming, ///< swimming
        Car, ///< car
        Custom, ///< custom
        NumOfValues
    };

    /// @brief Definition of "profile" member field of @ref odoCfg bitfield.
    using profile =
        field::common::EnumT<
            Profile,
            comms::option::FixedBitLength<3>,
            comms::option::ValidNumValueRange<0, (int)Profile::NumOfValues - 1>
        >;

    /// @brief Definition of "odoCfg" field.
    struct odoCfg : public
        field::common::BitfieldT<
            std::tuple<
                profile,
                field::common::res1T<comms::option::FixedBitLength<5> >
            >
        >
    {
        /// @brief Allow access to internal fields.
        /// @details See definition of @b COMMS_FIELD_MEMBERS_ACCESS macro
        ///     related to @b comms::field::Bitfield class from COMMS library
        ///     for details.
        COMMS_FIELD_MEMBERS_ACCESS(profile, reserved);
    };

    /// @brief Definition of "reserved2" field.
    using reserved2 = field::common::res6;

    /// @brief Definition of "cogMaxSpeed" field.
    using cogMaxSpeed =
        field::common::U1T<
            comms::option::ScalingRatio<1, 10>,
            comms::option::UnitsMetersPerSecond
        >;

    /// @brief Definition of "cogMaxPosAcc" field.
    using cogMaxPosAcc = field::common::U1T<comms::option::UnitsMeters>;

    /// @brief Definition of "reserved3" field.
    using reserved3 = field::common::res2;

    /// @brief Definition of "velLpGain" field.
    using velLpGain = field::common::U1;

    /// @brief Definition of "cogLpGain" field.
    using cogLpGain = field::common::U1;

    /// @brief Definition of "reserved4" field.
    using reserved4 = field::common::res2;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        version,
        reserved1,
        flags,
        odoCfg,
        reserved2,
        cogMaxSpeed,
        cogMaxPosAcc,
        reserved3,
        velLpGain,
        cogLpGain,
        reserved4
    >;
};

/// @brief Definition of CFG-ODO message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref CfgOdoFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class CfgOdo : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_ODO>,
        comms::option::FieldsImpl<CfgOdoFields::All>,
        comms::option::MsgType<CfgOdo<TMsgBase> >
    >
{
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b version for @ref CfgOdoFields::version field
    ///     @li @b reserved1 for @ref CfgOdoFields::reserved1 field
    ///     @li @b flags for @ref CfgOdoFields::flags field
    ///     @li @b odoCfg for @ref CfgOdoFields::odoCfg field
    ///     @li @b reserved2 for @ref CfgOdoFields::reserved2 field
    ///     @li @b cogMaxSpeed for @ref CfgOdoFields::cogMaxSpeed field
    ///     @li @b cogMaxPosAcc for @ref CfgOdoFields::cogMaxPosAcc field
    ///     @li @b reserved3 for @ref CfgOdoFields::reserved3 field
    ///     @li @b velLpGain for @ref CfgOdoFields::velLpGain field
    ///     @li @b cogLpGain for @ref CfgOdoFields::cogLpGain field
    ///     @li @b reserved4 for @ref CfgOdoFields::reserved4 field
    COMMS_MSG_FIELDS_ACCESS(
        version,
        reserved1,
        flags,
        odoCfg,
        reserved2,
        cogMaxSpeed,
        cogMaxPosAcc,
        reserved3,
        velLpGain,
        cogLpGain,
        reserved4);

    /// @brief Default constructor
    CfgOdo() = default;

    /// @brief Copy constructor
    CfgOdo(const CfgOdo&) = default;

    /// @brief Move constructor
    CfgOdo(CfgOdo&& other) = default;

    /// @brief Destructor
    ~CfgOdo() = default;

    /// @brief Copy assignment
    CfgOdo& operator=(const CfgOdo&) = default;

    /// @brief Move assignment
    CfgOdo& operator=(CfgOdo&&) = default;
};


}  // namespace message

}  // namespace ublox

