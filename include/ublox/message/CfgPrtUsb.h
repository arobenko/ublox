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
/// @brief Contains definition of CFG-PRT (@b USB) message and its fields.

#pragma once

#include "ublox/Message.h"
#include "CfgPrt.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the CFG-PRT (@b USB) message fields.
/// @see CfgPrtUsb
struct CfgPrtUsbFields : public CfgPrtFields
{
    /// @brief Definition of "portID" field.
    using portID =
        field::common::EnumT<
            PortId,
            comms::option::ValidNumValueRange<(int)PortId::USB, (int)PortId::USB>,
            comms::option::DefaultNumValue<(int)PortId::USB>
        >;

    /// @brief Definition of "reserved2" field
    using reserved2 = field::common::res4;

    /// @brief Definition of "reserved4" field
    using reserved4 = field::common::res2;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        portID,
        reserved0,
        txReady,
        reserved2,
        reserved3,
        inProtoMask,
        outProtoMask,
        reserved4,
        reserved5
    >;
};

/// @brief Definition of CFG-PRT (@b USB) message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref CfgPrtUsbFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class CfgPrtUsb : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_PRT>,
        comms::option::FieldsImpl<CfgPrtUsbFields::All>,
        comms::option::MsgType<CfgPrtUsb<TMsgBase> >,
        comms::option::HasDoRefresh
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_PRT>,
        comms::option::FieldsImpl<CfgPrtUsbFields::All>,
        comms::option::MsgType<CfgPrtUsb<TMsgBase> >,
        comms::option::HasDoRefresh
    > Base;
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b portID for @ref CfgPrtUsbFields::portID field
    ///     @li @b reserved0 for @ref CfgPrtUsbFields::reserved0 field
    ///     @li @b txReady for @ref CfgPrtFields::txReady field
    ///     @li @b reserved2 for @ref CfgPrtUsbFields::reserved2 field
    ///     @li @b reserved3 for @ref CfgPrtUsbFields::reserved3 field
    ///     @li @b inProtoMask for @ref CfgPrtFields::inProtoMask field
    ///     @li @b outProtoMask for @ref CfgPrtFields::outProtoMask field
    ///     @li @b reserved4 for @ref CfgPrtUsbFields::reserved4 field
    ///     @li @b reserved5 for @ref CfgPrtUsbFields::reserved5 field
    COMMS_MSG_FIELDS_ACCESS(Base,
        portID,
        reserved0,
        txReady,
        reserved2,
        reserved3,
        inProtoMask,
        outProtoMask,
        reserved4,
        reserved5
    );

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    /// @brief Default constructor
    CfgPrtUsb() = default;

    /// @brief Copy constructor
    CfgPrtUsb(const CfgPrtUsb&) = default;

    /// @brief Move constructor
    CfgPrtUsb(CfgPrtUsb&& other) = default;

    /// @brief Destructor
    virtual ~CfgPrtUsb() = default;

    /// @brief Copy assignment
    CfgPrtUsb& operator=(const CfgPrtUsb&) = default;

    /// @brief Move assignment
    CfgPrtUsb& operator=(CfgPrtUsb&&) = default;

    /// @brief Provides custom read functionality.
    /// @details Reads only first "portID" field (@ref CfgPrtUsbFields::portID) and
    ///     checks its value. If the value is @b NOT CfgPrtUsbFields::PortId::USB,
    ///     the read operation fails with comms::ErrorStatus::InvalidMsgData error
    ///     status. Otherwise the read operation continues as expected.
    template <typename TIter>
    comms::ErrorStatus doRead(TIter& iter, std::size_t len)
    {
        auto es = Base::template readFieldsUntil<FieldIdx_reserved0>(iter, len);
        if (es != comms::ErrorStatus::Success) {
            return es;
        }

        auto& allFields = Base::fields();
        auto& portIdField = std::get<FieldIdx_portID>(allFields);
        if (portIdField.value() != CfgPrtUsbFields::PortId::USB) {
            return comms::ErrorStatus::InvalidMsgData;
        }

        return Base::template readFieldsFrom<FieldIdx_reserved0>(iter, len);
    }

    /// @brief Provides custom refresh functionality
    /// @details This function makes sure that the value of the
    ///     "portID" field (@ref CfgPrtUsbFields::portID) remains CfgPrtUsbFields::PortId::USB.
    /// @return @b true in case the "portID" field was modified, @b false otherwise
    bool doRefresh()
    {
        auto& allFields = Base::fields();
        auto& portIdField = std::get<FieldIdx_portID>(allFields);
        if (portIdField.value() == CfgPrtUsbFields::PortId::USB) {
            return false;
        }

        portIdField.value() = CfgPrtUsbFields::PortId::USB;
        return true;
    }

};

}  // namespace message

}  // namespace ublox





