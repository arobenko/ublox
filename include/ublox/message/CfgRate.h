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
/// @brief Contains definition of CFG-RATE message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the CFG-RATE message fields.
/// @see CfgRate
struct CfgRateFields
{
    /// @brief Value enumeration for @ref timeRef field
    enum class TimeRef : std::uint16_t
    {
        UTC, ///< UTC time
        GPS, ///< GPS time
        GLONASS, ///< Glonass time
        BeiDou, ///< BeiDou time
        Galileo, ///< Galileo time
        NumOfValues ///< number of available values
    };

    /// @brief Definition of "measRate" field.
    using measRate = field::common::U2T<field::common::Scaling_ms2s>;

    /// @brief Definition of "navRate" field.
    using navRate =
        field::common::U2T<
            comms::option::DefaultNumValue<1>,
            comms::option::ValidNumValueRange<1, 1>
        >;

    /// @brief Definition of "timeRef" field.
    using timeRef =
        field::common::EnumT<
            TimeRef,
            comms::option::ValidNumValueRange<0, (int)TimeRef::NumOfValues - 1>
        >;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        measRate,
        navRate,
        timeRef
    >;
};

/// @brief Definition of CFG-RATE message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref CfgRateFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class CfgRate : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_RATE>,
        comms::option::FieldsImpl<CfgRateFields::All>,
        comms::option::MsgType<CfgRate<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_RATE>,
        comms::option::FieldsImpl<CfgRateFields::All>,
        comms::option::MsgType<CfgRate<TMsgBase> >
    > Base;
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b measRate for @ref CfgRateFields::measRate field
    ///     @li @b navRate for @ref CfgRateFields::navRate field
    ///     @li @b timeRef for @ref CfgRateFields::timeRef field
    COMMS_MSG_FIELDS_ACCESS(measRate, navRate, timeRef);

    /// @brief Default constructor
    CfgRate() = default;

    /// @brief Copy constructor
    CfgRate(const CfgRate&) = default;

    /// @brief Move constructor
    CfgRate(CfgRate&& other) = default;

    /// @brief Destructor
    virtual ~CfgRate() = default;

    /// @brief Copy assignment
    CfgRate& operator=(const CfgRate&) = default;

    /// @brief Move assignment
    CfgRate& operator=(CfgRate&&) = default;
};


}  // namespace message

}  // namespace ublox

