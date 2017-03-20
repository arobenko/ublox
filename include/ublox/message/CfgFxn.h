//
// Copyright 2015 - 2017 (C). Alex Robenko. All rights reserved.
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
    /// @brief Definition of "flags" field.
    struct flags : public
        field::common::X4T<
            comms::option::BitmaskReservedBits<0xffffffe5, 0>
        >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS(sleep=1, absAlign=3, onOff);
    };

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
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref CfgFxnFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class CfgFxn : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_FXN>,
        comms::option::FieldsImpl<CfgFxnFields::All>,
        comms::option::MsgType<CfgFxn<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_FXN>,
        comms::option::FieldsImpl<CfgFxnFields::All>,
        comms::option::MsgType<CfgFxn<TMsgBase> >
    > Base;
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b flags for @ref CfgFxnFields::flags field
    ///     @li @b tReacq for @ref CfgFxnFields::tReacq field
    ///     @li @b tAcq for @ref CfgFxnFields::tAcq field
    ///     @li @b tReacqOff for @ref CfgFxnFields::tReacqOff field
    ///     @li @b tAcqOff for @ref CfgFxnFields::tAcqOff field
    ///     @li @b tOn for @ref CfgFxnFields::tOn field
    ///     @li @b tOff for @ref CfgFxnFields::tOff field
    ///     @li @b res for @ref CfgFxnFields::res field
    ///     @li @b baseTow for @ref CfgFxnFields::baseTow field
    COMMS_MSG_FIELDS_ACCESS(
        flags,
        tReacq,
        tAcq,
        tReacqOff,
        tAcqOff,
        tOn,
        tOff,
        res,
        baseTow
    );

    /// @brief Default constructor
    CfgFxn() = default;

    /// @brief Copy constructor
    CfgFxn(const CfgFxn&) = default;

    /// @brief Move constructor
    CfgFxn(CfgFxn&& other) = default;

    /// @brief Destructor
    ~CfgFxn() = default;

    /// @brief Copy assignment
    CfgFxn& operator=(const CfgFxn&) = default;

    /// @brief Move assignment
    CfgFxn& operator=(CfgFxn&&) = default;
};


}  // namespace message

}  // namespace ublox

