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
/// @brief Contains definition of AID-AOP (<b>poll SV</b>) message and its fields.

#pragma once

#include "ublox/Message.h"

#include "ublox/field/aid.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the AID-AOP (<b>poll SV</b>) message fields.
/// @see AidAopPollSv
struct AidAopPollSvFields
{
    /// @brief Definition of "svid" field.
    using svid = field::aid::svid;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        svid
    >;
};

/// @brief Definition of AID-AOP (<b>poll SV</b>) message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref AidAopPollSvFields and for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class AidAopPollSv : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_AID_AOP>,
        comms::option::FieldsImpl<AidAopPollSvFields::All>,
        comms::option::MsgType<AidAopPollSv<TMsgBase> >,
        comms::option::DispatchImpl
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_AID_AOP>,
        comms::option::FieldsImpl<AidAopPollSvFields::All>,
        comms::option::MsgType<AidAopPollSv<TMsgBase> >,
        comms::option::DispatchImpl
    > Base;
public:

#ifdef FOR_DOXYGEN_DOC_ONLY
    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_svid, ///< svid field, see @ref AidAopPollSvFields::svid
        FieldIdx_numOfValues ///< number of available fields
    };

    /// @brief Access to fields bundled as a struct
    struct FieldsAsStruct
    {
        AidAopPollSvFields::svid& svid; ///< svid field, see @ref AidAopPollSvFields::svid
    };

    /// @brief Access to @b const fields bundled as a struct
    struct ConstFieldsAsStruct
    {
        const AidAopPollSvFields::svid& svid; ///< svid field, see @ref AidAopPollSvFields::svid
    };

    /// @brief Get access to fields bundled into a struct
    FieldsAsStruct fieldsAsStruct();

    /// @brief Get access to @b const fields bundled into a struct
    ConstFieldsAsStruct fieldsAsStruct() const;

#else
    COMMS_MSG_FIELDS_ACCESS(Base, svid);
#endif // #ifdef FOR_DOXYGEN_DOC_ONLY

    /// @brief Default constructor
    AidAopPollSv() = default;

    /// @brief Copy constructor
    AidAopPollSv(const AidAopPollSv&) = default;

    /// @brief Move constructor
    AidAopPollSv(AidAopPollSv&& other) = default;

    /// @brief Destructor
    virtual ~AidAopPollSv() = default;

    /// @brief Copy assignment
    AidAopPollSv& operator=(const AidAopPollSv&) = default;

    /// @brief Move assignment
    AidAopPollSv& operator=(AidAopPollSv&&) = default;
};

}  // namespace message

}  // namespace ublox





