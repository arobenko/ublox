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

#include "ublox/field/nav.h"

namespace ublox
{

namespace message
{

using NavVelnedField_iTOW = field::nav::iTOW;
using NavVelnedField_velN = field::common::I4T<field::common::Scaling_cm2m>;;
using NavVelnedField_velE = NavVelnedField_velN;
using NavVelnedField_velD = NavVelnedField_velN;
using NavVelnedField_speed = field::common::U4T<field::common::Scaling_cm2m>;
using NavVelnedField_gSpeed = field::common::U4T<field::common::Scaling_cm2m>;
using NavVelnedField_heading = field::nav::heading;
using NavVelnedField_sAcc = field::nav::sAcc;
using NavVelnedField_cAcc =
    field::common::U4T<comms::option::ScalingRatio<1, 100000> >;

using NavVelnedFields = std::tuple<
    NavVelnedField_iTOW,
    NavVelnedField_velN,
    NavVelnedField_velE,
    NavVelnedField_velD,
    NavVelnedField_speed,
    NavVelnedField_gSpeed,
    NavVelnedField_heading,
    NavVelnedField_sAcc,
    NavVelnedField_cAcc
>;


template <typename TMsgBase = Message>
class NavVelned : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_VELNED>,
        comms::option::FieldsImpl<NavVelnedFields>,
        comms::option::DispatchImpl<NavVelned<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_VELNED>,
        comms::option::FieldsImpl<NavVelnedFields>,
        comms::option::DispatchImpl<NavVelned<TMsgBase> >
    > Base;
public:
    enum FieldIdx
    {
        FieldIdx_iTOW,
        FieldIdx_velN,
        FieldIdx_velE,
        FieldIdx_velD,
        FieldIdx_speed,
        FieldIdx_gSpeed,
        FieldIdx_heading,
        FieldIdx_sAcc,
        FieldIdx_cAcc,
        FieldIdx_numOfValues
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    NavVelned() = default;
    NavVelned(const NavVelned&) = default;
    NavVelned(NavVelned&& other) = default;
    virtual ~NavVelned() = default;

    NavVelned& operator=(const NavVelned&) = default;
    NavVelned& operator=(NavVelned&&) = default;
};


}  // namespace message

}  // namespace ublox





