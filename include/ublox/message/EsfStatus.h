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
/// @brief Contains definition of ESF-STATUS message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the ESF-STATUS message fields.
/// @see EsfStatus
struct EsfStatusFields
{
    /// @brief Definition of "iTOW" field.
    using iTOW = field::common::iTOW;

    /// @brief Definition of "version" field.
    using version =
        field::common::U1T<
            comms::option::ValidNumValueRange<2, 2>,
            comms::option::DefaultNumValue<2>
        >;

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res7;

    /// @brief Value enumeration for @ref fusionMode field.
    enum class FusionMode : std::uint8_t
    {
        Initializing, ///< Sensor fusion filter is initializing.
        On, ///< Sensor fusion is on
        OnHold, ///< Sensor fusion is on-hold.
        Off, ///< Sensor fusion is off
        NumOfValues /// number of available values
    };

    /// @brief Definition of "fusionMode" field.
    using fusionMode =
        field::common::EnumT<
            FusionMode,
            comms::option::ValidNumValueRange<0, (int)FusionMode::NumOfValues - 1>
        >;

    /// @brief Definition of "reserved2" field.
    using reserved2 = field::common::res2;

    /// @brief Definition of "numSens" field.
    using numSens = field::common::U1;

    /// @brief Definition of "type" member field of @ref sensStatus1 bitfield.
    using type =
        field::common::U1T<
            comms::option::FixedBitLength<6>,
            comms::option::ValidNumValueRange<0, 0x3f>
        >;

    /// @brief Definition of "flagsSensStatus1" member field of @ref sensStatus1 bitfield.
    struct flagsSensStatus1 : public
            field::common::X1T<comms::option::FixedBitLength<2> >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS(used, ready);
    };

    /// @brief Definition of "sensStatus1" field.
    struct sensStatus1 : public
        field::common::BitfieldT<
            std::tuple<
                type,
                flagsSensStatus1
            >
        >
    {
        /// @brief Allow access to internal fields.
        /// @details See definition of @b COMMS_FIELD_MEMBERS_ACCESS macro
        ///     related to @b comms::field::Bitfield class from COMMS library
        ///     for details.
        ///
        ///     The field names are:
        ///     @li @b type for @ref EsfStatusFields::type field
        ///     @li @b flags for @ref EsfStatusFields::flagsSensStatus1 field
        COMMS_FIELD_MEMBERS_ACCESS(type, flags);
    };

    /// @brief Value enumeration for @ref calibStatus field.
    enum class CalibStatus : std::uint8_t
    {
        NotCalibrated, ///< Sensor is not calibrated.
        Calibrating, ///< Sensor is calibrating
        Calibrated, ///< Sensor is calibrated.
        Calibrated2, ///< Sensor is calibrated
        NumOfValues /// number of available values
    };

    /// @brief Definition of "calibStatus" member field of @ref sensStatus2 bitfield.
    using calibStatus =
        field::common::EnumT<
            CalibStatus,
            comms::option::ValidNumValueRange<0, (int)CalibStatus::NumOfValues - 1>,
            comms::option::FixedBitLength<2>
        >;

    /// @brief Value enumeration for @ref timeStatus field.
    enum class TimeStatus : std::uint8_t
    {
        NoData, ///< No data.
        FirstByte, ///< Reception of the first byte used to tag the measurement.
        EventInput, ///< Event input used to tag the measurement.
        TimeTag, ///< Time tag provided with the data
        NumOfValues /// number of available values
    };

    /// @brief Definition of "timeStatus" member field of @ref sensStatus2 bitfield.
    using timeStatus =
        field::common::EnumT<
            TimeStatus,
            comms::option::ValidNumValueRange<0, (int)TimeStatus::NumOfValues - 1>,
            comms::option::FixedBitLength<2>
        >;

    /// @brief Definition of "sensStatus2" field.
    struct sensStatus2 : public
        field::common::BitfieldT<
            std::tuple<
                calibStatus,
                timeStatus,
                field::common::res1T<comms::option::FixedBitLength<4> >
            >
        >
    {
        /// @brief Allow access to internal fields.
        /// @details See definition of @b COMMS_FIELD_MEMBERS_ACCESS macro
        ///     related to @b comms::field::Bitfield class from COMMS library
        ///     for details.
        ///
        ///     The field names are:
        COMMS_FIELD_MEMBERS_ACCESS(calibStatus, timeStatus, reserved);
    };


    /// @brief Definition of "freq" field.
    using freq = field::common::U1;

    /// @brief Definition of "faults" field.
    struct faults : public
            field::common::X1T<
                comms::option::BitmaskReservedBits<0xf0, 0>
            >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS(badMeas, badTTag, missingMeas, noisyMeas);
    };


    /// @brief Definition of a block field repeated multiple times in @ref
    ///     data list.
    struct block : public
        field::common::BundleT<
            std::tuple<
                sensStatus1,
                sensStatus2,
                freq,
                faults
            >
        >
    {
        /// @brief Allow access to internal fields.
        /// @details See definition of @b COMMS_FIELD_MEMBERS_ACCESS macro
        ///     related to @b comms::field::Bitfield class from COMMS library
        ///     for details.
        COMMS_FIELD_MEMBERS_ACCESS(sensStatus1, sensStatus2, freq, faults);
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
        iTOW,
        version,
        reserved1,
        fusionMode,
        reserved2,
        numSens,
        data<TOpt>
    >;
};

/// @brief Definition of ESF-STATUS message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref EsfStatusFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
/// @tparam TDataOpt Extra option(s) for @b data field
template <typename TMsgBase = Message, typename TDataOpt = comms::option::EmptyOption>
class EsfStatus : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_ESF_STATUS>,
        comms::option::FieldsImpl<EsfStatusFields::All<TDataOpt> >,
        comms::option::MsgType<EsfStatus<TMsgBase, TDataOpt> >,
        comms::option::HasDoRefresh
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_ESF_STATUS>,
        comms::option::FieldsImpl<EsfStatusFields::All<TDataOpt> >,
        comms::option::MsgType<EsfStatus<TMsgBase, TDataOpt> >,
        comms::option::HasDoRefresh
    > Base;
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b iTOW for @ref EsfStatusFields::iTOW field
    ///     @li @b version for @ref EsfStatusFields::version field
    ///     @li @b reserved1 for @ref EsfStatusFields::reserved1 field
    ///     @li @b fusionMode for @ref EsfStatusFields::fusionMode field
    ///     @li @b reserved2 for @ref EsfStatusFields::reserved2 field
    ///     @li @b numSens for @ref EsfStatusFields::numSens field
    ///     @li @b data for @ref EsfStatusFields::data field
    COMMS_MSG_FIELDS_ACCESS(
        iTOW,
        version,
        reserved1,
        fusionMode,
        reserved2,
        numSens,
        data
    );

    /// @brief Default constructor
    EsfStatus() = default;

    /// @brief Copy constructor
    EsfStatus(const EsfStatus&) = default;

    /// @brief Move constructor
    EsfStatus(EsfStatus&& other) = default;

    /// @brief Destructor
    ~EsfStatus() = default;

    /// @brief Copy assignment
    EsfStatus& operator=(const EsfStatus&) = default;

    /// @brief Move assignment
    EsfStatus& operator=(EsfStatus&&) = default;

    /// @brief Provides custom read functionality.
    /// @details The number of blocks in @b data (@ref EsfStatusFields::data)
    ///     list is determined by the value of @b numSens (@ref EsfStatusFields::numSens)
    ///     field.
    template <typename TIter>
    comms::ErrorStatus doRead(TIter& iter, std::size_t len)
    {
        auto es = Base::template readFieldsUntil<FieldIdx_data>(iter, len);
        if (es != comms::ErrorStatus::Success) {
            return es;
        }

        field_data().forceReadElemCount(field_numSens().value());
        return Base::template readFieldsFrom<FieldIdx_data>(iter, len);
    }

    /// @brief Provides custom refresh functionality
    /// @details The value of @b numSens (@ref EsfStatusFields::numSens) field is
    ///     determined by number of blocks stored in @b data (@ref EsfStatusFields::data)
    ///     list.
    /// @return @b true in case the value of "numSens" field was modified, @b false otherwise
    bool doRefresh()
    {
        if (field_numSens().value() == field_data().value().size()) {
            return false;
        }

        field_numSens().value() = field_data().value().size();
        return true;
    }

};


}  // namespace message

}  // namespace ublox





