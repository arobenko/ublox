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

#include <cstdint>
#include <limits>

#include "comms/comms.h"

#include "ublox/Message.h"

namespace ublox
{

namespace field
{

namespace common
{

typedef ublox::Message::Field FieldBase;

template <typename... TOptions>
using U1T =
    comms::field::IntValue<
        FieldBase,
        std::uint8_t,
        TOptions...
    >;

typedef U1T<> U1;

template <typename... TOptions>
using I1T =
    comms::field::IntValue<
        FieldBase,
        std::int8_t,
        TOptions...
    >;

typedef I1T<> I1;

template <typename... TOptions>
using X1T =
    comms::field::BitmaskValue<
        FieldBase,
        comms::option::FixedLength<1>,
        TOptions...
    >;

typedef X1T<> X1;


template <typename... TOptions>
using U2T =
    comms::field::IntValue<
        FieldBase,
        std::uint16_t,
        TOptions...
    >;

typedef U2T<> U2;

template <typename... TOptions>
using I2T =
    comms::field::IntValue<
        FieldBase,
        std::int16_t,
        TOptions...
    >;

typedef I2T<> I2;

template <typename... TOptions>
using X2T =
    comms::field::BitmaskValue<
        FieldBase,
        comms::option::FixedLength<2>,
        TOptions...
    >;

typedef X2T<> X2;

template <typename... TOptions>
using U4T =
    comms::field::IntValue<
        FieldBase,
        std::uint32_t,
        TOptions...
    >;

typedef U4T<> U4;

template <typename... TOptions>
using I4T =
    comms::field::IntValue<
        FieldBase,
        std::int32_t,
        TOptions...
    >;

typedef I4T<> I4;

template <typename... TOptions>
using X4T =
    comms::field::BitmaskValue<
        FieldBase,
        comms::option::FixedLength<4>,
        TOptions...
    >;

typedef X4T<> X4;

template <typename... TOptions>
using res1T = U1T<comms::option::ValidNumValueRange<0, 0>, TOptions...>;
using res1 = res1T<>;

template <typename... TOptions>
using res2T = U2T<comms::option::ValidNumValueRange<0, 0>, TOptions...>;
using res2 = res2T<>;

using res3 =
    comms::field::IntValue<
        FieldBase,
        std::uint32_t,
        comms::option::FixedLength<3>,
        comms::option::ValidNumValueRange<0, 0>
    >;

template <typename... TOptions>
using res4T = U4T<comms::option::ValidNumValueRange<0, 0>, TOptions...>;
using res4 = res4T<>;

template <typename... TOptions>
using R4T =
    comms::field::FloatValue<
        FieldBase,
        float,
        TOptions...
    >;

typedef R4T<> R4;

static_assert(std::numeric_limits<float>::is_iec559,
    "float is expected to have IEEE 754 representation");

static_assert(sizeof(float) == sizeof(std::uint32_t),
    "float is expected to have size of 4 bytes");

template <typename... TOptions>
using R8T =
    comms::field::FloatValue<
        FieldBase,
        double,
        TOptions...
    >;

typedef R8T<> R8;

static_assert(std::numeric_limits<double>::is_iec559,
    "double is expected to have IEEE 754 representation");

static_assert(sizeof(double) == sizeof(std::uint64_t),
    "double is expected to have size of 8 bytes");

using Scaling_mm2m = comms::option::ScalingRatio<1, 1000000L>;
using Scaling_cm2m = comms::option::ScalingRatio<1, 1000>;
using Scaling_us2s = comms::option::ScalingRatio<1, 1000000000L>;
using Scaling_ns2s = comms::option::ScalingRatio<1, 1000000L>;
using Scaling_ms2s = comms::option::ScalingRatio<1, 1000>;

using iTOW =
    U4T<
        Scaling_ms2s,
        comms::option::ValidNumValueRange<0, 1000L * 60 * 60 * 24 * 7>
    >;

using week = I2;
using numSV = U1;
using svid = U1T<comms::option::ValidNumValueRange<1, 96> >;

}  // namespace common

}  // namespace field

}  // namespace ublox


