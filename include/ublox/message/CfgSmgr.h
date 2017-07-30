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
/// @brief Contains definition of CFG-SMGR message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the CFG-SMGR message fields.
/// @see CfgSmgr
struct CfgSmgrFields
{
    /// @brief Definition of "version" field.
    using version =
        field::common::U1T<
            comms::option::ValidNumValueRange<0, 0>
        >;

    /// @brief Definition of "minGNSSFix" field.
    using minGNSSFix = field::common::U1;

    /// @brief Definition of "maxFreqChangeRate" field.
    using maxFreqChangeRate = field::common::U2;

    /// @brief Definition of "maxPhaseCorrRate" field.
    using maxPhaseCorrRate = field::common::U2T<comms::option::UnitsNanoseconds>;

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res2;

    /// @brief Definition of "freqTolerance" field.
    using freqTolerance = field::common::U2;

    /// @brief Definition of "timeTolerance" field.
    using timeTolerance = field::common::U2T<comms::option::UnitsNanoseconds>;

    /// @brief Definition of "messageCfg" field.
    struct messageCfg : public
        field::common::X2T<comms::option::BitmaskReservedBits<0xfff0, 0> >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS_SEQ macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS_SEQ(measInternal, measGNSS, measEXTINT0, measEXTINT1);
    };

    /// @brief Definition of "maxSlewRate" field.
    using maxSlewRate = field::common::U2T<comms::option::UnitsMicroseconds>;

    /// @brief Enumeration value for @ref TPCoherent field.
    enum class TPCoherentVal : std::uint8_t
    {
        Coherent, ///< Cogerent pulses
        NonCoherent, ///< Non-coherent pulses
        PostInitializationCoherent, ///< Post-initialization coherent pulses
        NumOfValues ///< Limit of available values
    };

    /// @brief Definition of "TPCoherent" member field of @ref flags bitfield.
    using TPCoherent =
        field::common::EnumT<
            TPCoherentVal,
            comms::option::FixedBitLength<2>,
            comms::option::ValidNumValueRange<0, (int)TPCoherentVal::NumOfValues - 1>
        >;

    /// @brief Definition of "flagshLow" member field of @ref flags bitfield.
    struct flagsLow : public
        field::common::X2T<
            comms::option::FixedBitLength<14>,
            comms::option::BitmaskReservedBits<0xc300, 0>
        >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS(
            disableInternal,
            disableExternal,
            preferenceMode,
            enableGNSS,
            enableEXTINT0,
            enableEXTINT1,
            enableHostMeasInt,
            enableHostMeasExt,
            useAnyFix=10,
            disableMaxSlewRate,
            issueFreqWarning,
            issueTimeWarning
        );

        /// @brief Provide convenience access functions for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS_ACCESS macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS_ACCESS(
            disableInternal,
            disableExternal,
            preferenceMode,
            enableGNSS,
            enableEXTINT0,
            enableEXTINT1,
            enableHostMeasInt,
            enableHostMeasExt,
            useAnyFix,
            disableMaxSlewRate,
            issueFreqWarning,
            issueTimeWarning);
    };

    /// @brief Definition of "flagshHigh" member field of @ref flags bitfield.
    struct flagsHigh : public
        field::common::X2T<
            comms::option::FixedBitLength<16>,
            comms::option::BitmaskReservedBits<0xfffe, 0>
        >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS_SEQ macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS_SEQ(disableOffset);
    };

    /// @brief Definition of "flags" field.
    struct flags : public
        field::common::BitfieldT<
            std::tuple<
                flagsLow,
                TPCoherent,
                flagsHigh
            >
        >
    {
        /// @brief Allow access to internal fields.
        /// @details See definition of @b COMMS_FIELD_MEMBERS_ACCESS macro
        ///     related to @b comms::field::Bitfield class from COMMS library
        ///     for details.
        COMMS_FIELD_MEMBERS_ACCESS(flagsLow, TPCoherent, flagsHigh);
    };

    // TODO: flags high and low.
    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        version,
        minGNSSFix,
        maxFreqChangeRate,
        maxPhaseCorrRate,
        reserved1,
        freqTolerance,
        timeTolerance,
        messageCfg,
        maxSlewRate,
        flags
    >;
};

/// @brief Definition of CFG-SMGR message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref CfgSmgrFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class CfgSmgr : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_SMGR>,
        comms::option::FieldsImpl<CfgSmgrFields::All>,
        comms::option::MsgType<CfgSmgr<TMsgBase> >
    >
{
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b version for @ref CfgSmgrFields::version field
    ///     @li @b minGNSSFix for @ref CfgSmgrFields::minGNSSFix field
    ///     @li @b maxFreqChangeRate for @ref CfgSmgrFields::maxFreqChangeRate field
    ///     @li @b maxPhaseCorrRate for @ref CfgSmgrFields::maxPhaseCorrRate field
    ///     @li @b reserved1 for @ref CfgSmgrFields::reserved1 field
    ///     @li @b freqTolerance for @ref CfgSmgrFields::freqTolerance field
    ///     @li @b timeTolerance for @ref CfgSmgrFields::timeTolerance field
    ///     @li @b messageCfg for @ref CfgSmgrFields::messageCfg field
    ///     @li @b maxSlewRate for @ref CfgSmgrFields::maxSlewRate field
    ///     @li @b flags for @ref CfgSmgrFields::flags field
    COMMS_MSG_FIELDS_ACCESS(
        version,
        minGNSSFix,
        maxFreqChangeRate,
        maxPhaseCorrRate,
        reserved1,
        freqTolerance,
        timeTolerance,
        messageCfg,
        maxSlewRate,
        flags
    );

    /// @brief Default constructor
    CfgSmgr() = default;

    /// @brief Copy constructor
    CfgSmgr(const CfgSmgr&) = default;

    /// @brief Move constructor
    CfgSmgr(CfgSmgr&& other) = default;

    /// @brief Destructor
    ~CfgSmgr() = default;

    /// @brief Copy assignment
    CfgSmgr& operator=(const CfgSmgr&) = default;

    /// @brief Move assignment
    CfgSmgr& operator=(CfgSmgr&&) = default;
};


}  // namespace message

}  // namespace ublox

