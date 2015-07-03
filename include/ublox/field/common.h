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
#include <comms/comms.h>

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

}  // namespace common

}  // namespace field

}  // namespace ublox


