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
/// @brief Contains definition of CFG-PRT (<b>poll port</b>) message and its fields.

#pragma once

#include "ublox/Message.h"
#include "CfgPrt.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the CFG-PRT (<b>poll port</b>) message fields.
/// @see CfgPrtPollPort
struct CfgPrtPollPortFields : public CfgPrtFields
{
    /// @brief Definition of "portID" field.
    using portID =
        field::common::EnumT<
            PortId,
            comms::option::ValidNumValueRange<(int)PortId::DDC, (int)PortId::SPI>
        >;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        portID
    >;
};

/// @brief Definition of CFG-PRT (<b>poll port</b>) message
/// @details Inherits from
///     <a href="https://dl.dropboxusercontent.com/u/46999418/comms_champion/comms/html/classcomms_1_1MessageBase.html">comms::MessageBase</a>
///     while providing @b TMsgBase as common interface class as well as
///     @b comms::option::StaticNumIdImpl, @b comms::option::FieldsImpl, and
///     @b comms::option::DispatchImpl as options. @n
///     See @ref CfgPrtPollPortFields and for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class CfgPrtPollPort : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_PRT>,
        comms::option::FieldsImpl<CfgPrtPollPortFields::All>,
        comms::option::DispatchImpl<CfgPrtPollPort<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_PRT>,
        comms::option::FieldsImpl<CfgPrtPollPortFields::All>,
        comms::option::DispatchImpl<CfgPrtPollPort<TMsgBase> >
    > Base;
public:

    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_portID, ///< @b portID field, see @ref CfgPrtPollPortFields::portID
        FieldIdx_numOfValues ///< number of available fields
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    /// @brief Default constructor
    CfgPrtPollPort() = default;

    /// @brief Copy constructor
    CfgPrtPollPort(const CfgPrtPollPort&) = default;

    /// @brief Move constructor
    CfgPrtPollPort(CfgPrtPollPort&& other) = default;

    /// @brief Destructor
    virtual ~CfgPrtPollPort() = default;

    /// @brief Copy assignment
    CfgPrtPollPort& operator=(const CfgPrtPollPort&) = default;

    /// @brief Move assignment
    CfgPrtPollPort& operator=(CfgPrtPollPort&&) = default;

};


}  // namespace message

}  // namespace ublox





