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
/// @brief Contains definition of MON-HW message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the MON-HW message fields.
/// @see MonHw
struct MonHwFields
{
    /// @brief Value enumeration for @ref aStatus field.
    enum class AStatus : std::uint8_t
    {
        INIT, ///< INIT
        DONTKNOW, ///< DONTKNOW
        OK, ///< OK
        SHORT, ///< SHORT
        OPEN, ///< OPEN
        NumOfValues ///< number of available values
    };

    /// @brief Value enumeration for @ref aPower field.
    enum class APower : std::uint8_t
    {
        OFF, ///< OFF
        ON, ///< ON
        DONTKNOW, ///< DONTKNOW
        NumOfValues ///< number of available values
    };

    /// @brief Value enumration for @ref safeBoot field
    enum class SafeBoot : std::uint8_t
    {
        Inactive, ///< inactive
        Active, ///< active
        NumOfValues ///< number of available values
    };

    /// @brief Value enumeration for @ref jammingState field
    enum class JammingState : std::uint8_t
    {
        Unknown, ///< unknown of feature disabled
        Ok, ///< ok - no jamming
        Warning, ///< warning - interference visible but fix OK
        Critical, ///< critical - interference visible and no fix
        NumOfValues ///< number of available values
    };

    /// @brief Use this enumeration to access member fields of @ref flags bitfield.
    enum
    {
        flags_rtcCalib, ///< index of @ref rtcCalib member field
        flags_safeBoot, ///< index of @ref safeBoot member field
        flags_jammingState, ///< index of @ref jammingState member field
        flags_numOfValues = flags_jammingState + 2 ///< number of member fields
    };

    /// @brief Bits access enumeration for bits in @b rtcCalib member of
    ///     @ref flags bitfield field.
    enum
    {
        rtcCalib_bit, ///< single bit index
        rtcCalib_numOfValues ///< number of available bits
    };

    /// @brief Definition of "pinSel" field.
    using pinSel = field::common::X4;

    /// @brief Definition of "pinBank" field.
    using pinBank = field::common::X4;

    /// @brief Definition of "pinDir" field.
    using pinDir = field::common::X4;

    /// @brief Definition of "pinVal" field.
    using pinVal = field::common::X4;

    /// @brief Definition of "noisePerMS" field.
    using noisePerMS = field::common::U2;

    /// @brief Definition of "agcCnt" field.
    using agcCnt = field::common::U2T<comms::option::ValidNumValueRange<0, 8191> >;

    /// @brief Definition of "aStatus" field.
    using aStatus =
        field::common::EnumT<
            AStatus,
            comms::option::ValidNumValueRange<0, (int)AStatus::NumOfValues - 1>
        >;

    /// @brief Definition of "aPower" field.
    using aPower =
        field::common::EnumT<
            APower,
            comms::option::ValidNumValueRange<0, (int)APower::NumOfValues - 1>
        >;

    /// @brief Definition of "rtcCalib" single bit bitmask member field of @ref flags bitfield.
    using rtcCalib =
        field::common::X1T<
            comms::option::FixedBitLength<1>
        >;

    /// @brief Definition of "safeBoot" member field of @ref flags bitfield.
    using safeBoot =
        field::common::EnumT<
            SafeBoot,
            comms::option::ValidNumValueRange<0, (int)SafeBoot::NumOfValues - 1>,
            comms::option::FixedBitLength<1>
        >;

    /// @brief Definition of "jamingState" member field of @ref flags bitfield.
    using jammingState =
        field::common::EnumT<
            JammingState,
            comms::option::ValidNumValueRange<0, (int)JammingState::NumOfValues - 1>,
            comms::option::FixedBitLength<2>
        >;

    /// @brief Definition of "flags" field.
    using flags =
        field::common::BitfieldT<
            std::tuple<
                rtcCalib,
                safeBoot,
                jammingState,
                field::common::res1T<
                    comms::option::FixedBitLength<4>
                >
            >
        >;

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res1;

    /// @brief Definition of "usedMask" field.
    using usedMask = field::common::X4;

    /// @brief Definition of "VP" field.
    using VP =
        field::common::ListT<
            field::common::U1,
            comms::option::SequenceFixedSize<17>
        >;

    /// @brief Definition of "jamInd" field.
    using jamInd = field::common::U1;

    /// @brief Definition of "reserved3" field.
    using reserved3 = field::common::res2;

    /// @brief Definition of "pinIrq" field.
    using pinIrq = field::common::X4;

    /// @brief Definition of "pullH" field.
    using pullH = field::common::X4;

    /// @brief Definition of "pullL" field.
    using pullL = field::common::X4;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        pinSel,
        pinBank,
        pinDir,
        pinVal,
        noisePerMS,
        agcCnt,
        aStatus,
        aPower,
        flags,
        reserved1,
        usedMask,
        VP,
        jamInd,
        reserved3,
        pinIrq,
        pullH,
        pullL
    >;
};

/// @brief Definition of MON-HW message
/// @details Inherits from
///     <a href="https://dl.dropboxusercontent.com/u/46999418/comms_champion/comms/html/classcomms_1_1MessageBase.html">comms::MessageBase</a>
///     while providing @b TMsgBase as common interface class as well as
///     @b comms::option::StaticNumIdImpl, @b comms::option::FieldsImpl, and
///     @b comms::option::DispatchImpl as options. @n
///     See @ref MonHwFields and for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class MonHw : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_MON_HW>,
        comms::option::FieldsImpl<MonHwFields::All>,
        comms::option::DispatchImpl<MonHw<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_MON_HW>,
        comms::option::FieldsImpl<MonHwFields::All>,
        comms::option::DispatchImpl<MonHw<TMsgBase> >
    > Base;
public:

    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_pinSel, ///< @b pinSel field, see @ref MonHwFields::pinSel
        FieldIdx_pinBank, ///< @b pinBank field, see @ref MonHwFields::pinBank
        FieldIdx_pinDir, ///< @b pinDir field, see @ref MonHwFields::pinDir
        FieldIdx_pinVal, ///< @b pinVal field, see @ref MonHwFields::pinVal
        FieldIdx_noisePerMS, ///< @b noisePerMS field, see @ref MonHwFields::noisePerMS
        FieldIdx_agcCnt, ///< @b agcCnt field, see @ref MonHwFields::agcCnt
        FieldIdx_aStatus, ///< @b aStatus field, see @ref MonHwFields::aStatus
        FieldIdx_aPower, ///< @b aPower field, see @ref MonHwFields::aPower
        FieldIdx_flags, ///< @b flags field, see @ref MonHwFields::flags
        FieldIdx_reserved1, ///< @b reserved1 field, see @ref MonHwFields::reserved1
        FieldIdx_usedMask, ///< @b usedMask field, see @ref MonHwFields::usedMask
        FieldIdx_VP, ///< @b VP field, see @ref MonHwFields::VP
        FieldIdx_jamInd, ///< @b jamInd field, see @ref MonHwFields::jamInd
        FieldIdx_reserved3, ///< @b reserved3 field, see @ref MonHwFields::reserved3
        FieldIdx_pinIrq, ///< @b pinIrq field, see @ref MonHwFields::pinIrq
        FieldIdx_pullH, ///< @b pullH field, see @ref MonHwFields::pullH
        FieldIdx_pullL, ///< @b pullL field, see @ref MonHwFields::pullL
        FieldIdx_numOfValues ///< number of available fields
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    /// @brief Default constructor
    MonHw() = default;

    /// @brief Copy constructor
    MonHw(const MonHw&) = default;

    /// @brief Move constructor
    MonHw(MonHw&& other) = default;

    /// @brief Destructor
    virtual ~MonHw() = default;

    /// @brief Copy assignment
    MonHw& operator=(const MonHw&) = default;

    /// @brief Move assignment
    MonHw& operator=(MonHw&&) = default;
};


}  // namespace message

}  // namespace ublox

