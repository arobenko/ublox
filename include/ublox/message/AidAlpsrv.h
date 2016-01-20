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

/// @file
/// @brief Contains definition of AID-ALPSRV message and its fields.

#pragma once

#include <iterator>

#include "ublox/Message.h"

#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the AID-ALPSRV message fields.
/// @see AidAlpsrv
struct AidAlpsrvFields
{
    /// @brief Definition of "idSize" field.
    using idSize = field::common::U1;

    /// @brief Definition of "type" field.
    using type =
        field::common::U1T<
            comms::option::ValidNumValueRange<0, 0xfe>
        >;

    /// @brief Definition of "ofs" field.
    using ofs = field::common::U2;

    /// @brief Definition of "size" field.
    using size = field::common::U2;

    /// @brief Definition of "fileId" field.
    using fileId = field::common::U2;

    /// @brief Definition of "dataSize" field.
    using dataSize = field::common::U2;

    /// @brief Definition of "id1" field.
    using id1 = field::common::U1;

    /// @brief Definition of "id2" field.
    using id2 = field::common::U1;

    /// @brief Definition of "id3" field.
    using id3 = field::common::U4;

    /// @brief Definition of "data" field.
    using data =
        field::common::ListT<
            std::uint8_t,
            comms::option::SequenceSizeForcingEnabled
        >;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        idSize,
        type,
        ofs,
        size,
        fileId,
        dataSize,
        id1,
        id2,
        id3,
        data
    >;
};

/// @brief Definition of AID-ALPSRV message
/// @details Inherits from
///     <a href="https://dl.dropboxusercontent.com/u/46999418/comms_champion/comms/html/classcomms_1_1MessageBase.html">comms::MessageBase</a>
///     while providing @b TMsgBase as common interface class as well as
///     @b comms::option::StaticNumIdImpl, @b comms::option::FieldsImpl, and
///     @b comms::option::DispatchImpl as options. @n
///     See @ref AidAlpsrvFields and for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class AidAlpsrv : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_AID_ALPSRV>,
        comms::option::FieldsImpl<AidAlpsrvFields::All>,
        comms::option::DispatchImpl<AidAlpsrv<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_AID_ALPSRV>,
        comms::option::FieldsImpl<AidAlpsrvFields::All>,
        comms::option::DispatchImpl<AidAlpsrv<TMsgBase> >
    > Base;
public:

    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_idSize, ///< idSize field, see @ref AidAlpsrvFields::idSize
        FieldIdx_type, ///< type field, see @ref AidAlpsrvFields::type
        FieldIdx_ofs, ///< ofs field, see @ref AidAlpsrvFields::ofs
        FieldIdx_size, ///< size field, see @ref AidAlpsrvFields::size
        FieldIdx_fileId, ///< type fileId, see @ref AidAlpsrvFields::fileId
        FieldIdx_dataSize, ///< dataSize field, see @ref AidAlpsrvFields::dataSize
        FieldIdx_id1, ///< id1 field, see @ref AidAlpsrvFields::id1
        FieldIdx_id2, ///< id2 field, see @ref AidAlpsrvFields::id2
        FieldIdx_id3, ///< id3 field, see @ref AidAlpsrvFields::id3
        FieldIdx_data, ///< data field, see @ref AidAlpsrvFields::data
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

    /// @brief Overrides read functionality provided by the base class.
    /// @details The function reads all the fields up and including "type"
    ///     (see @ref AidAlpsrvFields::type). If its value is invalid (equal to
    ///     0xff), the read operation fails with comms::ErrorStatus::InvalidMsgData
    ///     error status, otherwise continues. The size of the "data" list
    ///     (see @ref AidAlpsrvFields::data) is determined by the value of
    ///     "dataSize" field (see @ref AidAlpsrvFields::dataSize).
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

    /// @brief Overrides default refreshing functionality provided by the interface class.
    /// @details The value of "dataSize" field (see @ref AidAlpsrvFields::dataSize) is
    ///     determined by the size of the "data" list (see @ref AidAlpsrvFields::data).
    /// @return @b true in case the mode of "dataSize" field was modified, @b false otherwise
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





