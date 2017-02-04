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
/// @brief Contains definition of AID-AOP message and its fields.

#pragma once

#include <iterator>

#include "ublox/Message.h"
#include "ublox/field/aid.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the AID-AOP message fields.
/// @see AidAop
struct AidAopFields
{
    /// @brief Definition of "svid" field.
    using svid = field::aid::svid;

    /// @brief Definition of "data" field.
    /// @tparam TOpt Extra option(s)
    template <typename TOpt = comms::option::EmptyOption>
    using data =
        field::common::ListT<
            std::uint8_t,
            comms::option::SequenceFixedSize<59>,
            TOpt
        >;

    /// @brief Definition of "optional" field.
    /// @tparam TOpt Extra option(s)
    template <typename TOpt = comms::option::EmptyOption>
    using optional =
        field::common::OptionalT<
            field::common::ListT<
                std::uint8_t,
                comms::option::SequenceFixedSize<48 * 3>,
                TOpt
            >
        >;

    /// @brief All the fields bundled in std::tuple.
    /// @tparam TDataOpt Extra option(s) for @ref data field
    /// @tparam TOptionalOpt Extra option(s) for @ref optional field
    template <typename TDataOpt, typename TOptionalOpt>
    using All = std::tuple<
        svid,
        data<TDataOpt>,
        optional<TOptionalOpt>
    >;
};

/// @brief Definition of AID-AOP message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref AidAopFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
/// @tparam TDataOpt Extra option(s) for @b data field
/// @tparam TOptionalOpt Extra option(s) for @b optional field
template <
    typename TMsgBase = Message,
    typename TDataOpt = comms::option::EmptyOption,
    typename TOptionalOpt = comms::option::EmptyOption>
class AidAop : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_AID_AOP>,
        comms::option::FieldsImpl<AidAopFields::All<TDataOpt, TOptionalOpt> >,
        comms::option::MsgType<AidAop<TMsgBase, TDataOpt, TOptionalOpt> >
    >
{
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b svid for @ref AidAopFields::svid field
    ///     @li @b data for @ref AidAopFields::data field
    ///     @li @b optional for @ref AidAopFields::optional field
    COMMS_MSG_FIELDS_ACCESS(svid, data, optional);

    /// @brief Default constructor
    AidAop() = default;

    /// @brief Copy constructor
    AidAop(const AidAop&) = default;

    /// @brief Move constructor
    AidAop(AidAop&& other) = default;

    /// @brief Destructor
    virtual ~AidAop() = default;

    /// @brief Copy assignment
    AidAop& operator=(const AidAop&) = default;

    /// @brief Move assignment
    AidAop& operator=(AidAop&&) = default;
};


}  // namespace message

}  // namespace ublox





