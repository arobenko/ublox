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
/// @brief Contains definition of TIM-VCOCAL (extended command) message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the TIM-VCOCAL (extended command) message fields.
/// @see TimVcocalExt
struct TimVcocalExtFields
{
    /// @brief Definition of "type" field.
    using type =
        field::common::U1T<
        comms::option::ValidNumValueRange<2, 2>,
        comms::option::DefaultNumValue<2>,
        comms::option::FailOnInvalid
    >;

    /// @brief Definition of "version" field.
    using version = field::common::U1T<comms::option::ValidNumValueRange<0, 0> >;

    /// @brief Enumeration value for @ref oscId field
    enum class OscId : std::uint8_t
    {
        Internal, ///< internal oschillator
        External, ///< external oscillator
        NumOfValues ///< number of available values
    };

    /// @brief Definition of "oscId" field.
    using oscId =
        field::common::EnumT<
            OscId,
            comms::option::ValidNumValueRange<0, (int)OscId::NumOfValues - 1>
        >;

    /// @brief Enumeration value for @ref srcId field
    enum class SrcId : std::uint8_t
    {
        InternalOsc, ///< internal oschillator
        GNSS, ///< GNSS
        EXTINT0, ///< EXTINT0
        EXTINT1, ///< EXTINT1
        NumOfValues ///< number of available values
    };

    /// @brief Definition of "srcId" field.
    using srcId =
        field::common::EnumT<
            SrcId,
            comms::option::ValidNumValueRange<0, (int)SrcId::NumOfValues - 1>
        >;

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res2;

    /// @brief Definition of "raw0" field.
    using raw0 = field::common::U2;

    /// @brief Definition of "raw1" field.
    using raw1 = field::common::U2;

    /// @brief Definition of "maxStepSize" field.
    using maxStepSize = field::common::U2;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        type,
        version,
        oscId,
        srcId,
        reserved1,
        raw0,
        raw1,
        maxStepSize
    >;
};

/// @brief Definition of TIM-VCOCAL (extended command) message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref TimVcocalExtFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class TimVcocalExt : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_TIM_VCOCAL>,
        comms::option::FieldsImpl<TimVcocalExtFields::All>,
        comms::option::MsgType<TimVcocalExt<TMsgBase> >
    >
{
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b type for @ref TimVcocalExtFields::type field
    ///     @li @b version for @ref TimVcocalExtFields::version field
    ///     @li @b oscId for @ref TimVcocalExtFields::oscId field
    ///     @li @b srcId for @ref TimVcocalExtFields::srcId field
    ///     @li @b reserved1 for @ref TimVcocalExtFields::reserved1 field
    ///     @li @b raw0 for @ref TimVcocalExtFields::raw0 field
    ///     @li @b raw1 for @ref TimVcocalExtFields::raw1 field
    ///     @li @b maxStepSize for @ref TimVcocalExtFields::maxStepSize field
    COMMS_MSG_FIELDS_ACCESS(
        type,
        version,
        oscId,
        srcId,
        reserved1,
        raw0,
        raw1,
        maxStepSize
    );

    /// @brief Default constructor
    TimVcocalExt() = default;

    /// @brief Copy constructor
    TimVcocalExt(const TimVcocalExt&) = default;

    /// @brief Move constructor
    TimVcocalExt(TimVcocalExt&& other) = default;

    /// @brief Destructor
    ~TimVcocalExt() = default;

    /// @brief Copy assignment
    TimVcocalExt& operator=(const TimVcocalExt&) = default;

    /// @brief Move assignment
    TimVcocalExt& operator=(TimVcocalExt&&) = default;
};


}  // namespace message

}  // namespace ublox

