//
// Copyright 2015 - 2017 (C). Alex Robenko. All rights reserved.
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

    /// @brief Definition of "ecefX" field.
    using ecefX =
        field::common::OptionalT<
            field::common::I4T<comms::option::UnitsCentimeters>,
            comms::option::DefaultOptionalMode<comms::field::OptionalMode::Exists>
        >;

    /// @brief Definition of "lat" field.
    using lat =
        field::common::OptionalT<
            field::common::I4T<
                comms::option::ScalingRatio<1, 10000000L>,
                comms::option::UnitsDegrees
            >,
            comms::option::DefaultOptionalMode<comms::field::OptionalMode::Missing>
        >;

    /// @brief Definition of "ecefY" field.
    using ecefY = ecefX;

    /// @brief Definition of "lon" field.
    using lon = lat;

    /// @brief Definition of "ecefZ" field.
    using ecefZ = ecefX;

    /// @brief Definition of "alt" field.
    using alt =
        field::common::OptionalT<
            field::common::I4T<comms::option::UnitsCentimeters>,
            comms::option::DefaultOptionalMode<comms::field::OptionalMode::Missing>
        >;

    /// @brief Definition of "posAcc" field.
    using posAcc = field::common::U4T<comms::option::UnitsCentimeters>;

    /// @brief Definition of "tmCfg" field.
    struct tmCfg : public
        field::common::X2T<
            comms::option::BitmaskReservedBits<0xfffad, 0>
        >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS(fEdge=1, tm1=4, f1=6);
    };

    /// @brief Definition of "wno" field.
    using wno =
        field::common::OptionalT<
            field::common::U2T<comms::option::UnitsWeeks>,
            comms::option::DefaultOptionalMode<comms::field::OptionalMode::Exists>
        >;

    /// @brief Definition of the @ref date bitfield
    struct dateBitfield : public
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
    {
        /// @brief Allow access to internal fields.
        /// @details See definition of @b COMMS_FIELD_MEMBERS_ACCESS macro
        ///     related to @b comms::field::Bitfield class from COMMS library
        ///     for details.
        COMMS_FIELD_MEMBERS_ACCESS(month, year);
    };

    /// @brief Definition of "date" field.
    using date =
        field::common::OptionalT<
            dateBitfield,
            comms::option::DefaultOptionalMode<comms::field::OptionalMode::Missing>
        >;

    /// @brief Definition of "tow" field.
    using tow =
        field::common::OptionalT<
            field::common::U4T<comms::option::UnitsMilliseconds>,
            comms::option::DefaultOptionalMode<comms::field::OptionalMode::Exists>
        >;

    /// @brief Definition of the @ref time bitfield
    struct timeBitfield : public
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
    {
        /// @brief Allow access to internal fields.
        /// @details See definition of @b COMMS_FIELD_MEMBERS_ACCESS macro
        ///     related to @b comms::field::Bitfield class from COMMS library
        ///     for details.
        COMMS_FIELD_MEMBERS_ACCESS(sec, min, hour, day);
    };

    /// @brief Definition of "time" field.
    using time =
        field::common::OptionalT<
            timeBitfield,
            comms::option::DefaultOptionalMode<comms::field::OptionalMode::Missing>
        >;

    /// @brief Definition of "towNs" field.
    using towNs = field::common::I4T<comms::option::UnitsNanoseconds>;

    /// @brief Definition of "tAccMs" field.
    using tAccMs = field::common::U4T<comms::option::UnitsMilliseconds>;

    /// @brief Definition of "tAccNs" field.
    using tAccNs = field::common::U4T<comms::option::UnitsNanoseconds>;

    /// @brief Definition of "clkD" field.
    using clkD =
        field::common::OptionalT<
            field::common::I4T<comms::option::UnitsNanoseconds>,
            comms::option::DefaultOptionalMode<comms::field::OptionalMode::Exists>
        >;

    /// @brief Definition of "freq" field.
    using freq =
        field::common::OptionalT<
            field::common::I4T<
                comms::option::ScalingRatio<1, 100>,
                comms::option::UnitsHertz
            >,
            comms::option::DefaultOptionalMode<comms::field::OptionalMode::Missing>
        >;

    /// @brief Definition of "clkDAcc" field.
    using clkDAcc =
        field::common::OptionalT<
            field::common::U4T<comms::option::UnitsNanoseconds>,
            comms::option::DefaultOptionalMode<comms::field::OptionalMode::Exists>
        >;

    /// @brief Definition of "freqAcc" field.
    using freqAcc =
        field::common::OptionalT<
            field::common::U4,
            comms::option::DefaultOptionalMode<comms::field::OptionalMode::Missing>
        >;

    /// @brief Definition of "flags" field.
    struct flags : public
        field::common::X4T<
            comms::option::BitmaskReservedBits<0xfffffb00, 0>
        >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS(pos, time, clockD, tp, clockF, lla, altInv, prevTm, utc=10);
    };

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
///     See @ref AidIniFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
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
        comms::option::HasDoRefresh
    >
{
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b ecefX for @ref AidIniFields::ecefX field
    ///     @li @b lat for @ref AidIniFields::lat field
    ///     @li @b ecefY for @ref AidIniFields::ecefY field
    ///     @li @b lon for @ref AidIniFields::lon field
    ///     @li @b ecefZ for @ref AidIniFields::ecefZ field
    ///     @li @b alt for @ref AidIniFields::alt field
    ///     @li @b posAcc for @ref AidIniFields::posAcc field
    ///     @li @b tmCfg for @ref AidIniFields::tmCfg field
    ///     @li @b wno for @ref AidIniFields::wno field
    ///     @li @b date for @ref AidIniFields::date field
    ///     @li @b tow for @ref AidIniFields::tow field
    ///     @li @b time for @ref AidIniFields::time field
    ///     @li @b towNs for @ref AidIniFields::towNs field
    ///     @li @b tAccMs for @ref AidIniFields::tAccMs field
    ///     @li @b tAccNs for @ref AidIniFields::tAccNs field
    ///     @li @b clkD for @ref AidIniFields::clkD field
    ///     @li @b freq for @ref AidIniFields::freq field
    ///     @li @b clkDAcc for @ref AidIniFields::clkDAcc field
    ///     @li @b freqAcc for @ref AidIniFields::freqAcc field
    ///     @li @b flags for @ref AidIniFields::flags field
    COMMS_MSG_FIELDS_ACCESS(
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

    /// @brief Default constructor
    /// @details The existing/missing mode of the optional fields is determined
    ///     by the default value of the @b flags (see @ref AidIniFields::flags)
    ///     field.
    AidIni() = default;

    /// @brief Copy constructor
    AidIni(const AidIni&) = default;

    /// @brief Move constructor
    AidIni(AidIni&& other) = default;

    /// @brief Destructor
    ~AidIni() = default;

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
        using Base = typename std::decay<decltype(comms::toMessageBase(*this))>::type;
        field_flags().value() = 0;
        doRefresh();

        auto es = Base::doRead(iter, len);
        if (es != comms::ErrorStatus::Success) {
            return es;
        }

        if (field_flags().getBitValue(AidIniFields::flags::BitIdx_lla)) {
            reassignToField(field_ecefX(), field_lat());
            reassignToField(field_ecefY(), field_lon());
            reassignToField(field_ecefZ(), field_alt());
        }

        if (field_flags().getBitValue(AidIniFields::flags::BitIdx_utc)) {
            reassignToBitfield(field_wno(), field_date());
            reassignToBitfield(field_tow(), field_time());
        }

        if (field_flags().getBitValue(AidIniFields::flags::BitIdx_clockF)) {
            reassignToField(field_clkD(), field_freq());
            reassignToField(field_clkDAcc(), field_freqAcc());
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

        auto expectedCartesian = comms::field::OptionalMode::Exists;
        auto expectedGeodetic = comms::field::OptionalMode::Missing;
        if (field_flags().getBitValue(AidIniFields::flags::BitIdx_lla)) {
            std::swap(expectedCartesian, expectedGeodetic);
        }

        if ((field_ecefX().getMode() != expectedCartesian) ||
            (field_ecefY().getMode() != expectedCartesian) ||
            (field_ecefZ().getMode() != expectedCartesian) ||
            (field_lat().getMode() != expectedGeodetic) ||
            (field_lon().getMode() != expectedGeodetic) ||
            (field_alt().getMode() != expectedGeodetic)) {

            field_ecefX().setMode(expectedCartesian);
            field_ecefY().setMode(expectedCartesian);
            field_ecefZ().setMode(expectedCartesian);
            field_lat().setMode(expectedGeodetic);
            field_lon().setMode(expectedGeodetic);
            field_alt().setMode(expectedGeodetic);

            refreshed = true;
        }

        auto expectedWnoTowMode = comms::field::OptionalMode::Exists;
        auto expectedDateTimeMode = comms::field::OptionalMode::Missing;
        if (field_flags().getBitValue(AidIniFields::flags::BitIdx_utc)) {
            std::swap(expectedWnoTowMode, expectedDateTimeMode);
        }

        if ((field_wno().getMode() != expectedWnoTowMode) ||
            (field_tow().getMode() != expectedWnoTowMode) ||
            (field_date().getMode() != expectedDateTimeMode) ||
            (field_time().getMode() != expectedDateTimeMode)) {
            field_wno().setMode(expectedWnoTowMode);
            field_tow().setMode(expectedWnoTowMode);
            field_date().setMode(expectedDateTimeMode);
            field_time().setMode(expectedDateTimeMode);
            refreshed = true;
        }

        auto expectedClkDMode = comms::field::OptionalMode::Exists;
        auto expectedFreqMode = comms::field::OptionalMode::Missing;
        if (field_flags().getBitValue(AidIniFields::flags::BitIdx_clockF)) {
            std::swap(expectedClkDMode, expectedFreqMode);
        }

        if ((field_clkD().getMode() != expectedClkDMode) ||
            (field_clkDAcc().getMode() != expectedClkDMode) ||
            (field_freq().getMode() != expectedFreqMode) ||
            (field_freqAcc().getMode() != expectedFreqMode)) {
            field_clkD().setMode(expectedClkDMode);
            field_clkDAcc().setMode(expectedClkDMode);
            field_freq().setMode(expectedFreqMode);
            field_freqAcc().setMode(expectedFreqMode);
            refreshed = true;
        }

        return refreshed;
    }

private:

    template <typename TFrom, typename TTo>
    void reassignToBitfield(TFrom& from, TTo& to)
    {
        to.setMode(comms::field::OptionalMode::Exists);
        using FromOptField = typename std::decay<decltype(from)>::type;
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

