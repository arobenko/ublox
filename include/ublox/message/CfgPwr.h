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
/// @brief Contains definition of CFG-PWR message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the CFG-PWR message fields.
/// @see CfgPwr
struct CfgPwrFields
{
    /// @brief Definition of "version" field.
    using version =
        field::common::U1T<
            comms::option::ValidNumValueRange<1, 1>,
            comms::option::DefaultNumValue<1>
        >;

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res3;

    /// @brief Value enumeration for @ref state field
    enum class State : std::uint32_t
    {
        SoftwareBackup = 0x42434B50, ///< Software backup
        GnssRunning = 0x52554E20, ///< GNSS running
        GnssStopped = 0x53544F50 ///< GNSS stopped
    };

    struct StateValidator
    {
        template <typename TField>
        bool operator()(const TField& field) const
        {
            auto val = field.value();
            return
                (val == State::SoftwareBackup) ||
                (val == State::GnssRunning) ||
                (val == State::GnssStopped);
        }
    };

    /// @brief Definition of "state" field.
    using state =
        field::common::EnumT<
            State,
            comms::option::ContentsValidator<StateValidator>,
            comms::option::DefaultNumValue<(std::intmax_t)State::GnssRunning>
        >;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        version,
        reserved1,
        state
    >;
};

/// @brief Definition of CFG-PWR message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref CfgPwrFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class CfgPwr : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_PWR>,
        comms::option::FieldsImpl<CfgPwrFields::All>,
        comms::option::MsgType<CfgPwr<TMsgBase> >
    >
{
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b version for @ref CfgPwrFields::version field
    ///     @li @b reserved1 for @ref CfgPwrFields::reserved1 field
    ///     @li @b state for @ref CfgPwrFields::state field
    COMMS_MSG_FIELDS_ACCESS(version, reserved1, state);

    /// @brief Default constructor
    CfgPwr() = default;

    /// @brief Copy constructor
    CfgPwr(const CfgPwr&) = default;

    /// @brief Move constructor
    CfgPwr(CfgPwr&& other) = default;

    /// @brief Destructor
    ~CfgPwr() = default;

    /// @brief Copy assignment
    CfgPwr& operator=(const CfgPwr&) = default;

    /// @brief Move assignment
    CfgPwr& operator=(CfgPwr&&) = default;
};


}  // namespace message

}  // namespace ublox

