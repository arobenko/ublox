//
// Copyright 2015 (C). Alex Robenko. All rights reserved.
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


#pragma once

#include <iterator>
#include <algorithm>

#include "comms/Message.h"
#include "ublox/Message.h"

#include "CfgPrt.h"

namespace ublox
{

namespace message
{

struct CfgPrtPollPort_PortIdValidator
{
    template <typename TField>
    bool operator()(const TField& field)
    {
        static const CfgPrt_PortId Values[] = {
            CfgPrt_PortId::DDC,
            CfgPrt_PortId::UART,
            CfgPrt_PortId::USB,
            CfgPrt_PortId::SPI
        };

        auto value = field.value();
        auto iter = std::lower_bound(std::begin(Values), std::end(Values), value);
        return ((iter != std::end(Values)) && (*iter == value));
    }
};


using CfgPrtPollPortField_portID =
    field::common::EnumT<
        CfgPrt_PortId,
        comms::option::ContentsValidator<CfgPrtPollPort_PortIdValidator>
    >;


using CfgPrtPollPortFields = std::tuple<
    CfgPrtPollPortField_portID
>;

template <typename TMsgBase = Message>
class CfgPrtPollPort : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_PRT>,
        comms::option::FieldsImpl<CfgPrtPollPortFields>,
        comms::option::DispatchImpl<CfgPrtPollPort<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_PRT>,
        comms::option::FieldsImpl<CfgPrtPollPortFields>,
        comms::option::DispatchImpl<CfgPrtPollPort<TMsgBase> >
    > Base;
public:

    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_portID,
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





