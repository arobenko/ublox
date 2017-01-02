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
/// @brief Contains definition of CFG-RINV message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the CFG-RINV message fields.
/// @see CfgRinv
struct CfgRinvFields
{
    /// @brief Bits access enumeration for @ref flags bitmask field.
    enum
    {
        data_dump, ///< @b dump bit index
        data_binary, ///< @b binary bit index
        data_numOfValues ///< number of available bits
    };

    /// @brief Definition of "flags" field.
    using flags =
        field::common::X1T<
            comms::option::BitmaskReservedBits<0xfc, 0>
        >;

    /// @brief Definition of "data" field.
    using data =
        field::common::ListT<std::uint8_t>;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        flags,
        data
    >;
};

/// @brief Definition of CFG-RINV message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref CfgRinvFields and for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class CfgRinv : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_RINV>,
        comms::option::FieldsImpl<CfgRinvFields::All>,
        comms::option::MsgType<CfgRinv<TMsgBase> >,
        comms::option::DispatchImpl
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_RINV>,
        comms::option::FieldsImpl<CfgRinvFields::All>,
        comms::option::MsgType<CfgRinv<TMsgBase> >,
        comms::option::DispatchImpl
    > Base;
public:

#ifdef FOR_DOXYGEN_DOC_ONLY
    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_flags, ///< @b flags field, see @ref CfgRinvFields::flags
        FieldIdx_data, ///< @b data field, see @ref CfgRinvFields::data
        FieldIdx_numOfValues ///< number of available fields
    };

    /// @brief Access to fields bundled as a struct
    struct FieldsAsStruct
    {
        CfgRinvFields::flags& flags; ///< @b flags field, see @ref CfgRinvFields::flags
        CfgRinvFields::data& data; ///< @b data field, see @ref CfgRinvFields::data
    };

    /// @brief Access to @b const fields bundled as a struct
    struct ConstFieldsAsStruct
    {
        const CfgRinvFields::flags& flags; ///< @b flags field, see @ref CfgRinvFields::flags
        const CfgRinvFields::data& data; ///< @b data field, see @ref CfgRinvFields::data
    };

    /// @brief Get access to fields bundled into a struct
    FieldsAsStruct fieldsAsStruct();

    /// @brief Get access to @b const fields bundled into a struct
    ConstFieldsAsStruct fieldsAsStruct() const;

#else
    COMMS_MSG_FIELDS_ACCESS(Base, flags, data);
#endif // #ifdef FOR_DOXYGEN_DOC_ONLY

    /// @brief Default constructor
    CfgRinv() = default;

    /// @brief Copy constructor
    CfgRinv(const CfgRinv&) = default;

    /// @brief Move constructor
    CfgRinv(CfgRinv&& other) = default;

    /// @brief Destructor
    virtual ~CfgRinv() = default;

    /// @brief Copy assignment
    CfgRinv& operator=(const CfgRinv&) = default;

    /// @brief Move assignment
    CfgRinv& operator=(CfgRinv&&) = default;
};


}  // namespace message

}  // namespace ublox

