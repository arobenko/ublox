//
// Copyright 2015 - 2017 (C). Alex Robenko. All rights reserved.
//

// This file is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRPMSY; without even the implied warranty of
// MERCHPMSABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

/// @file
/// @brief Contains definition of CFG-PMS (@b poll) message and its fields.

#pragma once

#include "ublox/Message.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the CFG-PMS (@b poll) message fields.
/// @see CfgPmsPoll
struct CfgPmsPollFields
{
    using All = std::tuple<>;
};

/// @brief Definition of CFG-PMS (@b poll) message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref CfgPmsPollFields and for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class CfgPmsPoll : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_PMS>,
        comms::option::FieldsImpl<CfgPmsPollFields::All>,
        comms::option::MsgType<CfgPmsPoll<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_PMS>,
        comms::option::FieldsImpl<CfgPmsPollFields::All>,
        comms::option::MsgType<CfgPmsPoll<TMsgBase> >
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
    CfgPmsPoll() = default;

    /// @brief Copy constructor
    CfgPmsPoll(const CfgPmsPoll&) = default;

    /// @brief Move constructor
    CfgPmsPoll(CfgPmsPoll&& other) = default;

    /// @brief Destructor
    virtual ~CfgPmsPoll() = default;

    /// @brief Copy assignment
    CfgPmsPoll& operator=(const CfgPmsPoll&) = default;

    /// @brief Move assignment
    CfgPmsPoll& operator=(CfgPmsPoll&&) = default;
};


}  // namespace message

}  // namespace ublox

