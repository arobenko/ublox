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
/// @brief Contains definition of TIM-SVIN message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the TIM-SVIN message fields.
/// @see TimSvin
struct TimSvinFields
{
    /// @brief Definition of "dur" field.
    using dur = field::common::U4;

    /// @brief Definition of "meanX" field.
    using meanX = field::common::I4T<comms::option::UnitsCentimeters>;

    /// @brief Definition of "meanY" field.
    using meanY = meanX;

    /// @brief Definition of "meanZ" field.
    using meanZ = meanX;

    /// @brief Definition of "meanV" field.
    using meanV = field::common::U4T<comms::option::ScalingRatio<1, 1000000L> >;

    /// @brief Definition of "obs" field.
    using obs = field::common::U4;

    /// @brief Definition of "valid" field.
    using valid = field::common::U1;

    /// @brief Definition of "active" field.
    using active = field::common::U1;

    /// @brief Definition of "reserved" field.
    using reserved = field::common::res2;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        dur,
        meanX,
        meanY,
        meanZ,
        meanV,
        obs,
        valid,
        active,
        reserved
    >;
};

/// @brief Definition of TIM-SVIN message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref TimSvinFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class TimSvin : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_TIM_SVIN>,
        comms::option::FieldsImpl<TimSvinFields::All>,
        comms::option::MsgType<TimSvin<TMsgBase> >
    >
{
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b dur for @ref TimSvinFields::dur field
    ///     @li @b meanX for @ref TimSvinFields::meanX field
    ///     @li @b meanY for @ref TimSvinFields::meanY field
    ///     @li @b meanZ for @ref TimSvinFields::meanZ field
    ///     @li @b meanV for @ref TimSvinFields::meanV field
    ///     @li @b obs for @ref TimSvinFields::obs field
    ///     @li @b valid for @ref TimSvinFields::valid field
    ///     @li @b active for @ref TimSvinFields::active field
    ///     @li @b reserved for @ref TimSvinFields::reserved field
    COMMS_MSG_FIELDS_ACCESS(dur, meanX, meanY, meanZ, meanV, obs, valid, active, reserved);

    /// @brief Default constructor
    TimSvin() = default;

    /// @brief Copy constructor
    TimSvin(const TimSvin&) = default;

    /// @brief Move constructor
    TimSvin(TimSvin&& other) = default;

    /// @brief Destructor
    ~TimSvin() = default;

    /// @brief Copy assignment
    TimSvin& operator=(const TimSvin&) = default;

    /// @brief Move assignment
    TimSvin& operator=(TimSvin&&) = default;
};


}  // namespace message

}  // namespace ublox

