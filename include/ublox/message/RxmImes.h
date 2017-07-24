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
/// @brief Contains definition of RXM-IMES message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/rxm.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the RXM-IMES message fields.
/// @see RxmImes
struct RxmImesFields
{
    /// @brief Definition of "numTx" field.
    using numTx = field::common::U1;

    /// @brief Definition of "version" field.
    using version =
        field::common::U1T<
            comms::option::ValidNumValueRange<1, 1>,
            comms::option::DefaultNumValue<1>
        >;

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res2;

    /// @brief Definition of "reserved2" field.
    using reserved2 = field::common::res1;

    /// @brief Definition of "txId" field.
    using txId = field::common::U1;

    /// @brief Definition of "reserved3" field.
    using reserved3 = field::common::res3;

    /// @brief Definition of "cno" field.
    using cno = field::common::U1;

    /// @brief Definition of "reserved4" field.
    using reserved4 = field::common::res2;

    /// @brief Definition of "doppler" field.
    using doppler =
        field::common::I4T<
            comms::option::ScalingRatio<1, 0x1000>,
            comms::option::UnitsHertz
        >;

    /// @brief Definition of "pos1Floor" member field of @ref position1_1 bitfield.
    using pos1Floor = field::common::I1T<comms::option::FixedBitLength<8> >;

    /// @brief Definition of "pos1Lat" member field of @ref position1_1 bitfield.
    using pos1Lat =
        field::common::I4T<
            comms::option::FixedBitLength<23>,
            comms::option::ScalingRatio<180, 0x800000>,
            comms::option::UnitsDegrees
        >;

    /// @brief Definition of "position1_1" field.
    struct position1_1 : public
        field::common::BitfieldT<
            std::tuple<
                pos1Floor,
                pos1Lat,
                field::common::res1T<comms::option::FixedBitLength<1> >
            >
        >
    {
        /// @brief Allow access to internal fields.
        /// @details See definition of @b COMMS_FIELD_MEMBERS_ACCESS macro
        ///     related to @b comms::field::Bitfield class from COMMS library
        ///     for details.
        COMMS_FIELD_MEMBERS_ACCESS(pos1Floor, pos1Lat, reserved);
    };

    /// @brief Definition of "pos1Lon" member field of @ref position1_2 bitfield.
    using pos1Lon =
        field::common::I4T<
            comms::option::FixedBitLength<24>,
            comms::option::ScalingRatio<360, 0x1000000>,
            comms::option::UnitsDegrees
        >;

    /// @brief Definition of the remaining bits in @ref position1_2 bitfield as a
    ///     bitmask field.
    struct pos1Flags : public
        field::common::X1T<
            comms::option::FixedBitLength<8>,
            comms::option::BitmaskReservedBits<0xfe, 0>
        >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS_SEQ macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS_SEQ(pos1Valid);
    };

    /// @brief Definition of "position1_2" field.
    struct position1_2 : public
        field::common::BitfieldT<
            std::tuple<
                pos1Lon,
                pos1Flags
            >
        >
    {
        /// @brief Allow access to internal fields.
        /// @details See definition of @b COMMS_FIELD_MEMBERS_ACCESS macro
        ///     related to @b comms::field::Bitfield class from COMMS library
        ///     for details.
        COMMS_FIELD_MEMBERS_ACCESS(pos1Lon, pos1Flags);
    };

    /// @brief Definition of "pos2Floor" member field of @ref position2_1 bitfield.
    using pos2Floor = field::common::I2T<comms::option::FixedBitLength<9> >;

    /// @brief Definition of "pos2Alt" member field of @ref position2_1 bitfield.
    using pos2Alt =
        field::common::I2T<
            comms::option::FixedBitLength<12>,
            comms::option::UnitsMeters
        >;

    /// @brief Enumeration value for @ref pos2Acc field.
    enum class Pos2Acc : std::uint8_t
    {
        Undef, ///< undefinded
        LessThan_7m, ///< <7m
        LessThan_15m, ///< <15m
        GreatherThan_15m, ///< >15m
        NumOfValues ///< number of available values.
    };

    /// @brief Definition of "pos2Acc" member field of @ref position2_1 bitfield.
    using pos2Acc =
        field::common::EnumT<
            Pos2Acc,
            comms::option::ValidNumValueRange<0, (int)Pos2Acc::NumOfValues - 1>,
            comms::option::FixedBitLength<2>
        >;

    /// @brief Definition of the remaining bits in @ref position2_1 bitfield as a
    ///     bitmask field.
    struct pos2Flags : public
        field::common::X2T<
            comms::option::FixedBitLength<9>,
            comms::option::BitmaskReservedBits<0xfe, 0>
        >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS_SEQ macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS_SEQ(pos2Valid);
    };

    /// @brief Definition of "position2_1" field.
    struct position2_1 : public
        field::common::BitfieldT<
            std::tuple<
                pos2Floor,
                pos2Alt,
                pos2Acc,
                pos2Flags
            >
        >
    {
        /// @brief Allow access to internal fields.
        /// @details See definition of @b COMMS_FIELD_MEMBERS_ACCESS macro
        ///     related to @b comms::field::Bitfield class from COMMS library
        ///     for details.
        COMMS_FIELD_MEMBERS_ACCESS(pos2Floor, pos2Alt, pos2Acc, pos2Flags);
    };

    /// @brief Definition of "lat" field.
    using lat =
        field::common::I4T<
            comms::option::ScalingRatio<180, 0x1000000>,
            comms::option::UnitsDegrees
        >;

    /// @brief Definition of "lon" field.
    using lon =
        field::common::I4T<
            comms::option::ScalingRatio<360, 0x2000000>,
            comms::option::UnitsDegrees
        >;

    /// @brief Definition of "shortId" member field of @ref shortIdFrame bitfield.
    using shortId = field::common::U2T<comms::option::FixedBitLength<12> >;

    /// @brief Definition of the remaining bits in @ref shortIdFrame bitfield as a
    ///     bitmask field.
    struct shortIdFlags : public
        field::common::X4T<
            comms::option::FixedBitLength<20>,
            comms::option::BitmaskReservedBits<0xfffffffc, 0>
        >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS_SEQ macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS_SEQ(shortValid, shortBoundary);
    };

    /// @brief Definition of "shortIdFrame" field.
    struct shortIdFrame : public
        field::common::BitfieldT<
            std::tuple<
                shortId,
                shortIdFlags
            >
        >
    {
        /// @brief Allow access to internal fields.
        /// @details See definition of @b COMMS_FIELD_MEMBERS_ACCESS macro
        ///     related to @b comms::field::Bitfield class from COMMS library
        ///     for details.
        COMMS_FIELD_MEMBERS_ACCESS(shortId, shortIdFlags);
    };

    /// @brief Definition of "mediumIdLSB" field.
    using mediumIdLSB = field::common::U4;

    /// @brief Definition of "mediumId_2" field.
    struct mediumId_2 : public
        field::common::X4T<
            comms::option::BitmaskReservedBits<0xfffffff8, 0>
        >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS_SEQ macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS_SEQ(mediumIdMSB, mediumValid, mediumboundary);
    };

    /// @brief Definition of a single block of @ref data list
    struct block : public
        field::common::BundleT<
            std::tuple<
                reserved2,
                txId,
                reserved3,
                cno,
                reserved4,
                doppler,
                position1_1,
                position1_2,
                position2_1,
                lat,
                lon,
                shortIdFrame,
                mediumIdLSB,
                mediumId_2
            >
        >
    {
        /// @brief Allow access to internal fields.
        /// @details See definition of @b COMMS_FIELD_MEMBERS_ACCESS macro
        ///     related to @b comms::field::Bundle class from COMMS library
        ///     for details.
        COMMS_FIELD_MEMBERS_ACCESS(
            reserved2,
            txId,
            reserved3,
            cno,
            reserved4,
            doppler,
            position1_1,
            position1_2,
            position2_1,
            lat,
            lon,
            shortIdFrame,
            mediumIdLSB,
            mediumId_2
        );
    };

    /// @brief Definition of the list of blocks (@ref block)
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
        numTx,
        version,
        reserved1,
        data<TOpt>
    >;
};

/// @brief Definition of RXM-IMES message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref RxmImesFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TDataOpt Extra option(s) for @b data field
template <typename TMsgBase = Message, typename TDataOpt = comms::option::EmptyOption>
class RxmImes : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_RXM_IMES>,
        comms::option::FieldsImpl<RxmImesFields::All<TDataOpt> >,
        comms::option::MsgType<RxmImes<TMsgBase, TDataOpt> >,
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
    ///     @li @b numTx for @ref RxmImesFields::numTx field
    ///     @li @b version for @ref RxmImesFields::version field
    ///     @li @b reserved1 for @ref RxmImesFields::reserved1 field
    ///     @li @b data for @ref RxmImesFields::data field
    COMMS_MSG_FIELDS_ACCESS(numTx, version, reserved1, data);

    /// @brief Default constructor
    RxmImes() = default;

    /// @brief Copy constructor
    RxmImes(const RxmImes&) = default;

    /// @brief Move constructor
    RxmImes(RxmImes&& other) = default;

    /// @brief Destructor
    ~RxmImes() = default;

    /// @brief Copy assignment
    RxmImes& operator=(const RxmImes&) = default;

    /// @brief Move assignment
    RxmImes& operator=(RxmImes&&) = default;

    /// @brief Provides custom read functionality.
    /// @details Number of elements in @ref RxmImesFields::data depends on
    ///     the value in @ref RxmImesFields::numTx
    template <typename TIter>
    comms::ErrorStatus doRead(TIter& iter, std::size_t len)
    {
        using Base = typename std::decay<decltype(comms::toMessageBase(*this))>::type;
        auto es = Base::template readFieldsUntil<FieldIdx_data>(iter, len);
        if (es != comms::ErrorStatus::Success) {
            return es;
        }

        field_data().forceReadElemCount(field_numTx().value());
        return Base::template readFieldsFrom<FieldIdx_data>(iter, len);
    }

    /// @brief Provides custom refresh functionality
    /// @details The value of @ref RxmImesFields::numTx field depends on
    ///     actual number of elements in @ref RxmImesFields::data.
    bool doRefresh()
    {
        if (field_numTx().value() == field_data().value().size()) {
            return false;
        }

        field_numTx().value() = field_data().value().size();
        return true;
    }

};


}  // namespace message

}  // namespace ublox





