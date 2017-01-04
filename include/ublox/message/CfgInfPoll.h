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
/// @brief Contains definition of CFG-INF (@b poll) message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/cfg.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the CFG-INF (@b poll) message fields.
/// @see CfgInfPoll
struct CfgInfPollFields
{
    /// @brief Protocol ID enumeration.
    using ProtocolId = field::cfg::ProtocolId;

    /// @brief Definition of "protocolID" field.
    using protocolID = field::cfg::protocolID;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        protocolID
    >;
};

/// @brief Definition of CFG-INF (@b poll) message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref CfgInfPollFields and for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class CfgInfPoll : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_INF>,
        comms::option::FieldsImpl<CfgInfPollFields::All>,
        comms::option::MsgType<CfgInfPoll<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_INF>,
        comms::option::FieldsImpl<CfgInfPollFields::All>,
        comms::option::MsgType<CfgInfPoll<TMsgBase> >
    > Base;
public:

#ifdef FOR_DOXYGEN_DOC_ONLY
    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_protocolID, ///< @b protocolID field, see @ref CfgInfPollFields::protocolID
        FieldIdx_numOfValues ///< number of available fields
    };

    /// @brief Access to fields bundled as a struct
    struct FieldsAsStruct
    {
        CfgInfPollFields::protocolID& protocolID; ///< @b protocolID field, see @ref CfgInfPollFields::protocolID
    };

    /// @brief Access to @b const fields bundled as a struct
    struct ConstFieldsAsStruct
    {
        const CfgInfPollFields::protocolID& protocolID; ///< @b protocolID field, see @ref CfgInfPollFields::protocolID
    };

    /// @brief Get access to fields bundled into a struct
    FieldsAsStruct fieldsAsStruct();

    /// @brief Get access to @b const fields bundled into a struct
    ConstFieldsAsStruct fieldsAsStruct() const;

#else
    COMMS_MSG_FIELDS_ACCESS(Base, protocolID);
#endif // #ifdef FOR_DOXYGEN_DOC_ONLY

    /// @brief Default constructor
    CfgInfPoll() = default;

    /// @brief Copy constructor
    CfgInfPoll(const CfgInfPoll&) = default;

    /// @brief Move constructor
    CfgInfPoll(CfgInfPoll&& other) = default;

    /// @brief Destructor
    virtual ~CfgInfPoll() = default;

    /// @brief Copy assignment
    CfgInfPoll& operator=(const CfgInfPoll&) = default;

    /// @brief Move assignment
    CfgInfPoll& operator=(CfgInfPoll&&) = default;
};


}  // namespace message

}  // namespace ublox

