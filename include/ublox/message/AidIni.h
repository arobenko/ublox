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

enum
{
    AidIniField_tmCfg_fEdge = 1,
    AidIniField_tmCfg_tm1 = 4,
    AidIniField_tmCfg_f1 = 6,
    AidIniField_tmCfg_numOfValues
};

enum
{
    AidIniField_date_month,
    AidIniField_date_year,
    AidIniField_date_numOfValues
};

enum
{
    AidIniField_time_sec,
    AidIniField_time_min,
    AidIniField_time_hour,
    AidIniField_time_day,
    AidIniField_time_numOfValues
};

enum
{
    AidIniField_flags_pos,
    AidIniField_flags_time,
    AidIniField_flags_clockD,
    AidIniField_flags_tp,
    AidIniField_flags_clockF,
    AidIniField_flags_lla,
    AidIniField_flags_altInv,
    AidIniField_flags_prevTm,
    AidIniField_flags_utc = 10,
    AidIniField_flags_numOfValues
};

using AidIniField_ecefX =
    field::common::OptionalT<
        field::common::I4T<field::common::Scaling_cm2m>
    >;
using AidIniField_lat =
    field::common::OptionalT<
        field::common::I4T<comms::option::ScalingRatio<1, 10000000L> >
    >;
using AidIniField_ecefY = AidIniField_ecefX;
using AidIniField_lon = AidIniField_lat;
using AidIniField_ecefZ = AidIniField_ecefX;
using AidIniField_alt = AidIniField_ecefZ;
using AidIniField_posAcc = field::common::U4T<field::common::Scaling_cm2m>;
using AidIniField_tmCfg =
    field::common::X2T<
        comms::option::BitmaskReservedBits<0xfffad, 0>
    >;
using AidIniField_wno =
    field::common::OptionalT<
        field::common::U2
    >;
using AidIniField_date =
    field::common::OptionalT<
        field::common::BitfieldT<
            std::tuple<
                field::common::U1T<
                    comms::option::ValidNumValueRange<1, 12>,
                    comms::option::FixedBitLength<8>
                >,
                field::common::U2T<
                    comms::option::DefaultNumValue<2000>,
                    comms::option::NumValueSerOffset<-2000>,
                    comms::option::ValidNumValueRange<2000, 2000 + 0xff>,
                    comms::option::FixedBitLength<8>
                >
            >
        >
    >;
using AidIniField_tow =
    field::common::OptionalT<
        field::common::U4T<field::common::Scaling_ms2s>
    >;
using AidIniField_time =
    field::common::OptionalT<
        field::common::BitfieldT<
            std::tuple<
                field::common::U1T<
                    comms::option::ValidNumValueRange<0, 60>,
                    comms::option::FixedBitLength<8>
                >,
                field::common::U1T<
                    comms::option::ValidNumValueRange<0, 59>,
                    comms::option::FixedBitLength<8>
                >,
                field::common::U1T<
                    comms::option::ValidNumValueRange<0, 59>,
                    comms::option::FixedBitLength<8>
                >,
                field::common::U1T<
                    comms::option::ValidNumValueRange<1, 31>,
                    comms::option::FixedBitLength<8>
                >
            >
        >
    >;
using AidIniField_towNs = field::common::I4T<field::common::Scaling_ns2s>;
using AidIniField_tAccMs = field::common::U4T<field::common::Scaling_ms2s>;
using AidIniField_tAccNs = field::common::U4T<field::common::Scaling_ns2s>;
using AidIniField_clkD =
    field::common::OptionalT<
        field::common::I4T<field::common::Scaling_ns2s>
    >;
using AidIniField_freq =
    field::common::OptionalT<
        field::common::I4T<comms::option::ScalingRatio<1, 100> >
    >;
using AidIniField_clkDAcc =
    field::common::OptionalT<
        field::common::U4T<field::common::Scaling_ns2s>
    >;
using AidIniField_freqAcc =
    field::common::OptionalT<
        field::common::U4
    >;
using AidIniField_flags =
    field::common::X4T<
        comms::option::BitmaskReservedBits<0xfffffb00, 0>
    >;


using AidIniFields = std::tuple<
    AidIniField_ecefX,
    AidIniField_lat,
    AidIniField_ecefY,
    AidIniField_lon,
    AidIniField_ecefZ,
    AidIniField_alt,
    AidIniField_posAcc,
    AidIniField_tmCfg,
    AidIniField_wno,
    AidIniField_date,
    AidIniField_tow,
    AidIniField_time,
    AidIniField_towNs,
    AidIniField_tAccMs,
    AidIniField_tAccNs,
    AidIniField_clkD,
    AidIniField_freq,
    AidIniField_clkDAcc,
    AidIniField_freqAcc,
    AidIniField_flags
>;


template <typename TMsgBase = Message>
class AidIni : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_AID_INI>,
        comms::option::FieldsImpl<AidIniFields>,
        comms::option::DispatchImpl<AidIni<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_AID_INI>,
        comms::option::FieldsImpl<AidIniFields>,
        comms::option::DispatchImpl<AidIni<TMsgBase> >
    > Base;
public:

    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_ecefX,
        FieldIdx_lat,
        FieldIdx_ecefY,
        FieldIdx_lon,
        FieldIdx_ecefZ,
        FieldIdx_alt,
        FieldIdx_posAcc,
        FieldIdx_tmCfg,
        FieldIdx_wno,
        FieldIdx_date,
        FieldIdx_tow,
        FieldIdx_time,
        FieldIdx_towNs,
        FieldIdx_tAccMs,
        FieldIdx_tAccNs,
        FieldIdx_clkD,
        FieldIdx_freq,
        FieldIdx_clkDAcc,
        FieldIdx_freqAcc,
        FieldIdx_flags,
        FieldIdx_numOfValues ///< number of available fields
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    /// @brief Default constructor
    AidIni()
    {

        auto& allFields = Base::fields();
        auto exists = comms::field::OptionalMode::Exists;
        auto missing = comms::field::OptionalMode::Missing;

        std::get<FieldIdx_ecefX>(allFields).setMode(exists);
        std::get<FieldIdx_lat>(allFields).setMode(missing);
        std::get<FieldIdx_ecefY>(allFields).setMode(exists);
        std::get<FieldIdx_lon>(allFields).setMode(missing);
        std::get<FieldIdx_ecefZ>(allFields).setMode(exists);
        std::get<FieldIdx_alt>(allFields).setMode(missing);
        std::get<FieldIdx_wno>(allFields).setMode(exists);
        std::get<FieldIdx_date>(allFields).setMode(missing);
        std::get<FieldIdx_tow>(allFields).setMode(exists);
        std::get<FieldIdx_time>(allFields).setMode(missing);
        std::get<FieldIdx_clkD>(allFields).setMode(exists);
        std::get<FieldIdx_freq>(allFields).setMode(missing);
        std::get<FieldIdx_clkDAcc>(allFields).setMode(exists);
        std::get<FieldIdx_freqAcc>(allFields).setMode(missing);
    }

    /// @brief Copy constructor
    AidIni(const AidIni&) = default;

    /// @brief Move constructor
    AidIni(AidIni&& other) = default;

    /// @brief Destructor
    virtual ~AidIni() = default;

    /// @brief Copy assignment
    AidIni& operator=(const AidIni&) = default;

    /// @brief Move assignment
    AidIni& operator=(AidIni&&) = default;

protected:
    virtual comms::ErrorStatus readImpl(
        typename Base::ReadIterator& iter,
        std::size_t len) override
    {
        auto es = Base::readImpl(iter, len);
        if (es != comms::ErrorStatus::Success) {
            return es;
        }

        auto& allFields = Base::fields();
        auto& flagsField = std::get<FieldIdx_flags>(allFields);

        if (flagsField.getBitValue(AidIniField_flags_lla)) {
            auto& ecefXField = std::get<FieldIdx_ecefX>(allFields);
            auto& latField = std::get<FieldIdx_lat>(allFields);
            auto& ecefYField = std::get<FieldIdx_ecefY>(allFields);
            auto& lonField = std::get<FieldIdx_lon>(allFields);
            auto& ecefZField = std::get<FieldIdx_ecefZ>(allFields);
            auto& altField = std::get<FieldIdx_alt>(allFields);

            reassignToField(ecefXField, latField);
            reassignToField(ecefYField, lonField);
            reassignToField(ecefZField, altField);
        }

        if (flagsField.getBitValue(AidIniField_flags_utc)) {
            auto& wnoField = std::get<FieldIdx_wno>(allFields);
            auto& dateField = std::get<FieldIdx_date>(allFields);
            auto& towField = std::get<FieldIdx_tow>(allFields);
            auto& timeField = std::get<FieldIdx_time>(allFields);

            reassignToBitfield(wnoField, dateField);
            reassignToBitfield(towField, timeField);
        }

        if (flagsField.getBitValue(AidIniField_flags_clockF)) {
            auto& clkDField = std::get<FieldIdx_clkD>(allFields);
            auto& freqField = std::get<FieldIdx_freq>(allFields);
            auto& clkDAccField = std::get<FieldIdx_clkDAcc>(allFields);
            auto& freqAccField = std::get<FieldIdx_freqAcc>(allFields);

            reassignToField(clkDField, freqField);
            reassignToField(clkDAccField, freqAccField);
        }

        return es;
    }

    virtual bool refreshImpl() override
    {
        bool refreshed = false;

        auto& allFields = Base::fields();
        auto& flagsField = std::get<FieldIdx_flags>(allFields);

        auto expectedCartesian = comms::field::OptionalMode::Exists;
        auto expectedGeodetic = comms::field::OptionalMode::Missing;
        if (flagsField.getBitValue(AidIniField_flags_lla)) {
            std::swap(expectedCartesian, expectedGeodetic);
        }

        auto& ecefXField = std::get<FieldIdx_ecefX>(allFields);
        auto& latField = std::get<FieldIdx_lat>(allFields);
        auto& ecefYField = std::get<FieldIdx_ecefY>(allFields);
        auto& lonField = std::get<FieldIdx_lon>(allFields);
        auto& ecefZField = std::get<FieldIdx_ecefZ>(allFields);
        auto& altField = std::get<FieldIdx_alt>(allFields);

        if ((ecefXField.getMode() != expectedCartesian) ||
            (ecefYField.getMode() != expectedCartesian) ||
            (ecefZField.getMode() != expectedCartesian) ||
            (latField.getMode() != expectedGeodetic) ||
            (lonField.getMode() != expectedGeodetic) ||
            (altField.getMode() != expectedGeodetic)) {

            ecefXField.setMode(expectedCartesian);
            ecefYField.setMode(expectedCartesian);
            ecefZField.setMode(expectedCartesian);
            latField.setMode(expectedGeodetic);
            lonField.setMode(expectedGeodetic);
            altField.setMode(expectedGeodetic);

            refreshed = true;
        }

        auto expectedWnoTowMode = comms::field::OptionalMode::Exists;
        auto expectedDateTimeMode = comms::field::OptionalMode::Missing;
        if (flagsField.getBitValue(AidIniField_flags_utc)) {
            std::swap(expectedWnoTowMode, expectedDateTimeMode);
        }

        auto& wnoField = std::get<FieldIdx_wno>(allFields);
        auto& dateField = std::get<FieldIdx_date>(allFields);
        auto& towField = std::get<FieldIdx_tow>(allFields);
        auto& timeField = std::get<FieldIdx_time>(allFields);

        if ((wnoField.getMode() != expectedWnoTowMode) ||
            (towField.getMode() != expectedWnoTowMode) ||
            (dateField.getMode() != expectedDateTimeMode) ||
            (timeField.getMode() != expectedDateTimeMode)) {
            wnoField.setMode(expectedWnoTowMode);
            towField.setMode(expectedWnoTowMode);
            dateField.setMode(expectedDateTimeMode);
            timeField.setMode(expectedDateTimeMode);
            refreshed = true;
        }

        auto expectedClkDMode = comms::field::OptionalMode::Exists;
        auto expectedFreqMode = comms::field::OptionalMode::Missing;
        if (flagsField.getBitValue(AidIniField_flags_clockF)) {
            std::swap(expectedClkDMode, expectedFreqMode);
        }

        auto& clkDField = std::get<FieldIdx_clkD>(allFields);
        auto& freqField = std::get<FieldIdx_freq>(allFields);
        auto& clkDAccField = std::get<FieldIdx_clkDAcc>(allFields);
        auto& freqAccField = std::get<FieldIdx_freqAcc>(allFields);

        if ((clkDField.getMode() != expectedClkDMode) ||
            (clkDAccField.getMode() != expectedClkDMode) ||
            (freqField.getMode() != expectedFreqMode) ||
            (freqAccField.getMode() != expectedFreqMode)) {
            clkDField.setMode(expectedClkDMode);
            clkDAccField.setMode(expectedClkDMode);
            freqField.setMode(expectedFreqMode);
            freqAccField.setMode(expectedFreqMode);
            refreshed = true;
        }

        return refreshed;
    }

private:

    template <typename TFrom, typename TTo>
    void reassignToBitfield(TFrom& from, TTo& to)
    {
        to.setMode(comms::field::OptionalMode::Exists);
        typedef typename std::decay<decltype(from)>::type FromOptField;
        static const auto BufSize = sizeof(typename FromOptField::Field::ValueType);
        std::uint8_t buf[BufSize];
        auto* writeIter = &buf[0];
        auto es = from.write(writeIter, BufSize);
        static_cast<void>(es);
        GASSERT(es == comms::ErrorStatus::Success);
        const auto* readIter = &buf[0];
        es = to.read(readIter, BufSize);
        static_cast<void>(es);
        GASSERT(es == comms::ErrorStatus::Success);
        from.setMode(comms::field::OptionalMode::Missing);
    }

    template <typename TFrom, typename TTo>
    void reassignToField(TFrom& from, TTo& to)
    {
        to.setMode(comms::field::OptionalMode::Exists);
        to.field().value() = from.field().value();
        from.setMode(comms::field::OptionalMode::Missing);
    }


};


}  // namespace message

}  // namespace ublox

