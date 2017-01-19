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
/// @brief Contains definition of RXM-ALM message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/rxm.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the RXM-ALM message fields.
/// @see RxmAlm
struct RxmAlmFields
{
    /// @brief Definition of "svid" field.
    using svid = field::rxm::svid_ext;

    /// @brief Definition of "week" field.
    using week = field::common::U4;

    /// @brief Definition of "dwrd" field.
    using dwrd =
        field::common::OptionalT<
            field::common::ListT<
                field::common::U4,
                comms::option::SequenceFixedSize<8>
            >
        >;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        svid,
        week,
        dwrd
    >;
};

/// @brief Definition of RXM-ALM message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref RxmAlmFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class RxmAlm : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_RXM_ALM>,
        comms::option::FieldsImpl<RxmAlmFields::All>,
        comms::option::MsgType<RxmAlm<TMsgBase> >,
        comms::option::HasDoRefresh
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_RXM_ALM>,
        comms::option::FieldsImpl<RxmAlmFields::All>,
        comms::option::MsgType<RxmAlm<TMsgBase> >,
        comms::option::HasDoRefresh
    > Base;
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b svid for @ref RxmAlmFields::svid field
    ///     @li @b week for @ref RxmAlmFields::week field
    ///     @li @b dwrd for @ref RxmAlmFields::dwrd field
    COMMS_MSG_FIELDS_ACCESS(Base, svid, week, dwrd);

    /// @brief Default constructor
    /// @details Marks "dwrd" (see @ref RxmAlmFields::dwrd) to be missing.
    RxmAlm()
    {
        field_dwrd().setMissing();
    }

    /// @brief Copy constructor
    RxmAlm(const RxmAlm&) = default;

    /// @brief Move constructor
    RxmAlm(RxmAlm&& other) = default;

    /// @brief Destructor
    virtual ~RxmAlm() = default;

    /// @brief Copy assignment
    RxmAlm& operator=(const RxmAlm&) = default;

    /// @brief Move assignment
    RxmAlm& operator=(RxmAlm&&) = default;


    /// @brief Provides custom read functionality.
    /// @details The existence of "dwrd" (see @ref RxmAlmFields::dwrd) is
    ///     determined by the contents of "week" (see @ref RxmAlmFields::week)
    ///     field. If the value of the latter is 0, the "dwrd" is marked to
    ///     be missing, otherwise it exists.
    template <typename TIter>
    comms::ErrorStatus doRead(TIter& iter, std::size_t len)
    {
        auto es = Base::template readFieldsUntil<FieldIdx_dwrd>(iter, len);
        if (es != comms::ErrorStatus::Success) {
            return es;
        }

        auto& allFields = Base::fields();
        auto& weekField = std::get<FieldIdx_week>(allFields);
        auto dataMode = comms::field::OptionalMode::Exists;
        if (weekField.value() == 0U) {
            dataMode = comms::field::OptionalMode::Missing;
        }

        auto& dataField = std::get<FieldIdx_dwrd>(allFields);
        dataField.setMode(dataMode);
        return Base::template readFieldsFrom<FieldIdx_dwrd>(iter, len);
    }

    /// @brief Provides custom refresh functionality
    /// @details The existence of "dwrd" (see @ref RxmAlmFields::dwrd) is
    ///     determined by the contents of "week" (see @ref RxmAlmFields::week)
    ///     field. If the value of the latter is 0, the "dwrd" is marked to
    ///     be missing, otherwise it exists.
    /// @return @b true in case the mode of "dwrd" field was modified, @b false otherwise
    bool doRefresh()
    {
        auto& allFields = Base::fields();
        auto& weekField = std::get<FieldIdx_week>(allFields);
        auto expectedMode = comms::field::OptionalMode::Exists;
        if (weekField.value() == 0U) {
            expectedMode = comms::field::OptionalMode::Missing;
        }

        auto& dataField = std::get<FieldIdx_dwrd>(allFields);
        if (dataField.getMode() == expectedMode) {
            return false;
        }

        dataField.setMode(expectedMode);
        return true;
    }

};


}  // namespace message

}  // namespace ublox





