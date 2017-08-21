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
/// @brief Contains definition of NAV-RELPOSNED message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/nav.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the NAV-RELPOSNED message fields.
/// @see NavRelposned
struct NavRelposnedFields
{
    /// @brief Definition of "version" field.
    using version =
        field::common::U1T<
            comms::option::ValidNumValueRange<0, 0>
        >;

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res1;

    /// @brief Definition of "refStationId" field.
    using refStationId =
        field::common::U2T<
            comms::option::ValidNumValueRange<0, 4095>
        >;

    /// @brief Definition of "iTOW" field.
    using iTOW = field::nav::iTOW;

    /// @brief Definition of "relPosN" field.
    using relPosN =
        field::common::I4T<
            comms::option::UnitsCentimeters
        >;

    /// @brief Definition of "relPosE" field.
    using relPosE = relPosN;

    /// @brief Definition of "relPosD" field.
    using relPosD = relPosN;

    /// @brief Definition of "relPosHPN" field.
    using relPosHPN =
        field::common::I1T<
            comms::option::UnitsMillimeters,
            comms::option::ScalingRatio<1, 10>,
            comms::option::ValidNumValueRange<-99, 99>
        >;

    /// @brief Definition of "relPosHPE" field.
    using relPosHPE = relPosHPN;

    /// @brief Definition of "relPosHPD" field.
    using relPosHPD = relPosHPN;

    /// @brief Definition of "reserved2" field.
    using reserved2 = field::common::res1;

    /// @brief Definition of "accN" field.
    using accN =
        field::common::U4T<
            comms::option::UnitsMillimeters,
            comms::option::ScalingRatio<1, 10>
        >;

    /// @brief Definition of "accE" field.
    using accE = accN;

    /// @brief Definition of "accD" field.
    using accD = accN;

    /// @brief Definition of bits in low part of @b flags bifield.
    struct flagsLow : public
        field::common::X1T<
            comms::option::FixedBitLength<3>,
            comms::option::BitmaskReservedBits<0xf8, 0>
        >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS_SEQ macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS_SEQ(gnssFixOK, diffSoln, relPosValid);
    };

    /// @brief Value enumeration for @ref carrSoln field.
    using CarrSoln = field::nav::CarrSoln;

    /// @brief Definition of "carrSoln" member field in @ref flags bitmask field.
    using carrSoln = field::nav::carrSoln<comms::option::FixedBitLength<2> >;

    /// @brief Definition of bits in high part of @b flags bifield.
    struct flagsHigh : public
        field::common::X4T<
            comms::option::FixedBitLength<27>,
            comms::option::BitmaskReservedBits<0xfffffff8, 0>
        >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS_SEQ macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS_SEQ(isMoving, refPosMiss, refObsMiss);
    };

    /// @brief Definition of "flags" field.
    struct flags : public
        field::common::BitfieldT<
            std::tuple<
                flagsLow,
                carrSoln,
                flagsHigh
            >
        >
    {
        /// @brief Allow access to internal fields.
        /// @details See definition of @b COMMS_FIELD_MEMBERS_ACCESS macro
        ///     related to @b comms::field::Bitfield class from COMMS library
        ///     for details.
        COMMS_FIELD_MEMBERS_ACCESS(flagsLow, carrSoln, flagsHigh);
    };

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        version,
        reserved1,
        refStationId,
        iTOW,
        relPosN,
        relPosE,
        relPosD,
        relPosHPN,
        relPosHPE,
        relPosHPD,
        reserved2,
        accN,
        accE,
        accD,
        flags
    >;
};

/// @brief Definition of NAV-RELPOSNED message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref NavRelposnedFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class NavRelposned : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_RELPOSNED>,
        comms::option::FieldsImpl<NavRelposnedFields::All>,
        comms::option::MsgType<NavRelposned<TMsgBase> >
    >
{
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b version for @ref NavRelposnedFields::version field
    ///     @li @b reserved1 for @ref NavRelposnedFields::reserved1 field
    ///     @li @b refStationId for @ref NavRelposnedFields::refStationId field
    ///     @li @b iTOW for @ref NavRelposnedFields::iTOW field
    ///     @li @b relPosN for @ref NavRelposnedFields::relPosN field
    ///     @li @b relPosE for @ref NavRelposnedFields::relPosE field
    ///     @li @b relPosD for @ref NavRelposnedFields::relPosD field
    ///     @li @b relPosHPN for @ref NavRelposnedFields::relPosHPN field
    ///     @li @b relPosHPE for @ref NavRelposnedFields::relPosHPE field
    ///     @li @b relPosHPD for @ref NavRelposnedFields::relPosHPD field
    ///     @li @b reserved2 for @ref NavRelposnedFields::reserved2 field
    ///     @li @b accN for @ref NavRelposnedFields::accN field
    ///     @li @b accE for @ref NavRelposnedFields::accE field
    ///     @li @b accD for @ref NavRelposnedFields::accD field
    ///     @li @b flags for @ref NavRelposnedFields::flags field
    COMMS_MSG_FIELDS_ACCESS(
        version,
        reserved1,
        refStationId,
        iTOW,
        relPosN,
        relPosE,
        relPosD,
        relPosHPN,
        relPosHPE,
        relPosHPD,
        reserved2,
        accN,
        accE,
        accD,
        flags
    );

    /// @brief Default constructor
    NavRelposned() = default;

    /// @brief Copy constructor
    NavRelposned(const NavRelposned&) = default;

    /// @brief Move constructor
    NavRelposned(NavRelposned&& other) = default;

    /// @brief Destructor
    ~NavRelposned() = default;

    /// @brief Copy assignment
    NavRelposned& operator=(const NavRelposned&) = default;

    /// @brief Move assignment
    NavRelposned& operator=(NavRelposned&&) = default;
};


}  // namespace message

}  // namespace ublox





