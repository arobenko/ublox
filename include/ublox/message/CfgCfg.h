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
/// @brief Contains definition of CFG-CFG message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the CFG-CFG message fields.
/// @see CfgCfg
struct CfgCfgFields
{
    /// @brief common definition for @ref clearMask, @ref saveMask, and @ref loadMask fields
    struct mask : public
        field::common::X4T<
            comms::option::BitmaskReservedBits<0xffffe1e0, 0>
        >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS(ioPort, msgConf, infMsg, navConf, rxmConf, rinvConf=9, antConf, logConf, ftsConf);
    };

    /// @brief Definition of "clearMask" field.
    using clearMask = mask;

    /// @brief Definition of "saveMask" field.
    using saveMask = mask;

    /// @brief Definition of "loadMask" field.
    using loadMask = mask;

    /// @brief Definition of "deviceMask" bitmask field.
    struct deviceMaskBitmask : public
            field::common::X1T<comms::option::BitmaskReservedBits<0xe8, 0> >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS(devBBR, devFlash, devEEPROM, devSpiFlash=4);
    };

    /// @brief Definition of optional "deviceMask" field.
    using deviceMask = field::common::OptionalT<deviceMaskBitmask>;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        clearMask,
        saveMask,
        loadMask,
        deviceMask
    >;
};

/// @brief Definition of CFG-CFG message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref CfgCfgFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class CfgCfg : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_CFG>,
        comms::option::FieldsImpl<CfgCfgFields::All>,
        comms::option::MsgType<CfgCfg<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_CFG>,
        comms::option::FieldsImpl<CfgCfgFields::All>,
        comms::option::MsgType<CfgCfg<TMsgBase> >
    > Base;
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b clearMask for @ref CfgCfgFields::clearMask field
    ///     @li @b saveMask for @ref CfgCfgFields::saveMask field
    ///     @li @b loadMask for @ref CfgCfgFields::loadMask field
    ///     @li @b deviceMask for @ref CfgCfgFields::deviceMask field
    COMMS_MSG_FIELDS_ACCESS(clearMask, saveMask, loadMask, deviceMask);

    /// @brief Default constructor
    CfgCfg()
    {
        field_deviceMask().setMissing();
    }

    /// @brief Copy constructor
    CfgCfg(const CfgCfg&) = default;

    /// @brief Move constructor
    CfgCfg(CfgCfg&& other) = default;

    /// @brief Destructor
    virtual ~CfgCfg() = default;

    /// @brief Copy assignment
    CfgCfg& operator=(const CfgCfg&) = default;

    /// @brief Move assignment
    CfgCfg& operator=(CfgCfg&&) = default;
};


}  // namespace message

}  // namespace ublox

