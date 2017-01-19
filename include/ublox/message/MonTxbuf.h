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
/// @brief Contains definition of MON-TXBUF message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the MON-TXBUF message fields.
/// @see MonTxbuf
struct MonTxbufFields
{

    /// @brief Definition of "pending" field.
    using pending =
        field::common::ListT<
            field::common::U2,
            comms::option::SequenceFixedSize<6>
        >;

    /// @brief Definition of "usage" field.
    using usage =
        field::common::ListT<
            field::common::U1T<comms::option::ValidNumValueRange<0, 100> >,
            comms::option::SequenceFixedSize<6>
        >;

    /// @brief Definition of "peakUsage" field.
    using peakUsage = usage;

    /// @brief Definition of "tUsage" field.
    using tUsage = field::common::U1T<comms::option::ValidNumValueRange<0, 100> >;

    /// @brief Definition of "tPeakUsage" field.
    using tPeakUsage = tUsage;

    /// @brief Definition of "limit" member field in @ref errors bitfield.
    using limit =
        field::common::U1T<
            comms::option::ValidNumValueRange<0, 0x3f>,
            comms::option::FixedBitLength<6>
        >;

    /// @brief Definition of remaining bits in @ref errors bitfield as
    ///     a single bitmask.
    struct errorsBits : public
        field::common::X1T<
            comms::option::FixedBitLength<2>
        >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS(mem, alloc);
    };

    /// @brief Base class of @ref errors field.
    using errorsBase =
        field::common::BitfieldT<
            std::tuple<
                limit,
                errorsBits
            >
        >;

    /// @brief Definition of "errors" field.
    struct errors : public errorsBase
    {
        /// @brief Allow access to internal fields.
        /// @details See definition of @b COMMS_FIELD_MEMBERS_ACCESS macro
        ///     related to @b comms::field::Bitfield class from COMMS library
        ///     for details.
        COMMS_FIELD_MEMBERS_ACCESS(errorsBase, limit, errorsBits);
    };

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res1;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        pending,
        usage,
        peakUsage,
        tUsage,
        tPeakUsage,
        errors,
        reserved1
    >;
};

/// @brief Definition of MON-TXBUF message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref MonTxbufFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class MonTxbuf : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_MON_TXBUF>,
        comms::option::FieldsImpl<MonTxbufFields::All>,
        comms::option::MsgType<MonTxbuf<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_MON_TXBUF>,
        comms::option::FieldsImpl<MonTxbufFields::All>,
        comms::option::MsgType<MonTxbuf<TMsgBase> >
    > Base;
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b pending for @ref MonTxbufFields::pending field
    ///     @li @b usage for @ref MonTxbufFields::usage field
    ///     @li @b peakUsage for @ref MonTxbufFields::peakUsage field
    ///     @li @b tUsage for @ref MonTxbufFields::tUsage field
    ///     @li @b tPeakUsage for @ref MonTxbufFields::tPeakUsage field
    ///     @li @b errors for @ref MonTxbufFields::errors field
    ///     @li @b reserved1 for @ref MonTxbufFields::reserved1 field
    COMMS_MSG_FIELDS_ACCESS(Base,
        pending,
        usage,
        peakUsage,
        tUsage,
        tPeakUsage,
        errors,
        reserved1
    );

    /// @brief Default constructor
    MonTxbuf() = default;

    /// @brief Copy constructor
    MonTxbuf(const MonTxbuf&) = default;

    /// @brief Move constructor
    MonTxbuf(MonTxbuf&& other) = default;

    /// @brief Destructor
    virtual ~MonTxbuf() = default;

    /// @brief Copy assignment
    MonTxbuf& operator=(const MonTxbuf&) = default;

    /// @brief Move assignment
    MonTxbuf& operator=(MonTxbuf&&) = default;
};


}  // namespace message

}  // namespace ublox

