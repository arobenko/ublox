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
///     See @ref MonMsgppFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class MonMsgpp : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_MON_MSGPP>,
        comms::option::FieldsImpl<MonMsgppFields::All>,
        comms::option::MsgType<MonMsgpp<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_MON_MSGPP>,
        comms::option::FieldsImpl<MonMsgppFields::All>,
        comms::option::MsgType<MonMsgpp<TMsgBase> >
    > Base;
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b msg1 for @ref MonMsgppFields::msg1 field
    ///     @li @b msg2 for @ref MonMsgppFields::msg2 field
    ///     @li @b msg3 for @ref MonMsgppFields::msg3 field
    ///     @li @b msg4 for @ref MonMsgppFields::msg4 field
    ///     @li @b msg5 for @ref MonMsgppFields::msg5 field
    ///     @li @b msg6 for @ref MonMsgppFields::msg6 field
    ///     @li @b skipped for @ref MonMsgppFields::skipped field
    COMMS_MSG_FIELDS_ACCESS(Base, msg1, msg2, msg3, msg4, msg5, msg6, skipped);

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

