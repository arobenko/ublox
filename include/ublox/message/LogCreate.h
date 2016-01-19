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

#include "comms/Message.h"
#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

enum class LogCreate_LogSize : std::uint8_t
{
    Max,
    Min,
    UserDefined,
    NumOfValues
};

enum
{
    LogCreateField_logCfg_circular,
    LogCreateField_logCfg_numOfValues
};

using LogCreateField_version =
    field::common::U1T<
        comms::option::ValidNumValueRange<0, 0>
    >;
using LogCreateField_logCfg =
    field::common::X1T<
        comms::option::BitmaskReservedBits<0xfe, 0>
    >;
using LogCreateField_reserved = field::common::res1;
using LogCreateField_logSize  =
    field::common::EnumT<
        LogCreate_LogSize,
        comms::option::ValidNumValueRange<0, (int)LogCreate_LogSize::NumOfValues - 1>
    >;
using LogCreateField_userDefinedSize = field::common::U4;

using LogCreateFields = std::tuple<
    LogCreateField_version,
    LogCreateField_logCfg,
    LogCreateField_reserved,
    LogCreateField_logSize,
    LogCreateField_userDefinedSize
>;


template <typename TMsgBase = Message>
class LogCreate : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_LOG_CREATE>,
        comms::option::FieldsImpl<LogCreateFields>,
        comms::option::DispatchImpl<LogCreate<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_LOG_CREATE>,
        comms::option::FieldsImpl<LogCreateFields>,
        comms::option::DispatchImpl<LogCreate<TMsgBase> >
    > Base;
public:

    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_version,
        FieldIdx_logCfg,
        FieldIdx_reserved,
        FieldIdx_logSize,
        FieldIdx_userDefinedSize,
        FieldIdx_numOfValues ///< number of available fields
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    /// @brief Default constructor
    LogCreate() = default;

    /// @brief Copy constructor
    LogCreate(const LogCreate&) = default;

    /// @brief Move constructor
    LogCreate(LogCreate&& other) = default;

    /// @brief Destructor
    virtual ~LogCreate() = default;

    /// @brief Copy assignment
    LogCreate& operator=(const LogCreate&) = default;

    /// @brief Move assignment
    LogCreate& operator=(LogCreate&&) = default;
};


}  // namespace message

}  // namespace ublox

