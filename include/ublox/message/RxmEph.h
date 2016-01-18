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

#include "ublox/field/rxm.h"

namespace ublox
{

namespace message
{

using RxmEphField_svid = field::rxm::svid_ext;
using RxmEphField_how = field::common::U4;
using RxmEphField_sf1d =
    field::common::OptionalT<
        field::common::ListT<
            field::common::U4,
            comms::option::SequenceFixedSize<8>
        >
    >;
using RxmEphField_sf2d = RxmEphField_sf1d;
using RxmEphField_sf3d = RxmEphField_sf1d;

using RxmEphFields = std::tuple<
    RxmEphField_svid,
    RxmEphField_how,
    RxmEphField_sf1d,
    RxmEphField_sf2d,
    RxmEphField_sf3d
>;

template <typename TMsgBase = Message>
class RxmEph : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_RXM_EPH>,
        comms::option::FieldsImpl<RxmEphFields>,
        comms::option::DispatchImpl<RxmEph<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_RXM_EPH>,
        comms::option::FieldsImpl<RxmEphFields>,
        comms::option::DispatchImpl<RxmEph<TMsgBase> >
    > Base;
public:

    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_svid,
        FieldIdx_how,
        FieldIdx_sf1d,
        FieldIdx_sf2d,
        FieldIdx_sf3d,
        FieldIdx_numOfValues ///< number of available fields
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    /// @brief Default constructor
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





