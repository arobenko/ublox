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
/// @brief Contains definition of CFG-PRT (@b UART) message and its fields.

#pragma once

#include "ublox/Message.h"
#include "CfgPrt.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the CFG-PRT (@b SPI) message fields.
/// @see CfgPrtUart
struct CfgPrtUartFields : public CfgPrtFields
{
    /// @brief Value enumeration for @ref charLen member field of @ref mode bitfield.
    enum class CharLen : std::uint8_t
    {
        Bits_5, ///< 5 bits
        Bits_6, ///< 6 bits
        Bits_7, ///< 7 bits
        Bits_8, ///< 8 bits
        NumOfValues ///< number of available values
    };

    /// @brief Value enumeration for @ref parity member field of @ref mode bitfield.
    enum class Parity : std::uint8_t
    {
        Even, ///< even
        Odd, ///< odd
        NoParity = 4, ///< none
        NoParity2 ///< none
    };

    /// @brief Value enumeration for @ref nStopBits member field of @ref mode bitfield.
    enum class StopBits : std::uint8_t
    {
        One, ///< 1 stop bit
        OneAndHalf, ///< 1.5 stop bits
        Two, ///< 2 stop bits
        Half, ///< 0.5 stop bits
        NumOfValues /// number of available values
    };

    /// @brief Custom validator for @ref parity member field
    struct ParityValidator
    {
        template <typename TField>
        bool operator()(const TField& field) const
        {
            auto value = field.value();
            return
                (value == Parity::Even) ||
                (value == Parity::Odd) ||
                (value == Parity::NoParity) ||
                (value == Parity::NoParity2);
        }
    };

    enum
    {
        mode_reserved1,
        mode_charLen,
        mode_reserved2,
        mode_parity,
        mode_nStopBits,
        mode_reserved3,
        mode_numOfValues
    };

    /// @brief Definition of "portID" field.
    using portID =
        field::common::EnumT<
            PortId,
            comms::option::ValidNumValueRange<(int)PortId::UART, (int)PortId::UART2>,
            comms::option::DefaultNumValue<(int)PortId::UART>
        >;

    /// @brief Definition of "charLen" member field of @ref mode bitfield.
    using charLen =
        field::common::EnumT<
            CharLen,
            comms::option::FixedBitLength<2>,
            comms::option::ValidNumValueRange<0, (int)CharLen::NumOfValues - 1>,
            comms::option::DefaultNumValue<(int)CharLen::Bits_8>
        >;

    /// @brief Definition of "parity" member field of @ref mode bitfield.
    using parity =
        field::common::EnumT<
            Parity,
            comms::option::FixedBitLength<3>,
            comms::option::ContentsValidator<ParityValidator>
        >;

    /// @brief Definition of "nStopBits" member field of @ref mode bitfield.
    using nStopBits =
        field::common::EnumT<
            StopBits,
            comms::option::FixedBitLength<2>,
            comms::option::ValidNumValueRange<0, (int)StopBits::NumOfValues - 1>
        >;

    /// @brief Definition of "mode" field.
    using mode =
        field::common::BitfieldT<
            std::tuple<
                field::common::X1T<
                    comms::option::FixedBitLength<6>,
                    comms::option::BitmaskReservedBits<0xff, 0x10>,
                    comms::option::DefaultNumValue<0x10>
                >,
                charLen,
                field::common::res1T<comms::option::FixedBitLength<1> >,
                parity,
                nStopBits,
                field::common::res4T<comms::option::FixedBitLength<18> >
            >
        >;

    /// @brief Definition of "baudRate" field.
    using baudRate = field::common::U4;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        portID,
        reserved0,
        txReady,
        mode,
        baudRate,
        inProtoMask,
        outProtoMask,
        flags,
        reserved5
    >;
};

/// @brief Definition of CFG-PRT (@b UART) message
/// @details Inherits from
///     <a href="https://dl.dropboxusercontent.com/u/46999418/comms_champion/comms/html/classcomms_1_1MessageBase.html">comms::MessageBase</a>
///     while providing @b TMsgBase as common interface class as well as
///     @b comms::option::StaticNumIdImpl, @b comms::option::FieldsImpl, and
///     @b comms::option::DispatchImpl as options. @n
///     See @ref CfgPrtUartFields and for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class CfgPrtUart : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_PRT>,
        comms::option::FieldsImpl<CfgPrtUartFields::All>,
        comms::option::DispatchImpl<CfgPrtUart<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_PRT>,
        comms::option::FieldsImpl<CfgPrtUartFields::All>,
        comms::option::DispatchImpl<CfgPrtUart<TMsgBase> >
    > Base;
public:

    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_portID, ///< @b portID field, see @ref CfgPrtUartFields::portID
        FieldIdx_reserved0, ///< @b reserved0 field, see @ref CfgPrtUartFields::reserved0
        FieldIdx_txReady, ///< @b txReady field, see @ref CfgPrtUartFields::txReady
        FieldIdx_mode, ///< @b mode field, see @ref CfgPrtUartFields::mode
        FieldIdx_baudRate, ///< @b baudRate field, see @ref CfgPrtUartFields::baudRate
        FieldIdx_inProtoMask, ///< @b inProtoMask field, see @ref CfgPrtUartFields::inProtoMask
        FieldIdx_outProtoMask, ///< @b outProtoMask field, see @ref CfgPrtUartFields::outProtoMask
        FieldIdx_flags, ///< @b flags field, see @ref CfgPrtUartFields::flags
        FieldIdx_reserved5, ///< @b reserved5 field, see @ref CfgPrtUartFields::reserved5
        FieldIdx_numOfValues ///< number of available fields
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    /// @brief Default constructor
    CfgPrtUart() = default;

    /// @brief Copy constructor
    CfgPrtUart(const CfgPrtUart&) = default;

    /// @brief Move constructor
    CfgPrtUart(CfgPrtUart&& other) = default;

    /// @brief Destructor
    virtual ~CfgPrtUart() = default;

    /// @brief Copy assignment
    CfgPrtUart& operator=(const CfgPrtUart&) = default;

    /// @brief Move assignment
    CfgPrtUart& operator=(CfgPrtUart&&) = default;

protected:

    /// @brief Overrides read functionality provided by the base class.
    /// @details Reads only first "portID" field (@ref CfgPrtUartFields::portID) and
    ///     checks its value. If the value is @b NOT CfgPrtUartFields::PortId::UART,
    ///     the read operation fails with comms::ErrorStatus::InvalidMsgData error
    ///     status. Otherwise the read operation continues as expected.
    virtual comms::ErrorStatus readImpl(
        typename Base::ReadIterator& iter,
        std::size_t len) override
    {
        auto es = Base::template readFieldsUntil<FieldIdx_reserved0>(iter, len);
        if (es != comms::ErrorStatus::Success) {
            return es;
        }

        auto& allFields = Base::fields();
        auto& portIdField = std::get<FieldIdx_portID>(allFields);
        if ((portIdField.value() != CfgPrtUartFields::PortId::UART) &&
            (portIdField.value() != CfgPrtUartFields::PortId::UART2)) {
            return comms::ErrorStatus::InvalidMsgData;
        }

        return Base::template readFieldsFrom<FieldIdx_reserved0>(iter, len);
    }

    /// @brief Overrides default refreshing functionality provided by the interface class.
    /// @details This function makes sure that the value of the
    ///     "portID" field (@ref CfgPrtUartFields::portID) remains CfgPrtUartFields::PortId::UART.
    /// @return @b true in case the "portID" field was modified, @b false otherwise
    virtual bool refreshImpl() override
    {
        auto& allFields = Base::fields();
        auto& portIdField = std::get<FieldIdx_portID>(allFields);
        if ((portIdField.value() == CfgPrtUartFields::PortId::UART) ||
            (portIdField.value() == CfgPrtUartFields::PortId::UART2)) {
            return false;
        }

        portIdField.value() = CfgPrtUartFields::PortId::UART;
        return true;
    }

};


}  // namespace message

}  // namespace ublox





