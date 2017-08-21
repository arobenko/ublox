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
/// @brief Contains definition of RXM-RTCM message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the RXM-RTCM message fields.
/// @see RxmRtcm
struct RxmRtcmFields
{
    /// @brief Definition of "version" field.
    using version =
        field::common::U1T<
            comms::option::DefaultNumValue<2>,
            comms::option::ValidNumValueRange<2, 2>
        >;

    /// @brief Definition of "flags" field.
    struct flags : public
        field::common::X1T<
            comms::option::BitmaskReservedBits<0xfe, 0>
        >
    {
        /// @brief Provide names and access functions for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS_SEQ macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS_SEQ(crcFailed);
    };

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res2;

    /// @brief Definition of "refStation" field.
    using refStation = field::common::U2;

    /// @brief Definition of "msgType" field.
    using msgType = field::common::U2;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        version,
        flags,
        reserved1,
        refStation,
        msgType
    >;
};

/// @brief Definition of RXM-RTCM message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref RxmRtcmFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class RxmRtcm : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_RXM_RTCM>,
        comms::option::FieldsImpl<RxmRtcmFields::All>,
        comms::option::MsgType<RxmRtcm<TMsgBase> >
    >
{
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b version for @ref RxmRtcmFields::version field
    ///     @li @b flags for @ref RxmRtcmFields::flags field
    ///     @li @b reserved1 for @ref RxmRtcmFields::reserved1 field
    ///     @li @b refStation for @ref RxmRtcmFields::refStation field
    ///     @li @b msgType for @ref RxmRtcmFields::msgType field
    COMMS_MSG_FIELDS_ACCESS(
        version,
        flags,
        reserved1,
        refStation,
        msgType);

    /// @brief Default constructor
    RxmRtcm() = default;

    /// @brief Copy constructor
    RxmRtcm(const RxmRtcm&) = default;

    /// @brief Move constructor
    RxmRtcm(RxmRtcm&& other) = default;

    /// @brief Destructor
    ~RxmRtcm() = default;

    /// @brief Copy assignment
    RxmRtcm& operator=(const RxmRtcm&) = default;

    /// @brief Move assignment
    RxmRtcm& operator=(RxmRtcm&&) = default;
};


}  // namespace message

}  // namespace ublox





