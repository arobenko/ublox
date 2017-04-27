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
/// @brief Contains definition of MGA-INI-EOP message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the MGA-INI-EOP message fields.
/// @see MgaIniEop
struct MgaIniEopFields
{
    /// @brief Definition of "type" field.
    using type  =
    field::common::U1T<
        comms::option::ValidNumValueRange<0x30, 0x30>,
        comms::option::DefaultNumValue<0x30>,
        comms::option::FailOnInvalid<>
    >;

    /// @brief Definition of "version" field.
    using version =
        field::common::U1T<
            comms::option::ValidNumValueRange<0, 0>
        >;


    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res2;

    /// @brief Definition of "d2kRef" field.
    using d2kRef = field::common::U2T<comms::option::UnitsDays>;

    /// @brief Definition of "d2kMax" field.
    using d2kMax = field::common::U2T<comms::option::UnitsDays>;

    /// @brief Definition of "xpP0" field.
    using xpP0 = field::common::I4T<comms::option::ScalingRatio<1, 0x40000000> >;

    /// @brief Definition of "xpP1" field.
    using xpP1 = xpP0;

    /// @brief Definition of "ypP0" field.
    using ypP0 = xpP0;

    /// @brief Definition of "ypP1" field.
    using ypP1 = xpP0;

    /// @brief Definition of "dUT1" field.
    using dUT1 =
        field::common::I4T<
            comms::option::ScalingRatio<1, 0x2000000>,
            comms::option::UnitsSeconds
        >;

    /// @brief Definition of "ddUT1" field.
    using ddUT1 =
        field::common::I4T<
            comms::option::ScalingRatio<1, 0x40000000>,
            comms::option::UnitsSeconds
        >;

    /// @brief Definition of "reserved2" field.
    using reserved2 = field::common::res4;

    /// @brief Definition of "reserved3" field.
    using reserved3 = field::common::res4;

    /// @brief Definition of "reserved4" field.
    using reserved4 = field::common::res4;

    /// @brief Definition of "reserved5" field.
    using reserved5 = field::common::res4;

    /// @brief Definition of "reserved6" field.
    using reserved6 = field::common::res4;

    /// @brief Definition of "reserved7" field.
    using reserved7 = field::common::res4;

    /// @brief Definition of "reserved8" field.
    using reserved8 = field::common::res4;

    /// @brief Definition of "reserved9" field.
    using reserved9 = field::common::res4;

    /// @brief Definition of "reserved10" field.
    using reserved10 = field::common::res4;

    /// @brief Definition of "reserved11" field.
    using reserved11 = field::common::res4;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        type,
        version,
        reserved1,
        d2kRef,
        d2kMax,
        xpP0,
        xpP1,
        ypP0,
        ypP1,
        dUT1,
        ddUT1,
        reserved2,
        reserved3,
        reserved4,
        reserved5,
        reserved6,
        reserved7,
        reserved8,
        reserved9,
        reserved10,
        reserved11
    >;
};

/// @brief Definition of MGA-INI-EOP message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref MgaIniEopFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class MgaIniEop : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_MGA_INI>,
        comms::option::FieldsImpl<MgaIniEopFields::All>,
        comms::option::MsgType<MgaIniEop<TMsgBase> >
    >
{
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b type for @ref MgaIniEopFields::type field
    ///     @li @b version for @ref MgaIniEopFields::version field
    ///     @li @b reserved1 for @ref MgaIniEopFields::reserved1 field
    ///     @li @b d2kRef for @ref MgaIniEopFields::d2kRef field
    ///     @li @b d2kMax for @ref MgaIniEopFields::d2kMax field
    ///     @li @b xpP0 for @ref MgaIniEopFields::xpP0 field
    ///     @li @b xpP1 for @ref MgaIniEopFields::xpP1 field
    ///     @li @b ypP0 for @ref MgaIniEopFields::ypP0 field
    ///     @li @b ypP1 for @ref MgaIniEopFields::ypP1 field
    ///     @li @b dUT1 for @ref MgaIniEopFields::dUT1 field
    ///     @li @b ddUT1 for @ref MgaIniEopFields::ddUT1 field
    ///     @li @b reserved2 for @ref MgaIniEopFields::reserved2 field
    ///     @li @b reserved3 for @ref MgaIniEopFields::reserved3 field
    ///     @li @b reserved4 for @ref MgaIniEopFields::reserved4 field
    ///     @li @b reserved5 for @ref MgaIniEopFields::reserved5 field
    ///     @li @b reserved6 for @ref MgaIniEopFields::reserved6 field
    ///     @li @b reserved7 for @ref MgaIniEopFields::reserved7 field
    ///     @li @b reserved8 for @ref MgaIniEopFields::reserved8 field
    ///     @li @b reserved9 for @ref MgaIniEopFields::reserved9 field
    ///     @li @b reserved10 for @ref MgaIniEopFields::reserved10 field
    ///     @li @b reserved11 for @ref MgaIniEopFields::reserved11 field
    COMMS_MSG_FIELDS_ACCESS(
        type,
        version,
        reserved1,
        d2kRef,
        d2kMax,
        xpP0,
        xpP1,
        ypP0,
        ypP1,
        dUT1,
        ddUT1,
        reserved2,
        reserved3,
        reserved4,
        reserved5,
        reserved6,
        reserved7,
        reserved8,
        reserved9,
        reserved10,
        reserved11
    );

    /// @brief Default constructor
    MgaIniEop() = default;

    /// @brief Copy constructor
    MgaIniEop(const MgaIniEop&) = default;

    /// @brief Move constructor
    MgaIniEop(MgaIniEop&& other) = default;

    /// @brief Destructor
    ~MgaIniEop() = default;

    /// @brief Copy assignment
    MgaIniEop& operator=(const MgaIniEop&) = default;

    /// @brief Move assignment
    MgaIniEop& operator=(MgaIniEop&&) = default;
};

}  // namespace message

}  // namespace ublox

