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

using AidAlpsrvField_idSize = field::common::U1;
using AidAlpsrvField_type =
    field::common::U1T<
        comms::option::ValidNumValueRange<0, 0xfe>
    >;
using AidAlpsrvField_ofs = field::common::U2;
using AidAlpsrvField_size = field::common::U2;
using AidAlpsrvField_fileId = field::common::U2;
using AidAlpsrvField_dataSize = field::common::U2;
using AidAlpsrvField_id1 = field::common::U1;
using AidAlpsrvField_id2 = field::common::U1;
using AidAlpsrvField_id3 = field::common::U4;
using AidAlpsrvField_data =
    field::common::ListT<
        std::uint8_t,
        comms::option::SequenceSizeForcingEnabled
    >;

using AidAlpsrvFields = std::tuple<
    AidAlpsrvField_idSize,
    AidAlpsrvField_type,
    AidAlpsrvField_ofs,
    AidAlpsrvField_size,
    AidAlpsrvField_fileId,
    AidAlpsrvField_dataSize,
    AidAlpsrvField_id1,
    AidAlpsrvField_id2,
    AidAlpsrvField_id3,
    AidAlpsrvField_data
>;

template <typename TMsgBase = Message>
class AidAlpsrv : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_AID_ALPSRV>,
        comms::option::FieldsImpl<AidAlpsrvFields>,
        comms::option::DispatchImpl<AidAlpsrv<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_AID_ALPSRV>,
        comms::option::FieldsImpl<AidAlpsrvFields>,
        comms::option::DispatchImpl<AidAlpsrv<TMsgBase> >
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
        FieldIdx_dataSize,
        FieldIdx_id1,
        FieldIdx_id2,
        FieldIdx_id3,
        FieldIdx_data,
        FieldIdx_numOfValues ///< number of available fields
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    /// @brief Default constructor
    AidAlpsrv() = default;

    /// @brief Copy constructor
    AidAlpsrv(const AidAlpsrv&) = default;

    /// @brief Move constructor
    AidAlpsrv(AidAlpsrv&& other) = default;

    /// @brief Destructor
    virtual ~AidAlpsrv() = default;

    /// @brief Copy assignment
    AidAlpsrv& operator=(const AidAlpsrv&) = default;

    /// @brief Move assignment
    AidAlpsrv& operator=(AidAlpsrv&&) = default;

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


        auto& dataSizeField = std::get<FieldIdx_dataSize>(allFields);
        auto& dataField = std::get<FieldIdx_data>(allFields);
        dataField.forceReadElemCount(dataSizeField.value());

        return Base::template readFieldsFrom<FieldIdx_data>(iter, len);
    }

    virtual bool refreshImpl() override
    {
        auto& allFields = Base::fields();
        auto& dataSizeField = std::get<FieldIdx_dataSize>(allFields);
        auto& dataField = std::get<FieldIdx_data>(allFields);
        if (dataSizeField.value() == dataField.value().size()) {
            return false;
        }

        dataSizeField.value() = dataField.value().size();
        return true;
    }

};


}  // namespace message

}  // namespace ublox





