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
/// @brief Contains definition of RXM-PMREQ message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the RXM-PMREQ message fields.
/// @see RxmPmreq
struct RxmPmreqFields
{
    /// @brief Bits access enumeration for bits in @b flags bitmask field
    enum
    {
        flags_backup = 1, ///< @b backup bit index
        flags_numOfValues ///< upper limit for available bits
    };

    /// @brief Definition of "duration" field.
    using duration = field::common::U4T<field::common::Scaling_ms2s>;

    /// @brief Definition of "flags" field.
    using flags =
        field::common::X4T<
            comms::option::BitmaskReservedBits<0xfffffffd, 0>
        >;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        duration,
        flags
    >;
};

/// @brief Definition of RXM-PMREQ message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref RxmPmreqFields and for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class RxmPmreq : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_RXM_PMREQ>,
        comms::option::FieldsImpl<RxmPmreqFields::All>,
        comms::option::MsgType<RxmPmreq<TMsgBase> >,
        comms::option::DispatchImpl
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_RXM_PMREQ>,
        comms::option::FieldsImpl<RxmPmreqFields::All>,
        comms::option::MsgType<RxmPmreq<TMsgBase> >,
        comms::option::DispatchImpl
    > Base;
public:

#ifdef FOR_DOXYGEN_DOC_ONLY
    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_duration, ///< @b duration field, see @ref RxmPmreqFields::duration
        FieldIdx_flags, ///< @b flags field, see @ref RxmPmreqFields::flags
        FieldIdx_numOfValues ///< number of available fields
    };

    /// @brief Access to fields bundled as a struct
    struct FieldsAsStruct
    {
        RxmPmreqFields::duration& duration; ///< duration field, see @ref RxmPmreqFields::duration
        RxmPmreqFields::flags& flags; ///< flags field, see @ref RxmPmreqFields::flags
    };

    /// @brief Access to @b const fields bundled as a struct
    struct ConstFieldsAsStruct
    {
        const RxmPmreqFields::duration& duration; ///< duration field, see @ref RxmPmreqFields::duration
        const RxmPmreqFields::flags& flags; ///< flags field, see @ref RxmPmreqFields::flags
    };

    /// @brief Get access to fields bundled into a struct
    FieldsAsStruct fieldsAsStruct();

    /// @brief Get access to @b const fields bundled into a struct
    ConstFieldsAsStruct fieldsAsStruct() const;

#else
    COMMS_MSG_FIELDS_ACCESS(Base, duration, flags);
#endif // #ifdef FOR_DOXYGEN_DOC_ONLY

    /// @brief Default constructor
    RxmPmreq() = default;

    /// @brief Copy constructor
    RxmPmreq(const RxmPmreq&) = default;

    /// @brief Move constructor
    RxmPmreq(RxmPmreq&& other) = default;

    /// @brief Destructor
    virtual ~RxmPmreq() = default;

    /// @brief Copy assignment
    RxmPmreq& operator=(const RxmPmreq&) = default;

    /// @brief Move assignment
    RxmPmreq& operator=(RxmPmreq&&) = default;
};


}  // namespace message

}  // namespace ublox





