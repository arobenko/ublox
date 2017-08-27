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
/// @brief Contains definition of ESF-INS message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the ESF-INS message fields.
/// @see EsfIns
struct EsfInsFields
{
    /// @brief Definition of "version" field.
    using version =
        field::common::U1T<
            comms::option::ValidNumValueRange<1, 1>,
            comms::option::DefaultNumValue<1>
        >;

    /// @brief Definition of "bitfield0" field excluding "version" information.
    struct bitfield0 : public
        field::common::X3T<
            comms::option::BitmaskReservedBits<0xffffc0, 0>
        >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS_SEQ macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS_SEQ(
            xAngRateValid,
            yAngRateValid,
            zAngRateValid,
            xAccelValid,
            yAccelValid,
            zAccelValid);
    };

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res4;

    /// @brief Definition of "iTOW" field.
    using iTOW = field::common::iTOW;

    /// @brief Definition of "xAngRate" field.
    using xAngRate =
        field::common::I4T<
            comms::option::ScalingRatio<1, 1000>,
            comms::option::UnitsDegrees
        >;

    /// @brief Definition of "yAngRate" field.
    using yAngRate = xAngRate;

    /// @brief Definition of "zAngRate" field.
    using zAngRate = xAngRate;

    /// @brief Definition of "xAccel" field.
    using xAccel = field::common::I4;

    /// @brief Definition of "yAccel" field.
    using yAccel = xAccel;

    /// @brief Definition of "zAccel" field.
    using zAccel = xAccel;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        version,
        bitfield0,
        reserved1,
        iTOW,
        xAngRate,
        yAngRate,
        zAngRate,
        xAccel,
        yAccel,
        zAccel
    >;
};

/// @brief Definition of ESF-INS message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref EsfInsFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class EsfIns : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_ESF_INS>,
        comms::option::FieldsImpl<EsfInsFields::All>,
        comms::option::MsgType<EsfIns<TMsgBase> >
    >
{
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b version for @ref EsfInsFields::version field
    ///     @li @b bitfield0 for @ref EsfInsFields::bitfield0 field
    ///     @li @b reserved1 for @ref EsfInsFields::reserved1 field
    ///     @li @b iTOW for @ref EsfInsFields::iTOW field
    ///     @li @b xAngRate for @ref EsfInsFields::xAngRate field
    ///     @li @b yAngRate for @ref EsfInsFields::yAngRate field
    ///     @li @b zAngRate for @ref EsfInsFields::zAngRate field
    ///     @li @b xAccel for @ref EsfInsFields::xAccel field
    ///     @li @b yAccel for @ref EsfInsFields::yAccel field
    ///     @li @b zAccel for @ref EsfInsFields::zAccel field
    COMMS_MSG_FIELDS_ACCESS(
        version,
        bitfield0,
        reserved1,
        iTOW,
        xAngRate,
        yAngRate,
        zAngRate,
        xAccel,
        yAccel,
        zAccel
    );

    /// @brief Default constructor
    EsfIns() = default;

    /// @brief Copy constructor
    EsfIns(const EsfIns&) = default;

    /// @brief Move constructor
    EsfIns(EsfIns&& other) = default;

    /// @brief Destructor
    ~EsfIns() = default;

    /// @brief Copy assignment
    EsfIns& operator=(const EsfIns&) = default;

    /// @brief Move assignment
    EsfIns& operator=(EsfIns&&) = default;
};


}  // namespace message

}  // namespace ublox





