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
/// @brief Contains definition of MON-IO message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the MON-IO message fields.
/// @see MonIo
struct MonIoFields
{
    /// @brief Use this enumeration to access member fields of @ref block bundle.
    enum
    {
        block_rxBytes, ///< index of @ref rxBytes member field
        block_txBytes, ///< index of @ref txBytes member field
        block_parityErrs, ///< index of @ref parityErrs member field
        block_framingErrs, ///< index of @ref framingErrs member field
        block_overrunErrs, ///< index of @ref overrunErrs member field
        block_breakCond, ///< index of @ref breakCond member field
        block_rxBusy, ///< index of @ref rxBusy member field
        block_txBusy, ///< index of @ref txBusy member field
        block_reserved1, ///< index of @ref reserved1 member field
        block_numOfValues ///< number of available member fields
    };

    /// @brief Definition of "rxBytes" field.
    using rxBytes = field::common::U4;

    /// @brief Definition of "txBytes" field.
    using txBytes = field::common::U4;

    /// @brief Definition of "parityErrs" field.
    using parityErrs = field::common::U2;

    /// @brief Definition of "framingErrs" field.
    using framingErrs = field::common::U2;

    /// @brief Definition of "overrunErrs" field.
    using overrunErrs = field::common::U2;

    /// @brief Definition of "breakCond" field.
    using breakCond = field::common::U2;

    /// @brief Definition of "rxBusy" field.
    using rxBusy = field::common::U1;

    /// @brief Definition of "txBusy" field.
    using txBusy = field::common::U1;

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::U2;

    /// @brief Definition of the single block of data.
    using block =
        field::common::BundleT<
            std::tuple<
                rxBytes,
                txBytes,
                parityErrs,
                framingErrs,
                overrunErrs,
                breakCond,
                rxBusy,
                txBusy,
                reserved1
            >
        >;

    /// @brief Definition of the list of blocks.
    using data =
        field::common::ListT<block>;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        data
    >;
};

/// @brief Definition of MON-IO message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref MonIoFields and for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class MonIo : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_MON_IO>,
        comms::option::FieldsImpl<MonIoFields::All>,
        comms::option::MsgType<MonIo<TMsgBase> >,
        comms::option::DispatchImpl
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_MON_IO>,
        comms::option::FieldsImpl<MonIoFields::All>,
        comms::option::MsgType<MonIo<TMsgBase> >,
        comms::option::DispatchImpl
    > Base;
public:

#ifdef FOR_DOXYGEN_DOC_ONLY
    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_data, ///< @b data field, see @ref MonIoFields::data
        FieldIdx_numOfValues ///< number of available fields
    };

    /// @brief Access to fields bundled as a struct
    struct FieldsAsStruct
    {
        MonIoFields::data& data; ///< @b data field, see @ref MonIoFields::data
    };

    /// @brief Access to @b const fields bundled as a struct
    struct ConstFieldsAsStruct
    {
        const MonIoFields::data& data;
    };

    /// @brief Get access to fields bundled into a struct
    FieldsAsStruct fieldsAsStruct();

    /// @brief Get access to @b const fields bundled into a struct
    ConstFieldsAsStruct fieldsAsStruct() const;

#else
    COMMS_MSG_FIELDS_ACCESS(Base, data);
#endif // #ifdef FOR_DOXYGEN_DOC_ONLY

    /// @brief Default constructor
    MonIo() = default;

    /// @brief Copy constructor
    MonIo(const MonIo&) = default;

    /// @brief Move constructor
    MonIo(MonIo&& other) = default;

    /// @brief Destructor
    virtual ~MonIo() = default;

    /// @brief Copy assignment
    MonIo& operator=(const MonIo&) = default;

    /// @brief Move assignment
    MonIo& operator=(MonIo&&) = default;
};


}  // namespace message

}  // namespace ublox

