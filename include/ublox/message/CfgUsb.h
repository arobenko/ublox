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
    /// @brief Bits access enumeration for @ref flags bitmask field.
    enum
    {
        flags_reEnum, ///< @b reEnum bit index
        flags_powerMode, ///< @b powerMode bit index
        flags_numOfValues /// number of available bits
    };

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
    using flags =
        field::common::X2T<
            comms::option::BitmaskReservedBits<0xfffc, 0>
        >;

    /// @brief Definition of "vendorString" field.
    using vendorString = field::common::ZString<32>;

    /// @brief Definition of "productString" field.
    using productString = field::common::ZString<32>;

    /// @brief Definition of "serialNumber" field.
    using serialNumber = field::common::ZString<32>;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        vendorID,
        productID,
        reserved1,
        reserved2,
        powerConsumption,
        flags,
        vendorString,
        productString,
        serialNumber
    >;
};

/// @brief Definition of CFG-USB message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref CfgUsbFields and for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class CfgUsb : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_USB>,
        comms::option::FieldsImpl<CfgUsbFields::All>,
        comms::option::MsgType<CfgUsb<TMsgBase> >,
        comms::option::DispatchImpl
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_USB>,
        comms::option::FieldsImpl<CfgUsbFields::All>,
        comms::option::MsgType<CfgUsb<TMsgBase> >,
        comms::option::DispatchImpl
    > Base;
public:

#ifdef FOR_DOXYGEN_DOC_ONLY
    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_vendorID, ///< @b vendorID field, see @ref CfgUsbFields::vendorID
        FieldIdx_productID, ///< @b productID field, see @ref CfgUsbFields::productID
        FieldIdx_reserved1, ///< @b reserved1 field, see @ref CfgUsbFields::reserved1
        FieldIdx_reserved2, ///< @b reserved2 field, see @ref CfgUsbFields::reserved2
        FieldIdx_powerConsumption, ///< @b powerConsumption field, see @ref CfgUsbFields::powerConsumption
        FieldIdx_flags, ///< @b flags field, see @ref CfgUsbFields::flags
        FieldIdx_vendorString, ///< @b vendorString field, see @ref CfgUsbFields::vendorString
        FieldIdx_productString, ///< @b productString field, see @ref CfgUsbFields::productString
        FieldIdx_serialNumber, ///< @b serialNumber field, see @ref CfgUsbFields::serialNumber
        FieldIdx_numOfValues ///< number of available fields
    };

    /// @brief Access to fields bundled as a struct
    struct FieldsAsStruct
    {
        CfgUsbFields::vendorID& vendorID; ///< @b vendorID field, see @ref CfgUsbFields::vendorID
        CfgUsbFields::productID& productID; ///< @b productID field, see @ref CfgUsbFields::productID
        CfgUsbFields::reserved1& reserved1; ///< @b reserved1 field, see @ref CfgUsbFields::reserved1
        CfgUsbFields::reserved2& reserved2; ///< @b reserved2 field, see @ref CfgUsbFields::reserved2
        CfgUsbFields::powerConsumption& powerConsumption; ///< @b powerConsumption field, see @ref CfgUsbFields::powerConsumption
        CfgUsbFields::flags& flags; ///< @b flags field, see @ref CfgUsbFields::flags
        CfgUsbFields::vendorString& vendorString; ///< @b vendorString field, see @ref CfgUsbFields::vendorString
        CfgUsbFields::productString& productString; ///< @b productString field, see @ref CfgUsbFields::productString
        CfgUsbFields::serialNumber& serialNumber; ///< @b serialNumber field, see @ref CfgUsbFields::serialNumber
    };

    /// @brief Access to @b const fields bundled as a struct
    struct ConstFieldsAsStruct
    {
        const CfgUsbFields::vendorID& vendorID; ///< @b vendorID field, see @ref CfgUsbFields::vendorID
        const CfgUsbFields::productID& productID; ///< @b productID field, see @ref CfgUsbFields::productID
        const CfgUsbFields::reserved1& reserved1; ///< @b reserved1 field, see @ref CfgUsbFields::reserved1
        const CfgUsbFields::reserved2& reserved2; ///< @b reserved2 field, see @ref CfgUsbFields::reserved2
        const CfgUsbFields::powerConsumption& powerConsumption; ///< @b powerConsumption field, see @ref CfgUsbFields::powerConsumption
        const CfgUsbFields::flags& flags; ///< @b flags field, see @ref CfgUsbFields::flags
        const CfgUsbFields::vendorString& vendorString; ///< @b vendorString field, see @ref CfgUsbFields::vendorString
        const CfgUsbFields::productString& productString; ///< @b productString field, see @ref CfgUsbFields::productString
        const CfgUsbFields::serialNumber& serialNumber; ///< @b serialNumber field, see @ref CfgUsbFields::serialNumber
    };

    /// @brief Get access to fields bundled into a struct
    FieldsAsStruct fieldsAsStruct();

    /// @brief Get access to @b const fields bundled into a struct
    ConstFieldsAsStruct fieldsAsStruct() const;

#else
    COMMS_MSG_FIELDS_ACCESS(Base,
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
#endif // #ifdef FOR_DOXYGEN_DOC_ONLY

    /// @brief Default constructor
    CfgUsb() = default;

    /// @brief Copy constructor
    CfgUsb(const CfgUsb&) = default;

    /// @brief Move constructor
    CfgUsb(CfgUsb&& other) = default;

    /// @brief Destructor
    virtual ~CfgUsb() = default;

    /// @brief Copy assignment
    CfgUsb& operator=(const CfgUsb&) = default;

    /// @brief Move assignment
    CfgUsb& operator=(CfgUsb&&) = default;
};


}  // namespace message

}  // namespace ublox

