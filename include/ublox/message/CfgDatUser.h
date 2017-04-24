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
/// @brief Contains definition of CFG-DAT (<b>user input</b>) message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/cfg.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the CFG-DAT (<b>user input</b>) message fields.
/// @see CfgDatUser
struct CfgDatUserFields
{
    /// @brief Definition of "majA" field.
    using majA = field::cfg::datMajA;

    /// @brief Definition of "flat" field.
    using flat = field::cfg::datFlat;

    /// @brief Definition of "dX" field.
    using dX = field::cfg::datDX;

    /// @brief Definition of "dY" field.
    using dY = field::cfg::datDY;

    /// @brief Definition of "dZ" field.
    using dZ = field::cfg::datDZ;

    /// @brief Definition of "rotX" field.
    using rotX = field::cfg::datRotX;

    /// @brief Definition of "rotY" field.
    using rotY = field::cfg::datRotY;

    /// @brief Definition of "rotZ" field.
    using rotZ = field::cfg::datRotZ;

    /// @brief Definition of "scale" field.
    using scale = field::cfg::datScale;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        majA,
        flat,
        dX,
        dY,
        dZ,
        rotX,
        rotY,
        rotZ,
        scale
    >;
};

/// @brief Definition of CFG-DAT (<b>user input</b>) message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref CfgDatUserFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class CfgDatUser : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_DAT>,
        comms::option::FieldsImpl<CfgDatUserFields::All>,
        comms::option::MsgType<CfgDatUser<TMsgBase> >
    >
{
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b majA for @ref CfgDatUserFields::majA field
    ///     @li @b flat for @ref CfgDatUserFields::flat field
    ///     @li @b dX for @ref CfgDatUserFields::dX field
    ///     @li @b dY for @ref CfgDatUserFields::dY field
    ///     @li @b dZ for @ref CfgDatUserFields::dZ field
    ///     @li @b rotX for @ref CfgDatUserFields::rotX field
    ///     @li @b rotY for @ref CfgDatUserFields::rotY field
    ///     @li @b rotZ for @ref CfgDatUserFields::rotZ field
    ///     @li @b scale for @ref CfgDatUserFields::scale field
    COMMS_MSG_FIELDS_ACCESS(
        majA,
        flat,
        dX,
        dY,
        dZ,
        rotX,
        rotY,
        rotZ,
        scale
    );

    /// @brief Default constructor
    CfgDatUser() = default;

    /// @brief Copy constructor
    CfgDatUser(const CfgDatUser&) = default;

    /// @brief Move constructor
    CfgDatUser(CfgDatUser&& other) = default;

    /// @brief Destructor
    ~CfgDatUser() = default;

    /// @brief Copy assignment
    CfgDatUser& operator=(const CfgDatUser&) = default;

    /// @brief Move assignment
    CfgDatUser& operator=(CfgDatUser&&) = default;
};


}  // namespace message

}  // namespace ublox

