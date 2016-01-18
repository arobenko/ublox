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
#include "ublox/field/cfg.h"

namespace ublox
{

namespace message
{

using CfgTp5PollSelectField_tpIdx = field::cfg::tpIdx;

using CfgTp5PollSelectFields = std::tuple<
    CfgTp5PollSelectField_tpIdx
>;

template <typename TMsgBase = Message>
class CfgTp5PollSelect : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_TP5>,
        comms::option::FieldsImpl<CfgTp5PollSelectFields>,
        comms::option::DispatchImpl<CfgTp5PollSelect<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_TP5>,
        comms::option::FieldsImpl<CfgTp5PollSelectFields>,
        comms::option::DispatchImpl<CfgTp5PollSelect<TMsgBase> >
    > Base;
public:

    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_tpIdx,
        FieldIdx_numOfValues ///< number of available fields
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    /// @brief Default constructor
    CfgTp5PollSelect() = default;

    /// @brief Copy constructor
    CfgTp5PollSelect(const CfgTp5PollSelect&) = default;

    /// @brief Move constructor
    CfgTp5PollSelect(CfgTp5PollSelect&& other) = default;

    /// @brief Destructor
    virtual ~CfgTp5PollSelect() = default;

    /// @brief Copy assignment
    CfgTp5PollSelect& operator=(const CfgTp5PollSelect&) = default;

    /// @brief Move assignment
    CfgTp5PollSelect& operator=(CfgTp5PollSelect&&) = default;
};


}  // namespace message

}  // namespace ublox

