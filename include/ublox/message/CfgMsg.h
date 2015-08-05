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

#include "ublox/Message.h"
#include "ublox/field/MsgId.h"
#include "ublox/field/cfg.h"

namespace ublox
{

namespace message
{

using CfgMsgSingleRateFields =
    comms::field::Bundle<
        std::tuple<
            ublox::field::MsgId,
            ublox::field::cfg::Rate
        >
    >;

using CfgMsgMultiRateFields =
    comms::field::ArrayList<
        ublox::field::common::FieldBase,
        comms::field::Bundle<
            std::tuple<
                ublox::field::MsgId,
                ublox::field::cfg::Rate,
                ublox::field::cfg::Rate,
                ublox::field::cfg::Rate,
                ublox::field::cfg::Rate
            >
        >
    >;


using CfgMsgFields = std::tuple<
    comms::field::Optional<CfgMsgSingleRateFields>,
    comms::field::Optional<CfgMsgMultiRateFields>
>;


template <typename TMsgBase = Message>
class CfgMsg : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_MSG>,
        comms::option::FieldsImpl<CfgMsgFields>,
        comms::option::DispatchImpl<CfgMsg<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_MSG>,
        comms::option::FieldsImpl<CfgMsgFields>,
        comms::option::DispatchImpl<CfgMsg<TMsgBase> >
    > Base;
public:
    enum FieldIdx
    {
        FieldIdx_SingleRate,
        FieldIdx_MultiRate,
        FieldIdx_NumOfValues
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_NumOfValues,
        "Number of fields is incorrect");

    CfgMsg()
    {
        auto& allFields = Base::fields();
        auto& singleRateField = std::get<FieldIdx_SingleRate>(allFields);
        auto& multiRateField = std::get<FieldIdx_MultiRate>(allFields);
        singleRateField.setMode(comms::field::OptionalMode::Exists);
        multiRateField.setMode(comms::field::OptionalMode::Missing);
    }

    CfgMsg(const CfgMsg&) = default;
    CfgMsg(CfgMsg&& other) = default;
    virtual ~CfgMsg() = default;

    CfgMsg& operator=(const CfgMsg&) = default;
    CfgMsg& operator=(CfgMsg&&) = default;

protected:
    virtual comms::ErrorStatus readImpl(
        typename Base::ReadIterator& iter,
        std::size_t len) override
    {
        auto& allFields = Base::fields();
        auto& singleRateField = std::get<FieldIdx_SingleRate>(allFields);
        auto& multiRateField = std::get<FieldIdx_MultiRate>(allFields);
        if (len == CfgMsgSingleRateFields::maxLength()) {
            singleRateField.setMode(comms::field::OptionalMode::Exists);
            multiRateField.setMode(comms::field::OptionalMode::Missing);
        }
        else {
            singleRateField.setMode(comms::field::OptionalMode::Missing);
            multiRateField.setMode(comms::field::OptionalMode::Exists);
        }

        return Base::readImpl(iter, len);
    }

    virtual bool refreshImpl() override
    {
        auto& allFields = Base::fields();
        auto& singleRateField = std::get<FieldIdx_SingleRate>(allFields);
        auto& multiRateField = std::get<FieldIdx_MultiRate>(allFields);

        auto expectedMultiRateMode = comms::field::OptionalMode::Missing;
        if (singleRateField.getMode() != comms::field::OptionalMode::Exists) {
            expectedMultiRateMode = comms::field::OptionalMode::Exists;
        }

        if (multiRateField.getMode() == expectedMultiRateMode) {
            return false;
        }

        multiRateField.setMode(expectedMultiRateMode);
        return true;
    }
};


}  // namespace message

}  // namespace ublox

