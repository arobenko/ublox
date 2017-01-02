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
/// @brief Contains definition of CFG-DAT (<b>set standard</b>) message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/cfg.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the CFG-DAT (<b>set standard</b>) message fields.
/// @see CfgDatStandard
struct CfgDatStandardFields
{
    /// @brief Definition of "datumNum" field.
    using datumNum = field::cfg::datumNum;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        datumNum
    >;
};

/// @brief Definition of CFG-DAT (<b>set standard</b>) message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref CfgDatStandardFields and for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class CfgDatStandard : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_DAT>,
        comms::option::FieldsImpl<CfgDatStandardFields::All>,
        comms::option::MsgType<CfgDatStandard<TMsgBase> >,
        comms::option::DispatchImpl
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_DAT>,
        comms::option::FieldsImpl<CfgDatStandardFields::All>,
        comms::option::MsgType<CfgDatStandard<TMsgBase> >,
        comms::option::DispatchImpl
    > Base;
public:

#ifdef FOR_DOXYGEN_DOC_ONLY
    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_datumNum, ///< @b datumNum field, see @ref CfgDatStandardFields::datumNum
        FieldIdx_numOfValues ///< number of available fields
    };

    /// @brief Access to fields bundled as a struct
    struct FieldsAsStruct
    {
        CfgDatStandardFields::datumNum& datumNum; ///< @b datumNum field, see @ref CfgDatStandardFields::datumNum
    };

    /// @brief Access to @b const fields bundled as a struct
    struct ConstFieldsAsStruct
    {
        const CfgDatStandardFields::datumNum& datumNum; ///< @b datumNum field, see @ref CfgDatStandardFields::datumNum
    };

    /// @brief Get access to fields bundled into a struct
    FieldsAsStruct fieldsAsStruct();

    /// @brief Get access to @b const fields bundled into a struct
    ConstFieldsAsStruct fieldsAsStruct() const;

#else
    COMMS_MSG_FIELDS_ACCESS(Base, datumNum);
#endif // #ifdef FOR_DOXYGEN_DOC_ONLY

    /// @brief Default constructor
    CfgDatStandard() = default;

    /// @brief Copy constructor
    CfgDatStandard(const CfgDatStandard&) = default;

    /// @brief Move constructor
    CfgDatStandard(CfgDatStandard&& other) = default;

    /// @brief Destructor
    virtual ~CfgDatStandard() = default;

    /// @brief Copy assignment
    CfgDatStandard& operator=(const CfgDatStandard&) = default;

    /// @brief Move assignment
    CfgDatStandard& operator=(CfgDatStandard&&) = default;
};


}  // namespace message

}  // namespace ublox

