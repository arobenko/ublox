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
/// @brief Contains definition of MGA-FLASH-STOP message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the MGA-FLASH-STOP message fields.
/// @see MgaFlashStop
struct MgaFlashStopFields
{

    /// @brief Definition of "type" field.
    using type  =
    field::common::U1T<
        comms::option::ValidNumValueRange<2, 2>,
        comms::option::DefaultNumValue<2>,
        comms::option::FailOnInvalid
    >;

    /// @brief Definition of "version" field.
    using version =
        field::common::U1T<
            comms::option::ValidNumValueRange<0, 0>
        >;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        type,
        version
    >;
};

/// @brief Definition of MGA-FLASH-STOP message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref MgaFlashStopFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class MgaFlashStop : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_MGA_FLASH>,
        comms::option::FieldsImpl<MgaFlashStopFields::All>,
        comms::option::MsgType<MgaFlashStop<TMsgBase> >
    >
{
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b type for @ref MgaFlashStopFields::type field
    ///     @li @b version for @ref MgaFlashStopFields::version field
    COMMS_MSG_FIELDS_ACCESS(
        type,
        version
    );

    /// @brief Default constructor
    MgaFlashStop() = default;

    /// @brief Copy constructor
    MgaFlashStop(const MgaFlashStop&) = default;

    /// @brief Move constructor
    MgaFlashStop(MgaFlashStop&& other) = default;

    /// @brief Destructor
    ~MgaFlashStop() = default;

    /// @brief Copy assignment
    MgaFlashStop& operator=(const MgaFlashStop&) = default;

    /// @brief Move assignment
    MgaFlashStop& operator=(MgaFlashStop&&) = default;
};


}  // namespace message

}  // namespace ublox





