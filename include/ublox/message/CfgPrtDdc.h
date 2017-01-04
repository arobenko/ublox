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
    /// @brief Use this enumeration to access member fields of @ref mode bitfield.
    enum
    {
        mode_slaveAddr = 1, ///< index of @ref slaveAddr member field
        mode_numOfValues = 3 ///< upper limit for available fields
    };

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
    using mode =
        field::common::BitfieldT<
            std::tuple<
                field::common::res1T<comms::option::FixedBitLength<1> >,
                slaveAddr,
                field::common::res4T<comms::option::FixedBitLength<24> >
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

/// @brief Definition of CFG-PRT (@b DDC) message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref CfgPrtDdcFields and for definition of the fields this message contains.
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

#ifdef FOR_DOXYGEN_DOC_ONLY
    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_portID, ///< @b portID field, see @ref CfgPrtDdcFields::portID
        FieldIdx_reserved0, ///< @b reserved0 field, see @ref CfgPrtDdcFields::reserved0
        FieldIdx_txReady, ///< @b txReady field, see @ref CfgPrtDdcFields::txReady
        FieldIdx_mode, ///< @b mode field, see @ref CfgPrtDdcFields::mode
        FieldIdx_reserved3, ///< @b reserved3 field, see @ref CfgPrtDdcFields::reserved3
        FieldIdx_inProtoMask, ///< @b inProtoMask field, see @ref CfgPrtDdcFields::inProtoMask
        FieldIdx_outProtoMask, ///< @b outProtoMask field, see @ref CfgPrtDdcFields::outProtoMask
        FieldIdx_flags, ///< @b flags field, see @ref CfgPrtDdcFields::flags
        FieldIdx_reserved5, ///< @b reserved5 field, see @ref CfgPrtDdcFields::reserved5
        FieldIdx_numOfValues ///< number of available fields
    };

    /// @brief Access to fields bundled as a struct
    struct FieldsAsStruct
    {
        CfgPrtDdcFields::portID& portID; ///< @b portID field, see @ref CfgPrtDdcFields::portID
        CfgPrtDdcFields::reserved0& reserved0; ///< @b reserved0 field, see @ref CfgPrtDdcFields::reserved0
        CfgPrtDdcFields::txReady& txReady; ///< @b txReady field, see @ref CfgPrtDdcFields::txReady
        CfgPrtDdcFields::mode& mode; ///< @b mode field, see @ref CfgPrtDdcFields::mode
        CfgPrtDdcFields::reserved3& reserved3; ///< @b reserved3 field, see @ref CfgPrtDdcFields::reserved3
        CfgPrtDdcFields::inProtoMask& inProtoMask; ///< @b inProtoMask field, see @ref CfgPrtDdcFields::inProtoMask
        CfgPrtDdcFields::outProtoMask& outProtoMask; ///< @b outProtoMask field, see @ref CfgPrtDdcFields::outProtoMask
        CfgPrtDdcFields::flags& flags; ///< @b flags field, see @ref CfgPrtDdcFields::flags
        CfgPrtDdcFields::reserved5& reserved5; ///< @b reserved5 field, see @ref CfgPrtDdcFields::reserved5
    };

    /// @brief Access to @b const fields bundled as a struct
    struct ConstFieldsAsStruct
    {
        const CfgPrtDdcFields::portID& portID; ///< @b portID field, see @ref CfgPrtDdcFields::portID
        const CfgPrtDdcFields::reserved0& reserved0; ///< @b reserved0 field, see @ref CfgPrtDdcFields::reserved0
        const CfgPrtDdcFields::txReady& txReady; ///< @b txReady field, see @ref CfgPrtDdcFields::txReady
        const CfgPrtDdcFields::mode& mode; ///< @b mode field, see @ref CfgPrtDdcFields::mode
        const CfgPrtDdcFields::reserved3& reserved3; ///< @b reserved3 field, see @ref CfgPrtDdcFields::reserved3
        const CfgPrtDdcFields::inProtoMask& inProtoMask; ///< @b inProtoMask field, see @ref CfgPrtDdcFields::inProtoMask
        const CfgPrtDdcFields::outProtoMask& outProtoMask; ///< @b outProtoMask field, see @ref CfgPrtDdcFields::outProtoMask
        const CfgPrtDdcFields::flags& flags; ///< @b flags field, see @ref CfgPrtDdcFields::flags
        const CfgPrtDdcFields::reserved5& reserved5; ///< @b reserved5 field, see @ref CfgPrtDdcFields::reserved5
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
    CfgPrtDdc() = default;

    /// @brief Copy constructor
    CfgPrtDdc(const CfgPrtDdc&) = default;

    /// @brief Move constructor
    CfgPrtDdc(CfgPrtDdc&& other) = default;

    /// @brief Destructor
    virtual ~CfgPrtDdc() = default;

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





