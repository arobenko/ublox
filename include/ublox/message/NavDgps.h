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
/// @brief Contains definition of NAV-DGPS message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/nav.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the NAV-DGPS message fields.
/// @see NavDgps
struct NavDgpsFields
{
    /// @brief Value enumeration for @ref status field.
    enum class Status : std::uint8_t
    {
        None, ///< none
        PR_PRR_Correction, ///< PR + PRR Correction
        NumOfValues ///< number of available values
    };


    /// @brief Use this enumeration to access member fields of @ref flags bitfield.
    enum
    {
        flags_channel, ///< index of @ref channel member field
        flags_bits, ///< index of @ref flagsBits member field
        flags_numOfValues ///< number of available member fields
    };

    /// @brief Bits access enumeration for bits in @b flagsBits member of
    ///     @ref flags bitfield field.
    enum
    {
        flagsBits_dgpsUsed, ///< @b dgpsUsed bit index
        flagsBits_numOfValues ///< number of available bits
    };

    /// @brief Use this enumeration to access member fields of @ref block bundle.
    enum
    {
        block_svid, ///< index of @ref svid member field
        block_flags, ///< index of @ref flags member field
        block_ageC, ///< index of @ref ageC member field
        block_prc, ///< index of @ref prc member field
        block_prrc, ///< index of @ref prrc member field
        block_numOfValues ///< number of availble member fields
    };

    /// @brief Definition of "iTOW" field.
    using iTOW = field::nav::iTOW;

    /// @brief Definition of "age" field.
    using age = field::common::I4T<field::common::Scaling_ms2s>;

    /// @brief Definition of "baseId" field.
    using baseId = field::common::I2;

    /// @brief Definition of "baseHealth" field.
    using baseHealth = field::common::I2;

    /// @brief Definition of "numCh" field.
    using numCh = field::nav::numCh;

    /// @brief Definition of "status" field.
    using status =
        field::common::EnumT<
            Status,
            comms::option::ValidNumValueRange<0, (int)Status::NumOfValues - 1>
        >;

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res2;

    /// @brief Definition of "svid" field.
    using svid = field::nav::svid;

    /// @brief Definition of "channel" member field in @ref flags bitfield.
    using channel =
        field::common::U1T<
            comms::option::FixedBitLength<4>,
            comms::option::ValidNumValueRange<0, 15>
        >;

    /// @brief Definition of remaining bits as a single bitmask member field in @ref flags bitfield.
    using flagsBits =
        field::common::X1T<
            comms::option::FixedBitLength<4>,
            comms::option::BitmaskReservedBits<0xfe, 0>
        >;

    /// @brief Definition of "flags" field.
    using flags =
        field::common::BitfieldT<
            std::tuple<
                channel,
                flagsBits
            >
        >;

    /// @brief Definition of "agec" field.
    using ageC = field::common::U2T<field::common::Scaling_ms2s>;

    /// @brief Definition of "prc" field.
    using prc = field::common::R4;

    /// @brief Definition of "prrc" field.
    using prrc = field::common::R4;

    /// @brief Definition of the repeated block as a single bundle field
    using block =
        field::common::BundleT<
            std::tuple<
                svid,
                flags,
                ageC,
                prc,
                prrc
            >
        >;

    /// @brief Definition of the list of repeated blocks (@ref block).
    using data =
        field::common::ListT<
            block,
            comms::option::SequenceSizeForcingEnabled
        >;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        iTOW,
        age,
        baseId,
        baseHealth,
        numCh,
        status,
        reserved1,
        data
    >;
};

/// @brief Definition of NAV-DGPS message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref NavDgpsFields and for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class NavDgps : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_DGPS>,
        comms::option::FieldsImpl<NavDgpsFields::All>,
        comms::option::MsgType<NavDgps<TMsgBase> >,
        comms::option::HasDoRefresh
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_DGPS>,
        comms::option::FieldsImpl<NavDgpsFields::All>,
        comms::option::MsgType<NavDgps<TMsgBase> >,
        comms::option::HasDoRefresh
    > Base;
public:

#ifdef FOR_DOXYGEN_DOC_ONLY
    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_iTOW, ///< @b iTOW field, see @ref NavDgpsFields::iTOW
        FieldIdx_age, ///< @b age field, see @ref NavDgpsFields::age
        FieldIdx_baseId, ///< @b baseId field, see @ref NavDgpsFields::baseId
        FieldIdx_baseHealth, ///< @b baseHealth field, see @ref NavDgpsFields::baseHealth
        FieldIdx_numCh, ///< @b numCh field, see @ref NavDgpsFields::numCh
        FieldIdx_status, ///< @b status field, see @ref NavDgpsFields::status
        FieldIdx_reserved1, ///< @b reserved1 field, see @ref NavDgpsFields::reserved1
        FieldIdx_data, ///< @b data field, see @ref NavDgpsFields::data
        FieldIdx_numOfValues ///< number of available fields
    };

    /// @brief Access to fields bundled as a struct
    struct FieldsAsStruct
    {
        NavDgpsFields::iTOW& iTOW; ///< @b iTOW field, see @ref NavDgpsFields::iTOW
        NavDgpsFields::age& age; ///< @b age field, see @ref NavDgpsFields::age
        NavDgpsFields::baseId& baseId; ///< @b baseId field, see @ref NavDgpsFields::baseId
        NavDgpsFields::baseHealth& baseHealth; ///< @b baseHealth field, see @ref NavDgpsFields::baseHealth
        NavDgpsFields::numCh& numCh; ///< @b numCh field, see @ref NavDgpsFields::numCh
        NavDgpsFields::status& status; ///< @b status field, see @ref NavDgpsFields::status
        NavDgpsFields::reserved1& reserved1; ///< @b reserved1 field, see @ref NavDgpsFields::reserved1
        NavDgpsFields::data& data; ///< @b data field, see @ref NavDgpsFields::data
    };

    /// @brief Access to @b const fields bundled as a struct
    struct ConstFieldsAsStruct
    {
        const NavDgpsFields::iTOW& iTOW; ///< @b iTOW field, see @ref NavDgpsFields::iTOW
        const NavDgpsFields::age& age; ///< @b age field, see @ref NavDgpsFields::age
        const NavDgpsFields::baseId& baseId; ///< @b baseId field, see @ref NavDgpsFields::baseId
        const NavDgpsFields::baseHealth& baseHealth; ///< @b baseHealth field, see @ref NavDgpsFields::baseHealth
        const NavDgpsFields::numCh& numCh; ///< @b numCh field, see @ref NavDgpsFields::numCh
        const NavDgpsFields::status& status; ///< @b status field, see @ref NavDgpsFields::status
        const NavDgpsFields::reserved1& reserved1; ///< @b reserved1 field, see @ref NavDgpsFields::reserved1
        const NavDgpsFields::data& data; ///< @b data field, see @ref NavDgpsFields::data
    };

    /// @brief Get access to fields bundled into a struct
    FieldsAsStruct fieldsAsStruct();

    /// @brief Get access to @b const fields bundled into a struct
    ConstFieldsAsStruct fieldsAsStruct() const;

#else
    COMMS_MSG_FIELDS_ACCESS(Base,
        iTOW,
        age,
        baseId,
        baseHealth,
        numCh,
        status,
        reserved1,
        data
    );
#endif // #ifdef FOR_DOXYGEN_DOC_ONLY

    /// @brief Default constructor
    NavDgps() = default;

    /// @brief Copy constructor
    NavDgps(const NavDgps&) = default;

    /// @brief Move constructor
    NavDgps(NavDgps&& other) = default;

    /// @brief Destructor
    virtual ~NavDgps() = default;

    /// @brief Copy assignment
    NavDgps& operator=(const NavDgps&) = default;

    /// @brief Move assignment
    NavDgps& operator=(NavDgps&&) = default;

    /// @brief Provides custom read functionality.
    /// @details The number of blocks in @b data (@ref NavDgpsFields::data)
    ///     list is determined by the value of @b numCh (@ref NavDgpsFields::numCh)
    ///     field.
    template <typename TIter>
    comms::ErrorStatus doRead(TIter& iter, std::size_t len)
    {
        auto es = Base::template readFieldsUntil<FieldIdx_data>(iter, len);
        if (es != comms::ErrorStatus::Success) {
            return es;
        }

        auto& allFields = Base::fields();
        auto& numChField = std::get<FieldIdx_numCh>(allFields);
        auto& dataField = std::get<FieldIdx_data>(allFields);
        dataField.forceReadElemCount(numChField.value());

        return Base::template readFieldsFrom<FieldIdx_data>(iter, len);
    }

    /// @brief Provides custom refresh functionality
    /// @details The value of @b numCh (@ref NavDgpsFields::numCh) field is
    ///     determined by the number of elements in the internal storage collection
    ///     of the @b data (@ref NavDgpsFields::data) list.
    /// @return @b true in case the value of "numCh" field was modified, @b false otherwise
    bool doRefresh()
    {
        auto& allFields = Base::fields();
        auto& numChField = std::get<FieldIdx_numCh>(allFields);
        auto& dataField = std::get<FieldIdx_data>(allFields);
        if (numChField.value() == dataField.value().size()) {
            return false;
        }

        numChField.value() = dataField.value().size();
        return true;
    }

};

}  // namespace message

}  // namespace ublox





