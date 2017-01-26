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
    struct flags : public
        field::common::X4T<
            comms::option::BitmaskReservedBits<0xfffffffe, 0>
        >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS(enable);
    };

    /// @brief Definition of a single configuration block
    struct block : public
        field::common::BundleT<
            std::tuple<
                gnssId,
                resTrkCh,
                maxTrkCh,
                reserved1,
                flags
            >
        >
    {
        /// @brief Allow access to internal fields.
        /// @details See definition of @b COMMS_FIELD_MEMBERS_ACCESS macro
        ///     related to @b comms::field::Bitfield class from COMMS library
        ///     for details.
        COMMS_FIELD_MEMBERS_ACCESS(gnssId, resTrkCh, maxTrkCh, reserved1, flags);
    };

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
///     See @ref CfgGnssFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class CfgGnss : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_GNSS>,
        comms::option::FieldsImpl<CfgGnssFields::All>,
        comms::option::MsgType<CfgGnss<TMsgBase> >,
        comms::option::HasDoRefresh
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_GNSS>,
        comms::option::FieldsImpl<CfgGnssFields::All>,
        comms::option::MsgType<CfgGnss<TMsgBase> >,
        comms::option::HasDoRefresh
    > Base;
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b msgVer for @ref CfgGnssFields::msgVer field
    ///     @li @b numTrkChHw for @ref CfgGnssFields::numTrkChHw field
    ///     @li @b numTrkChUse for @ref CfgGnssFields::numTrkChUse field
    ///     @li @b numConfigBlocks for @ref CfgGnssFields::numConfigBlocks field
    ///     @li @b blocksList for @ref CfgGnssFields::blocksList field
    COMMS_MSG_FIELDS_ACCESS(msgVer, numTrkChHw, numTrkChUse, numConfigBlocks, blocksList);

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

