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
/// @brief Contains definition of AID-ALP message and its fields.

#pragma once

#include <iterator>

#include "comms/Message.h"
#include "ublox/Message.h"

#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the AID-ALP message fields.
/// @see AidAlp
struct AidAlpFields
{
    /// @brief Definition of "predTow" field.
    using predTow = field::common::U4;

    /// @brief Definition of "predDur" field.
    using predDur = field::common::U4;

    /// @brief Definition of "age" field.
    using age = field::common::I4;

    /// @brief Definition of "predWno" field.
    using predWno = field::common::U2;

    /// @brief Definition of "almWno" field.
    using almWno = field::common::U2;

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res4;

    /// @brief Definition of "svs" field.
    using svs = field::common::U1;

    /// @brief Definition of "reserved2" field.
    using reserved2 = field::common::res1;

    /// @brief Definition of "reserved3" field.
    using reserved3 = field::common::res2;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        predTow,
        predDur,
        age,
        predWno,
        almWno,
        reserved1,
        svs,
        reserved2,
        reserved3
    >;

};

/// @brief Definition of AID-ALP message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref AidAlpFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class AidAlp : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_AID_ALP>,
        comms::option::FieldsImpl<AidAlpFields::All>,
        comms::option::MsgType<AidAlp<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_AID_ALP>,
        comms::option::FieldsImpl<AidAlpFields::All>,
        comms::option::MsgType<AidAlp<TMsgBase> >
    > Base;
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b predTow for @ref AidAlpFields::predTow field
    ///     @li @b predDur for @ref AidAlpFields::predDur field
    ///     @li @b age for @ref AidAlpFields::age field
    ///     @li @b predWno for @ref AidAlpFields::predWno field
    ///     @li @b almWno for @ref AidAlpFields::almWno field
    ///     @li @b reserved1 for @ref AidAlpFields::reserved1 field
    ///     @li @b svs for @ref AidAlpFields::svs field
    ///     @li @b reserved2 for @ref AidAlpFields::reserved2 field
    ///     @li @b reserved3 for @ref AidAlpFields::reserved3 field
    COMMS_MSG_FIELDS_ACCESS(predTow, predDur, age, predWno, almWno, reserved1, svs, reserved2, reserved3);

    /// @brief Default constructor
    AidAlp() = default;

    /// @brief Copy constructor
    AidAlp(const AidAlp&) = default;

    /// @brief Move constructor
    AidAlp(AidAlp&& other) = default;

    /// @brief Destructor
    ~AidAlp() = default;

    /// @brief Copy assignment
    AidAlp& operator=(const AidAlp&) = default;

    /// @brief Move assignment
    AidAlp& operator=(AidAlp&&) = default;
};


}  // namespace message

}  // namespace ublox





