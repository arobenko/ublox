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
/// @brief Contains definition of TIM-VCOCAL (stop command) message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the TIM-VCOCAL (stop command) message fields.
/// @see TimVcocalStop
struct TimVcocalStopFields
{
    /// @brief Definition of "type" field.
    using type =
        field::common::U1T<
        comms::option::ValidNumValueRange<0, 0>,
        comms::option::FailOnInvalid
    >;


    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        type
    >;
};

/// @brief Definition of TIM-VCOCAL (stop command) message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref TimVcocalStopFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class TimVcocalStop : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_TIM_VCOCAL>,
        comms::option::FieldsImpl<TimVcocalStopFields::All>,
        comms::option::MsgType<TimVcocalStop<TMsgBase> >
    >
{
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b type for @ref TimVcocalStopFields::type field
    COMMS_MSG_FIELDS_ACCESS(type);

    /// @brief Default constructor
    TimVcocalStop() = default;

    /// @brief Copy constructor
    TimVcocalStop(const TimVcocalStop&) = default;

    /// @brief Move constructor
    TimVcocalStop(TimVcocalStop&& other) = default;

    /// @brief Destructor
    virtual ~TimVcocalStop() = default;

    /// @brief Copy assignment
    TimVcocalStop& operator=(const TimVcocalStop&) = default;

    /// @brief Move assignment
    TimVcocalStop& operator=(TimVcocalStop&&) = default;
};


}  // namespace message

}  // namespace ublox

