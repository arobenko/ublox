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
/// @brief Contains definition of RXM-SVSI message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/rxm.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the RXM-SVSI message fields.
/// @see RxmSvsi
struct RxmSvsiFields
{
    /// @brief Use this enumeration to access member fields of @ref svFlag bitfield.
    enum
    {
        svFlag_ura, ///< index of @ref ura member field.
        svFlag_bits, ///< index of @ref svFlagBits member field.
        svFlag_numOfValues ///< number of available member fields.
    };

    /// @brief Bits access enumeration for bits in @b svFlagBits member of
    ///     @ref svFlag bitfield field.
    enum
    {
        svFlagBits_healthy, ///< @b healthy bit index
        svFlagBits_ephVal, ///< @b ephVal bit index
        svFlagBits_almVal, ///< @b almVal bit index
        svFlagBits_notAvail, ///< @b notAvail bit index
        svFlagBits_numOfValues ///< number of available bits
    };

    /// @brief Use this enumeration to access member fields of @ref age bitfield.
    enum
    {
        age_almAge, ///< index of @ref almAge member field.
        age_ephAge, ///< index of @ref ephAge member field.
        age_numOfValues  ///< number of available member fields.
    };

    /// @brief Use this enumeration to access member fields of @ref block bundle.
    enum
    {
        block_svid,
        block_svFlag,
        block_azim,
        block_elev,
        block_age,
        block_numOfValues
    };

    /// @brief Definition of "iTOW" field.
    using iTOW = field::rxm::iTOW;

    /// @brief Definition of "week" field.
    using week = field::rxm::week;

    /// @brief Definition of "iTOW" field.
    using numVis = field::common::U1;

    /// @brief Definition of "numSV" field.
    using numSV = field::rxm::numSV;

    /// @brief Definition of "svid" field.
    using svid = field::rxm::svid;

    /// @brief Definition of "ura" member field of @ref svFlag bitfield.
    using ura =
        field::common::U1T<
            comms::option::ValidNumValueRange<0, 15>,
            comms::option::FixedBitLength<4>
        >;

    /// @brief Definition of the remaining bits in @ref svFlag bitfield as a
    ///     single bitmask field.
    using svFlagBits =
        field::common::X1T<
            comms::option::FixedBitLength<4>
        >;

    /// @brief Definition of "svFlag" field.
    using svFlag =
        field::common::BitfieldT<
            std::tuple<
                ura,
                svFlagBits
            >
        >;

    /// @brief Definition of "azim" field.
    using azim = field::common::I2;

    /// @brief Definition of "elev" field.
    using elev = field::common::I1;

    /// @brief Definition of "almAge" member fields in @ref age bitfield.
    using almAge =
        field::common::U1T<
            comms::option::FixedBitLength<4>,
            comms::option::ValidNumValueRange<0, 15>
        >;

    /// @brief Definition of "ephAge" member fields in @ref age bitfield.
    using ephAge = almAge;

    /// @brief Definition of "age" field.
    using age =
        field::common::BitfieldT<
            std::tuple<
                almAge,
                ephAge
            >
        >;

    /// @brief Definition of a single block of @ref data list
    using block =
        field::common::BundleT<
            std::tuple<
                svid,
                svFlag,
                azim,
                elev,
                age
            >
        >;

    /// @brief Definition of the list of blocks (@ref block)
    using data =
        field::common::ListT<
            block,
            comms::option::SequenceSizeForcingEnabled
        >;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        iTOW,
        week,
        numVis,
        numSV,
        data
    >;
};

/// @brief Definition of RXM-SVSI message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref RxmSvsiFields and for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class RxmSvsi : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_RXM_SVSI>,
        comms::option::FieldsImpl<RxmSvsiFields::All>,
        comms::option::MsgType<RxmSvsi<TMsgBase> >,
        comms::option::HasDoRefresh
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_RXM_SVSI>,
        comms::option::FieldsImpl<RxmSvsiFields::All>,
        comms::option::MsgType<RxmSvsi<TMsgBase> >,
        comms::option::HasDoRefresh
    > Base;
public:

#ifdef FOR_DOXYGEN_DOC_ONLY
    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_iTOW, ///< @b iTOW field, see @ref RxmSvsiFields::iTOW
        FieldIdx_week, ///< @b week field, see @ref RxmSvsiFields::week
        FieldIdx_numVis, ///< @b numVis field, see @ref RxmSvsiFields::numVis
        FieldIdx_numSV, ///< @b numSV field, see @ref RxmSvsiFields::numSV
        FieldIdx_data, ///< @b data field, see @ref RxmSvsiFields::data
        FieldIdx_numOfValues ///< number of available fields
    };

    /// @brief Access to fields bundled as a struct
    struct FieldsAsStruct
    {
        RxmSvsiFields::iTOW& iTOW; ///< @b iTOW field, see @ref RxmSvsiFields::iTOW
        RxmSvsiFields::week& week; ///< @b week field, see @ref RxmSvsiFields::week
        RxmSvsiFields::numVis& numVis; ///< @b numVis field, see @ref RxmSvsiFields::numVis
        RxmSvsiFields::numSV& numSV; ///< @b numSV field, see @ref RxmSvsiFields::numSV
        RxmSvsiFields::data& data; ///< @b data field, see @ref RxmSvsiFields::data
    };

    /// @brief Access to @b const fields bundled as a struct
    struct ConstFieldsAsStruct
    {
        const RxmSvsiFields::iTOW& iTOW; ///< @b iTOW field, see @ref RxmSvsiFields::iTOW
        const RxmSvsiFields::week& week; ///< @b week field, see @ref RxmSvsiFields::week
        const RxmSvsiFields::numVis& numVis; ///< @b numVis field, see @ref RxmSvsiFields::numVis
        const RxmSvsiFields::numSV& numSV; ///< @b numSV field, see @ref RxmSvsiFields::numSV
        const RxmSvsiFields::data& data; ///< @b data field, see @ref RxmSvsiFields::data
    };

    /// @brief Get access to fields bundled into a struct
    FieldsAsStruct fieldsAsStruct();

    /// @brief Get access to @b const fields bundled into a struct
    ConstFieldsAsStruct fieldsAsStruct() const;

#else
    COMMS_MSG_FIELDS_ACCESS(Base, iTWO, week, numVis, numSV, data);
#endif // #ifdef FOR_DOXYGEN_DOC_ONLY

    /// @brief Default constructor
    RxmSvsi() = default;

    /// @brief Copy constructor
    RxmSvsi(const RxmSvsi&) = default;

    /// @brief Move constructor
    RxmSvsi(RxmSvsi&& other) = default;

    /// @brief Destructor
    virtual ~RxmSvsi() = default;

    /// @brief Copy assignment
    RxmSvsi& operator=(const RxmSvsi&) = default;

    /// @brief Move assignment
    RxmSvsi& operator=(RxmSvsi&&) = default;

    /// @brief Provides custom read functionality.
    /// @details Number of elements in @ref RxmSvsiFields::data depends on
    ///     the value in @ref RxmSvsiFields::numSV
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
    /// @details The value of @ref RxmSvsiFields::numSV field depends on
    ///     actual number of elements in @ref RxmSvsiFields::data.
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





