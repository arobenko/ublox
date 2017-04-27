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
/// @brief Contains definition of CFG-PMS message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the CFG-PMS message fields.
/// @see CfgPms
struct CfgPmsFields
{
    /// @brief Definition of "version" field.
    using version =
        field::common::U1T<
            comms::option::ValidNumValueRange<0, 0>
        >;

    /// @brief Value enumeration for @ref powerSetupValue field.
    enum class PowerSetupValue : std::uint8_t
    {
        FullPower, ///< Full power
        Balanced, ///< Default Mode
        Interval, ///< Intervale
        Aggressive_1Hz, ///< Aggressive with 1Hz
        Aggressive_2Hz, ///< Aggressive with 2Hz
        Invalid = 0xff /// Invalid
    };

    struct PowerSetupValueValidator
    {
        template <typename TField>
        bool operator()(const TField& field) const
        {
            auto val = field.value();
            if (val == PowerSetupValue::Invalid) {
                return true;
            }
            return (PowerSetupValue::FullPower <= val) && (val <= PowerSetupValue::Aggressive_2Hz);
        }
    };

    /// @brief Definition of "powerSetupValue" field.
    using powerSetupValue =
        field::common::EnumT<
            PowerSetupValue,
            comms::option::ContentsValidator<PowerSetupValueValidator>
        >;

    /// @brief Definition of "period" field.
    using period = field::common::U2T<comms::option::UnitsSeconds>;

    /// @brief Definition of "onTime" field.
    using onTime = field::common::U2T<comms::option::UnitsSeconds>;

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res2;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        version,
        powerSetupValue,
        period,
        onTime,
        reserved1
    >;
};

/// @brief Definition of CFG-PMS message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref CfgPmsFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class CfgPms : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_PMS>,
        comms::option::FieldsImpl<CfgPmsFields::All>,
        comms::option::MsgType<CfgPms<TMsgBase> >
    >
{
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b version for @ref CfgPmsFields::version field
    ///     @li @b powerSetupValue for @ref CfgPmsFields::powerSetupValue field
    ///     @li @b period for @ref CfgPmsFields::period field
    ///     @li @b onTime for @ref CfgPmsFields::onTime field
    ///     @li @b reserved1 for @ref CfgPmsFields::reserved1 field
    COMMS_MSG_FIELDS_ACCESS(
            version,
            powerSetupValue,
            period,
            onTime,
            reserved1);

    /// @brief Default constructor
    CfgPms() = default;

    /// @brief Copy constructor
    CfgPms(const CfgPms&) = default;

    /// @brief Move constructor
    CfgPms(CfgPms&& other) = default;

    /// @brief Destructor
    ~CfgPms() = default;

    /// @brief Copy assignment
    CfgPms& operator=(const CfgPms&) = default;

    /// @brief Move assignment
    CfgPms& operator=(CfgPms&&) = default;
};


}  // namespace message

}  // namespace ublox

