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

#include <iterator>

#include "comms/Message.h"
#include "ublox/Message.h"

#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

enum class AidAlpStatus_Status : std::uint8_t
{
    NAK,
    ACK,
    NumOfValues
};

using AidAlpStatusField_status =
    field::common::EnumT<
        AidAlpStatus_Status,
        comms::option::ValidNumValueRange<0,(int)AidAlpStatus_Status::NumOfValues - 1>
    >;

using AidAlpStatusFields = std::tuple<
    AidAlpStatusField_status
>;

template <typename TMsgBase = Message>
class AidAlpStatus : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_AID_ALP>,
        comms::option::FieldsImpl<AidAlpStatusFields>,
        comms::option::DispatchImpl<AidAlpStatus<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_AID_ALP>,
        comms::option::FieldsImpl<AidAlpStatusFields>,
        comms::option::DispatchImpl<AidAlpStatus<TMsgBase> >
    > Base;
public:

    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_status,
        FieldIdx_numOfValues ///< number of available fields
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    /// @brief Default constructor
    AidAlpStatus() = default;

    /// @brief Copy constructor
    AidAlpStatus(const AidAlpStatus&) = default;

    /// @brief Move constructor
    AidAlpStatus(AidAlpStatus&& other) = default;

    /// @brief Destructor
    virtual ~AidAlpStatus() = default;

    /// @brief Copy assignment
    AidAlpStatus& operator=(const AidAlpStatus&) = default;

    /// @brief Move assignment
    AidAlpStatus& operator=(AidAlpStatus&&) = default;

protected:
    virtual comms::ErrorStatus readImpl(
        typename Base::ReadIterator& iter,
        std::size_t len) override
    {
        auto& allFields = Base::fields();
        auto& statusField = std::get<FieldIdx_status>(allFields);
        if (len != statusField.length()) {
            return comms::ErrorStatus::InvalidMsgData;
        }

        return Base::readImpl(iter, len);
    }

};


}  // namespace message

}  // namespace ublox





