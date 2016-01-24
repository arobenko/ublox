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
/// @brief Contains definition of CFG-EKF message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the CFG-EKF message fields.
/// @see CfgEkf
struct CfgEkfFields
{
    /// @brief Enumerator for @ref disableEkf field
    enum class DisableEkf : std::uint8_t
    {
        Enabled, ///< Solution enabled
        Disabled, ///< Solution disabled
        NumOfValues ///< Number of values
    };

    /// @brief Bits access enumerator for @ref actionFlags bitmask field.
    enum
    {
        actionFlags_clTab = 1, ///< @b clTab bit number
        actionFlags_clCalib = 2, ///< @b clCalib bit number
        actionFlags_nomTacho = 4, ///< @b nomTacho bit number
        actionFlags_nomGyro = 5, ///< @b nomGyro bit number
        actionFlags_setTemp = 6, ///< @b setTemp bit number
        actionFlags_dir = 7, ///< @b dir bit number
        actionFlags_numOfValues ///< upper limit of available bits
    };

    /// @brief Bits access enumerator for @ref configFlags bitmask field.
    enum
    {
        configFlags_pulsesPerM, ///< @b pulsesPerM bit number
        configFlags_useSerWt, ///< @b useSerWt bit number
        configFlags_numOfValues ///< number of available bits
    };

    /// @brief Bits access enumerator for @ref inverseFlags bitmask field.
    enum
    {
        inverseFlags_invDir, ///< @b invDir bit number
        inverseFlags_invGyro, ///< @b invGyro bit number
        inverseFlags_numOfValues ///< number of available bits
    };

    /// @brief Definition of "disableEkf" field.
    using disableEkf =
        field::common::EnumT<
            DisableEkf,
            comms::option::ValidNumValueRange<0, (int)DisableEkf::NumOfValues - 1>
        >;

    /// @brief Definition of "actionFlags" field.
    using actionFlags =
        field::common::X1T<
            comms::option::BitmaskReservedBits<0x9, 0>
        >;

    /// @brief Definition of "configFlags" field.
    using configFlags =
        field::common::X1T<
            comms::option::BitmaskReservedBits<0xfc, 0>
        >;

    /// @brief Definition of "inverseFlags" field.
    using inverseFlags =
        field::common::X1T<
            comms::option::BitmaskReservedBits<0xfc, 0>
        >;

    /// @brief Definition of "reserved2" field.
    using reserved2 = field::common::res4;

    /// @brief Definition of "nomPPDist" field.
    using nomPPDist = field::common::U2;

    /// @brief Definition of "nomZero" field.
    using nomZero =
        field::common::U2T<
            comms::option::ValidNumValueRange<2000, 3000>
        >;

    /// @brief Definition of "nomSens" field.
    using nomSens =
        field::common::U1T<
            comms::option::ValidNumValueRange<20, 40>
        >;

    /// @brief Definition of "rmsTemp" field.
    using rmsTemp =
        field::common::U1T<
            comms::option::ValidNumValueRange<1, 10>,
            comms::option::ScalingRatio<1, 10>
        >;

    /// @brief Definition of "tempUpdate" field.
    using tempUpdate =
        field::common::U2T<
            comms::option::ValidNumValueRange<9, 0xffff>
        >;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        disableEkf,
        actionFlags,
        configFlags,
        inverseFlags,
        reserved2,
        nomPPDist,
        nomZero,
        nomSens,
        rmsTemp,
        tempUpdate
    >;
};

/// @brief Definition of CFG-EKF message
/// @details Inherits from
///     <a href="https://dl.dropboxusercontent.com/u/46999418/comms_champion/comms/html/classcomms_1_1MessageBase.html">comms::MessageBase</a>
///     while providing @b TMsgBase as common interface class as well as
///     @b comms::option::StaticNumIdImpl, @b comms::option::FieldsImpl, and
///     @b comms::option::DispatchImpl as options. @n
///     See @ref CfgEkfFields and for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class CfgEkf : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_EKF>,
        comms::option::FieldsImpl<CfgEkfFields::All>,
        comms::option::DispatchImpl<CfgEkf<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_EKF>,
        comms::option::FieldsImpl<CfgEkfFields::All>,
        comms::option::DispatchImpl<CfgEkf<TMsgBase> >
    > Base;
public:

    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_disableEkf, ///< @b disableEkf field, see @ref CfgEkfFields::disableEkf
        FieldIdx_actionFlags, ///< @b actionFlags field, see @ref CfgEkfFields::actionFlags
        FieldIdx_configFlags, ///< @b configFlags field, see @ref CfgEkfFields::configFlags
        FieldIdx_inverseFlags, ///< @b inverseFlags field, see @ref CfgEkfFields::inverseFlags
        FieldIdx_reserved2, ///< @b reserved2 field, see @ref CfgEkfFields::reserved2
        FieldIdx_nomPPDist, ///< @b nomPPDist field, see @ref CfgEkfFields::nomPPDist
        FieldIdx_nomZero, ///< @b nomZero field, see @ref CfgEkfFields::nomZero
        FieldIdx_nomSens, ///< @b nomSens field, see @ref CfgEkfFields::nomSens
        FieldIdx_rmsTemp, ///< @b rmsTemp field, see @ref CfgEkfFields::rmsTemp
        FieldIdx_tempUpdate, ///< @b tempUpdate field, see @ref CfgEkfFields::tempUpdate
        FieldIdx_numOfValues ///< number of available fields
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    /// @brief Default constructor
    CfgEkf() = default;

    /// @brief Copy constructor
    CfgEkf(const CfgEkf&) = default;

    /// @brief Move constructor
    CfgEkf(CfgEkf&& other) = default;

    /// @brief Destructor
    virtual ~CfgEkf() = default;

    /// @brief Copy assignment
    CfgEkf& operator=(const CfgEkf&) = default;

    /// @brief Move assignment
    CfgEkf& operator=(CfgEkf&&) = default;
};


}  // namespace message

}  // namespace ublox

