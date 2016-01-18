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

#include <iterator>

#include "comms/Message.h"
#include "ublox/Message.h"

#include "ublox/field/aid.h"

namespace ublox
{

namespace message
{

using AidAopField_svid = field::aid::svid;
using AidAopField_data =
    field::common::ListT<
        std::uint8_t,
        comms::option::SequenceFixedSize<59>
    >;
using AidAopField_optional =
    field::common::OptionalT<
        field::common::ListT<
            std::uint8_t,
            comms::option::SequenceFixedSize<48 * 3>
        >
    >;

using AidAopFields = std::tuple<
    AidAopField_svid,
    AidAopField_data,
    AidAopField_optional
>;

template <typename TMsgBase = Message>
class AidAop : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_AID_AOP>,
        comms::option::FieldsImpl<AidAopFields>,
        comms::option::DispatchImpl<AidAop<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_AID_AOP>,
        comms::option::FieldsImpl<AidAopFields>,
        comms::option::DispatchImpl<AidAop<TMsgBase> >
    > Base;
public:
    enum FieldIdx
    {
        FieldIdx_svid,
        FieldIdx_data,
        FieldIdx_optional,
        FieldIdx_numOfValues
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    AidAop() = default;
    AidAop(const AidAop&) = default;
    AidAop(AidAop&& other) = default;
    virtual ~AidAop() = default;

    AidAop& operator=(const AidAop&) = default;
    AidAop& operator=(AidAop&&) = default;
};


}  // namespace message

}  // namespace ublox





