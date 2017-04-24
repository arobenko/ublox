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
/// @brief Contains definition of NAV-TIMEBDS message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/nav.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the NAV-TIMEBDS message fields.
/// @see NavTimebds
struct NavTimebdsFields
{
    /// @brief Definition of "iTOW" field.
    using iTOW = field::nav::iTOW;

    /// @brief Definition of "SOW" field.
    using SOW = field::common::U4T<comms::option::UnitsSeconds>;

    /// @brief Definition of "fSOW" field.
    using fSOW = field::nav::fTOW;

    /// @brief Definition of "week" field.
    using week = field::nav::week;

    /// @brief Definition of "leapS" field.
    using leapS = field::common::I1T<comms::option::UnitsSeconds>;

    /// @brief Definition of "valid" field.
    struct validBits : public
        field::common::X1T<comms::option::BitmaskReservedBits<0xf8, 0> >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS(sowValid, weekValid, leapSValid);
    };

    /// @brief Definition of "tAcc" field.
    using tAcc = field::nav::tAcc;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        iTOW,
        SOW,
        fSOW,
        week,
        leapS,
        validBits,
        tAcc
    >;
};

/// @brief Definition of NAV-TIMEBDS message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref NavTimebdsFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class NavTimebds : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_TIMEBDS>,
        comms::option::FieldsImpl<NavTimebdsFields::All>,
        comms::option::MsgType<NavTimebds<TMsgBase> >
    >
{
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b iTOW for @ref NavTimebdsFields::iTOW field
    ///     @li @b SOW for @ref NavTimebdsFields::SOW field
    ///     @li @b fSOW for @ref NavTimebdsFields::fSOW field
    ///     @li @b week for @ref NavTimebdsFields::week field
    ///     @li @b leapS for @ref NavTimebdsFields::leapS field
    ///     @li @b valid for @ref NavTimebdsFields::validBits field
    ///     @li @b tAcc for @ref NavTimebdsFields::tAcc field
    COMMS_MSG_FIELDS_ACCESS(iTOW, SOW, fSOW, week, leapS, valid, tAcc);

    /// @brief Default constructor
    NavTimebds() = default;

    /// @brief Copy constructor
    NavTimebds(const NavTimebds&) = default;

    /// @brief Move constructor
    NavTimebds(NavTimebds&& other) = default;

    /// @brief Destructor
    ~NavTimebds() = default;

    /// @brief Copy assignment
    NavTimebds& operator=(const NavTimebds&) = default;

    /// @brief Move assignment
    NavTimebds& operator=(NavTimebds&&) = default;
};


}  // namespace message

}  // namespace ublox





