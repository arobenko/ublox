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
/// @brief Contains definition of TIM-DOSC message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the TIM-DOSC message fields.
/// @see TimDosc
struct TimDoscFields
{
    /// @brief Definition of "version" field.
    using version = field::common::U1T<comms::option::ValidNumValueRange<0, 0> >;

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res3;

    /// @brief Definition of "value" field.
    using value = field::common::U4;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        version,
        reserved1,
        value
    >;
};

/// @brief Definition of TIM-DOSC message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref TimDoscFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class TimDosc : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_TIM_DOSC>,
        comms::option::FieldsImpl<TimDoscFields::All>,
        comms::option::MsgType<TimDosc<TMsgBase> >
    >
{
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b version for @ref TimDoscFields::version field
    ///     @li @b reserved1 for @ref TimDoscFields::reserved1 field
    ///     @li @b value for @ref TimDoscFields::value field
    COMMS_MSG_FIELDS_ACCESS(version, reserved1, value);

    /// @brief Default constructor
    TimDosc() = default;

    /// @brief Copy constructor
    TimDosc(const TimDosc&) = default;

    /// @brief Move constructor
    TimDosc(TimDosc&& other) = default;

    /// @brief Destructor
    ~TimDosc() = default;

    /// @brief Copy assignment
    TimDosc& operator=(const TimDosc&) = default;

    /// @brief Move assignment
    TimDosc& operator=(TimDosc&&) = default;
};


}  // namespace message

}  // namespace ublox

