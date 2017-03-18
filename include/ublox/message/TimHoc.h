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
/// @brief Contains definition of TIM-HOC message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the TIM-HOC message fields.
/// @see TimHoc
struct TimHocFields
{
    /// @brief Definition of "version" field.
    using version = field::common::U1T<comms::option::ValidNumValueRange<0, 0> >;

    /// @brief Value enumeration for @ref oscId field.
    enum class OscId : std::uint8_t
    {
        Internal, ///< Internal oscillator
        External, ///< External oschillator
        NumOfValues ///< number of available values
    };

    /// @brief Definition of "oscId" field.
    using oscId =
        field::common::EnumT<
            OscId,
            comms::option::ValidNumValueRange<0, (int)OscId::NumOfValues - 1>
        >;

    /// @brief Definition of "flags" field.
    struct flags : public
        field::common::X1T<
            comms::option::BitmaskReservedBits<0xfc, 0>
        >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS(raw, difference);
    };


    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res1;

    /// @brief Definition of "value" field.
    using value =
        field::common::I4T<
            comms::option::ScalingRatio<1, 0x100>
        >;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        version,
        oscId,
        flags,
        reserved1,
        value
    >;

};

/// @brief Definition of TIM-HOC message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref TimHocFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class TimHoc : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_TIM_HOC>,
        comms::option::FieldsImpl<TimHocFields::All>,
        comms::option::MsgType<TimHoc<TMsgBase> >
    >
{
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b version for @ref TimHocFields::version field
    ///     @li @b oscId for @ref TimHocFields::oscId field
    ///     @li @b flags for @ref TimHocFields::flags field
    ///     @li @b reserved1 for @ref TimHocFields::reserved1 field
    ///     @li @b value for @ref TimHocFields::value field
    COMMS_MSG_FIELDS_ACCESS(
        version,
        oscId,
        flags,
        reserved1,
        value
    );

    /// @brief Default constructor
    TimHoc() = default;

    /// @brief Copy constructor
    TimHoc(const TimHoc&) = default;

    /// @brief Move constructor
    TimHoc(TimHoc&& other) = default;

    /// @brief Destructor
    virtual ~TimHoc() = default;

    /// @brief Copy assignment
    TimHoc& operator=(const TimHoc&) = default;

    /// @brief Move assignment
    TimHoc& operator=(TimHoc&&) = default;
};


}  // namespace message

}  // namespace ublox

