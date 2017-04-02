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
/// @brief Contains definition of CFG-PRT (@b DDC) message and its fields.

#pragma once

#include <iterator>

#include "ublox/Message.h"
#include "ublox/field/common.h"
#include "CfgPrt.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the CFG-PRT (@b DDC) message fields.
/// @see CfgPrtDdc
struct CfgPrtDdcFields : public CfgPrtFields
{
    /// @brief Custom value validator of @ref slaveAddr member field.
    struct SlaveAddrValidator
    {
        template <typename TField>
        bool operator()(const TField& field) const
        {
            auto value = field.value();
            return (0x7 < value) && (value < 0x78) && ((value & 0x1) == 0);
        }
    };

    /// @brief Definition of "portID" field.
    using portID =
        field::common::EnumT<
            PortId,
            comms::option::ValidNumValueRange<(int)PortId::DDC, (int)PortId::DDC>,
            comms::option::DefaultNumValue<(int)PortId::DDC>
        >;

    /// @brief Definition of "slaveAddr" member field of @ref mode bitfield.
    using slaveAddr =
        field::common::U1T<
            comms::option::FixedBitLength<7>,
            comms::option::ContentsValidator<SlaveAddrValidator>
        >;

    /// @brief Definition of "mode" field.
    class mode : public
        field::common::BitfieldT<
            std::tuple<
                field::common::res1T<comms::option::FixedBitLength<1> >,
                slaveAddr,
                field::common::res4T<comms::option::FixedBitLength<24> >
            >
        >
    {
    public:
        /// @brief Allow access to internal fields.
        /// @details See definition of @b COMMS_FIELD_MEMBERS_ACCESS macro
        ///     related to @b comms::field::Bitfield class from COMMS library
        ///     for details.
        COMMS_FIELD_MEMBERS_ACCESS(unused0, slaveAddr, unused1);
    };

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        portID,
        reserved0,
        txReady,
        mode,
        reserved3,
        inProtoMask,
        outProtoMask,
        flags,
        reserved5
    >;
};

/// @brief Definition of CFG-PRT (@b DDC) message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref CfgPrtDdcFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class CfgPrtDdc : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_PRT>,
        comms::option::FieldsImpl<CfgPrtDdcFields::All>,
        comms::option::MsgType<CfgPrtDdc<TMsgBase> >,
        comms::option::HasDoRefresh
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_PRT>,
        comms::option::FieldsImpl<CfgPrtDdcFields::All>,
        comms::option::MsgType<CfgPrtDdc<TMsgBase> >,
        comms::option::HasDoRefresh
    > Base;
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b portID for @ref CfgPrtDdcFields::portID field
    ///     @li @b reserved0 for @ref CfgPrtDdcFields::reserved0 field
    ///     @li @b txReady for @ref CfgPrtFields::txReady field
    ///     @li @b mode for @ref CfgPrtDdcFields::mode field
    ///     @li @b reserved3 for @ref CfgPrtDdcFields::reserved3 field
    ///     @li @b inProtoMask for @ref CfgPrtFields::inProtoMask field
    ///     @li @b outProtoMask for @ref CfgPrtFields::outProtoMask field
    ///     @li @b flags for @ref CfgPrtFields::flags field
    ///     @li @b reserved5 for @ref CfgPrtDdcFields::reserved5 field
    COMMS_MSG_FIELDS_ACCESS(
        portID,
        reserved0,
        txReady,
        mode,
        reserved3,
        inProtoMask,
        outProtoMask,
        flags,
        reserved5
    );

    /// @brief Default constructor
    CfgPrtDdc() = default;

    /// @brief Copy constructor
    CfgPrtDdc(const CfgPrtDdc&) = default;

    /// @brief Move constructor
    CfgPrtDdc(CfgPrtDdc&& other) = default;

    /// @brief Destructor
    ~CfgPrtDdc() = default;

    /// @brief Copy assignment
    CfgPrtDdc& operator=(const CfgPrtDdc&) = default;

    /// @brief Move assignment
    CfgPrtDdc& operator=(CfgPrtDdc&&) = default;

    /// @brief Provides custom read functionality.
    /// @details Reads only first "portID" field (@ref CfgPrtDdcFields::portID) and
    ///     checks its value. If the value is @b NOT CfgPrtDdcFields::PortId::DDC,
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
        if (portIdField.value() != CfgPrtDdcFields::PortId::DDC) {
            return comms::ErrorStatus::InvalidMsgData;
        }

        return Base::template readFieldsFrom<FieldIdx_reserved0>(iter, len);
    }

    /// @brief Provides custom refresh functionality
    /// @details This function makes sure that the value of the
    ///     "portID" field (@ref CfgPrtDdcFields::portID) remains CfgPrtDdcFields::PortId::DDC.
    /// @return @b true in case the "portID" field was modified, @b false otherwise
    bool doRefresh()
    {
        auto& allFields = Base::fields();
        auto& portIdField = std::get<FieldIdx_portID>(allFields);
        if (portIdField.value() == CfgPrtDdcFields::PortId::DDC) {
            return false;
        }

        portIdField.value() = CfgPrtDdcFields::PortId::DDC;
        return true;
    }
};


}  // namespace message

}  // namespace ublox





