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

    /// @brief Use this enumeration to access member fields of @ref mode bitfield.
    enum
    {
        mode_spiMode = 1, ///< index of @ref spiMode member field
        mode_flowControl = 3, ///< index of @ref flowControl member field
        mode_ffCnt = 5, ///< index of @ref ffCnt member field
        mode_numOfValues = 7 ///< number of available member fields
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
    using mode =
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
        >;

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
///     See @ref CfgPrtSpiFields and for definition of the fields this message contains.
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

#ifdef FOR_DOXYGEN_DOC_ONLY
    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_portID, ///< @b portID field, see @ref CfgPrtSpiFields::portID
        FieldIdx_reserved0, ///< @b reserved0 field, see @ref CfgPrtSpiFields::reserved0
        FieldIdx_txReady, ///< @b txReady field, see @ref CfgPrtSpiFields::txReady
        FieldIdx_mode, ///< @b mode field, see @ref CfgPrtSpiFields::mode
        FieldIdx_reserved3, ///< @b reserved3 field, see @ref CfgPrtSpiFields::reserved3
        FieldIdx_inProtoMask, ///< @b inProtoMask field, see @ref CfgPrtSpiFields::inProtoMask
        FieldIdx_outProtoMask, ///< @b outProtoMask field, see @ref CfgPrtSpiFields::outProtoMask
        FieldIdx_flags, ///< @b flags field, see @ref CfgPrtSpiFields::flags
        FieldIdx_reserved5, ///< @b reserved5 field, see @ref CfgPrtSpiFields::reserved5
        FieldIdx_numOfValues ///< number of available fields
    };

    /// @brief Access to fields bundled as a struct
    struct FieldsAsStruct
    {
        CfgPrtSpiFields::portID& portID; ///< @b portID field, see @ref CfgPrtSpiFields::portID
        CfgPrtSpiFields::reserved0& reserved0; ///< @b reserved0 field, see @ref CfgPrtSpiFields::reserved0
        CfgPrtSpiFields::txReady& txReady; ///< @b txReady field, see @ref CfgPrtSpiFields::txReady
        CfgPrtSpiFields::mode& mode; ///< @b mode field, see @ref CfgPrtSpiFields::mode
        CfgPrtSpiFields::reserved3& reserved3; ///< @b reserved3 field, see @ref CfgPrtSpiFields::reserved3
        CfgPrtSpiFields::inProtoMask& inProtoMask; ///< @b inProtoMask field, see @ref CfgPrtSpiFields::inProtoMask
        CfgPrtSpiFields::outProtoMask& outProtoMask; ///< @b outProtoMask field, see @ref CfgPrtSpiFields::outProtoMask
        CfgPrtSpiFields::flags& flags; ///< @b flags field, see @ref CfgPrtSpiFields::flags
        CfgPrtSpiFields::reserved5& reserved5; ///< @b reserved5 field, see @ref CfgPrtSpiFields::reserved5
    };

    /// @brief Access to @b const fields bundled as a struct
    struct ConstFieldsAsStruct
    {
        const CfgPrtSpiFields::portID& portID; ///< @b portID field, see @ref CfgPrtSpiFields::portID
        const CfgPrtSpiFields::reserved0& reserved0; ///< @b reserved0 field, see @ref CfgPrtSpiFields::reserved0
        const CfgPrtSpiFields::txReady& txReady; ///< @b txReady field, see @ref CfgPrtSpiFields::txReady
        const CfgPrtSpiFields::mode& mode; ///< @b mode field, see @ref CfgPrtSpiFields::mode
        const CfgPrtSpiFields::reserved3& reserved3; ///< @b reserved3 field, see @ref CfgPrtSpiFields::reserved3
        const CfgPrtSpiFields::inProtoMask& inProtoMask; ///< @b inProtoMask field, see @ref CfgPrtSpiFields::inProtoMask
        const CfgPrtSpiFields::outProtoMask& outProtoMask; ///< @b outProtoMask field, see @ref CfgPrtSpiFields::outProtoMask
        const CfgPrtSpiFields::flags& flags; ///< @b flags field, see @ref CfgPrtSpiFields::flags
        const CfgPrtSpiFields::reserved5& reserved5; ///< @b reserved5 field, see @ref CfgPrtSpiFields::reserved5
    };

    /// @brief Get access to fields bundled into a struct
    FieldsAsStruct fieldsAsStruct();

    /// @brief Get access to @b const fields bundled into a struct
    ConstFieldsAsStruct fieldsAsStruct() const;

#else
    COMMS_MSG_FIELDS_ACCESS(Base,
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
#endif // #ifdef FOR_DOXYGEN_DOC_ONLY

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





