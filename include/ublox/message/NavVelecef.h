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
/// @brief Contains definition of NAV-VELECEF message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/nav.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the NAV-VELECEF message fields.
/// @see NavVelecef
struct NavVelecefFields
{
    /// @brief Definition of "iTOW" field.
    using iTOW = field::nav::iTOW;

    /// @brief Definition of "ecefVX" field.
    using ecefVX = field::nav::ecefVX;

    /// @brief Definition of "ecefVY" field.
    using ecefVY = field::nav::ecefVY;

    /// @brief Definition of "ecefVZ" field.
    using ecefVZ = field::nav::ecefVZ;

    /// @brief Definition of "sAcc" field.
    using sAcc = field::nav::sAcc;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        iTOW,
        ecefVX,
        ecefVY,
        ecefVZ,
        sAcc
    >;
};

/// @brief Definition of NAV-VELECEF message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref NavVelecefFields and for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class NavVelecef : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_VELECEF>,
        comms::option::FieldsImpl<NavVelecefFields::All>,
        comms::option::MsgType<NavVelecef<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_VELECEF>,
        comms::option::FieldsImpl<NavVelecefFields::All>,
        comms::option::MsgType<NavVelecef<TMsgBase> >
    > Base;
public:

#ifdef FOR_DOXYGEN_DOC_ONLY

    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_iTOW, ///< @b iTOW field, see @ref NavVelecefFields::iTOW
        FieldIdx_ecefVX, ///< @b ecefVX field, see @ref NavVelecefFields::ecefVX
        FieldIdx_ecefVY, ///< @b ecefVY field, see @ref NavVelecefFields::ecefVY
        FieldIdx_ecefVZ, ///< @b ecefVZ field, see @ref NavVelecefFields::ecefVZ
        FieldIdx_sAcc, ///< @b sAcc field, see @ref NavVelecefFields::sAcc
        FieldIdx_numOfValues ///< number of available fields
    };


    /// @brief Access to fields bundled as a struct
    struct FieldsAsStruct
    {
        NavVelecefFields::iTOW& iTOW; ///< @b iTOW field, see @ref NavVelecefFields::iTOW
        NavVelecefFields::ecefVX& ecefVX; ///< @b ecefVX field, see @ref NavVelecefFields::ecefVX
        NavVelecefFields::ecefVY& ecefVY; ///< @b ecefVY field, see @ref NavVelecefFields::ecefVY
        NavVelecefFields::ecefVZ& ecefVZ; ///< @b ecefVZ field, see @ref NavVelecefFields::ecefVZ
        NavVelecefFields::sAcc& sAcc; ///< @b sAcc field, see @ref NavVelecefFields::sAcc
    };

    /// @brief Access to @b const fields bundled as a struct
    struct ConstFieldsAsStruct
    {
        const NavVelecefFields::iTOW& iTOW; ///< @b iTOW field, see @ref NavVelecefFields::iTOW
        const NavVelecefFields::ecefVX& ecefVX; ///< @b ecefVX field, see @ref NavVelecefFields::ecefVX
        const NavVelecefFields::ecefVY& ecefVY; ///< @b ecefVY field, see @ref NavVelecefFields::ecefVY
        const NavVelecefFields::ecefVZ& ecefVZ; ///< @b ecefVZ field, see @ref NavVelecefFields::ecefVZ
        const NavVelecefFields::sAcc& sAcc; ///< @b sAcc field, see @ref NavVelecefFields::sAcc
    };

    /// @brief Get access to fields bundled into a struct
    FieldsAsStruct fieldsAsStruct();

    /// @brief Get access to @b const fields bundled into a struct
    ConstFieldsAsStruct fieldsAsStruct() const;

#else
    COMMS_MSG_FIELDS_ACCESS(Base, iTOW, ecevVX, ecefVY, ecefVZ, sAcc);
#endif // #ifdef FOR_DOXYGEN_DOC_ONLY

    /// @brief Default constructor
    NavVelecef() = default;

    /// @brief Copy constructor
    NavVelecef(const NavVelecef&) = default;

    /// @brief Move constructor
    NavVelecef(NavVelecef&& other) = default;

    /// @brief Destructor
    virtual ~NavVelecef() = default;

    /// @brief Copy assignment
    NavVelecef& operator=(const NavVelecef&) = default;

    /// @brief Move assignment
    NavVelecef& operator=(NavVelecef&&) = default;
};


}  // namespace message

}  // namespace ublox





