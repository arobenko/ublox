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
/// @brief Contains definition of MGA-ANO message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the MGA-ANO message fields.
/// @see MgaAno
struct MgaAnoFields
{
    /// @brief Definition of "type" field.
    using type  =
    field::common::U1T<
        comms::option::ValidNumValueRange<0, 0>
    >;

    /// @brief Definition of "version" field.
    using version =
        field::common::U1T<
            comms::option::ValidNumValueRange<0, 0>
        >;

    /// @brief Definition of "svId" field.
    using svId = field::common::U1;

    /// @brief Definition of "gnssId" field.
    using gnssId = field::common::gnssId;

    /// @brief Definition of "year" field.
    using year  =
        field::common::U2T<
            comms::option::NumValueSerOffset<-2000>,
            comms::option::FixedLength<1>,
            comms::option::DefaultNumValue<2000>,
            comms::option::ValidNumValueRange<2000, 2255>
        >;

    /// @brief Definition of "month" field.
    using month  =
        field::common::U1T<
            comms::option::ValidNumValueRange<1, 12>
        >;

    /// @brief Definition of "day" field.
    using day  =
        field::common::U1T<
            comms::option::ValidNumValueRange<1, 31>
        >;

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res1;

    /// @brief Definition of "data" field as list of bytes.
    /// @tparam TOpt Extra option(s)
    template <typename TOpt = comms::option::EmptyOption>
    using data =
        field::common::ListT<
            std::uint8_t,
            comms::option::SequenceFixedSize<64>,
            TOpt
        >;


    /// @brief Definition of "reserved1" field.
    using reserved2 = field::common::res4;

    /// @brief All the fields bundled in std::tuple.
    /// @tparam TOpt Extra option(s) for @ref data field
    template <typename TOpt = comms::option::EmptyOption>
    using All = std::tuple<
        type,
        version,
        svId,
        gnssId,
        year,
        month,
        day,
        reserved1,
        data<TOpt>,
        reserved2
    >;
};

/// @brief Definition of MGA-ANO message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref MgaAnoFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
/// @tparam TDataOpt Extra option(s) for @b data field
template <typename TMsgBase = Message, typename TDataOpt = comms::option::EmptyOption>
class MgaAno : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_MGA_ANO>,
        comms::option::FieldsImpl<MgaAnoFields::All<TDataOpt> >,
        comms::option::MsgType<MgaAno<TMsgBase, TDataOpt> >
    >
{
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b type for @ref MgaAnoFields::type field
    ///     @li @b version for @ref MgaAnoFields::version field
    ///     @li @b svId for @ref MgaAnoFields::svId field
    ///     @li @b gnssId for @ref MgaAnoFields::gnssId field
    ///     @li @b year for @ref MgaAnoFields::year field
    ///     @li @b month for @ref MgaAnoFields::msgPayloadStart field
    ///     @li @b day for @ref MgaAnoFields::day field
    ///     @li @b reserved1 for @ref MgaAnoFields::reserved1 field
    ///     @li @b data for @ref MgaAnoFields::data field
    ///     @li @b reserved2 for @ref MgaAnoFields::reserved2 field
    COMMS_MSG_FIELDS_ACCESS(
        type,
        version,
        svId,
        gnssId,
        year,
        month,
        day,
        reserved1,
        data,
        reserved2
    );

    /// @brief Default constructor
    MgaAno() = default;

    /// @brief Copy constructor
    MgaAno(const MgaAno&) = default;

    /// @brief Move constructor
    MgaAno(MgaAno&& other) = default;

    /// @brief Destructor
    virtual ~MgaAno() = default;

    /// @brief Copy assignment
    MgaAno& operator=(const MgaAno&) = default;

    /// @brief Move assignment
    MgaAno& operator=(MgaAno&&) = default;
};

}  // namespace message

}  // namespace ublox

