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
/// @brief Contains definition of RXM-PMREQ message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the RXM-PMREQ message fields.
/// @see RxmPmreq
struct RxmPmreqFields
{
    /// @brief Definition of "duration" field.
    using duration = field::common::U4T<comms::option::UnitsMilliseconds>;

    /// @brief Definition of "flags" field.
    struct flags : public
        field::common::X4T<
            comms::option::BitmaskReservedBits<0xfffffffd, 0>
        >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS(backup=1);
    };

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        duration,
        flags
    >;
};

/// @brief Definition of RXM-PMREQ message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref RxmPmreqFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class RxmPmreq : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_RXM_PMREQ>,
        comms::option::FieldsImpl<RxmPmreqFields::All>,
        comms::option::MsgType<RxmPmreq<TMsgBase> >
    >
{
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b duration for @ref RxmPmreqFields::duration field
    ///     @li @b flags for @ref RxmPmreqFields::flags field
    COMMS_MSG_FIELDS_ACCESS(duration, flags);

    /// @brief Default constructor
    RxmPmreq() = default;

    /// @brief Copy constructor
    RxmPmreq(const RxmPmreq&) = default;

    /// @brief Move constructor
    RxmPmreq(RxmPmreq&& other) = default;

    /// @brief Destructor
    ~RxmPmreq() = default;

    /// @brief Copy assignment
    RxmPmreq& operator=(const RxmPmreq&) = default;

    /// @brief Move assignment
    RxmPmreq& operator=(RxmPmreq&&) = default;
};


}  // namespace message

}  // namespace ublox





