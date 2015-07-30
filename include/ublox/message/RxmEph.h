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

#include "ublox/field/rxm.h"

namespace ublox
{

namespace message
{

using RxmEphFields = std::tuple<
    field::rxm::SVID_Ext,
    field::rxm::HOW,
    comms::field::Optional<
        comms::field::ArrayList<
            field::common::FieldBase,
            field::rxm::SFxDx,
            comms::option::SequenceFixedSize<24>
        >
    >
>;

template <typename TMsgBase = Message>
class RxmEph : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_RXM_EPH>,
        comms::option::FieldsImpl<RxmEphFields>,
        comms::option::DispatchImpl<RxmEph<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_RXM_EPH>,
        comms::option::FieldsImpl<RxmEphFields>,
        comms::option::DispatchImpl<RxmEph<TMsgBase> >
    > Base;
public:
    enum FieldIdx
    {
        FieldIdx_Svid,
        FieldIdx_How,
        FieldIdx_Data,
        FieldIdx_NumOfValues
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_NumOfValues,
        "Number of fields is incorrect");

    RxmEph() = default;
    RxmEph(const RxmEph&) = default;
    RxmEph(RxmEph&& other) = default;
    virtual ~RxmEph() = default;

    RxmEph& operator=(const RxmEph&) = default;
    RxmEph& operator=(RxmEph&&) = default;

};


}  // namespace message

}  // namespace ublox





