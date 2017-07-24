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
/// @brief Contains definition of NAV-TIMELS message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/nav.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the NAV-TIMELS message fields.
/// @see NavTimels
struct NavTimelsFields
{
    /// @brief Definition of "iTOW" field.
    using iTOW = field::nav::iTOW;

    /// @brief Definition of "version" field.
    using version =
        field::common::U1T<
            comms::option::ValidNumValueRange<0, 0>
        >;

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res3;


    /// @brief Value enumeration for @ref srcOfCurrLs field
    enum class SrcOfCurrLs : std::uint8_t
    {
        Default, ///< Default (hardcoded in the firmware, can be outdated)
        DiffDerived, ///< Derived from time difference between GPS and GLONASS time.
        Gps, ///< GPS
        Sbas, ///< SBAS
        BeiDou, ///< BeiDou
        Galileo, ///< Galileo
        AidedData, ///< Aided data
        Configured, ///< Configured
        Unknown = 0xff ///< Unknown
    };

    /// @brief Custom validation class for @ref srcOfCurrLs field
    struct SrcOfCurrLsValidator
    {
        template <typename TField>
        bool operator()(const TField& field) const
        {
            auto val = field.value();
            return
                (val <= SrcOfCurrLs::Configured) ||
                (val == SrcOfCurrLs::Unknown);
        }
    };

    /// @brief Definition of "srcOfCurrLs" field.
    using srcOfCurrLs =
        field::common::EnumT<
            SrcOfCurrLs,
            comms::option::ContentsValidator<SrcOfCurrLsValidator>
        >;

    /// @brief Definition of "currLs" field.
    using currLs = field::common::I1T<comms::option::UnitsSeconds>;

    /// @brief Value enumeration for @ref srcOfLsChange field
    enum class SrcOfLsChange : std::uint8_t
    {
        NoSource, ///< No source
        Gps, ///< GPS
        Sbas, ///< SBAS
        BeiDou, ///< BeiDou
        Galileo, ///< Galileo
        Glonass, ///< GLONASS
        NumOfValues ///< number of available values
    };

    /// @brief Definition of "srcOfLsChange" field.
    using srcOfLsChange =
        field::common::EnumT<
            SrcOfLsChange,
            comms::option::ValidNumValueRange<0, (int)SrcOfLsChange::NumOfValues - 1>
        >;

    /// @brief Definition of "lsChange" field.
    using lsChange = field::common::I1T<comms::option::UnitsSeconds>;

    /// @brief Definition of "timeToLsEvent" field.
    using timeToLsEvent = field::common::I4T<comms::option::UnitsSeconds>;

    /// @brief Definition of "dateOfLsGpsWn" field.
    using dateOfLsGpsWn = field::common::U2;

    /// @brief Definition of "dateOfLsGpsDn" field.
    using dateOfLsGpsDn = field::common::U2;

    /// @brief Definition of "reserved2" field.
    using reserved2 = field::common::res3;

    /// @brief Definition of "valid" field.
    struct validBits : public
        field::common::X1T<
            comms::option::BitmaskReservedBits<0xfc, 0>
        >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS_SEQ macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS_SEQ(validCurrLs, validTimeToLsEvent);
    };

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        iTOW,
        version,
        reserved1,
        srcOfCurrLs,
        currLs,
        srcOfLsChange,
        lsChange,
        timeToLsEvent,
        dateOfLsGpsWn,
        dateOfLsGpsDn,
        reserved2,
        validBits
    >;
};

/// @brief Definition of NAV-TIMELS message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref NavTimelsFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class NavTimels : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_TIMELS>,
        comms::option::FieldsImpl<NavTimelsFields::All>,
        comms::option::MsgType<NavTimels<TMsgBase> >
    >
{
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b iTOW for @ref NavTimelsFields::iTOW field
    ///     @li @b version for @ref NavTimelsFields::version field
    ///     @li @b reserved1 for @ref NavTimelsFields::reserved1 field
    ///     @li @b srcOfCurrLs for @ref NavTimelsFields::srcOfCurrLs field
    ///     @li @b lsChange for @ref NavTimelsFields::lsChange field
    ///     @li @b timeToLsEvent for @ref NavTimelsFields::timeToLsEvent field
    ///     @li @b dateOfLsGpsWn for @ref NavTimelsFields::dateOfLsGpsWn field
    ///     @li @b dateOfLsGpsDn for @ref NavTimelsFields::dateOfLsGpsDn field
    ///     @li @b reserved2 for @ref NavTimelsFields::reserved2 field
    ///     @li @b valid for @ref NavTimelsFields::validBits field
    COMMS_MSG_FIELDS_ACCESS(
        iTOW,
        version,
        reserved1,
        srcOfCurrLs,
        currLs,
        srcOfLsChange,
        lsChange,
        timeToLsEvent,
        dateOfLsGpsWn,
        dateOfLsGpsDn,
        reserved2,
        valid
    );

    /// @brief Default constructor
    NavTimels() = default;

    /// @brief Copy constructor
    NavTimels(const NavTimels&) = default;

    /// @brief Move constructor
    NavTimels(NavTimels&& other) = default;

    /// @brief Destructor
    ~NavTimels() = default;

    /// @brief Copy assignment
    NavTimels& operator=(const NavTimels&) = default;

    /// @brief Move assignment
    NavTimels& operator=(NavTimels&&) = default;
};


}  // namespace message

}  // namespace ublox





