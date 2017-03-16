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
/// @brief Contains definition of RXM-RLM (@b short) message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the RXM-RLM (@b short) message fields.
/// @see RxmRlmShort
struct RxmRlmShortFields
{
    /// @brief Definition of "version" field.
    using version = field::common::U1T<comms::option::ValidNumValueRange<0, 0> >;

    /// @brief Definition of "type" field.
    using type =
        field::common::U1T<
            comms::option::ValidNumValueRange<1, 1>,
            comms::option::DefaultNumValue<1>,
            comms::option::FailOnInvalid
        >;

    /// @brief Definition of "svId" field.
    using svId = field::common::U1;

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res1;

    /// @brief Definition of "beacon_1" field.
    using beacon_1 = field::common::U4;

    /// @brief Definition of "beacon_2" field.
    using beacon_2 = field::common::U4;

    /// @brief Definition of "message" field.
    using message = field::common::U1;

    /// @brief Definition of "params" field.
    using params = field::common::U2;

    /// @brief Definition of "reserved2" field.
    using reserved2 = field::common::res1;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        version,
        type,
        svId,
        reserved1,
        beacon_1,
        beacon_2,
        message,
        params,
        reserved2
    >;
};

/// @brief Definition of RXM-RLM (@b short) message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref RxmRlmShortFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class RxmRlmShort : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_RXM_RLM>,
        comms::option::FieldsImpl<RxmRlmShortFields::All>,
        comms::option::MsgType<RxmRlmShort<TMsgBase> >
    >
{
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b version for @ref RxmRlmShortFields::version field
    ///     @li @b type for @ref RxmRlmShortFields::type field
    ///     @li @b svId for @ref RxmRlmShortFields::svId field
    ///     @li @b reserved1 for @ref RxmRlmShortFields::reserved1 field
    ///     @li @b beacon_1 for @ref RxmRlmShortFields::beacon_1 field
    ///     @li @b beacon_2 for @ref RxmRlmShortFields::beacon_2 field
    ///     @li @b message for @ref RxmRlmShortFields::message field
    ///     @li @b params for @ref RxmRlmShortFields::params field
    ///     @li @b reserved2 for @ref RxmRlmShortFields::reserved2 field
    COMMS_MSG_FIELDS_ACCESS(
        version,
        type,
        svId,
        reserved1,
        beacon_1,
        beacon_2,
        message,
        params,
        reserved2
    );

    /// @brief Default constructor
    RxmRlmShort() = default;

    /// @brief Copy constructor
    RxmRlmShort(const RxmRlmShort&) = default;

    /// @brief Move constructor
    RxmRlmShort(RxmRlmShort&& other) = default;

    /// @brief Destructor
    virtual ~RxmRlmShort() = default;

    /// @brief Copy assignment
    RxmRlmShort& operator=(const RxmRlmShort&) = default;

    /// @brief Move assignment
    RxmRlmShort& operator=(RxmRlmShort&&) = default;
};


}  // namespace message

}  // namespace ublox





