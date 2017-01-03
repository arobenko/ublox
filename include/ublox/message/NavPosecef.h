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
/// @brief Contains definition of NAV-POSECEF message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/nav.h"

namespace ublox
{

namespace message
{
/// @brief Accumulates details of all the NAV-POSECEF message fields.
/// @see NavPosecef
struct NavPosecefFields
{
    /// @brief Definition of "iTOW" field.
    using iTOW = field::nav::iTOW;

    /// @brief Definition of "iTOW" field.
    using ecefX = field::nav::ecefX;

    /// @brief Definition of "iTOW" field.
    using ecefY = field::nav::ecefY;

    /// @brief Definition of "iTOW" field.
    using ecefZ = field::nav::ecefZ;

    /// @brief Definition of "iTOW" field.
    using pAcc = field::nav::pAcc;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        iTOW,
        ecefX,
        ecefY,
        ecefZ,
        pAcc
    >;
};

/// @brief Definition of NAV-POSECEF message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref NavPosecefFields and for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class NavPosecef : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_POSECEF>,
        comms::option::FieldsImpl<NavPosecefFields::All>,
        comms::option::MsgType<NavPosecef<TMsgBase> >,
        comms::option::DispatchImpl
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_POSECEF>,
        comms::option::FieldsImpl<NavPosecefFields::All>,
        comms::option::MsgType<NavPosecef<TMsgBase> >,
        comms::option::DispatchImpl
    > Base;
public:

#ifdef FOR_DOXYGEN_DOC_ONLY
    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_iTow, ///< @b iTOW field, see @ref NavPosecefFields::iTOW
        FieldIdx_ecefX, ///< @b ecefX field, see @ref NavPosecefFields::ecefX
        FieldIdx_ecefY, ///< @b ecefY field, see @ref NavPosecefFields::ecefY
        FieldIdx_ecefZ, ///< @b ecefZ field, see @ref NavPosecefFields::ecefZ
        FieldIdx_pAcc, ///< @b pAcc field, see @ref NavPosecefFields::pAcc
        FieldIdx_numOfValues ///< number of available fields
    };

    /// @brief Access to fields bundled as a struct
    struct FieldsAsStruct
    {
        NavPosecefFields::iTOW& iTOW; ///< @b iTOW field, see @ref NavPosecefFields::iTOW
        NavPosecefFields::ecefX& ecefX; ///< @b ecefX field, see @ref NavPosecefFields::ecefX
        NavPosecefFields::ecefY& ecefY; ///< @b ecefY field, see @ref NavPosecefFields::ecefY
        NavPosecefFields::ecefZ& ecefZ; ///< @b ecefZ field, see @ref NavPosecefFields::ecefZ
        NavPosecefFields::pAcc& pAcc; ///< @b pAcc field, see @ref NavPosecefFields::pAcc
    };

    /// @brief Access to @b const fields bundled as a struct
    struct ConstFieldsAsStruct
    {
        const NavPosecefFields::iTOW& iTOW; ///< @b iTOW field, see @ref NavPosecefFields::iTOW
        const NavPosecefFields::ecefX& ecefX; ///< @b ecefX field, see @ref NavPosecefFields::ecefX
        const NavPosecefFields::ecefY& ecefY; ///< @b ecefY field, see @ref NavPosecefFields::ecefY
        const NavPosecefFields::ecefZ& ecefZ; ///< @b ecefZ field, see @ref NavPosecefFields::ecefZ
        const NavPosecefFields::pAcc& pAcc; ///< @b pAcc field, see @ref NavPosecefFields::pAcc
    };

    /// @brief Get access to fields bundled into a struct
    FieldsAsStruct fieldsAsStruct();

    /// @brief Get access to @b const fields bundled into a struct
    ConstFieldsAsStruct fieldsAsStruct() const;

#else
    COMMS_MSG_FIELDS_ACCESS(Base, iTOW, ecefX, ecefY, ecefZ, pAcc);
#endif // #ifdef FOR_DOXYGEN_DOC_ONLY

    /// @brief Default constructor
    NavPosecef() = default;

    /// @brief Copy constructor
    NavPosecef(const NavPosecef&) = default;

    /// @brief Move constructor
    NavPosecef(NavPosecef&& other) = default;

    /// @brief Destructor
    virtual ~NavPosecef() = default;

    /// @brief Copy assignment
    NavPosecef& operator=(const NavPosecef&) = default;

    /// @brief Move assignment
    NavPosecef& operator=(NavPosecef&&) = default;
};


}  // namespace message

}  // namespace ublox





