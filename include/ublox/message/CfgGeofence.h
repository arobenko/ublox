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
/// @brief Contains definition of CFG-GEOFENCE message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the CFG-GEOFENCE message fields.
/// @see CfgGeofence
struct CfgGeofenceFields
{
    /// @brief Definition of "version" field.
    using version =
        field::common::U1T<
            comms::option::ValidNumValueRange<0, 0>
        >;

    /// @brief Definition of "numFences" field.
    using numFences = field::common::U1;

    /// @brief Definition of "confLvl" field.
    using confLvl = field::common::U1;

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res1;

    /// @brief Value enumeration for @ref pioEnabled field.
    enum class PioEnabled : std::uint8_t
    {
        Disable, ///< disable
        Enable, ///< enable
        NumOfValues /// number of available values
    };

    /// @brief Definition of "pioEnabled" field.
    using pioEnabled =
        field::common::EnumT<
            PioEnabled,
            comms::option::ValidNumValueRange<0, (int)PioEnabled::NumOfValues - 1>
        >;

    /// @brief Value enumeration for @ref pioPolarity field.
    enum class PioPolarity : std::uint8_t
    {
        LowInside, ///< low inside
        LowOutside, ///< low outside
        NumOfValues /// number of available values
    };

    /// @brief Definition of "pioPolarity" field.
    using pioPolarity =
        field::common::EnumT<
            PioPolarity,
            comms::option::ValidNumValueRange<0, (int)PioPolarity::NumOfValues - 1>
        >;

    /// @brief Definition of "pin" field.
    using pin = field::common::U1;


    /// @brief Definition of "reserved2" field.
    using reserved2 = field::common::res1;

    /// @brief Definition of "lat" field.
    using lat = field::common::I4T<
        comms::option::ScalingRatio<1, 10000000L>,
        comms::option::UnitsDegrees
    >;

    /// @brief Definition of "lon" field.
    using lon = field::common::I4T<
        comms::option::ScalingRatio<1, 10000000L>,
        comms::option::UnitsDegrees
    >;

    /// @brief Definition of "radius" field.
    using radius = field::common::U4T<
        comms::option::ScalingRatio<1, 100L>,
        comms::option::UnitsMeters
    >;


    /// @brief Definition of a block field repeated multiple times in @ref
    ///     data list.
    struct block : public
        field::common::BundleT<
            std::tuple<
                lat,
                lon,
                radius
            >
        >
    {
        /// @brief Allow access to internal fields.
        /// @details See definition of @b COMMS_FIELD_MEMBERS_ACCESS macro
        ///     related to @b comms::field::Bundle class from COMMS library
        ///     for details.
        COMMS_FIELD_MEMBERS_ACCESS(lat, lon, radius);
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
        numFences,
        confLvl,
        reserved1,
        pioEnabled,
        pioPolarity,
        pin,
        reserved2,
        data<TOpt>
    >;
};

/// @brief Definition of CFG-GEOFENCE message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref CfgGeofenceFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
/// @tparam TDataOpt Extra option(s) for @b data field
template <typename TMsgBase = Message, typename TDataOpt = comms::option::EmptyOption>
class CfgGeofence : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_GEOFENCE>,
        comms::option::FieldsImpl<CfgGeofenceFields::All<TDataOpt> >,
        comms::option::MsgType<CfgGeofence<TMsgBase, TDataOpt> >,
        comms::option::HasDoRefresh
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_GEOFENCE>,
        comms::option::FieldsImpl<CfgGeofenceFields::All<TDataOpt> >,
        comms::option::MsgType<CfgGeofence<TMsgBase, TDataOpt> >,
        comms::option::HasDoRefresh
    > Base;
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b version for @ref CfgGeofenceFields::version field
    ///     @li @b numFences for @ref CfgGeofenceFields::numFences field
    ///     @li @b confLvl for @ref CfgGeofenceFields::confLvl field
    ///     @li @b reserved1 for @ref CfgGeofenceFields::reserved1 field
    ///     @li @b pioEnabled for @ref CfgGeofenceFields::pioEnabled field
    ///     @li @b pioPolarity for @ref CfgGeofenceFields::pioPolarity field
    ///     @li @b reserved2 for @ref CfgGeofenceFields::reserved2 field
    ///     @li @b data for @ref CfgGeofenceFields::data field
    COMMS_MSG_FIELDS_ACCESS(
            version,
            numFences,
            confLvl,
            reserved1,
            pioEnabled,
            pioPolarity,
            pin,
            reserved2,
            data);

    /// @brief Default constructor
    CfgGeofence() = default;

    /// @brief Copy constructor
    CfgGeofence(const CfgGeofence&) = default;

    /// @brief Move constructor
    CfgGeofence(CfgGeofence&& other) = default;

    /// @brief Destructor
    ~CfgGeofence() = default;

    /// @brief Copy assignment
    CfgGeofence& operator=(const CfgGeofence&) = default;

    /// @brief Move assignment
    CfgGeofence& operator=(CfgGeofence&&) = default;

    /// @brief Provides custom read functionality.
    /// @details The number of blocks in @b data (@ref CfgGeofenceFields::data)
    ///     list is determined by the value of @b numFences (@ref CfgGeofenceFields::numFences)
    ///     field.
    template <typename TIter>
    comms::ErrorStatus doRead(TIter& iter, std::size_t len)
    {
        auto es = Base::template readFieldsUntil<FieldIdx_data>(iter, len);
        if (es != comms::ErrorStatus::Success) {
            return es;
        }

        field_data().forceReadElemCount(field_numFences().value());
        return Base::template readFieldsFrom<FieldIdx_data>(iter, len);
    }

    /// @brief Provides custom refresh functionality
    /// @details The value of @b numFences (@ref CfgGeofenceFields::numFences) field is
    ///     determined by number of blocks stored in @b data (@ref CfgGeofenceFields::data)
    ///     list.
    /// @return @b true in case the value of "numFences" field was modified, @b false otherwise
    bool doRefresh()
    {
        if (field_numFences().value() == field_data().value().size()) {
            return false;
        }

        field_numFences().value() = field_data().value().size();
        return true;
    }

};


}  // namespace message

}  // namespace ublox





