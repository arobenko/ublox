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
/// @brief Contains definition of MGA-GPS-IONO message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the MGA-GPS-IONO message fields.
/// @see MgaGpsIono
struct MgaGpsIonoFields
{
    /// @brief Definition of "type" field.
    using type  =
    field::common::U1T<
        comms::option::ValidNumValueRange<6, 6>,
        comms::option::DefaultNumValue<6>,
        comms::option::FailOnInvalid
    >;

    /// @brief Definition of "version" field.
    using version =
        field::common::U1T<
            comms::option::ValidNumValueRange<0, 0>
        >;

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res2;

    /// @brief Definition of "ionoAlpha0" field.
    using ionoAlpha0 = field::common::I1;

    /// @brief Definition of "ionoAlpha1" field.
    using ionoAlpha1 = field::common::I1;

    /// @brief Definition of "ionoAlpha2" field.
    using ionoAlpha2 = field::common::I1;

    /// @brief Definition of "ionoAlpha3" field.
    using ionoAlpha3 = field::common::I1;

    /// @brief Definition of "ionoBeta0" field.
    using ionoBeta0 = field::common::I1;

    /// @brief Definition of "ionoBeta1" field.
    using ionoBeta1 = field::common::I1;

    /// @brief Definition of "ionoBeta2" field.
    using ionoBeta2 = field::common::I1;

    /// @brief Definition of "ionoBeta3" field.
    using ionoBeta3 = field::common::I1;

    /// @brief Definition of "reserved2" field.
    using reserved2 = field::common::res4;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        type,
        version,
        reserved1,
        ionoAlpha0,
        ionoAlpha1,
        ionoAlpha2,
        ionoAlpha3,
        ionoBeta0,
        ionoBeta1,
        ionoBeta2,
        ionoBeta3,
        reserved2
    >;
};

/// @brief Definition of MGA-GPS-IONO message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref MgaGpsIonoFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class MgaGpsIono : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_MGA_GPS>,
        comms::option::FieldsImpl<MgaGpsIonoFields::All>,
        comms::option::MsgType<MgaGpsIono<TMsgBase> >
    >
{
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b type for @ref MgaGpsIonoFields::type field
    ///     @li @b version for @ref MgaGpsIonoFields::version field
    ///     @li @b reserved1 for @ref MgaGpsIonoFields::reserved1 field
    ///     @li @b ionoAlpha0 for @ref MgaGpsIonoFields::ionoAlpha0 field
    ///     @li @b ionoAlpha1 for @ref MgaGpsIonoFields::ionoAlpha1 field
    ///     @li @b ionoAlpha2 for @ref MgaGpsIonoFields::ionoAlpha2 field
    ///     @li @b ionoAlpha3 for @ref MgaGpsIonoFields::ionoAlpha3 field
    ///     @li @b ionoBeta0 for @ref MgaGpsIonoFields::ionoBeta0 field
    ///     @li @b ionoBeta1 for @ref MgaGpsIonoFields::ionoBeta1 field
    ///     @li @b ionoBeta2 for @ref MgaGpsIonoFields::ionoBeta2 field
    ///     @li @b ionoBeta3 for @ref MgaGpsIonoFields::ionoBeta3 field
    ///     @li @b reserved2 for @ref MgaGpsIonoFields::reserved2 field
    COMMS_MSG_FIELDS_ACCESS(
        type,
        version,
        reserved1,
        ionoAlpha0,
        ionoAlpha1,
        ionoAlpha2,
        ionoAlpha3,
        ionoBeta0,
        ionoBeta1,
        ionoBeta2,
        ionoBeta3,
        reserved2
    );

    /// @brief Default constructor
    MgaGpsIono() = default;

    /// @brief Copy constructor
    MgaGpsIono(const MgaGpsIono&) = default;

    /// @brief Move constructor
    MgaGpsIono(MgaGpsIono&& other) = default;

    /// @brief Destructor
    virtual ~MgaGpsIono() = default;

    /// @brief Copy assignment
    MgaGpsIono& operator=(const MgaGpsIono&) = default;

    /// @brief Move assignment
    MgaGpsIono& operator=(MgaGpsIono&&) = default;
};

}  // namespace message

}  // namespace ublox

