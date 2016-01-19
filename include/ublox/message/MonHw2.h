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
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

enum class MonHw2_CfgSource : std::uint8_t
{
    FlashImage = 102,
    OTP = 111,
    ConfigPins = 112,
    ROM = 114
};

struct MonHw2_CfgSourceValidator
{
    template <typename TField>
    bool operator()(const TField& field) const
    {
        static const MonHw2_CfgSource Values[] = {
            MonHw2_CfgSource::FlashImage,
            MonHw2_CfgSource::OTP,
            MonHw2_CfgSource::ConfigPins,
            MonHw2_CfgSource::ROM
        };

        auto value = field.value();
        auto iter = std::lower_bound(std::begin(Values), std::end(Values), value);
        return (iter != std::end(Values)) && (*iter == value);
    }
};

using MonHw2Field_ofsI = field::common::I1;
using MonHw2Field_magI = field::common::U1;
using MonHw2Field_ofsQ = field::common::I1;
using MonHw2Field_magQ = field::common::U1;
using MonHw2Field_cfgSource =
    field::common::EnumT<
        MonHw2_CfgSource,
        comms::option::ContentsValidator<MonHw2_CfgSourceValidator>
    >;
using MonHw2Field_reserved0 = field::common::res3;
using MonHw2Field_lowLevelCfg = field::common::U4;
using MonHw2Field_reserved1 =
    field::common::ListT<
        field::common::res4,
        comms::option::SequenceFixedSize<2>
    >;
using MonHw2Field_postStatus = field::common::U4;
using MonHw2Field_reserved2 = field::common::res4;

using MonHw2Fields = std::tuple<
    MonHw2Field_ofsI,
    MonHw2Field_magI,
    MonHw2Field_ofsQ,
    MonHw2Field_magQ,
    MonHw2Field_cfgSource,
    MonHw2Field_reserved0,
    MonHw2Field_lowLevelCfg,
    MonHw2Field_reserved1,
    MonHw2Field_postStatus,
    MonHw2Field_reserved2
>;


template <typename TMsgBase = Message>
class MonHw2 : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_MON_HW2>,
        comms::option::FieldsImpl<MonHw2Fields>,
        comms::option::DispatchImpl<MonHw2<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_MON_HW2>,
        comms::option::FieldsImpl<MonHw2Fields>,
        comms::option::DispatchImpl<MonHw2<TMsgBase> >
    > Base;
public:

    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_ofsI,
        FieldIdx_magI,
        FieldIdx_ofsQ,
        FieldIdx_magQ,
        FieldIdx_cfgSource,
        FieldIdx_reserved0,
        FieldIdx_lowLevelCfg,
        FieldIdx_reserved1,
        FieldIdx_postStatus,
        FieldIdx_reserved2,
        FieldIdx_numOfValues ///< number of available fields
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    /// @brief Default constructor
    MonHw2() = default;

    /// @brief Copy constructor
    MonHw2(const MonHw2&) = default;

    /// @brief Move constructor
    MonHw2(MonHw2&& other) = default;

    /// @brief Destructor
    virtual ~MonHw2() = default;

    /// @brief Copy assignment
    MonHw2& operator=(const MonHw2&) = default;

    /// @brief Move assignment
    MonHw2& operator=(MonHw2&&) = default;
};


}  // namespace message

}  // namespace ublox

