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
/// @brief Contains definition of AID-EPH message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/aid.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the AID-EPH message fields.
/// @see AidEph
struct AidEphFields
{
    /// @brief Definition of "svid" field.
    using svid = field::aid::svid_ext;

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

/// @brief Definition of AID-EPH message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref AidEphFields and for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class AidEph : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_AID_EPH>,
        comms::option::FieldsImpl<AidEphFields::All>,
        comms::option::MsgType<AidEph<TMsgBase> >,
        comms::option::DispatchImpl,
        comms::option::MsgDoRead,
        comms::option::MsgDoRefresh
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_AID_EPH>,
        comms::option::FieldsImpl<AidEphFields::All>,
        comms::option::MsgType<AidEph<TMsgBase> >,
        comms::option::DispatchImpl,
        comms::option::MsgDoRead,
        comms::option::MsgDoRefresh
    > Base;
public:

#ifdef FOR_DOXYGEN_DOC_ONLY
    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_svid, ///< svid field, see @ref AidEphFields::svid
        FieldIdx_how, ///< how field, see @ref AidEphFields::how
        FieldIdx_sf1d, ///< sf1d field, see @ref AidEphFields::sf1d
        FieldIdx_sf2d, ///< sf2d field, see @ref AidEphFields::sf2d
        FieldIdx_sf3d, ///< sf3d field, see @ref AidEphFields::sf3d
        FieldIdx_numOfValues ///< number of available fields
    };


    /// @brief Access to fields bundled as a struct
    struct FieldsAsStruct
    {
        AidEphFields::svid& svid; ///< svid field, see @ref AidEphFields::svid
        AidEphFields::how& how; ///< how field, see @ref AidEphFields::how
        AidEphFields::sf1d& sf1d; ///< sf1d field, see @ref AidEphFields::sf1d
        AidEphFields::sf2d& sf2d; ///< sf2d field, see @ref AidEphFields::sf2d
        AidEphFields::sf3d& sf3d; ///< sf3d field, see @ref AidEphFields::sf3d
    };

    /// @brief Access to @b const fields bundled as a struct
    struct ConstFieldsAsStruct
    {
        const AidEphFields::svid& svid; ///< svid field, see @ref AidEphFields::svid
        const AidEphFields::how& how; ///< how field, see @ref AidEphFields::how
        const AidEphFields::sf1d& sf1d; ///< sf1d field, see @ref AidEphFields::sf1d
        const AidEphFields::sf2d& sf2d; ///< sf2d field, see @ref AidEphFields::sf2d
        const AidEphFields::sf3d& sf3d; ///< sf3d field, see @ref AidEphFields::sf3d
    };

    /// @brief Get access to fields bundled into a struct
    FieldsAsStruct fieldsAsStruct();

    /// @brief Get access to @b const fields bundled into a struct
    ConstFieldsAsStruct fieldsAsStruct() const;

#else
    COMMS_MSG_FIELDS_ACCESS(Base, svid, how, sf1d, sf2d, sf3d);
#endif // #ifdef FOR_DOXYGEN_DOC_ONLY

    /// @brief Default constructor
    /// @details Marks "sf1d" (see @ref AidEphFields::sf1d),
    ///     "sf2d" (see @ref AidEphFields::sf2d), and "sf3d" (see @ref AidEphFields::sf3d)
    ///     fields to be missing.
    AidEph()
    {
        auto& allFields = Base::fields();
        auto& sf1dField = std::get<FieldIdx_sf1d>(allFields);
        auto& sf2dField = std::get<FieldIdx_sf2d>(allFields);
        auto& sf3dField = std::get<FieldIdx_sf3d>(allFields);
        sf1dField.setMissing();
        sf2dField.setMissing();
        sf3dField.setMissing();
    }

    /// @brief Copy constructor
    AidEph(const AidEph&) = default;

    /// @brief Move constructor
    AidEph(AidEph&& other) = default;

    /// @brief Destructor
    virtual ~AidEph() = default;

    /// @brief Copy assignment
    AidEph& operator=(const AidEph&) = default;

    /// @brief Move assignment
    AidEph& operator=(AidEph&&) = default;

    /// @brief Provides custom read functionality.
    /// @details The existence of "sf1d" (see @ref AidEphFields::sf1d),
    ///     "sf2d" (see @ref AidEphFields::sf2d), and "sf3d" (see @ref AidEphFields::sf3d)
    ///     is determined by the contents of "how" (see @ref AidEphFields::how)
    ///     field. If the value of the latter is 0, the "sfXd" fields are marked to
    ///     be missing, otherwise they exist.
    template <typename TIter>
    comms::ErrorStatus doRead(TIter& iter, std::size_t len)
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

    /// @brief Provides custom refresh functionality
    /// @details The existence of "sf1d" (see @ref AidEphFields::sf1d),
    ///     "sf2d" (see @ref AidEphFields::sf2d), and "sf3d" (see @ref AidEphFields::sf3d)
    ///     is determined by the contents of "how" (see @ref AidEphFields::how)
    ///     field. If the value of the latter is 0, the "sfXd" fields are marked to
    ///     be missing, otherwise they exist.
    /// @return @b true in case the modes of "sfXd" fields were modified, @b false otherwise
    bool doRefresh()
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





