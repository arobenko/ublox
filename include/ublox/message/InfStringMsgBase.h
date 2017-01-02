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
/// @brief Contains base class of all the INF messages.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the INF-* message fields.
/// @see InfStringMsgBase
struct InfStringMsgBaseFields
{
    /// @brief Definition of "str" field.
    using str = field::common::String;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        str
    >;
};

/// @brief Base class of any INF-* message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref InfStringMsgBaseFields and for definition of the fields this message contains.
/// @tparam TId ID of actual INF-* message
/// @tparam TMsgBase Common interface class for all the messages.
template <MsgId TId, typename TMsgBase = Message>
class InfStringMsgBase : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<TId>,
        comms::option::FieldsImpl<InfStringMsgBaseFields::All>,
        comms::option::MsgType<InfStringMsgBase<TId, TMsgBase> >,
        comms::option::DispatchImpl
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<TId>,
        comms::option::FieldsImpl<InfStringMsgBaseFields::All>,
        comms::option::MsgType<InfStringMsgBase<TId, TMsgBase> >,
        comms::option::DispatchImpl
    > Base;
public:

#ifdef FOR_DOXYGEN_DOC_ONLY
    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_str, ///< @b str field, see @ref InfStringMsgBaseFields::str
        FieldIdx_numOfValues ///< number of available fields
    };

    /// @brief Access to fields bundled as a struct
    struct FieldsAsStruct
    {
        InfStringMsgBaseFields::str& str; ///< @b str field, see @ref InfStringMsgBaseFields::str
    };

    /// @brief Access to @b const fields bundled as a struct
    struct ConstFieldsAsStruct
    {
        const InfStringMsgBaseFields::str& str; ///< @b str field, see @ref InfStringMsgBaseFields::str
    };

    /// @brief Get access to fields bundled into a struct
    FieldsAsStruct fieldsAsStruct();

    /// @brief Get access to @b const fields bundled into a struct
    ConstFieldsAsStruct fieldsAsStruct() const;

#else
    COMMS_MSG_FIELDS_ACCESS(Base, str);
#endif // #ifdef FOR_DOXYGEN_DOC_ONLY


    /// @brief Default constructor
    InfStringMsgBase() = default;

    /// @brief Copy constructor
    InfStringMsgBase(const InfStringMsgBase&) = default;

    /// @brief Move constructor
    InfStringMsgBase(InfStringMsgBase&& other) = default;

    /// @brief Destructor
    virtual ~InfStringMsgBase() = default;

    /// @brief Copy assignment
    InfStringMsgBase& operator=(const InfStringMsgBase&) = default;

    /// @brief Move assignment
    InfStringMsgBase& operator=(InfStringMsgBase&&) = default;
};


}  // namespace message

}  // namespace ublox

