//
// Copyright 2015 - 2016 (C). Alex Robenko. All rights reserved.
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

/// @file
/// @brief Contains definition of AID-INI message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the AID-INI message fields.
/// @see AidIni
struct AidIniFields
{
    /// @brief Bits access enumerator for @ref tmCfg bitmask field.
    enum
    {
        tmCfg_fEdge = 1, ///< @b fEdge bit index
        tmCfg_tm1 = 4, ///< @b tm1 bit index
        tmCfg_f1 = 6, ///< @b f1 bit index
        tmCfg_numOfValues ///< Upper limit for access bits
    };

    /// @brief Use this enumerator to access member fields of @ref date bitfield.
    enum
    {
        date_month, ///< Index of @b month member field
        date_year, ///< Index of @b year member field
        date_numOfValues ///< Number of member fields
    };

    /// @brief Use this enumerator to access member fields of @ref time bitfield.
    enum
    {
        time_sec, ///< Index of @b seconds member field
        time_min, ///< Index of @b minutes member field
        time_hour, ///< Index of @b hours member field
        time_day, ///< Index of @b day member field
        time_numOfValues ///< Number of member fields
    };

    /// @brief Bits access enumerator for @ref flags bitmask field.
    enum
    {
        flags_pos, ///< @b pos bit index
        flags_time, ///< @b time bit index
        flags_clockD, ///< @b clockD bit index
        flags_tp, ///< @b tp bit index
        flags_clockF, ///< @b clockF bit index
        flags_lla, ///< @b lla bit index
        flags_altInv, ///< @b altInv bit index
        flags_prevTm, ///< @b prevTm bit index
        flags_utc = 10, ///< @b utc bit index
        flags_numOfValues ///< Upper limit for access bits
    };

    /// @brief Definition of "ecefX" field.
    using ecefX =
        field::common::OptionalT<
            field::common::I4T<field::common::Scaling_cm2m>
        >;

    /// @brief Definition of "lat" field.
    using lat =
        field::common::OptionalT<
            field::common::I4T<comms::option::ScalingRatio<1, 10000000L> >
        >;

    /// @brief Definition of "ecefY" field.
    using ecefY = ecefX;

    /// @brief Definition of "lon" field.
    using lon = lat;

    /// @brief Definition of "ecefZ" field.
    using ecefZ = ecefX;

    /// @brief Definition of "alt" field.
    using alt = ecefZ;

    /// @brief Definition of "posAcc" field.
    using posAcc = field::common::U4T<field::common::Scaling_cm2m>;

    /// @brief Definition of "tmCfg" field.
    using tmCfg =
        field::common::X2T<
            comms::option::BitmaskReservedBits<0xfffad, 0>
        >;

    /// @brief Definition of "wno" field.
    using wno =
        field::common::OptionalT<
            field::common::U2
        >;

    /// @brief Definition of "date" field.
    using date =
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

    /// @brief Definition of "tow" field.
    using tow =
        field::common::OptionalT<
            field::common::U4T<field::common::Scaling_ms2s>
        >;

    /// @brief Definition of "time" field.
    using time =
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

    /// @brief Definition of "towNs" field.
    using towNs = field::common::I4T<field::common::Scaling_ns2s>;

    /// @brief Definition of "tAccMs" field.
    using tAccMs = field::common::U4T<field::common::Scaling_ms2s>;

    /// @brief Definition of "tAccNs" field.
    using tAccNs = field::common::U4T<field::common::Scaling_ns2s>;

    /// @brief Definition of "clkD" field.
    using clkD =
        field::common::OptionalT<
            field::common::I4T<field::common::Scaling_ns2s>
        >;

    /// @brief Definition of "freq" field.
    using freq =
        field::common::OptionalT<
            field::common::I4T<comms::option::ScalingRatio<1, 100> >
        >;

    /// @brief Definition of "clkDAcc" field.
    using clkDAcc =
        field::common::OptionalT<
            field::common::U4T<field::common::Scaling_ns2s>
        >;

    /// @brief Definition of "freqAcc" field.
    using freqAcc =
        field::common::OptionalT<
            field::common::U4
        >;

    /// @brief Definition of "flags" field.
    using flags =
        field::common::X4T<
            comms::option::BitmaskReservedBits<0xfffffb00, 0>
        >;


    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        ecefX,
        lat,
        ecefY,
        lon,
        ecefZ,
        alt,
        posAcc,
        tmCfg,
        wno,
        date,
        tow,
        time,
        towNs,
        tAccMs,
        tAccNs,
        clkD,
        freq,
        clkDAcc,
        freqAcc,
        flags
    >;
};

/// @brief Definition of AID-INI message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref AidIniFields and for definition of the fields this message contains.
///
///     @b NOTE, that Ublox binary protocol specification reinterprets value of
///     some fields based on the value of some bits in @b flags (see @ref AidIniFields::flags)
///     field. It also combines the dual meaning of the field in a single name, such as
///     @b ecefXOrLat, @b ecefYOrLon, @b ecefZOrAlt, etc... @n
///     The implementation of this message splits these names into two separate
///     fields: @b ecefX + @b lat, @b ecefY + @b lon, @b ecefZ + @b alt, etc...
///     These fields are @b optional (see @ref field::common::OptionalT), and
///     marked as @b missing or @b existing based on the value of relevant bits
///     in @b flags (see @ref AidIniFields::flags) field.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class AidIni : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_AID_INI>,
        comms::option::FieldsImpl<AidIniFields::All>,
        comms::option::MsgType<AidIni<TMsgBase> >,
        comms::option::DispatchImpl,
        comms::option::MsgDoRead,
        comms::option::MsgDoRefresh
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_AID_INI>,
        comms::option::FieldsImpl<AidIniFields::All>,
        comms::option::MsgType<AidIni<TMsgBase> >,
        comms::option::DispatchImpl,
        comms::option::MsgDoRead,
        comms::option::MsgDoRefresh
    > Base;
public:

#ifdef FOR_DOXYGEN_DOC_ONLY
    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_ecefX, ///< @b ecefX field, see @ref AidIniFields::ecefX
        FieldIdx_lat, ///< @b lat field, see @ref AidIniFields::lat
        FieldIdx_ecefY, ///< @b ecefY field, see @ref AidIniFields::ecefY
        FieldIdx_lon, ///< @b lon field, see @ref AidIniFields::lon
        FieldIdx_ecefZ, ///< @b ecefZ field, see @ref AidIniFields::ecefZ
        FieldIdx_alt, ///< @b alt field, see @ref AidIniFields::alt
        FieldIdx_posAcc, ///< @b posAcc field, see @ref AidIniFields::posAcc
        FieldIdx_tmCfg, ///< @b tmCfg field, see @ref AidIniFields::tmCfg
        FieldIdx_wno, ///< @b wno field, see @ref AidIniFields::wno
        FieldIdx_date, ///< @b date field, see @ref AidIniFields::date
        FieldIdx_tow, ///< @b tow field, see @ref AidIniFields::tow
        FieldIdx_time, ///< @b time field, see @ref AidIniFields::time
        FieldIdx_towNs, ///< @b towNs field, see @ref AidIniFields::towNs
        FieldIdx_tAccMs, ///< @b tAccMs field, see @ref AidIniFields::tAccMs
        FieldIdx_tAccNs, ///< @b tAccNs field, see @ref AidIniFields::tAccNs
        FieldIdx_clkD, ///< @b clkD field, see @ref AidIniFields::clkD
        FieldIdx_freq, ///< @b posAcc freq, see @ref AidIniFields::freq
        FieldIdx_clkDAcc, ///< @b clkDAcc field, see @ref AidIniFields::clkDAcc
        FieldIdx_freqAcc, ///< @b freqAcc field, see @ref AidIniFields::freqAcc
        FieldIdx_flags, ///< @b flags field, see @ref AidIniFields::flags
        FieldIdx_numOfValues ///< number of available fields
    };

    /// @brief Access to fields bundled as a struct
    struct FieldsAsStruct
    {
        AidIniFields::ecefX& ecefX; ///< @b ecefX field, see @ref AidIniFields::ecefX
        AidIniFields::lat& lat; ///< @b lat field, see @ref AidIniFields::lat
        AidIniFields::ecefY& ecefY; ///< @b ecefY field, see @ref AidIniFields::ecefY
        AidIniFields::lon& lon; ///< @b lon field, see @ref AidIniFields::lon
        AidIniFields::ecefZ& ecefZ; ///< @b ecefZ field, see @ref AidIniFields::ecefZ
        AidIniFields::alt& alt; ///< @b alt field, see @ref AidIniFields::alt
        AidIniFields::posAcc& posAcc; ///< @b posAcc field, see @ref AidIniFields::posAcc
        AidIniFields::tmCfg& tmCfg; ///< @b tmCfg field, see @ref AidIniFields::tmCfg
        AidIniFields::wno& wno; ///< @b wno field, see @ref AidIniFields::wno
        AidIniFields::date& date; ///< @b date field, see @ref AidIniFields::date
        AidIniFields::tow& tow; ///< @b tow field, see @ref AidIniFields::tow
        AidIniFields::time& time; ///< @b time field, see @ref AidIniFields::time
        AidIniFields::towNs& towNs; ///< @b towNs field, see @ref AidIniFields::towNs
        AidIniFields::tAccMs& tAccMs; ///< @b tAccMs field, see @ref AidIniFields::tAccMs
        AidIniFields::tAccNs& tAccNs; ///< @b tAccNs field, see @ref AidIniFields::tAccNs
        AidIniFields::clkD& clkD; ///< @b clkD field, see @ref AidIniFields::clkD
        AidIniFields::posAcc& posAcc; ///< @b posAcc freq, see @ref AidIniFields::freq
        AidIniFields::clkDAcc& clkDAcc; ///< @b clkDAcc field, see @ref AidIniFields::clkDAcc
        AidIniFields::freqAcc& freqAcc; ///< @b freqAcc field, see @ref AidIniFields::freqAcc
        AidIniFields::flags& flags; ///< @b flags field, see @ref AidIniFields::flags
    };

    /// @brief Access to @b const fields bundled as a struct
    struct ConstFieldsAsStruct
    {
        const AidIniFields::ecefX& ecefX; ///< @b ecefX field, see @ref AidIniFields::ecefX
        const AidIniFields::lat& lat; ///< @b lat field, see @ref AidIniFields::lat
        const AidIniFields::ecefY& ecefY; ///< @b ecefY field, see @ref AidIniFields::ecefY
        const AidIniFields::lon& lon; ///< @b lon field, see @ref AidIniFields::lon
        const AidIniFields::ecefZ& ecefZ; ///< @b ecefZ field, see @ref AidIniFields::ecefZ
        const AidIniFields::alt& alt; ///< @b alt field, see @ref AidIniFields::alt
        const AidIniFields::posAcc& posAcc; ///< @b posAcc field, see @ref AidIniFields::posAcc
        const AidIniFields::tmCfg& tmCfg; ///< @b tmCfg field, see @ref AidIniFields::tmCfg
        const AidIniFields::wno& wno; ///< @b wno field, see @ref AidIniFields::wno
        const AidIniFields::date& date; ///< @b date field, see @ref AidIniFields::date
        const AidIniFields::tow& tow; ///< @b tow field, see @ref AidIniFields::tow
        const AidIniFields::time& time; ///< @b time field, see @ref AidIniFields::time
        const AidIniFields::towNs& towNs; ///< @b towNs field, see @ref AidIniFields::towNs
        const AidIniFields::tAccMs& tAccMs; ///< @b tAccMs field, see @ref AidIniFields::tAccMs
        const AidIniFields::tAccNs& tAccNs; ///< @b tAccNs field, see @ref AidIniFields::tAccNs
        const AidIniFields::clkD& clkD; ///< @b clkD field, see @ref AidIniFields::clkD
        const AidIniFields::posAcc& posAcc; ///< @b posAcc freq, see @ref AidIniFields::freq
        const AidIniFields::clkDAcc& clkDAcc; ///< @b clkDAcc field, see @ref AidIniFields::clkDAcc
        const AidIniFields::freqAcc& freqAcc; ///< @b freqAcc field, see @ref AidIniFields::freqAcc
        const AidIniFields::flags& flags; ///< @b flags field, see @ref AidIniFields::flags
    };

    /// @brief Get access to fields bundled into a struct
    FieldsAsStruct fieldsAsStruct();

    /// @brief Get access to @b const fields bundled into a struct
    ConstFieldsAsStruct fieldsAsStruct() const;

#else
    COMMS_MSG_FIELDS_ACCESS(Base,
        ecefX,
        lat,
        ecefY,
        lon,
        ecefZ,
        alt,
        posAcc,
        tmCfg,
        wno,
        date,
        tow,
        time,
        towNs,
        tAccMs,
        tAccNs,
        clkD,
        freq,
        clkDAcc,
        freqAcc,
        flags);
#endif // #ifdef FOR_DOXYGEN_DOC_ONLY

    /// @brief Default constructor
    /// @details The existing/missing mode of the optional fields is determined
    ///     by the default value of the @b flags (see @ref AidIniFields::flags)
    ///     field.
    AidIni()
    {
        auto& allFields = Base::fields();

        std::get<FieldIdx_ecefX>(allFields).setExists();
        std::get<FieldIdx_lat>(allFields).setMissing();
        std::get<FieldIdx_ecefY>(allFields).setExists();
        std::get<FieldIdx_lon>(allFields).setMissing();
        std::get<FieldIdx_ecefZ>(allFields).setExists();
        std::get<FieldIdx_alt>(allFields).setMissing();
        std::get<FieldIdx_wno>(allFields).setExists();
        std::get<FieldIdx_date>(allFields).setMissing();
        std::get<FieldIdx_tow>(allFields).setExists();
        std::get<FieldIdx_time>(allFields).setMissing();
        std::get<FieldIdx_clkD>(allFields).setExists();
        std::get<FieldIdx_freq>(allFields).setMissing();
        std::get<FieldIdx_clkDAcc>(allFields).setExists();
        std::get<FieldIdx_freqAcc>(allFields).setMissing();
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

    /// @brief Provides custom read functionality.
    /// @details This function performs full read as if the value of the
    ///     @b flags (see @ref AidIniFields::flags) field contains value 0.
    ///     When such read is complete the function checks the actual value
    ///     of the @b flags field and reassigns values to appropriate optional
    ///     fields if needed.
    template <typename TIter>
    comms::ErrorStatus doRead(TIter& iter, std::size_t len)
    {
        auto& allFields = Base::fields();
        auto& flagsField = std::get<FieldIdx_flags>(allFields);
        flagsField.value() = 0;

        auto es = Base::doRead(iter, len);
        if (es != comms::ErrorStatus::Success) {
            return es;
        }

        if (flagsField.getBitValue(AidIniFields::flags_lla)) {
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

        if (flagsField.getBitValue(AidIniFields::flags_utc)) {
            auto& wnoField = std::get<FieldIdx_wno>(allFields);
            auto& dateField = std::get<FieldIdx_date>(allFields);
            auto& towField = std::get<FieldIdx_tow>(allFields);
            auto& timeField = std::get<FieldIdx_time>(allFields);

            reassignToBitfield(wnoField, dateField);
            reassignToBitfield(towField, timeField);
        }

        if (flagsField.getBitValue(AidIniFields::flags_clockF)) {
            auto& clkDField = std::get<FieldIdx_clkD>(allFields);
            auto& freqField = std::get<FieldIdx_freq>(allFields);
            auto& clkDAccField = std::get<FieldIdx_clkDAcc>(allFields);
            auto& freqAccField = std::get<FieldIdx_freqAcc>(allFields);

            reassignToField(clkDField, freqField);
            reassignToField(clkDAccField, freqAccField);
        }

        return es;
    }

    /// @brief Provides custom refresh functionality
    /// @details The function checks the value of  @b flags
    ///     (see @ref AidIniFields::flags) field and modifies mode of other
    ///     @b optional fields accordingly.
    /// @return @b true in case the mode of any optional field was modified, @b false otherwise
    bool doRefresh()
    {
        bool refreshed = false;

        auto& allFields = Base::fields();
        auto& flagsField = std::get<FieldIdx_flags>(allFields);

        auto expectedCartesian = comms::field::OptionalMode::Exists;
        auto expectedGeodetic = comms::field::OptionalMode::Missing;
        if (flagsField.getBitValue(AidIniFields::flags_lla)) {
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
        if (flagsField.getBitValue(AidIniFields::flags_utc)) {
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
        if (flagsField.getBitValue(AidIniFields::flags_clockF)) {
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
        std::uint8_t buf[BufSize] = {0};
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

