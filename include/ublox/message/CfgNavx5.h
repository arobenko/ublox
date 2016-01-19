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
#include "ublox/field/MsgId.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

enum
{
    CfgNavx5Field_mask1_minMax = 2,
    CfgNavx5Field_mask1_minCno,
    CfgNavx5Field_mask1_initial3dfix = 6,
    CfgNavx5Field_mask1_wknRoll = 9,
    CfgNavx5Field_mask1_ppp = 13,
    CfgNavx5Field_mask1_aop = 14,
    CfgNavx5Field_mask1_numOfValues
};

enum class CfgNavx5_BoolVal : std::uint8_t
{
    False,
    True,
    NumOfValues
};

enum
{
    CfgNavx5Field_aopCfg_useAOP,
    CfgNavx5Field_aopCfg_numOfValues
};

struct CfgNavx5_AopOrbMaxErrValidator
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

using CfgNavx5_IniFix3D = CfgNavx5_BoolVal;
using CfgNavx5_UsePPP = CfgNavx5_BoolVal;

using CfgNavx5Field_version = field::common::U2;
using CfgNavx5Field_mask1 =
    field::common::X2T<
        comms::option::BitmaskReservedBits<0x9db3, 0>
    >;
using CfgNavx5Field_reserved0 = field::common::res4;
using CfgNavx5Field_reserved1 = field::common::res1;
using CfgNavx5Field_reserved2 = field::common::res1;
using CfgNavx5Field_minSVs = field::common::U1;
using CfgNavx5Field_maxSVs = field::common::U1;
using CfgNavx5Field_minCNO = field::common::U1;
using CfgNavx5Field_reserved5 = field::common::res1;
using CfgNavx5Field_iniFix3D =
    field::common::EnumT<
        CfgNavx5_IniFix3D,
        comms::option::ValidNumValueRange<0, (int)CfgNavx5_IniFix3D::NumOfValues - 1>
    >;
using CfgNavx5Field_reserved6 = field::common::res1;
using CfgNavx5Field_reserved7 = field::common::res1;
using CfgNavx5Field_reserved8 = field::common::res1;
using CfgNavx5Field_wknRollover = field::common::U2;
using CfgNavx5Field_reserved9 = field::common::res4;
using CfgNavx5Field_reserved10 = field::common::res1;
using CfgNavx5Field_reserved11 = field::common::res1;
using CfgNavx5Field_usePPP =
    field::common::EnumT<
        CfgNavx5_UsePPP,
        comms::option::ValidNumValueRange<0, (int)CfgNavx5_UsePPP::NumOfValues - 1>
    >;
using CfgNavx5Field_aopCfg =
    field::common::X1T<
        comms::option::BitmaskReservedBits<0xfe, 0>
    >;
using CfgNavx5Field_reserved12 = field::common::res1;
using CfgNavx5Field_reserved13 = field::common::res1;
using CfgNavx5Field_aopOrbMaxErr =
    field::common::U2T<
        comms::option::ContentsValidator<CfgNavx5_AopOrbMaxErrValidator>
    >;
using CfgNavx5Field_reserved14 = field::common::res1;
using CfgNavx5Field_reserved15 = field::common::res1;
using CfgNavx5Field_reserved3 = field::common::res2;
using CfgNavx5Field_reserved4 = field::common::res4;

using CfgNavx5Fields = std::tuple<
    CfgNavx5Field_version,
    CfgNavx5Field_mask1,
    CfgNavx5Field_reserved0,
    CfgNavx5Field_reserved1,
    CfgNavx5Field_reserved2,
    CfgNavx5Field_minSVs,
    CfgNavx5Field_maxSVs,
    CfgNavx5Field_minCNO,
    CfgNavx5Field_reserved5,
    CfgNavx5Field_iniFix3D,
    CfgNavx5Field_reserved6,
    CfgNavx5Field_reserved7,
    CfgNavx5Field_reserved8,
    CfgNavx5Field_wknRollover,
    CfgNavx5Field_reserved9,
    CfgNavx5Field_reserved10,
    CfgNavx5Field_reserved11,
    CfgNavx5Field_usePPP,
    CfgNavx5Field_aopCfg,
    CfgNavx5Field_reserved12,
    CfgNavx5Field_reserved13,
    CfgNavx5Field_aopOrbMaxErr,
    CfgNavx5Field_reserved14,
    CfgNavx5Field_reserved15,
    CfgNavx5Field_reserved3,
    CfgNavx5Field_reserved4
>;

template <typename TMsgBase = Message>
class CfgNavx5 : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_NAVX5>,
        comms::option::FieldsImpl<CfgNavx5Fields>,
        comms::option::DispatchImpl<CfgNavx5<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_NAVX5>,
        comms::option::FieldsImpl<CfgNavx5Fields>,
        comms::option::DispatchImpl<CfgNavx5<TMsgBase> >
    > Base;
public:

    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_version,
        FieldIdx_mask1,
        FieldIdx_reserved0,
        FieldIdx_reserved1,
        FieldIdx_reserved2,
        FieldIdx_minSVs,
        FieldIdx_maxSVs,
        FieldIdx_minCNO,
        FieldIdx_reserved5,
        FieldIdx_iniFix3D,
        FieldIdx_reserved6,
        FieldIdx_reserved7,
        FieldIdx_reserved8,
        FieldIdx_wknRollover,
        FieldIdx_reserved9,
        FieldIdx_reserved10,
        FieldIdx_reserved11,
        FieldIdx_usePPP,
        FieldIdx_aopCfg,
        FieldIdx_reserved12,
        FieldIdx_reserved13,
        FieldIdx_aopOrbMaxErr,
        FieldIdx_reserved14,
        FieldIdx_reserved15,
        FieldIdx_reserved3,
        FieldIdx_reserved4,
        FieldIdx_numOfValues ///< number of available fields
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

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

