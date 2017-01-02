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
    /// @brief Bits access enumeration for @ref navBbrMask bitmask field.
    enum
    {
        navBbrMask_eph, ///< @b eph bit index
        navBbrMask_alm, ///< @b alm bit index
        navBbrMask_health, ///< @b health bit index
        navBbrMask_klob, ///< @b klob bit index
        navBbrMask_pos, ///< @b pos bit index
        navBbrMask_clkd, ///< @b clkd bit index
        navBbrMask_osc, ///< @b osc bit index
        navBbrMask_utc, ///< @b utc bit index
        navBbrMask_rtc, ///< @b rtc bit index
        navBbrMask_sfdr = 11, ///< @b sfdr bit index
        navBbrMask_vmon, ///< @b vmon bit index
        navBbrMask_tct, ///< @b tct bit index
        navBbrMask_aop = 15, ///< @b aop bit index
        navBbrMask_numOfValues ///< upper limit for available bits
    };

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
    using navBbrMask = field::common::X2;

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
///     See @ref CfgRstFields and for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class CfgRst : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_RST>,
        comms::option::FieldsImpl<CfgRstFields::All>,
        comms::option::MsgType<CfgRst<TMsgBase> >,
        comms::option::DispatchImpl
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_RST>,
        comms::option::FieldsImpl<CfgRstFields::All>,
        comms::option::MsgType<CfgRst<TMsgBase> >,
        comms::option::DispatchImpl
    > Base;
public:

#ifdef FOR_DOXYGEN_DOC_ONLY
    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_navBbrMask, ///< @b navBbrMask field, see @ref CfgRstFields::navBbrMask
        FieldIdx_resetMode, ///< @b resetMode field, see @ref CfgRstFields::resetMode
        FieldIdx_reserved1, ///< @b reserved1 field, see @ref CfgRstFields::reserved1
        FieldIdx_numOfValues ///< number of available fields
    };

    /// @brief Access to fields bundled as a struct
    struct FieldsAsStruct
    {
        CfgRstFields::navBbrMask& navBbrMask; ///< @b navBbrMask field, see @ref CfgRstFields::navBbrMask
        CfgRstFields::resetMode& resetMode; ///< @b resetMode field, see @ref CfgRstFields::resetMode
        CfgRstFields::reserved1& reserved1; ///< @b reserved1 field, see @ref CfgRstFields::reserved1
    };

    /// @brief Access to @b const fields bundled as a struct
    struct ConstFieldsAsStruct
    {
        const CfgRstFields::navBbrMask& navBbrMask; ///< @b navBbrMask field, see @ref CfgRstFields::navBbrMask
        const CfgRstFields::resetMode& resetMode; ///< @b resetMode field, see @ref CfgRstFields::resetMode
        const CfgRstFields::reserved1& reserved1; ///< @b reserved1 field, see @ref CfgRstFields::reserved1
    };

    /// @brief Get access to fields bundled into a struct
    FieldsAsStruct fieldsAsStruct();

    /// @brief Get access to @b const fields bundled into a struct
    ConstFieldsAsStruct fieldsAsStruct() const;

#else
    COMMS_MSG_FIELDS_ACCESS(Base, navBbrMask, resetMode, reserved1);
#endif // #ifdef FOR_DOXYGEN_DOC_ONLY

    /// @brief Default constructor
    CfgRst() = default;

    /// @brief Copy constructor
    CfgRst(const CfgRst&) = default;

    /// @brief Move constructor
    CfgRst(CfgRst&& other) = default;

    /// @brief Destructor
    virtual ~CfgRst() = default;

    /// @brief Copy assignment
    CfgRst& operator=(const CfgRst&) = default;

    /// @brief Move assignment
    CfgRst& operator=(CfgRst&&) = default;
};


}  // namespace message

}  // namespace ublox

