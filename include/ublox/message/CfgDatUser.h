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

using CfgDatUserFields = std::tuple<
    ublox::field::cfg::majA,
    ublox::field::cfg::flat,
    ublox::field::cfg::dX,
    ublox::field::cfg::dY,
    ublox::field::cfg::dZ,
    ublox::field::cfg::rotX,
    ublox::field::cfg::rotY,
    ublox::field::cfg::rotZ,
    ublox::field::cfg::scale
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
        FieldIdx_MajA,
        FieldIdx_Flat,
        FieldIdx_dX,
        FieldIdx_dY,
        FieldIdx_dZ,
        FieldIdx_RotX,
        FieldIdx_RotY,
        FieldIdx_RotZ,
        FieldIdx_Scale,
        FieldIdx_NumOfValues
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_NumOfValues,
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

