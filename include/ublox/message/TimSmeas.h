//
// Copyright 2017 (C). Alex Robenko. All rights reserved.
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
/// @brief Contains definition of TIM-SMEAS message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the TIM-SMEAS message fields.
/// @see TimSmeas
struct TimSmeasFields
{
    /// @brief Definition of "version" field.
    using version =
        field::common::U1T<comms::option::ValidNumValueRange<0, 0> >;

    /// @brief Definition of "numMeas" field.
    using numMeas = field::common::U1;

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res2;

    /// @brief Definition of "iTOW" field.
    using iTOW = field::common::iTOW;

    /// @brief Definition of "reserved2" field.
    using reserved2 = field::common::res4;

    /// @brief Definition of "sourceId" field.
    using sourceId = field::common::U1;

    /// @brief Definition of "flags" field.
    struct flags : public
        field::common::X1T<comms::option::BitmaskReservedBits<0xfc, 0> >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS(freqValid, phaseValid);
    };

    /// @brief Definition of "phaseOffsetFrac" field.
    using phaseOffsetFrac =
        field::common::I1T<
            comms::option::ScalingRatio<1, 0x100>,
            comms::option::UnitsNanoseconds
        >;

    /// @brief Definition of "phaseUncFrac" field.
    using phaseUncFrac =
        field::common::U1T<
            comms::option::ScalingRatio<1, 0x100>,
            comms::option::UnitsNanoseconds
        >;

    /// @brief Definition of "phaseOffset" field.
    using phaseOffset = field::common::I4T<comms::option::UnitsNanoseconds>;

    /// @brief Definition of "phaseUnc" field.
    using phaseUnc = field::common::U4T<comms::option::UnitsNanoseconds>;

    /// @brief Definition of "reserved3" field.
    using reserved3 = field::common::res4;

    /// @brief Definition of "freqOffset" field.
    using freqOffset =
        field::common::I4T<
            comms::option::ScalingRatio<1, 0x100>
        >;

    /// @brief Definition of "freqUnc" field.
    using freqUnc =
        field::common::U4T<
            comms::option::ScalingRatio<1, 0x100>
        >;

    /// @brief Definition of a block field repeated multiple times in @ref
    ///     data list.
    struct block : public
        field::common::BundleT<
            std::tuple<
                sourceId,
                flags,
                phaseOffsetFrac,
                phaseUncFrac,
                phaseOffset,
                phaseUnc,
                reserved3,
                freqOffset,
                freqUnc
            >
        >
    {
        /// @brief Allow access to internal fields.
        /// @details See definition of @b COMMS_FIELD_MEMBERS_ACCESS macro
        ///     related to @b comms::field::Bundle class from COMMS library
        ///     for details.
        COMMS_FIELD_MEMBERS_ACCESS(
            sourceId,
            flags,
            phaseOffsetFrac,
            phaseUncFrac,
            phaseOffset,
            phaseUnc,
            reserved3,
            freqOffset,
            freqUnc
        );
    };

    /// @brief Definition of "data" field as list of blocks (@ref block).
    /// @tparam TOpt Extra option(s)
    template <typename TOpt = comms::option::EmptyOption>
    using data =
        field::common::ListT<
            block,
            comms::option::SequenceSizeForcingEnabled,
            TOpt
        >;

    /// @brief All the fields bundled in std::tuple.
    /// @tparam TOpt Extra option(s) for @ref data field
    template <typename TOpt>
    using All = std::tuple<
        version,
        numMeas,
        reserved1,
        iTOW,
        reserved2,
        data<TOpt>
    >;
};

/// @brief Definition of TIM-SMEAS message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref TimSmeasFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
/// @tparam TDataOpt Extra option(s) for @b data field
template <typename TMsgBase = Message, typename TDataOpt = comms::option::EmptyOption>
class TimSmeas : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_TIM_SMEAS>,
        comms::option::FieldsImpl<TimSmeasFields::All<TDataOpt> >,
        comms::option::MsgType<TimSmeas<TMsgBase, TDataOpt> >,
        comms::option::HasDoRefresh
    >
{
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b version for @ref TimSmeasFields::version field
    ///     @li @b numMeas for @ref TimSmeasFields::numMeas field
    ///     @li @b reserved1 for @ref TimSmeasFields::reserved1 field
    ///     @li @b iTOW for @ref TimSmeasFields::iTOW field
    ///     @li @b reserved2 for @ref TimSmeasFields::reserved2 field
    ///     @li @b data for @ref TimSmeasFields::data field
    COMMS_MSG_FIELDS_ACCESS(version, numMeas, reserved1, iTOW, reserved2, data);

    /// @brief Default constructor
    TimSmeas() = default;

    /// @brief Copy constructor
    TimSmeas(const TimSmeas&) = default;

    /// @brief Move constructor
    TimSmeas(TimSmeas&& other) = default;

    /// @brief Destructor
    ~TimSmeas() = default;

    /// @brief Copy assignment
    TimSmeas& operator=(const TimSmeas&) = default;

    /// @brief Move assignment
    TimSmeas& operator=(TimSmeas&&) = default;

    /// @brief Provides custom read functionality.
    /// @details The number of blocks in @b data (@ref TimSmeasFields::data)
    ///     list is determined by the value of @b numMeas (@ref TimSmeasFields::numMeas)
    ///     field.
    template <typename TIter>
    comms::ErrorStatus doRead(TIter& iter, std::size_t len)
    {
        typedef typename std::decay<decltype(comms::toMessageBase(*this))>::type Base;
        auto es = Base::template readFieldsUntil<FieldIdx_data>(iter, len);
        if (es != comms::ErrorStatus::Success) {
            return es;
        }

        field_data().forceReadElemCount(field_numMeas().value());
        return Base::template readFieldsFrom<FieldIdx_data>(iter, len);
    }

    /// @brief Provides custom refresh functionality
    /// @details The value of @b numMeas (@ref TimSmeasFields::numMeas) field is
    ///     determined by number of blocks stored in @b data (@ref TimSmeasFields::data)
    ///     list.
    /// @return @b true in case the value of "numMeas" field was modified, @b false otherwise
    bool doRefresh()
    {
        if (field_numMeas().value() == field_data().value().size()) {
            return false;
        }

        field_numMeas().value() = field_data().value().size();
        return true;
    }

};


}  // namespace message

}  // namespace ublox





