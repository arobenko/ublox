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

enum
{
    CfgLogfilterField_flags_recordEnabled,
    CfgLogfilterField_flags_psmOncePerWakupEnabled,
    CfgLogfilterField_flags_applyAllFilterSettings,
    CfgLogfilterField_flags_numOfValues
};

using CfgLogfilterField_version =
    field::common::U1T<
        comms::option::DefaultNumValue<1>,
        comms::option::ValidNumValueRange<1, 1>
    >;
using CfgLogfilterField_flags =
    field::common::X1T<
        comms::option::BitmaskReservedBits<0xf8, 0>
    >;
using CfgLogfilterField_minInterval = field::common::U2;
using CfgLogfilterField_timeThreshold = field::common::U2;
using CfgLogfilterField_speedThreshold = field::common::U2;
using CfgLogfilterField_positionThreshold = field::common::U4;

using CfgLogfilterFields = std::tuple<
    CfgLogfilterField_version,
    CfgLogfilterField_flags,
    CfgLogfilterField_minInterval,
    CfgLogfilterField_timeThreshold,
    CfgLogfilterField_speedThreshold,
    CfgLogfilterField_positionThreshold
>;

template <typename TMsgBase = Message>
class CfgLogfilter : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_LOGFILTER>,
        comms::option::FieldsImpl<CfgLogfilterFields>,
        comms::option::DispatchImpl<CfgLogfilter<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_LOGFILTER>,
        comms::option::FieldsImpl<CfgLogfilterFields>,
        comms::option::DispatchImpl<CfgLogfilter<TMsgBase> >
    > Base;
public:

    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_version,
        FieldIdx_flags,
        FieldIdx_minInterval,
        FieldIdx_timeThreshold,
        FieldIdx_speedThreshold,
        FieldIdx_positionThreshold,
        FieldIdx_numOfValues ///< number of available fields
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    /// @brief Default constructor
    CfgLogfilter() = default;

    /// @brief Copy constructor
    CfgLogfilter(const CfgLogfilter&) = default;

    /// @brief Move constructor
    CfgLogfilter(CfgLogfilter&& other) = default;

    /// @brief Destructor
    virtual ~CfgLogfilter() = default;

    /// @brief Copy assignment
    CfgLogfilter& operator=(const CfgLogfilter&) = default;

    /// @brief Move assignment
    CfgLogfilter& operator=(CfgLogfilter&&) = default;
};


}  // namespace message

}  // namespace ublox

