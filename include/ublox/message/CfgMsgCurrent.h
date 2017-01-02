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
/// @brief Contains definition of CFG-MSG (<b>current port</b>) message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/MsgId.h"
#include "ublox/field/cfg.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the CFG-MSG (<b>current port</b>) message fields.
/// @see CfgMsgCurrent
struct CfgMsgCurrentFields
{
    /// @brief Definition of "id" field (combining class ID and message ID).
    using id = field::MsgId;

    /// @brief Definition of "rate" field.
    using rate = field::common::U1;

    /// @brief All the fields bundled in std::tuple.
    using All =
        std::tuple<
            id,
            rate
        >;
};

/// @brief Definition of CFG-MSG (<b>current port</b>) message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref CfgMsgCurrentFields and for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class CfgMsgCurrent : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_MSG>,
        comms::option::FieldsImpl<CfgMsgCurrentFields::All>,
        comms::option::MsgType<CfgMsgCurrent<TMsgBase> >,
        comms::option::DispatchImpl
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_MSG>,
        comms::option::FieldsImpl<CfgMsgCurrentFields::All>,
        comms::option::MsgType<CfgMsgCurrent<TMsgBase> >,
        comms::option::DispatchImpl
    > Base;
public:

#ifdef FOR_DOXYGEN_DOC_ONLY
    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_id, ///< @b id field, see @ref CfgMsgCurrentFields::id
        FieldIdx_rate, ///< @b rate field, see @ref CfgMsgCurrentFields::rate
        FieldIdx_numOfValues ///< number of available fields
    };
    /// @brief Access to fields bundled as a struct
    struct FieldsAsStruct
    {
        CfgMsgCurrentFields::id& id; ///< @b id field, see @ref CfgMsgCurrentFields::id
        CfgMsgCurrentFields::rate& rate; ///< @b rate field, see @ref CfgMsgCurrentFields::rate
    };

    /// @brief Access to @b const fields bundled as a struct
    struct ConstFieldsAsStruct
    {
        const CfgMsgCurrentFields::id& id; ///< @b id field, see @ref CfgMsgCurrentFields::id
        const CfgMsgCurrentFields::rate& rate; ///< @b rate field, see @ref CfgMsgCurrentFields::rate
    };

    /// @brief Get access to fields bundled into a struct
    FieldsAsStruct fieldsAsStruct();

    /// @brief Get access to @b const fields bundled into a struct
    ConstFieldsAsStruct fieldsAsStruct() const;

#else
    COMMS_MSG_FIELDS_ACCESS(Base, id, rate);
#endif // #ifdef FOR_DOXYGEN_DOC_ONLY

    /// @brief Default constructor
    CfgMsgCurrent() = default;

    /// @brief Copy constructor
    CfgMsgCurrent(const CfgMsgCurrent&) = default;

    /// @brief Move constructor
    CfgMsgCurrent(CfgMsgCurrent&& other) = default;

    /// @brief Destructor
    virtual ~CfgMsgCurrent() = default;

    /// @brief Copy assignment
    CfgMsgCurrent& operator=(const CfgMsgCurrent&) = default;

    /// @brief Move assignment
    CfgMsgCurrent& operator=(CfgMsgCurrent&&) = default;
};


}  // namespace message

}  // namespace ublox

