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
/// @details Inherits from
///     <a href="https://dl.dropboxusercontent.com/u/46999418/comms_champion/comms/html/classcomms_1_1MessageBase.html">comms::MessageBase</a>
///     while providing @b TMsgBase as common interface class as well as
///     @b comms::option::StaticNumIdImpl, @b comms::option::FieldsImpl, and
///     @b comms::option::DispatchImpl as options. @n
///     See @ref RxmAlmFields and for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class RxmAlm : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_RXM_ALM>,
        comms::option::FieldsImpl<RxmAlmFields::All>,
        comms::option::DispatchImpl<RxmAlm<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_RXM_ALM>,
        comms::option::FieldsImpl<RxmAlmFields::All>,
        comms::option::DispatchImpl<RxmAlm<TMsgBase> >
    > Base;
public:

    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_svid, ///< svid field, see @ref RxmAlmFields::svid
        FieldIdx_week, ///< week field, see @ref RxmAlmFields::week
        FieldIdx_dwrd, ///< dwrd field, see @ref RxmAlmFields::dwrd
        FieldIdx_numOfValues ///< number of available fields
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    /// @brief Default constructor
    /// @details Marks "dwrd" (see @ref RxmAlmFields::dwrd) to be missing.
    RxmAlm()
    {
        auto& allFields = Base::fields();
        auto& dataField = std::get<FieldIdx_dwrd>(allFields);
        dataField.setMode(comms::field::OptionalMode::Missing);
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

protected:

    /// @brief Overrides read functionality provided by the base class.
    /// @details The existence of "dwrd" (see @ref RxmAlmFields::dwrd) is
    ///     determined by the contents of "week" (see @ref RxmAlmFields::week)
    ///     field. If the value of the latter is 0, the "dwrd" is marked to
    ///     be missing, otherwise it exists.
    virtual comms::ErrorStatus readImpl(
        typename Base::ReadIterator& iter,
        std::size_t len) override
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

    /// @brief Overrides default refreshing functionality provided by the interface class.
    /// @details The existence of "dwrd" (see @ref RxmAlmFields::dwrd) is
    ///     determined by the contents of "week" (see @ref RxmAlmFields::week)
    ///     field. If the value of the latter is 0, the "dwrd" is marked to
    ///     be missing, otherwise it exists.
    /// @return @b true in case the mode of "dwrd" field was modified, @b false otherwise
    virtual bool refreshImpl() override
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





