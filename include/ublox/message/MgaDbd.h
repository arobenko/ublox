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
/// @brief Contains definition of MGA-DBD message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the MGA-DBD message fields.
/// @see MgaDbd
struct MgaDbdFields
{

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res4;

    /// @brief Definition of "reserved2" field.
    using reserved2 = field::common::res4;

    /// @brief Definition of "reserved3" field.
    using reserved3 = field::common::res4;


    /// @brief Definition of "data" field.
    /// @tparam TOpt Extra option(s)
    template <typename TOpt = comms::option::EmptyOption>
    using data =
        field::common::ListT<
            std::uint8_t,
            TOpt
        >;

    /// @brief All the fields bundled in std::tuple.
    /// @tparam TOpt Extra option(s) for @ref data field
    template <typename TOpt>
    using All = std::tuple<
        reserved1,
        reserved2,
        reserved3,
        data<TOpt>
    >;
};

/// @brief Definition of MGA-DBD message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref MgaDbdFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
/// @tparam TDataOpt Extra option(s) for @b data field
template <typename TMsgBase = Message, typename TDataOpt = comms::option::EmptyOption>
class MgaDbd : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_MGA_DBD>,
        comms::option::FieldsImpl<MgaDbdFields::All<TDataOpt> >,
        comms::option::MsgType<MgaDbd<TMsgBase, TDataOpt> >
    >
{
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b reserved1 for @ref MgaDbdFields::reserved1 field
    ///     @li @b reserved2 for @ref MgaDbdFields::reserved2 field
    ///     @li @b reserved3 for @ref MgaDbdFields::reserved3 field
    ///     @li @b data for @ref MgaDbdFields::data field
    COMMS_MSG_FIELDS_ACCESS(
        reserved1,
        reserved2,
        reserved3,
        data
    );

    /// @brief Default constructor
    MgaDbd() = default;

    /// @brief Copy constructor
    MgaDbd(const MgaDbd&) = default;

    /// @brief Move constructor
    MgaDbd(MgaDbd&& other) = default;

    /// @brief Destructor
    ~MgaDbd() = default;

    /// @brief Copy assignment
    MgaDbd& operator=(const MgaDbd&) = default;

    /// @brief Move assignment
    MgaDbd& operator=(MgaDbd&&) = default;

};


}  // namespace message

}  // namespace ublox





