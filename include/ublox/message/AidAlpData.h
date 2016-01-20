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
/// @brief Contains definition of AID-ALP (<b>data transfer</b>) message
///     and its fields.

#pragma once

#include "comms/Message.h"
#include "ublox/Message.h"

#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the AID-ALP (<b>data transfer</b>)
///     message fields.
/// @see AidAlpData
struct AidAlpDataFields
{
    /// @brief Definition of "status" field.
    using alpData = field::common::ListT<field::common::U2>;


    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        alpData
    >;
};

/// @brief Definition of AID-ALP  (<b>data transfer</b>) message
/// @details
///     This message is sent as an intput to the receiver. @n
///     Inherits from
///     <a href="https://dl.dropboxusercontent.com/u/46999418/comms_champion/comms/html/classcomms_1_1MessageBase.html">comms::MessageBase</a>
///     while providing @b TMsgBase as common interface class as well as
///     @b comms::option::StaticNumIdImpl, @b comms::option::FieldsImpl, and
///     @b comms::option::DispatchImpl as options. @n
///     See @ref AidAlpDataFields and for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class AidAlpData : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_AID_ALP>,
        comms::option::FieldsImpl<AidAlpDataFields::All>,
        comms::option::DispatchImpl<AidAlpData<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_AID_ALP>,
        comms::option::FieldsImpl<AidAlpDataFields::All>,
        comms::option::DispatchImpl<AidAlpData<TMsgBase> >
    > Base;
public:

    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_alpData, ///< alpData field, see @ref AidAlpDataFields::alpData
        FieldIdx_numOfValues ///< number of available fields
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    /// @brief Default constructor
    AidAlpData() = default;

    /// @brief Copy constructor
    AidAlpData(const AidAlpData&) = default;

    /// @brief Move constructor
    AidAlpData(AidAlpData&& other) = default;

    /// @brief Destructor
    virtual ~AidAlpData() = default;

    /// @brief Copy assignment
    AidAlpData& operator=(const AidAlpData&) = default;

    /// @brief Move assignment
    AidAlpData& operator=(AidAlpData&&) = default;
};


}  // namespace message

}  // namespace ublox





