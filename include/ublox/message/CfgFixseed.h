//
// Copyright 2017 (C). Alex Robenko. All rights reserved.
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
/// @brief Contains definition of CFG-FIXSEED message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"
#include "ublox/field/MsgId.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the CFG-FIXSEED message fields.
/// @see CfgFixseed
struct CfgFixseedFields
{
    /// @brief Definition of "version" field.
    using version =
        field::common::U1T<
            comms::option::ValidNumValueRange<2, 2>,
            comms::option::DefaultNumValue<2>
        >;

    /// @brief Definition of "length" field.
    using length = field::common::U1T<comms::option::ValidNumValueRange<1, 10> >;

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res2;

    /// @brief Definition of "seedHi" field.
    using seedHi = field::common::U4;

    /// @brief Definition of "seedLo" field.
    using seedLo = field::common::U4;

    /// @brief Definition of "list" field as list of blocks message IDs.
    /// @tparam TOpt Extra option(s)
    template <typename TOpt = comms::option::EmptyOption>
    using list =
        field::common::ListT<
            field::MsgId,
            comms::option::SequenceSizeForcingEnabled,
            TOpt
        >;

    /// @brief All the fields bundled in std::tuple.
    /// @tparam TOpt Extra option(s) for @ref list field
    template <typename TOpt>
    using All = std::tuple<
        version,
        length,
        reserved1,
        seedHi,
        seedLo,
        list<TOpt>
    >;
};

/// @brief Definition of CFG-FIXSEED message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref CfgFixseedFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
/// @tparam TDataOpt Extra option(s) for @b list field
template <typename TMsgBase = Message, typename TDataOpt = comms::option::EmptyOption>
class CfgFixseed : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_FIXSEED>,
        comms::option::FieldsImpl<CfgFixseedFields::All<TDataOpt> >,
        comms::option::MsgType<CfgFixseed<TMsgBase, TDataOpt> >,
        comms::option::HasDoRefresh
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_FIXSEED>,
        comms::option::FieldsImpl<CfgFixseedFields::All<TDataOpt> >,
        comms::option::MsgType<CfgFixseed<TMsgBase, TDataOpt> >,
        comms::option::HasDoRefresh
    > Base;
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b version for @ref CfgFixseedFields::version field
    ///     @li @b length for @ref CfgFixseedFields::length field
    ///     @li @b reserved1 for @ref CfgFixseedFields::reserved1 field
    ///     @li @b seedHi for @ref CfgFixseedFields::seedHi field
    ///     @li @b seedLo for @ref CfgFixseedFields::seedLo field
    ///     @li @b list for @ref CfgFixseedFields::list field
    COMMS_MSG_FIELDS_ACCESS(version, length, reserved1, seedHi, seedLo, list);

    /// @brief Default constructor
    CfgFixseed() = default;

    /// @brief Copy constructor
    CfgFixseed(const CfgFixseed&) = default;

    /// @brief Move constructor
    CfgFixseed(CfgFixseed&& other) = default;

    /// @brief Destructor
    ~CfgFixseed() = default;

    /// @brief Copy assignment
    CfgFixseed& operator=(const CfgFixseed&) = default;

    /// @brief Move assignment
    CfgFixseed& operator=(CfgFixseed&&) = default;

    /// @brief Provides custom read functionality.
    /// @details The number of blocks in @b list (@ref CfgFixseedFields::list)
    ///     list is determined by the value of @b length (@ref CfgFixseedFields::length)
    ///     field.
    template <typename TIter>
    comms::ErrorStatus doRead(TIter& iter, std::size_t len)
    {
        auto es = Base::template readFieldsUntil<FieldIdx_list>(iter, len);
        if (es != comms::ErrorStatus::Success) {
            return es;
        }

        field_list().forceReadElemCount(field_length().value());
        return Base::template readFieldsFrom<FieldIdx_list>(iter, len);
    }

    /// @brief Provides custom refresh functionality
    /// @details The value of @b length (@ref CfgFixseedFields::length) field is
    ///     determined by number of blocks stored in @b list (@ref CfgFixseedFields::list)
    ///     list.
    /// @return @b true in case the value of "length" field was modified, @b false otherwise
    bool doRefresh()
    {
        if (field_length().value() == field_list().value().size()) {
            return false;
        }

        field_length().value() = field_list().value().size();
        return true;
    }

};


}  // namespace message

}  // namespace ublox





