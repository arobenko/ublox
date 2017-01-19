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
/// @brief Contains definition of CFG-NAV5 message and its fields.

#pragma once

#include <algorithm>

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the CFG-NAV5 message fields.
/// @see CfgNav5
struct CfgNav5Fields
{
    /// @brief Value enumeration for @ref dynModel enum value field.
    enum class DynModel : std::uint8_t
    {
        Portable, ///< Portable model
        Stationary = 2, ///< Stationary model
        Pedestrian, ///< Pedestrian model
        Automotive, ///< Automotive model
        Sea, ///< Sea model
        Airborne_1g, ///< Airborne with <1g Acceleration
        Airborne_2g,///< Airborne with <2g Acceleration
        Airborne_4g,///< Airborne with <4g Acceleration
    };

    /// @brief Custom value validator for @ref dynModel field.
    struct DynModelValidator
    {
        template <typename TField>
        bool operator()(const TField& field) const
        {
            static const DynModel Values[] = {
                DynModel::Portable,
                DynModel::Stationary,
                DynModel::Pedestrian,
                DynModel::Automotive,
                DynModel::Sea,
                DynModel::Airborne_1g,
                DynModel::Airborne_2g,
                DynModel::Airborne_4g
            };

            auto value = field.value();
            auto iter = std::lower_bound(std::begin(Values), std::end(Values), value);
            return (iter != std::end(Values)) && (*iter == value);
        }
    };

    /// @brief Value enumeration for @ref fixMode enum value field.
    enum class FixMode : std::uint8_t
    {
        Only_2D = 1,
        Only_3D,
        Auto,
    };

    /// @brief Definition of "mask" field.
    struct mask : public
        field::common::X2T<
            comms::option::BitmaskReservedBits<0xff00, 0>
        >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS(dyn, minEl, posFixMode, drLim, posMask, timeMask, staticHoldMask, dgps);
    };

    /// @brief Definition of "dynModel" field.
    using dynModel =
        field::common::EnumT<
            DynModel,
            comms::option::ContentsValidator<DynModelValidator>
        >;

    /// @brief Definition of "fixMode" field.
    using fixMode =
        field::common::EnumT<
            FixMode,
            comms::option::ValidNumValueRange<(int)FixMode::Only_2D, (int)FixMode::Auto>
        >;

    /// @brief Definition of "fixedAlt" field.
    using fixedAlt = field::common::I4T<comms::option::ScalingRatio<1, 100> >;

    /// @brief Definition of "fixedAltVar" field.
    using fixedAltVar = field::common::U4T<comms::option::ScalingRatio<1, 10000> >;

    /// @brief Definition of "minElev" field.
    using minElev = field::common::I1;

    /// @brief Definition of "drLimit" field.
    using drLimit = field::common::U1;

    /// @brief Definition of "pDOP" field.
    using pDOP = field::common::U2T<comms::option::ScalingRatio<1, 10> >;

    /// @brief Definition of "tDOP" field.
    using tDOP = field::common::U2T<comms::option::ScalingRatio<1, 10> >;

    /// @brief Definition of "pAcc" field.
    using pAcc = field::common::U2;

    /// @brief Definition of "tAcc" field.
    using tAcc = field::common::U2;

    /// @brief Definition of "staticHoldThreash" field.
    using staticHoldThreash = field::common::U1T<field::common::Scaling_cm2m>;

    /// @brief Definition of "dgpsTimeOut" field.
    using dgpsTimeOut = field::common::U1;

    /// @brief Definition of "cnoThreshNumSVs" field.
    using cnoThreshNumSVs = field::common::U1;

    /// @brief Definition of "cnoThresh" field.
    using cnoThresh = field::common::U1;

    /// @brief Definition of "reserved2" field.
    using reserved2 = field::common::res2;

    /// @brief Definition of "reserved3" field.
    using reserved3 = field::common::res4;

    /// @brief Definition of "reserved4" field.
    using reserved4 = field::common::res4;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        mask,
        dynModel,
        fixMode,
        fixedAlt,
        fixedAltVar,
        minElev,
        drLimit,
        pDOP,
        tDOP,
        pAcc,
        tAcc,
        staticHoldThreash,
        dgpsTimeOut,
        cnoThreshNumSVs,
        cnoThresh,
        reserved2,
        reserved3,
        reserved4
    >;
};

/// @brief Definition of CFG-NAV5 message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref CfgNav5Fields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class CfgNav5 : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_NAV5>,
        comms::option::FieldsImpl<CfgNav5Fields::All>,
        comms::option::MsgType<CfgNav5<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_NAV5>,
        comms::option::FieldsImpl<CfgNav5Fields::All>,
        comms::option::MsgType<CfgNav5<TMsgBase> >
    > Base;
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b mask for @ref CfgNav5Fields::mask field
    ///     @li @b dynModel for @ref CfgNav5Fields::dynModel field
    ///     @li @b fixMode for @ref CfgNav5Fields::fixMode field
    ///     @li @b fixedAlt for @ref CfgNav5Fields::fixedAlt field
    ///     @li @b fixedAltVar for @ref CfgNav5Fields::fixedAltVar field
    ///     @li @b minElev for @ref CfgNav5Fields::minElev field
    ///     @li @b drLimit for @ref CfgNav5Fields::drLimit field
    ///     @li @b pDOP for @ref CfgNav5Fields::pDOP field
    ///     @li @b tDOP for @ref CfgNav5Fields::tDOP field
    ///     @li @b pAcc for @ref CfgNav5Fields::pAcc field
    ///     @li @b tAcc for @ref CfgNav5Fields::tAcc field
    ///     @li @b staticHoldThreash for @ref CfgNav5Fields::staticHoldThreash field
    ///     @li @b dgpsTimeOut for @ref CfgNav5Fields::dgpsTimeOut field
    ///     @li @b cnoThreshNumSVs for @ref CfgNav5Fields::cnoThreshNumSVs field
    ///     @li @b cnoThresh for @ref CfgNav5Fields::cnoThresh field
    ///     @li @b reserved2 for @ref CfgNav5Fields::reserved2 field
    ///     @li @b reserved3 for @ref CfgNav5Fields::reserved3 field
    ///     @li @b reserved4 for @ref CfgNav5Fields::reserved4 field
    COMMS_MSG_FIELDS_ACCESS(Base,
        mask,
        dynModel,
        fixMode,
        fixedAlt,
        fixedAltVar,
        minElev,
        drLimit,
        pDOP,
        tDOP,
        pAcc,
        tAcc,
        staticHoldThreash,
        dgpsTimeOut,
        cnoThreshNumSVs,
        cnoThresh,
        reserved2,
        reserved3,
        reserved4
    );

    /// @brief Default constructor
    CfgNav5() = default;

    /// @brief Copy constructor
    CfgNav5(const CfgNav5&) = default;

    /// @brief Move constructor
    CfgNav5(CfgNav5&& other) = default;

    /// @brief Destructor
    virtual ~CfgNav5() = default;

    /// @brief Copy assignment
    CfgNav5& operator=(const CfgNav5&) = default;

    /// @brief Move assignment
    CfgNav5& operator=(CfgNav5&&) = default;
};


}  // namespace message

}  // namespace ublox

