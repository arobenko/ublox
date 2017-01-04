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
/// @brief Contains definition of MON-VER message and its fields.
#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the MON-VER message fields.
/// @see MonVer
struct MonVerFields
{
    /// @brief Definition of "pullL" field.
    using swVersion = field::common::ZString<30>;

    /// @brief Definition of "pullL" field.
    using hwVersion = field::common::ZString<10>;

    /// @brief Definition of "pullL" field.
    using extensions =
        field::common::ListT<
            field::common::ZString<30>
        >;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        swVersion,
        hwVersion,
        extensions
    >;
};

/// @brief Definition of MON-VER message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref MonVerFields and for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class MonVer : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_MON_VER>,
        comms::option::FieldsImpl<MonVerFields::All>,
        comms::option::MsgType<MonVer<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_MON_VER>,
        comms::option::FieldsImpl<MonVerFields::All>,
        comms::option::MsgType<MonVer<TMsgBase> >
    > Base;
public:

#ifdef FOR_DOXYGEN_DOC_ONLY
    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_swVersion, ///< @b swVersion field, see @ref MonVerFields::swVersion
        FieldIdx_hwVersion, ///< @b hwVersion field, see @ref MonVerFields::hwVersion
        FieldIdx_extensions, ///< @b extensions field, see @ref MonVerFields::extensions
        FieldIdx_numOfValues ///< number of available fields
    };

    /// @brief Access to fields bundled as a struct
    struct FieldsAsStruct
    {
        MonVerFields::swVersion& swVersion; ///< @b swVersion field, see @ref MonVerFields::swVersion
        MonVerFields::hwVersion& hwVersion; ///< @b hwVersion field, see @ref MonVerFields::hwVersion
        MonVerFields::extensions& extensions; ///< @b extensions field, see @ref MonVerFields::extensions
    };

    /// @brief Access to @b const fields bundled as a struct
    struct ConstFieldsAsStruct
    {
        const MonVerFields::swVersion& swVersion; ///< @b swVersion field, see @ref MonVerFields::swVersion
        const MonVerFields::hwVersion& hwVersion; ///< @b hwVersion field, see @ref MonVerFields::hwVersion
        const MonVerFields::extensions& extensions; ///< @b extensions field, see @ref MonVerFields::extensions
    };

    /// @brief Get access to fields bundled into a struct
    FieldsAsStruct fieldsAsStruct();

    /// @brief Get access to @b const fields bundled into a struct
    ConstFieldsAsStruct fieldsAsStruct() const;

#else
    COMMS_MSG_FIELDS_ACCESS(Base, svid, week, dwrd);
#endif // #ifdef FOR_DOXYGEN_DOC_ONLY

    /// @brief Default constructor
    MonVer() = default;

    /// @brief Copy constructor
    MonVer(const MonVer&) = default;

    /// @brief Move constructor
    MonVer(MonVer&& other) = default;

    /// @brief Destructor
    virtual ~MonVer() = default;

    /// @brief Copy assignment
    MonVer& operator=(const MonVer&) = default;

    /// @brief Move assignment
    MonVer& operator=(MonVer&&) = default;
};


}  // namespace message

}  // namespace ublox

