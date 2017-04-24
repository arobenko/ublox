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
/// @brief Contains definition of CFG-ESRC message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the CFG-ESRC message fields.
/// @see CfgEsrc
struct CfgEsrcFields
{
    /// @brief Definition of "version" field.
    using version =
        field::common::U1T<
            comms::option::ValidNumValueRange<0, 0>
        >;

    /// @brief Definition of "numSources" field.
    using numSources = field::common::U1;

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res2;

    /// @brief Value enumeration for @ref oscId field.
    enum class OscId : std::uint8_t
    {
        Internal, ///< Internal oscillator
        External, ///< External oscillator
        NumOfValues /// number of available values
    };

    /// @brief Definition of "oscId" field.
    using oscId =
        field::common::EnumT<
            OscId,
            comms::option::ValidNumValueRange<0, (int)OscId::NumOfValues - 1>
        >;

    /// @brief Value enumeration for @ref extInt field.
    enum class ExtInt : std::uint8_t
    {
        EXTINT0, ///< EXTINT0
        EXTINT1, ///< EXTINT1
        NumOfValues ///< number of available values
    };

    /// @brief Definition of "extInt" field.
    using extInt =
        field::common::EnumT<
            ExtInt,
            comms::option::ValidNumValueRange<0, (int)ExtInt::NumOfValues - 1>
        >;

    /// @brief Value enumeration for @ref sourceType field.
    enum class SourceType : std::uint8_t
    {
        None, ///< None
        Frequency, ///< Frequency source
        Time, ///< Time source
        ExtOsc, ///< Feedback from external oscillator
        NumOfValues ///< number of available values
    };

    /// @brief Definition of "sourceType" field.
    using sourceType =
        field::common::EnumT<
            SourceType,
            comms::option::ValidNumValueRange<0, (int)SourceType::NumOfValues - 1>
        >;

    /// @brief Value enumeration for @ref polarity field.
    enum class Polarity : std::uint8_t
    {
        Rising, ///< rising edge
        Falling, ///< falling edge
        NumOfValues ///< number of available values
    };

    /// @brief Definition of "polarity" member field in @ref flags bitfield.
    using polarity =
        field::common::EnumT<
            Polarity,
            comms::option::FixedBitLength<1>,
            comms::option::ValidNumValueRange<0, (int)Polarity::NumOfValues - 1>
        >;

    /// @brief Value enumeration for @ref gnssUtc field.
    enum class GnssUtc : std::uint8_t
    {
        Gnss, ///< GNSS - as specified in CFG-TP5
        Utc, ///< UTC
        NumOfValues ///< number of available values
    };

    /// @brief Definition of "gnssUtc" member field of @ref flags bitfield.
    using gnssUtc =
        field::common::EnumT<
            GnssUtc,
            comms::option::FixedBitLength<1>,
            comms::option::ValidNumValueRange<0, (int)GnssUtc::NumOfValues - 1>
        >;


    /// @brief Definition of "flags" field.
    struct flags : public
        field::common::BitfieldT<
            std::tuple<
                polarity,
                gnssUtc,
                field::common::res2T<comms::option::FixedBitLength<14> >
            >
        >
    {
        /// @brief Allow access to internal fields.
        /// @details See definition of @b COMMS_FIELD_MEMBERS_ACCESS macro
        ///     related to @b comms::field::Bitfield class from COMMS library
        ///     for details.
        COMMS_FIELD_MEMBERS_ACCESS(polarity, gnssUtc, reserved);
    };

    /// @brief Definition of "freq" field.
    using freq =
        field::common::U4T<
            comms::option::ScalingRatio<1, 2>,
            comms::option::UnitsHertz
        >;

    /// @brief Definition of "reserved2" field.
    using reserved2 = field::common::res4;

    /// @brief Definition of "withTemp" field.
    using withTemp = field::common::U4T<comms::option::ScalingRatio<1, 0x100> >;

    /// @brief Definition of "withAge" field.
    using withAge = field::common::U4T<comms::option::ScalingRatio<1, 0x100> >;

    /// @brief Definition of "timeToTemp" field.
    using timeToTemp = field::common::U2T<comms::option::UnitsSeconds>;

    /// @brief Definition of "maxDevLifeTime" field.
    using maxDevLifeTime = field::common::U2;

    /// @brief Definition of "offset" field.
    using offset = field::common::I4T<comms::option::UnitsNanoseconds>;

    /// @brief Definition of "offsetUncertainty" field.
    using offsetUncertainty = field::common::U4T<comms::option::UnitsNanoseconds>;

    /// @brief Definition of "jitter" field.
    using jitter = field::common::U4T<comms::option::UnitsNanoseconds>;

    /// @brief Definition of a block field repeated multiple times in @ref
    ///     data list.
    struct block : public
        field::common::BundleT<
            std::tuple<
                extInt,
                sourceType,
                flags,
                freq,
                reserved2,
                withTemp,
                withAge,
                timeToTemp,
                maxDevLifeTime,
                offset,
                offsetUncertainty,
                jitter
            >
        >
    {
        /// @brief Allow access to internal fields.
        /// @details See definition of @b COMMS_FIELD_MEMBERS_ACCESS macro
        ///     related to @b comms::field::Bundle class from COMMS library
        ///     for details.
        COMMS_FIELD_MEMBERS_ACCESS(
            extInt,
            sourceType,
            flags,
            freq,
            reserved2,
            withTemp,
            withAge,
            timeToTemp,
            maxDevLifeTime,
            offset,
            offsetUncertainty,
            jitter
        );
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
        version,
        numSources,
        reserved1,
        data<TOpt>
    >;
};

/// @brief Definition of CFG-ESRC message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref CfgEsrcFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
/// @tparam TDataOpt Extra option(s) for @b data field
template <typename TMsgBase = Message, typename TDataOpt = comms::option::EmptyOption>
class CfgEsrc : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_ESRC>,
        comms::option::FieldsImpl<CfgEsrcFields::All<TDataOpt> >,
        comms::option::MsgType<CfgEsrc<TMsgBase, TDataOpt> >,
        comms::option::HasDoRefresh
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_ESRC>,
        comms::option::FieldsImpl<CfgEsrcFields::All<TDataOpt> >,
        comms::option::MsgType<CfgEsrc<TMsgBase, TDataOpt> >,
        comms::option::HasDoRefresh
    > Base;
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b version for @ref CfgEsrcFields::version field
    ///     @li @b numSources for @ref CfgEsrcFields::numSources field
    ///     @li @b reserved1 for @ref CfgEsrcFields::reserved1 field
    ///     @li @b data for @ref CfgEsrcFields::data field
    COMMS_MSG_FIELDS_ACCESS(version, numSources, reserved1, data);

    /// @brief Default constructor
    CfgEsrc() = default;

    /// @brief Copy constructor
    CfgEsrc(const CfgEsrc&) = default;

    /// @brief Move constructor
    CfgEsrc(CfgEsrc&& other) = default;

    /// @brief Destructor
    ~CfgEsrc() = default;

    /// @brief Copy assignment
    CfgEsrc& operator=(const CfgEsrc&) = default;

    /// @brief Move assignment
    CfgEsrc& operator=(CfgEsrc&&) = default;

    /// @brief Provides custom read functionality.
    /// @details The number of blocks in @b data (@ref CfgEsrcFields::data)
    ///     list is determined by the value of @b numSources (@ref CfgEsrcFields::numSources)
    ///     field.
    template <typename TIter>
    comms::ErrorStatus doRead(TIter& iter, std::size_t len)
    {
        auto es = Base::template readFieldsUntil<FieldIdx_data>(iter, len);
        if (es != comms::ErrorStatus::Success) {
            return es;
        }

        field_data().forceReadElemCount(field_numSources().value());
        return Base::template readFieldsFrom<FieldIdx_data>(iter, len);
    }

    /// @brief Provides custom refresh functionality
    /// @details The value of @b numSources (@ref CfgEsrcFields::numSources) field is
    ///     determined by number of blocks stored in @b data (@ref CfgEsrcFields::data)
    ///     list.
    /// @return @b true in case the value of "numSources" field was modified, @b false otherwise
    bool doRefresh()
    {
        if (field_numSources().value() == field_data().value().size()) {
            return false;
        }

        field_numSources().value() = field_data().value().size();
        return true;
    }

};


}  // namespace message

}  // namespace ublox





