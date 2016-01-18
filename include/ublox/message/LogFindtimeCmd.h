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
#include "ublox/field/log.h"

namespace ublox
{

namespace message
{

using LogFindtimeCmdField_version =
    field::common::U1T<
        comms::option::ValidNumValueRange<0, 0>
    >;
using LogFindtimeCmdField_type  =
    field::common::U1T<
        comms::option::ValidNumValueRange<0, 0>
    >;
using LogFindtimeCmdField_reserved1 = field::common::res2;
using LogFindtimeCmdField_year = field::log::year;
using LogFindtimeCmdField_month = field::log::month;
using LogFindtimeCmdField_day = field::log::day;
using LogFindtimeCmdField_hour = field::log::hour;
using LogFindtimeCmdField_minute = field::log::minute;
using LogFindtimeCmdField_second = field::log::second;
using LogFindtimeCmdField_reserved2 = field::common::res1;

using LogFindtimeCmdFields = std::tuple<
    LogFindtimeCmdField_version,
    LogFindtimeCmdField_type,
    LogFindtimeCmdField_reserved1,
    LogFindtimeCmdField_year,
    LogFindtimeCmdField_month,
    LogFindtimeCmdField_day,
    LogFindtimeCmdField_hour,
    LogFindtimeCmdField_minute,
    LogFindtimeCmdField_second,
    LogFindtimeCmdField_reserved2
>;


template <typename TMsgBase = Message>
class LogFindtimeCmd : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_LOG_FINDTIME>,
        comms::option::FieldsImpl<LogFindtimeCmdFields>,
        comms::option::DispatchImpl<LogFindtimeCmd<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_LOG_FINDTIME>,
        comms::option::FieldsImpl<LogFindtimeCmdFields>,
        comms::option::DispatchImpl<LogFindtimeCmd<TMsgBase> >
    > Base;
public:

    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_version,
        FieldIdx_type,
        FieldIdx_reserved1,
        FieldIdx_year,
        FieldIdx_month,
        FieldIdx_day,
        FieldIdx_hour,
        FieldIdx_minute,
        FieldIdx_second,
        FieldIdx_reserved2,
        FieldIdx_numOfValues ///< number of available fields
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    /// @brief Default constructor
    LogFindtimeCmd() = default;

    /// @brief Copy constructor
    LogFindtimeCmd(const LogFindtimeCmd&) = default;

    /// @brief Move constructor
    LogFindtimeCmd(LogFindtimeCmd&& other) = default;

    /// @brief Destructor
    virtual ~LogFindtimeCmd() = default;

    /// @brief Copy assignment
    LogFindtimeCmd& operator=(const LogFindtimeCmd&) = default;

    /// @brief Move assignment
    LogFindtimeCmd& operator=(LogFindtimeCmd&&) = default;

protected:
    virtual comms::ErrorStatus readImpl(
        typename Base::ReadIterator& iter,
        std::size_t len) override
    {
        auto es = Base::template readFieldsUntil<FieldIdx_reserved1>(iter, len);
        if (es != comms::ErrorStatus::Success) {
            return es;
        }

        auto& allFields = Base::fields();
        auto& typeField = std::get<FieldIdx_type>(allFields);
        if (!typeField.valid()) {
            return comms::ErrorStatus::InvalidMsgData;
        }

        return Base::template readFieldsFrom<FieldIdx_reserved1>(iter, len);
    }
};


}  // namespace message

}  // namespace ublox

