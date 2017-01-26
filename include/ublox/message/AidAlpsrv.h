//
// Copyright 2015 - 2017 (C). Alex Robenko. All rights reserved.
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
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref AidAlpsrvFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class AidAlpsrv : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_AID_ALPSRV>,
        comms::option::FieldsImpl<AidAlpsrvFields::All>,
        comms::option::MsgType<AidAlpsrv<TMsgBase> >,
        comms::option::HasDoRefresh
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_AID_ALPSRV>,
        comms::option::FieldsImpl<AidAlpsrvFields::All>,
        comms::option::MsgType<AidAlpsrv<TMsgBase> >,
        comms::option::HasDoRefresh
    > Base;
public:
    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b idSize for @ref AidAlpsrvFields::idSize field
    ///     @li @b type for @ref AidAlpsrvFields::type field
    ///     @li @b ofs for @ref AidAlpsrvFields::ofs field
    ///     @li @b size for @ref AidAlpsrvFields::size field
    ///     @li @b fileId for @ref AidAlpsrvFields::fileId field
    ///     @li @b dataSize for @ref AidAlpsrvFields::dataSize field
    ///     @li @b id1 for @ref AidAlpsrvFields::id1 field
    ///     @li @b id2 for @ref AidAlpsrvFields::id2 field
    ///     @li @b id3 for @ref AidAlpsrvFields::id3 field
    ///     @li @b data for @ref AidAlpsrvFields::data field
    COMMS_MSG_FIELDS_ACCESS(idSize, type, ofs, size, fileId, dataSize, id1, id2, id3, data);

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

    /// @brief Provides custom read functionality.
    /// @details The function reads all the fields up and including "type"
    ///     (see @ref AidAlpsrvFields::type). If its value is invalid (equal to
    ///     0xff), the read operation fails with comms::ErrorStatus::InvalidMsgData
    ///     error status, otherwise continues. The size of the "data" list
    ///     (see @ref AidAlpsrvFields::data) is determined by the value of
    ///     "dataSize" field (see @ref AidAlpsrvFields::dataSize).
    template <typename TIter>
    comms::ErrorStatus doRead(TIter& iter, std::size_t len)
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

    /// @brief Provides custom refreshing functionality.
    /// @details The value of "dataSize" field (see @ref AidAlpsrvFields::dataSize) is
    ///     determined by the size of the "data" list (see @ref AidAlpsrvFields::data).
    /// @return @b true in case the mode of "dataSize" field was modified, @b false otherwise
    bool doRefresh()
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





