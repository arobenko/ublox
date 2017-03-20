//
// Copyright 2017 (C). Alex Robenko. All rights reserved.
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
/// @brief Contains definition of MON-PATCH message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the MON-PATCH message fields.
/// @see MonPatch
struct MonPatchFields
{
    /// @brief Definition of "version" field.
    using version =
        field::common::U2T<
            comms::option::ValidNumValueRange<1, 1>,
            comms::option::DefaultNumValue<1>
        >;

    /// @brief Definition of "nEntries" field.
    using nEntries = field::common::U2;

    /// @brief Definition of "activated" single bit bitmask member field of @ref patchInfo bitfield.
    struct activated : public
        field::common::X1T<
            comms::option::FixedBitLength<1>
        >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS(bit);
    };


    /// @brief Value enumeration for @ref location field.
    enum class Location : std::uint8_t
    {
        eFuse, ///< eFuse
        ROM, ///< ROM
        BBR, ///< BBR
        FileSystem, ///< file system
        NumOfValues /// number of available values
    };

    /// @brief Definition of "location" member field of @ref patchInfo bitfield.
    using location =
        field::common::EnumT<
            Location,
            comms::option::FixedBitLength<2>,
            comms::option::ValidNumValueRange<0, (int)Location::NumOfValues - 1>
        >;

    /// @brief Definition of "patchInfo" field.
    struct patchInfo : public
        field::common::BitfieldT<
            std::tuple<
                activated,
                location,
                field::common::res4T<comms::option::FixedBitLength<29> >
            >
        >
    {
        /// @brief Allow access to internal fields.
        /// @details See definition of @b COMMS_FIELD_MEMBERS_ACCESS macro
        ///     related to @b comms::field::Bitfield class from COMMS library
        ///     for details.
        COMMS_FIELD_MEMBERS_ACCESS(activated, location, reserved);
    };

    /// @brief Definition of "comparatorNumber" field.
    using comparatorNumber = field::common::U4;

    /// @brief Definition of "patchAddress" field.
    using patchAddress = field::common::U4;

    /// @brief Definition of "patchData" field.
    using patchData = field::common::U4;

    /// @brief Definition of a block field repeated multiple times in @ref
    ///     data list.
    struct block : public
        field::common::BundleT<
            std::tuple<
                patchInfo,
                comparatorNumber,
                patchAddress,
                patchData
            >
        >
    {
        /// @brief Allow access to internal fields.
        /// @details See definition of @b COMMS_FIELD_MEMBERS_ACCESS macro
        ///     related to @b comms::field::Bitfield class from COMMS library
        ///     for details.
        COMMS_FIELD_MEMBERS_ACCESS(patchInfo, comparatorNumber, patchAddress, patchData);
    };

    /// @brief Definition of "data" field as list of blocks (@ref block).
    /// @tparam TOpt Extra option(s)
    template <typename TOpt = comms::option::EmptyOption>
    using data =
        field::common::ListT<
            block,
            comms::option::SequenceSizeForcingEnabled,
            TOpt
        >;

    /// @brief All the fields bundled in std::tuple.
    /// @tparam TOpt Extra option(s) for @ref data field
    template <typename TOpt>
    using All = std::tuple<
        version,
        nEntries,
        data<TOpt>
    >;
};

/// @brief Definition of MON-PATCH message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref MonPatchFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
/// @tparam TDataOpt Extra option(s) for @b data field
template <typename TMsgBase = Message, typename TDataOpt = comms::option::EmptyOption>
class MonPatch : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_MON_PATCH>,
        comms::option::FieldsImpl<MonPatchFields::All<TDataOpt> >,
        comms::option::MsgType<MonPatch<TMsgBase, TDataOpt> >,
        comms::option::HasDoRefresh
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_MON_PATCH>,
        comms::option::FieldsImpl<MonPatchFields::All<TDataOpt> >,
        comms::option::MsgType<MonPatch<TMsgBase, TDataOpt> >,
        comms::option::HasDoRefresh
    > Base;
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b version for @ref MonPatchFields::version field
    ///     @li @b nEntries for @ref MonPatchFields::nEntries field
    ///     @li @b data for @ref MonPatchFields::data field
    COMMS_MSG_FIELDS_ACCESS(version, nEntries, data);

    /// @brief Default constructor
    MonPatch() = default;

    /// @brief Copy constructor
    MonPatch(const MonPatch&) = default;

    /// @brief Move constructor
    MonPatch(MonPatch&& other) = default;

    /// @brief Destructor
    ~MonPatch() = default;

    /// @brief Copy assignment
    MonPatch& operator=(const MonPatch&) = default;

    /// @brief Move assignment
    MonPatch& operator=(MonPatch&&) = default;

    /// @brief Provides custom read functionality.
    /// @details The number of blocks in @b data (@ref MonPatchFields::data)
    ///     list is determined by the value of @b nEntries (@ref MonPatchFields::nEntries)
    ///     field.
    template <typename TIter>
    comms::ErrorStatus doRead(TIter& iter, std::size_t len)
    {
        auto es = Base::template readFieldsUntil<FieldIdx_data>(iter, len);
        if (es != comms::ErrorStatus::Success) {
            return es;
        }

        field_data().forceReadElemCount(field_nEntries().value());
        return Base::template readFieldsFrom<FieldIdx_data>(iter, len);
    }

    /// @brief Provides custom refresh functionality
    /// @details The value of @b nEntries (@ref MonPatchFields::nEntries) field is
    ///     determined by number of blocks stored in @b data (@ref MonPatchFields::data)
    ///     list.
    /// @return @b true in case the value of "nEntries" field was modified, @b false otherwise
    bool doRefresh()
    {
        if (field_nEntries().value() == field_data().value().size()) {
            return false;
        }

        field_nEntries().value() = field_data().value().size();
        return true;
    }

};


}  // namespace message

}  // namespace ublox





