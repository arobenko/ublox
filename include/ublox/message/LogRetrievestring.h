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

using LogRetrievestringField_entryIndex  = field::common::U4;
using LogRetrievestringField_version =
    field::common::U1T<
        comms::option::ValidNumValueRange<0, 0>
    >;
using LogRetrievestringField_reserved1 = field::common::res1;
using LogRetrievestringField_year = field::log::year;
using LogRetrievestringField_month = field::log::month;
using LogRetrievestringField_day = field::log::day;
using LogRetrievestringField_hour = field::log::hour;
using LogRetrievestringField_minute = field::log::minute;
using LogRetrievestringField_second = field::log::second;
using LogRetrievestringField_reserved2 = field::common::res1;
using LogRetrievestringField_byteCount = field::common::U2;
using LogRetrievestringField_bytes =
    comms::field::String<
        field::common::FieldBase,
        comms::option::SequenceSizeForcingEnabled
    >;

using LogRetrievestringFields = std::tuple<
    LogRetrievestringField_entryIndex,
    LogRetrievestringField_version,
    LogRetrievestringField_reserved1,
    LogRetrievestringField_year,
    LogRetrievestringField_month,
    LogRetrievestringField_day,
    LogRetrievestringField_hour,
    LogRetrievestringField_minute,
    LogRetrievestringField_second,
    LogRetrievestringField_reserved2,
    LogRetrievestringField_byteCount,
    LogRetrievestringField_bytes
>;


template <typename TMsgBase = Message>
class LogRetrievestring : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_LOG_RETRIEVESTRING>,
        comms::option::FieldsImpl<LogRetrievestringFields>,
        comms::option::DispatchImpl<LogRetrievestring<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_LOG_RETRIEVESTRING>,
        comms::option::FieldsImpl<LogRetrievestringFields>,
        comms::option::DispatchImpl<LogRetrievestring<TMsgBase> >
    > Base;
public:

    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_entryIndex,
        FieldIdx_version,
        FieldIdx_reserved1,
        FieldIdx_year,
        FieldIdx_month,
        FieldIdx_day,
        FieldIdx_hour,
        FieldIdx_minute,
        FieldIdx_second,
        FieldIdx_reserved2,
        FieldIdx_byteCount,
        FieldIdx_bytes,
        FieldIdx_numOfValues ///< number of available fields
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    /// @brief Default constructor
    LogRetrievestring() = default;

    /// @brief Copy constructor
    LogRetrievestring(const LogRetrievestring&) = default;

    /// @brief Move constructor
    LogRetrievestring(LogRetrievestring&& other) = default;

    /// @brief Destructor
    virtual ~LogRetrievestring() = default;

    /// @brief Copy assignment
    LogRetrievestring& operator=(const LogRetrievestring&) = default;

    /// @brief Move assignment
    LogRetrievestring& operator=(LogRetrievestring&&) = default;

protected:
    virtual comms::ErrorStatus readImpl(
        typename Base::ReadIterator& iter,
        std::size_t len) override
    {
        auto es = Base::template readFieldsUntil<FieldIdx_bytes>(iter, len);
        if (es != comms::ErrorStatus::Success) {
            return es;
        }

        auto& allFields = Base::fields();
        auto& countField = std::get<FieldIdx_byteCount>(allFields);
        auto& bytesField = std::get<FieldIdx_bytes>(allFields);
        bytesField.forceReadElemCount(countField.value());

        return Base::template readFieldsFrom<FieldIdx_bytes>(iter, len);
    }

    virtual bool refreshImpl() override
    {
        auto& allFields = Base::fields();
        auto& countField = std::get<FieldIdx_byteCount>(allFields);
        auto& bytesField = std::get<FieldIdx_bytes>(allFields);
        if (countField.value() == bytesField.value().size()) {
            return false;
        }

        countField.value() = bytesField.value().size();
        return true;
    }

};


}  // namespace message

}  // namespace ublox

