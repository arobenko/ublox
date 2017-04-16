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
/// @brief Contains definition of RXM-RAWX message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/rxm.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the RXM-RAWX message fields.
/// @see RxmRawx
struct RxmRawxFields
{
    /// @brief Definition of "rcvTow" field.
    using rcvTow = field::common::R8T<comms::option::UnitsSeconds>;

    /// @brief Definition of "week" field.
    using week = field::common::U2T<comms::option::UnitsWeeks>;

    /// @brief Definition of "leapS" field.
    using leapS = field::common::I1T<comms::option::UnitsSeconds>;

    /// @brief Definition of "numMeas" field.
    using numMeas = field::common::U1;

    /// @brief Definition of "recStat" field.
    struct recStat : public
        field::common::X1T<
            comms::option::BitmaskReservedBits<0xfc, 0>
        >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS(leapSec, clkReset);
    };

    /// @brief Definition of "version" field.
    using version =
        field::common::U1T<
            comms::option::ValidNumValueRange<0, 1>
        >;

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res2;

    /// @brief Definition of "prMes" field.
    using prMes = field::common::R8T<comms::option::UnitsMeters>;

    /// @brief Definition of "cpMes" field.
    using cpMes = field::common::R8;

    /// @brief Definition of "doMes" field.
    using doMes = field::common::R4T<comms::option::UnitsHertz>;

    /// @brief Definition of "gnssId" field.
    using gnssId = field::common::gnssId;

    /// @brief Definition of "svId" field.
    using svId = field::common::U1;

    /// @brief Definition of "reserved2" field.
    using reserved2 = field::common::res1;

    /// @brief Definition of "freqId" field.
    using freqId =
        field::common::U1T<
            comms::option::ValidNumValueRange<0, 13>
        >;

    /// @brief Definition of "locktime" field.
    using locktime =
        field::common::U2T<
            comms::option::ValidNumValueRange<0, 64500>,
            comms::option::UnitsMilliseconds
        >;

    /// @brief Definition of "cno" field.
    using cno = field::common::U1;

    /// @brief Definition of "prStdev" field.
    using prStdev = field::common::U1T<comms::option::UnitsMeters>;

    /// @brief Definition of "cpStdev" field.
    using cpStdev = field::common::U1T<comms::option::ScalingRatio<4, 1000> >;

    /// @brief Definition of "doStdev" field.
    using doStdev = field::common::U1T<comms::option::UnitsHertz>;

    /// @brief Definition of "trkStat" field.
    struct trkStat : public
        field::common::X1T<
            comms::option::BitmaskReservedBits<0xf0, 0>
        >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS(prValid, cpValid, halfCyc, subHalfCyc);
    };

    /// @brief Definition of "reserved3" field.
    using reserved3 = field::common::res1;


    /// @brief Definition of a single block of @ref data
    struct block : public
        field::common::BundleT<
            std::tuple<
                prMes,
                cpMes,
                doMes,
                gnssId,
                svId,
                reserved2,
                freqId,
                locktime,
                cno,
                prStdev,
                cpStdev,
                doStdev,
                trkStat,
                reserved3
            >
        >
    {
        /// @brief Allow access to internal fields.
        /// @details See definition of @b COMMS_FIELD_MEMBERS_ACCESS macro
        ///     related to @b comms::field::Bitfield class from COMMS library
        ///     for details.
        COMMS_FIELD_MEMBERS_ACCESS(
            prMes,
            cpMes,
            doMes,
            gnssId,
            svId,
            reserved2,
            freqId,
            locktime,
            cno,
            prStdev,
            cpStdev,
            doStdev,
            trkStat,
            reserved3
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
        rcvTow,
        week,
        leapS,
        numMeas,
        recStat,
        version,
        reserved1,
        data<TOpt>
    >;
};

/// @brief Definition of RXM-RAWX message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref RxmRawxFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
/// @tparam TDataOpt Extra option(s) for @b data field
template <typename TMsgBase = Message, typename TDataOpt = comms::option::EmptyOption>
class RxmRawx : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_RXM_RAWX>,
        comms::option::FieldsImpl<RxmRawxFields::All<TDataOpt> >,
        comms::option::MsgType<RxmRawx<TMsgBase, TDataOpt> >,
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
    ///     @li @b rcvTow for @ref RxmRawxFields::rcvTow field
    ///     @li @b week for @ref RxmRawxFields::week field
    ///     @li @b leapS for @ref RxmRawxFields::leapS field
    ///     @li @b numMeas for @ref RxmRawxFields::numMeas field
    ///     @li @b recStat for @ref RxmRawxFields::recStat field
    ///     @li @b version for @ref RxmRawxFields::version field
    ///     @li @b reserved1 for @ref RxmRawxFields::reserved1 field
    ///     @li @b data for @ref RxmRawxFields::data field
    COMMS_MSG_FIELDS_ACCESS(
        rcvTow,
        week,
        leapS,
        numMeas,
        recStat,
        version,
        reserved1,
        data);

    /// @brief Default constructor
    RxmRawx() = default;

    /// @brief Copy constructor
    RxmRawx(const RxmRawx&) = default;

    /// @brief Move constructor
    RxmRawx(RxmRawx&& other) = default;

    /// @brief Destructor
    ~RxmRawx() = default;

    /// @brief Copy assignment
    RxmRawx& operator=(const RxmRawx&) = default;

    /// @brief Move assignment
    RxmRawx& operator=(RxmRawx&&) = default;

    /// @brief Provides custom read functionality.
    /// @details The number of blocks in @b data (@ref RxmRawxFields::data) list
    ///     is determined by the value of @b numMeas (@ref RxmRawxFields::numMeas) field.
    template <typename TIter>
    comms::ErrorStatus doRead(TIter& iter, std::size_t len)
    {
        typedef typename std::decay<decltype(comms::toMessageBase(*this))>::type Base;
        auto es = Base::template readFieldsUntil<FieldIdx_data>(iter, len);
        if (es != comms::ErrorStatus::Success) {
            return es;
        }

        field_data().forceReadElemCount(field_numMeas().value());
        return Base::template readFieldsFrom<FieldIdx_data>(iter, len);
    }

    /// @brief Provides custom refresh functionality
    /// @details The value of @b numMeas (@ref RxmRawxFields::numMeas) field is determined
    ///     by the amount of blocks stored in @b data (@ref RxmRawxFields::data) list.
    /// @return @b true in case the value of "numMeas" field was modified, @b false otherwise
    bool doRefresh()
    {
        if (field_numMeas().value() == field_data().value().size()) {
            return false;
        }

        field_numMeas().value() = field_data().value().size();
        return true;
    }

};


}  // namespace message

}  // namespace ublox





