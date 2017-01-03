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
/// @brief Contains definition of NAV-AOPSTATUS message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/nav.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the NAV-AOPSTATUS message fields.
/// @see NavAopstatus
struct NavAopstatusFields
{
    /// @brief Bits access enumeration for @ref aopCfg bitmask field.
    enum
    {
        aopCfg_useAOP, ///< @b useAOP bit index
        aopCfg_numOfValues ///< number of available bits
    };

    /// @brief Definition of "iTOW" field.
    using iTOW = field::nav::iTOW;

    /// @brief Definition of "aopCfg" field.
    using aopCfg =
        field::common::X1T<comms::option::BitmaskReservedBits<0xfe, 0> >;

    /// @brief Definition of "status" field.
    using status = field::common::U1;

    /// @brief Definition of "reserved0" field.
    using reserved0 = field::common::res1;

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res1;

    /// @brief Definition of "availGPS" field.
    using availGPS = field::common::X4;

    /// @brief Definition of "reserved2" field.
    using reserved2 = field::common::res4;

    /// @brief Definition of "reserved3" field.
    using reserved3 = field::common::res4;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        iTOW,
        aopCfg,
        status,
        reserved0,
        reserved1,
        availGPS,
        reserved2,
        reserved3
    >;
};

/// @brief Definition of NAV-AOPSTATUS message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref NavAopstatusFields and for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class NavAopstatus : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_AOPSTATUS>,
        comms::option::FieldsImpl<NavAopstatusFields::All>,
        comms::option::MsgType<NavAopstatus<TMsgBase> >,
        comms::option::DispatchImpl
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_AOPSTATUS>,
        comms::option::FieldsImpl<NavAopstatusFields::All>,
        comms::option::MsgType<NavAopstatus<TMsgBase> >,
        comms::option::DispatchImpl
    > Base;
public:

#ifdef FOR_DOXYGEN_DOC_ONLY
    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_iTOW, ///< @b iTOW field, see @ref NavAopstatusFields::iTOW
        FieldIdx_aopCfg, ///< @b aopCfg field, see @ref NavAopstatusFields::aopCfg
        FieldIdx_status, ///< @b status field, see @ref NavAopstatusFields::status
        FieldIdx_reserved0, ///< @b reserved0 field, see @ref NavAopstatusFields::reserved0
        FieldIdx_reserved1, ///< @b reserved1 field, see @ref NavAopstatusFields::reserved1
        FieldIdx_availGPS, ///< @b availGPS field, see @ref NavAopstatusFields::availGPS
        FieldIdx_reserved2, ///< @b reserved2 field, see @ref NavAopstatusFields::reserved2
        FieldIdx_reserved3, ///< @b reserved3 field, see @ref NavAopstatusFields::reserved3
        FieldIdx_numOfValues ///< number of available fields
    };

    /// @brief Access to fields bundled as a struct
    struct FieldsAsStruct
    {
        NavAopstatusFields::iTOW& iTOW; ///< @b iTOW field, see @ref NavAopstatusFields::iTOW
        NavAopstatusFields::aopCfg& aopCfg; ///< @b aopCfg field, see @ref NavAopstatusFields::aopCfg
        NavAopstatusFields::status& status; ///< @b status field, see @ref NavAopstatusFields::status
        NavAopstatusFields::reserved0& reserved0; ///< @b reserved0 field, see @ref NavAopstatusFields::reserved0
        NavAopstatusFields::reserved1& reserved1; ///< @b reserved1 field, see @ref NavAopstatusFields::reserved1
        NavAopstatusFields::availGPS& availGPS; ///< @b availGPS field, see @ref NavAopstatusFields::availGPS
        NavAopstatusFields::reserved2& reserved2; ///< @b reserved2 field, see @ref NavAopstatusFields::reserved2
        NavAopstatusFields::reserved3& reserved3; ///< @b reserved3 field, see @ref NavAopstatusFields::reserved3
    };

    /// @brief Access to @b const fields bundled as a struct
    struct ConstFieldsAsStruct
    {
        const NavAopstatusFields::iTOW& iTOW; ///< @b iTOW field, see @ref NavAopstatusFields::iTOW
        const NavAopstatusFields::aopCfg& aopCfg; ///< @b aopCfg field, see @ref NavAopstatusFields::aopCfg
        const NavAopstatusFields::status& status; ///< @b status field, see @ref NavAopstatusFields::status
        const NavAopstatusFields::reserved0& reserved0; ///< @b reserved0 field, see @ref NavAopstatusFields::reserved0
        const NavAopstatusFields::reserved1& reserved1; ///< @b reserved1 field, see @ref NavAopstatusFields::reserved1
        const NavAopstatusFields::availGPS& availGPS; ///< @b availGPS field, see @ref NavAopstatusFields::availGPS
        const NavAopstatusFields::reserved2& reserved2; ///< @b reserved2 field, see @ref NavAopstatusFields::reserved2
        const NavAopstatusFields::reserved3& reserved3; ///< @b reserved3 field, see @ref NavAopstatusFields::reserved3
    };

    /// @brief Get access to fields bundled into a struct
    FieldsAsStruct fieldsAsStruct();

    /// @brief Get access to @b const fields bundled into a struct
    ConstFieldsAsStruct fieldsAsStruct() const;

#else
    COMMS_MSG_FIELDS_ACCESS(Base,
        iTOW,
        aopCfg,
        status,
        reserved0,
        reserved1,
        availGPS,
        reserved2,
        reserved3
    );
#endif // #ifdef FOR_DOXYGEN_DOC_ONLY

    /// @brief Default constructor
    NavAopstatus() = default;

    /// @brief Copy constructor
    NavAopstatus(const NavAopstatus&) = default;

    /// @brief Move constructor
    NavAopstatus(NavAopstatus&& other) = default;

    /// @brief Destructor
    virtual ~NavAopstatus() = default;

    /// @brief Copy assignment
    NavAopstatus& operator=(const NavAopstatus&) = default;

    /// @brief Move assignment
    NavAopstatus& operator=(NavAopstatus&&) = default;
};


}  // namespace message

}  // namespace ublox





