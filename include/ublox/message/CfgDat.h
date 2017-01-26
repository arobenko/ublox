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
/// @brief Contains definition of CFG-DAT message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/cfg.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the CFG-DAT message fields.
/// @see CfgDat
struct CfgDatFields
{
    /// @brief Definition of "datumNum" field.
    using datumNum = field::cfg::datumNum;

    /// @brief Definition of "datumName" field.
    using datumName = field::cfg::datumName;

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
        datumNum,
        datumName,
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

/// @brief Definition of CFG-DAT message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref CfgDatFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class CfgDat : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_DAT>,
        comms::option::FieldsImpl<CfgDatFields::All>,
        comms::option::MsgType<CfgDat<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_DAT>,
        comms::option::FieldsImpl<CfgDatFields::All>,
        comms::option::MsgType<CfgDat<TMsgBase> >
    > Base;
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b datumNum for @ref CfgDatFields::datumNum field
    ///     @li @b datumName for @ref CfgDatFields::datumName field
    ///     @li @b majA for @ref CfgDatFields::majA field
    ///     @li @b flat for @ref CfgDatFields::flat field
    ///     @li @b dX for @ref CfgDatFields::dX field
    ///     @li @b dY for @ref CfgDatFields::dY field
    ///     @li @b dZ for @ref CfgDatFields::dZ field
    ///     @li @b rotX for @ref CfgDatFields::rotX field
    ///     @li @b rotY for @ref CfgDatFields::rotY field
    ///     @li @b rotZ for @ref CfgDatFields::rotZ field
    ///     @li @b scale for @ref CfgDatFields::scale field
    COMMS_MSG_FIELDS_ACCESS(
        datumNum,
        datumName,
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
    CfgDat() = default;

    /// @brief Copy constructor
    CfgDat(const CfgDat&) = default;

    /// @brief Move constructor
    CfgDat(CfgDat&& other) = default;

    /// @brief Destructor
    virtual ~CfgDat() = default;

    /// @brief Copy assignment
    CfgDat& operator=(const CfgDat&) = default;

    /// @brief Move assignment
    CfgDat& operator=(CfgDat&&) = default;
};


}  // namespace message

}  // namespace ublox

