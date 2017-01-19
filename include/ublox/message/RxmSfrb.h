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
/// @brief Contains definition of RXM-SFRB message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/rxm.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the RXM-SFRB message fields.
/// @see RxmSfrb
struct RxmSfrbFields
{
    /// @brief Definition of "chn" field.
    using chn = field::common::U1;

    /// @brief Definition of "svid" field.
    using svid = field::rxm::svid;

    /// @brief Definition of "dword" field.
    using dwrd =
        field::common::ListT<
            field::common::U4,
            comms::option::SequenceFixedSize<10>
        >;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        chn,
        svid,
        dwrd
    >;
};

/// @brief Definition of RXM-SFRB message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref RxmSfrbFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class RxmSfrb : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_RXM_SFRB>,
        comms::option::FieldsImpl<RxmSfrbFields::All>,
        comms::option::MsgType<RxmSfrb<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_RXM_SFRB>,
        comms::option::FieldsImpl<RxmSfrbFields::All>,
        comms::option::MsgType<RxmSfrb<TMsgBase> >
    > Base;
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b chn for @ref RxmSfrbFields::chn field
    ///     @li @b svid for @ref RxmSfrbFields::svid field
    ///     @li @b dwrd for @ref RxmSfrbFields::dwrd field
    COMMS_MSG_FIELDS_ACCESS(Base, chn, svid, dwrd);

    /// @brief Default constructor
    RxmSfrb() = default;

    /// @brief Copy constructor
    RxmSfrb(const RxmSfrb&) = default;

    /// @brief Move constructor
    RxmSfrb(RxmSfrb&& other) = default;

    /// @brief Destructor
    virtual ~RxmSfrb() = default;

    /// @brief Copy assignment
    RxmSfrb& operator=(const RxmSfrb&) = default;

    /// @brief Move assignment
    RxmSfrb& operator=(RxmSfrb&&) = default;

};


}  // namespace message

}  // namespace ublox





