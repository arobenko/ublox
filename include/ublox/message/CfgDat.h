//
// Copyright 2015 - 2016 (C). Alex Robenko. All rights reserved.
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
/// @details Inherits from
///     <a href="https://dl.dropboxusercontent.com/u/46999418/comms_champion/comms/html/classcomms_1_1MessageBase.html">comms::MessageBase</a>
///     while providing @b TMsgBase as common interface class as well as
///     @b comms::option::StaticNumIdImpl, @b comms::option::FieldsImpl, and
///     @b comms::option::DispatchImpl as options. @n
///     See @ref CfgDatFields and for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class CfgDat : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_DAT>,
        comms::option::FieldsImpl<CfgDatFields::All>,
        comms::option::DispatchImpl<CfgDat<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_DAT>,
        comms::option::FieldsImpl<CfgDatFields::All>,
        comms::option::DispatchImpl<CfgDat<TMsgBase> >
    > Base;
public:

    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_datumNum,  ///< @b datumNum field, see @ref CfgDatFields::datumNum
        FieldIdx_datumName,  ///< @b datumName field, see @ref CfgDatFields::datumName
        FieldIdx_majA,  ///< @b majA field, see @ref CfgDatFields::majA
        FieldIdx_flat,  ///< @b flat field, see @ref CfgDatFields::flat
        FieldIdx_dX,  ///< @b dX field, see @ref CfgDatFields::dX
        FieldIdx_dY,  ///< @b dY field, see @ref CfgDatFields::dY
        FieldIdx_dZ,  ///< @b dZ field, see @ref CfgDatFields::dZ
        FieldIdx_rotX,  ///< @b rotX field, see @ref CfgDatFields::rotX
        FieldIdx_rotY,  ///< @b rotY field, see @ref CfgDatFields::rotY
        FieldIdx_rotZ,  ///< @b rotZ field, see @ref CfgDatFields::rotZ
        FieldIdx_scale,  ///< @b scal field, see @ref CfgDatFields::scale
        FieldIdx_numOfValues ///< number of available fields
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

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

