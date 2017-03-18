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
/// @see TimFchg
struct TimFchgFields
{
    /// @brief Definition of "version" field.
    using version = field::common::U1T<comms::option::ValidNumValueRange<0, 0> >;

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res3;

    /// @brief Definition of "iTOW" field.
    using iTOW = field::common::iTOW;

    /// @brief Definition of "intDeltaFreq" field.
    using intDeltaFreq =
        field::common::I4T<
            comms::option::ScalingRatio<1, 0x100>
        >;

    /// @brief Definition of "intDeltaFreqUnc" field.
    using intDeltaFreqUnc =
        field::common::U4T<
            comms::option::ScalingRatio<1, 0x100>
        >;

    /// @brief Definition of "intRaw" field.
    using intRaw = field::common::U4;

    /// @brief Definition of "extDeltaFreq" field.
    using extDeltaFreq =
        field::common::I4T<
            comms::option::ScalingRatio<1, 0x100>
        >;

    /// @brief Definition of "extDeltaFreqUnc" field.
    using extDeltaFreqUnc =
        field::common::U4T<
            comms::option::ScalingRatio<1, 0x100>
        >;

    /// @brief Definition of "extRaw" field.
    using extRaw = field::common::U4;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        version,
        reserved1,
        iTOW,
        intDeltaFreq,
        intDeltaFreqUnc,
        intRaw,
        extDeltaFreq,
        extDeltaFreqUnc,
        extRaw
    >;
};

/// @brief Definition of TIM-DOSC message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref TimFchgFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class TimFchg : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_TIM_FCHG>,
        comms::option::FieldsImpl<TimFchgFields::All>,
        comms::option::MsgType<TimFchg<TMsgBase> >
    >
{
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b version for @ref TimFchgFields::version field
    ///     @li @b reserved1 for @ref TimFchgFields::reserved1 field
    ///     @li @b iTOW for @ref TimFchgFields::iTOW field
    ///     @li @b intDeltaFreq for @ref TimFchgFields::intDeltaFreq field
    ///     @li @b intDeltaFreqUnc for @ref TimFchgFields::intDeltaFreqUnc field
    ///     @li @b intRaw for @ref TimFchgFields::intRaw field
    ///     @li @b extDeltaFreq for @ref TimFchgFields::extDeltaFreq field
    ///     @li @b extDeltaFreqUnc for @ref TimFchgFields::extDeltaFreqUnc field
    ///     @li @b extRaw for @ref TimFchgFields::extRaw field
    COMMS_MSG_FIELDS_ACCESS(
        version,
        reserved1,
        iTOW,
        intDeltaFreq,
        intDeltaFreqUnc,
        intRaw,
        extDeltaFreq,
        extDeltaFreqUnc,
        extRaw
    );

    /// @brief Default constructor
    TimFchg() = default;

    /// @brief Copy constructor
    TimFchg(const TimFchg&) = default;

    /// @brief Move constructor
    TimFchg(TimFchg&& other) = default;

    /// @brief Destructor
    virtual ~TimFchg() = default;

    /// @brief Copy assignment
    TimFchg& operator=(const TimFchg&) = default;

    /// @brief Move assignment
    TimFchg& operator=(TimFchg&&) = default;
};


}  // namespace message

}  // namespace ublox

