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
/// @brief Contains definition of AID-HUI message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the AID-HUI message fields.
/// @see AidHui
struct AidHuiFields
{
    /// @brief Definition of "health" field.
    using health = field::common::X4;

    /// @brief Definition of "utcA0" field.
    using utcA0 = field::common::R8;

    /// @brief Definition of "utcA1" field.
    using utcA1 = field::common::R8;

    /// @brief Definition of "utcTOW" field.
    using utcTOW = field::common::I4;

    /// @brief Definition of "utcWNT" field.
    using utcWNT = field::common::I2;

    /// @brief Definition of "utcLS" field.
    using utcLS = field::common::I2;

    /// @brief Definition of "utcWNF" field.
    using utcWNF = field::common::I2;

    /// @brief Definition of "utcDN" field.
    using utcDN = field::common::I2;

    /// @brief Definition of "utcLSF" field.
    using utcLSF = field::common::I2;

    /// @brief Definition of "utcSpare" field.
    using utcSpare = field::common::I2;

    /// @brief Definition of "klobA0" field.
    using klobA0 = field::common::R4;

    /// @brief Definition of "klobA1" field.
    using klobA1 = field::common::R4;

    /// @brief Definition of "klobA2" field.
    using klobA2 = field::common::R4;

    /// @brief Definition of "klobA3" field.
    using klobA3 = field::common::R4;

    /// @brief Definition of "klobB0" field.
    using klobB0 = field::common::R4;

    /// @brief Definition of "klobB1" field.
    using klobB1 = field::common::R4;

    /// @brief Definition of "klobB2" field.
    using klobB2 = field::common::R4;

    /// @brief Definition of "klobB3" field.
    using klobB3 = field::common::R4;

    /// @brief Definition of "flags" field.
    struct flags : public
        field::common::X4T<
            comms::option::BitmaskReservedBits<0xfffffff8, 0>
        >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS_SEQ macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS_SEQ(healthValid, utcValid, klobValid);
    };

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        health,
        utcA0,
        utcA1,
        utcTOW,
        utcWNT,
        utcLS,
        utcWNF,
        utcDN,
        utcLSF,
        utcSpare,
        klobA0,
        klobA1,
        klobA2,
        klobA3,
        klobB0,
        klobB1,
        klobB2,
        klobB3,
        flags
    >;
};

/// @brief Definition of AID-HUI message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref AidHuiFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class AidHui : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_AID_HUI>,
        comms::option::FieldsImpl<AidHuiFields::All>,
        comms::option::MsgType<AidHui<TMsgBase> >
    >
{
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b health for @ref AidHuiFields::health field
    ///     @li @b utcA0 for @ref AidHuiFields::utcA0 field
    ///     @li @b utcA1 for @ref AidHuiFields::utcA1 field
    ///     @li @b utcTOW for @ref AidHuiFields::utcTOW field
    ///     @li @b utcWNT for @ref AidHuiFields::utcWNT field
    ///     @li @b utcLS for @ref AidHuiFields::utcLS field
    ///     @li @b utcWNF for @ref AidHuiFields::utcWNF field
    ///     @li @b utcDN for @ref AidHuiFields::utcDN field
    ///     @li @b utcLSF for @ref AidHuiFields::utcLSF field
    ///     @li @b utcSpare for @ref AidHuiFields::utcSpare field
    ///     @li @b klobA0 for @ref AidHuiFields::klobA0 field
    ///     @li @b klobA1 for @ref AidHuiFields::klobA1 field
    ///     @li @b klobA2 for @ref AidHuiFields::klobA2 field
    ///     @li @b klobA3 for @ref AidHuiFields::klobA3 field
    ///     @li @b klobB0 for @ref AidHuiFields::klobB0 field
    ///     @li @b klobB1 for @ref AidHuiFields::klobB1 field
    ///     @li @b klobB2 for @ref AidHuiFields::klobB2 field
    ///     @li @b klobB3 for @ref AidHuiFields::klobB3 field
    ///     @li @b flags for @ref AidHuiFields::flags field
    COMMS_MSG_FIELDS_ACCESS(
        health,
        utcA0,
        utcA1,
        utcTOW,
        utcWNT,
        utcLS,
        utcWNF,
        utcDN,
        utcLSF,
        utcSpare,
        klobA0,
        klobA1,
        klobA2,
        klobA3,
        klobB0,
        klobB1,
        klobB2,
        klobB3,
        flags);

    /// @brief Default constructor
    AidHui() = default;

    /// @brief Copy constructor
    AidHui(const AidHui&) = default;

    /// @brief Move constructor
    AidHui(AidHui&& other) = default;

    /// @brief Destructor
    ~AidHui() = default;

    /// @brief Copy assignment
    AidHui& operator=(const AidHui&) = default;

    /// @brief Move assignment
    AidHui& operator=(AidHui&&) = default;
};


}  // namespace message

}  // namespace ublox

