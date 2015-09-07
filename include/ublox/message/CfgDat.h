//
// Copyright 2015 (C). Alex Robenko. All rights reserved.
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


#pragma once

#include "comms/Message.h"
#include "ublox/Message.h"
#include "ublox/field/MsgId.h"
#include "ublox/field/cfg.h"

namespace ublox
{

namespace message
{

using CfgDatField_datumNum = field::cfg::datumNum;
using CfgDatField_datumName = field::cfg::datumName;
using CfgDatField_majA = field::cfg::datMajA;
using CfgDatField_flat = field::cfg::datFlat;
using CfgDatField_dX = field::cfg::datDX;
using CfgDatField_dY = field::cfg::datDY;
using CfgDatField_dZ = field::cfg::datDZ;
using CfgDatField_rotX = field::cfg::datRotX;
using CfgDatField_rotY = field::cfg::datRotY;
using CfgDatField_rotZ = field::cfg::datRotZ;
using CfgDatField_scale = field::cfg::datScale;

using CfgDatFields = std::tuple<
    CfgDatField_datumNum,
    CfgDatField_datumName,
    CfgDatField_majA,
    CfgDatField_flat,
    CfgDatField_dX,
    CfgDatField_dY,
    CfgDatField_dZ,
    CfgDatField_rotX,
    CfgDatField_rotY,
    CfgDatField_rotZ,
    CfgDatField_scale
>;

template <typename TMsgBase = Message>
class CfgDat : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_DAT>,
        comms::option::FieldsImpl<CfgDatFields>,
        comms::option::DispatchImpl<CfgDat<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_DAT>,
        comms::option::FieldsImpl<CfgDatFields>,
        comms::option::DispatchImpl<CfgDat<TMsgBase> >
    > Base;
public:
    enum FieldIdx
    {
        FieldIdx_datumNum,
        FieldIdx_datumName,
        FieldIdx_majA,
        FieldIdx_flat,
        FieldIdx_dX,
        FieldIdx_dY,
        FieldIdx_dZ,
        FieldIdx_rotX,
        FieldIdx_rotY,
        FieldIdx_rotZ,
        FieldIdx_scale,
        FieldIdx_numOfValues
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    CfgDat() = default;
    CfgDat(const CfgDat&) = default;
    CfgDat(CfgDat&& other) = default;
    virtual ~CfgDat() = default;

    CfgDat& operator=(const CfgDat&) = default;
    CfgDat& operator=(CfgDat&&) = default;
};


}  // namespace message

}  // namespace ublox

