//
// Copyright 2017 (C). Alex Robenko. All rights reserved.
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
/// @brief Contains definition of NAV-SAT message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/nav.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the NAV-SAT message fields.
/// @see NavSat
struct NavSatFields
{
    /// @brief Definition of "iTOW" field.
    using iTOW = field::nav::iTOW;

    /// @brief Definition of "version" field.
    using version =
        field::common::U1T<
            comms::option::ValidNumValueRange<1, 1>,
            comms::option::DefaultNumValue<1>
        >;

    /// @brief Definition of "numSvs" field.
    using numSvs = field::common::U1;

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res2;

    /// @brief Definition of "gnssId" field.
    using gnssId = field::common::gnssId;

    /// @brief Definition of "svId" field.
    using svId = field::common::U1;

    /// @brief Definition of "cno" field.
    using cno = field::common::U1;

    /// @brief Definition of "elev" field.
    using elev = field::common::I1;

    /// @brief Definition of "azim" field.
    using azim = field::common::I2;

    /// @brief Definition of "prRes" field.
    using prRes = field::common::I2T<comms::option::ScalingRatio<1, 10> >;

    /// @brief Value enumeration for @ref qualityInd field.
    enum class QualityInd : std::uint8_t
    {
        Idle, ///< no signal
        Searching, ///< searching
        SignalAcquired, ///< signal acquired
        SignalUnusable, ///< signal unusable
        CodeLock, ///< code lock on signal
        CodeCarrierLocked, ///< code and carrier locked
        CodeCarrierLocked2, ///< code and carrier locked
        CodeCarrierLocked3, ///< code and carrier locked
        NumOfValues ///< number of available values
    };

    /// @brief Definition of "qualityInd" field.
    using qualityInd =
        field::common::EnumT<
            QualityInd,
            comms::option::ValidNumValueRange<0, (int)QualityInd::NumOfValues - 1>,
            comms::option::FixedBitLength<3>
        >;

    /// @brief Definition of "flagsLow" member field of @ref flags bitfield.
    struct flagsLow : public
        field::common::X1T<
            comms::option::FixedBitLength<1>
        >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS(svUsed);
    };

    /// @brief Value enumeration for @ref health field.
    enum class Health : std::uint8_t
    {
        Unknown, ///< unknown
        Healthy, ///< healthy
        Unhealthy, ///< unhealthy
        NumOfValues ///< number of available values
    };

    /// @brief Definition of "health" field.
    using health =
        field::common::EnumT<
            Health,
            comms::option::ValidNumValueRange<0, (int)Health::NumOfValues - 1>,
            comms::option::FixedBitLength<2>
        >;

    /// @brief Definition of "flagsMid" member field of @ref flags bitfield.
    struct flagsMid : public
        field::common::X1T<
            comms::option::FixedBitLength<2>
        >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS(diffCorr, smoothed);
    };

    /// @brief Value enumeration for @ref orbitSource field.
    enum class OrbitSource : std::uint8_t
    {
        NoInfo, ///< no orbit information is available for this SV
        Ephemeris, ///< ephemeris is used
        Almanac, ///< almanac is used
        AssistNowOffline, ///< AssistNow Offline orbit is used
        AssistNowAutonomous, ///< AssistNow Autonomous orbit is used
        NumOfValues ///< number of available values
    };

    /// @brief Definition of "orbitSource" field.
    using orbitSource =
        field::common::EnumT<
            OrbitSource,
            comms::option::ValidNumValueRange<0, (int)OrbitSource::NumOfValues - 1>,
            comms::option::FixedBitLength<3>
        >;

    /// @brief Definition of "flagsHigh" member field of @ref flags bitfield.
    struct flagsHigh : public
        field::common::X4T<
            comms::option::FixedBitLength<21>,
            comms::option::BitmaskReservedBits<0xfffffff0, 0>
        >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS(ephAvail, almAvail, anoAvail, aopAvail);
    };

    /// @brief Definition of "flags" field.
    struct flags : public
        field::common::BitfieldT<
            std::tuple<
                qualityInd,
                flagsLow,
                health,
                flagsMid,
                orbitSource,
                flagsHigh
            >
        >
    {
        /// @brief Allow access to internal fields.
        /// @details See definition of @b COMMS_FIELD_MEMBERS_ACCESS macro
        ///     related to @b comms::field::Bitfield class from COMMS library
        ///     for details.
        COMMS_FIELD_MEMBERS_ACCESS(
            qualityInd,
            flagsLow,
            health,
            flagsMid,
            orbitSource,
            flagsHigh);
    };

    /// @brief Definition of a block field repeated multiple times in @ref
    ///     data list.
    struct block : public
        field::common::BundleT<
            std::tuple<
                gnssId,
                svId,
                cno,
                elev,
                azim,
                prRes,
                flags
            >
        >
    {
        /// @brief Allow access to internal fields.
        /// @details See definition of @b COMMS_FIELD_MEMBERS_ACCESS macro
        ///     related to @b comms::field::Bitfield class from COMMS library
        ///     for details.
        COMMS_FIELD_MEMBERS_ACCESS(gnssId, svId, cno, elev, azim, prRes, flags);
    };

    /// @brief Definition of "data" field as list of blocks (@ref block).
    /// @tparam TOpt Extra option(s)
    template <typename TOpt = comms::option::EmptyOption>
    using data =
        field::common::ListT<
            block,
            comms::option::SequenceSizeForcingEnabled,
            TOpt
        >;

    /// @brief All the fields bundled in std::tuple.
    /// @tparam TOpt Extra option(s) for @ref data field
    template <typename TOpt>
    using All = std::tuple<
        iTOW,
        version,
        numSvs,
        reserved1,
        data<TOpt>
    >;
};

/// @brief Definition of NAV-SAT message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref NavSatFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
/// @tparam TDataOpt Extra option(s) for @b data field
template <typename TMsgBase = Message, typename TDataOpt = comms::option::EmptyOption>
class NavSat : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_SAT>,
        comms::option::FieldsImpl<NavSatFields::All<TDataOpt> >,
        comms::option::MsgType<NavSat<TMsgBase, TDataOpt> >,
        comms::option::HasDoRefresh
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_SAT>,
        comms::option::FieldsImpl<NavSatFields::All<TDataOpt> >,
        comms::option::MsgType<NavSat<TMsgBase, TDataOpt> >,
        comms::option::HasDoRefresh
    > Base;
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b iTOW for @ref NavSatFields::iTOW field
    ///     @li @b version for @ref NavSatFields::version field
    ///     @li @b numSvs for @ref NavSatFields::numSvs field
    ///     @li @b reserved1 for @ref NavSatFields::reserved1 field
    ///     @li @b data for @ref NavSatFields::data field
    COMMS_MSG_FIELDS_ACCESS(
        iTOW,
        version,
        numSvs,
        reserved1,
        data
    );

    /// @brief Default constructor
    NavSat() = default;

    /// @brief Copy constructor
    NavSat(const NavSat&) = default;

    /// @brief Move constructor
    NavSat(NavSat&& other) = default;

    /// @brief Destructor
    ~NavSat() = default;

    /// @brief Copy assignment
    NavSat& operator=(const NavSat&) = default;

    /// @brief Move assignment
    NavSat& operator=(NavSat&&) = default;

    /// @brief Provides custom read functionality.
    /// @details The number of blocks in @b data (@ref NavSatFields::data)
    ///     list is determined by the value of @b numSvs (@ref NavSatFields::numSvs)
    ///     field.
    template <typename TIter>
    comms::ErrorStatus doRead(TIter& iter, std::size_t len)
    {
        auto es = Base::template readFieldsUntil<FieldIdx_data>(iter, len);
        if (es != comms::ErrorStatus::Success) {
            return es;
        }

        field_data().forceReadElemCount(field_numSvs().value());
        return Base::template readFieldsFrom<FieldIdx_data>(iter, len);
    }

    /// @brief Provides custom refresh functionality
    /// @details The value of @b numSvs (@ref NavSatFields::numSvs) field is
    ///     determined by number of blocks stored in @b data (@ref NavSatFields::data)
    ///     list.
    /// @return @b true in case the value of "numSvs" field was modified, @b false otherwise
    bool doRefresh()
    {
        if (field_numSvs().value() == field_data().value().size()) {
            return false;
        }

        field_numSvs().value() = field_data().value().size();
        return true;
    }

};

}  // namespace message

}  // namespace ublox





