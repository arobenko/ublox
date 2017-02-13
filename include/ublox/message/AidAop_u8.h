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
#include <tuple>

#include "ublox/Message.h"
#include "ublox/field/aid.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the AID-AOP message fields.
/// @see AidAop_u8
struct AidAopFields_u8
{
    /// @brief Definition of "gnssId" field.
    using gnssId = field::common::gnssId;

    /// @brief Definition of "svid" field.
    using svid = field::aid::svid;

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res2;

    /// @brief Definition of "data" field.
    /// @tparam TOpt Extra option(s)
    template <typename TOpt = comms::option::EmptyOption>
    using data =
        field::common::ListT<
            std::uint8_t,
            comms::option::SequenceFixedSize<64>,
            TOpt
        >;

    /// @brief All the fields bundled in std::tuple.
    /// @tparam TDataOpt Extra option(s) for @ref data field
    template <typename TDataOpt>
    using All = std::tuple<
        gnssId,
        svid,
        reserved1,
        data<TDataOpt>
    >;
};

/// @brief Definition of AID-AOP (@b ublox-8) message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref AidAopFields_u8 and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
/// @tparam TDataOpt Extra option(s) for @b data field
template <
    typename TMsgBase = Message,
    typename TDataOpt = comms::option::EmptyOption>
class AidAop_u8 : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_AID_AOP>,
        comms::option::FieldsImpl<AidAopFields_u8::All<TDataOpt> >,
        comms::option::MsgType<AidAop_u8<TMsgBase, TDataOpt> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_AID_AOP>,
        comms::option::FieldsImpl<AidAopFields_u8::All<TDataOpt> >,
        comms::option::MsgType<AidAop_u8<TMsgBase, TDataOpt> >
    > Base;
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b gnssId for @ref AidAopFields_u8::gnssId field
    ///     @li @b svid for @ref AidAopFields_u8::svid field
    ///     @li @b reserved1 for @ref AidAopFields_u8::reserved1 field
    ///     @li @b data for @ref AidAopFields_u8::data field
    COMMS_MSG_FIELDS_ACCESS(gnssId, svid, reserved1, data);

    /// @brief Default constructor
    AidAop_u8() = default;

    /// @brief Copy constructor
    AidAop_u8(const AidAop_u8&) = default;

    /// @brief Move constructor
    AidAop_u8(AidAop_u8&& other) = default;

    /// @brief Destructor
    virtual ~AidAop_u8() = default;

    /// @brief Copy assignment
    AidAop_u8& operator=(const AidAop_u8&) = default;

    /// @brief Move assignment
    AidAop_u8& operator=(AidAop_u8&&) = default;

    /// @brief Provides custom read functionality.
    /// @details Verifies the data length prior to invoking default read of the fields
    template <typename TIter>
    comms::ErrorStatus doRead(TIter& iter, std::size_t len)
    {
        if (len != Base::doLength()) {
            return comms::ErrorStatus::InvalidMsgData;
        }

        return Base::doRead(iter, len);
    }
};


}  // namespace message

}  // namespace ublox





