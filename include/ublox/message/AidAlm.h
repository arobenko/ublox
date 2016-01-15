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

#include <iterator>

#include "comms/Message.h"
#include "ublox/Message.h"

#include "ublox/field/aid.h"

namespace ublox
{

namespace message
{

/// @brief Definition of "svid" field in AID-ALM message.
using AidAlmField_svid = field::aid::svid_ext;

/// @brief Definition of "week" field in AID-ALM message.
using AidAlmField_week = field::common::U4;

/// @brief Definition of "dwrd" field in AID-ALM message.
/// @details The field is defined to be
///     <a href="https://dl.dropboxusercontent.com/u/46999418/comms_champion/comms/html/classcomms_1_1field_1_1Optional.html">comms::field::Optional</a> that
///     wraps
///     <a href="https://dl.dropboxusercontent.com/u/46999418/comms_champion/comms/html/classcomms_1_1field_1_1ArrayList.html">comms::field::ArrayList</a>
///     of 4 byte unsigned integer value fields, which
///     has fixed size of 8 elements.
using AidAlmField_dwrd =
    comms::field::Optional<
        comms::field::ArrayList<
            field::common::FieldBase,
            field::common::U4,
            comms::option::SequenceFixedSize<8>
        >
    >;

/// @brief Definition of the fields for AID-ALM message.
/// @see AidAlm
using AidAlmFields = std::tuple<
    AidAlmField_svid,
    AidAlmField_week,
    AidAlmField_dwrd
>;

/// @brief Definition of AID-ALM message
/// @details Inherits from
///     <a href="https://dl.dropboxusercontent.com/u/46999418/comms_champion/comms/html/classcomms_1_1MessageBase.html">comms::MessageBase</a>
///     while providing @b TMsgBase as common interface class as well as
///     @b comms::option::StaticNumIdImpl, @b comms::option::FieldsImpl, and
///     @b comms::option::DispatchImpl as options. @n
///     See @ref AidAlmFields for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class AidAlm : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_AID_ALM>,
        comms::option::FieldsImpl<AidAlmFields>,
        comms::option::DispatchImpl<AidAlm<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_AID_ALM>,
        comms::option::FieldsImpl<AidAlmFields>,
        comms::option::DispatchImpl<AidAlm<TMsgBase> >
    > Base;
public:

    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_svid, ///< svid field, see @ref AidAlmField_svid
        FieldIdx_week, ///< week field, see @ref AidAlmField_week
        FieldIdx_dwrd, ///< dwrd field, see @ref AidAlmField_dwrd
        FieldIdx_numOfValues ///< number of available fields
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    /// @brief Default constructor
    /// @details Marks "dwrd" (see @ref AidAlmField_dwrd) to be missing.
    AidAlm()
    {
        auto& allFields = Base::fields();
        auto& dataField = std::get<FieldIdx_dwrd>(allFields);
        dataField.setMode(comms::field::OptionalMode::Missing);
    }

    /// @brief Copy constructor
    AidAlm(const AidAlm&) = default;

    /// @brief Move constructor
    AidAlm(AidAlm&& other) = default;

    /// @brief Destructor
    virtual ~AidAlm() = default;

    /// @brief Copy assignment
    AidAlm& operator=(const AidAlm&) = default;

    /// @brief Move assignment
    AidAlm& operator=(AidAlm&&) = default;

protected:

    /// @brief Overrides read functionality provided by the base class.
    /// @details The existence of "dwrd" (see @ref AidAlmField_dwrd) is
    ///     determined by the contents of "week" (see @ref AidAlmField_week)
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
    /// @details The existence of "dwrd" (see @ref AidAlmField_dwrd) is
    ///     determined by the contents of "week" (see @ref AidAlmField_week)
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





