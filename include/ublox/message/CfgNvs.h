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
/// @brief Contains definition of CFG-NVS message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the CFG-NVS message fields.
/// @see CfgNvs
struct CfgNvsFields
{
    /// @brief Bits access enumeration for @ref clearMask, @ref saveMask,
    ///     and @ref loadMask fields
    enum
    {
        mask_alm = 17, ///< @b alm bit index
        mask_aop = 29, ///< @b aop bit index
        mask_numOfValues ///< upper limit for available bits
    };

    /// @brief Bits access enumeration for @ref deviceMask bitmask field
    enum
    {
        deviceMask_devBBR, ///< b devBBR bit index
        deviceMask_devFlash, ///< b devFlash bit index
        deviceMask_devEEPROM, ///< b devEEPROM bit index
        deviceMask_devSpiFlash = 4,  ///< b devSpiFlash bit index
        deviceMask_numOfValues ///< upper limit for available bits
    };

    /// @brief Common mask field definition for @ref clearMask, @ref saveMask,
    ///     and @ref loadMask
    using mask =
        field::common::X4T<
            comms::option::BitmaskReservedBits<0xdffdffff, 0>
        >;

    /// @brief Definition of "clearMask" field.
    using clearMask = mask;

    /// @brief Definition of "saveMask" field.
    using saveMask = mask;

    /// @brief Definition of "loadMask" field.
    using loadMask = mask;

    /// @brief Definition of "deviceMask" field.
    using deviceMask =
        field::common::X1T<
            comms::option::BitmaskReservedBits<0xe8, 0>
        >;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        clearMask,
        saveMask,
        loadMask,
        deviceMask
    >;
};

/// @brief Definition of CFG-NVS message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref CfgNvsFields and for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class CfgNvs : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_NVS>,
        comms::option::FieldsImpl<CfgNvsFields::All>,
        comms::option::MsgType<CfgNvs<TMsgBase> >,
        comms::option::DispatchImpl
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_NVS>,
        comms::option::FieldsImpl<CfgNvsFields::All>,
        comms::option::MsgType<CfgNvs<TMsgBase> >,
        comms::option::DispatchImpl
    > Base;
public:

#ifdef FOR_DOXYGEN_DOC_ONLY
    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_clearMask, ///< @b clearMask field, see @ref CfgNvsFields::clearMask
        FieldIdx_saveMask, ///< @b saveMask field, see @ref CfgNvsFields::saveMask
        FieldIdx_loadMask, ///< @b loadMask field, see @ref CfgNvsFields::loadMask
        FieldIdx_deviceMask, ///< @b deviceMask field, see @ref CfgNvsFields::deviceMask
        FieldIdx_numOfValues ///< number of available fields
    };

    /// @brief Access to fields bundled as a struct
    struct FieldsAsStruct
    {
        CfgNvsFields::clearMask& clearMask; ///< @b clearMask field, see @ref CfgNvsFields::clearMask
        CfgNvsFields::saveMask& saveMask; ///< @b saveMask field, see @ref CfgNvsFields::saveMask
        CfgNvsFields::loadMask& loadMask; ///< @b loadMask field, see @ref CfgNvsFields::loadMask
        CfgNvsFields::deviceMask& deviceMask; ///< @b deviceMask field, see @ref CfgNvsFields::deviceMask
    };

    /// @brief Access to @b const fields bundled as a struct
    struct ConstFieldsAsStruct
    {
        const CfgNvsFields::clearMask& clearMask; ///< @b clearMask field, see @ref CfgNvsFields::clearMask
        const CfgNvsFields::saveMask& saveMask; ///< @b saveMask field, see @ref CfgNvsFields::saveMask
        const CfgNvsFields::loadMask& loadMask; ///< @b loadMask field, see @ref CfgNvsFields::loadMask
        const CfgNvsFields::deviceMask& deviceMask; ///< @b deviceMask field, see @ref CfgNvsFields::deviceMask
    };

    /// @brief Get access to fields bundled into a struct
    FieldsAsStruct fieldsAsStruct();

    /// @brief Get access to @b const fields bundled into a struct
    ConstFieldsAsStruct fieldsAsStruct() const;

#else
    COMMS_MSG_FIELDS_ACCESS(Base, clearMask, saveMask, loadMask, deviceMask);
#endif // #ifdef FOR_DOXYGEN_DOC_ONLY

    /// @brief Default constructor
    CfgNvs() = default;

    /// @brief Copy constructor
    CfgNvs(const CfgNvs&) = default;

    /// @brief Move constructor
    CfgNvs(CfgNvs&& other) = default;

    /// @brief Destructor
    virtual ~CfgNvs() = default;

    /// @brief Copy assignment
    CfgNvs& operator=(const CfgNvs&) = default;

    /// @brief Move assignment
    CfgNvs& operator=(CfgNvs&&) = default;
};


}  // namespace message

}  // namespace ublox

