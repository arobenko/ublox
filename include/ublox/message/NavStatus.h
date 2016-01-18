//
// Copyright 2015 (C). Alex Robenko. All rights reserved.
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


#pragma once

#include "comms/Message.h"
#include "ublox/Message.h"

#include "ublox/field/nav.h"

namespace ublox
{

namespace message
{

enum
{
    NavStatusField_flags_gpsFixOK,
    NavStatusField_flags_diffSoln,
    NavStatusField_flags_wknSet,
    NavStatusField_flags_towSet,
    NavStatusField_flags_numOfValues
};

enum class DgpsIStat : std::uint8_t
{
    None,
    PR_PRR_Correction,
    NumOfValues
};

enum class MapMatching : std::uint8_t
{
    None,
    Valid,
    Used,
    DR,
    NumOfValues
};

enum class PsmState : std::uint8_t
{
    Acquisition,
    Tracking,
    PowerOptimizedTracking,
    Inactive,
    NumOfValues
};

enum
{
    NavStatusField_fixStat_dgpsIStat,
    NavStatusField_fixStat_reserved,
    NavStatusField_fixStat_mapMatching,
    NavStatusField_fixStat_numOfValues
};

enum
{
    NavStatusField_flags2_psmState,
    NavStatusField_flags2_reserved,
    NavStatusField_flags2_numOfValues
};


using NavStatusField_iTOW = field::nav::iTOW;
using NavStatusField_gpsFix = field::nav::gpsFix;
using NavStatusField_flags =
    field::common::X1T<
        comms::option::BitmaskReservedBits<0xf0, 0>
    >;
using NavStatusField_fixStat =
    comms::field::Bitfield<
        field::common::FieldBase,
        std::tuple<
            comms::field::EnumValue<
                field::common::FieldBase,
                PsmState,
                comms::option::ValidNumValueRange<0, (int)PsmState::NumOfValues - 1>,
                comms::option::FixedBitLength<1>
            >,
            comms::field::IntValue<
                field::common::FieldBase,
                std::uint8_t,
                comms::option::ValidNumValueRange<0, 0>,
                comms::option::FixedBitLength<5>
            >,
            comms::field::EnumValue<
                field::common::FieldBase,
                MapMatching,
                comms::option::ValidNumValueRange<0, (int)MapMatching::NumOfValues - 1>,
                comms::option::FixedBitLength<2>
            >
        >
    >;

using NavStatusField_flags2 =
    comms::field::Bitfield<
        field::common::FieldBase,
        std::tuple<
            comms::field::EnumValue<
                field::common::FieldBase,
                PsmState,
                comms::option::ValidNumValueRange<0, (int)PsmState::NumOfValues - 1>,
                comms::option::FixedBitLength<2>
            >,
            comms::field::IntValue<
                field::common::FieldBase,
                std::uint8_t,
                comms::option::ValidNumValueRange<0, 0>,
                comms::option::FixedBitLength<6>
            >
        >
    >;

using NavStatusField_ttff = field::common::U4T<field::common::Scaling_ms2s>;
using NavStatusField_msss = field::common::U4T<field::common::Scaling_ms2s>;

using NavStatusFields = std::tuple<
    NavStatusField_iTOW,
    NavStatusField_gpsFix,
    NavStatusField_flags,
    NavStatusField_fixStat,
    NavStatusField_flags2,
    NavStatusField_ttff,
    NavStatusField_msss
>;


template <typename TMsgBase = Message>
class NavStatus : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_STATUS>,
        comms::option::FieldsImpl<NavStatusFields>,
        comms::option::DispatchImpl<NavStatus<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_STATUS>,
        comms::option::FieldsImpl<NavStatusFields>,
        comms::option::DispatchImpl<NavStatus<TMsgBase> >
    > Base;
public:

    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_iTOW,
        FieldIdx_gpsFix,
        FieldIdx_flags,
        FieldIdx_fixStat,
        FieldIdx_flags2,
        FieldIdx_ttff,
        FieldIdx_msss,
        FieldIdx_numOfValues ///< number of available fields
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    /// @brief Default constructor
    NavStatus() = default;

    /// @brief Copy constructor
    NavStatus(const NavStatus&) = default;

    /// @brief Move constructor
    NavStatus(NavStatus&& other) = default;

    /// @brief Destructor
    virtual ~NavStatus() = default;

    /// @brief Copy assignment
    NavStatus& operator=(const NavStatus&) = default;

    /// @brief Move assignment
    NavStatus& operator=(NavStatus&&) = default;
};


}  // namespace message

}  // namespace ublox





