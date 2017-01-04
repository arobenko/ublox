//
// Copyright 2015 - 2016 (C). Alex Robenko. All rights reserved.
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
/// @brief Contains definition of AID-ALPSRV (@b udpate) message and its fields.

#pragma once

#include <iterator>

#include "ublox/Message.h"

#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the AID-ALPSRV (@b update) message fields.
/// @see AidAlpsrvUpdate
struct AidAlpsrvUpdateFields
{
    /// @brief Definition of "idSize" field.
    using idSize = field::common::U1;

    /// @brief Definition of "type" field.
    using type =
        field::common::U1T<
            comms::option::DefaultNumValue<0xff>,
            comms::option::ValidNumValueRange<0xff, 0xff>
        >;

    /// @brief Definition of "ofs" field.
    using ofs = field::common::U2;

    /// @brief Definition of "size" field.
    using size = field::common::U2;

    /// @brief Definition of "fileId" field.
    using fileId = field::common::U2;

    /// @brief Definition of "data" field.
    using data =
        field::common::ListT<
            field::common::U2,
            comms::option::SequenceSizeForcingEnabled
        >;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        idSize,
        type,
        ofs,
        size,
        fileId,
        data
    >;
};

/// @brief Definition of AID-ALPSRV (@b update) message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref AidAlpsrvUpdateFields and for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class AidAlpsrvUpdate : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_AID_ALPSRV>,
        comms::option::FieldsImpl<AidAlpsrvUpdateFields::All>,
        comms::option::MsgType<AidAlpsrvUpdate<TMsgBase> >,
        comms::option::HasDoRefresh
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_AID_ALPSRV>,
        comms::option::FieldsImpl<AidAlpsrvUpdateFields::All>,
        comms::option::MsgType<AidAlpsrvUpdate<TMsgBase> >,
        comms::option::HasDoRefresh
    > Base;
public:


#ifdef FOR_DOXYGEN_DOC_ONLY
    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_idSize, ///< idSize field, see @ref AidAlpsrvUpdateFields::idSize
        FieldIdx_type, ///< type field, see @ref AidAlpsrvUpdateFields::type
        FieldIdx_ofs, ///< ofs field, see @ref AidAlpsrvUpdateFields::ofs
        FieldIdx_size, ///< size field, see @ref AidAlpsrvUpdateFields::size
        FieldIdx_fileId, ///< fileId field, see @ref AidAlpsrvUpdateFields::fileId
        FieldIdx_data, ///< data field, see @ref AidAlpsrvUpdateFields::data
        FieldIdx_numOfValues ///< number of available fields
    };

    /// @brief Access to fields bundled as a struct
    struct FieldsAsStruct
    {
        AidAlpsrvUpdateFields::idSize& idSize; ///< idSize field, see @ref AidAlpsrvUpdateFields::idSize
        AidAlpsrvUpdateFields::type& type; ///< type field, see @ref AidAlpsrvUpdateFields::type
        AidAlpsrvUpdateFields::ofs& ofs; ///< ofs field, see @ref AidAlpsrvUpdateFields::ofs
        AidAlpsrvUpdateFields::size& size; ///< size field, see @ref AidAlpsrvUpdateFields::size
        AidAlpsrvUpdateFields::fileId& fileId; ///< fileId field, see @ref AidAlpsrvUpdateFields::fileId
        AidAlpsrvUpdateFields::data& data; ///< data field, see @ref AidAlpsrvUpdateFields::data
    };

    /// @brief Access to @b const fields bundled as a struct
    struct ConstFieldsAsStruct
    {
        const AidAlpsrvUpdateFields::idSize& idSize; ///< idSize field, see @ref AidAlpsrvUpdateFields::idSize
        const AidAlpsrvUpdateFields::type& type; ///< type field, see @ref AidAlpsrvUpdateFields::type
        const AidAlpsrvUpdateFields::ofs& ofs; ///< ofs field, see @ref AidAlpsrvUpdateFields::ofs
        const AidAlpsrvUpdateFields::size& size; ///< size field, see @ref AidAlpsrvUpdateFields::size
        const AidAlpsrvUpdateFields::fileId& fileId; ///< fileId field, see @ref AidAlpsrvUpdateFields::fileId
        const AidAlpsrvUpdateFields::data& data; ///< data field, see @ref AidAlpsrvUpdateFields::data
    };

    /// @brief Get access to fields bundled into a struct
    FieldsAsStruct fieldsAsStruct();

    /// @brief Get access to @b const fields bundled into a struct
    ConstFieldsAsStruct fieldsAsStruct() const;

#else
    COMMS_MSG_FIELDS_ACCESS(Base, idSize, type, ofs, size, fileId, data);
#endif // #ifdef FOR_DOXYGEN_DOC_ONLY

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

    /// @brief Provides custom read functionality.
    /// @details The function reads all the fields up and including "type"
    ///     (see @ref AidAlpsrvUpdateFields::type). If its value is invalid (@b NOT equal to
    ///     0xff), the read operation fails with comms::ErrorStatus::InvalidMsgData
    ///     error status, otherwise continues. The size of the "data" list
    ///     (see @ref AidAlpsrvUpdateFields::data) is determined by the value of
    ///     "size" field (see @ref AidAlpsrvUpdateFields::size).
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


        auto& sizeField = std::get<FieldIdx_size>(allFields);
        auto& dataField = std::get<FieldIdx_data>(allFields);
        dataField.forceReadElemCount(sizeField.value());

        return Base::template readFieldsFrom<FieldIdx_data>(iter, len);
    }

    /// @brief Provides custom refreshing functionality.
    /// @details The value of "size" field (see @ref AidAlpsrvUpdateFields::size) is
    ///     determined by the size of the "data" list (see @ref AidAlpsrvUpdateFields::data).
    /// @return @b true in case the mode of "size" field was modified, @b false otherwise
    bool doRefresh()
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





