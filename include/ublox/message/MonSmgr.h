//
// Copyright 2017 (C). Alex Robenko. All rights reserved.
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
/// @brief Contains definition of MON-SMGR message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the MON-SMGR message fields.
/// @see MonSmgr
struct MonSmgrFields
{
    /// @brief Definition of "version" field.
    using version =
        field::common::U1T<
            comms::option::ValidNumValueRange<0, 0>
        >;

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res3;

    /// @brief Definition of "iTOW" field.
    using iTOW = field::common::iTOW;

    /// @brief Enumeration value for @ref intOscState field.
    enum class IntOscState : std::uint8_t
    {
        Autonomous, ///< autonomous operation
        Calibration, ///< calibration ongoing
        HostSteered, /// oscillator is steered by the host,
        Idle, ///< idle state
        NumOfValues ///< number of available values
    };

    /// @brief Definition of "intOscState" field.
    using intOscState =
        field::common::EnumT<
            IntOscState,
            comms::option::ValidNumValueRange<0, (int)IntOscState::NumOfValues - 1>,
            comms::option::FixedBitLength<4>
        >;

    /// @brief Definition of bit flags in @ref intOsc field.
    struct intOscFlags : public
        field::common::X2T<
            comms::option::BitmaskReservedBits<0xfffc, 0>,
            comms::option::FixedBitLength<12>
        >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS(intOscCalib, intOscDisc);
    };

    /// @brief Definition of "intOsc" field.
    struct intOsc : public
        field::common::BitfieldT<
            std::tuple<
                intOscState,
                intOscFlags
            >
        >
    {
        /// @brief Allow access to internal fields.
        /// @details See definition of @b COMMS_FIELD_MEMBERS_ACCESS macro
        ///     related to @b comms::field::Bitfield class from COMMS library
        ///     for details.
        COMMS_FIELD_MEMBERS_ACCESS(intOscState, intOscFlags);
    };

    /// @brief Enumeration value for @ref extOscState field.
    using EntOscState = IntOscState;

    /// @brief Definition of "extOscState" field.
    using extOscState = intOscState;

    /// @brief Definition of bit flags in @ref extOsc field.
    struct extOscFlags : public
        field::common::X2T<
            comms::option::BitmaskReservedBits<0xfffc, 0>,
            comms::option::FixedBitLength<12>
        >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS(extOscCalib, extOscDisc);
    };

    /// @brief Definition of "extOsc" field.
    struct extOsc : public
        field::common::BitfieldT<
            std::tuple<
                extOscState,
                extOscFlags
            >
        >
    {
        /// @brief Allow access to internal fields.
        /// @details See definition of @b COMMS_FIELD_MEMBERS_ACCESS macro
        ///     related to @b comms::field::Bitfield class from COMMS library
        ///     for details.
        COMMS_FIELD_MEMBERS_ACCESS(extOscState, extOscFlags);
    };

    /// @brief Enumeration value for @ref discSrc field.
    enum class DiscSrc : std::uint8_t
    {
        Internal, ///< internal oscillator
        Gnss, ///< GNSS
        Extint0, ///< EXTINT0
        Extint1, ///< EXTINT1
        HostInternal, ///< internal oscillator measured by the host
        HostExternal, ///< external oscillator measured by the host
        NumOfValues
    };

    /// @brief Definition of "discSrc" field.
    using discSrc =
        field::common::EnumT<
            DiscSrc,
            comms::option::ValidNumValueRange<0, (int)DiscSrc::NumOfValues - 1>
        >;

    /// @brief Definition of "gnss" field.
    struct gnss : public
        field::common::X1T<
            comms::option::BitmaskReservedBits<0xfe, 0>
        >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS(gnssAvail);
    };

    /// @brief Definition of "extInt0" field.
    struct extInt0 : public
        field::common::X1T<
            comms::option::BitmaskReservedBits<0xf8, 0>
        >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS(extInt0Avail, extInt0Type, extInt0FeedBack);
    };

    /// @brief Definition of "extInt1" field.
    struct extInt1 : public
        field::common::X1T<
            comms::option::BitmaskReservedBits<0xf8, 0>
        >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS(extInt1Avail, extInt1Type, extInt1FeedBack);
    };

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        version,
        reserved1,
        iTOW,
        intOsc,
        extOsc,
        discSrc,
        gnss,
        extInt0,
        extInt1
    >;
};

/// @brief Definition of MON-SMGR message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref MonSmgrFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class MonSmgr : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_MON_SMGR>,
        comms::option::FieldsImpl<MonSmgrFields::All>,
        comms::option::MsgType<MonSmgr<TMsgBase> >
    >
{
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b version for @ref MonSmgrFields::version field
    ///     @li @b reserved1 for @ref MonSmgrFields::reserved1 field
    ///     @li @b iTOW for @ref MonSmgrFields::iTOW field
    ///     @li @b intOsc for @ref MonSmgrFields::intOsc field
    ///     @li @b extOsc for @ref MonSmgrFields::extOsc field
    ///     @li @b discSrc for @ref MonSmgrFields::discSrc field
    ///     @li @b gnss for @ref MonSmgrFields::gnss field
    ///     @li @b extInt0 for @ref MonSmgrFields::extInt0 field
    ///     @li @b extInt1 for @ref MonSmgrFields::extInt1 field
    COMMS_MSG_FIELDS_ACCESS(
        version,
        reserved1,
        iTOW,
        intOsc,
        extOsc,
        discSrc,
        gnss,
        extInt0,
        extInt1
    );

    /// @brief Default constructor
    MonSmgr() = default;

    /// @brief Copy constructor
    MonSmgr(const MonSmgr&) = default;

    /// @brief Move constructor
    MonSmgr(MonSmgr&& other) = default;

    /// @brief Destructor
    ~MonSmgr() = default;

    /// @brief Copy assignment
    MonSmgr& operator=(const MonSmgr&) = default;

    /// @brief Move assignment
    MonSmgr& operator=(MonSmgr&&) = default;
};

}  // namespace message

}  // namespace ublox

