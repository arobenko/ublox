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

using CfgDatUserField_majA = field::cfg::datMajA;
using CfgDatUserField_flat = field::cfg::datFlat;
using CfgDatUserField_dX = field::cfg::datDX;
using CfgDatUserField_dY = field::cfg::datDY;
using CfgDatUserField_dZ = field::cfg::datDZ;
using CfgDatUserField_rotX = field::cfg::datRotX;
using CfgDatUserField_rotY = field::cfg::datRotY;
using CfgDatUserField_rotZ = field::cfg::datRotZ;
using CfgDatUserField_scale = field::cfg::datScale;

using CfgDatUserFields = std::tuple<
    CfgDatUserField_majA,
    CfgDatUserField_flat,
    CfgDatUserField_dX,
    CfgDatUserField_dY,
    CfgDatUserField_dZ,
    CfgDatUserField_rotX,
    CfgDatUserField_rotY,
    CfgDatUserField_rotZ,
    CfgDatUserField_scale
>;

template <typename TMsgBase = Message>
class CfgDatUser : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_DAT>,
        comms::option::FieldsImpl<CfgDatUserFields>,
        comms::option::DispatchImpl<CfgDatUser<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_DAT>,
        comms::option::FieldsImpl<CfgDatUserFields>,
        comms::option::DispatchImpl<CfgDatUser<TMsgBase> >
    > Base;
public:
    enum FieldIdx
    {
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

    CfgDatUser() = default;
    CfgDatUser(const CfgDatUser&) = default;
    CfgDatUser(CfgDatUser&& other) = default;
    virtual ~CfgDatUser() = default;

    CfgDatUser& operator=(const CfgDatUser&) = default;
    CfgDatUser& operator=(CfgDatUser&&) = default;
};


}  // namespace message

}  // namespace ublox

