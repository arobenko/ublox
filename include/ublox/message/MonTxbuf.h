//
// Copyright 2015 - 2016 (C). Alex Robenko. All rights reserved.
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
    /// @brief Use this enumeration to access member fields of @ref errors bitfield.
    enum
    {
        errors_limit, ///< index of @ref limit member field
        errors_bits, ///< index of @ref errorsBits member field.
        errors_numOfValues ///< number of available member fields
    };

    /// @brief Bits access enumeration for bits in @b errorsBits member of
    ///     @ref errors bitfield field.
    enum
    {
        errorsBits_mem, ///< @b mem bit index
        errorsBits_alloc, ///< @b alloc bit index
        errorsBits_numOfValues ///< number of available bits
    };

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
    using errorsBits =
        field::common::X1T<
            comms::option::FixedBitLength<2>
        >;

    /// @brief Definition of "errors" field.
    using errors =
        field::common::BitfieldT<
            std::tuple<
                limit,
                errorsBits
            >
        >;

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
///     See @ref MonTxbufFields and for definition of the fields this message contains.
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

#ifdef FOR_DOXYGEN_DOC_ONLY
    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_pending, ///< @b pending field, see @ref MonTxbufFields::pending
        FieldIdx_usage, ///< @b usage field, see @ref MonTxbufFields::usage
        FieldIdx_peakUsage, ///< @b peakUsage field, see @ref MonTxbufFields::peakUsage
        FieldIdx_tUsage, ///< @b tUsage field, see @ref MonTxbufFields::tUsage
        FieldIdx_tPeakUsage, ///< @b tPeakUsage field, see @ref MonTxbufFields::tPeakUsage
        FieldIdx_errors, ///< @b errors field, see @ref MonTxbufFields::errors
        FieldIdx_reserved1, ///< @b reserved1 field, see @ref MonTxbufFields::reserved1
        FieldIdx_numOfValues ///< number of available fields
    };

    /// @brief Access to fields bundled as a struct
    struct FieldsAsStruct
    {
        MonTxbufFields::pending& pending; ///< @b pending field, see @ref MonTxbufFields::pending
        MonTxbufFields::usage& usage; ///< @b usage field, see @ref MonTxbufFields::usage
        MonTxbufFields::peakUsage& peakUsage; ///< @b peakUsage field, see @ref MonTxbufFields::peakUsage
        MonTxbufFields::tUsage& tUsage; ///< @b tUsage field, see @ref MonTxbufFields::tUsage
        MonTxbufFields::tPeakUsage& tPeakUsage; ///< @b tPeakUsage field, see @ref MonTxbufFields::tPeakUsage
        MonTxbufFields::errors& errors; ///< @b errors field, see @ref MonTxbufFields::errors
        MonTxbufFields::reserved1& reserved1; ///< @b reserved1 field, see @ref MonTxbufFields::reserved1
    };

    /// @brief Access to @b const fields bundled as a struct
    struct ConstFieldsAsStruct
    {
        MonTxbufFields::pending& pending; ///< @b pending field, see @ref MonTxbufFields::pending
        MonTxbufFields::usage& usage; ///< @b usage field, see @ref MonTxbufFields::usage
        MonTxbufFields::peakUsage& peakUsage; ///< @b peakUsage field, see @ref MonTxbufFields::peakUsage
        MonTxbufFields::tUsage& tUsage; ///< @b tUsage field, see @ref MonTxbufFields::tUsage
        MonTxbufFields::tPeakUsage& tPeakUsage; ///< @b tPeakUsage field, see @ref MonTxbufFields::tPeakUsage
        MonTxbufFields::errors& errors; ///< @b errors field, see @ref MonTxbufFields::errors
        MonTxbufFields::reserved1& reserved1; ///< @b reserved1 field, see @ref MonTxbufFields::reserved1
    };

    /// @brief Get access to fields bundled into a struct
    FieldsAsStruct fieldsAsStruct();

    /// @brief Get access to @b const fields bundled into a struct
    ConstFieldsAsStruct fieldsAsStruct() const;

#else
    COMMS_MSG_FIELDS_ACCESS(Base,
        pending,
        usage,
        peakUsage,
        tUsage,
        tPeakUsage,
        errors,
        reserved1
    );
#endif // #ifdef FOR_DOXYGEN_DOC_ONLY

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

