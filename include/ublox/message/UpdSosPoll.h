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
/// @brief Contains definition of UPD-SOS (@b poll) message and its fields.

#pragma once

#include "ublox/Message.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the UPD-SOS (@b poll) message fields.
/// @see UpdSosPoll
struct UpdSosPollFields
{
    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<>;
};

/// @brief Definition of UPD-SOS (@b poll) message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref UpdSosPollFields and for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class UpdSosPoll : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_UPD_SOS>,
        comms::option::FieldsImpl<UpdSosPollFields::All>,
        comms::option::MsgType<UpdSosPoll<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_UPD_SOS>,
        comms::option::FieldsImpl<UpdSosPollFields::All>,
        comms::option::MsgType<UpdSosPoll<TMsgBase> >
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
    UpdSosPoll() = default;

    /// @brief Copy constructor
    UpdSosPoll(const UpdSosPoll&) = default;

    /// @brief Move constructor
    UpdSosPoll(UpdSosPoll&& other) = default;

    /// @brief Destructor
    ~UpdSosPoll() = default;

    /// @brief Copy assignment
    UpdSosPoll& operator=(const UpdSosPoll&) = default;

    /// @brief Move assignment
    UpdSosPoll& operator=(UpdSosPoll&&) = default;
};


}  // namespace message

}  // namespace ublox

