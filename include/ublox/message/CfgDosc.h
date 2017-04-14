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
/// @brief Contains definition of CFG-DOSC message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the CFG-DOSC message fields.
/// @see CfgDosc
struct CfgDoscFields
{
    /// @brief Definition of "version" field.
    using version =
        field::common::U1T<
            comms::option::ValidNumValueRange<0, 0>
        >;

    /// @brief Definition of "numOsc" field.
    using numOsc = field::common::U1;

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

    /// @brief Definition of "reserved2" field.
    using reserved2 = field::common::res1;

    /// @brief Definition of "isCallibrated" single bit bitmask member of @ref flags bitfield.
    struct isCalibrated : public field::common::X1T<comms::option::FixedBitLength<1> >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS(bit);
    };


    /// @brief Value enumeration for @ref controlIf field.
    enum class ControlIf: std::uint8_t
    {
        CustomDac, ///< Custom DAC attached to receiver's I2C
        Microchip, ///< Microchip MCP4726 (12 bit DAC) attached to receiver's I2C
        Ti, ///< TI DAC 8571 (16 bit DAC) attached to receiver's I2C
        Dac_12 = 13, ///< 12 bit DAC attached to host
        Dac_14, ///< 14 bit DAC attached to host
        Dac_16, ///< 16 bit DAC attached to host
        NumOfValues ///< number of available values
    };

    struct ControlIfValidator
    {
        template <typename TField>
        bool operator()(const TField& field) const
        {
            auto val = field.value();
            return
                ((ControlIf::CustomDac <= val) && (val <= ControlIf::Ti)) ||
                ((ControlIf::Dac_12 <= val) && (val < ControlIf::NumOfValues));
        }
    };

    /// @brief Definition of "controlIf" member field of @ref flags bitfield.
    using controlIf =
        field::common::EnumT<
            ControlIf,
            comms::option::FixedBitLength<4>,
            comms::option::ContentsValidator<ControlIfValidator>
        >;

    /// @brief Definition of "flags" field.
    struct flags : public
        field::common::BitfieldT<
            std::tuple<
                isCalibrated,
                controlIf,
                field::common::res2T<comms::option::FixedBitLength<11> >
            >
        >
    {
        /// @brief Allow access to internal fields.
        /// @details See definition of @b COMMS_FIELD_MEMBERS_ACCESS macro
        ///     related to @b comms::field::Bitfield class from COMMS library
        ///     for details.
        COMMS_FIELD_MEMBERS_ACCESS(isCalibrated, controlIf, reserved);
    };

    /// @brief Definition of "freq" field.
    using freq =
        field::common::U4T<
            comms::option::ScalingRatio<1, 2>,
            comms::option::UnitsHertz
        >;

    /// @brief Definition of "phaseOffset" field.
    using phaseOffset = field::common::I4;

    /// @brief Definition of "withTemp" field.
    using withTemp = field::common::U4T<comms::option::ScalingRatio<1, 0x100> >;

    /// @brief Definition of "withAge" field.
    using withAge = field::common::U4T<comms::option::ScalingRatio<1, 0x100> >;

    /// @brief Definition of "timeToTemp" field.
    using timeToTemp = field::common::U2T<comms::option::UnitsSeconds>;

    /// @brief Definition of "reserved3" field.
    using reserved3 = field::common::res2;

    /// @brief Definition of "gainVco" field.
    using gainVco = field::common::I4T<comms::option::ScalingRatio<1, 0x10000> >;

    /// @brief Definition of "gainUncertainty" field.
    using gainUncertainty = field::common::U1T<comms::option::ScalingRatio<1, 0x100> >;

    /// @brief Definition of "reserved4" field.
    using reserved4 = field::common::res3;

    /// @brief Definition of a block field repeated multiple times in @ref
    ///     data list.
    struct block : public
        field::common::BundleT<
            std::tuple<
                oscId,
                reserved2,
                flags,
                freq,
                phaseOffset,
                withTemp,
                withAge,
                timeToTemp,
                reserved3,
                gainVco,
                gainUncertainty,
                reserved4
            >
        >
    {
        /// @brief Allow access to internal fields.
        /// @details See definition of @b COMMS_FIELD_MEMBERS_ACCESS macro
        ///     related to @b comms::field::Bitfield class from COMMS library
        ///     for details.
        COMMS_FIELD_MEMBERS_ACCESS(
            oscId,
            reserved2,
            flags,
            freq,
            phaseOffset,
            withTemp,
            withAge,
            timeToTemp,
            reserved3,
            gainVco,
            gainUncertainty,
            reserved4);
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
        numOsc,
        reserved1,
        data<TOpt>
    >;
};

/// @brief Definition of CFG-DOSC message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref CfgDoscFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
/// @tparam TDataOpt Extra option(s) for @b data field
template <typename TMsgBase = Message, typename TDataOpt = comms::option::EmptyOption>
class CfgDosc : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_DOSC>,
        comms::option::FieldsImpl<CfgDoscFields::All<TDataOpt> >,
        comms::option::MsgType<CfgDosc<TMsgBase, TDataOpt> >,
        comms::option::HasDoRefresh
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_DOSC>,
        comms::option::FieldsImpl<CfgDoscFields::All<TDataOpt> >,
        comms::option::MsgType<CfgDosc<TMsgBase, TDataOpt> >,
        comms::option::HasDoRefresh
    > Base;
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b version for @ref CfgDoscFields::version field
    ///     @li @b numOsc for @ref CfgDoscFields::numOsc field
    ///     @li @b reserved1 for @ref CfgDoscFields::reserved1 field
    ///     @li @b data for @ref CfgDoscFields::data field
    COMMS_MSG_FIELDS_ACCESS(version, numOsc, reserved1, data);

    /// @brief Default constructor
    CfgDosc() = default;

    /// @brief Copy constructor
    CfgDosc(const CfgDosc&) = default;

    /// @brief Move constructor
    CfgDosc(CfgDosc&& other) = default;

    /// @brief Destructor
    ~CfgDosc() = default;

    /// @brief Copy assignment
    CfgDosc& operator=(const CfgDosc&) = default;

    /// @brief Move assignment
    CfgDosc& operator=(CfgDosc&&) = default;

    /// @brief Provides custom read functionality.
    /// @details The number of blocks in @b data (@ref CfgDoscFields::data)
    ///     list is determined by the value of @b numOsc (@ref CfgDoscFields::numOsc)
    ///     field.
    template <typename TIter>
    comms::ErrorStatus doRead(TIter& iter, std::size_t len)
    {
        auto es = Base::template readFieldsUntil<FieldIdx_data>(iter, len);
        if (es != comms::ErrorStatus::Success) {
            return es;
        }

        field_data().forceReadElemCount(field_numOsc().value());
        return Base::template readFieldsFrom<FieldIdx_data>(iter, len);
    }

    /// @brief Provides custom refresh functionality
    /// @details The value of @b numOsc (@ref CfgDoscFields::numOsc) field is
    ///     determined by number of blocks stored in @b data (@ref CfgDoscFields::data)
    ///     list.
    /// @return @b true in case the value of "numOsc" field was modified, @b false otherwise
    bool doRefresh()
    {
        if (field_numOsc().value() == field_data().value().size()) {
            return false;
        }

        field_numOsc().value() = field_data().value().size();
        return true;
    }

};


}  // namespace message

}  // namespace ublox





