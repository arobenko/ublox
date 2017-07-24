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
/// @brief Contains definition of NAV-TIMEUTC message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/nav.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the NAV-TIMEUTC message fields.
/// @see NavTimeutc
struct NavTimeutcFields
{
    /// @brief Definition of "iTOW" field.
    using iTOW = field::nav::iTOW;

    /// @brief Definition of "tAcc" field.
    using tAcc = field::nav::tAcc;

    /// @brief Definition of "nano" field.
    using nano = field::nav::nano;

    /// @brief Definition of "year" field.
    using year = field::nav::year;

    /// @brief Definition of "month" field.
    using month = field::nav::month;

    /// @brief Definition of "day" field.
    using day = field::nav::day;

    /// @brief Definition of "hour" field.
    using hour = field::nav::hour;

    /// @brief Definition of "min" field.
    using min = field::nav::min;

    /// @brief Definition of "sec" field.
    using sec = field::nav::sec;

    /// @brief Definition of validity bits in @ref validBitfield field.
    struct validBits : public
        field::common::X1T<
            comms::option::BitmaskReservedBits<0xf8, 0>,
            comms::option::FixedBitLength<4>
        >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS_SEQ macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS_SEQ(validTOW, validWKN, validUTC);
    };

    /// @brief Definition of "utcStandard" member field of @ref validBitfield field.
    using utcStandard = field::common::utcStandardT<comms::option::FixedBitLength<4> >;

    /// @brief Definition of "valid" field as a bitfield.
    struct validBitfield : public
        field::common::BitfieldT<
            std::tuple<
                validBits,
                utcStandard
            >
        >
    {
        /// @brief Allow access to internal fields.
        /// @details See definition of @b COMMS_FIELD_MEMBERS_ACCESS macro
        ///     related to @b comms::field::Bitfield class from COMMS library
        ///     for details.
        COMMS_FIELD_MEMBERS_ACCESS(validBits, utcStandard);
    };


    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        iTOW,
        tAcc,
        nano,
        year,
        month,
        day,
        hour,
        min,
        sec,
        validBitfield
    >;
};

/// @brief Definition of NAV-TIMEUTC message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref NavTimeutcFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class NavTimeutc : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_TIMEUTC>,
        comms::option::FieldsImpl<NavTimeutcFields::All>,
        comms::option::MsgType<NavTimeutc<TMsgBase> >
    >
{
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b iTOW for @ref NavTimeutcFields::iTOW field
    ///     @li @b tAcc for @ref NavTimeutcFields::tAcc field
    ///     @li @b nano for @ref NavTimeutcFields::nano field
    ///     @li @b year for @ref NavTimeutcFields::year field
    ///     @li @b month for @ref NavTimeutcFields::month field
    ///     @li @b day for @ref NavTimeutcFields::day field
    ///     @li @b hour for @ref NavTimeutcFields::hour field
    ///     @li @b min for @ref NavTimeutcFields::min field
    ///     @li @b sec for @ref NavTimeutcFields::sec field
    ///     @li @b valid for @ref NavTimeutcFields::validBitfield field
    COMMS_MSG_FIELDS_ACCESS(iTOW, tAcc, nano, year, month, day, hour, min, sec, valid);

    /// @brief Default constructor
    NavTimeutc() = default;

    /// @brief Copy constructor
    NavTimeutc(const NavTimeutc&) = default;

    /// @brief Move constructor
    NavTimeutc(NavTimeutc&& other) = default;

    /// @brief Destructor
    ~NavTimeutc() = default;

    /// @brief Copy assignment
    NavTimeutc& operator=(const NavTimeutc&) = default;

    /// @brief Move assignment
    NavTimeutc& operator=(NavTimeutc&&) = default;
};


}  // namespace message

}  // namespace ublox





