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

#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

using AidAlpField_predTow = field::common::U4;
using AidAlpField_predDur = field::common::U4;
using AidAlpField_age = field::common::I4;
using AidAlpField_predWno = field::common::U2;
using AidAlpField_almWno = field::common::U2;
using AidAlpField_reserved1 = field::common::res4;
using AidAlpField_svs = field::common::U1;
using AidAlpField_reserved2 = field::common::res1;
using AidAlpField_reserved3 = field::common::res2;

using AidAlpFields = std::tuple<
    AidAlpField_predTow,
    AidAlpField_predDur,
    AidAlpField_age,
    AidAlpField_predWno,
    AidAlpField_almWno,
    AidAlpField_reserved1,
    AidAlpField_svs,
    AidAlpField_reserved2,
    AidAlpField_reserved3
>;

template <typename TMsgBase = Message>
class AidAlp : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_AID_ALP>,
        comms::option::FieldsImpl<AidAlpFields>,
        comms::option::DispatchImpl<AidAlp<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_AID_ALP>,
        comms::option::FieldsImpl<AidAlpFields>,
        comms::option::DispatchImpl<AidAlp<TMsgBase> >
    > Base;
public:

    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_predTow,
        FieldIdx_predDur,
        FieldIdx_age,
        FieldIdx_predWno,
        FieldIdx_almWno,
        FieldIdx_reserved1,
        FieldIdx_svs,
        FieldIdx_reserved2,
        FieldIdx_reserved3,
        FieldIdx_numOfValues ///< number of available fields
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    /// @brief Default constructor
    AidAlp() = default;

    /// @brief Copy constructor
    AidAlp(const AidAlp&) = default;

    /// @brief Move constructor
    AidAlp(AidAlp&& other) = default;

    /// @brief Destructor
    virtual ~AidAlp() = default;

    /// @brief Copy assignment
    AidAlp& operator=(const AidAlp&) = default;

    /// @brief Move assignment
    AidAlp& operator=(AidAlp&&) = default;
};


}  // namespace message

}  // namespace ublox





