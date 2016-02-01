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
/// @brief Contains definition of LOG-FINDTIME (@b command) message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/log.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the LOG-FINDTIME (@b command) message fields.
/// @see LogFindtimeCmd
struct LogFindtimeCmdFields
{
    /// @brief Definition of "version" field.
    using version =
        field::common::U1T<
            comms::option::ValidNumValueRange<0, 0>
        >;

    /// @brief Definition of "type" field.
    using type  =
        field::common::U1T<
            comms::option::ValidNumValueRange<0, 0>
        >;

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res2;

    /// @brief Definition of "year" field.
    using year = field::log::year;

    /// @brief Definition of "month" field.
    using month = field::log::month;

    /// @brief Definition of "day" field.
    using day = field::log::day;

    /// @brief Definition of "hour" field.
    using hour = field::log::hour;

    /// @brief Definition of "minute" field.
    using minute = field::log::minute;

    /// @brief Definition of "second" field.
    using second = field::log::second;

    /// @brief Definition of "reserved2" field.
    using reserved2 = field::common::res1;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        version,
        type,
        reserved1,
        year,
        month,
        day,
        hour,
        minute,
        second,
        reserved2
    >;
};

/// @brief Definition of LOG-FINDTIME (@b command) message
/// @details Inherits from
///     <a href="https://dl.dropboxusercontent.com/u/46999418/comms_champion/comms/html/classcomms_1_1MessageBase.html">comms::MessageBase</a>
///     while providing @b TMsgBase as common interface class as well as
///     @b comms::option::StaticNumIdImpl, @b comms::option::FieldsImpl, and
///     @b comms::option::DispatchImpl as options. @n
///     See @ref LogFindtimeCmdFields and for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class LogFindtimeCmd : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_LOG_FINDTIME>,
        comms::option::FieldsImpl<LogFindtimeCmdFields::All>,
        comms::option::DispatchImpl<LogFindtimeCmd<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_LOG_FINDTIME>,
        comms::option::FieldsImpl<LogFindtimeCmdFields::All>,
        comms::option::DispatchImpl<LogFindtimeCmd<TMsgBase> >
    > Base;
public:

    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_version, ///< @b version field, see @ref LogFindtimeCmdFields::version
        FieldIdx_type, ///< @b type field, see @ref LogFindtimeCmdFields::type
        FieldIdx_reserved1, ///< @b reserved1 field, see @ref LogFindtimeCmdFields::reserved1
        FieldIdx_year, ///< @b year field, see @ref LogFindtimeCmdFields::year
        FieldIdx_month, ///< @b month field, see @ref LogFindtimeCmdFields::month
        FieldIdx_day, ///< @b day field, see @ref LogFindtimeCmdFields::day
        FieldIdx_hour, ///< @b hour field, see @ref LogFindtimeCmdFields::hour
        FieldIdx_minute, ///< @b minute field, see @ref LogFindtimeCmdFields::minute
        FieldIdx_second, ///< @b second field, see @ref LogFindtimeCmdFields::second
        FieldIdx_reserved2, ///< @b reserved2 field, see @ref LogFindtimeCmdFields::reserved2
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
    /// @brief Overrides read functionality provided by the base class.
    /// @details The function performs read up to the @b type field (@ref
    /// LogFindtimeCmdFields::type) and checks its value. If it's valid (has value 0),
    /// the read continues for the rest of the fields. Otherwise
    /// comms::ErrorStatus::InvalidMsgData is returned.
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

