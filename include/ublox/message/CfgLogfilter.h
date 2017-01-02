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
    /// @brief Bits access enumeration for @ref flags bitmask field.
    enum
    {
        flags_recordEnabled, ///< @b recordEnabled bit index
        flags_psmOncePerWakupEnabled, ///< @b psmOncePerWakupEnabled bit index
        flags_applyAllFilterSettings, ///< @b applyAllFilterSettings bit index
        flags_numOfValues ///< number of available bits
    };

    /// @brief Definition of "version" field.
    using version =
        field::common::U1T<
            comms::option::DefaultNumValue<1>,
            comms::option::ValidNumValueRange<1, 1>
        >;

    /// @brief Definition of "flags" field.
    using flags =
        field::common::X1T<
            comms::option::BitmaskReservedBits<0xf8, 0>
        >;

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
///     See @ref CfgLogfilterFields and for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class CfgLogfilter : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_LOGFILTER>,
        comms::option::FieldsImpl<CfgLogfilterFields::All>,
        comms::option::MsgType<CfgLogfilter<TMsgBase> >,
        comms::option::DispatchImpl
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_LOGFILTER>,
        comms::option::FieldsImpl<CfgLogfilterFields::All>,
        comms::option::MsgType<CfgLogfilter<TMsgBase> >,
        comms::option::DispatchImpl
    > Base;
public:

#ifdef FOR_DOXYGEN_DOC_ONLY
    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_version, ///< @b version field, see @ref CfgLogfilterFields::version
        FieldIdx_flags, ///< @b flags field, see @ref CfgLogfilterFields::flags
        FieldIdx_minInterval, ///< @b minInterval field, see @ref CfgLogfilterFields::minInterval
        FieldIdx_timeThreshold, ///< @b timeThreshold field, see @ref CfgLogfilterFields::timeThreshold
        FieldIdx_speedThreshold, ///< @b speedThreshold field, see @ref CfgLogfilterFields::speedThreshold
        FieldIdx_positionThreshold, ///< @b positionThreshold field, see @ref CfgLogfilterFields::positionThreshold
        FieldIdx_numOfValues ///< number of available fields
    };

    /// @brief Access to fields bundled as a struct
    struct FieldsAsStruct
    {
        CfgLogfilterFields::version& version; ///< @b version field, see @ref CfgLogfilterFields::version
        CfgLogfilterFields::flags& flags; ///< @b flags field, see @ref CfgLogfilterFields::flags
        CfgLogfilterFields::minInterval& minInterval; ///< @b minInterval field, see @ref CfgLogfilterFields::minInterval
        CfgLogfilterFields::timeThreshold& timeThreshold; ///< @b timeThreshold field, see @ref CfgLogfilterFields::timeThreshold
        CfgLogfilterFields::speedThreshold& speedThreshold; ///< @b speedThreshold field, see @ref CfgLogfilterFields::speedThreshold
        CfgLogfilterFields::positionThreshold& positionThreshold; ///< @b positionThreshold field, see @ref CfgLogfilterFields::positionThreshold
    };

    /// @brief Access to @b const fields bundled as a struct
    struct ConstFieldsAsStruct
    {
        const CfgLogfilterFields::version& version; ///< @b version field, see @ref CfgLogfilterFields::version
        const CfgLogfilterFields::flags& flags; ///< @b flags field, see @ref CfgLogfilterFields::flags
        const CfgLogfilterFields::minInterval& minInterval; ///< @b minInterval field, see @ref CfgLogfilterFields::minInterval
        const CfgLogfilterFields::timeThreshold& timeThreshold; ///< @b timeThreshold field, see @ref CfgLogfilterFields::timeThreshold
        const CfgLogfilterFields::speedThreshold& speedThreshold; ///< @b speedThreshold field, see @ref CfgLogfilterFields::speedThreshold
        const CfgLogfilterFields::positionThreshold& positionThreshold; ///< @b positionThreshold field, see @ref CfgLogfilterFields::positionThreshold
    };

    /// @brief Get access to fields bundled into a struct
    FieldsAsStruct fieldsAsStruct();

    /// @brief Get access to @b const fields bundled into a struct
    ConstFieldsAsStruct fieldsAsStruct() const;

#else
    COMMS_MSG_FIELDS_ACCESS(Base, version, flags, minInterval, timeThreshold, speedThreshold, positionThreshold);
#endif // #ifdef FOR_DOXYGEN_DOC_ONLY

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

