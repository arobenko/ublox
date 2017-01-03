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
    /// @brief Bits access enumeration for bits in @b valid bitmask field
    enum
    {
        valid_validTOW, ///< @b validTOW bit index
        valid_validWKN, ///< @b validWKN bit index
        valid_validUTC, ///< @b validUTC bit index
        valid_numOfValues ///< number of available bits
    };

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

    /// @brief Definition of "valid" field.
    using valid = field::common::X1T<comms::option::BitmaskReservedBits<0xf8, 0> >;

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
        valid
    >;
};

/// @brief Definition of NAV-TIMEUTC message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref NavTimeutcFields and for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class NavTimeutc : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_TIMEUTC>,
        comms::option::FieldsImpl<NavTimeutcFields::All>,
        comms::option::MsgType<NavTimeutc<TMsgBase> >,
        comms::option::DispatchImpl
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_TIMEUTC>,
        comms::option::FieldsImpl<NavTimeutcFields::All>,
        comms::option::MsgType<NavTimeutc<TMsgBase> >,
        comms::option::DispatchImpl
    > Base;
public:

#ifdef FOR_DOXYGEN_DOC_ONLY
    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_iTOW, ///< @b iTOW field, see @ref NavTimeutcFields::iTOW
        FieldIdx_tAcc, ///< @b tAcc field, see @ref NavTimeutcFields::tAcc
        FieldIdx_nano, ///< @b nano field, see @ref NavTimeutcFields::nano
        FieldIdx_year, ///< @b year field, see @ref NavTimeutcFields::year
        FieldIdx_month, ///< @b month field, see @ref NavTimeutcFields::month
        FieldIdx_day, ///< @b day field, see @ref NavTimeutcFields::day
        FieldIdx_hour, ///< @b hour field, see @ref NavTimeutcFields::hour
        FieldIdx_min, ///< @b min field, see @ref NavTimeutcFields::min
        FieldIdx_sec, ///< @b sec field, see @ref NavTimeutcFields::sec
        FieldIdx_valid, ///< @b valid field, see @ref NavTimeutcFields::valid
        FieldIdx_numOfValues ///< number of available fields
    };

    /// @brief Access to fields bundled as a struct
    struct FieldsAsStruct
    {
        NavTimeutcFields::iTOW& iTOW; ///< @b iTOW field, see @ref NavTimeutcFields::iTOW
        NavTimeutcFields::tAcc& tAcc; ///< @b tAcc field, see @ref NavTimeutcFields::tAcc
        NavTimeutcFields::nano& nano; ///< @b nano field, see @ref NavTimeutcFields::nano
        NavTimeutcFields::year& year; ///< @b year field, see @ref NavTimeutcFields::year
        NavTimeutcFields::month& month; ///< @b month field, see @ref NavTimeutcFields::month
        NavTimeutcFields::day& day; ///< @b day field, see @ref NavTimeutcFields::day
        NavTimeutcFields::hour& hour; ///< @b hour field, see @ref NavTimeutcFields::hour
        NavTimeutcFields::min& min; ///< @b min field, see @ref NavTimeutcFields::min
        NavTimeutcFields::sec& sec; ///< @b sec field, see @ref NavTimeutcFields::sec
        NavTimeutcFields::valid& valid; ///< @b valid field, see @ref NavTimeutcFields::valid
    };

    /// @brief Access to @b const fields bundled as a struct
    struct ConstFieldsAsStruct
    {
        const NavTimeutcFields::iTOW& iTOW; ///< @b iTOW field, see @ref NavTimeutcFields::iTOW
        const NavTimeutcFields::tAcc& tAcc; ///< @b tAcc field, see @ref NavTimeutcFields::tAcc
        const NavTimeutcFields::nano& nano; ///< @b nano field, see @ref NavTimeutcFields::nano
        const NavTimeutcFields::year& year; ///< @b year field, see @ref NavTimeutcFields::year
        const NavTimeutcFields::month& month; ///< @b month field, see @ref NavTimeutcFields::month
        const NavTimeutcFields::day& day; ///< @b day field, see @ref NavTimeutcFields::day
        const NavTimeutcFields::hour& hour; ///< @b hour field, see @ref NavTimeutcFields::hour
        const NavTimeutcFields::min& min; ///< @b min field, see @ref NavTimeutcFields::min
        const NavTimeutcFields::sec& sec; ///< @b sec field, see @ref NavTimeutcFields::sec
        const NavTimeutcFields::valid& valid; ///< @b valid field, see @ref NavTimeutcFields::valid
    };

    /// @brief Get access to fields bundled into a struct
    FieldsAsStruct fieldsAsStruct();

    /// @brief Get access to @b const fields bundled into a struct
    ConstFieldsAsStruct fieldsAsStruct() const;

#else
    COMMS_MSG_FIELDS_ACCESS(Base, iTOW, tAcc, nano, year, month, day, hour, min, sec, valid);
#endif // #ifdef FOR_DOXYGEN_DOC_ONLY

    /// @brief Default constructor
    NavTimeutc() = default;

    /// @brief Copy constructor
    NavTimeutc(const NavTimeutc&) = default;

    /// @brief Move constructor
    NavTimeutc(NavTimeutc&& other) = default;

    /// @brief Destructor
    virtual ~NavTimeutc() = default;

    /// @brief Copy assignment
    NavTimeutc& operator=(const NavTimeutc&) = default;

    /// @brief Move assignment
    NavTimeutc& operator=(NavTimeutc&&) = default;
};


}  // namespace message

}  // namespace ublox





