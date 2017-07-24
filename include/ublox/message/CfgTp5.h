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
/// @brief Contains definition of CFG-TP5 message and its fields.

#pragma once

#include <algorithm>

#include "ublox/Message.h"
#include "ublox/field/cfg.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the CFG-TP5 message fields.
/// @see CfgTp5
struct CfgTp5Fields
{
    /// @brief Definition of "tpIdx" field.
    using tpIdx = field::cfg::tpIdx;

    /// @brief Definition of "version" field.
    using version =
        field::common::U1T<
            comms::option::ValidNumValueRange<0, 1>
        >;

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res2;

    /// @brief Definition of "antCableDelay" field.
    using antCableDelay = field::common::I2T<comms::option::UnitsNanoseconds>;

    /// @brief Definition of "rfGroupDelay" field.
    using rfGroupDelay = field::common::I2T<comms::option::UnitsNanoseconds>;

    /// @brief Definition of "freq" part of the @ref freqPeriod field.
    using freq =
        field::common::OptionalT<
            field::common::U4T<
                comms::option::UnitsHertz
            >,
            comms::option::DefaultOptionalMode<comms::field::OptionalMode::Missing>
        >;

    /// @brief Definition of "period" part of the @ref freqPeriod field.
    using period =
        field::common::OptionalT<
            field::common::U4T<
                comms::option::UnitsMicroseconds
            >,
            comms::option::DefaultOptionalMode<comms::field::OptionalMode::Exists>
        >;


    /// @brief Definition of "freqPeriod" field.
    struct freqPeriod : public
        field::common::BundleT<
            std::tuple<
                freq,
                period
            >
        >
    {
        /// @brief Allow access to internal fields.
        /// @details See definition of @b COMMS_FIELD_MEMBERS_ACCESS macro
        ///     related to @b comms::field::Bundle class from COMMS library
        ///     for details.
        COMMS_FIELD_MEMBERS_ACCESS(freq, period);
    };

    /// @brief Definition of "freqLock" part of the @ref freqPeriodLock field.
    using freqLock = freq;

    /// @brief Definition of "periodLock" part of the @ref freqPeriodLock field.
    using periodLock = period;

    /// @brief Definition of "freqPeriodLock" field.
    struct freqPeriodLock : public
        field::common::BundleT<
            std::tuple<
                freqLock,
                periodLock
            >
        >
    {
        /// @brief Allow access to internal fields.
        /// @details See definition of @b COMMS_FIELD_MEMBERS_ACCESS macro
        ///     related to @b comms::field::Bundle class from COMMS library
        ///     for details.
        COMMS_FIELD_MEMBERS_ACCESS(freqLock, periodLock);
    };

    /// @brief Definition of "pulseLen" part of the @ref pulseLenRatio field.
    using pulseLen =
        field::common::OptionalT<
            field::common::U4T<
                comms::option::UnitsMicroseconds
            >,
            comms::option::DefaultOptionalMode<comms::field::OptionalMode::Missing>
        >;

    /// @brief Definition of "ratio" part of the @ref pulseLenRatio field.
    using ratio =
        field::common::OptionalT<
            field::common::U4T<
                comms::option::ScalingRatio<1, 0x100000000ULL>
            >,
            comms::option::DefaultOptionalMode<comms::field::OptionalMode::Exists>
        >;


    /// @brief Definition of "pulseLenRatio" field.
    struct pulseLenRatio : public
        field::common::BundleT<
            std::tuple<
                pulseLen,
                ratio
            >
        >
    {
        /// @brief Allow access to internal fields.
        /// @details See definition of @b COMMS_FIELD_MEMBERS_ACCESS macro
        ///     related to @b comms::field::Bundle class from COMMS library
        ///     for details.
        COMMS_FIELD_MEMBERS_ACCESS(pulseLen, ratio);
    };

    /// @brief Definition of "pulseLenLock" part of the @ref pulseLenRatioLock field.
    using pulseLenLock = pulseLen;

    /// @brief Definition of "ratioLock" part of the @ref pulseLenRatioLock field.
    using ratioLock = ratio;

    /// @brief Definition of "pulseLenRatioLock" field.
    struct pulseLenRatioLock : public
        field::common::BundleT<
            std::tuple<
                pulseLenLock,
                ratioLock
            >
        >
    {
        /// @brief Allow access to internal fields.
        /// @details See definition of @b COMMS_FIELD_MEMBERS_ACCESS macro
        ///     related to @b comms::field::Bundle class from COMMS library
        ///     for details.
        COMMS_FIELD_MEMBERS_ACCESS(pulseLenLock, ratioLock);
    };

    /// @brief Definition of "userConfigDelay" field.
    using userConfigDelay = field::common::I4T<comms::option::UnitsNanoseconds>;

    /// @brief Definition of "flagsLow" member field of @ref flags bitfield.
    struct flagsLow : public
        field::common::X1T<
            comms::option::FixedBitLength<7>,
            comms::option::BitmaskReservedBits<0x80, 0>
        >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS_SEQ macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS_SEQ(active, logGpsFreq, lockedOtherSet, isFreq, isLength, alignToTow, polarity);
    };

    /// @brief Enumeration for @ref gridUtcGnss field.
    enum class GridUtcGnss : std::uint8_t
    {
        Utc, ///< UTC
        Gps, ///< GPS
        Glonass, ///< GLONASS
        BeiDou, ///< BeiDou
        Galileo, ///< Galileo
        NumOfValues ///< number of available values
    };

    /// @brief Definition of common "gridUtcGnss" member field of @ref flags bitfield.
    using gridUtcGnss =
        field::common::EnumT<
            GridUtcGnss,
            comms::option::ValidNumValueRange<0, (int)GridUtcGnss::NumOfValues - 1>,
            comms::option::FixedBitLength<4>
        >;


    /// @brief Enumeration for @ref syncMode field.
    enum class SyncMode : std::uint8_t
    {
        SyncMode0, ///< value 0
        SyncMode1, ///< value 1
        NumOfValues ///< number of available values
    };

    /// @brief Definition of common "syncMode" member field of @ref flags bitfield.
    using syncMode =
        field::common::EnumT<
            SyncMode,
            comms::option::ValidNumValueRange<0, (int)SyncMode::NumOfValues - 1>,
            comms::option::FixedBitLength<3>
        >;

    /// @brief Definition of "flags" field.
    struct flags : public
        field::common::BitfieldT<
            std::tuple<
                flagsLow,
                gridUtcGnss,
                syncMode,
                field::common::res4T<comms::option::FixedBitLength<18> >
            >
        >
    {
        /// @brief Allow access to internal fields.
        /// @details See definition of @b COMMS_FIELD_MEMBERS_ACCESS macro
        ///     related to @b comms::field::Bitfield class from COMMS library
        ///     for details.
        COMMS_FIELD_MEMBERS_ACCESS(flagsLow, gridUtcGnss, syncMode, reserved);
    };

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        tpIdx,
        version,
        reserved1,
        antCableDelay,
        rfGroupDelay,
        freqPeriod,
        freqPeriodLock,
        pulseLenRatio,
        pulseLenRatioLock,
        userConfigDelay,
        flags
    >;
};

/// @brief Definition of CFG-TP5 message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref CfgTp5Fields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class CfgTp5 : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_TP5>,
        comms::option::FieldsImpl<CfgTp5Fields::All>,
        comms::option::MsgType<CfgTp5<TMsgBase> >,
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
    ///     @li @b tpIdx for @ref CfgTp5Fields::tpIdx field
    ///     @li @b version for @ref CfgTp5Fields::version field
    ///     @li @b reserved1 for @ref CfgTp5Fields::reserved1 field
    ///     @li @b antCableDelay for @ref CfgTp5Fields::antCableDelay field
    ///     @li @b rfGroupDelay for @ref CfgTp5Fields::rfGroupDelay field
    ///     @li @b freqPeriod for @ref CfgTp5Fields::freqPeriod field
    ///     @li @b freqPeriodLock for @ref CfgTp5Fields::freqPeriodLock field
    ///     @li @b pulseLenRatio for @ref CfgTp5Fields::pulseLenRatio field
    ///     @li @b pulseLenRatioLock for @ref CfgTp5Fields::pulseLenRatioLock field
    ///     @li @b userConfigDelay for @ref CfgTp5Fields::userConfigDelay field
    ///     @li @b flags for @ref CfgTp5Fields::flags field
    COMMS_MSG_FIELDS_ACCESS(
        tpIdx,
        version,
        reserved1,
        antCableDelay,
        rfGroupDelay,
        freqPeriod,
        freqPeriodLock,
        pulseLenRatio,
        pulseLenRatioLock,
        userConfigDelay,
        flags
    );

    /// @brief Default constructor
    CfgTp5() = default;

    /// @brief Copy constructor
    CfgTp5(const CfgTp5&) = default;

    /// @brief Move constructor
    CfgTp5(CfgTp5&& other) = default;

    /// @brief Destructor
    ~CfgTp5() = default;

    /// @brief Copy assignment
    CfgTp5& operator=(const CfgTp5&) = default;

    /// @brief Move assignment
    CfgTp5& operator=(CfgTp5&&) = default;

    /// @brief Provides custom read functionality.
    /// @details The function reads all the fields up and including "flags"
    ///     (see @ref CfgTp5Fields::flags), then updates the optional fields
    ///     according to the relevant flags values.
    template <typename TIter>
    comms::ErrorStatus doRead(TIter& iter, std::size_t len)
    {
        using Base = typename std::decay<decltype(comms::toMessageBase(*this))>::type;
        auto es = Base::doRead(iter, len);
        if (es != comms::ErrorStatus::Success) {
            return es;
        }

        auto& flagsBits = field_flags().field_flagsLow();

        bool isFreq = flagsBits.getBitValue(CfgTp5Fields::flagsLow::BitIdx_isFreq);
        refreshFields(field_freqPeriod(), isFreq, true);
        refreshFields(field_freqPeriodLock(), isFreq, true);

        bool isLength = flagsBits.getBitValue(CfgTp5Fields::flagsLow::BitIdx_isLength);
        refreshFields(field_pulseLenRatio(), isLength, true);
        refreshFields(field_pulseLenRatioLock(), isLength, true);
        return es;
    }

    /// @brief Provides custom refreshing functionality.
    /// @details The existance of various optional fields depends on value
    ///     of the flags.
    bool doRefresh()
    {
        auto& flagsBits = field_flags().field_flagsLow();

        bool isFreq = flagsBits.getBitValue(CfgTp5Fields::flagsLow::BitIdx_isFreq);
        bool refreshed = refreshFields(field_freqPeriod(), isFreq);
        refreshed = refreshFields(field_freqPeriodLock(), isFreq) || refreshed;

        bool isLength = flagsBits.getBitValue(CfgTp5Fields::flagsLow::BitIdx_isLength);
        refreshed = refreshFields(field_pulseLenRatio(), isLength) || refreshed;
        refreshed = refreshFields(field_pulseLenRatioLock(), isLength) || refreshed;

        return refreshed;
    }

private:
    template <typename TBundle>
    static bool refreshFields(TBundle& bundle, bool enableFirst, bool updateValue = false)
    {
        auto& fields = bundle.value();
        if ((std::get<0>(fields).doesExist() == enableFirst) &&
            (std::get<1>(fields).isMissing() == enableFirst)) {
            return false;
        }

        auto firstMode = comms::field::OptionalMode::Exists;
        auto secondMode = comms::field::OptionalMode::Missing;
        if (!enableFirst) {
            std::swap(firstMode, secondMode);
        }

        std::get<0>(fields).setMode(firstMode);
        std::get<1>(fields).setMode(secondMode);

        if (!updateValue) {
            return true;
        }

        if (enableFirst) {
            std::get<0>(fields).field().value() = std::get<1>(fields).field().value();
        }
        else {
            std::get<1>(fields).field().value() = std::get<0>(fields).field().value();
        }

        return true;
    }

};


}  // namespace message

}  // namespace ublox

