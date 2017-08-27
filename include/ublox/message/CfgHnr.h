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
/// @brief Contains definition of CFG-HNR message and its fields.

#pragma once

#include <algorithm>

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the CFG-HNR message fields.
/// @see CfgHnr
struct CfgHnrFields
{
    /// @brief Definition of "highNavRate" field.
    using highNavRate =
        field::common::U1T<
            comms::option::UnitsHertz
        >;

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res3;


    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        highNavRate,
        reserved1
    >;

};

/// @brief Definition of CFG-HNR message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref CfgHnrFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
/// @tparam TBlocksListOpt Extra option(s) for @b blocksList field
template <typename TMsgBase = Message>
class CfgHnr : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_HNR>,
        comms::option::FieldsImpl<CfgHnrFields::All>,
        comms::option::MsgType<CfgHnr<TMsgBase> >
    >
{

public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b highNavRate for @ref CfgHnrFields::highNavRate field
    ///     @li @b reserved1 for @ref CfgHnrFields::reserved1 field
    COMMS_MSG_FIELDS_ACCESS(highNavRate, reserved1);

    /// @brief Default constructor
    CfgHnr() = default;

    /// @brief Copy constructor
    CfgHnr(const CfgHnr&) = default;

    /// @brief Move constructor
    CfgHnr(CfgHnr&& other) = default;

    /// @brief Destructor
    ~CfgHnr() = default;

    /// @brief Copy assignment
    CfgHnr& operator=(const CfgHnr&) = default;

    /// @brief Move assignment
    CfgHnr& operator=(CfgHnr&&) = default;
};


}  // namespace message

}  // namespace ublox

