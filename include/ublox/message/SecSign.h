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
/// @brief Contains definition of SEC-SIGN message and its fields.

#pragma once

#include "comms/Message.h"
#include "ublox/Message.h"
#include "ublox/field/MsgId.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the SEC-SIGN message fields.
/// @see SecSign
struct SecSignFields
{
    /// @brief Definition of "version".
    using version =
        field::common::U1T<
            comms::option::ValidNumValueRange<1, 1>,
            comms::option::DefaultNumValue<1>
        >;

    /// @brief Definition of "reserved1".
    using reserved1 = field::common::res3;

    /// @brief Definition of "id" field (combining class ID and message ID).
    using id = ublox::field::MsgId;

    /// @brief Definition of "checksum" field.
    using checksum = field::common::U2;

    /// @brief Definition of "hash" field.
    /// @tparam TOpt Extra options
    template <typename TOpt = comms::option::EmptyOption>
    using hash =
        field::common::ListT<
            std::uint8_t,
            comms::option::SequenceFixedSize<32>,
            TOpt
        >;

    /// @brief All the fields bundled in std::tuple.
    /// @tparam TOpt Extra options for @ref hash field
    template <typename TOpt>
    using All = std::tuple<
        version,
        reserved1,
        id,
        checksum,
        hash<TOpt>
    >;
};

/// @brief Definition of SEC-SIGN message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref SecSignFields for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
/// @tparam THashOpt Extra options for @b hash field.
template <typename TMsgBase = Message, typename THashOpt = comms::option::EmptyOption>
class SecSign : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_SEC_SIGN>,
        comms::option::FieldsImpl<SecSignFields::All<THashOpt> >,
        comms::option::MsgType<SecSign<TMsgBase, THashOpt> >
    >
{
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b version for @ref SecSignFields::version field
    ///     @li @b reserved1 for @ref SecSignFields::reserved1 field
    ///     @li @b id for @ref SecSignFields::id field
    ///     @li @b checksum for @ref SecSignFields::checksum field
    ///     @li @b hash for @ref SecSignFields::hash field
    COMMS_MSG_FIELDS_ACCESS(version, reserved1, id, checksum, hash);

    /// @brief Default constructor
    SecSign() = default;

    /// @brief Copy constructor
    SecSign(const SecSign&) = default;

    /// @brief Move constructor
    SecSign(SecSign&& other) = default;

    /// @brief Destructor
    virtual ~SecSign() = default;

    /// @brief Copy assignment
    SecSign& operator=(const SecSign&) = default;

    /// @brief Move assignment
    SecSign& operator=(SecSign&&) = default;
};


}  // namespace message

}  // namespace ublox

