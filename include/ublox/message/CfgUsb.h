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
/// @brief Contains definition of CFG-USB message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the CFG-USB message fields.
/// @see CfgUsb
struct CfgUsbFields
{
    /// @brief Definition of "vendorID" field.
    using vendorID = field::common::U2;

    /// @brief Definition of "productID" field.
    using productID = field::common::U2;

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res2;

    /// @brief Definition of "reserved2" field.
    using reserved2 =
        field::common::U2T<
            comms::option::DefaultNumValue<1>,
            comms::option::ValidNumValueRange<1, 1>
        >;

    /// @brief Definition of "powerConsumption" field.
    using powerConsumption = field::common::U2;

    /// @brief Definition of "flags" field.
    struct flags : public
        field::common::X2T<
            comms::option::BitmaskReservedBits<0xfffc, 0>
        >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS(reEnum, powerMode);
    };

    /// @brief Definition of "vendorString" field.
    /// @tparam TOpt Extra option(s)
    template <typename TOpt = comms::option::EmptyOption>
    using vendorString = field::common::ZString<32, TOpt>;

    /// @brief Definition of "productString" field.
    /// @tparam TOpt Extra option(s)
    template <typename TOpt = comms::option::EmptyOption>
    using productString = field::common::ZString<32, TOpt>;

    /// @brief Definition of "serialNumber" field.
    /// @tparam TOpt Extra option(s)
    template <typename TOpt = comms::option::EmptyOption>
    using serialNumber = field::common::ZString<32, TOpt>;

    /// @brief All the fields bundled in std::tuple.
    /// @tparam TOpt Extra option(s) for @ref vendorString, @ref productString
    ///     and @ref serialNumber fields
    template <typename TOpt>
    using All = std::tuple<
        vendorID,
        productID,
        reserved1,
        reserved2,
        powerConsumption,
        flags,
        vendorString<TOpt>,
        productString<TOpt>,
        serialNumber<TOpt>
    >;
};

/// @brief Definition of CFG-USB message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref CfgUsbFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
/// @tparam TStrsOpt Extra option(s) for @b vendorString, @b productString
///     and @b serialNumber fields
template <typename TMsgBase = Message, typename TStrsOpt = comms::option::EmptyOption>
class CfgUsb : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_USB>,
        comms::option::FieldsImpl<CfgUsbFields::All<TStrsOpt> >,
        comms::option::MsgType<CfgUsb<TMsgBase, TStrsOpt> >
    >
{
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b vendorID for @ref CfgUsbFields::vendorID field
    ///     @li @b productID for @ref CfgUsbFields::productID field
    ///     @li @b reserved1 for @ref CfgUsbFields::reserved1 field
    ///     @li @b reserved2 for @ref CfgUsbFields::reserved2 field
    ///     @li @b powerConsumption for @ref CfgUsbFields::powerConsumption field
    ///     @li @b flags for @ref CfgUsbFields::flags field
    ///     @li @b vendorString for @ref CfgUsbFields::vendorString field
    ///     @li @b productString for @ref CfgUsbFields::productString field
    ///     @li @b serialNumber for @ref CfgUsbFields::serialNumber field
    COMMS_MSG_FIELDS_ACCESS(
        vendorID,
        productID,
        reserved1,
        reserved2,
        powerConsumption,
        flags,
        vendorString,
        productString,
        serialNumber
    );

    /// @brief Default constructor
    CfgUsb() = default;

    /// @brief Copy constructor
    CfgUsb(const CfgUsb&) = default;

    /// @brief Move constructor
    CfgUsb(CfgUsb&& other) = default;

    /// @brief Destructor
    ~CfgUsb() = default;

    /// @brief Copy assignment
    CfgUsb& operator=(const CfgUsb&) = default;

    /// @brief Move assignment
    CfgUsb& operator=(CfgUsb&&) = default;
};


}  // namespace message

}  // namespace ublox

