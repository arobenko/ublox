//
// Copyright 2015 - 2017 (C). Alex Robenko. All rights reserved.
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
/// @brief Contains definition of ESF-RAW message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the ESF-RAW message fields.
/// @see EsfRaw
struct EsfRawFields
{
    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res4;

    /// @brief Definition of "dataField" field.
    using dataField = field::common::U3;

    /// @brief Definition of "dataType" field.
    using dataType = field::common::U1;

    /// @brief Definition of "sTtag" field.
    using sTtag = field::common::U4;

    /// @brief Definition of single block element for @ref list field.
    struct block : public
        field::common::BundleT<
            std::tuple<
                dataField,
                dataType,
                sTtag
            >
        >
    {
        /// @brief Allow access to internal fields.
        /// @details See definition of @b COMMS_FIELD_MEMBERS_ACCESS macro
        ///     related to @b comms::field::Bitfield class from COMMS library
        ///     for details.
        ///
        ///     The field names are:
        ///     @li @b dataField for @ref EsfRawFields::dataField field
        ///     @li @b dataType for @ref EsfRawFields::dataType field
        ///     @li @b sTtag for @ref EsfRawFields::sTtag field
        COMMS_FIELD_MEMBERS_ACCESS(dataField, dataType, sTtag);
    };

    /// @brief Definition of "list" field as list of elements (@ref block).
    /// @tparam TOpt Extra option(s)
    template <typename TOpt = comms::option::EmptyOption>
    using list =
        field::common::ListT<
            block,
            TOpt
        >;

    /// @brief All the fields bundled in std::tuple.
    /// @tparam TOpt Extra option(s) for @ref list field
    template <typename TOpt>
    using All = std::tuple<
        reserved1,
        list<TOpt>
    >;
};

/// @brief Definition of ESF-RAW message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref EsfRawFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
/// @tparam TListOpt Extra option(s) for @b list field
template <typename TMsgBase = Message, typename TListOpt = comms::option::EmptyOption>
class EsfRaw : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_ESF_RAW>,
        comms::option::FieldsImpl<EsfRawFields::All<TListOpt> >,
        comms::option::MsgType<EsfRaw<TMsgBase, TListOpt> >
    >
{

public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b reserved1 for @ref EsfRawFields::reserved1 field
    ///     @li @b list for @ref EsfRawFields::list field
    COMMS_MSG_FIELDS_ACCESS(reserved1, list);

    /// @brief Default constructor
    EsfRaw() = default;

    /// @brief Copy constructor
    EsfRaw(const EsfRaw&) = default;

    /// @brief Move constructor
    EsfRaw(EsfRaw&& other) = default;

    /// @brief Destructor
    ~EsfRaw() = default;

    /// @brief Copy assignment
    EsfRaw& operator=(const EsfRaw&) = default;

    /// @brief Move assignment
    EsfRaw& operator=(EsfRaw&&) = default;
};

}  // namespace message

}  // namespace ublox





