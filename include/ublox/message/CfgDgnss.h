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
/// @brief Contains definition of CFG-DGNSS message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the CFG-DGNSS message fields.
/// @see CfgDgnss
struct CfgDgnssFields
{
    /// @brief Value enumeration for @ref dgnssMode field.
    enum class DgnssMode : std::uint8_t
    {
        RtkFloat, ///< No attempts are made to fix ambiguities.
        RtkFixed, ///< Ambiguities are fixed whenever possible.
        NumOfValues /// number of available values
    };

    /// @brief Definition of "dgnssMode" field.
    using dgnssMode =
        field::common::EnumT<
            DgnssMode,
            comms::option::ValidNumValueRange<0, (int)DgnssMode::NumOfValues - 1>
        >;

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res3;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        dgnssMode,
        reserved1
    >;
};

/// @brief Definition of CFG-DGNSS message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref CfgDgnssFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
/// @tparam TDataOpt Extra option(s) for @b data field
template <typename TMsgBase = Message>
class CfgDgnss : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_DGNSS>,
        comms::option::FieldsImpl<CfgDgnssFields::All>,
        comms::option::MsgType<CfgDgnss<TMsgBase> >
    >
{
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b dgnssMode for @ref CfgDgnssFields::dgnssMode field
    ///     @li @b reserved1 for @ref CfgDgnssFields::reserved1 field
    COMMS_MSG_FIELDS_ACCESS(dgnssMode, reserved1);

    /// @brief Default constructor
    CfgDgnss() = default;

    /// @brief Copy constructor
    CfgDgnss(const CfgDgnss&) = default;

    /// @brief Move constructor
    CfgDgnss(CfgDgnss&& other) = default;

    /// @brief Destructor
    ~CfgDgnss() = default;

    /// @brief Copy assignment
    CfgDgnss& operator=(const CfgDgnss&) = default;

    /// @brief Move assignment
    CfgDgnss& operator=(CfgDgnss&&) = default;
};


}  // namespace message

}  // namespace ublox





