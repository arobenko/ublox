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
/// @brief Contains definition of CFG-DYNSEED message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the CFG-DYNSEED message fields.
/// @see CfgDynseed
struct CfgDynseedFields
{
    /// @brief Definition of "version" field.
    using version =
        field::common::U1T<
            comms::option::ValidNumValueRange<1, 1>,
            comms::option::DefaultNumValue<1>
        >;

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res3;

    /// @brief Definition of "seedHi" field.
    using seedHi = field::common::U4;

    /// @brief Definition of "seedLo" field.
    using seedLo = field::common::U4;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        version,
        reserved1,
        seedHi,
        seedLo
    >;
};

/// @brief Definition of CFG-DYNSEED message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref CfgDynseedFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class CfgDynseed : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_DYNSEED>,
        comms::option::FieldsImpl<CfgDynseedFields::All>,
        comms::option::MsgType<CfgDynseed<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_DYNSEED>,
        comms::option::FieldsImpl<CfgDynseedFields::All>,
        comms::option::MsgType<CfgDynseed<TMsgBase> >
    > Base;
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b version for @ref CfgDynseedFields::version field
    ///     @li @b reserved1 for @ref CfgDynseedFields::reserved1 field
    ///     @li @b seedHi for @ref CfgDynseedFields::seedHi field
    ///     @li @b seedLo for @ref CfgDynseedFields::seedLo field
    COMMS_MSG_FIELDS_ACCESS(version, reserved1, seedHi, seedLo);

    /// @brief Default constructor
    CfgDynseed() = default;

    /// @brief Copy constructor
    CfgDynseed(const CfgDynseed&) = default;

    /// @brief Move constructor
    CfgDynseed(CfgDynseed&& other) = default;

    /// @brief Destructor
    virtual ~CfgDynseed() = default;

    /// @brief Copy assignment
    CfgDynseed& operator=(const CfgDynseed&) = default;

    /// @brief Move assignment
    CfgDynseed& operator=(CfgDynseed&&) = default;
};


}  // namespace message

}  // namespace ublox

