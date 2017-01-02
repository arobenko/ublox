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
/// @brief Contains definition of CFG-ITFM (@b poll) message and its fields.

#pragma once

#include "ublox/Message.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the CFG-ITFM (@b poll) message fields.
/// @see CfgItfmPoll
struct CfgItfmPollFields
{
    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<>;
};

/// @brief Definition of CFG-ITFM (@b poll) message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref CfgItfmPollFields and for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class CfgItfmPoll : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_ITFM>,
        comms::option::FieldsImpl<CfgItfmPollFields::All>,
        comms::option::MsgType<CfgItfmPoll<TMsgBase> >,
        comms::option::DispatchImpl
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_ITFM>,
        comms::option::FieldsImpl<CfgItfmPollFields::All>,
        comms::option::MsgType<CfgItfmPoll<TMsgBase> >,
        comms::option::DispatchImpl
    > Base;
public:

    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_numOfValues ///< number of available fields
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    /// @brief Default constructor
    CfgItfmPoll() = default;

    /// @brief Copy constructor
    CfgItfmPoll(const CfgItfmPoll&) = default;

    /// @brief Move constructor
    CfgItfmPoll(CfgItfmPoll&& other) = default;

    /// @brief Destructor
    virtual ~CfgItfmPoll() = default;

    /// @brief Copy assignment
    CfgItfmPoll& operator=(const CfgItfmPoll&) = default;

    /// @brief Move assignment
    CfgItfmPoll& operator=(CfgItfmPoll&&) = default;
};


}  // namespace message

}  // namespace ublox

