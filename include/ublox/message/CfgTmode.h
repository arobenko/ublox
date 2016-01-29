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
/// @brief Contains definition of CFG-TMODE message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the CFG-TMODE message fields.
/// @see CfgTmode
struct CfgTmodeFields
{
    /// @brief Value enumeration for @ref timeMode field
    enum class TimeMode : std::uint32_t
    {
        Disabled, ///< disabled
        SurveyIn, ///< survey in
        FixedMode, ///< fixed mode
        NumOfValues ///< number of available values
    };

    /// @brief Definition of "timeMode" field.
    using timeMode =
        field::common::EnumT<
            TimeMode,
            comms::option::ValidNumValueRange<0, (int)TimeMode::NumOfValues - 1>
        >;

    /// @brief Definition of "fixedPosX" field.
    using fixedPosX = field::common::I4T<field::common::Scaling_cm2m>;

    /// @brief Definition of "fixedPosY" field.
    using fixedPosY = fixedPosX;

    /// @brief Definition of "fixedPosZ" field.
    using fixedPosZ = fixedPosX;

    /// @brief Definition of "fixedPosVar" field.
    using fixedPosVar =
        field::common::U4T<
            comms::option::ScalingRatio<1, 1000000L>
        >;

    /// @brief Definition of "svinMinDur" field.
    using svinMinDur = field::common::U4;

    /// @brief Definition of "svinVarLimit" field.
    using svinVarLimit =
        field::common::U4T<
            comms::option::ScalingRatio<1, 1000000L>
        >;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        timeMode,
        fixedPosX,
        fixedPosY,
        fixedPosZ,
        fixedPosVar,
        svinMinDur,
        svinVarLimit
    >;
};

/// @brief Definition of CFG-TMODE message
/// @details Inherits from
///     <a href="https://dl.dropboxusercontent.com/u/46999418/comms_champion/comms/html/classcomms_1_1MessageBase.html">comms::MessageBase</a>
///     while providing @b TMsgBase as common interface class as well as
///     @b comms::option::StaticNumIdImpl, @b comms::option::FieldsImpl, and
///     @b comms::option::DispatchImpl as options. @n
///     See @ref CfgTmodeFields and for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class CfgTmode : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_TMODE>,
        comms::option::FieldsImpl<CfgTmodeFields::All>,
        comms::option::DispatchImpl<CfgTmode<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_TMODE>,
        comms::option::FieldsImpl<CfgTmodeFields::All>,
        comms::option::DispatchImpl<CfgTmode<TMsgBase> >
    > Base;
public:

    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_timeMode, ///< @b timeMode field, see @ref CfgTmodeFields::timeMode
        FieldIdx_fixedPosX, ///< @b fixedPosX field, see @ref CfgTmodeFields::fixedPosX
        FieldIdx_fixedPosY, ///< @b fixedPosY field, see @ref CfgTmodeFields::fixedPosY
        FieldIdx_fixedPosZ, ///< @b fixedPosZ field, see @ref CfgTmodeFields::fixedPosZ
        FieldIdx_fixedPosVar, ///< @b fixedPosVar field, see @ref CfgTmodeFields::fixedPosVar
        FieldIdx_svinMinDur, ///< @b svinMinDur field, see @ref CfgTmodeFields::svinMinDur
        FieldIdx_svinVarLimit, ///< @b svinVarLimit field, see @ref CfgTmodeFields::svinVarLimit
        FieldIdx_numOfValues ///< number of available fields
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    /// @brief Default constructor
    CfgTmode() = default;

    /// @brief Copy constructor
    CfgTmode(const CfgTmode&) = default;

    /// @brief Move constructor
    CfgTmode(CfgTmode&& other) = default;

    /// @brief Destructor
    virtual ~CfgTmode() = default;

    /// @brief Copy assignment
    CfgTmode& operator=(const CfgTmode&) = default;

    /// @brief Move assignment
    CfgTmode& operator=(CfgTmode&&) = default;
};


}  // namespace message

}  // namespace ublox

