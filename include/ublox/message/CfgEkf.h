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

    /// @brief Definition of "disableEkf" field.
    using disableEkf =
        field::common::EnumT<
            DisableEkf,
            comms::option::ValidNumValueRange<0, (int)DisableEkf::NumOfValues - 1>
        >;

    /// @brief Definition of "actionFlags" field.
    struct actionFlags : public
        field::common::X1T<
            comms::option::BitmaskReservedBits<0x9, 0>
        >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS(clTab=1, clCalib=2, nomTacho=4, nomGyro=5, setTemp=6, dir=7);

        /// @brief Provide convenience access functions for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS_ACCESS macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS_ACCESS(clTab, clCalib, nomTacho, nomGyro, setTemp, dir);
    };

    /// @brief Definition of "configFlags" field.
    struct configFlags : public
        field::common::X1T<
            comms::option::BitmaskReservedBits<0xfc, 0>
        >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS_SEQ macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS_SEQ(pulsesPerM, useSerWt);
    };

    /// @brief Definition of "inverseFlags" field.
    struct inverseFlags : public
        field::common::X1T<
            comms::option::BitmaskReservedBits<0xfc, 0>
        >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS_SEQ macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS_SEQ(invDir, invGyro);
    };

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
            comms::option::ValidNumValueRange<9, 0xffff>,
            comms::option::UnitsSeconds
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
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref CfgEkfFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class CfgEkf : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_EKF>,
        comms::option::FieldsImpl<CfgEkfFields::All>,
        comms::option::MsgType<CfgEkf<TMsgBase> >
    >
{
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b disableEkf for @ref CfgEkfFields::disableEkf field
    ///     @li @b actionFlags for @ref CfgEkfFields::actionFlags field
    ///     @li @b configFlags for @ref CfgEkfFields::configFlags field
    ///     @li @b inverseFlags for @ref CfgEkfFields::inverseFlags field
    ///     @li @b reserved2 for @ref CfgEkfFields::reserved2 field
    ///     @li @b nomPPDist for @ref CfgEkfFields::nomPPDist field
    ///     @li @b nomZero for @ref CfgEkfFields::nomZero field
    ///     @li @b nomSens for @ref CfgEkfFields::nomSens field
    ///     @li @b rmsTemp for @ref CfgEkfFields::rmsTemp field
    ///     @li @b tempUpdate for @ref CfgEkfFields::tempUpdate field
    COMMS_MSG_FIELDS_ACCESS(
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
    );

    /// @brief Default constructor
    CfgEkf() = default;

    /// @brief Copy constructor
    CfgEkf(const CfgEkf&) = default;

    /// @brief Move constructor
    CfgEkf(CfgEkf&& other) = default;

    /// @brief Destructor
    ~CfgEkf() = default;

    /// @brief Copy assignment
    CfgEkf& operator=(const CfgEkf&) = default;

    /// @brief Move assignment
    CfgEkf& operator=(CfgEkf&&) = default;
};

}  // namespace message

}  // namespace ublox

