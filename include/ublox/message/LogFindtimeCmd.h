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
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref LogFindtimeCmdFields and for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class LogFindtimeCmd : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_LOG_FINDTIME>,
        comms::option::FieldsImpl<LogFindtimeCmdFields::All>,
        comms::option::MsgType<LogFindtimeCmd<TMsgBase> >,
        comms::option::DispatchImpl,
        comms::option::MsgDoRead
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_LOG_FINDTIME>,
        comms::option::FieldsImpl<LogFindtimeCmdFields::All>,
        comms::option::MsgType<LogFindtimeCmd<TMsgBase> >,
        comms::option::DispatchImpl,
        comms::option::MsgDoRead
    > Base;
public:

#ifdef FOR_DOXYGEN_DOC_ONLY
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

    /// @brief Access to fields bundled as a struct
    struct FieldsAsStruct
    {
        LogFindtimeCmdFields::version& version; ///< @b version field, see @ref LogFindtimeCmdFields::version
        LogFindtimeCmdFields::type& type; ///< @b type field, see @ref LogFindtimeCmdFields::type
        LogFindtimeCmdFields::reserved1& reserved1; ///< @b reserved1 field, see @ref LogFindtimeCmdFields::reserved1
        LogFindtimeCmdFields::year& year; ///< @b year field, see @ref LogFindtimeCmdFields::year
        LogFindtimeCmdFields::month& month; ///< @b month field, see @ref LogFindtimeCmdFields::month
        LogFindtimeCmdFields::day& day; ///< @b day field, see @ref LogFindtimeCmdFields::day
        LogFindtimeCmdFields::hour& hour; ///< @b hour field, see @ref LogFindtimeCmdFields::hour
        LogFindtimeCmdFields::minute& minute; ///< @b minute field, see @ref LogFindtimeCmdFields::minute
        LogFindtimeCmdFields::second& second; ///< @b second field, see @ref LogFindtimeCmdFields::second
        LogFindtimeCmdFields::reserved2& reserved2; ///< @b reserved2 field, see @ref LogFindtimeCmdFields::reserved2
    };

    /// @brief Access to @b const fields bundled as a struct
    struct ConstFieldsAsStruct
    {
        const LogFindtimeCmdFields::version& version; ///< @b version field, see @ref LogFindtimeCmdFields::version
        const LogFindtimeCmdFields::type& type; ///< @b type field, see @ref LogFindtimeCmdFields::type
        const LogFindtimeCmdFields::reserved1& reserved1; ///< @b reserved1 field, see @ref LogFindtimeCmdFields::reserved1
        const LogFindtimeCmdFields::year& year; ///< @b year field, see @ref LogFindtimeCmdFields::year
        const LogFindtimeCmdFields::month& month; ///< @b month field, see @ref LogFindtimeCmdFields::month
        const LogFindtimeCmdFields::day& day; ///< @b day field, see @ref LogFindtimeCmdFields::day
        const LogFindtimeCmdFields::hour& hour; ///< @b hour field, see @ref LogFindtimeCmdFields::hour
        const LogFindtimeCmdFields::minute& minute; ///< @b minute field, see @ref LogFindtimeCmdFields::minute
        const LogFindtimeCmdFields::second& second; ///< @b second field, see @ref LogFindtimeCmdFields::second
        const LogFindtimeCmdFields::reserved2& reserved2; ///< @b reserved2 field, see @ref LogFindtimeCmdFields::reserved2
    };

    /// @brief Get access to fields bundled into a struct
    FieldsAsStruct fieldsAsStruct();

    /// @brief Get access to @b const fields bundled into a struct
    ConstFieldsAsStruct fieldsAsStruct() const;

#else
    COMMS_MSG_FIELDS_ACCESS(Base,
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
    );
#endif // #ifdef FOR_DOXYGEN_DOC_ONLY

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

    /// @brief Provides custom read functionality.
    /// @details The function performs read up to the @b type field (@ref
    /// LogFindtimeCmdFields::type) and checks its value. If it's valid (has value 0),
    /// the read continues for the rest of the fields. Otherwise
    /// comms::ErrorStatus::InvalidMsgData is returned.
    template <typename TIter>
    comms::ErrorStatus doRead(TIter& iter, std::size_t len)
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

