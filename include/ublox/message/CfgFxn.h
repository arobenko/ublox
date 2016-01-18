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

enum
{
    CfgFxnField_flags_reserved0,
    CfgFxnField_flags_sleep,
    CfgFxnField_flags_reserved1,
    CfgFxnField_flags_absAlign,
    CfgFxnField_flags_onOff,
    CfgFxnField_flags_numOfValues
};

using CfgFxnField_flags =
    field::common::X4T<
        comms::option::BitmaskReservedBits<0xffffffe5, 0>
    >;
using CfgFxnField_tReacq = field::common::U4T<field::common::Scaling_ms2s>;
using CfgFxnField_tAcq = field::common::U4T<field::common::Scaling_ms2s>;
using CfgFxnField_tReacqOff = field::common::U4T<field::common::Scaling_ms2s>;
using CfgFxnField_tAcqOff = field::common::U4T<field::common::Scaling_ms2s>;
using CfgFxnField_tOn = field::common::U4T<field::common::Scaling_ms2s>;
using CfgFxnField_tOff = field::common::U4T<field::common::Scaling_ms2s>;
using CfgFxnField_res = field::common::res4;
using CfgFxnField_baseTow = field::common::U4T<field::common::Scaling_ms2s>;

using CfgFxnFields = std::tuple<
    CfgFxnField_flags,
    CfgFxnField_tReacq,
    CfgFxnField_tAcq,
    CfgFxnField_tReacqOff,
    CfgFxnField_tAcqOff,
    CfgFxnField_tOn,
    CfgFxnField_tOff,
    CfgFxnField_res,
    CfgFxnField_baseTow
>;

template <typename TMsgBase = Message>
class CfgFxn : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_FXN>,
        comms::option::FieldsImpl<CfgFxnFields>,
        comms::option::DispatchImpl<CfgFxn<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_FXN>,
        comms::option::FieldsImpl<CfgFxnFields>,
        comms::option::DispatchImpl<CfgFxn<TMsgBase> >
    > Base;
public:

    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_flags,
        FieldIdx_tReacq,
        FieldIdx_tAcq,
        FieldIdx_tReacqOff,
        FieldIdx_tAcqOff,
        FieldIdx_tOn,
        FieldIdx_tOff,
        FieldIdx_res,
        FieldIdx_baseTow,
        FieldIdx_numOfValues ///< number of available fields
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    /// @brief Default constructor
    CfgFxn() = default;

    /// @brief Copy constructor
    CfgFxn(const CfgFxn&) = default;

    /// @brief Move constructor
    CfgFxn(CfgFxn&& other) = default;

    /// @brief Destructor
    virtual ~CfgFxn() = default;

    /// @brief Copy assignment
    CfgFxn& operator=(const CfgFxn&) = default;

    /// @brief Move assignment
    CfgFxn& operator=(CfgFxn&&) = default;
};


}  // namespace message

}  // namespace ublox

