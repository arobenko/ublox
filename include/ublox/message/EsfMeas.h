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
/// @brief Contains definition of ESF-MEAS message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the ESF-MEAS message fields.
/// @see EsfMeas
struct EsfMeasFields
{
    /// @brief Definition of "timeTag" field.
    using timeTag = field::common::U4;

    /// @brief Value enumeration for @ref timeMarkSent field.
    enum class TimeMarkSent : std::uint8_t
    {
        None, ///< none
        Ext0, ///< on Ext0
        Ext1, ///< on Ext1
        NumOfValues /// number of available values
    };

    /// @brief Definition of "timeMarkSent" member of @ref flags bitfield.
    using timeMarkSent =
        field::common::EnumT<
            TimeMarkSent,
            comms::option::ValidNumValueRange<0, (int)TimeMarkSent::NumOfValues - 1>,
            comms::option::FixedBitLength<2>
        >;

    /// @brief Value enumeration for @ref timeMarkEdge field.
    enum class TimeMarkEdge : std::uint8_t
    {
        Rising, ///< rising edge
        Falling, ///< falling edge
        NumOfValues /// number of available values
    };

    /// @brief Definition of "timeMarkEdge" member of @ref flags bitfield.
    using timeMarkEdge =
        field::common::EnumT<
            TimeMarkEdge,
            comms::option::ValidNumValueRange<0, (int)TimeMarkEdge::NumOfValues - 1>,
            comms::option::FixedBitLength<1>
        >;


    /// @brief Definition of bits in @ref flags field as a separate member field.
    struct flagsBits : public
            field::common::X2T<
                comms::option::BitmaskReservedBits<0xfffe, 0>,
                comms::option::FixedBitLength<13>
            >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS_SEQ macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS_SEQ(calibTtagValid);
    };

    /// @brief Definition of "flags" field.
    struct flags : public
        field::common::BitfieldT<
            std::tuple<
                timeMarkSent,
                timeMarkEdge,
                flagsBits
            >
        >
    {
        /// @brief Allow access to internal fields.
        /// @details See definition of @b COMMS_FIELD_MEMBERS_ACCESS macro
        ///     related to @b comms::field::Bitfield class from COMMS library
        ///     for details.
        ///
        ///     The field names are:
        ///     @li @b timeMarkSent for @ref EsfMeasFields::timeMarkSent field
        ///     @li @b timeMarkEdge for @ref EsfMeasFields::timeMarkEdge field
        ///     @li @b flagsBits for @ref EsfMeasFields::flagsBits field
        COMMS_FIELD_MEMBERS_ACCESS(timeMarkSent, timeMarkEdge, flagsBits);
    };

    /// @brief Definition of "id" field.
    using id = field::common::U2;

    /// @brief Definition of "dataField" field.
    using dataField = field::common::U3;

    /// @brief Definition of "dataType" field.
    using dataType =
        field::common::U1T<
            comms::option::ValidNumValueRange<0, 63>
        >;

    /// @breif Definition of single data element for @ref data field.
    struct dataElem : public
        field::common::BundleT<
            std::tuple<
                dataField,
                dataType
            >
        >
    {
        /// @brief Allow access to internal fields.
        /// @details See definition of @b COMMS_FIELD_MEMBERS_ACCESS macro
        ///     related to @b comms::field::Bitfield class from COMMS library
        ///     for details.
        ///
        ///     The field names are:
        ///     @li @b dataField for @ref EsfMeasFields::dataField field
        ///     @li @b dataType for @ref EsfMeasFields::dataType field
        COMMS_FIELD_MEMBERS_ACCESS(dataField, dataType);
    };

    /// @brief Definition of "data" field as list of elements (@ref dataElem).
    /// @tparam TOpt Extra option(s)
    template <typename TOpt = comms::option::EmptyOption>
    using data =
        field::common::ListT<
            dataElem,
            TOpt
        >;

    /// @brief Definition of "calibTtag" field.
    using calibTtag =
        field::common::OptionalT<
            field::common::U4T<comms::option::UnitsMilliseconds>,
            comms::option::DefaultOptionalMode<comms::field::OptionalMode::Missing>
        >;


    /// @brief All the fields bundled in std::tuple.
    /// @tparam TOpt Extra option(s) for @ref data field
    template <typename TOpt>
    using All = std::tuple<
        timeTag,
        flags,
        id,
        data<TOpt>,
        calibTtag
    >;
};

/// @brief Definition of ESF-MEAS message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref EsfMeasFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
/// @tparam TDataOpt Extra option(s) for @b data field
template <typename TMsgBase = Message, typename TDataOpt = comms::option::EmptyOption>
class EsfMeas : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_ESF_MEAS>,
        comms::option::FieldsImpl<EsfMeasFields::All<TDataOpt> >,
        comms::option::MsgType<EsfMeas<TMsgBase, TDataOpt> >,
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
    ///     @li @b timeTag for @ref EsfMeasFields::timeTag field
    ///     @li @b flags for @ref EsfMeasFields::flags field
    ///     @li @b id for @ref EsfMeasFields::id field
    ///     @li @b data for @ref EsfMeasFields::data field
    ///     @li @b calibTtag for @ref EsfMeasFields::calibTtag field
    COMMS_MSG_FIELDS_ACCESS(
        timeTag,
        flags,
        id,
        data,
        calibTtag
    );

    /// @brief Default constructor
    EsfMeas() = default;

    /// @brief Copy constructor
    EsfMeas(const EsfMeas&) = default;

    /// @brief Move constructor
    EsfMeas(EsfMeas&& other) = default;

    /// @brief Destructor
    ~EsfMeas() = default;

    /// @brief Copy assignment
    EsfMeas& operator=(const EsfMeas&) = default;

    /// @brief Move assignment
    EsfMeas& operator=(EsfMeas&&) = default;

    /// @brief Provides custom read functionality.
    template <typename TIter>
    comms::ErrorStatus doRead(TIter& iter, std::size_t len)
    {
        using Base = typename std::decay<decltype(comms::toMessageBase(*this))>::type;
        auto es = Base::template readFieldsUntil<FieldIdx_data>(iter, len);
        if (es != comms::ErrorStatus::Success) {
            return es;
        }

        if (!field_flags().field_flagsBits().getBitValue_calibTtagValid()) {
            field_calibTtag().setMissing();
            return Base::template readFieldsFrom<FieldIdx_data>(iter, len);
        }

        std::size_t calibTtagLen = EsfMeasFields::calibTtag::maxLength();
        if (len < calibTtagLen) {
            return comms::ErrorStatus::NotEnoughData;
        }

        es = field_data().read(iter, len - calibTtagLen);
        if (es != comms::ErrorStatus::Success) {
            return es;
        }

        field_calibTtag().setExists();
        return Base::template readFieldsFrom<FieldIdx_calibTtag>(iter, calibTtagLen);
    }

    /// @brief Provides custom refresh functionality
    bool doRefresh()
    {
        auto calibTtagMode = comms::field::OptionalMode::Missing;
        if (field_flags().field_flagsBits().getBitValue_calibTtagValid()) {
            calibTtagMode = comms::field::OptionalMode::Exists;
        }

        if (field_calibTtag().getMode() == calibTtagMode) {
            return false;
        }

        field_calibTtag().setMode(calibTtagMode);
        return true;
    }
};


}  // namespace message

}  // namespace ublox





