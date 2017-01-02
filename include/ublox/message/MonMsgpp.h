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
/// @brief Contains definition of MON-MSGPP message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the MON-MSGPP message fields.
/// @see MonMsgpp
struct MonMsgppFields
{
    /// @brief Definition of "msg1" field.
    using msg1 =
        field::common::ListT<
            field::common::U2,
            comms::option::SequenceFixedSize<8>
        >;

    /// @brief Definition of "msg2" field.
    using msg2 = msg1;

    /// @brief Definition of "msg2" field.
    using msg3 = msg1;

    /// @brief Definition of "msg2" field.
    using msg4 = msg1;

    /// @brief Definition of "msg2" field.
    using msg5 = msg1;

    /// @brief Definition of "msg2" field.
    using msg6 = msg1;

    /// @brief Definition of "msg2" field.
    using skipped =
        field::common::ListT<
            field::common::U4,
            comms::option::SequenceFixedSize<6>
        >;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        msg1,
        msg2,
        msg3,
        msg4,
        msg5,
        msg6,
        skipped
    >;
};

/// @brief Definition of MON-MSGPP message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref MonMsgppFields and for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class MonMsgpp : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_MON_MSGPP>,
        comms::option::FieldsImpl<MonMsgppFields::All>,
        comms::option::MsgType<MonMsgpp<TMsgBase> >,
        comms::option::DispatchImpl
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_MON_MSGPP>,
        comms::option::FieldsImpl<MonMsgppFields::All>,
        comms::option::MsgType<MonMsgpp<TMsgBase> >,
        comms::option::DispatchImpl
    > Base;
public:

#ifdef FOR_DOXYGEN_DOC_ONLY
    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_msg1, ///< @b msg1 field, see @ref MonMsgppFields::msg1
        FieldIdx_msg2, ///< @b msg2 field, see @ref MonMsgppFields::msg2
        FieldIdx_msg3, ///< @b msg3 field, see @ref MonMsgppFields::msg3
        FieldIdx_msg4, ///< @b msg4 field, see @ref MonMsgppFields::msg4
        FieldIdx_msg5, ///< @b msg5 field, see @ref MonMsgppFields::msg5
        FieldIdx_msg6, ///< @b msg6 field, see @ref MonMsgppFields::msg6
        FieldIdx_skipped, ///< @b skipped field, see @ref MonMsgppFields::skipped
        FieldIdx_numOfValues ///< number of available fields
    };

    /// @brief Access to fields bundled as a struct
    struct FieldsAsStruct
    {
        MonMsgppFields::msg1& msg1; ///< @b msg1 field, see @ref MonMsgppFields::msg1
        MonMsgppFields::msg2& msg2; ///< @b msg2 field, see @ref MonMsgppFields::msg2
        MonMsgppFields::msg3& msg3; ///< @b msg3 field, see @ref MonMsgppFields::msg3
        MonMsgppFields::msg4& msg4; ///< @b msg4 field, see @ref MonMsgppFields::msg4
        MonMsgppFields::msg5& msg5; ///< @b msg5 field, see @ref MonMsgppFields::msg5
        MonMsgppFields::msg6& msg6; ///< @b msg6 field, see @ref MonMsgppFields::msg6
        MonMsgppFields::skipped& skipped; ///< @b skipped field, see @ref MonMsgppFields::skipped
    };

    /// @brief Access to @b const fields bundled as a struct
    struct ConstFieldsAsStruct
    {
        const MonMsgppFields::msg1& msg1; ///< @b msg1 field, see @ref MonMsgppFields::msg1
        const MonMsgppFields::msg2& msg2; ///< @b msg2 field, see @ref MonMsgppFields::msg2
        const MonMsgppFields::msg3& msg3; ///< @b msg3 field, see @ref MonMsgppFields::msg3
        const MonMsgppFields::msg4& msg4; ///< @b msg4 field, see @ref MonMsgppFields::msg4
        const MonMsgppFields::msg5& msg5; ///< @b msg5 field, see @ref MonMsgppFields::msg5
        const MonMsgppFields::msg6& msg6; ///< @b msg6 field, see @ref MonMsgppFields::msg6
        const MonMsgppFields::skipped& skipped; ///< @b skipped field, see @ref MonMsgppFields::skipped
    };

    /// @brief Get access to fields bundled into a struct
    FieldsAsStruct fieldsAsStruct();

    /// @brief Get access to @b const fields bundled into a struct
    ConstFieldsAsStruct fieldsAsStruct() const;

#else
    COMMS_MSG_FIELDS_ACCESS(Base, msg1, msg2, msg3, msg4, msg5, msg6, skipped);
#endif // #ifdef FOR_DOXYGEN_DOC_ONLY

    /// @brief Default constructor
    MonMsgpp() = default;

    /// @brief Copy constructor
    MonMsgpp(const MonMsgpp&) = default;

    /// @brief Move constructor
    MonMsgpp(MonMsgpp&& other) = default;

    /// @brief Destructor
    virtual ~MonMsgpp() = default;

    /// @brief Copy assignment
    MonMsgpp& operator=(const MonMsgpp&) = default;

    /// @brief Move assignment
    MonMsgpp& operator=(MonMsgpp&&) = default;
};


}  // namespace message

}  // namespace ublox

