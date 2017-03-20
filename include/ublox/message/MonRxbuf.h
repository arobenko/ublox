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
/// @brief Contains definition of MON-RXBUF message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the MON-RXBUF message fields.
/// @see MonRxbuf
struct MonRxbufFields
{
    /// @brief Definition of "pending" field.
    /// @tparam TOpt Extra option(s)
    template <typename TOpt = comms::option::EmptyOption>
    using pending =
        field::common::ListT<
            field::common::U2,
            comms::option::SequenceFixedSize<6>,
            TOpt
        >;

    /// @brief Definition of "usage" field.
    /// @tparam TOpt Extra option(s)
    template <typename TOpt = comms::option::EmptyOption>
    using usage =
        field::common::ListT<
            field::common::U1T<comms::option::ValidNumValueRange<0, 100> >,
            comms::option::SequenceFixedSize<6>,
            TOpt
        >;

    /// @brief Definition of "peakUsage" field.
    /// @tparam TOpt Extra option(s)
    template <typename TOpt = comms::option::EmptyOption>
    using peakUsage = usage<TOpt>;

    /// @brief All the fields bundled in std::tuple.
    /// @tparam TOpt Extra option(s) for @ref pending, @ref usage, and @b peakUsage fields
    template <typename TOpt>
    using All = std::tuple<
        pending<TOpt>,
        usage<TOpt>,
        peakUsage<TOpt>
    >;
};

/// @brief Definition of MON-RXBUF message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref MonRxbufFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
/// @tparam TOpt Extra option(s) for @b pending, @b usage and @b peakUsage fields
template <typename TMsgBase = Message, typename TOpt = comms::option::EmptyOption>
class MonRxbuf : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_MON_RXBUF>,
        comms::option::FieldsImpl<MonRxbufFields::All<TOpt> >,
        comms::option::MsgType<MonRxbuf<TMsgBase, TOpt> >
    >
{
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b pending for @ref MonRxbufFields::pending field
    ///     @li @b usage for @ref MonRxbufFields::usage field
    ///     @li @b peakUsage for @ref MonRxbufFields::peakUsage field
    COMMS_MSG_FIELDS_ACCESS(pending, usage, peakUsage);

    /// @brief Default constructor
    MonRxbuf() = default;

    /// @brief Copy constructor
    MonRxbuf(const MonRxbuf&) = default;

    /// @brief Move constructor
    MonRxbuf(MonRxbuf&& other) = default;

    /// @brief Destructor
    ~MonRxbuf() = default;

    /// @brief Copy assignment
    MonRxbuf& operator=(const MonRxbuf&) = default;

    /// @brief Move assignment
    MonRxbuf& operator=(MonRxbuf&&) = default;
};


}  // namespace message

}  // namespace ublox

