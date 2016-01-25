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
/// @brief Contains definition of CFG-FXN message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the CFG-FXN message fields.
/// @see CfgFxn
struct CfgFxnFields
{
    /// @brief Bits access enumerator for @ref flags bitmask field.
    enum
    {
        flags_sleep = 1, ///< @b sleep bit number
        flags_absAlign = 3, ///< @b absAlign bit number
        flags_onOff, ///< @b onOff bit number
        flags_numOfValues ///< upper limit of available bits
    };

    /// @brief Definition of "flags" field.
    using flags =
        field::common::X4T<
            comms::option::BitmaskReservedBits<0xffffffe5, 0>
        >;

    /// @brief Definition of "tReacq" field.
    using tReacq = field::common::U4T<field::common::Scaling_ms2s>;

    /// @brief Definition of "tAcq" field.
    using tAcq = field::common::U4T<field::common::Scaling_ms2s>;

    /// @brief Definition of "tReacqOff" field.
    using tReacqOff = field::common::U4T<field::common::Scaling_ms2s>;

    /// @brief Definition of "tAcqOff" field.
    using tAcqOff = field::common::U4T<field::common::Scaling_ms2s>;

    /// @brief Definition of "tOn" field.
    using tOn = field::common::U4T<field::common::Scaling_ms2s>;

    /// @brief Definition of "tOff" field.
    using tOff = field::common::U4T<field::common::Scaling_ms2s>;

    /// @brief Definition of "res" field.
    using res = field::common::res4;

    /// @brief Definition of "baseTow" field.
    using baseTow = field::common::U4T<field::common::Scaling_ms2s>;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        flags,
        tReacq,
        tAcq,
        tReacqOff,
        tAcqOff,
        tOn,
        tOff,
        res,
        baseTow
    >;
};

/// @brief Definition of CFG-FXN message
/// @details Inherits from
///     <a href="https://dl.dropboxusercontent.com/u/46999418/comms_champion/comms/html/classcomms_1_1MessageBase.html">comms::MessageBase</a>
///     while providing @b TMsgBase as common interface class as well as
///     @b comms::option::StaticNumIdImpl, @b comms::option::FieldsImpl, and
///     @b comms::option::DispatchImpl as options. @n
///     See @ref CfgFxnFields and for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class CfgFxn : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_FXN>,
        comms::option::FieldsImpl<CfgFxnFields::All>,
        comms::option::DispatchImpl<CfgFxn<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_FXN>,
        comms::option::FieldsImpl<CfgFxnFields::All>,
        comms::option::DispatchImpl<CfgFxn<TMsgBase> >
    > Base;
public:

    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_flags, ///< @b flags field, see @ref CfgFxnFields::flags
        FieldIdx_tReacq, ///< @b tReacq field, see @ref CfgFxnFields::tReacq
        FieldIdx_tAcq, ///< @b tAcq field, see @ref CfgFxnFields::tAcq
        FieldIdx_tReacqOff, ///< @b tReacqOff field, see @ref CfgFxnFields::tReacqOff
        FieldIdx_tAcqOff, ///< @b tAcqOff field, see @ref CfgFxnFields::tAcqOff
        FieldIdx_tOn, ///< @b tOn field, see @ref CfgFxnFields::tOn
        FieldIdx_tOff, ///< @b tOff field, see @ref CfgFxnFields::tOff
        FieldIdx_res, ///< @b res field, see @ref CfgFxnFields::res
        FieldIdx_baseTow, ///< @b baseTow field, see @ref CfgFxnFields::baseTow
        FieldIdx_numOfValues ///< number of available fields
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    /// @brief Default constructor
    CfgFxn() = default;

    /// @brief Copy constructor
    CfgFxn(const CfgFxn&) = default;

    /// @brief Move constructor
    CfgFxn(CfgFxn&& other) = default;

    /// @brief Destructor
    virtual ~CfgFxn() = default;

    /// @brief Copy assignment
    CfgFxn& operator=(const CfgFxn&) = default;

    /// @brief Move assignment
    CfgFxn& operator=(CfgFxn&&) = default;
};


}  // namespace message

}  // namespace ublox

