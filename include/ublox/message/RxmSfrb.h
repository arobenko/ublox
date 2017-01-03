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
/// @brief Contains definition of RXM-SFRB message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/rxm.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the RXM-SFRB message fields.
/// @see RxmSfrb
struct RxmSfrbFields
{
    /// @brief Definition of "chn" field.
    using chn = field::common::U1;

    /// @brief Definition of "svid" field.
    using svid = field::rxm::svid;

    /// @brief Definition of "dword" field.
    using dwrd =
        field::common::ListT<
            field::common::U4,
            comms::option::SequenceFixedSize<10>
        >;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        chn,
        svid,
        dwrd
    >;
};

/// @brief Definition of RXM-SFRB message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref RxmSfrbFields and for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class RxmSfrb : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_RXM_SFRB>,
        comms::option::FieldsImpl<RxmSfrbFields::All>,
        comms::option::MsgType<RxmSfrb<TMsgBase> >,
        comms::option::DispatchImpl
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_RXM_SFRB>,
        comms::option::FieldsImpl<RxmSfrbFields::All>,
        comms::option::MsgType<RxmSfrb<TMsgBase> >,
        comms::option::DispatchImpl
    > Base;
public:

#ifdef FOR_DOXYGEN_DOC_ONLY
    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_chn, ///< @b chn field, see @ref RxmSfrbFields::chn
        FieldIdx_svid, ///< @b svid field, see @ref RxmSfrbFields::svid
        FieldIdx_dwrd, ///< @b dwrd field, see @ref RxmSfrbFields::dwrd
        FieldIdx_numOfValues ///< number of available fields
    };

    /// @brief Access to fields bundled as a struct
    struct FieldsAsStruct
    {
        RxmSfrbFields::chn& chn; ///< @b chn field, see @ref RxmSfrbFields::chn
        RxmSfrbFields::svid& svid; ///< @b svid field, see @ref RxmSfrbFields::svid
        RxmSfrbFields::dwrd& dwrd; ///< @b dwrd field, see @ref RxmSfrbFields::dwrd
    };

    /// @brief Access to @b const fields bundled as a struct
    struct ConstFieldsAsStruct
    {
        const RxmSfrbFields::chn& chn; ///< @b chn field, see @ref RxmSfrbFields::chn
        const RxmSfrbFields::svid& svid; ///< @b svid field, see @ref RxmSfrbFields::svid
        const RxmSfrbFields::dwrd& dwrd; ///< @b dwrd field, see @ref RxmSfrbFields::dwrd
    };

    /// @brief Get access to fields bundled into a struct
    FieldsAsStruct fieldsAsStruct();

    /// @brief Get access to @b const fields bundled into a struct
    ConstFieldsAsStruct fieldsAsStruct() const;

#else
    COMMS_MSG_FIELDS_ACCESS(Base, chn, svid, dwrd);
#endif // #ifdef FOR_DOXYGEN_DOC_ONLY

    /// @brief Default constructor
    RxmSfrb() = default;

    /// @brief Copy constructor
    RxmSfrb(const RxmSfrb&) = default;

    /// @brief Move constructor
    RxmSfrb(RxmSfrb&& other) = default;

    /// @brief Destructor
    virtual ~RxmSfrb() = default;

    /// @brief Copy assignment
    RxmSfrb& operator=(const RxmSfrb&) = default;

    /// @brief Move assignment
    RxmSfrb& operator=(RxmSfrb&&) = default;

};


}  // namespace message

}  // namespace ublox





