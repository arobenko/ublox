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
/// @brief Contains definition of TIM-SVIN message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the TIM-SVIN message fields.
/// @see TimSvin
struct TimSvinFields
{
    /// @brief Definition of "dur" field.
    using dur = field::common::U4;

    /// @brief Definition of "meanX" field.
    using meanX = field::common::I4T<field::common::Scaling_cm2m>;

    /// @brief Definition of "meanY" field.
    using meanY = meanX;

    /// @brief Definition of "meanZ" field.
    using meanZ = meanX;

    /// @brief Definition of "meanV" field.
    using meanV = field::common::U4T<comms::option::ScalingRatio<1, 1000000L> >;

    /// @brief Definition of "obs" field.
    using obs = field::common::U4;

    /// @brief Definition of "valid" field.
    using valid = field::common::U1;

    /// @brief Definition of "active" field.
    using active = field::common::U1;

    /// @brief Definition of "reserved" field.
    using reserved = field::common::res2;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        dur,
        meanX,
        meanY,
        meanZ,
        meanV,
        obs,
        valid,
        active,
        reserved
    >;
};

/// @brief Definition of TIM-SVIN message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref TimSvinFields and for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class TimSvin : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_TIM_SVIN>,
        comms::option::FieldsImpl<TimSvinFields::All>,
        comms::option::MsgType<TimSvin<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_TIM_SVIN>,
        comms::option::FieldsImpl<TimSvinFields::All>,
        comms::option::MsgType<TimSvin<TMsgBase> >
    > Base;
public:

#ifdef FOR_DOXYGEN_DOC_ONLY
    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_dur, ///< @b dur field, see @ref TimSvinFields::dur
        FieldIdx_meanX, ///< @b meanX field, see @ref TimSvinFields::meanX
        FieldIdx_meanY, ///< @b meanY field, see @ref TimSvinFields::meanY
        FieldIdx_meanZ, ///< @b meanZ field, see @ref TimSvinFields::meanZ
        FieldIdx_meanV, ///< @b meanV field, see @ref TimSvinFields::meanV
        FieldIdx_obs, ///< @b obs field, see @ref TimSvinFields::obs
        FieldIdx_valid, ///< @b valid field, see @ref TimSvinFields::valid
        FieldIdx_active, ///< @b active field, see @ref TimSvinFields::active
        FieldIdx_reserved, ///< @b reserved field, see @ref TimSvinFields::reserved
        FieldIdx_numOfValues ///< number of available fields
    };

    /// @brief Access to fields bundled as a struct
    struct FieldsAsStruct
    {
        TimSvinFields::dur& dur; ///< @b dur field, see @ref TimSvinFields::dur
        TimSvinFields::meanX& meanX; ///< @b meanX field, see @ref TimSvinFields::meanX
        TimSvinFields::meanY& meanY; ///< @b meanY field, see @ref TimSvinFields::meanY
        TimSvinFields::meanZ& meanZ; ///< @b meanZ field, see @ref TimSvinFields::meanZ
        TimSvinFields::meanV& meanV; ///< @b meanV field, see @ref TimSvinFields::meanV
        TimSvinFields::obs& obs; ///< @b obs field, see @ref TimSvinFields::obs
        TimSvinFields::valid& valid; ///< @b valid field, see @ref TimSvinFields::valid
        TimSvinFields::active& active; ///< @b active field, see @ref TimSvinFields::active
        TimSvinFields::reserved& reserved; ///< @b reserved field, see @ref TimSvinFields::reserved
    };

    /// @brief Access to @b const fields bundled as a struct
    struct ConstFieldsAsStruct
    {
        const TimSvinFields::dur& dur; ///< @b dur field, see @ref TimSvinFields::dur
        const TimSvinFields::meanX& meanX; ///< @b meanX field, see @ref TimSvinFields::meanX
        const TimSvinFields::meanY& meanY; ///< @b meanY field, see @ref TimSvinFields::meanY
        const TimSvinFields::meanZ& meanZ; ///< @b meanZ field, see @ref TimSvinFields::meanZ
        const TimSvinFields::meanV& meanV; ///< @b meanV field, see @ref TimSvinFields::meanV
        const TimSvinFields::obs& obs; ///< @b obs field, see @ref TimSvinFields::obs
        const TimSvinFields::valid& valid; ///< @b valid field, see @ref TimSvinFields::valid
        const TimSvinFields::active& active; ///< @b active field, see @ref TimSvinFields::active
        const TimSvinFields::reserved& reserved; ///< @b reserved field, see @ref TimSvinFields::reserved
    };

    /// @brief Get access to fields bundled into a struct
    FieldsAsStruct fieldsAsStruct();

    /// @brief Get access to @b const fields bundled into a struct
    ConstFieldsAsStruct fieldsAsStruct() const;

#else
    COMMS_MSG_FIELDS_ACCESS(Base, dur, meanX, meanY, meanZ, meanV, obs, valid, active, reserved);
#endif // #ifdef FOR_DOXYGEN_DOC_ONLY

    /// @brief Default constructor
    TimSvin() = default;

    /// @brief Copy constructor
    TimSvin(const TimSvin&) = default;

    /// @brief Move constructor
    TimSvin(TimSvin&& other) = default;

    /// @brief Destructor
    virtual ~TimSvin() = default;

    /// @brief Copy assignment
    TimSvin& operator=(const TimSvin&) = default;

    /// @brief Move assignment
    TimSvin& operator=(TimSvin&&) = default;
};


}  // namespace message

}  // namespace ublox

