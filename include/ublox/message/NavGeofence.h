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
/// @brief Contains definition of NAV-GEOFENCE message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/nav.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the NAV-GEOFENCE message fields.
/// @see NavGeofence
struct NavGeofenceFields
{
    /// @brief Definition of "iTOW" field.
    using iTOW = field::nav::iTOW;

    /// @brief Definition of "globalFlags" field.
    using version =
        field::common::U1T<
            comms::option::ValidNumValueRange<0, 0>
        >;

    /// @brief Value enumeration for @ref status field.
    enum class Status : std::uint8_t
    {
        NotAvailable, ///< Geofencing not available or not reliable
        Active, ///< Geofencing active
        NumOfValues /// number of available values
    };

    /// @brief Definition of "status" field.
    using status =
        field::common::EnumT<
            Status,
            comms::option::ValidNumValueRange<0, (int)Status::NumOfValues - 1>
        >;

    /// @brief Definition of "numFences" field.
    using numFences = field::common::U1;


    /// @brief Value enumeration for @ref combState and @ref state fields.
    enum class State : std::uint8_t
    {
        Unknown, ///< Outside
        Inside, ///< Inside
        Outside, ///< Outside
        NumOfValues /// number of available values
    };

    /// @brief Definition of "combState" field.
    using combState =
        field::common::EnumT<
            State,
            comms::option::ValidNumValueRange<0, (int)State::NumOfValues - 1>
        >;

    /// @brief Definition of "state" field.
    using state = combState;

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res1;

    /// @brief Definition of a block field repeated multiple times in @ref
    ///     data list.
    struct block : public
        field::common::BundleT<
            std::tuple<
                state,
                reserved1
            >
        >
    {
        /// @brief Allow access to internal fields.
        /// @details See definition of @b COMMS_FIELD_MEMBERS_ACCESS macro
        ///     related to @b comms::field::Bundle class from COMMS library
        ///     for details.
        COMMS_FIELD_MEMBERS_ACCESS(state, reserved1);
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
        iTOW,
        version,
        status,
        numFences,
        combState,
        data<TOpt>
    >;
};

/// @brief Definition of NAV-GEOFENCE message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref NavGeofenceFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
/// @tparam TDataOpt Extra option(s) for @b data field
template <typename TMsgBase = Message, typename TDataOpt = comms::option::EmptyOption>
class NavGeofence : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_GEOFENCE>,
        comms::option::FieldsImpl<NavGeofenceFields::All<TDataOpt> >,
        comms::option::MsgType<NavGeofence<TMsgBase, TDataOpt> >,
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
    ///     @li @b iTOW for @ref NavGeofenceFields::iTOW field
    ///     @li @b version for @ref NavGeofenceFields::version field
    ///     @li @b status for @ref NavGeofenceFields::status field
    ///     @li @b numFences for @ref NavGeofenceFields::numFences field
    ///     @li @b combState for @ref NavGeofenceFields::combState field
    ///     @li @b data for @ref NavGeofenceFields::data field
    COMMS_MSG_FIELDS_ACCESS(iTOW, version, status, numFences, combState, data);

    /// @brief Default constructor
    NavGeofence() = default;

    /// @brief Copy constructor
    NavGeofence(const NavGeofence&) = default;

    /// @brief Move constructor
    NavGeofence(NavGeofence&& other) = default;

    /// @brief Destructor
    ~NavGeofence() = default;

    /// @brief Copy assignment
    NavGeofence& operator=(const NavGeofence&) = default;

    /// @brief Move assignment
    NavGeofence& operator=(NavGeofence&&) = default;

    /// @brief Provides custom read functionality.
    /// @details The number of blocks in @b data (@ref NavGeofenceFields::data)
    ///     list is determined by the value of @b numFences (@ref NavGeofenceFields::numFences)
    ///     field.
    template <typename TIter>
    comms::ErrorStatus doRead(TIter& iter, std::size_t len)
    {
        using Base = typename std::decay<decltype(comms::toMessageBase(*this))>::type;
        auto es = Base::template readFieldsUntil<FieldIdx_data>(iter, len);
        if (es != comms::ErrorStatus::Success) {
            return es;
        }

        field_data().forceReadElemCount(field_numFences().value());
        return Base::template readFieldsFrom<FieldIdx_data>(iter, len);
    }

    /// @brief Provides custom refresh functionality
    /// @details The value of @b numFences (@ref NavGeofenceFields::numFences) field is
    ///     determined by number of blocks stored in @b data (@ref NavGeofenceFields::data)
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





