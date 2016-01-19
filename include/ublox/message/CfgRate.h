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
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

enum class CfgRate_TimeRef : std::uint16_t
{
    UTC,
    GPS,
    NumOfValues
};

using CfgRateField_measRate = field::common::U2T<field::common::Scaling_ms2s>;
using CfgRateField_navRate =
    field::common::U2T<
        comms::option::DefaultNumValue<1>,
        comms::option::ValidNumValueRange<1, 1>
    >;
using CfgRateField_timeRef =
    field::common::EnumT<
        CfgRate_TimeRef,
        comms::option::ValidNumValueRange<0, (int)CfgRate_TimeRef::NumOfValues - 1>
    >;


using CfgRateFields = std::tuple<
    CfgRateField_measRate,
    CfgRateField_navRate,
    CfgRateField_timeRef
>;

template <typename TMsgBase = Message>
class CfgRate : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_RATE>,
        comms::option::FieldsImpl<CfgRateFields>,
        comms::option::DispatchImpl<CfgRate<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_RATE>,
        comms::option::FieldsImpl<CfgRateFields>,
        comms::option::DispatchImpl<CfgRate<TMsgBase> >
    > Base;
public:

    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_measRate,
        FieldIdx_navRate,
        FieldIdx_timeRef,
        FieldIdx_numOfValues ///< number of available fields
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    /// @brief Default constructor
    CfgRate() = default;

    /// @brief Copy constructor
    CfgRate(const CfgRate&) = default;

    /// @brief Move constructor
    CfgRate(CfgRate&& other) = default;

    /// @brief Destructor
    virtual ~CfgRate() = default;

    /// @brief Copy assignment
    CfgRate& operator=(const CfgRate&) = default;

    /// @brief Move assignment
    CfgRate& operator=(CfgRate&&) = default;
};


}  // namespace message

}  // namespace ublox

