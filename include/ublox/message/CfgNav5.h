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
    /// @brief Bits access enumeration for @ref mask bitmask field.
    enum
    {
        mask_dyn, ///< @b dyn bit index
        mask_minEl, ///< @b minEl bit index
        mask_posFixMode, ///< @b posFixMode bit index
        mask_drLim, ///< @b drLim bit index
        mask_posMask, ///< @b posMask bit index
        mask_timeMask, ///< @b timeMask bit index
        mask_staticHoldMask, ///< @b staticHoldMask bit index
        mask_dgpsMask, ///< @b dgps bit index
        mask_numOfValues ///< number of available bits
    };

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
    using mask =
        field::common::X2T<
            comms::option::BitmaskReservedBits<0xff00, 0>
        >;

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
///     See @ref CfgNav5Fields and for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class CfgNav5 : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_NAV5>,
        comms::option::FieldsImpl<CfgNav5Fields::All>,
        comms::option::MsgType<CfgNav5<TMsgBase> >,
        comms::option::DispatchImpl
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_NAV5>,
        comms::option::FieldsImpl<CfgNav5Fields::All>,
        comms::option::MsgType<CfgNav5<TMsgBase> >,
        comms::option::DispatchImpl
    > Base;
public:

#ifdef FOR_DOXYGEN_DOC_ONLY
    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_mask, ///< @b mask field, see @ref CfgNav5Fields::mask
        FieldIdx_dynModel, ///< @b dynModel field, see @ref CfgNav5Fields::dynModel
        FieldIdx_fixMode, ///< @b fixMode field, see @ref CfgNav5Fields::fixMode
        FieldIdx_fixedAlt, ///< @b fixedAlt field, see @ref CfgNav5Fields::fixedAlt
        FieldIdx_fixedAltVar, ///< @b fixedAltVar field, see @ref CfgNav5Fields::fixedAltVar
        FieldIdx_minElev, ///< @b minElev field, see @ref CfgNav5Fields::minElev
        FieldIdx_drLimit, ///< @b drLimit field, see @ref CfgNav5Fields::drLimit
        FieldIdx_pDOP, ///< @b pDOP field, see @ref CfgNav5Fields::pDOP
        FieldIdx_tDOP, ///< @b tDOP field, see @ref CfgNav5Fields::tDOP
        FieldIdx_pAcc, ///< @b pAcc field, see @ref CfgNav5Fields::pAcc
        FieldIdx_tAcc, ///< @b tAcc field, see @ref CfgNav5Fields::tAcc
        FieldIdx_staticHoldThreash, ///< @b staticHoldThreash field, see @ref CfgNav5Fields::staticHoldThreash
        FieldIdx_dgpsTimeOut, ///< @b dgpsTimeOut field, see @ref CfgNav5Fields::dgpsTimeOut
        FieldIdx_cnoThreshNumSVs, ///< @b cnoThreshNumSVs field, see @ref CfgNav5Fields::cnoThreshNumSVs
        FieldIdx_cnoThresh, ///< @b cnoThresh field, see @ref CfgNav5Fields::cnoThresh
        FieldIdx_reserved2, ///< @b reserved2 field, see @ref CfgNav5Fields::reserved2
        FieldIdx_reserved3, ///< @b reserved3 field, see @ref CfgNav5Fields::reserved3
        FieldIdx_reserved4, ///< @b reserved4 field, see @ref CfgNav5Fields::reserved4
        FieldIdx_numOfValues ///< number of available fields
    };

    /// @brief Access to fields bundled as a struct
    struct FieldsAsStruct
    {
        CfgNav5Fields::mask& mask; ///< @b mask field, see @ref CfgNav5Fields::mask
        CfgNav5Fields::dynModel& dynModel; ///< @b dynModel field, see @ref CfgNav5Fields::dynModel
        CfgNav5Fields::fixMode& fixMode; ///< @b fixMode field, see @ref CfgNav5Fields::fixMode
        CfgNav5Fields::fixedAlt& fixedAlt; ///< @b fixedAlt field, see @ref CfgNav5Fields::fixedAlt
        CfgNav5Fields::fixedAltVar& fixedAltVar; ///< @b fixedAltVar field, see @ref CfgNav5Fields::fixedAltVar
        CfgNav5Fields::minElev& minElev; ///< @b minElev field, see @ref CfgNav5Fields::minElev
        CfgNav5Fields::drLimit& drLimit; ///< @b drLimit field, see @ref CfgNav5Fields::drLimit
        CfgNav5Fields::pDOP& pDOP; ///< @b pDOP field, see @ref CfgNav5Fields::pDOP
        CfgNav5Fields::tDOP& tDOP; ///< @b tDOP field, see @ref CfgNav5Fields::tDOP
        CfgNav5Fields::pAcc& pAcc; ///< @b pAcc field, see @ref CfgNav5Fields::pAcc
        CfgNav5Fields::tAcc& tAcc; ///< @b tAcc field, see @ref CfgNav5Fields::tAcc
        CfgNav5Fields::staticHoldThreash& staticHoldThreash; ///< @b staticHoldThreash field, see @ref CfgNav5Fields::staticHoldThreash
        CfgNav5Fields::dgpsTimeOut& dgpsTimeOut; ///< @b dgpsTimeOut field, see @ref CfgNav5Fields::dgpsTimeOut
        CfgNav5Fields::cnoThreshNumSVs& cnoThreshNumSVs; ///< @b cnoThreshNumSVs field, see @ref CfgNav5Fields::cnoThreshNumSVs
        CfgNav5Fields::cnoThresh& cnoThresh; ///< @b cnoThresh field, see @ref CfgNav5Fields::cnoThresh
        CfgNav5Fields::reserved2& reserved2; ///< @b reserved2 field, see @ref CfgNav5Fields::reserved2
        CfgNav5Fields::reserved3& reserved3; ///< @b reserved3 field, see @ref CfgNav5Fields::reserved3
        CfgNav5Fields::reserved4& reserved4; ///< @b reserved4 field, see @ref CfgNav5Fields::reserved4
    };

    /// @brief Access to @b const fields bundled as a struct
    struct ConstFieldsAsStruct
    {
        const CfgNav5Fields::mask& mask; ///< @b mask field, see @ref CfgNav5Fields::mask
        const CfgNav5Fields::dynModel& dynModel; ///< @b dynModel field, see @ref CfgNav5Fields::dynModel
        const CfgNav5Fields::fixMode& fixMode; ///< @b fixMode field, see @ref CfgNav5Fields::fixMode
        const CfgNav5Fields::fixedAlt& fixedAlt; ///< @b fixedAlt field, see @ref CfgNav5Fields::fixedAlt
        const CfgNav5Fields::fixedAltVar& fixedAltVar; ///< @b fixedAltVar field, see @ref CfgNav5Fields::fixedAltVar
        const CfgNav5Fields::minElev& minElev; ///< @b minElev field, see @ref CfgNav5Fields::minElev
        const CfgNav5Fields::drLimit& drLimit; ///< @b drLimit field, see @ref CfgNav5Fields::drLimit
        const CfgNav5Fields::pDOP& pDOP; ///< @b pDOP field, see @ref CfgNav5Fields::pDOP
        const CfgNav5Fields::tDOP& tDOP; ///< @b tDOP field, see @ref CfgNav5Fields::tDOP
        const CfgNav5Fields::pAcc& pAcc; ///< @b pAcc field, see @ref CfgNav5Fields::pAcc
        const CfgNav5Fields::tAcc& tAcc; ///< @b tAcc field, see @ref CfgNav5Fields::tAcc
        const CfgNav5Fields::staticHoldThreash& staticHoldThreash; ///< @b staticHoldThreash field, see @ref CfgNav5Fields::staticHoldThreash
        const CfgNav5Fields::dgpsTimeOut& dgpsTimeOut; ///< @b dgpsTimeOut field, see @ref CfgNav5Fields::dgpsTimeOut
        const CfgNav5Fields::cnoThreshNumSVs& cnoThreshNumSVs; ///< @b cnoThreshNumSVs field, see @ref CfgNav5Fields::cnoThreshNumSVs
        const CfgNav5Fields::cnoThresh& cnoThresh; ///< @b cnoThresh field, see @ref CfgNav5Fields::cnoThresh
        const CfgNav5Fields::reserved2& reserved2; ///< @b reserved2 field, see @ref CfgNav5Fields::reserved2
        const CfgNav5Fields::reserved3& reserved3; ///< @b reserved3 field, see @ref CfgNav5Fields::reserved3
        const CfgNav5Fields::reserved4& reserved4; ///< @b reserved4 field, see @ref CfgNav5Fields::reserved4
    };

    /// @brief Get access to fields bundled into a struct
    FieldsAsStruct fieldsAsStruct();

    /// @brief Get access to @b const fields bundled into a struct
    ConstFieldsAsStruct fieldsAsStruct() const;

#else
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
#endif // #ifdef FOR_DOXYGEN_DOC_ONLY

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

