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

using AidAlpsrvUpdateField_idSize = field::common::U1;
using AidAlpsrvUpdateField_type =
    field::common::U1T<
        comms::option::DefaultNumValue<0xff>,
        comms::option::ValidNumValueRange<0xff, 0xff>
    >;
using AidAlpsrvUpdateField_ofs = field::common::U2;
using AidAlpsrvUpdateField_size = field::common::U2;
using AidAlpsrvUpdateField_fileId = field::common::U2;
using AidAlpsrvUpdateField_data =
    field::common::ListT<
        field::common::U2,
        comms::option::SequenceSizeForcingEnabled
    >;

using AidAlpsrvUpdateFields = std::tuple<
    AidAlpsrvUpdateField_idSize,
    AidAlpsrvUpdateField_type,
    AidAlpsrvUpdateField_ofs,
    AidAlpsrvUpdateField_size,
    AidAlpsrvUpdateField_fileId,
    AidAlpsrvUpdateField_data
>;

template <typename TMsgBase = Message>
class AidAlpsrvUpdate : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_AID_ALPSRV>,
        comms::option::FieldsImpl<AidAlpsrvUpdateFields>,
        comms::option::DispatchImpl<AidAlpsrvUpdate<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_AID_ALPSRV>,
        comms::option::FieldsImpl<AidAlpsrvUpdateFields>,
        comms::option::DispatchImpl<AidAlpsrvUpdate<TMsgBase> >
    > Base;
public:

    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_idSize,
        FieldIdx_type,
        FieldIdx_ofs,
        FieldIdx_size,
        FieldIdx_fileId,
        FieldIdx_data,
        FieldIdx_numOfValues ///< number of available fields
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    /// @brief Default constructor
    AidAlpsrvUpdate() = default;

    /// @brief Copy constructor
    AidAlpsrvUpdate(const AidAlpsrvUpdate&) = default;

    /// @brief Move constructor
    AidAlpsrvUpdate(AidAlpsrvUpdate&& other) = default;

    /// @brief Destructor
    virtual ~AidAlpsrvUpdate() = default;

    /// @brief Copy assignment
    AidAlpsrvUpdate& operator=(const AidAlpsrvUpdate&) = default;

    /// @brief Move assignment
    AidAlpsrvUpdate& operator=(AidAlpsrvUpdate&&) = default;

protected:
    virtual comms::ErrorStatus readImpl(
        typename Base::ReadIterator& iter,
        std::size_t len) override
    {
        auto es = Base::template readFieldsUntil<FieldIdx_ofs>(iter, len);
        if (es != comms::ErrorStatus::Success) {
            return es;
        }

        auto& allFields = Base::fields();
        auto& typeField = std::get<FieldIdx_type>(allFields);
        if (!typeField.valid()) {
            return comms::ErrorStatus::InvalidMsgData;
        }

        es = Base::template readFieldsFromUntil<FieldIdx_ofs, FieldIdx_data>(iter, len);
        if (es != comms::ErrorStatus::Success) {
            return es;
        }


        auto& sizeField = std::get<FieldIdx_size>(allFields);
        auto& dataField = std::get<FieldIdx_data>(allFields);
        dataField.forceReadElemCount(sizeField.value());

        return Base::template readFieldsFrom<FieldIdx_data>(iter, len);
    }

    virtual bool refreshImpl() override
    {
        auto& allFields = Base::fields();
        auto& sizeField = std::get<FieldIdx_size>(allFields);
        auto& dataField = std::get<FieldIdx_data>(allFields);
        if (sizeField.value() == dataField.value().size()) {
            return false;
        }

        sizeField.value() = dataField.value().size();
        return true;
    }

};


}  // namespace message

}  // namespace ublox





