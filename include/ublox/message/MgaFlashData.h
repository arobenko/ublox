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
/// @brief Contains definition of MGA-FLASH-DATA message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the MGA-FLASH-DATA message fields.
/// @see MgaFlashData
struct MgaFlashDataFields
{

    /// @brief Definition of "type" field.
    using type  =
    field::common::U1T<
        comms::option::ValidNumValueRange<1, 1>,
        comms::option::DefaultNumValue<1>,
        comms::option::FailOnInvalid<>
    >;

    /// @brief Definition of "version" field.
    using version =
        field::common::U1T<
            comms::option::ValidNumValueRange<0, 0>
        >;

    /// @brief Definition of "sequence" field.
    using sequence = field::common::U2;

    /// @brief Definition of "size" field.
    using size = field::common::U2;

    /// @brief Definition of "data" field.
    /// @tparam TOpt Extra option(s)
    template <typename TOpt = comms::option::EmptyOption>
    using data =
        field::common::ListT<
            std::uint8_t,
            comms::option::SequenceSizeForcingEnabled,
            TOpt
        >;

    /// @brief All the fields bundled in std::tuple.
    /// @tparam TOpt Extra option(s) for @ref data field
    template <typename TOpt>
    using All = std::tuple<
        type,
        version,
        sequence,
        size,
        data<TOpt>
    >;
};

/// @brief Definition of MGA-FLASH-DATA message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref MgaFlashDataFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
/// @tparam TDataOpt Extra option(s) for @b data field
template <typename TMsgBase = Message, typename TDataOpt = comms::option::EmptyOption>
class MgaFlashData : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_MGA_FLASH>,
        comms::option::FieldsImpl<MgaFlashDataFields::All<TDataOpt> >,
        comms::option::MsgType<MgaFlashData<TMsgBase, TDataOpt> >,
        comms::option::HasDoRefresh
    >
{
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b type for @ref MgaFlashDataFields::type field
    ///     @li @b version for @ref MgaFlashDataFields::version field
    ///     @li @b sequence for @ref MgaFlashDataFields::sequence field
    ///     @li @b size for @ref MgaFlashDataFields::size field
    ///     @li @b data for @ref MgaFlashDataFields::data field
    COMMS_MSG_FIELDS_ACCESS(
        type,
        version,
        sequence,
        size,
        data
    );

    /// @brief Default constructor
    MgaFlashData() = default;

    /// @brief Copy constructor
    MgaFlashData(const MgaFlashData&) = default;

    /// @brief Move constructor
    MgaFlashData(MgaFlashData&& other) = default;

    /// @brief Destructor
    ~MgaFlashData() = default;

    /// @brief Copy assignment
    MgaFlashData& operator=(const MgaFlashData&) = default;

    /// @brief Move assignment
    MgaFlashData& operator=(MgaFlashData&&) = default;

    /// @brief Provides custom read functionality.
    /// @details The number of blocks in @b data (@ref MgaFlashDataFields::data)
    ///     list is determined by the value of @b size (@ref MgaFlashDataFields::size)
    ///     field.
    template <typename TIter>
    comms::ErrorStatus doRead(TIter& iter, std::size_t len)
    {
        using Base = typename std::decay<decltype(comms::toMessageBase(*this))>::type;
        auto es = Base::template readFieldsUntil<FieldIdx_data>(iter, len);
        if (es != comms::ErrorStatus::Success) {
            return es;
        }

        field_data().forceReadElemCount(field_size().value());
        return Base::template readFieldsFrom<FieldIdx_data>(iter, len);
    }

    /// @brief Provides custom refresh functionality
    /// @details The value of @b size (@ref MgaFlashDataFields::size) field is
    ///     determined by number of bytes stored in @b data (@ref MgaFlashDataFields::data)
    ///     list.
    /// @return @b true in case the value of "size" field was modified, @b false otherwise
    bool doRefresh()
    {
        if (field_size().value() == field_data().value().size()) {
            return false;
        }

        field_size().value() = field_data().value().size();
        return true;
    }
};


}  // namespace message

}  // namespace ublox





