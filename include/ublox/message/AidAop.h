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
/// @brief Contains definition of AID-AOP message and its fields.

#pragma once

#include <iterator>

#include "ublox/Message.h"
#include "ublox/field/aid.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the AID-AOP message fields.
/// @see AidAop
struct AidAopFields
{
    /// @brief Definition of "svid" field.
    using svid = field::aid::svid;

    /// @brief Definition of "data" field.
    using data =
        field::common::ListT<
            std::uint8_t,
            comms::option::SequenceFixedSize<59>
        >;

    /// @brief Definition of "optional" field.
    using optional =
        field::common::OptionalT<
            field::common::ListT<
                std::uint8_t,
                comms::option::SequenceFixedSize<48 * 3>
            >
        >;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        svid,
        data,
        optional
    >;
};

/// @brief Definition of AID-AOP message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref AidAopFields and for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class AidAop : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_AID_AOP>,
        comms::option::FieldsImpl<AidAopFields::All>,
        comms::option::MsgType<AidAop<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_AID_AOP>,
        comms::option::FieldsImpl<AidAopFields::All>,
        comms::option::MsgType<AidAop<TMsgBase> >
    > Base;
public:

#ifdef FOR_DOXYGEN_DOC_ONLY
    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_svid, ///< svid field, see @ref AidAopFields::svid
        FieldIdx_data, ///< data field, see @ref AidAopFields::data
        FieldIdx_optional, ///< optional field, see @ref AidAopFields::optional
        FieldIdx_numOfValues ///< number of available fields
    };

    /// @brief Access to fields bundled as a struct
    struct FieldsAsStruct
    {
        AidAopFields::svid& svid; ///< svid field, see @ref AidAopFields::svid
        AidAopFields::data& data; ///< data field, see @ref AidAopFields::data
        AidAopFields::optional& optional; ///< optional field, see @ref AidAopFields::optional
    };

    /// @brief Access to @b const fields bundled as a struct
    struct ConstFieldsAsStruct
    {
        const AidAopFields::svid& svid; ///< svid field, see @ref AidAopFields::svid
        const AidAopFields::data& data; ///< data field, see @ref AidAopFields::data
        const AidAopFields::optional& optional; ///< optional field, see @ref AidAopFields::optional
    };

    /// @brief Get access to fields bundled into a struct
    FieldsAsStruct fieldsAsStruct();

    /// @brief Get access to @b const fields bundled into a struct
    ConstFieldsAsStruct fieldsAsStruct() const;

#else
    COMMS_MSG_FIELDS_ACCESS(Base, svid, data, optional);
#endif // #ifdef FOR_DOXYGEN_DOC_ONLY

    /// @brief Default constructor
    AidAop() = default;

    /// @brief Copy constructor
    AidAop(const AidAop&) = default;

    /// @brief Move constructor
    AidAop(AidAop&& other) = default;

    /// @brief Destructor
    virtual ~AidAop() = default;

    /// @brief Copy assignment
    AidAop& operator=(const AidAop&) = default;

    /// @brief Move assignment
    AidAop& operator=(AidAop&&) = default;
};


}  // namespace message

}  // namespace ublox





