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

#include <algorithm>

#include "comms/Message.h"
#include "ublox/Message.h"
#include "ublox/field/MsgId.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

enum class CfgTmode2_TimeMode : std::uint8_t
{
    Disabled,
    SurveyIn,
    FixedMode,
    NumOfValues
};

enum
{
    CfgTmode2Field_flags_lla,
    CfgTmode2Field_flags_altInv,
    CfgTmode2Field_flags_numOfValues
};

using CfgTmode2Field_timeMode =
    comms::field::EnumValue<
        field::common::FieldBase,
        CfgTmode2_TimeMode,
        comms::option::ValidNumValueRange<0, (int)CfgTmode2_TimeMode::NumOfValues - 1>
    >;
using CfgTmode2Field_reserved1 = field::common::res1;
using CfgTmode2Field_flags =
    field::common::X2T<
        comms::option::BitmaskReservedBits<0xfffc, 0>
    >;
using CfgTmode2Field_ecefX =
    comms::field::Optional<
        field::common::I4T<field::common::Scaling_cm2m>
    >;
using CfgTmode2Field_lat =
    comms::field::Optional<
        field::common::I4T<comms::option::ScalingRatio<1, 10000000L> >
    >;
using CfgTmode2Field_ecefY =
    comms::field::Optional<
        field::common::I4T<field::common::Scaling_cm2m>
    >;
using CfgTmode2Field_lon =
    comms::field::Optional<
        field::common::I4T<comms::option::ScalingRatio<1, 10000000L> >
    >;
using CfgTmode2Field_ecefZ =
    comms::field::Optional<
        field::common::I4T<field::common::Scaling_cm2m>
    >;
using CfgTmode2Field_alt =
    comms::field::Optional<
        field::common::I4T<field::common::Scaling_cm2m>
    >;
using CfgTmode2Field_fixedPosAcc =
    field::common::U4T<
        field::common::Scaling_mm2m
    >;
using CfgTmode2Field_svinMinDur = field::common::U4;
using CfgTmode2Field_svinAccLimit =
    field::common::U4T<
        field::common::Scaling_mm2m
    >;


using CfgTmode2Fields = std::tuple<
    CfgTmode2Field_timeMode,
    CfgTmode2Field_reserved1,
    CfgTmode2Field_flags,
    CfgTmode2Field_ecefX,
    CfgTmode2Field_lat,
    CfgTmode2Field_ecefY,
    CfgTmode2Field_lon,
    CfgTmode2Field_ecefZ,
    CfgTmode2Field_alt,
    CfgTmode2Field_fixedPosAcc,
    CfgTmode2Field_svinMinDur,
    CfgTmode2Field_svinAccLimit
>;

template <typename TMsgBase = Message>
class CfgTmode2 : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_TMODE2>,
        comms::option::FieldsImpl<CfgTmode2Fields>,
        comms::option::DispatchImpl<CfgTmode2<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_TMODE2>,
        comms::option::FieldsImpl<CfgTmode2Fields>,
        comms::option::DispatchImpl<CfgTmode2<TMsgBase> >
    > Base;
public:
    enum FieldIdx
    {
        FieldIdx_timeMode,
        FieldIdx_reserved1,
        FieldIdx_flags,
        FieldIdx_ecefX,
        FieldIdx_lat,
        FieldIdx_ecefY,
        FieldIdx_lon,
        FieldIdx_ecefZ,
        FieldIdx_alt,
        FieldIdx_fixedPosAcc,
        FieldIdx_svinMinDur,
        FieldIdx_svinAccLimit,
        FieldIdx_numOfValues
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    CfgTmode2()
    {
        auto& allFields = Base::fields();

        auto& ecefXField = std::get<FieldIdx_ecefX>(allFields);
        auto& ecefYField = std::get<FieldIdx_ecefY>(allFields);
        auto& ecefZField = std::get<FieldIdx_ecefZ>(allFields);

        static const auto DefaultCartesianMode = comms::field::OptionalMode::Exists;
        ecefXField.setMode(DefaultCartesianMode);
        ecefYField.setMode(DefaultCartesianMode);
        ecefZField.setMode(DefaultCartesianMode);

        auto& latField = std::get<FieldIdx_lat>(allFields);
        auto& lonField = std::get<FieldIdx_lon>(allFields);
        auto& altField = std::get<FieldIdx_alt>(allFields);

        static const auto DefaultGeodeticMode = comms::field::OptionalMode::Missing;
        latField.setMode(DefaultGeodeticMode);
        lonField.setMode(DefaultGeodeticMode);
        altField.setMode(DefaultGeodeticMode);
    }

    CfgTmode2(const CfgTmode2&) = default;
    CfgTmode2(CfgTmode2&& other) = default;
    virtual ~CfgTmode2() = default;

    CfgTmode2& operator=(const CfgTmode2&) = default;
    CfgTmode2& operator=(CfgTmode2&&) = default;

protected:
    virtual comms::ErrorStatus readImpl(
        typename Base::ReadIterator& iter,
        std::size_t len) override
    {
        auto es = Base::template readFieldsUntil<FieldIdx_ecefX>(iter, len);
        if (es != comms::ErrorStatus::Success) {
            return es;
        }

        auto& allFields = Base::fields();
        auto& flagsField = std::get<FieldIdx_flags>(allFields);

        auto cartesianMode = comms::field::OptionalMode::Exists;
        auto geodeticMode = comms::field::OptionalMode::Missing;
        if (flagsField.getBitValue(CfgTmode2Field_flags_lla)) {
            std::swap(cartesianMode, geodeticMode);
        }

        auto& ecefXField = std::get<FieldIdx_ecefX>(allFields);
        auto& ecefYField = std::get<FieldIdx_ecefY>(allFields);
        auto& ecefZField = std::get<FieldIdx_ecefZ>(allFields);
        ecefXField.setMode(cartesianMode);
        ecefYField.setMode(cartesianMode);
        ecefZField.setMode(cartesianMode);

        auto& latField = std::get<FieldIdx_lat>(allFields);
        auto& lonField = std::get<FieldIdx_lon>(allFields);
        auto& altField = std::get<FieldIdx_alt>(allFields);
        latField.setMode(geodeticMode);
        lonField.setMode(geodeticMode);
        altField.setMode(geodeticMode);

        return Base::template readFieldsFrom<FieldIdx_ecefX>(iter, len);
    }

    virtual bool refreshImpl() override
    {
        auto& allFields = Base::fields();
        auto& flagsField = std::get<FieldIdx_flags>(allFields);

        auto cartesianMode = comms::field::OptionalMode::Exists;
        auto geodeticMode = comms::field::OptionalMode::Missing;
        if (flagsField.getBitValue(CfgTmode2Field_flags_lla)) {
            std::swap(cartesianMode, geodeticMode);
        }

        auto& ecefXField = std::get<FieldIdx_ecefX>(allFields);
        auto& ecefYField = std::get<FieldIdx_ecefY>(allFields);
        auto& ecefZField = std::get<FieldIdx_ecefZ>(allFields);
        auto& latField = std::get<FieldIdx_lat>(allFields);
        auto& lonField = std::get<FieldIdx_lon>(allFields);
        auto& altField = std::get<FieldIdx_alt>(allFields);

        if ((ecefXField.getMode() == cartesianMode) &&
            (ecefYField.getMode() == cartesianMode) &&
            (ecefZField.getMode() == cartesianMode) &&
            (latField.getMode() == geodeticMode) &&
            (lonField.getMode() == geodeticMode) &&
            (altField.getMode() == geodeticMode)) {
            return false;
        }

        ecefXField.setMode(cartesianMode);
        ecefYField.setMode(cartesianMode);
        ecefZField.setMode(cartesianMode);
        latField.setMode(geodeticMode);
        lonField.setMode(geodeticMode);
        altField.setMode(geodeticMode);
        return true;
    }

};


}  // namespace message

}  // namespace ublox

