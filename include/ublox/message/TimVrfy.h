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
/// @brief Contains definition of TIM-VRFY message and its fields.

#pragma once

#include <algorithm>

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the TIM-VRFY message fields.
/// @see TimVrfy
struct TimVrfyFields
{
    /// @brief Value enumeration for @ref src field.
    enum class Src : std::uint8_t
    {
        None, ///< no time aiding
        Rtc = 2, ///< source was RTC
        AidIni = 3 ///< source was AID-INI
    };

    /// @brief Custom validator for @ref src field
    struct SrcValidator
    {
        template <typename TField>
        bool operator()(const TField& field) const
        {
            auto value = field.value();
            static const Src Values[] = {
                Src::None,
                Src::Rtc,
                Src::AidIni
            };

            auto iter = std::lower_bound(std::begin(Values), std::end(Values), value);
            return (iter != std::end(Values)) && (*iter == value);
        }
    };

    /// @brief Definition of "itow" field.
    using itow = field::common::I4T<field::common::Scaling_ms2s>;

    /// @brief Definition of "frac" field.
    using frac = field::common::I4T<field::common::Scaling_ns2s>;

    /// @brief Definition of "deltaMS" field.
    using deltaMS = field::common::I4T<field::common::Scaling_ms2s>;

    /// @brief Definition of "deltaNS" field.
    using deltaNS = field::common::I4T<field::common::Scaling_ns2s>;

    /// @brief Definition of "wno" field.
    using wno = field::common::U2;

    /// @brief Definition of "src" member field of @ref flags field.
    using src =
        field::common::EnumT<
            Src,
            comms::option::ContentsValidator<SrcValidator>
        >;

    /// @brief Definition of "flags" field as equivalent to @ref src to save
    ///     extra work on reserved bits.
    using flags = src;

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res1;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        itow,
        frac,
        deltaMS,
        deltaNS,
        wno,
        flags,
        reserved1
    >;

};

/// @brief Definition of TIM-VRFY message
/// @details Inherits from
///     <a href="https://dl.dropboxusercontent.com/u/46999418/comms_champion/comms/html/classcomms_1_1MessageBase.html">comms::MessageBase</a>
///     while providing @b TMsgBase as common interface class as well as
///     @b comms::option::StaticNumIdImpl, @b comms::option::FieldsImpl, and
///     @b comms::option::DispatchImpl as options. @n
///     See @ref TimVrfyFields and for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class TimVrfy : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_TIM_VRFY>,
        comms::option::FieldsImpl<TimVrfyFields::All>,
        comms::option::DispatchImpl<TimVrfy<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_TIM_VRFY>,
        comms::option::FieldsImpl<TimVrfyFields::All>,
        comms::option::DispatchImpl<TimVrfy<TMsgBase> >
    > Base;
public:

    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_itow, ///< @b itow field, see @ref TimVrfyFields::itow
        FieldIdx_frac, ///< @b frac field, see @ref TimVrfyFields::frac
        FieldIdx_deltaMS, ///< @b deltaMS field, see @ref TimVrfyFields::deltaMS
        FieldIdx_deltaNS, ///< @b deltaNS field, see @ref TimVrfyFields::deltaNS
        FieldIdx_wno, ///< @b wno field, see @ref TimVrfyFields::wno
        FieldIdx_flags, ///< @b flags field, see @ref TimVrfyFields::flags
        FieldIdx_reserved1, ///< @b reserved1 field, see @ref TimVrfyFields::reserved1
        FieldIdx_numOfValues ///< number of available fields
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    /// @brief Default constructor
    TimVrfy() = default;

    /// @brief Copy constructor
    TimVrfy(const TimVrfy&) = default;

    /// @brief Move constructor
    TimVrfy(TimVrfy&& other) = default;

    /// @brief Destructor
    virtual ~TimVrfy() = default;

    /// @brief Copy assignment
    TimVrfy& operator=(const TimVrfy&) = default;

    /// @brief Move assignment
    TimVrfy& operator=(TimVrfy&&) = default;
};


}  // namespace message

}  // namespace ublox

