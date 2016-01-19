//
// Copyright 2015 (C). Alex Robenko. All rights reserved.
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


#pragma once

#include <algorithm>

#include "comms/Message.h"
#include "ublox/Message.h"
#include "ublox/field/MsgId.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

enum class CfgGnss_GnssId : std::uint8_t
{
    GPS = 0,
    SBAS = 1,
    QZSS = 5,
    GLONASS = 6
};

struct CfgGnss_GnssIdValidator
{
    template <typename TField>
    bool operator()(const TField& field) const
    {
        auto value = field.value();
        static const CfgGnss_GnssId Values[] = {
            CfgGnss_GnssId::GPS,
            CfgGnss_GnssId::SBAS,
            CfgGnss_GnssId::QZSS,
            CfgGnss_GnssId::GLONASS
        };

        auto iter = std::lower_bound(std::begin(Values), std::end(Values), value);
        return (iter != std::end(Values)) && (*iter == value);
    }
};

enum
{
    CfgGnssField_data_gnssId,
    CfgGnssField_data_resTrkCh,
    CfgGnssField_data_maxTrkCh,
    CfgGnssField_data_reserved1,
    CfgGnssField_data_flags,
    CfgGnssField_data_numOfValues
};

enum
{
    CfgGnssField_data_flags_enable,
    CfgGnssField_data_flags_numOfValues
};

using CfgGnssField_msgVer =
    field::common::U1T<
        comms::option::ValidNumValueRange<0, 0>
    >;
using CfgGnssField_numTrkChHw = field::common::U1;
using CfgGnssField_numTrkChUse = field::common::U1;
using CfgGnssField_numConfigBlocks = field::common::U1;

using CfgGnssField_gnssId =
    field::common::EnumT<
        CfgGnss_GnssId,
        comms::option::ContentsValidator<CfgGnss_GnssIdValidator>
    >;
using CfgGnssField_resTrkCh = field::common::U1;
using CfgGnssField_maxTrkCh = field::common::U1;
using CfgGnssField_reserved1 = field::common::res1;
using CfgGnssField_flags =
    field::common::X4T<
        comms::option::BitmaskReservedBits<0xfffffffe, 0>
    >;

using CfgGnssField_data =
    field::common::ListT<
        field::common::BundleT<
            std::tuple<
                CfgGnssField_gnssId,
                CfgGnssField_resTrkCh,
                CfgGnssField_maxTrkCh,
                CfgGnssField_reserved1,
                CfgGnssField_flags
            >
        >
    >;


using CfgGnssFields = std::tuple<
    CfgGnssField_msgVer,
    CfgGnssField_numTrkChHw,
    CfgGnssField_numTrkChUse,
    CfgGnssField_numConfigBlocks,
    CfgGnssField_data
>;

template <typename TMsgBase = Message>
class CfgGnss : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_GNSS>,
        comms::option::FieldsImpl<CfgGnssFields>,
        comms::option::DispatchImpl<CfgGnss<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_GNSS>,
        comms::option::FieldsImpl<CfgGnssFields>,
        comms::option::DispatchImpl<CfgGnss<TMsgBase> >
    > Base;
public:

    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_msgVer,
        FieldIdx_numTrkChHw,
        FieldIdx_numTrkChUse,
        FieldIdx_numConfigBlocks,
        FieldIdx_data,
        FieldIdx_numOfValues ///< number of available fields
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

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

protected:
    virtual comms::ErrorStatus readImpl(
        typename Base::ReadIterator& iter,
        std::size_t len) override
    {
        auto es = Base::template readFieldsUntil<FieldIdx_data>(iter, len);
        if (es != comms::ErrorStatus::Success) {
            return es;
        }

        auto& allFields = Base::fields();
        auto& numBlocksField = std::get<FieldIdx_numConfigBlocks>(allFields);
        auto& dataField = std::get<FieldIdx_data>(allFields);
        dataField.forceReadElemCount(numBlocksField.value());

        return Base::template readFieldsFrom<FieldIdx_data>(iter, len);
    }

    virtual bool refreshImpl() override
    {
        auto& allFields = Base::fields();
        auto& numBlocksField = std::get<FieldIdx_numConfigBlocks>(allFields);
        auto& dataField = std::get<FieldIdx_data>(allFields);
        if (numBlocksField.value() == dataField.value().size()) {
            return false;
        }

        numBlocksField.value() = dataField.value().size();
        return true;
    }

};


}  // namespace message

}  // namespace ublox

