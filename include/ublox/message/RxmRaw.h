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
/// @brief Contains definition of RXM-RAW message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/rxm.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the RXM-RAW message fields.
/// @see RxmRaw
struct RxmRawFields
{
    /// @brief Definition of "rcvTow" field.
    using rcvTow = field::common::I4T<field::common::Scaling_ms2s>;

    /// @brief Definition of "week" field.
    using week = field::rxm::week;

    /// @brief Definition of "numSV" field.
    using numSV = field::rxm::numSV;

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res1;

    /// @brief Definition of "cpMes" field.
    using cpMes = field::common::R8;

    /// @brief Definition of "prMes" field.
    using prMes = field::common::R8;

    /// @brief Definition of "doMes" field.
    using doMes = field::common::R4;

    /// @brief Definition of "sv" field.
    using sv = field::common::U1;

    /// @brief Definition of "mesQI" field.
    using mesQI = field::common::I1;

    /// @brief Definition of "cno" field.
    using cno = field::common::I1;

    /// @brief Definition of "lli" field.
    using lli = field::common::U1;

    /// @brief Definition of a single block of @ref data
    struct block : public
        field::common::BundleT<
            std::tuple<
                cpMes,
                prMes,
                doMes,
                sv,
                mesQI,
                cno,
                lli
            >
        >
    {
        /// @brief Allow access to internal fields.
        /// @details See definition of @b COMMS_FIELD_MEMBERS_ACCESS macro
        ///     related to @b comms::field::Bitfield class from COMMS library
        ///     for details.
        COMMS_FIELD_MEMBERS_ACCESS(cpMes, prMes, doMes, sv, mesQI, cno, lli);
    };

    /// @brief Definition of the list of blocks (@ref block)
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
        rcvTow,
        week,
        numSV,
        reserved1,
        data<TOpt>
    >;
};

/// @brief Definition of RXM-RAW message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref RxmRawFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
/// @tparam TDataOpt Extra option(s) for @b data field
template <typename TMsgBase = Message, typename TDataOpt = comms::option::EmptyOption>
class RxmRaw : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_RXM_RAW>,
        comms::option::FieldsImpl<RxmRawFields::All<TDataOpt> >,
        comms::option::MsgType<RxmRaw<TMsgBase, TDataOpt> >,
        comms::option::HasDoRefresh
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_RXM_RAW>,
        comms::option::FieldsImpl<RxmRawFields::All<TDataOpt> >,
        comms::option::MsgType<RxmRaw<TMsgBase, TDataOpt> >,
        comms::option::HasDoRefresh
    > Base;
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b rcvTow for @ref RxmRawFields::rcvTow field
    ///     @li @b week for @ref RxmRawFields::week field
    ///     @li @b numSV for @ref RxmRawFields::numSV field
    ///     @li @b reserved1 for @ref RxmRawFields::reserved1 field
    ///     @li @b data for @ref RxmRawFields::data field
    COMMS_MSG_FIELDS_ACCESS(rcvTow, week, numSV, reserved1, data);


    /// @brief Default constructor
    RxmRaw() = default;

    /// @brief Copy constructor
    RxmRaw(const RxmRaw&) = default;

    /// @brief Move constructor
    RxmRaw(RxmRaw&& other) = default;

    /// @brief Destructor
    ~RxmRaw() = default;

    /// @brief Copy assignment
    RxmRaw& operator=(const RxmRaw&) = default;

    /// @brief Move assignment
    RxmRaw& operator=(RxmRaw&&) = default;

    /// @brief Provides custom read functionality.
    /// @details The number of blocks in @b data (@ref RxmRawFields::data) list
    ///     is determined by the value of @b numSV (@ref RxmRawFields::numSV) field.
    template <typename TIter>
    comms::ErrorStatus doRead(TIter& iter, std::size_t len)
    {
        auto es = Base::template readFieldsUntil<FieldIdx_data>(iter, len);
        if (es != comms::ErrorStatus::Success) {
            return es;
        }

        auto& allFields = Base::fields();
        auto& numSvField = std::get<FieldIdx_numSV>(allFields);
        auto& dataField = std::get<FieldIdx_data>(allFields);
        dataField.forceReadElemCount(numSvField.value());

        return Base::template readFieldsFrom<FieldIdx_data>(iter, len);
    }

    /// @brief Provides custom refresh functionality
    /// @details The value of @b numSV (@ref RxmRawFields::numSV) field is determined
    ///     by the amount of blocks stored in @b data (@ref RxmRawFields::data) list.
    /// @return @b true in case the value of "numSV" field was modified, @b false otherwise
    bool doRefresh()
    {
        auto& allFields = Base::fields();
        auto& numSvField = std::get<FieldIdx_numSV>(allFields);
        auto& dataField = std::get<FieldIdx_data>(allFields);
        if (numSvField.value() == dataField.value().size()) {
            return false;
        }

        numSvField.value() = dataField.value().size();
        return true;
    }

};


}  // namespace message

}  // namespace ublox





