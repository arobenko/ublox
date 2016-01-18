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

#include <algorithm>

#include "comms/Message.h"
#include "ublox/Message.h"
#include "ublox/field/MsgId.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

enum class CfgRxm_LowPowerMode : std::uint8_t
{
    MaxPerformance,
    PowerSave,
    Eco = 4
};

struct CfgRxm_LowPowerModeValidator
{
    template <typename TField>
    bool operator()(const TField& field) const
    {
        auto value = field.value();

        static const CfgRxm_LowPowerMode ValidValues[] = {
            CfgRxm_LowPowerMode::MaxPerformance,
            CfgRxm_LowPowerMode::PowerSave,
            CfgRxm_LowPowerMode::Eco
        };

        auto iter = std::lower_bound(std::begin(ValidValues), std::end(ValidValues), value);
        return (iter != std::end(ValidValues)) && (*iter == value);
    }
};

using CfgRxmField_reserved1 =
    field::common::U1T<
        comms::option::DefaultNumValue<8>,
        comms::option::ValidNumValueRange<8, 8>
    >;
using CfgRxmField_lpMode =
    comms::field::EnumValue<
        field::common::FieldBase,
        CfgRxm_LowPowerMode,
        comms::option::ContentsValidator<CfgRxm_LowPowerModeValidator>
    >;

using CfgRxmFields = std::tuple<
    CfgRxmField_reserved1,
    CfgRxmField_lpMode
>;

template <typename TMsgBase = Message>
class CfgRxm : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_RXM>,
        comms::option::FieldsImpl<CfgRxmFields>,
        comms::option::DispatchImpl<CfgRxm<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_RXM>,
        comms::option::FieldsImpl<CfgRxmFields>,
        comms::option::DispatchImpl<CfgRxm<TMsgBase> >
    > Base;
public:

    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_reserved1,
        FieldIdx_lpMode,
        FieldIdx_numOfValues ///< number of available fields
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    /// @brief Default constructor
    CfgRxm() = default;

    /// @brief Copy constructor
    CfgRxm(const CfgRxm&) = default;

    /// @brief Move constructor
    CfgRxm(CfgRxm&& other) = default;

    /// @brief Destructor
    virtual ~CfgRxm() = default;

    /// @brief Copy assignment
    CfgRxm& operator=(const CfgRxm&) = default;

    /// @brief Move assignment
    CfgRxm& operator=(CfgRxm&&) = default;
};


}  // namespace message

}  // namespace ublox

