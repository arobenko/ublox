//
// Copyright 2015 - 2017 (C). Alex Robenko. All rights reserved.
//

// This file is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRGEOFENCEY; without even the implied warranty of
// MERCHGEOFENCEABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

/// @file
/// @brief Contains definition of CFG-GEOFENCE (@b poll) message and its fields.

#pragma once

#include "ublox/Message.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the CFG-GEOFENCE (@b poll) message fields.
/// @see CfgGeofencePoll
struct CfgGeofencePollFields
{
    using All = std::tuple<>;
};

/// @brief Definition of CFG-GEOFENCE (@b poll) message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref CfgGeofencePollFields and for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class CfgGeofencePoll : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_GEOFENCE>,
        comms::option::FieldsImpl<CfgGeofencePollFields::All>,
        comms::option::MsgType<CfgGeofencePoll<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_GEOFENCE>,
        comms::option::FieldsImpl<CfgGeofencePollFields::All>,
        comms::option::MsgType<CfgGeofencePoll<TMsgBase> >
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
    CfgGeofencePoll() = default;

    /// @brief Copy constructor
    CfgGeofencePoll(const CfgGeofencePoll&) = default;

    /// @brief Move constructor
    CfgGeofencePoll(CfgGeofencePoll&& other) = default;

    /// @brief Destructor
    virtual ~CfgGeofencePoll() = default;

    /// @brief Copy assignment
    CfgGeofencePoll& operator=(const CfgGeofencePoll&) = default;

    /// @brief Move assignment
    CfgGeofencePoll& operator=(CfgGeofencePoll&&) = default;
};


}  // namespace message

}  // namespace ublox

