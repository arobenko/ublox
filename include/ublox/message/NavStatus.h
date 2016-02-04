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
/// @brief Contains definition of NAV-STATUS message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/nav.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the NAV-STATUS message fields.
/// @see NavStatus
struct NavStatusFields
{
    /// @brief Bits access enumeration for bits in @b flags bitmask field.
    enum
    {
        flags_gpsFixOK, ///< @b gpsFixOk bit index
        flags_diffSoln, ///< @b diffSoln bit index
        flags_wknSet, ///< @b wknSen bit index
        flags_towSet, ///< @b towSet bit index
        flags_numOfValues ///< number of available bits
    };

    /// @brief Value enumeration for @ref dgpsIStat field
    enum class DgpsIStat : std::uint8_t
    {
        None, ///< none
        PR_PRR_Correction, ///< PR + PRR correction
        NumOfValues ///< number of available values
    };

    /// @brief Value enumeration for @ref mapMatching field
    enum class MapMatching : std::uint8_t
    {
        None, ///< none
        Valid, ///< valid
        Used, ///< used
        DR, ///< DR
        NumOfValues ///< number of available values
    };

    /// @brief Value enumeration for @ref psmState field.
    enum class PsmState : std::uint8_t
    {
        Acquisition, ///< ACKQUISITION
        Tracking, ///< TRACKING
        PowerOptimizedTracking, ///< POWER OPTIMIZED TRACKING
        Inactive, ///< INACTIVE
        NumOfValues ///< number of available values
    };

    /// @brief Use this enumeration to access member fields of @ref fixStat bitfield.
    enum
    {
        fixStat_dgpsIStat, ///< index of @ref dgpsIStat member field
        fixStat_mapMatching = fixStat_dgpsIStat + 2,  ///< index of @ref mapMatching member field
        fixStat_numOfValues ///< number of available member fields
    };

    /// @brief Use this enumeration to access member fields of @ref flags2 bitfield.
    enum
    {
        flags2_psmState, ///< index of @ref psmState member field
        flags2_numOfValues = flags2_psmState + 2 ///< number of available member fields
    };


    /// @brief Definition of "iTOW" field.
    using iTOW = field::nav::iTOW;

    /// @brief Definition of "gpsFix" field.
    using gpsFix = field::nav::gpsFix;

    /// @brief Definition of "flags" field.
    using flags =
        field::common::X1T<
            comms::option::BitmaskReservedBits<0xf0, 0>
        >;

    /// @brief Definition of "dgpsIStat" member fields of @ref fixStat bitfield.
    using dgpsIStat =
        field::common::EnumT<
            PsmState,
            comms::option::ValidNumValueRange<0, (int)PsmState::NumOfValues - 1>,
            comms::option::FixedBitLength<1>
        >;

    /// @brief Definition of "mapMatching" member fields of @ref fixStat bitfield.
    using mapMatching =
        field::common::EnumT<
            MapMatching,
            comms::option::ValidNumValueRange<0, (int)MapMatching::NumOfValues - 1>,
            comms::option::FixedBitLength<2>
        >;

    /// @brief Definition of "fixStat" field.
    using fixStat =
        field::common::BitfieldT<
            std::tuple<
                dgpsIStat,
                field::common::res1T<
                    comms::option::FixedBitLength<5>
                >,
                mapMatching
            >
        >;

    /// @brief Definition of "psmState" member fields of @ref flags2 bitfield.
    using psmState =
        field::common::EnumT<
            PsmState,
            comms::option::ValidNumValueRange<0, (int)PsmState::NumOfValues - 1>,
            comms::option::FixedBitLength<2>
        >;

    /// @brief Definition of "flags2" field.
    using flags2 =
        field::common::BitfieldT<
            std::tuple<
                psmState,
                field::common::res1T<
                    comms::option::FixedBitLength<6>
                >
            >
        >;

    /// @brief Definition of "ttff" field.
    using ttff = field::common::U4T<field::common::Scaling_ms2s>;

    /// @brief Definition of "msss" field.
    using msss = field::common::U4T<field::common::Scaling_ms2s>;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        iTOW,
        gpsFix,
        flags,
        fixStat,
        flags2,
        ttff,
        msss
    >;
};

/// @brief Definition of NAV-STATUS message
/// @details Inherits from
///     <a href="https://dl.dropboxusercontent.com/u/46999418/comms_champion/comms/html/classcomms_1_1MessageBase.html">comms::MessageBase</a>
///     while providing @b TMsgBase as common interface class as well as
///     @b comms::option::StaticNumIdImpl, @b comms::option::FieldsImpl, and
///     @b comms::option::DispatchImpl as options. @n
///     See @ref NavStatusFields and for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class NavStatus : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_STATUS>,
        comms::option::FieldsImpl<NavStatusFields::All>,
        comms::option::DispatchImpl<NavStatus<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_STATUS>,
        comms::option::FieldsImpl<NavStatusFields::All>,
        comms::option::DispatchImpl<NavStatus<TMsgBase> >
    > Base;
public:

    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_iTOW, ///< @b iTOW field, see @ref NavStatusFields::iTOW
        FieldIdx_gpsFix, ///< @b gpsFix field, see @ref NavStatusFields::gpsFix
        FieldIdx_flags, ///< @b flags field, see @ref NavStatusFields::flags
        FieldIdx_fixStat, ///< @b fixStat field, see @ref NavStatusFields::fixStat
        FieldIdx_flags2, ///< @b flags2 field, see @ref NavStatusFields::flags2
        FieldIdx_ttff, ///< @b ttff field, see @ref NavStatusFields::ttff
        FieldIdx_msss, ///< @b msss field, see @ref NavStatusFields::msss
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





