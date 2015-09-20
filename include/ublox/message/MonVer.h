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
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

using CfgUsbField_swVersion = field::common::ZString<30>;
using CfgUsbField_hwVersion = field::common::ZString<10>;
using CfgUsbField_extensions =
    comms::field::ArrayList<
        field::common::FieldBase,
        field::common::ZString<30>
    >;

using MonVerFields = std::tuple<
    CfgUsbField_swVersion,
    CfgUsbField_hwVersion,
    CfgUsbField_extensions
>;


template <typename TMsgBase = Message>
class MonVer : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_MON_VER>,
        comms::option::FieldsImpl<MonVerFields>,
        comms::option::DispatchImpl<MonVer<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_MON_VER>,
        comms::option::FieldsImpl<MonVerFields>,
        comms::option::DispatchImpl<MonVer<TMsgBase> >
    > Base;
public:
    enum FieldIdx
    {
        FieldIdx_swVersion,
        FieldIdx_hwVersion,
        FieldIdx_extensions,
        FieldIdx_numOfValues
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    MonVer() = default;
    MonVer(const MonVer&) = default;
    MonVer(MonVer&& other) = default;
    virtual ~MonVer() = default;

    MonVer& operator=(const MonVer&) = default;
    MonVer& operator=(MonVer&&) = default;
};


}  // namespace message

}  // namespace ublox

