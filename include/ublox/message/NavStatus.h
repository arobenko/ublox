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

    /// @brief Definition of "iTOW" field.
    using iTOW = field::nav::iTOW;

    /// @brief Definition of "gpsFix" field.
    using gpsFix = field::nav::gpsFix;

    /// @brief Definition of "flags" field.
    struct flags : public
        field::common::X1T<
            comms::option::BitmaskReservedBits<0xf0, 0>
        >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS(gpsFixOk, diffSoln, wknSet, towSet);
    };

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

    /// @brief Base class of @ref fixStat field
    using fixStatBase =
        field::common::BitfieldT<
            std::tuple<
                dgpsIStat,
                field::common::res1T<
                    comms::option::FixedBitLength<5>
                >,
                mapMatching
            >
        >;

    /// @brief Definition of "fixStat" field.
    struct fixStat : public fixStatBase
    {
        /// @brief Allow access to internal fields.
        /// @details See definition of @b COMMS_FIELD_MEMBERS_ACCESS macro
        ///     related to @b comms::field::Bitfield class from COMMS library
        ///     for details.
        COMMS_FIELD_MEMBERS_ACCESS(fixStatBase, dgpsIStat, reserved, mapMatching);
    };

    /// @brief Definition of "psmState" member fields of @ref flags2 bitfield.
    using psmState =
        field::common::EnumT<
            PsmState,
            comms::option::ValidNumValueRange<0, (int)PsmState::NumOfValues - 1>,
            comms::option::FixedBitLength<2>
        >;

    /// @brief Base class of @ref flags2 field.
    using flags2Base =
        field::common::BitfieldT<
            std::tuple<
                psmState,
                field::common::res1T<
                    comms::option::FixedBitLength<6>
                >
            >
        >;

    /// @brief Definition of "flags2" field.
    struct flags2 : public flags2Base
    {
        /// @brief Allow access to internal fields.
        /// @details See definition of @b COMMS_FIELD_MEMBERS_ACCESS macro
        ///     related to @b comms::field::Bitfield class from COMMS library
        ///     for details.
        COMMS_FIELD_MEMBERS_ACCESS(flags2Base, psmState, reserved);
    };

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
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref NavStatusFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class NavStatus : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_STATUS>,
        comms::option::FieldsImpl<NavStatusFields::All>,
        comms::option::MsgType<NavStatus<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_STATUS>,
        comms::option::FieldsImpl<NavStatusFields::All>,
        comms::option::MsgType<NavStatus<TMsgBase> >
    > Base;
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b iTOW for @ref NavStatusFields::iTOW field
    ///     @li @b gpsFix for @ref NavStatusFields::gpsFix field
    ///     @li @b flags for @ref NavStatusFields::flags field
    ///     @li @b fixStat for @ref NavStatusFields::fixStat field
    ///     @li @b flags2 for @ref NavStatusFields::flags2 field
    ///     @li @b ttff for @ref NavStatusFields::ttff field
    ///     @li @b msss for @ref NavStatusFields::msss field
    COMMS_MSG_FIELDS_ACCESS(Base, iTOW, gpsFix, flags, fixStat, flags2, ttff, msss);

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





