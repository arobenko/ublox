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

#include "ublox/field/nav.h"

namespace ublox
{

namespace message
{

enum class NavSvinfo_ChipGen : std::uint8_t
{
    Antaris,
    Ublox5,
    Ublox6,
    NumOfValues
};

enum class NavSvinfo_QualityInd : std::uint8_t
{
    Idle,
    Searching,
    SignalAcquired,
    SignalUnusable,
    CodeLock,
    CodeCarrierLocked,
    CodeCarrierLocked2,
    CodeCarrierLocked3,
    NumOfValues
};

enum {
    NavSvinfoField_globalFlags_chipGen,
    NavSvinfoField_globalFlags_reserved,
    NavSvinfoField_globalFlags_numOfValues
};

enum {
    NavSvinfoField_flags_svUsed,
    NavSvinfoField_flags_diffCorr,
    NavSvinfoField_flags_orbitAvail,
    NavSvinfoField_flags_orbitEph,
    NavSvinfoField_flags_unhealthy,
    NavSvinfoField_flags_orbitAlm,
    NavSvinfoField_flags_smoothed,
    NavSvinfoField_flags_numOfValues
};

enum {
    NavSvinfoField_info_chn,
    NavSvinfoField_info_svid,
    NavSvinfoField_info_flags,
    NavSvinfoField_info_quality,
    NavSvinfoField_info_cno,
    NavSvinfoField_info_elev,
    NavSvinfoField_info_azim,
    NavSvinfoField_info_prRes,
    NavSvinfoField_info_numOfValues
};

using NavSvinfoField_iTOW = field::nav::iTOW;
using NavSvinfoField_numCh = field::nav::numCh;
using NavSvinfoField_globalFlags =
    comms::field::Bitfield<
        field::common::FieldBase,
        std::tuple<
            comms::field::EnumValue<
                field::common::FieldBase,
                NavSvinfo_ChipGen,
                comms::option::FixedBitLength<3>,
                comms::option::ValidNumValueRange<0, (int)NavSvinfo_ChipGen::NumOfValues - 1>
            >,
            field::common::res1T<comms::option::FixedBitLength<5> >
        >
    >;
using NavSvinfoField_reserved2 = field::common::res2;
using NavSvinfoField_chn = field::common::U1;
using NavSvinfoField_svid = field::nav::svid;
using NavSvinfoField_flags = field::common::X1;
using NavSvinfoField_quality =
    comms::field::EnumValue<
        field::common::FieldBase,
        NavSvinfo_QualityInd,
        comms::option::ValidNumValueRange<0, (int)NavSvinfo_QualityInd::NumOfValues - 1>
    >;
using NavSvinfoField_cno = field::common::U1;
using NavSvinfoField_elev = field::common::I1;
using NavSvinfoField_azim = field::common::I2;
using NavSvinfoField_prRes = field::common::I4T<field::common::Scaling_cm2m>;
using NavSvinfoField_info =
    comms::field::ArrayList<
        field::common::FieldBase,
        comms::field::Bundle<
            std::tuple<
                NavSvinfoField_chn,
                NavSvinfoField_svid,
                NavSvinfoField_flags,
                NavSvinfoField_quality,
                NavSvinfoField_cno,
                NavSvinfoField_elev,
                NavSvinfoField_azim,
                NavSvinfoField_prRes
            >
        >,
        comms::option::SequenceSizeForcingEnabled
    >;

using NavSvinfoFields = std::tuple<
    NavSvinfoField_iTOW,
    NavSvinfoField_numCh,
    NavSvinfoField_globalFlags,
    NavSvinfoField_reserved2,
    NavSvinfoField_info
>;

template <typename TMsgBase = Message>
class NavSvinfo : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_SVINFO>,
        comms::option::FieldsImpl<NavSvinfoFields>,
        comms::option::DispatchImpl<NavSvinfo<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_SVINFO>,
        comms::option::FieldsImpl<NavSvinfoFields>,
        comms::option::DispatchImpl<NavSvinfo<TMsgBase> >
    > Base;
public:
    enum FieldIdx
    {
        FieldIdx_iTOW,
        FieldIdx_numCh,
        FieldIdx_globalFlags,
        FieldIdx_reserved2,
        FieldIdx_info,
        FieldIdx_numOfValues
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    NavSvinfo() = default;
    NavSvinfo(const NavSvinfo&) = default;
    NavSvinfo(NavSvinfo&& other) = default;
    virtual ~NavSvinfo() = default;

    NavSvinfo& operator=(const NavSvinfo&) = default;
    NavSvinfo& operator=(NavSvinfo&&) = default;

protected:
    virtual comms::ErrorStatus readImpl(
        typename Base::ReadIterator& iter,
        std::size_t len) override
    {
        auto es = Base::template readFieldsUntil<FieldIdx_info>(iter, len);
        if (es != comms::ErrorStatus::Success) {
            return es;
        }

        auto& allFields = Base::fields();
        auto& numChField = std::get<FieldIdx_numCh>(allFields);
        auto& infoField = std::get<FieldIdx_info>(allFields);
        infoField.forceReadElemCount(numChField.value());

        return Base::template readFieldsFrom<FieldIdx_info>(iter, len);
    }

    virtual bool refreshImpl() override
    {
        auto& allFields = Base::fields();
        auto& numChField = std::get<FieldIdx_numCh>(allFields);
        auto& infoField = std::get<FieldIdx_info>(allFields);
        if (numChField.value() == infoField.value().size()) {
            return false;
        }

        numChField.value() = infoField.value().size();
        return true;
    }

};


}  // namespace message

}  // namespace ublox





