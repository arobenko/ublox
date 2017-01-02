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
/// @brief Contains definition of CFG-GNSS message and its fields.

#pragma once

#include <algorithm>

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the CFG-GNSS message fields.
/// @see CfgGnss
struct CfgGnssFields
{
    /// @brief Enumeration for @ref gnssId field.
    enum class GnssId : std::uint8_t
    {
        GPS = 0,
        SBAS = 1,
        QZSS = 5,
        GLONASS = 6
    };

    /// @brief Custom value validator for @ref gnssId field.
    struct GnssIdValidator
    {
        template <typename TField>
        bool operator()(const TField& field) const
        {
            auto value = field.value();
            static const GnssId Values[] = {
                GnssId::GPS,
                GnssId::SBAS,
                GnssId::QZSS,
                GnssId::GLONASS
            };

            auto iter = std::lower_bound(std::begin(Values), std::end(Values), value);
            return (iter != std::end(Values)) && (*iter == value);
        }
    };

    /// @brief Bit access anumerator for @ref flags bitmask field
    enum
    {
        flags_enable, ///< @b enable bit numer
        flags_numOfValues ///< number of available bits
    };

    /// @brief Use this enumerator to access member fields of @ref block bundle field.
    enum
    {
        block_gnssId,  ///< @b index of @ref gnssId member field
        block_resTrkCh,  ///< @b index of @ref resTrkCh member field
        block_maxTrkCh,  ///< @b index of @ref maxTrkCh member field
        block_reserved1,  ///< @b index of @ref reserved1 member field
        block_flags,  ///< @b index of @ref flags member field
        block_numOfValues  ///< number of member fields
    };

    /// @brief Definition of "msgVer" field.
    using msgVer =
        field::common::U1T<
            comms::option::ValidNumValueRange<0, 0>
        >;

    /// @brief Definition of "numTrkChHw" field.
    using numTrkChHw = field::common::U1;

    /// @brief Definition of "numTrkChUse" field.
    using numTrkChUse = field::common::U1;

    /// @brief Definition of "numConfigBlocks" field.
    using numConfigBlocks = field::common::U1;

    /// @brief Definition of "gnssId" field.
    using gnssId =
        field::common::EnumT<
            GnssId,
            comms::option::ContentsValidator<GnssIdValidator>
        >;

    /// @brief Definition of "resTrkCh" field.
    using resTrkCh = field::common::U1;

    /// @brief Definition of "maxTrkCh" field.
    using maxTrkCh = field::common::U1;

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res1;

    /// @brief Definition of "flags" field.
    using flags =
        field::common::X4T<
            comms::option::BitmaskReservedBits<0xfffffffe, 0>
        >;

    /// @brief Definition of a single configuration block
    using block =
        field::common::BundleT<
            std::tuple<
                gnssId,
                resTrkCh,
                maxTrkCh,
                reserved1,
                flags
            >
        >;

    /// @brief Definition of the list of configuration blocks
    using blocksList = field::common::ListT<block>;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        msgVer,
        numTrkChHw,
        numTrkChUse,
        numConfigBlocks,
        blocksList
    >;

};

/// @brief Definition of CFG-GNSS message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref CfgGnssFields and for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class CfgGnss : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_GNSS>,
        comms::option::FieldsImpl<CfgGnssFields::All>,
        comms::option::MsgType<CfgGnss<TMsgBase> >,
        comms::option::DispatchImpl,
        comms::option::MsgDoRead,
        comms::option::MsgDoRefresh
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_GNSS>,
        comms::option::FieldsImpl<CfgGnssFields::All>,
        comms::option::MsgType<CfgGnss<TMsgBase> >,
        comms::option::DispatchImpl,
        comms::option::MsgDoRead,
        comms::option::MsgDoRefresh
    > Base;
public:

#ifdef FOR_DOXYGEN_DOC_ONLY
    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_msgVer, ///< @b msgVer field, see @ref CfgGnssFields::msgVer
        FieldIdx_numTrkChHw, ///< @b numTrkChHw field, see @ref CfgGnssFields::numTrkChHw
        FieldIdx_numTrkChUse, ///< @b numTrkChUse field, see @ref CfgGnssFields::numTrkChUse
        FieldIdx_numConfigBlocks, ///< @b numConfigBlocks field, see @ref CfgGnssFields::numConfigBlocks
        FieldIdx_blocksList, ///< @b blocksList field, see @ref CfgGnssFields::blocksList
        FieldIdx_numOfValues ///< number of available fields
    };

    /// @brief Access to fields bundled as a struct
    struct FieldsAsStruct
    {
        CfgGnssFields::msgVer& msgVer; ///< @b msgVer field, see @ref CfgGnssFields::msgVer
        CfgGnssFields::numTrkChHw& numTrkChHw; ///< @b numTrkChHw field, see @ref CfgGnssFields::numTrkChHw
        CfgGnssFields::numTrkChUse& numTrkChUse; ///< @b numTrkChUse field, see @ref CfgGnssFields::numTrkChUse
        CfgGnssFields::numConfigBlocks& numConfigBlocks; ///< @b numConfigBlocks field, see @ref CfgGnssFields::numConfigBlocks
        CfgGnssFields::blocksList& blocksList; ///< @b blocksList field, see @ref CfgGnssFields::blocksList
    };

    /// @brief Access to @b const fields bundled as a struct
    struct ConstFieldsAsStruct
    {
        const CfgGnssFields::msgVer& msgVer; ///< @b msgVer field, see @ref CfgGnssFields::msgVer
        const CfgGnssFields::numTrkChHw& numTrkChHw; ///< @b numTrkChHw field, see @ref CfgGnssFields::numTrkChHw
        const CfgGnssFields::numTrkChUse& numTrkChUse; ///< @b numTrkChUse field, see @ref CfgGnssFields::numTrkChUse
        const CfgGnssFields::numConfigBlocks& numConfigBlocks; ///< @b numConfigBlocks field, see @ref CfgGnssFields::numConfigBlocks
        const CfgGnssFields::blocksList& blocksList; ///< @b blocksList field, see @ref CfgGnssFields::blocksList
    };

    /// @brief Get access to fields bundled into a struct
    FieldsAsStruct fieldsAsStruct();

    /// @brief Get access to @b const fields bundled into a struct
    ConstFieldsAsStruct fieldsAsStruct() const;

#else
    COMMS_MSG_FIELDS_ACCESS(Base, msgVer, numTrkChHw, numTrkChUse, numConfigBlocks, blocksList);
#endif // #ifdef FOR_DOXYGEN_DOC_ONLY

    /// @brief Default constructor
    CfgGnss() = default;

    /// @brief Copy constructor
    CfgGnss(const CfgGnss&) = default;

    /// @brief Move constructor
    CfgGnss(CfgGnss&& other) = default;

    /// @brief Destructor
    virtual ~CfgGnss() = default;

    /// @brief Copy assignment
    CfgGnss& operator=(const CfgGnss&) = default;

    /// @brief Move assignment
    CfgGnss& operator=(CfgGnss&&) = default;

    /// @brief Provides custom read functionality.
    /// @details The size of "blocksList" (see @ref CfgGnssFields::blocksList) list is
    ///     determined (forced) by the value of "numConfigBlocks" (see @ref CfgGnssFields::numConfigBlocks)
    ///     field.
    template <typename TIter>
    comms::ErrorStatus doRead(TIter& iter, std::size_t len)
    {
        auto es = Base::template readFieldsUntil<FieldIdx_blocksList>(iter, len);
        if (es != comms::ErrorStatus::Success) {
            return es;
        }

        auto& allFields = Base::fields();
        auto& numBlocksField = std::get<FieldIdx_numConfigBlocks>(allFields);
        auto& dataField = std::get<FieldIdx_blocksList>(allFields);
        dataField.forceReadElemCount(numBlocksField.value());

        return Base::template readFieldsFrom<FieldIdx_blocksList>(iter, len);
    }

    /// @brief Provides custom refresh functionality
    /// @details The value of "numConfigBlocks" (see @ref CfgGnssFields::numConfigBlocks) is
    ///     determined by the size of the"blocksList" (see @ref CfgGnssFields::blocksList) list
    ///     field.
    /// @return @b true in case the value of @b "numConfigBlocks" field was modified, @b false otherwise
    bool doRefresh()
    {
        auto& allFields = Base::fields();
        auto& numBlocksField = std::get<FieldIdx_numConfigBlocks>(allFields);
        auto& dataField = std::get<FieldIdx_blocksList>(allFields);
        if (numBlocksField.value() == dataField.value().size()) {
            return false;
        }

        numBlocksField.value() = dataField.value().size();
        return true;
    }

};


}  // namespace message

}  // namespace ublox

