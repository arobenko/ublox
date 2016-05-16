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
/// @brief Contains definition of common fields.

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

/// @brief Base class for all the fields.
/// @details takes the endian information from the relevant option provided
///     to the ublox::Message as options, i.e. little endian.
using FieldBase = ublox::Message::Field;

/// @brief Common definition for 1 byte unsigned integer value field
/// @details Defined to be
///     <a href="https://dl.dropboxusercontent.com/u/46999418/comms_champion/comms/html/classcomms_1_1field_1_1IntValue.html">comms::field::IntValue</a>
///     with @ref FieldBase as a base class, @b std::uint8_t as a storage type
///     and @b TOptions... as extra options.
/// @tparam TOptions Extra options.
template <typename... TOptions>
using U1T =
    comms::field::IntValue<
        FieldBase,
        std::uint8_t,
        TOptions...
    >;

/// @brief Same as @ref U1T without any extra options.
using U1 = U1T<>;

/// @brief Common definition for 1 byte signed integer value field
/// @details Defined to be
///     <a href="https://dl.dropboxusercontent.com/u/46999418/comms_champion/comms/html/classcomms_1_1field_1_1IntValue.html">comms::field::IntValue</a>
///     with @ref FieldBase as a base class, @b std::int8_t as a storage type
///     and @b TOptions... as extra options.
/// @tparam TOptions Extra options.
template <typename... TOptions>
using I1T =
    comms::field::IntValue<
        FieldBase,
        std::int8_t,
        TOptions...
    >;

/// @brief Same as @ref I1T without any extra options
using I1 = I1T<>;

/// @brief Common definition for 1 byte bitmask value field
/// @details Defined to be
///     <a href="https://dl.dropboxusercontent.com/u/46999418/comms_champion/comms/html/classcomms_1_1field_1_1BitmaskValue.html">comms::field::BitmaskValue</a>
///     with @ref FieldBase as a base class, 1 byte fixed length
///     and @b TOptions... as extra options.
/// @tparam TOptions Extra options.
template <typename... TOptions>
using X1T =
    comms::field::BitmaskValue<
        FieldBase,
        comms::option::FixedLength<1>,
        TOptions...
    >;

/// @brief Same as @ref X1T without any extra options
using X1 = X1T<>;

/// @brief Common definition for 2 bytes unsigned integer value field
/// @details Defined to be
///     <a href="https://dl.dropboxusercontent.com/u/46999418/comms_champion/comms/html/classcomms_1_1field_1_1IntValue.html">comms::field::IntValue</a>
///     with @ref FieldBase as a base class, @b std::uint16_t as a storage type
///     and @b TOptions... as extra options.
/// @tparam TOptions Extra options.
template <typename... TOptions>
using U2T =
    comms::field::IntValue<
        FieldBase,
        std::uint16_t,
        TOptions...
    >;

/// @brief Same as @ref U2T without any extra options.
using U2 = U2T<>;

/// @brief Common definition for 2 bytes signed integer value field
/// @details Defined to be
///     <a href="https://dl.dropboxusercontent.com/u/46999418/comms_champion/comms/html/classcomms_1_1field_1_1IntValue.html">comms::field::IntValue</a>
///     with @ref FieldBase as a base class, @b std::int16_t as a storage type
///     and @b TOptions... as extra options.
/// @tparam TOptions Extra options.
template <typename... TOptions>
using I2T =
    comms::field::IntValue<
        FieldBase,
        std::int16_t,
        TOptions...
    >;

/// @brief Same as @ref I2T without any extra options.
using I2 = I2T<>;

/// @brief Common definition for 2 bytes bitmask value field
/// @details Defined to be
///     <a href="https://dl.dropboxusercontent.com/u/46999418/comms_champion/comms/html/classcomms_1_1field_1_1BitmaskValue.html">comms::field::BitmaskValue</a>
///     with @ref FieldBase as a base class, 2 bytes fixed length
///     and @b TOptions... as extra options.
/// @tparam TOptions Extra options.
template <typename... TOptions>
using X2T =
    comms::field::BitmaskValue<
        FieldBase,
        comms::option::FixedLength<2>,
        TOptions...
    >;

/// @brief Same as @ref X2T without any extra options
using X2 = X2T<>;

/// @brief Common definition for 4 bytes unsigned integer value field
/// @details Defined to be
///     <a href="https://dl.dropboxusercontent.com/u/46999418/comms_champion/comms/html/classcomms_1_1field_1_1IntValue.html">comms::field::IntValue</a>
///     with @ref FieldBase as a base class, @b std::uint32_t as a storage type
///     and @b TOptions... as extra options.
/// @tparam TOptions Extra options.
template <typename... TOptions>
using U4T =
    comms::field::IntValue<
        FieldBase,
        std::uint32_t,
        TOptions...
    >;

/// @brief Same as @ref U4T without any extra options.
using U4 = U4T<>;

/// @brief Common definition for 4 bytes signed integer value field
/// @details Defined to be
///     <a href="https://dl.dropboxusercontent.com/u/46999418/comms_champion/comms/html/classcomms_1_1field_1_1IntValue.html">comms::field::IntValue</a>
///     with @ref FieldBase as a base class, @b std::int32_t as a storage type
///     and @b TOptions... as extra options.
/// @tparam TOptions Extra options.
template <typename... TOptions>
using I4T =
    comms::field::IntValue<
        FieldBase,
        std::int32_t,
        TOptions...
    >;

/// @brief Same as @ref I4T without any extra options.
using I4 = I4T<>;

/// @brief Common definition for 4 bytes bitmask value field
/// @details Defined to be
///     <a href="https://dl.dropboxusercontent.com/u/46999418/comms_champion/comms/html/classcomms_1_1field_1_1BitmaskValue.html">comms::field::BitmaskValue</a>
///     with @ref FieldBase as a base class, 2 bytes fixed length
///     and @b TOptions... as extra options.
/// @tparam TOptions Extra options.
template <typename... TOptions>
using X4T =
    comms::field::BitmaskValue<
        FieldBase,
        comms::option::FixedLength<4>,
        TOptions...
    >;

/// @brief Same as @ref X4T without any extra options
using X4 = X4T<>;

/// @brief Common definition of reserved 1 byte field
/// @details Defined as @ref U1T with single valid value of 0.
/// @tparam TOptions extra options to be based to @ref U1T definition
template <typename... TOptions>
using res1T = U1T<comms::option::ValidNumValueRange<0, 0>, TOptions...>;

/// @brief Same as @ref res1T without any extra options
using res1 = res1T<>;

/// @brief Common definition of reserved 2 bytes field
/// @details Defined as @ref U2T with single valid value of 0.
/// @tparam TOptions extra options to be based to @ref U2T definition
template <typename... TOptions>
using res2T = U2T<comms::option::ValidNumValueRange<0, 0>, TOptions...>;

/// @brief Same as @ref res2T without any extra options
using res2 = res2T<>;

/// @brief Common definition of reserved 2 bytes field
/// @details Defined as @ref U4T with serialisation length limit to 3 bytes and
///     single valid value of 0.
/// @tparam TOptions extra options to be based to @ref U4T definition
template <typename... TOptions>
using res3T =
    U4T<
        comms::option::FixedLength<3>,
        comms::option::ValidNumValueRange<0, 0>,
        TOptions...
    >;

/// @brief Same as @ref res3T without any extra options
using res3 = res3T<>;

/// @brief Common definition of reserved 4 bytes field
/// @details Defined as @ref U4T with single valid value of 0.
/// @tparam TOptions extra options to be based to @ref U4T definition
template <typename... TOptions>
using res4T = U4T<comms::option::ValidNumValueRange<0, 0>, TOptions...>;

/// @brief Same as @ref res4T without any extra options
using res4 = res4T<>;

/// @brief Common definition for 4 byte IEEE 754 single precision floating point value field
/// @details Defined to be
///     <a href="https://dl.dropboxusercontent.com/u/46999418/comms_champion/comms/html/classcomms_1_1field_1_1FloatValue.html">comms::field::FloatValue</a>
///     with @ref FieldBase as a base class, @b float as a storage type
///     and @b TOptions... as extra options.
/// @tparam TOptions Extra options.
template <typename... TOptions>
using R4T =
    comms::field::FloatValue<
        FieldBase,
        float,
        TOptions...
    >;

/// @brief Same as @ref R4T without any extra options
using R4 = R4T<>;

static_assert(std::numeric_limits<float>::is_iec559,
    "float is expected to have IEEE 754 representation");

static_assert(sizeof(float) == sizeof(std::uint32_t),
    "float is expected to have size of 4 bytes");

/// @brief Common definition for 4 byte IEEE 754 double precision floating point value field
/// @details Defined to be
///     <a href="https://dl.dropboxusercontent.com/u/46999418/comms_champion/comms/html/classcomms_1_1field_1_1FloatValue.html">comms::field::FloatValue</a>
///     with @ref FieldBase as a base class, @b double as a storage type
///     and @b TOptions... as extra options.
/// @tparam TOptions Extra options.
template <typename... TOptions>
using R8T =
    comms::field::FloatValue<
        FieldBase,
        double,
        TOptions...
    >;

/// @brief Same as @ref R8T without any extra options
using R8 = R8T<>;

static_assert(std::numeric_limits<double>::is_iec559,
    "double is expected to have IEEE 754 representation");

static_assert(sizeof(double) == sizeof(std::uint64_t),
    "double is expected to have size of 8 bytes");

/// @brief Common option used to scale centimeters to meters
using Scaling_cm2m = comms::option::ScalingRatio<1, 100>;

/// @brief Common option used to scale millimeters to meters
using Scaling_mm2m = comms::option::ScalingRatio<1, 1000L>;

/// @brief Common option used to scale milliseconds to seconds
using Scaling_ms2s = comms::option::ScalingRatio<1, 1000>;

/// @brief Common option used to scale microseconds to seconds
using Scaling_us2s = comms::option::ScalingRatio<1, 1000000L>;

/// @brief Common option used to scale nanoseconds to seconds
using Scaling_ns2s = comms::option::ScalingRatio<1, 1000000000L>;

/// @brief Common definition of sequence of fields or raw bytes.
/// @details Defined to be
///     <a href="https://dl.dropboxusercontent.com/u/46999418/comms_champion/comms/html/classcomms_1_1field_1_1ArrayList.html">comms::field::ArrayList</a>
///     with @ref FieldBase as a base class, @b TElem as the element type, and
///     @b TOptions as extra options.
/// @tparam TElem Element of the list.
/// @tparam TOptions Extra options.
template <typename TElem, typename... TOptions>
using ListT =
    comms::field::ArrayList<
        FieldBase,
        TElem,
        TOptions...
    >;

/// @brief Common definition of enum value field.
/// @details Defined to be
///     <a href="https://dl.dropboxusercontent.com/u/46999418/comms_champion/comms/html/classcomms_1_1field_1_1EnumValue.html">comms::field::EnumValue</a>
///     with @ref FieldBase as a base class, @b TEnum as the enum type, and
///     @b TOptions as extra options.
/// @tparam TEnum Enum type.
/// @tparam TOptions Extra options.
template <typename TEnum, typename... TOptions>
using EnumT =
    comms::field::EnumValue<
        FieldBase,
        TEnum,
        TOptions...
    >;

/// @brief Common definition of optional field.
/// @details Defined to be
///     <a href="https://dl.dropboxusercontent.com/u/46999418/comms_champion/comms/html/classcomms_1_1field_1_1Optional.html">comms::field::Optional</a>
///     with @b TField as the field type.
/// @tparam TField Optional field.
template <typename TField>
using OptionalT = comms::field::Optional<TField>;

/// @brief Common definition of bitfield field.
/// @details Defined to be
///     <a href="https://dl.dropboxusercontent.com/u/46999418/comms_champion/comms/html/classcomms_1_1field_1_1Bitfield.html">comms::field::Bitfield</a>
///     with @ref FieldBase as a base class, all member fields bundled in @b std::tuple, and
///     @b TOptions as extra options.
/// @tparam TMemFields Member fields bundled in @b std::tuple.
/// @tparam TOptions Extra options.
template <typename TMemFields, typename...TOptions>
using BitfieldT =
    comms::field::Bitfield<
        FieldBase,
        TMemFields,
        TOptions...
    >;

/// @brief Common definition of string field.
/// @details Defined to be
///     <a href="https://dl.dropboxusercontent.com/u/46999418/comms_champion/comms/html/classcomms_1_1field_1_1String.html">comms::field::String</a>
///     with @ref FieldBase as a base class, and
///     @b TOptions as extra options.
/// @tparam TOptions Extra options.
template <typename...TOptions>
using StringT =
    comms::field::String<
        FieldBase,
        TOptions...
    >;

/// @brief Same as @ref StringT without any extra options
using String = StringT<>;

/// @brief Common definition of zero-terminated string with fixed serialisation
///     length.
/// @details Defined to be StringT with 1 byte zero value as a trailing suffix, and
///     having fixed serialisation length.
/// @tparam TSize Full fixed serialisation length (including zero termination) of the
///     string value
template <std::size_t TSize>
using ZString =
    StringT<
        comms::option::SequenceFixedSize<TSize - 1>,
        comms::option::SequenceTrailingFieldSuffix<
            field::common::U1T<
                comms::option::ValidNumValueRange<0, 0>
            >
        >
    >;

/// @brief Common definition of bundle field.
/// @details Defined to be
///     <a href="https://dl.dropboxusercontent.com/u/46999418/comms_champion/comms/html/classcomms_1_1field_1_1Bundle.html">comms::field::Bundle</a>
///     with all member fields bundled in @b std::tuple, and
///     @b TOptions as extra options.
/// @tparam TMemFields Member fields bundled in @b std::tuple.
/// @tparam TOptions Extra options.
template <typename TMemFields, typename...TOptions>
using BundleT =
    comms::field::Bundle<
        TMemFields,
        TOptions...
    >;


/// @brief Definition of common @b iTOW field used in multiple messages in
///     multiple message classes.
/// @details Defined as @ref U4T with ability to scale from milliseconds to
///     seconds.
using iTOW =
    U4T<
        Scaling_ms2s,
        comms::option::ValidNumValueRange<0, 1000L * 60 * 60 * 24 * 7>
    >;

/// @brief Definition of common @b week field used in multiple messages in
///     multiple message classes.
using week = I2;

/// @brief Definition of common @b numSV field used in multiple messages in
///     multiple message classes.
using numSV = U1;

/// @brief Definition of common @b svid field used in multiple messages in
///     multiple message classes.
using svid = U1T<comms::option::ValidNumValueRange<1, 96> >;

}  // namespace common

}  // namespace field

}  // namespace ublox


