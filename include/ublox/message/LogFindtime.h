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
/// @brief Contains definition of LOG-FINDTIME message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the LOG-FINDTIME message fields.
/// @see LogFindtime
struct LogFindtimeFields
{
    /// @brief Definition of "version" field.
    using version =
        field::common::U1T<
            comms::option::DefaultNumValue<1>,
            comms::option::ValidNumValueRange<1, 1>
        >;

    /// @brief Definition of "type" field.
    using type  =
        field::common::U1T<
            comms::option::DefaultNumValue<1>,
            comms::option::ValidNumValueRange<1, 1>
        >;

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res2;

    /// @brief Definition of "entryNumber" field.
    using entryNumber  = field::common::U4;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        version,
        type,
        reserved1,
        entryNumber
    >;
};

/// @brief Definition of LOG-FINDTIME message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref LogFindtimeFields and for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class LogFindtime : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_LOG_FINDTIME>,
        comms::option::FieldsImpl<LogFindtimeFields::All>,
        comms::option::MsgType<LogFindtime<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_LOG_FINDTIME>,
        comms::option::FieldsImpl<LogFindtimeFields::All>,
        comms::option::MsgType<LogFindtime<TMsgBase> >
    > Base;
public:

#ifdef FOR_DOXYGEN_DOC_ONLY
    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_version, ///< @b version field, see @ref LogFindtimeFields::version
        FieldIdx_type, ///< @b type field, see @ref LogFindtimeFields::type
        FieldIdx_reserved1, ///< @b reserved1 field, see @ref LogFindtimeFields::reserved1
        FieldIdx_entryNumber, ///< @b entryNumber field, see @ref LogFindtimeFields::entryNumber
        FieldIdx_numOfValues ///< number of available fields
    };

    /// @brief Access to fields bundled as a struct
    struct FieldsAsStruct
    {
        LogFindtimeFields::version& version; ///< @b version field, see @ref LogFindtimeFields::version
        LogFindtimeFields::type& type; ///< @b type field, see @ref LogFindtimeFields::type
        LogFindtimeFields::reserved1& reserved1; ///< @b reserved1 field, see @ref LogFindtimeFields::reserved1
        LogFindtimeFields::entryNumber& entryNumber; ///< @b entryNumber field, see @ref LogFindtimeFields::entryNumber
    };

    /// @brief Access to @b const fields bundled as a struct
    struct ConstFieldsAsStruct
    {
        const LogFindtimeFields::version& version; ///< @b version field, see @ref LogFindtimeFields::version
        const LogFindtimeFields::type& type; ///< @b type field, see @ref LogFindtimeFields::type
        const LogFindtimeFields::reserved1& reserved1; ///< @b reserved1 field, see @ref LogFindtimeFields::reserved1
        const LogFindtimeFields::entryNumber& entryNumber; ///< @b entryNumber field, see @ref LogFindtimeFields::entryNumber
    };

    /// @brief Get access to fields bundled into a struct
    FieldsAsStruct fieldsAsStruct();

    /// @brief Get access to @b const fields bundled into a struct
    ConstFieldsAsStruct fieldsAsStruct() const;

#else
    COMMS_MSG_FIELDS_ACCESS(Base, version, type, reserved1, entryNumber);
#endif // #ifdef FOR_DOXYGEN_DOC_ONLY

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

    /// @brief Provides custom read functionality.
    /// @details The function performs read up to the @b type field (@ref
    /// LogFindtimeFields::type) and checks its value. If it's valid (has value 1),
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

