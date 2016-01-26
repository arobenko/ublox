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

    /// @brief Bits access enumerator for @ref clearMask, @ref saveMask, and
    ///     @ref loadMask bitmask fields.
    enum
    {
        mask_ioPort,  ///< @b ioPort bit index
        mask_msgConf, ///< @b msgConf bit index
        mask_infMsg, ///< @b infMsg bit index
        mask_navConf, ///< @b navConf bit index
        mask_rxmConf, ///< @b rxmConf bit index
        mask_rinvConf = 9,  ///< @b rinvConf bit index
        mask_antConf, ///< @b antConf bit index
        mask_numOfValues ///< @b upper limit for available bits
    };

    /// @brief Bits access enumerator for @ref deviceMask bitmask field.
    enum
    {
        deviceMask_devBBR,  ///< @b devBBR bit index
        deviceMask_devFlash,  ///< @b devFlash bit index
        deviceMask_devEEPROM,  ///< @b devEEPROM bit index
        deviceMask_devSpiFlash = 4,  ///< @b devSpiFlash bit index
        deviceMask_numOfValues ///< @b upper limit for available bits
    };

    /// @brief common definition for @ref clearMask, @ref saveMask, and @ref loadMask fields
    using mask =
        field::common::X4T<
            comms::option::BitmaskReservedBits<0xfffff9e0, 0>
        >;

    /// @brief Definition of "clearMask" field.
    using clearMask = mask;

    /// @brief Definition of "saveMask" field.
    using saveMask = mask;

    /// @brief Definition of "loadMask" field.
    using loadMask = mask;

    /// @brief Definition of "deviceMask" field.
    using deviceMask =
        field::common::OptionalT<
            field::common::X1T<
                comms::option::BitmaskReservedBits<0xe8, 0>
            >
        >;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        clearMask,
        saveMask,
        loadMask,
        deviceMask
    >;
};

/// @brief Definition of CFG-CFG message
/// @details Inherits from
///     <a href="https://dl.dropboxusercontent.com/u/46999418/comms_champion/comms/html/classcomms_1_1MessageBase.html">comms::MessageBase</a>
///     while providing @b TMsgBase as common interface class as well as
///     @b comms::option::StaticNumIdImpl, @b comms::option::FieldsImpl, and
///     @b comms::option::DispatchImpl as options. @n
///     See @ref CfgCfgFields and for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class CfgCfg : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_CFG>,
        comms::option::FieldsImpl<CfgCfgFields::All>,
        comms::option::DispatchImpl<CfgCfg<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_CFG>,
        comms::option::FieldsImpl<CfgCfgFields::All>,
        comms::option::DispatchImpl<CfgCfg<TMsgBase> >
    > Base;
public:

    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_clearMask, ///< @b clearMask field, see @ref CfgCfgFields::clearMask
        FieldIdx_saveMask, ///< @b saveMask field, see @ref CfgCfgFields::saveMask
        FieldIdx_loadMask, ///< @b loadMask field, see @ref CfgCfgFields::loadMask
        FieldIdx_deviceMask, ///< @b deviceMask field, see @ref CfgCfgFields::deviceMask
        FieldIdx_numOfValues ///< number of available fields
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    /// @brief Default constructor
    CfgCfg() = default;

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

