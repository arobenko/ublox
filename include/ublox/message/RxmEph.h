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
/// @brief Contains definition of RXM-EPH message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/rxm.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the RXM-EPH message fields.
/// @see RxmEph
struct RxmEphFields
{
    /// @brief Definition of "svid" field.
    using svid = field::rxm::svid_ext;

    /// @brief Definition of "how" field.
    using how = field::common::U4;

    /// @brief Definition of "sf1d" field.
    using sf1d =
        field::common::OptionalT<
            field::common::ListT<
                field::common::U4,
                comms::option::SequenceFixedSize<8>
            >
        >;

    /// @brief Definition of "sf2d" field.
    using sf2d = sf1d;

    /// @brief Definition of "sf3d" field.
    using sf3d = sf1d;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        svid,
        how,
        sf1d,
        sf2d,
        sf3d
    >;
};

/// @brief Definition of RXM-EPH message
/// @details Inherits from
///     <a href="https://dl.dropboxusercontent.com/u/46999418/comms_champion/comms/html/classcomms_1_1MessageBase.html">comms::MessageBase</a>
///     while providing @b TMsgBase as common interface class as well as
///     @b comms::option::StaticNumIdImpl, @b comms::option::FieldsImpl, and
///     @b comms::option::DispatchImpl as options. @n
///     See @ref RxmEphFields and for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class RxmEph : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_RXM_EPH>,
        comms::option::FieldsImpl<RxmEphFields::All>,
        comms::option::DispatchImpl<RxmEph<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_RXM_EPH>,
        comms::option::FieldsImpl<RxmEphFields::All>,
        comms::option::DispatchImpl<RxmEph<TMsgBase> >
    > Base;
public:

    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_svid, ///< svid field, see @ref RxmEphFields::svid
        FieldIdx_how, ///< how field, see @ref RxmEphFields::how
        FieldIdx_sf1d, ///< sf1d field, see @ref RxmEphFields::sf1d
        FieldIdx_sf2d, ///< sf2d field, see @ref RxmEphFields::sf2d
        FieldIdx_sf3d, ///< sf3d field, see @ref RxmEphFields::sf3d
        FieldIdx_numOfValues ///< number of available fields
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    /// @brief Default constructor
    /// @details Marks "sf1d" (see @ref RxmEphFields::sf1d),
    ///     "sf2d" (see @ref RxmEphFields::sf2d), and "sf3d" (see @ref RxmEphFields::sf3d)
    ///     fields to be missing.
    RxmEph()
    {
        auto& allFields = Base::fields();
        auto& sf1dField = std::get<FieldIdx_sf1d>(allFields);
        auto& sf2dField = std::get<FieldIdx_sf2d>(allFields);
        auto& sf3dField = std::get<FieldIdx_sf3d>(allFields);
        sf1dField.setMode(comms::field::OptionalMode::Missing);
        sf2dField.setMode(comms::field::OptionalMode::Missing);
        sf3dField.setMode(comms::field::OptionalMode::Missing);
    }

    /// @brief Copy constructor
    RxmEph(const RxmEph&) = default;

    /// @brief Move constructor
    RxmEph(RxmEph&& other) = default;

    /// @brief Destructor
    virtual ~RxmEph() = default;

    /// @brief Copy assignment
    RxmEph& operator=(const RxmEph&) = default;

    /// @brief Move assignment
    RxmEph& operator=(RxmEph&&) = default;

protected:

    /// @brief Overrides read functionality provided by the base class.
    /// @details The existence of "sf1d" (see @ref RxmEphFields::sf1d),
    ///     "sf2d" (see @ref RxmEphFields::sf2d), and "sf3d" (see @ref RxmEphFields::sf3d)
    ///     is determined by the contents of "how" (see @ref RxmEphFields::how)
    ///     field. If the value of the latter is 0, the "sfXd" fields are marked to
    ///     be missing, otherwise they exist.
    virtual comms::ErrorStatus readImpl(
        typename Base::ReadIterator& iter,
        std::size_t len) override
    {
        auto es = Base::template readFieldsUntil<FieldIdx_sf1d>(iter, len);
        if (es != comms::ErrorStatus::Success) {
            return es;
        }

        auto& allFields = Base::fields();
        auto& howField = std::get<FieldIdx_how>(allFields);
        auto sfMode = comms::field::OptionalMode::Exists;
        if (howField.value() == 0U) {
            sfMode = comms::field::OptionalMode::Missing;
        }

        auto& sf1dField = std::get<FieldIdx_sf1d>(allFields);
        auto& sf2dField = std::get<FieldIdx_sf2d>(allFields);
        auto& sf3dField = std::get<FieldIdx_sf3d>(allFields);
        sf1dField.setMode(sfMode);
        sf2dField.setMode(sfMode);
        sf3dField.setMode(sfMode);
        return Base::template readFieldsFrom<FieldIdx_sf1d>(iter, len);
    }

    /// @brief Overrides default refreshing functionality provided by the interface class.
    /// @details The existence of "sf1d" (see @ref RxmEphFields::sf1d),
    ///     "sf2d" (see @ref RxmEphFields::sf2d), and "sf3d" (see @ref RxmEphFields::sf3d)
    ///     is determined by the contents of "how" (see @ref RxmEphFields::how)
    ///     field. If the value of the latter is 0, the "sfXd" fields are marked to
    ///     be missing, otherwise they exist.
    /// @return @b true in case the modes of "sfXd" fields were modified, @b false otherwise
    virtual bool refreshImpl() override
    {
        auto& allFields = Base::fields();
        auto& howField = std::get<FieldIdx_how>(allFields);
        auto expectedMode = comms::field::OptionalMode::Exists;
        if (howField.value() == 0U) {
            expectedMode = comms::field::OptionalMode::Missing;
        }

        auto& sf1dField = std::get<FieldIdx_sf1d>(allFields);
        auto& sf2dField = std::get<FieldIdx_sf2d>(allFields);
        auto& sf3dField = std::get<FieldIdx_sf3d>(allFields);
        if ((sf1dField.getMode() == expectedMode) &&
            (sf2dField.getMode() == expectedMode) &&
            (sf3dField.getMode() == expectedMode)){
            return false;
        }

        sf1dField.setMode(expectedMode);
        sf2dField.setMode(expectedMode);
        sf3dField.setMode(expectedMode);
        return true;
    }

};


}  // namespace message

}  // namespace ublox





