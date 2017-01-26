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
/// @brief Contains definition of NAV-POSLLH message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/nav.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the NAV-POSLLH message fields.
/// @see NavPosllh
struct NavPosllhFields
{
    /// @brief Definition of "iTOW" field.
    using iTOW = field::nav::iTOW;

    /// @brief Definition of "lat" field.
    using lat = field::nav::lat;

    /// @brief Definition of "lon" field.
    using lon = field::nav::lon;

    /// @brief Definition of "height" field.
    using height = field::nav::height;

    /// @brief Definition of "hMSL" field.
    using hMSL = field::nav::hMSL;

    /// @brief Definition of "hAcc" field.
    using hAcc = field::nav::hAcc;

    /// @brief Definition of "vAcc" field.
    using vAcc = field::nav::vAcc;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        iTOW,
        lon,
        lat,
        height,
        hMSL,
        hAcc,
        vAcc
    >;
};

/// @brief Definition of NAV-POSLLH message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref NavPosllhFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class NavPosllh : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_POSLLH>,
        comms::option::FieldsImpl<NavPosllhFields::All>,
        comms::option::MsgType<NavPosllh<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_POSLLH>,
        comms::option::FieldsImpl<NavPosllhFields::All>,
        comms::option::MsgType<NavPosllh<TMsgBase> >
    > Base;
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b iTOW for @ref NavPosllhFields::iTOW field
    ///     @li @b lon for @ref NavPosllhFields::lon field
    ///     @li @b lat for @ref NavPosllhFields::lat field
    ///     @li @b height for @ref NavPosllhFields::height field
    ///     @li @b hMSL for @ref NavPosllhFields::hMSL field
    ///     @li @b hAcc for @ref NavPosllhFields::hAcc field
    ///     @li @b vAcc for @ref NavPosllhFields::vAcc field
    COMMS_MSG_FIELDS_ACCESS(iTOW, lon, lat, height, hMSL, hAcc, vAcc);

    /// @brief Default constructor
    NavPosllh() = default;

    /// @brief Copy constructor
    NavPosllh(const NavPosllh&) = default;

    /// @brief Move constructor
    NavPosllh(NavPosllh&& other) = default;

    /// @brief Destructor
    virtual ~NavPosllh() = default;

    /// @brief Copy assignment
    NavPosllh& operator=(const NavPosllh&) = default;

    /// @brief Move assignment
    NavPosllh& operator=(NavPosllh&&) = default;
};


}  // namespace message

}  // namespace ublox





