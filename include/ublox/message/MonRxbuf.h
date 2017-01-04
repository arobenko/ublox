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

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        pending,
        usage,
        peakUsage
    >;
};

/// @brief Definition of MON-RXBUF message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref MonRxbufFields and for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class MonRxbuf : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_MON_RXBUF>,
        comms::option::FieldsImpl<MonRxbufFields::All>,
        comms::option::MsgType<MonRxbuf<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_MON_RXBUF>,
        comms::option::FieldsImpl<MonRxbufFields::All>,
        comms::option::MsgType<MonRxbuf<TMsgBase> >
    > Base;
public:

#ifdef FOR_DOXYGEN_DOC_ONLY
    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_pending, ///< @b pending field, see @ref MonRxbufFields::pending
        FieldIdx_usage, ///< @b usage field, see @ref MonRxbufFields::usage
        FieldIdx_peakUsage, ///< @b peakUsage field, see @ref MonRxbufFields::peakUsage
        FieldIdx_numOfValues ///< number of available fields
    };

    /// @brief Access to fields bundled as a struct
    struct FieldsAsStruct
    {
        MonRxbufFields::pending& pending; ///< @b pending field, see @ref MonRxbufFields::pending
        MonRxbufFields::usage& usage; ///< @b usage field, see @ref MonRxbufFields::usage
        MonRxbufFields::peakUsage& peakUsage; ///< @b peakUsage field, see @ref MonRxbufFields::peakUsage
    };

    /// @brief Access to @b const fields bundled as a struct
    struct ConstFieldsAsStruct
    {
        const MonRxbufFields::pending& pending; ///< @b pending field, see @ref MonRxbufFields::pending
        const MonRxbufFields::usage& usage; ///< @b usage field, see @ref MonRxbufFields::usage
        const MonRxbufFields::peakUsage& peakUsage; ///< @b peakUsage field, see @ref MonRxbufFields::peakUsage
    };

    /// @brief Get access to fields bundled into a struct
    FieldsAsStruct fieldsAsStruct();

    /// @brief Get access to @b const fields bundled into a struct
    ConstFieldsAsStruct fieldsAsStruct() const;

#else
    COMMS_MSG_FIELDS_ACCESS(Base, pending, usage, peakUsage);
#endif // #ifdef FOR_DOXYGEN_DOC_ONLY

    /// @brief Default constructor
    MonRxbuf() = default;

    /// @brief Copy constructor
    MonRxbuf(const MonRxbuf&) = default;

    /// @brief Move constructor
    MonRxbuf(MonRxbuf&& other) = default;

    /// @brief Destructor
    virtual ~MonRxbuf() = default;

    /// @brief Copy assignment
    MonRxbuf& operator=(const MonRxbuf&) = default;

    /// @brief Move assignment
    MonRxbuf& operator=(MonRxbuf&&) = default;
};


}  // namespace message

}  // namespace ublox

