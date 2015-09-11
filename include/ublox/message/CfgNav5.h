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

enum
{
    CfgNav5Field_mask_dyn,
    CfgNav5Field_mask_minEl,
    CfgNav5Field_mask_posFixMode,
    CfgNav5Field_mask_drLim,
    CfgNav5Field_mask_posMask,
    CfgNav5Field_mask_timeMask,
    CfgNav5Field_mask_staticHoldMask,
    CfgNav5Field_mask_dgpsMask,
    CfgNav5Field_mask_numOfValues
};

enum class CfgNav5_DynModel : std::uint8_t
{
    Portable,
    Stationary = 2,
    Pedestrian,
    Automotive,
    Sea,
    Airborne_1g,
    Airborne_2g,
    Airborne_4g,
};

struct CfgNav5_DynModelValidator
{
    template <typename TField>
    bool operator()(const TField& field) const
    {
        static const CfgNav5_DynModel Values[] = {
            CfgNav5_DynModel::Portable,
            CfgNav5_DynModel::Stationary,
            CfgNav5_DynModel::Pedestrian,
            CfgNav5_DynModel::Automotive,
            CfgNav5_DynModel::Sea,
            CfgNav5_DynModel::Airborne_1g,
            CfgNav5_DynModel::Airborne_2g,
            CfgNav5_DynModel::Airborne_4g
        };

        auto value = field.value();
        auto iter = std::lower_bound(std::begin(Values), std::end(Values), value);
        return (iter != std::end(Values)) && (*iter == value);
    }
};

enum class CfgNav5_FixMode : std::uint8_t
{
    Only_2D = 1,
    Only_3D,
    Auto,
};


using CfgNav5Field_mask =
    field::common::X2T<
        comms::option::BitmaskReservedBits<0xff00, 0>
    >;
using CfgNav5Field_dynModel =
    comms::field::EnumValue<
        field::common::FieldBase,
        CfgNav5_DynModel,
        comms::option::ContentsValidator<CfgNav5_DynModelValidator>
    >;
using CfgNav5Field_fixMode =
    comms::field::EnumValue<
        field::common::FieldBase,
        CfgNav5_FixMode,
        comms::option::ValidNumValueRange<(int)CfgNav5_FixMode::Only_2D, (int)CfgNav5_FixMode::Auto>
    >;
using CfgNav5Field_fixedAlt = field::common::I4T<comms::option::ScalingRatio<1, 100> >;
using CfgNav5Field_fixedAltVar = field::common::U4T<comms::option::ScalingRatio<1, 10000> >;
using CfgNav5Field_minElev = field::common::I1;
using CfgNav5Field_drLimit = field::common::U1;
using CfgNav5Field_pDOP = field::common::U2T<comms::option::ScalingRatio<1, 10> >;
using CfgNav5Field_tDOP = field::common::U2T<comms::option::ScalingRatio<1, 10> >;
using CfgNav5Field_pAcc = field::common::U2;
using CfgNav5Field_tAcc = field::common::U2;
using CfgNav5Field_staticHoldThreash = field::common::U1T<field::common::Scaling_cm2m>;
using CfgNav5Field_dgpsTimeOut = field::common::U1;
using CfgNav5Field_cnoThreshNumSVs = field::common::U1;
using CfgNav5Field_cnoThresh = field::common::U1;
using CfgNav5Field_reserved2 = field::common::res2;
using CfgNav5Field_reserved3 = field::common::res4;
using CfgNav5Field_reserved4 = field::common::res4;

using CfgNav5Fields = std::tuple<
    CfgNav5Field_mask,
    CfgNav5Field_dynModel,
    CfgNav5Field_fixMode,
    CfgNav5Field_fixedAlt,
    CfgNav5Field_fixedAltVar,
    CfgNav5Field_minElev,
    CfgNav5Field_drLimit,
    CfgNav5Field_pDOP,
    CfgNav5Field_tDOP,
    CfgNav5Field_pAcc,
    CfgNav5Field_tAcc,
    CfgNav5Field_staticHoldThreash,
    CfgNav5Field_dgpsTimeOut,
    CfgNav5Field_cnoThreshNumSVs,
    CfgNav5Field_cnoThresh,
    CfgNav5Field_reserved2,
    CfgNav5Field_reserved3,
    CfgNav5Field_reserved4
>;

template <typename TMsgBase = Message>
class CfgNav5 : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_NAV5>,
        comms::option::FieldsImpl<CfgNav5Fields>,
        comms::option::DispatchImpl<CfgNav5<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_NAV5>,
        comms::option::FieldsImpl<CfgNav5Fields>,
        comms::option::DispatchImpl<CfgNav5<TMsgBase> >
    > Base;
public:
    enum FieldIdx
    {
        FieldIdx_mask,
        FieldIdx_dynModel,
        FieldIdx_fixMode,
        FieldIdx_fixedAlt,
        FieldIdx_fixedAltVar,
        FieldIdx_minElev,
        FieldIdx_drLimit,
        FieldIdx_pDOP,
        FieldIdx_tDOP,
        FieldIdx_pAcc,
        FieldIdx_tAcc,
        FieldIdx_staticHoldThreash,
        FieldIdx_dgpsTimeOut,
        FieldIdx_cnoThreshNumSVs,
        FieldIdx_cnoThresh,
        FieldIdx_reserved2,
        FieldIdx_reserved3,
        FieldIdx_reserved4,
        FieldIdx_numOfValues
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    CfgNav5() = default;
    CfgNav5(const CfgNav5&) = default;
    CfgNav5(CfgNav5&& other) = default;
    virtual ~CfgNav5() = default;

    CfgNav5& operator=(const CfgNav5&) = default;
    CfgNav5& operator=(CfgNav5&&) = default;
};


}  // namespace message

}  // namespace ublox

