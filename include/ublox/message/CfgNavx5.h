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
/// @brief Contains definition of CFG-NAVX5 message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the CFG-NAVX5 message fields.
/// @see CfgNavx5
struct CfgNavx5Fields
{

    /// @brief Common boolean values enumeration
    enum class BoolVal : std::uint8_t
    {
        False, ///< false == 0
        True, ///< true ==1
        NumOfValues ///< number of available values
    };

    /// @brief Custom validator for @ref aopOrbMaxErr field
    struct AopOrbMaxErrValidator
    {
        template <typename TField>
        bool operator()(const TField& field) const
        {
            typedef typename std::decay<decltype(field)>::type FieldType;
            typedef typename FieldType::ValueType ValueType;
            auto value = field.value();
            if (value == static_cast<ValueType>(0)) {
                return true;
            }

            return (static_cast<ValueType>(5) <= value) &&
                   (value <= static_cast<ValueType>(1000));
        }
    };

    /// @brief Value enumeration for @ref iniFix3D field.
    using IniFix3D = BoolVal;

    /// @brief Value enumeration for @ref usePPP field.
    using UsePPP = BoolVal;

    /// @brief Validator for @ref version field
    struct VersionValidator
    {
        template <typename TField>
        bool operator()(const TField& field) const
        {
            return (field.value() == 0) || (field.value() == 2);
        }
    };

    /// @brief Definition of "version" field.
    using version =
        field::common::U2T<
            comms::option::ContentsValidator<VersionValidator>
        >;

    /// @brief Definition of "mask1" field.
    struct mask1 : public
        field::common::X2T<
            comms::option::BitmaskReservedBits<0x99b3, 0>
        >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS(minMax=2, minCno, initial3dfix=6, wknRoll=9, ackAid, ppp=13, aop=14);
    };

    /// @brief Definition of "mask2" field.
    struct mask2 : public
        field::common::X4T<
            comms::option::BitmaskReservedBits<0xffffff3f, 0>
        >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS(adr=6, sigAttenComp);
    };


    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res2;

    /// @brief Definition of "minSVs" field.
    using minSVs = field::common::U1;

    /// @brief Definition of "maxSVs" field.
    using maxSVs = field::common::U1;

    /// @brief Definition of "minCNO" field.
    using minCNO = field::common::U1;

    /// @brief Definition of "reserved2" field.
    using reserved2 = field::common::res1;

    /// @brief Definition of "iniFix3D" field.
    using iniFix3D =
        field::common::EnumT<
            IniFix3D,
            comms::option::ValidNumValueRange<0, (int)IniFix3D::NumOfValues - 1>
        >;

    /// @brief Definition of "reserved3" field.
    using reserved3 = field::common::res2;

    /// @brief Value enumeration for @ref ackAiding field.
    using AckAiding = BoolVal;

    /// @brief Definition of "ackAiding" field.
    using ackAiding =
        field::common::EnumT<
            AckAiding,
            comms::option::ValidNumValueRange<0, (int)AckAiding::NumOfValues - 1>
        >;

    /// @brief Definition of "wknRollover" field.
    using wknRollover = field::common::U2;

    /// @brief Definition of "sigAttenCompMode" field.
    using sigAttenCompMode = field::common::U1;

    /// @brief Definition of "reserved4" field.
    using reserved4 = field::common::res1;

    /// @brief Definition of "reserved5" field.
    using reserved5 = field::common::res2;

    /// @brief Definition of "reserved6" field.
    using reserved6 = field::common::res2;

    /// @brief Definition of "usePPP" field.
    using usePPP =
        field::common::EnumT<
            UsePPP,
            comms::option::ValidNumValueRange<0, (int)UsePPP::NumOfValues - 1>
        >;


    /// @brief Definition of "aopCfg" field.
    struct aopCfg : public
        field::common::X1T<
            comms::option::BitmaskReservedBits<0xfe, 0>
        >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS(useAOP);
    };

    /// @brief Definition of "reserved5" field.
    using reserved7 = field::common::res2;

    /// @brief Definition of "aopOrbMaxErr" field.
    using aopOrbMaxErr =
        field::common::U2T<
            comms::option::ContentsValidator<AopOrbMaxErrValidator>,
            comms::option::UnitsMeters
        >;

    /// @brief Definition of "reserved6" field.
    using reserved8 = field::common::res4;


    /// @brief Definition of "reserved7" field.
    using reserved9 = field::common::res3;

    /// @brief Value enumeration for @ref useAdr field.
    using UseAdr = BoolVal;

    /// @brief Definition of "useAdr" field.
    using useAdr =
        field::common::EnumT<
            UseAdr,
            comms::option::ValidNumValueRange<0, (int)UseAdr::NumOfValues - 1>
        >;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        version,
        mask1,
        mask2,
        reserved1,
        minSVs,
        maxSVs,
        minCNO,
        reserved2,
        iniFix3D,
        reserved3,
        ackAiding,
        wknRollover,
        sigAttenCompMode,
        reserved4,
        reserved5,
        reserved6,
        usePPP,
        aopCfg,
        reserved7,
        aopOrbMaxErr,
        reserved8,
        reserved9,
        useAdr
    >;
};

/// @brief Definition of CFG-NAVX5 message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref CfgNavx5Fields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class CfgNavx5 : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_NAVX5>,
        comms::option::FieldsImpl<CfgNavx5Fields::All>,
        comms::option::MsgType<CfgNavx5<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_NAVX5>,
        comms::option::FieldsImpl<CfgNavx5Fields::All>,
        comms::option::MsgType<CfgNavx5<TMsgBase> >
    > Base;
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b version for @ref CfgNavx5Fields::version field
    ///     @li @b mask1 for @ref CfgNavx5Fields::mask1 field
    ///     @li @b mask2 for @ref CfgNavx5Fields::mask2 field
    ///     @li @b reserved1 for @ref CfgNavx5Fields::reserved1 field
    ///     @li @b minSVs for @ref CfgNavx5Fields::minSVs field
    ///     @li @b maxSVs for @ref CfgNavx5Fields::maxSVs field
    ///     @li @b minCNO for @ref CfgNavx5Fields::minCNO field
    ///     @li @b reserved2 for @ref CfgNavx5Fields::reserved2 field
    ///     @li @b iniFix3D for @ref CfgNavx5Fields::iniFix3D field
    ///     @li @b reserved3 for @ref CfgNavx5Fields::reserved3 field
    ///     @li @b ackAiding for @ref CfgNavx5Fields::ackAiding field
    ///     @li @b wknRollover for @ref CfgNavx5Fields::wknRollover field
    ///     @li @b sigAttenCompMode for @ref CfgNavx5Fields::sigAttenCompMode field
    ///     @li @b reserved4 for @ref CfgNavx5Fields::reserved4 field
    ///     @li @b reserved5 for @ref CfgNavx5Fields::reserved5 field
    ///     @li @b reserved6 for @ref CfgNavx5Fields::reserved6 field
    ///     @li @b usePPP for @ref CfgNavx5Fields::usePPP field
    ///     @li @b aopCfg for @ref CfgNavx5Fields::aopCfg field
    ///     @li @b reserved7 for @ref CfgNavx5Fields::reserved7 field
    ///     @li @b aopOrbMaxErr for @ref CfgNavx5Fields::aopOrbMaxErr field
    ///     @li @b reserved8 for @ref CfgNavx5Fields::reserved8 field
    ///     @li @b reserved9 for @ref CfgNavx5Fields::reserved9 field
    ///     @li @b useAdr for @ref CfgNavx5Fields::useAdr field
    COMMS_MSG_FIELDS_ACCESS(
        version,
        mask1,
        mask2,
        reserved1,
        minSVs,
        maxSVs,
        minCNO,
        reserved2,
        iniFix3D,
        reserved3,
        ackAiding,
        wknRollover,
        sigAttenCompMode,
        reserved4,
        reserved5,
        reserved6,
        usePPP,
        aopCfg,
        reserved7,
        aopOrbMaxErr,
        reserved8,
        reserved9,
        useAdr
    );

    /// @brief Default constructor
    CfgNavx5() = default;

    /// @brief Copy constructor
    CfgNavx5(const CfgNavx5&) = default;

    /// @brief Move constructor
    CfgNavx5(CfgNavx5&& other) = default;

    /// @brief Destructor
    ~CfgNavx5() = default;

    /// @brief Copy assignment
    CfgNavx5& operator=(const CfgNavx5&) = default;

    /// @brief Move assignment
    CfgNavx5& operator=(CfgNavx5&&) = default;
};


}  // namespace message

}  // namespace ublox

