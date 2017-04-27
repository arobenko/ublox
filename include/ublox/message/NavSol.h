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
/// @brief Contains definition of NAV-SOL message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/nav.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the NAV-SOL message fields.
/// @see NavSol
struct NavSolFields
{
    /// @brief Definition of "iTOW" field.
    using iTOW = field::nav::iTOW;

    /// @brief Definition of "fTOW" field.
    using fTOW = field::nav::fTOW;

    /// @brief Definition of "week" field.
    using week = field::nav::week;

    /// @brief Definition of "gpsFix" field.
    using gpsFix = field::nav::gpsFix;

    /// @brief Definition of "flags" field.
    struct flags : public
        field::common::X1T<
            comms::option::BitmaskReservedBits<0xf0, 0>
        >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS(GPSfixOK, DiffSoln, WKNSET, TOWSET);
    };

    /// @brief Definition of "ecefX" field.
    using ecefX = field::nav::ecefX;

    /// @brief Definition of "ecefY" field.
    using ecefY = field::nav::ecefY;

    /// @brief Definition of "ecefZ" field.
    using ecefZ = field::nav::ecefZ;

    /// @brief Definition of "pAcc" field.
    using pAcc = field::nav::pAcc;

    /// @brief Definition of "ecefVX" field.
    using ecefVX = field::nav::ecefVX;

    /// @brief Definition of "ecefVY" field.
    using ecefVY = field::nav::ecefVY;

    /// @brief Definition of "ecefVZ" field.
    using ecefVZ = field::nav::ecefVZ;

    /// @brief Definition of "sAcc" field.
    using sAcc = field::nav::sAcc;

    /// @brief Definition of "pDOP" field.
    using pDOP = field::nav::pDOP;

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res1;

    /// @brief Definition of "numSV" field.
    using numSV = field::nav::numSV;

    /// @brief Definition of "reserved2" field.
    using reserved2 = field::common::res4;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        iTOW,
        fTOW,
        week,
        gpsFix,
        flags,
        ecefX,
        ecefY,
        ecefZ,
        pAcc,
        ecefVX,
        ecefVY,
        ecefVZ,
        sAcc,
        pDOP,
        reserved1,
        numSV,
        reserved2
    >;
};

/// @brief Definition of NAV-SOL message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref NavSolFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class NavSol : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_SOL>,
        comms::option::FieldsImpl<NavSolFields::All>,
        comms::option::MsgType<NavSol<TMsgBase> >
    >
{
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b iTOW for @ref NavSolFields::iTOW field
    ///     @li @b fTOW for @ref NavSolFields::fTOW field
    ///     @li @b week for @ref NavSolFields::week field
    ///     @li @b gpsFix for @ref NavSolFields::gpsFix field
    ///     @li @b ecefX for @ref NavSolFields::ecefX field
    ///     @li @b ecefY for @ref NavSolFields::ecefY field
    ///     @li @b ecefZ for @ref NavSolFields::ecefZ field
    ///     @li @b pAcc for @ref NavSolFields::pAcc field
    ///     @li @b ecefVX for @ref NavSolFields::ecefVX field
    ///     @li @b ecefVY for @ref NavSolFields::ecefVY field
    ///     @li @b ecefVZ for @ref NavSolFields::ecefVZ field
    ///     @li @b sAcc for @ref NavSolFields::sAcc field
    ///     @li @b pDOP for @ref NavSolFields::pDOP field
    ///     @li @b reserved1 for @ref NavSolFields::reserved1 field
    ///     @li @b numSV for @ref NavSolFields::numSV field
    ///     @li @b reserved2 for @ref NavSolFields::reserved2 field
    COMMS_MSG_FIELDS_ACCESS(
        iTOW,
        fTOW,
        week,
        gpsFix,
        flags,
        ecefX,
        ecefY,
        ecefZ,
        pAcc,
        ecefVX,
        ecefVY,
        ecefVZ,
        sAcc,
        pDOP,
        reserved1,
        numSV,
        reserved2
    );

    /// @brief Default constructor
    NavSol() = default;

    /// @brief Copy constructor
    NavSol(const NavSol&) = default;

    /// @brief Move constructor
    NavSol(NavSol&& other) = default;

    /// @brief Destructor
    ~NavSol() = default;

    /// @brief Copy assignment
    NavSol& operator=(const NavSol&) = default;

    /// @brief Move assignment
    NavSol& operator=(NavSol&&) = default;
};


}  // namespace message

}  // namespace ublox





