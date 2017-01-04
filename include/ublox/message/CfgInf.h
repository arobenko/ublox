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
/// @brief Contains definition of CFG-INF message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/cfg.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the CFG-INF message fields.
/// @see CfgInf
struct CfgInfFields
{
    /// @brief Protocol ID enumeration.
    using ProtocolId = field::cfg::ProtocolId;

    /// @brief Use this enumeration to access member fields of @ref element bundle.
    enum
    {
        element_protocolID, ///< index of @ref protocolID member field
        element_reserved0, ///< index of @ref reserved0 member field
        element_reserved1, ///< index of @ref reserved1 member field
        element_infMsgMask, ///< index of @ref infMsgMask member field
        element_numOfValues ///< number of member fields
    };

    /// @brief Use this enumeration to access right bitmask in @ref infMsgMask list field.
    enum
    {
        infMsgMask_ddc, ///< index of @b DDC bitmask field
        infMsgMask_uart, ///< index of @b UART bitmask field
        infMsgMask_uart2, ///< index of @b UART2 bitmask field
        infMsgMask_usb, ///< index of @b USB bitmask field
        infMsgMask_spi, ///< index of @b SPI bitmask field
        infMsgMask_reserved, ///< index of reserved bitmask field
        infMsgMask_numOfValues ///< number of available masks
    };

    /// @brief Bits access enumeration for @ref mask bitmask field from @ref infMsgMask list.
    enum
    {
        mask_ERROR, ///< @b ERROR bit index
        mask_WARNING, ///< @b WARNING bit index
        mask_NOTICE, ///< @b NOTICE bit index
        mask_DEBUG, ///< @b DEBUG bit index
        mask_TEST, ///< @b TEST bit index
        mask_numOfValues ///< number of available bits
    };

    /// @brief Definition of "protocolID" field.
    using protocolID = field::cfg::protocolID;

    /// @brief Definition of "reserved0" field.
    using reserved0 = field::common::res1;

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res2;

    /// @brief definition of single bitmask value field in @ref infMsgMask field
    using mask =
        field::common::X1T<comms::option::BitmaskReservedBits<0xe0, 0> >;

    /// @brief Definition of "infMsgMask" field.
    using infMsgMask =
        field::common::ListT<
            mask,
            comms::option::SequenceFixedSize<infMsgMask_numOfValues>
        >;

    /// @brief Definition of a single configuration bundle element in @ref list field.
    using element =
        field::common::BundleT<
            std::tuple<
                protocolID,
                reserved0,
                reserved1,
                infMsgMask
            >
        >;

    /// @brief @ref CfgInf message may contain multiple configuration elements
    ///     (see @ref element). This field defines a list of such elements.
    using list = field::common::ListT<element>;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        list
    >;
};

/// @brief Definition of CFG-INF message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref CfgInfFields and for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class CfgInf : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_INF>,
        comms::option::FieldsImpl<CfgInfFields::All>,
        comms::option::MsgType<CfgInf<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_INF>,
        comms::option::FieldsImpl<CfgInfFields::All>,
        comms::option::MsgType<CfgInf<TMsgBase> >
    > Base;
public:

#ifdef FOR_DOXYGEN_DOC_ONLY
    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_list, ///< @b list of configurations, see @ref CfgInfFields::list
        FieldIdx_numOfValues ///< number of available fields
    };

    /// @brief Access to fields bundled as a struct
    struct FieldsAsStruct
    {
        CfgInfFields::list& list; ///< @b list of configurations, see @ref CfgInfFields::list
    };

    /// @brief Access to @b const fields bundled as a struct
    struct ConstFieldsAsStruct
    {
        const CfgInfFields::list& list; ///< @b list of configurations, see @ref CfgInfFields::list
    };

    /// @brief Get access to fields bundled into a struct
    FieldsAsStruct fieldsAsStruct();

    /// @brief Get access to @b const fields bundled into a struct
    ConstFieldsAsStruct fieldsAsStruct() const;

#else
    COMMS_MSG_FIELDS_ACCESS(Base, list);
#endif // #ifdef FOR_DOXYGEN_DOC_ONLY

    /// @brief Default constructor
    CfgInf() = default;

    /// @brief Copy constructor
    CfgInf(const CfgInf&) = default;

    /// @brief Move constructor
    CfgInf(CfgInf&& other) = default;

    /// @brief Destructor
    virtual ~CfgInf() = default;

    /// @brief Copy assignment
    CfgInf& operator=(const CfgInf&) = default;

    /// @brief Move assignment
    CfgInf& operator=(CfgInf&&) = default;
};


}  // namespace message

}  // namespace ublox

