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
/// @brief Contains definition of SEC-UNIQID message and its fields.

#pragma once

#include "comms/Message.h"
#include "ublox/Message.h"
#include "ublox/field/MsgId.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the SEC-UNIQID message fields.
/// @see SecUniqid
struct SecUniqidFields
{
    /// @brief Definition of "version".
    using version =
        field::common::U1T<
            comms::option::ValidNumValueRange<1, 1>,
            comms::option::DefaultNumValue<1>
        >;

    /// @brief Definition of "reserved1".
    using reserved1 = field::common::res3;

    /// @brief Definition of "uniqueId" field.
    /// @tparam TOpt Extra options
    template <typename TOpt = comms::option::EmptyOption>
    using uniqueId =
        field::common::ListT<
            std::uint8_t,
            comms::option::SequenceFixedSize<5>,
            TOpt
        >;

    /// @brief All the fields bundled in std::tuple.
    /// @tparam TOpt Extra options for @ref uniqueId field
    template <typename TOpt>
    using All = std::tuple<
        version,
        reserved1,
        uniqueId<TOpt>
    >;
};

/// @brief Definition of SEC-UNIQID message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref SecUniqidFields for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
/// @tparam TUniqueIdOpt Extra options for @b uniqueId field.
template <typename TMsgBase = Message, typename TUniqueIdOpt = comms::option::EmptyOption>
class SecUniqid : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_SEC_UNIQID>,
        comms::option::FieldsImpl<SecUniqidFields::All<TUniqueIdOpt> >,
        comms::option::MsgType<SecUniqid<TMsgBase, TUniqueIdOpt> >
    >
{
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b version for @ref SecUniqidFields::version field
    ///     @li @b reserved1 for @ref SecUniqidFields::reserved1 field
    ///     @li @b uniqueId for @ref SecUniqidFields::uniqueId field
    COMMS_MSG_FIELDS_ACCESS(version, reserved1, uniqueId);

    /// @brief Default constructor
    SecUniqid() = default;

    /// @brief Copy constructor
    SecUniqid(const SecUniqid&) = default;

    /// @brief Move constructor
    SecUniqid(SecUniqid&& other) = default;

    /// @brief Destructor
    virtual ~SecUniqid() = default;

    /// @brief Copy assignment
    SecUniqid& operator=(const SecUniqid&) = default;

    /// @brief Move assignment
    SecUniqid& operator=(SecUniqid&&) = default;
};


}  // namespace message

}  // namespace ublox

