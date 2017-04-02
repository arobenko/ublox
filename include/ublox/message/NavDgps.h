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
    struct flagsBits : public
        field::common::X1T<
            comms::option::FixedBitLength<4>,
            comms::option::BitmaskReservedBits<0xfe, 0>
        >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS(dgpsUsed);
    };

    /// @brief Definition of "flags" field.
    struct flags : public
        field::common::BitfieldT<
            std::tuple<
                channel,
                flagsBits
            >
        >
    {
        /// @brief Allow access to internal fields.
        /// @details See definition of @b COMMS_FIELD_MEMBERS_ACCESS macro
        ///     related to @b comms::field::Bitfield class from COMMS library
        ///     for details.
        COMMS_FIELD_MEMBERS_ACCESS(channel, flagsBits);
    };

    /// @brief Definition of "agec" field.
    using ageC = field::common::U2T<field::common::Scaling_ms2s>;

    /// @brief Definition of "prc" field.
    using prc = field::common::R4;

    /// @brief Definition of "prrc" field.
    using prrc = field::common::R4;

    /// @brief Definition of the repeated block as a single bundle field
    struct block : public
        field::common::BundleT<
            std::tuple<
                svid,
                flags,
                ageC,
                prc,
                prrc
            >
        >
    {
        /// @brief Allow access to internal fields.
        /// @details See definition of @b COMMS_FIELD_MEMBERS_ACCESS macro
        ///     related to @b comms::field::Bitfield class from COMMS library
        ///     for details.
        COMMS_FIELD_MEMBERS_ACCESS(svid, flags, ageC, prc, prrc);
    };

    /// @brief Definition of the list of repeated blocks (@ref block).
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
        iTOW,
        age,
        baseId,
        baseHealth,
        numCh,
        status,
        reserved1,
        data<TOpt>
    >;
};

/// @brief Definition of NAV-DGPS message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref NavDgpsFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
/// @tparam TDataOpt Extra option(s) for @b data field
template <typename TMsgBase = Message, typename TDataOpt = comms::option::EmptyOption>
class NavDgps : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_DGPS>,
        comms::option::FieldsImpl<NavDgpsFields::All<TDataOpt> >,
        comms::option::MsgType<NavDgps<TMsgBase, TDataOpt> >,
        comms::option::HasDoRefresh
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_DGPS>,
        comms::option::FieldsImpl<NavDgpsFields::All<TDataOpt> >,
        comms::option::MsgType<NavDgps<TMsgBase, TDataOpt> >,
        comms::option::HasDoRefresh
    > Base;
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b iTOW for @ref NavDgpsFields::iTOW field
    ///     @li @b age for @ref NavDgpsFields::age field
    ///     @li @b baseId for @ref NavDgpsFields::baseId field
    ///     @li @b baseHealth for @ref NavDgpsFields::baseHealth field
    ///     @li @b numCh for @ref NavDgpsFields::numCh field
    ///     @li @b status for @ref NavDgpsFields::status field
    ///     @li @b reserved1 for @ref NavDgpsFields::reserved1 field
    ///     @li @b data for @ref NavDgpsFields::data field
    COMMS_MSG_FIELDS_ACCESS(
        iTOW,
        age,
        baseId,
        baseHealth,
        numCh,
        status,
        reserved1,
        data
    );

    /// @brief Default constructor
    NavDgps() = default;

    /// @brief Copy constructor
    NavDgps(const NavDgps&) = default;

    /// @brief Move constructor
    NavDgps(NavDgps&& other) = default;

    /// @brief Destructor
    ~NavDgps() = default;

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





