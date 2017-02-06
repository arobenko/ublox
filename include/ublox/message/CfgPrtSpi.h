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
/// @brief Contains definition of CFG-PRT (@b SPI) message and its fields.

#pragma once


#include "ublox/Message.h"
#include "CfgPrt.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the CFG-PRT (@b SPI) message fields.
/// @see CfgPrtSpi
struct CfgPrtSpiFields : public CfgPrtFields
{
    /// @brief Value enumeration for @ref spiMode member field of @ref mode bitfield.
    enum class SpiMode : std::uint8_t
    {
        Mode_0, ///< SPI Mode 0
        Mode_1, ///< SPI Mode 1
        Mode_2, ///< SPI Mode 2
        Mode_3, ///< SPI Mode 3
        NumOfValues ///< number of available modes
    };

    /// @brief Value enumeration for @ref flowControl member field of @ref mode bitfield.
    enum class FlowControl : std::uint8_t
    {
        Disabled, ///< disabled
        Enabled, ///< enabled
        NumOfValues ///< number of available values
    };

    /// @brief Definition of "portID" field.
    using portID =
        field::common::EnumT<
            PortId,
            comms::option::ValidNumValueRange<(int)PortId::SPI, (int)PortId::SPI>,
            comms::option::DefaultNumValue<(int)PortId::SPI>
        >;

    /// @brief Definition of "spiMode" member field of @ref mode bitfield.
    using spiMode =
        field::common::EnumT<
            SpiMode,
            comms::option::FixedBitLength<2>,
            comms::option::ValidNumValueRange<0, (int)SpiMode::NumOfValues - 1>
        >;

    /// @brief Definition of "flowControl" member field of @ref mode bitfield.
    using flowControl =
        field::common::EnumT<
            FlowControl,
            comms::option::FixedBitLength<1>,
            comms::option::ValidNumValueRange<0, (int)FlowControl::NumOfValues - 1>
        >;

    /// @brief Definition of "ffCnt" member field of @ref mode bitfield.
    using ffCnt =
        field::common::U1T<
            comms::option::FixedBitLength<8>
        >;

    /// @brief Definition of "mode" field.
    class mode : public
        field::common::BitfieldT<
            std::tuple<
                field::common::res1T<comms::option::FixedBitLength<1> >,
                spiMode,
                field::common::res1T<comms::option::FixedBitLength<3> >,
                flowControl,
                field::common::res1T<comms::option::FixedBitLength<1> >,
                ffCnt,
                field::common::res4T< comms::option::FixedBitLength<16> >
            >
        >
    {
    public:
        /// @brief Allow access to internal fields.
        /// @details See definition of @b COMMS_FIELD_MEMBERS_ACCESS macro
        ///     related to @b comms::field::Bitfield class from COMMS library
        ///     for details.
        COMMS_FIELD_MEMBERS_ACCESS(
            unused0,
            spiMode,
            unused1,
            flowControl,
            unused2,
            ffCnt,
            unused3);
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

/// @brief Definition of CFG-PRT (@b SPI) message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref CfgPrtSpiFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class CfgPrtSpi : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_PRT>,
        comms::option::FieldsImpl<CfgPrtSpiFields::All>,
        comms::option::MsgType<CfgPrtSpi<TMsgBase> >,
        comms::option::HasDoRefresh
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_PRT>,
        comms::option::FieldsImpl<CfgPrtSpiFields::All>,
        comms::option::MsgType<CfgPrtSpi<TMsgBase> >,
        comms::option::HasDoRefresh
    > Base;
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b portID for @ref CfgPrtSpiFields::portID field
    ///     @li @b reserved0 for @ref CfgPrtSpiFields::reserved0 field
    ///     @li @b txReady for @ref CfgPrtFields::txReady field
    ///     @li @b mode for @ref CfgPrtSpiFields::mode field
    ///     @li @b reserved3 for @ref CfgPrtSpiFields::reserved3 field
    ///     @li @b inProtoMask for @ref CfgPrtFields::inProtoMask field
    ///     @li @b outProtoMask for @ref CfgPrtFields::outProtoMask field
    ///     @li @b flags for @ref CfgPrtFields::flags field
    ///     @li @b reserved5 for @ref CfgPrtSpiFields::reserved5 field
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
    CfgPrtSpi() = default;

    /// @brief Copy constructor
    CfgPrtSpi(const CfgPrtSpi&) = default;

    /// @brief Move constructor
    CfgPrtSpi(CfgPrtSpi&& other) = default;

    /// @brief Destructor
    virtual ~CfgPrtSpi() = default;

    /// @brief Copy assignment
    CfgPrtSpi& operator=(const CfgPrtSpi&) = default;

    /// @brief Move assignment
    CfgPrtSpi& operator=(CfgPrtSpi&&) = default;

    /// @brief Provides custom read functionality.
    /// @details Reads only first "portID" field (@ref CfgPrtSpiFields::portID) and
    ///     checks its value. If the value is @b NOT CfgPrtSpiFields::PortId::SPI,
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
        if (portIdField.value() != CfgPrtSpiFields::PortId::SPI) {
            return comms::ErrorStatus::InvalidMsgData;
        }

        return Base::template readFieldsFrom<FieldIdx_reserved0>(iter, len);
    }

    /// @brief Provides custom refresh functionality
    /// @details This function makes sure that the value of the
    ///     "portID" field (@ref CfgPrtSpiFields::portID) remains CfgPrtSpiFields::PortId::SPI.
    /// @return @b true in case the "portID" field was modified, @b false otherwise
    bool doRefresh()
    {
        auto& allFields = Base::fields();
        auto& portIdField = std::get<FieldIdx_portID>(allFields);
        if (portIdField.value() == CfgPrtSpiFields::PortId::SPI) {
            return false;
        }

        portIdField.value() = CfgPrtSpiFields::PortId::SPI;
        return true;
    }
};


}  // namespace message

}  // namespace ublox





