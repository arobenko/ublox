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
/// @brief Contains definition of CFG-RST message and its fields.

#pragma once

#include <algorithm>

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the CFG-RST message fields.
/// @see CfgRst
struct CfgRstFields
{
    /// @brief Value enumeration for @ref resetMode field
    enum class ResetMode : std::uint8_t
    {
        Hardware, ///< Hardware reset
        Software, ///< Software reset
        GnssOnly, ///< Software reset (GNSS only)
        HardwareAfterShutdown = 4, ///< Hardware reset after shutdown
        GnssStop = 8, ///< Controlled GNSS stop
        GnssStart ///< Controlled GNSS start
    };

    /// @brief Custom value validator for @ref resetMode field
    struct ResetModeValidator
    {
        template <typename TField>
        bool operator()(const TField& field) const
        {
            static const ResetMode Values[] =
            {
                ResetMode::Hardware,
                ResetMode::Software,
                ResetMode::GnssOnly,
                ResetMode::HardwareAfterShutdown,
                ResetMode::GnssStop,
                ResetMode::GnssStart
            };
            auto value = field.value();
            auto iter = std::lower_bound(std::begin(Values), std::end(Values), value);
            return (iter != std::end(Values)) && (*iter == value);
        }
    };

    /// @brief Definition of "navBbrMask" field.
    struct navBbrMask : public field::common::X2
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS(eph, alm, health, klob, pos, clkd, osc, utc, rtc, sfdr=11, vmon, tct, aop=15);
    };

    /// @brief Definition of "resetMode" field.
    using resetMode =
        field::common::EnumT<
            ResetMode,
            comms::option::ContentsValidator<ResetModeValidator>
        >;

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res1;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        navBbrMask,
        resetMode,
        reserved1
    >;

};

/// @brief Definition of CFG-RST message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref CfgRstFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class CfgRst : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_RST>,
        comms::option::FieldsImpl<CfgRstFields::All>,
        comms::option::MsgType<CfgRst<TMsgBase> >
    >
{
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b navBbrMask for @ref CfgRstFields::navBbrMask field
    ///     @li @b resetMode for @ref CfgRstFields::resetMode field
    ///     @li @b reserved1 for @ref CfgRstFields::reserved1 field
    COMMS_MSG_FIELDS_ACCESS(navBbrMask, resetMode, reserved1);

    /// @brief Default constructor
    CfgRst() = default;

    /// @brief Copy constructor
    CfgRst(const CfgRst&) = default;

    /// @brief Move constructor
    CfgRst(CfgRst&& other) = default;

    /// @brief Destructor
    ~CfgRst() = default;

    /// @brief Copy assignment
    CfgRst& operator=(const CfgRst&) = default;

    /// @brief Move assignment
    CfgRst& operator=(CfgRst&&) = default;
};


}  // namespace message

}  // namespace ublox

