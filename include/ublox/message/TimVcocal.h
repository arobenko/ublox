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
/// @brief Contains definition of TIM-VCOCAL message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the TIM-VCOCAL message fields.
/// @see TimVcocal
struct TimVcocalFields
{
    /// @brief Definition of "type" field.
    using type =
        field::common::U1T<
        comms::option::ValidNumValueRange<3, 3>,
        comms::option::DefaultNumValue<3>,
        comms::option::FailOnInvalid
    >;

    /// @brief Definition of "version" field.
    using version = field::common::U1T<comms::option::ValidNumValueRange<0, 0> >;

    /// @brief Enumeration value for @ref oscId field
    enum class OscId : std::uint8_t
    {
        Internal, ///< internal oschillator
        ernal, ///< external oscillator
        NumOfValues ///< number of available values
    };

    /// @brief Definition of "oscId" field.
    using oscId =
        field::common::EnumT<
            OscId,
            comms::option::ValidNumValueRange<0, (int)OscId::NumOfValues - 1>
        >;

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res3;

    /// @brief Definition of "gainUncertainty" field.
    using gainUncertainty =
        field::common::U2T<comms::option::ScalingRatio<1, 0x10000> >;

    /// @brief Definition of "gainVco" field.
    using gainVco =
        field::common::I4T<comms::option::ScalingRatio<1, 0x10000> >;


    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        type,
        version,
        oscId,
        reserved1,
        gainUncertainty,
        gainVco
    >;
};

/// @brief Definition of TIM-VCOCAL message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref TimVcocalFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class TimVcocal : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_TIM_VCOCAL>,
        comms::option::FieldsImpl<TimVcocalFields::All>,
        comms::option::MsgType<TimVcocal<TMsgBase> >
    >
{
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b type for @ref TimVcocalFields::type field
    ///     @li @b version for @ref TimVcocalFields::version field
    ///     @li @b oscId for @ref TimVcocalFields::oscId field
    ///     @li @b reserved1 for @ref TimVcocalFields::reserved1 field
    ///     @li @b gainUncertainty for @ref TimVcocalFields::gainUncertainty field
    ///     @li @b gainVco for @ref TimVcocalFields::gainVco field
    COMMS_MSG_FIELDS_ACCESS(
        type,
        version,
        oscId,
        reserved1,
        gainUncertainty,
        gainVco
    );

    /// @brief Default constructor
    TimVcocal() = default;

    /// @brief Copy constructor
    TimVcocal(const TimVcocal&) = default;

    /// @brief Move constructor
    TimVcocal(TimVcocal&& other) = default;

    /// @brief Destructor
    virtual ~TimVcocal() = default;

    /// @brief Copy assignment
    TimVcocal& operator=(const TimVcocal&) = default;

    /// @brief Move assignment
    TimVcocal& operator=(TimVcocal&&) = default;
};


}  // namespace message

}  // namespace ublox

