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
/// @brief Contains definition of RXM-PMREQ (version 0) message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the RXM-PMREQ (version 0) message fields.
/// @see RxmPmreqV0
struct RxmPmreqV0Fields
{
    /// @brief Definition of "version" field.
    using version =
        field::common::U1T<
            comms::option::ValidNumValueRange<0, 0>
        >;

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res3;

    /// @brief Definition of "duration" field.
    using duration = field::common::U4T<field::common::Scaling_ms2s>;

    /// @brief Definition of "flags" field.
    struct flags : public
        field::common::X4T<
            comms::option::BitmaskReservedBits<0xfffffff9, 0>
        >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS(backup=1, force);
    };

    /// @brief Definition of "wakeupSources" field.
    struct wakeupSources : public
        field::common::X4T<
            comms::option::BitmaskReservedBits<0xffffff17, 0>
        >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS(uartrx=3, extint0=5, extint1, spics);
    };

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        version,
        reserved1,
        duration,
        flags,
        wakeupSources
    >;
};

/// @brief Definition of RXM-PMREQ (version 0) message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref RxmPmreqV0Fields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class RxmPmreqV0 : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_RXM_PMREQ>,
        comms::option::FieldsImpl<RxmPmreqV0Fields::All>,
        comms::option::MsgType<RxmPmreqV0<TMsgBase> >
    >
{
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b version for @ref RxmPmreqV0Fields::version field
    ///     @li @b reserved1 for @ref RxmPmreqV0Fields::reserved1 field
    ///     @li @b duration for @ref RxmPmreqV0Fields::duration field
    ///     @li @b flags for @ref RxmPmreqV0Fields::flags field
    ///     @li @b wakeupSources for @ref RxmPmreqV0Fields::wakeupSources field
    COMMS_MSG_FIELDS_ACCESS(
        version,
        reserved1,
        duration,
        flags,
        wakeupSources
    );

    /// @brief Default constructor
    RxmPmreqV0() = default;

    /// @brief Copy constructor
    RxmPmreqV0(const RxmPmreqV0&) = default;

    /// @brief Move constructor
    RxmPmreqV0(RxmPmreqV0&& other) = default;

    /// @brief Destructor
    virtual ~RxmPmreqV0() = default;

    /// @brief Copy assignment
    RxmPmreqV0& operator=(const RxmPmreqV0&) = default;

    /// @brief Move assignment
    RxmPmreqV0& operator=(RxmPmreqV0&&) = default;

    /// @brief Provides custom read functionality.
    template <typename TIter>
    comms::ErrorStatus doRead(TIter& iter, std::size_t len)
    {
        typedef typename std::decay<decltype(comms::toMessageBase(*this))>::type Base;
        if (len < Base::doLength()) {
            return comms::ErrorStatus::InvalidMsgData;
        }

        return Base::doRead(iter, len);
    }
};


}  // namespace message

}  // namespace ublox





