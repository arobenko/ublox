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
    struct rtcCalib : public
        field::common::X1T<
            comms::option::FixedBitLength<1>
        >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS(bit);
    };

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

    /// @brief Definition of "xtalAbsent" single bit bitmask member field of @ref flags bitfield.
    struct xtalAbsent : public
        field::common::X1T<
            comms::option::FixedBitLength<1>
        >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS(bit);
    };


    /// @brief Definition of "flags" field.
    struct flags : public
        field::common::BitfieldT<
            std::tuple<
                rtcCalib,
                safeBoot,
                jammingState,
                xtalAbsent,
                field::common::res1T<
                    comms::option::FixedBitLength<3>
                >
            >
        >
    {
        /// @brief Allow access to internal fields.
        /// @details See definition of @b COMMS_FIELD_MEMBERS_ACCESS macro
        ///     related to @b comms::field::Bitfield class from COMMS library
        ///     for details.
        COMMS_FIELD_MEMBERS_ACCESS(rtcCalib, safeBoot, jammingState, xtalAbsent, reserved);
    };

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res1;

    /// @brief Definition of "usedMask" field.
    using usedMask = field::common::X4;

    /// @brief Definition of "VP" field.
    /// @tparam TOpt Extra option(s)
    template <typename TOpt = comms::option::EmptyOption>
    using VP =
        field::common::ListT<
            field::common::U1,
            comms::option::SequenceFixedSize<17>,
            TOpt
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
    /// @tparam TOpt Extra option(s) for @ref VP field
    template <typename TOpt>
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
        VP<TOpt>,
        jamInd,
        reserved3,
        pinIrq,
        pullH,
        pullL
    >;
};

/// @brief Definition of MON-HW message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref MonHwFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
/// @tparam TVpOpt Extra option(s) for @b VP field
template <typename TMsgBase = Message, typename TVpOpt = comms::option::EmptyOption>
class MonHw : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_MON_HW>,
        comms::option::FieldsImpl<MonHwFields::All<TVpOpt> >,
        comms::option::MsgType<MonHw<TMsgBase, TVpOpt> >
    >
{
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b pinSel for @ref MonHwFields::pinSel field
    ///     @li @b pinBank for @ref MonHwFields::pinBank field
    ///     @li @b pinDir for @ref MonHwFields::pinDir field
    ///     @li @b pinVal for @ref MonHwFields::pinVal field
    ///     @li @b noisePerMS for @ref MonHwFields::noisePerMS field
    ///     @li @b agcCnt for @ref MonHwFields::agcCnt field
    ///     @li @b aStatus for @ref MonHwFields::aStatus field
    ///     @li @b aPower for @ref MonHwFields::aPower field
    ///     @li @b flags for @ref MonHwFields::flags field
    ///     @li @b reserved1 for @ref MonHwFields::reserved1 field
    ///     @li @b usedMask for @ref MonHwFields::usedMask field
    ///     @li @b VP for @ref MonHwFields::VP field
    ///     @li @b jamInd for @ref MonHwFields::jamInd field
    ///     @li @b reserved3 for @ref MonHwFields::reserved3 field
    ///     @li @b pinIrq for @ref MonHwFields::pinIrq field
    ///     @li @b pullH for @ref MonHwFields::pullH field
    ///     @li @b pullL for @ref MonHwFields::pullL field
    COMMS_MSG_FIELDS_ACCESS(
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
    );

    /// @brief Default constructor
    MonHw() = default;

    /// @brief Copy constructor
    MonHw(const MonHw&) = default;

    /// @brief Move constructor
    MonHw(MonHw&& other) = default;

    /// @brief Destructor
    ~MonHw() = default;

    /// @brief Copy assignment
    MonHw& operator=(const MonHw&) = default;

    /// @brief Move assignment
    MonHw& operator=(MonHw&&) = default;
};


}  // namespace message

}  // namespace ublox

