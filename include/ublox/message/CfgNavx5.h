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
    /// @brief Bits access enumeration for @ref mask1 bitmask field.
    enum
    {
        mask1_minMax = 2, ///< @b minMax bit index
        mask1_minCno, ///< @b minCno bit index
        mask1_initial3dfix = 6, ///< @b initial3dfix bit index
        mask1_wknRoll = 9, ///< @b wknRoll bit index
        mask1_ppp = 13, ///< @b ppp bit index
        mask1_aop = 14, ///< @b aop bit index
        mask1_numOfValues ///< upper limit for available bits
    };

    /// @brief Common boolean values enumeration
    enum class BoolVal : std::uint8_t
    {
        False, ///< false == 0
        True, ///< true ==1
        NumOfValues ///< number of available values
    };

    /// @brief Bits access enumeration for @ref aopCfg bitmask field.
    enum
    {
        aopCfg_useAOP, ///< @b useAOP bit index
        aopCfg_numOfValues ///< number of available bits
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

    /// @brief Definition of "version" field.
    using version = field::common::U2;

    /// @brief Definition of "mask1" field.
    using mask1 =
        field::common::X2T<
            comms::option::BitmaskReservedBits<0x9db3, 0>
        >;

    /// @brief Definition of "reserved0" field.
    using reserved0 = field::common::res4;

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res1;

    /// @brief Definition of "reserved2" field.
    using reserved2 = field::common::res1;

    /// @brief Definition of "minSVs" field.
    using minSVs = field::common::U1;

    /// @brief Definition of "maxSVs" field.
    using maxSVs = field::common::U1;

    /// @brief Definition of "minCNO" field.
    using minCNO = field::common::U1;

    /// @brief Definition of "reserved5" field.
    using reserved5 = field::common::res1;

    /// @brief Definition of "iniFix3D" field.
    using iniFix3D =
        field::common::EnumT<
            IniFix3D,
            comms::option::ValidNumValueRange<0, (int)IniFix3D::NumOfValues - 1>
        >;

    /// @brief Definition of "reserved6" field.
    using reserved6 = field::common::res1;

    /// @brief Definition of "reserved7" field.
    using reserved7 = field::common::res1;

    /// @brief Definition of "reserved8" field.
    using reserved8 = field::common::res1;

    /// @brief Definition of "wknRollover" field.
    using wknRollover = field::common::U2;

    /// @brief Definition of "reserved9" field.
    using reserved9 = field::common::res4;

    /// @brief Definition of "reserved10" field.
    using reserved10 = field::common::res1;

    /// @brief Definition of "reserved11" field.
    using reserved11 = field::common::res1;

    /// @brief Definition of "usePPP" field.
    using usePPP =
        field::common::EnumT<
            UsePPP,
            comms::option::ValidNumValueRange<0, (int)UsePPP::NumOfValues - 1>
        >;

    /// @brief Definition of "aopCfg" field.
    using aopCfg =
        field::common::X1T<
            comms::option::BitmaskReservedBits<0xfe, 0>
        >;

    /// @brief Definition of "reserved12" field.
    using reserved12 = field::common::res1;

    /// @brief Definition of "reserved13" field.
    using reserved13 = field::common::res1;

    /// @brief Definition of "aopOrbMaxErr" field.
    using aopOrbMaxErr =
        field::common::U2T<
            comms::option::ContentsValidator<AopOrbMaxErrValidator>
        >;

    /// @brief Definition of "reserved14" field.
    using reserved14 = field::common::res1;

    /// @brief Definition of "reserved15" field.
    using reserved15 = field::common::res1;

    /// @brief Definition of "reserved3" field.
    using reserved3 = field::common::res2;

    /// @brief Definition of "reserved4" field.
    using reserved4 = field::common::res4;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        version,
        mask1,
        reserved0,
        reserved1,
        reserved2,
        minSVs,
        maxSVs,
        minCNO,
        reserved5,
        iniFix3D,
        reserved6,
        reserved7,
        reserved8,
        wknRollover,
        reserved9,
        reserved10,
        reserved11,
        usePPP,
        aopCfg,
        reserved12,
        reserved13,
        aopOrbMaxErr,
        reserved14,
        reserved15,
        reserved3,
        reserved4
    >;
};

/// @brief Definition of CFG-NAVX5 message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref CfgNavx5Fields and for definition of the fields this message contains.
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

#ifdef FOR_DOXYGEN_DOC_ONLY
    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_version, ///< @b version field, see @ref CfgNavx5Fields::version
        FieldIdx_mask1, ///< @b mask1 field, see @ref CfgNavx5Fields::mask1
        FieldIdx_reserved0, ///< @b reserved0 field, see @ref CfgNavx5Fields::reserved0
        FieldIdx_reserved1, ///< @b reserved1 field, see @ref CfgNavx5Fields::reserved1
        FieldIdx_reserved2, ///< @b reserved2 field, see @ref CfgNavx5Fields::reserved2
        FieldIdx_minSVs, ///< @b minSVs field, see @ref CfgNavx5Fields::minSVs
        FieldIdx_maxSVs, ///< @b maxSVs field, see @ref CfgNavx5Fields::maxSVs
        FieldIdx_minCNO, ///< @b minCNO field, see @ref CfgNavx5Fields::minCNO
        FieldIdx_reserved5, ///< @b reserved5 field, see @ref CfgNavx5Fields::reserved5
        FieldIdx_iniFix3D, ///< @b iniFix3D field, see @ref CfgNavx5Fields::iniFix3D
        FieldIdx_reserved6, ///< @b reserved6 field, see @ref CfgNavx5Fields::reserved6
        FieldIdx_reserved7, ///< @b reserved7 field, see @ref CfgNavx5Fields::reserved7
        FieldIdx_reserved8, ///< @b reserved8 field, see @ref CfgNavx5Fields::reserved8
        FieldIdx_wknRollover, ///< @b wknRollover field, see @ref CfgNavx5Fields::wknRollover
        FieldIdx_reserved9, ///< @b reserved9 field, see @ref CfgNavx5Fields::reserved9
        FieldIdx_reserved10, ///< @b reserved10 field, see @ref CfgNavx5Fields::reserved10
        FieldIdx_reserved11, ///< @b reserved11 field, see @ref CfgNavx5Fields::reserved11
        FieldIdx_usePPP, ///< @b usePPP field, see @ref CfgNavx5Fields::usePPP
        FieldIdx_aopCfg, ///< @b aopCfg field, see @ref CfgNavx5Fields::aopCfg
        FieldIdx_reserved12, ///< @b reserved12 field, see @ref CfgNavx5Fields::reserved12
        FieldIdx_reserved13, ///< @b reserved13 field, see @ref CfgNavx5Fields::reserved13
        FieldIdx_aopOrbMaxErr, ///< @b aopOrbMaxErr field, see @ref CfgNavx5Fields::aopOrbMaxErr
        FieldIdx_reserved14, ///< @b reserved14 field, see @ref CfgNavx5Fields::reserved14
        FieldIdx_reserved15, ///< @b reserved15 field, see @ref CfgNavx5Fields::reserved15
        FieldIdx_reserved3, ///< @b reserved3 field, see @ref CfgNavx5Fields::reserved3
        FieldIdx_reserved4, ///< @b reserved4 field, see @ref CfgNavx5Fields::reserved4
        FieldIdx_numOfValues ///< number of available fields
    };

    /// @brief Access to fields bundled as a struct
    struct FieldsAsStruct
    {
        CfgNavx5Fields::version& version; ///< @b version field, see @ref CfgNavx5Fields::version
        CfgNavx5Fields::mask1& mask1; ///< @b mask1 field, see @ref CfgNavx5Fields::mask1
        CfgNavx5Fields::reserved0& reserved0; ///< @b reserved0 field, see @ref CfgNavx5Fields::reserved0
        CfgNavx5Fields::reserved1& reserved1; ///< @b reserved1 field, see @ref CfgNavx5Fields::reserved1
        CfgNavx5Fields::reserved2& reserved2; ///< @b reserved2 field, see @ref CfgNavx5Fields::reserved2
        CfgNavx5Fields::minSVs& minSVs; ///< @b minSVs field, see @ref CfgNavx5Fields::minSVs
        CfgNavx5Fields::maxSVs& maxSVs; ///< @b maxSVs field, see @ref CfgNavx5Fields::maxSVs
        CfgNavx5Fields::minCNO& minCNO; ///< @b minCNO field, see @ref CfgNavx5Fields::minCNO
        CfgNavx5Fields::reserved5& reserved5; ///< @b reserved5 field, see @ref CfgNavx5Fields::reserved5
        CfgNavx5Fields::iniFix3D& iniFix3D; ///< @b iniFix3D field, see @ref CfgNavx5Fields::iniFix3D
        CfgNavx5Fields::reserved6& reserved6; ///< @b reserved6 field, see @ref CfgNavx5Fields::reserved6
        CfgNavx5Fields::reserved7& reserved7; ///< @b reserved7 field, see @ref CfgNavx5Fields::reserved7
        CfgNavx5Fields::reserved8& reserved8; ///< @b reserved8 field, see @ref CfgNavx5Fields::reserved8
        CfgNavx5Fields::wknRollover& wknRollover; ///< @b wknRollover field, see @ref CfgNavx5Fields::wknRollover
        CfgNavx5Fields::reserved9& reserved9; ///< @b reserved9 field, see @ref CfgNavx5Fields::reserved9
        CfgNavx5Fields::reserved10& reserved10; ///< @b reserved10 field, see @ref CfgNavx5Fields::reserved10
        CfgNavx5Fields::reserved11& reserved11; ///< @b reserved11 field, see @ref CfgNavx5Fields::reserved11
        CfgNavx5Fields::usePPP& usePPP; ///< @b usePPP field, see @ref CfgNavx5Fields::usePPP
        CfgNavx5Fields::aopCfg& aopCfg; ///< @b aopCfg field, see @ref CfgNavx5Fields::aopCfg
        CfgNavx5Fields::reserved12& reserved12; ///< @b reserved12 field, see @ref CfgNavx5Fields::reserved12
        CfgNavx5Fields::reserved13& reserved13; ///< @b reserved13 field, see @ref CfgNavx5Fields::reserved13
        CfgNavx5Fields::aopOrbMaxErr& aopOrbMaxErr; ///< @b aopOrbMaxErr field, see @ref CfgNavx5Fields::aopOrbMaxErr
        CfgNavx5Fields::reserved14& reserved14; ///< @b reserved14 field, see @ref CfgNavx5Fields::reserved14
        CfgNavx5Fields::reserved15& reserved15; ///< @b reserved15 field, see @ref CfgNavx5Fields::reserved15
        CfgNavx5Fields::reserved3& reserved3; ///< @b reserved3 field, see @ref CfgNavx5Fields::reserved3
        CfgNavx5Fields::reserved4& reserved4; ///< @b reserved4 field, see @ref CfgNavx5Fields::reserved4
    };

    /// @brief Access to @b const fields bundled as a struct
    struct ConstFieldsAsStruct
    {
        const CfgNavx5Fields::version& version; ///< @b version field, see @ref CfgNavx5Fields::version
        const CfgNavx5Fields::mask1& mask1; ///< @b mask1 field, see @ref CfgNavx5Fields::mask1
        const CfgNavx5Fields::reserved0& reserved0; ///< @b reserved0 field, see @ref CfgNavx5Fields::reserved0
        const CfgNavx5Fields::reserved1& reserved1; ///< @b reserved1 field, see @ref CfgNavx5Fields::reserved1
        const CfgNavx5Fields::reserved2& reserved2; ///< @b reserved2 field, see @ref CfgNavx5Fields::reserved2
        const CfgNavx5Fields::minSVs& minSVs; ///< @b minSVs field, see @ref CfgNavx5Fields::minSVs
        const CfgNavx5Fields::maxSVs& maxSVs; ///< @b maxSVs field, see @ref CfgNavx5Fields::maxSVs
        const CfgNavx5Fields::minCNO& minCNO; ///< @b minCNO field, see @ref CfgNavx5Fields::minCNO
        const CfgNavx5Fields::reserved5& reserved5; ///< @b reserved5 field, see @ref CfgNavx5Fields::reserved5
        const CfgNavx5Fields::iniFix3D& iniFix3D; ///< @b iniFix3D field, see @ref CfgNavx5Fields::iniFix3D
        const CfgNavx5Fields::reserved6& reserved6; ///< @b reserved6 field, see @ref CfgNavx5Fields::reserved6
        const CfgNavx5Fields::reserved7& reserved7; ///< @b reserved7 field, see @ref CfgNavx5Fields::reserved7
        const CfgNavx5Fields::reserved8& reserved8; ///< @b reserved8 field, see @ref CfgNavx5Fields::reserved8
        const CfgNavx5Fields::wknRollover& wknRollover; ///< @b wknRollover field, see @ref CfgNavx5Fields::wknRollover
        const CfgNavx5Fields::reserved9& reserved9; ///< @b reserved9 field, see @ref CfgNavx5Fields::reserved9
        const CfgNavx5Fields::reserved10& reserved10; ///< @b reserved10 field, see @ref CfgNavx5Fields::reserved10
        const CfgNavx5Fields::reserved11& reserved11; ///< @b reserved11 field, see @ref CfgNavx5Fields::reserved11
        const CfgNavx5Fields::usePPP& usePPP; ///< @b usePPP field, see @ref CfgNavx5Fields::usePPP
        const CfgNavx5Fields::aopCfg& aopCfg; ///< @b aopCfg field, see @ref CfgNavx5Fields::aopCfg
        const CfgNavx5Fields::reserved12& reserved12; ///< @b reserved12 field, see @ref CfgNavx5Fields::reserved12
        const CfgNavx5Fields::reserved13& reserved13; ///< @b reserved13 field, see @ref CfgNavx5Fields::reserved13
        const CfgNavx5Fields::aopOrbMaxErr& aopOrbMaxErr; ///< @b aopOrbMaxErr field, see @ref CfgNavx5Fields::aopOrbMaxErr
        const CfgNavx5Fields::reserved14& reserved14; ///< @b reserved14 field, see @ref CfgNavx5Fields::reserved14
        const CfgNavx5Fields::reserved15& reserved15; ///< @b reserved15 field, see @ref CfgNavx5Fields::reserved15
        const CfgNavx5Fields::reserved3& reserved3; ///< @b reserved3 field, see @ref CfgNavx5Fields::reserved3
        const CfgNavx5Fields::reserved4& reserved4; ///< @b reserved4 field, see @ref CfgNavx5Fields::reserved4
    };

    /// @brief Get access to fields bundled into a struct
    FieldsAsStruct fieldsAsStruct();

    /// @brief Get access to @b const fields bundled into a struct
    ConstFieldsAsStruct fieldsAsStruct() const;

#else
    COMMS_MSG_FIELDS_ACCESS(Base,
        version,
        mask1,
        reserved0,
        reserved1,
        reserved2,
        minSVs,
        maxSVs,
        minCNO,
        reserved5,
        iniFix3D,
        reserved6,
        reserved7,
        reserved8,
        wknRollover,
        reserved9,
        reserved10,
        reserved11,
        usePPP,
        aopCfg,
        reserved12,
        reserved13,
        aopOrbMaxErr,
        reserved14,
        reserved15,
        reserved3,
        reserved4
    );
#endif // #ifdef FOR_DOXYGEN_DOC_ONLY

    /// @brief Default constructor
    CfgNavx5() = default;

    /// @brief Copy constructor
    CfgNavx5(const CfgNavx5&) = default;

    /// @brief Move constructor
    CfgNavx5(CfgNavx5&& other) = default;

    /// @brief Destructor
    virtual ~CfgNavx5() = default;

    /// @brief Copy assignment
    CfgNavx5& operator=(const CfgNavx5&) = default;

    /// @brief Move assignment
    CfgNavx5& operator=(CfgNavx5&&) = default;
};


}  // namespace message

}  // namespace ublox

