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

using LogFindtimeField_version =
    field::common::U1T<
        comms::option::DefaultNumValue<1>,
        comms::option::ValidNumValueRange<1, 1>
    >;
using LogFindtimeField_type  =
    field::common::U1T<
        comms::option::DefaultNumValue<1>,
        comms::option::ValidNumValueRange<1, 1>
    >;
using LogFindtimeField_reserved1 = field::common::res2;
using LogFindtimeField_entryNumber  = field::common::U4;

using LogFindtimeFields = std::tuple<
    LogFindtimeField_version,
    LogFindtimeField_type,
    LogFindtimeField_reserved1,
    LogFindtimeField_entryNumber
>;


template <typename TMsgBase = Message>
class LogFindtime : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_LOG_FINDTIME>,
        comms::option::FieldsImpl<LogFindtimeFields>,
        comms::option::DispatchImpl<LogFindtime<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_LOG_FINDTIME>,
        comms::option::FieldsImpl<LogFindtimeFields>,
        comms::option::DispatchImpl<LogFindtime<TMsgBase> >
    > Base;
public:

    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_version,
        FieldIdx_type,
        FieldIdx_reserved1,
        FieldIdx_entryNumber,
        FieldIdx_numOfValues ///< number of available fields
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    /// @brief Default constructor
    LogFindtime() = default;

    /// @brief Copy constructor
    LogFindtime(const LogFindtime&) = default;

    /// @brief Move constructor
    LogFindtime(LogFindtime&& other) = default;

    /// @brief Destructor
    virtual ~LogFindtime() = default;

    /// @brief Copy assignment
    LogFindtime& operator=(const LogFindtime&) = default;

    /// @brief Move assignment
    LogFindtime& operator=(LogFindtime&&) = default;

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

