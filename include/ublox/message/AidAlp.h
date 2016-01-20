//
// Copyright 2015 (C). Alex Robenko. All rights reserved.
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
/// @brief Contains definition of AID-ALP message and its fields.

#pragma once

#include <iterator>

#include "comms/Message.h"
#include "ublox/Message.h"

#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the AID-ALP message fields.
/// @see AidAlp
struct AidAlpFields
{
    /// @brief Definition of "predTow" field.
    using predTow = field::common::U4;

    /// @brief Definition of "predDur" field.
    using predDur = field::common::U4;

    /// @brief Definition of "age" field.
    using age = field::common::I4;

    /// @brief Definition of "predWno" field.
    using predWno = field::common::U2;

    /// @brief Definition of "almWno" field.
    using almWno = field::common::U2;

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res4;

    /// @brief Definition of "svs" field.
    using svs = field::common::U1;

    /// @brief Definition of "reserved2" field.
    using reserved2 = field::common::res1;

    /// @brief Definition of "reserved3" field.
    using reserved3 = field::common::res2;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        predTow,
        predDur,
        age,
        predWno,
        almWno,
        reserved1,
        svs,
        reserved2,
        reserved3
    >;

};

/// @brief Definition of AID-ALP message
/// @details Inherits from
///     <a href="https://dl.dropboxusercontent.com/u/46999418/comms_champion/comms/html/classcomms_1_1MessageBase.html">comms::MessageBase</a>
///     while providing @b TMsgBase as common interface class as well as
///     @b comms::option::StaticNumIdImpl, @b comms::option::FieldsImpl, and
///     @b comms::option::DispatchImpl as options. @n
///     See @ref AidAlpFields and for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class AidAlp : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_AID_ALP>,
        comms::option::FieldsImpl<AidAlpFields::All>,
        comms::option::DispatchImpl<AidAlp<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_AID_ALP>,
        comms::option::FieldsImpl<AidAlpFields::All>,
        comms::option::DispatchImpl<AidAlp<TMsgBase> >
    > Base;
public:

    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_predTow, ///< predTow field, see @ref AidAlpFields::predTow
        FieldIdx_predDur, ///< predDur field, see @ref AidAlpFields::predDur
        FieldIdx_age, ///< age field, see @ref AidAlpFields::age
        FieldIdx_predWno, ///< predWno field, see @ref AidAlpFields::predWno
        FieldIdx_almWno, ///< almWno field, see @ref AidAlpFields::almWno
        FieldIdx_reserved1, ///< reserved1 field, see @ref AidAlpFields::reserved1
        FieldIdx_svs, ///< svs field, see @ref AidAlpFields::svs
        FieldIdx_reserved2, ///< reserved2 field, see @ref AidAlpFields::reserved2
        FieldIdx_reserved3, ///< reserved3 field, see @ref AidAlpFields::reserved3
        FieldIdx_numOfValues ///< number of available fields
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    /// @brief Default constructor
    AidAlp() = default;

    /// @brief Copy constructor
    AidAlp(const AidAlp&) = default;

    /// @brief Move constructor
    AidAlp(AidAlp&& other) = default;

    /// @brief Destructor
    virtual ~AidAlp() = default;

    /// @brief Copy assignment
    AidAlp& operator=(const AidAlp&) = default;

    /// @brief Move assignment
    AidAlp& operator=(AidAlp&&) = default;
};


}  // namespace message

}  // namespace ublox





