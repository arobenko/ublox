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


#pragma once

#include "comms/Message.h"
#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

enum
{
    MonTxbufField_errors_limit,
    MonTxbufField_errors_bits,
    MonTxbufField_errors_numOfValues
};

enum
{
    MonTxbufField_errors_bits_mem,
    MonTxbufField_errors_bits_alloc,
    MonTxbufField_errors_bits_numOfValues
};

using MonTxbufField_pending =
    field::common::ListT<
        field::common::U2,
        comms::option::SequenceFixedSize<6>
    >;
using MonTxbufField_usage =
    field::common::ListT<
        field::common::U1T<comms::option::ValidNumValueRange<0, 100> >,
        comms::option::SequenceFixedSize<6>
    >;
using MonTxbufField_peakUsage = MonTxbufField_usage;
using MonTxbufField_tUsage = field::common::U1T<comms::option::ValidNumValueRange<0, 100> >;
using MonTxbufField_tPeakUsage = MonTxbufField_tUsage;
using MonTxbufField_errors =
    comms::field::Bitfield<
        field::common::FieldBase,
        std::tuple<
            field::common::U1T<
                comms::option::ValidNumValueRange<0, 0x3f>,
                comms::option::FixedBitLength<6>
            >,
            field::common::X1T<
                comms::option::FixedBitLength<2>
            >
        >
    >;
using MonTxbufField_reserved1 = field::common::res1;

using MonTxbufFields = std::tuple<
    MonTxbufField_pending,
    MonTxbufField_usage,
    MonTxbufField_peakUsage,
    MonTxbufField_tUsage,
    MonTxbufField_tPeakUsage,
    MonTxbufField_errors,
    MonTxbufField_reserved1
>;


template <typename TMsgBase = Message>
class MonTxbuf : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_MON_TXBUF>,
        comms::option::FieldsImpl<MonTxbufFields>,
        comms::option::DispatchImpl<MonTxbuf<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_MON_TXBUF>,
        comms::option::FieldsImpl<MonTxbufFields>,
        comms::option::DispatchImpl<MonTxbuf<TMsgBase> >
    > Base;
public:

    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_pending,
        FieldIdx_usage,
        FieldIdx_peakUsage,
        FieldIdx_tUsage,
        FieldIdx_tPeakUsage,
        FieldIdx_errors,
        FieldIdx_reserved1,
        FieldIdx_numOfValues ///< number of available fields
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    /// @brief Default constructor
    MonTxbuf() = default;

    /// @brief Copy constructor
    MonTxbuf(const MonTxbuf&) = default;

    /// @brief Move constructor
    MonTxbuf(MonTxbuf&& other) = default;

    /// @brief Destructor
    virtual ~MonTxbuf() = default;

    /// @brief Copy assignment
    MonTxbuf& operator=(const MonTxbuf&) = default;

    /// @brief Move assignment
    MonTxbuf& operator=(MonTxbuf&&) = default;
};


}  // namespace message

}  // namespace ublox

