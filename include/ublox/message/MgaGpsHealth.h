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
/// @brief Contains definition of MGA-GPS-HEALTH message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the MGA-GPS-HEALTH message fields.
/// @see MgaGpsHealth
struct MgaGpsHealthFields
{
    /// @brief Definition of "type" field.
    using type  =
    field::common::U1T<
        comms::option::ValidNumValueRange<4, 4>,
        comms::option::DefaultNumValue<4>,
        comms::option::FailOnInvalid
    >;

    /// @brief Definition of "version" field.
    using version =
        field::common::U1T<
            comms::option::ValidNumValueRange<0, 0>
        >;

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res2;

    /// @brief Definition of "healthCode" field.
    /// @tparam TOpt Extra option(s)
    template <typename TOpt = comms::option::EmptyOption>
    using healthCode =
        field::common::ListT<
            std::uint8_t,
            comms::option::SequenceFixedSize<32>,
            TOpt
        >;

    /// @brief Definition of "reserved2" field.
    using reserved2 = field::common::res4;


    /// @brief All the fields bundled in std::tuple.
    /// @tparam TOpt Extra option(s) for @ref healthCode field
    template <typename TOpt>
    using All = std::tuple<
        type,
        version,
        reserved1,
        healthCode<TOpt>,
        reserved2
    >;
};

/// @brief Definition of MGA-GPS-HEALTH message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref MgaGpsHealthFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
/// @tparam THealthCodeOpt Extra option(s) for @b healthCode field
template <typename TMsgBase = Message, typename THealthCodeOpt = comms::option::EmptyOption>
class MgaGpsHealth : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_MGA_GPS>,
        comms::option::FieldsImpl<MgaGpsHealthFields::All<THealthCodeOpt> >,
        comms::option::MsgType<MgaGpsHealth<TMsgBase, THealthCodeOpt> >
    >
{
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b type for @ref MgaGpsHealthFields::type field
    ///     @li @b version for @ref MgaGpsHealthFields::version field
    ///     @li @b reserved1 for @ref MgaGpsHealthFields::reserved1 field
    ///     @li @b healthCode for @ref MgaGpsHealthFields::healthCode field
    ///     @li @b reserved2 for @ref MgaGpsHealthFields::reserved2 field
    COMMS_MSG_FIELDS_ACCESS(
        type,
        version,
        reserved1,
        healthCode,
        reserved2
    );

    /// @brief Default constructor
    MgaGpsHealth() = default;

    /// @brief Copy constructor
    MgaGpsHealth(const MgaGpsHealth&) = default;

    /// @brief Move constructor
    MgaGpsHealth(MgaGpsHealth&& other) = default;

    /// @brief Destructor
    virtual ~MgaGpsHealth() = default;

    /// @brief Copy assignment
    MgaGpsHealth& operator=(const MgaGpsHealth&) = default;

    /// @brief Move assignment
    MgaGpsHealth& operator=(MgaGpsHealth&&) = default;
};

}  // namespace message

}  // namespace ublox

