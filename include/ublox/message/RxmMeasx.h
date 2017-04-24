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
/// @brief Contains definition of RXM-MEASX message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/rxm.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the RXM-MEASX message fields.
/// @see RxmMeasx
struct RxmMeasxFields
{
    /// @brief Definition of "version" field.
    using version =
        field::common::U1T<
            comms::option::ValidNumValueRange<0, 0>
        >;

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res3;

    /// @brief Definition of "gpsTOW" field.
    using gpsTOW = field::rxm::iTOW;

    /// @brief Definition of "gloTOW" field.
    using gloTOW = field::rxm::iTOW;

    /// @brief Definition of "bdsTOW" field.
    using bdsTOW = field::rxm::iTOW;

    /// @brief Definition of "reserved2" field.
    using reserved2 = field::common::res4;

    /// @brief Definition of "qzssTOW" field.
    using qzssTOW = field::rxm::iTOW;

    /// @brief Definition of "gpsTOWacc" field.
    using gpsTOWacc =
        field::common::U2T<
            comms::option::ScalingRatio<1, 0x10>,
            comms::option::UnitsMilliseconds
        >;

    /// @brief Definition of "gloTOWacc" field.
    using gloTOWacc = gpsTOWacc;

    /// @brief Definition of "bdsTOWacc" field.
    using bdsTOWacc = gpsTOWacc;

    /// @brief Definition of "reserved3" field.
    using reserved3 = field::common::res2;

    /// @brief Definition of "qzssTOWacc" field.
    using qzssTOWacc = gpsTOWacc;

    /// @brief Definition of "numSV" field.
    using numSV = field::common::U1;

    /// @brief Enumeration value for @ref towSet field.
    enum class TowSet : std::uint8_t
    {
        No, ///< no
        Yes, ///< yes
        Yes2, ///< yes
        NumOfValues ///< number of available values
    };

    /// @brief Definition of "towSet" member field of @ref flags bitfield.
    using towSet =
        field::common::EnumT<
            TowSet,
            comms::option::ValidNumValueRange<0, (int)TowSet::NumOfValues - 1>,
            comms::option::FixedBitLength<2>
        >;

    /// @brief Definition of "flags" field.
    struct flags : public
        field::common::BitfieldT<
            std::tuple<
                towSet,
                field::common::res1T<comms::option::FixedBitLength<6> >
            >
        >
    {
        /// @brief Allow access to internal fields.
        /// @details See definition of @b COMMS_FIELD_MEMBERS_ACCESS macro
        ///     related to @b comms::field::Bitfield class from COMMS library
        ///     for details.
        COMMS_FIELD_MEMBERS_ACCESS(towSet, reserved);
    };

    /// @brief Definition of "reserved4" field.
    using reserved4 = field::common::res4;

    /// @brief Definition of "reserved5" field.
    using reserved5 = field::common::res4;

    /// @brief Definition of "gnssId" field.
    using gnssId = field::common::gnssId;

    /// @brief Definition of "svId" field.
    using svId = field::common::U1;

    /// @brief Definition of "cNo" field.
    using cNo =
        field::common::U1T<
            comms::option::ValidNumValueRange<0, 63>
        >;

    /// @brief Enumeration value for @ref mpathIndic field.
    enum class MpathIndic : std::uint8_t
    {
        NotMeasured, ///< not measured
        Low, ///< low
        Medium, ///< medium
        High, ///< high
        NumOfValues ///< number of available values
    };

    /// @brief Definition of "mpathIndic" field.
    using mpathIndic =
        field::common::EnumT<
            MpathIndic,
            comms::option::ValidNumValueRange<0, (int)MpathIndic::NumOfValues - 1>
        >;

    /// @brief Definition of "dopplerMS" field.
    using dopplerMS =
        field::common::I4T<
            comms::option::ScalingRatio<4, 100>,
            comms::option::UnitsMetersPerSecond
        >;

    /// @brief Definition of "dopplerHZ" field.
    using dopplerHZ =
        field::common::I4T<
            comms::option::ScalingRatio<2, 10>,
            comms::option::UnitsHertz
        >;

    /// @brief Definition of "wholeChips" field.
    using wholeChips =
        field::common::U2T<
            comms::option::ValidNumValueRange<0, 1022>
        >;

    /// @brief Definition of "fracChips" field.
    using fracChips =
        field::common::U2T<
            comms::option::ValidNumValueRange<0, 1023>
        >;

    /// @brief Definition of "codePhase" field.
    using codePhase =
        field::common::U4T<
            comms::option::ScalingRatio<1, 0x200000>,
            comms::option::UnitsMilliseconds
        >;

    /// @brief Definition of "intCodePhase" field.
    using intCodePhase =
        field::common::U1T<
            comms::option::UnitsMilliseconds
        >;

    /// @brief Definition of "pseuRangeRMSErr" field.
    using pseuRangeRMSErr =
        field::common::U1T<
            comms::option::ValidNumValueRange<0, 63>
        >;

    /// @brief Definition of "reserved6" field.
    using reserved6 = field::common::res2;

    /// @brief Definition of a single block of @ref data list
    struct block : public
        field::common::BundleT<
            std::tuple<
                gnssId,
                svId,
                cNo,
                mpathIndic,
                dopplerMS,
                dopplerHZ,
                wholeChips,
                fracChips,
                codePhase,
                intCodePhase,
                pseuRangeRMSErr,
                reserved6
            >
        >
    {
        /// @brief Allow access to internal fields.
        /// @details See definition of @b COMMS_FIELD_MEMBERS_ACCESS macro
        ///     related to @b comms::field::Bundle class from COMMS library
        ///     for details.
        COMMS_FIELD_MEMBERS_ACCESS(
            gnssId,
            svId,
            cNo,
            mpathIndic,
            dopplerMS,
            dopplerHZ,
            wholeChips,
            fracChips,
            codePhase,
            intCodePhase,
            pseuRangeRMSErr,
            reserved6
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
        version,
        reserved1,
        gpsTOW,
        gloTOW,
        bdsTOW,
        reserved2,
        qzssTOW,
        gpsTOWacc,
        gloTOWacc,
        bdsTOWacc,
        reserved3,
        qzssTOWacc,
        numSV,
        flags,
        reserved4,
        reserved5,
        data<TOpt>
    >;
};

/// @brief Definition of RXM-MEASX message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref RxmMeasxFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TDataOpt Extra option(s) for @b data field
template <typename TMsgBase = Message, typename TDataOpt = comms::option::EmptyOption>
class RxmMeasx : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_RXM_MEASX>,
        comms::option::FieldsImpl<RxmMeasxFields::All<TDataOpt> >,
        comms::option::MsgType<RxmMeasx<TMsgBase, TDataOpt> >,
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
    ///     @li @b version for @ref RxmMeasxFields::version field
    ///     @li @b reserved1 for @ref RxmMeasxFields::reserved1 field
    ///     @li @b gpsTOW for @ref RxmMeasxFields::gpsTOW field
    ///     @li @b gloTOW for @ref RxmMeasxFields::gloTOW field
    ///     @li @b bdsTOW for @ref RxmMeasxFields::bdsTOW field
    ///     @li @b reserved2 for @ref RxmMeasxFields::reserved2 field
    ///     @li @b qzssTOW for @ref RxmMeasxFields::qzssTOW field
    ///     @li @b gpsTOWacc for @ref RxmMeasxFields::gpsTOWacc field
    ///     @li @b gloTOWacc for @ref RxmMeasxFields::gloTOWacc field
    ///     @li @b bdsTOWacc for @ref RxmMeasxFields::bdsTOWacc field
    ///     @li @b reserved3 for @ref RxmMeasxFields::reserved3 field
    ///     @li @b qzssTOWacc for @ref RxmMeasxFields::qzssTOWacc field
    ///     @li @b numSV for @ref RxmMeasxFields::numSV field
    ///     @li @b flags for @ref RxmMeasxFields::flags field
    ///     @li @b reserved4 for @ref RxmMeasxFields::reserved4 field
    ///     @li @b reserved5 for @ref RxmMeasxFields::reserved5 field
    ///     @li @b data for @ref RxmMeasxFields::data field
    COMMS_MSG_FIELDS_ACCESS(
        version,
        reserved1,
        gpsTOW,
        gloTOW,
        bdsTOW,
        reserved2,
        qzssTOW,
        gpsTOWacc,
        gloTOWacc,
        bdsTOWacc,
        reserved3,
        qzssTOWacc,
        numSV,
        flags,
        reserved4,
        reserved5,
        data
    );

    /// @brief Default constructor
    RxmMeasx() = default;

    /// @brief Copy constructor
    RxmMeasx(const RxmMeasx&) = default;

    /// @brief Move constructor
    RxmMeasx(RxmMeasx&& other) = default;

    /// @brief Destructor
    ~RxmMeasx() = default;

    /// @brief Copy assignment
    RxmMeasx& operator=(const RxmMeasx&) = default;

    /// @brief Move assignment
    RxmMeasx& operator=(RxmMeasx&&) = default;

    /// @brief Provides custom read functionality.
    /// @details Number of elements in @ref RxmMeasxFields::data depends on
    ///     the value in @ref RxmMeasxFields::numSV
    template <typename TIter>
    comms::ErrorStatus doRead(TIter& iter, std::size_t len)
    {
        using Base = typename std::decay<decltype(comms::toMessageBase(*this))>::type;
        auto es = Base::template readFieldsUntil<FieldIdx_data>(iter, len);
        if (es != comms::ErrorStatus::Success) {
            return es;
        }

        field_data().forceReadElemCount(field_numSV().value());
        return Base::template readFieldsFrom<FieldIdx_data>(iter, len);
    }

    /// @brief Provides custom refresh functionality
    /// @details The value of @ref RxmMeasxFields::numSV field depends on
    ///     actual number of elements in @ref RxmMeasxFields::data.
    bool doRefresh()
    {
        if (field_numSV().value() == field_data().value().size()) {
            return false;
        }

        field_numSV().value() = field_data().value().size();
        return true;
    }

};


}  // namespace message

}  // namespace ublox





