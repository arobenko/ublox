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
/// @brief Contains definition of CFG-LOGFILTER message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the CFG-LOGFILTER message fields.
/// @see CfgLogfilter
struct CfgLogfilterFields
{
    /// @brief Definition of "version" field.
    using version =
        field::common::U1T<
            comms::option::DefaultNumValue<1>,
            comms::option::ValidNumValueRange<1, 1>
        >;

    /// @brief Definition of "flags" field.
    struct flags : public
        field::common::X1T<
            comms::option::BitmaskReservedBits<0xf8, 0>
        >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS(recordEnabled, psmOncePerWakupEnabled, applyAllFilterSettings);
    };

    /// @brief Definition of "minInterval" field.
    using minInterval = field::common::U2;

    /// @brief Definition of "timeThreshold" field.
    using timeThreshold = field::common::U2;

    /// @brief Definition of "speedThreshold" field.
    using speedThreshold = field::common::U2;

    /// @brief Definition of "positionThreshold" field.
    using positionThreshold = field::common::U4;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        version,
        flags,
        minInterval,
        timeThreshold,
        speedThreshold,
        positionThreshold
    >;
};

/// @brief Definition of CFG-LOGFILTER message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref CfgLogfilterFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class CfgLogfilter : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_LOGFILTER>,
        comms::option::FieldsImpl<CfgLogfilterFields::All>,
        comms::option::MsgType<CfgLogfilter<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_LOGFILTER>,
        comms::option::FieldsImpl<CfgLogfilterFields::All>,
        comms::option::MsgType<CfgLogfilter<TMsgBase> >
    > Base;
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b version for @ref CfgLogfilterFields::version field
    ///     @li @b flags for @ref CfgLogfilterFields::flags field
    ///     @li @b minInterval for @ref CfgLogfilterFields::minInterval field
    ///     @li @b timeThreshold for @ref CfgLogfilterFields::timeThreshold field
    ///     @li @b speedThreshold for @ref CfgLogfilterFields::speedThreshold field
    ///     @li @b positionThreshold for @ref CfgLogfilterFields::positionThreshold field
    COMMS_MSG_FIELDS_ACCESS(version, flags, minInterval, timeThreshold, speedThreshold, positionThreshold);

    /// @brief Default constructor
    CfgLogfilter() = default;

    /// @brief Copy constructor
    CfgLogfilter(const CfgLogfilter&) = default;

    /// @brief Move constructor
    CfgLogfilter(CfgLogfilter&& other) = default;

    /// @brief Destructor
    virtual ~CfgLogfilter() = default;

    /// @brief Copy assignment
    CfgLogfilter& operator=(const CfgLogfilter&) = default;

    /// @brief Move assignment
    CfgLogfilter& operator=(CfgLogfilter&&) = default;
};


}  // namespace message

}  // namespace ublox

