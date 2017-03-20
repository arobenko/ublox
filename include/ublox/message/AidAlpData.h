//
// Copyright 2015 - 2017 (C). Alex Robenko. All rights reserved.
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
    /// @brief Definition of "alpData" field.
    /// @tparam TOpt Extra option(s)
    template <typename TOpt = comms::option::EmptyOption>
    using alpData = field::common::ListT<field::common::U2, TOpt>;


    /// @brief All the fields bundled in std::tuple.
    /// @tparam TOpt Extra option(s) for @ref alpData field
    template <typename TOpt>
    using All = std::tuple<
        alpData<TOpt>
    >;
};

/// @brief Definition of AID-ALP  (<b>data transfer</b>) message
/// @details
///     This message is sent as an intput to the receiver. @n
///     Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref AidAlpDataFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
/// @tparam TAlpDataOpt Extra option(s) for @b alpData field
template <typename TMsgBase = Message, typename TAlpDataOpt = comms::option::EmptyOption>
class AidAlpData : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_AID_ALP>,
        comms::option::FieldsImpl<AidAlpDataFields::All<TAlpDataOpt> >,
        comms::option::MsgType<AidAlpData<TMsgBase, TAlpDataOpt> >
    >
{
public:
    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b alpData for @ref AidAlpDataFields::alpData field
    COMMS_MSG_FIELDS_ACCESS(alpData);

    /// @brief Default constructor
    AidAlpData() = default;

    /// @brief Copy constructor
    AidAlpData(const AidAlpData&) = default;

    /// @brief Move constructor
    AidAlpData(AidAlpData&& other) = default;

    /// @brief Destructor
    ~AidAlpData() = default;

    /// @brief Copy assignment
    AidAlpData& operator=(const AidAlpData&) = default;

    /// @brief Move assignment
    AidAlpData& operator=(AidAlpData&&) = default;
};


}  // namespace message

}  // namespace ublox





