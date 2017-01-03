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
/// @brief Contains definition of NAV-SVINFO message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/nav.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the NAV-SVINFO message fields.
/// @see NavSvinfo
struct NavSvinfoFields
{
    /// @brief Value enumeration for @ref chipGen field.
    enum class ChipGen : std::uint8_t
    {
        Antaris, ///< Antaris
        Ublox5, ///< u-blox 5
        Ublox6, ///< u-blox 6
        NumOfValues /// number of available values
    };

    /// @brief Value enumeration for @ref quality field.
    enum class QualityInd : std::uint8_t
    {
        Idle, ///< idle
        Searching, ///< searching
        SignalAcquired, ///< signal acquired
        SignalUnusable, ///< signal unusable
        CodeLock, ///< code lock on signal
        CodeCarrierLocked, ///< code and carrier locked
        CodeCarrierLocked2, ///< code and carrier locked
        CodeCarrierLocked3, ///< code and carrier locked
        NumOfValues ///< number of available values
    };

    enum {
        globalFlags_chipGen,
        globalFlags_reserved,
        globalFlags_numOfValues
    };

    /// @brief Bits access enumeration for bits in @b flags bitmask field.
    enum {
        flags_svUsed, ///< @b svUsed bit index
        flags_diffCorr, ///< @b diffCorr bit index
        flags_orbitAvail, ///< @b orbitAvail bit index
        flags_orbitEph, ///< @b orbitEph bit index
        flags_unhealthy, ///< @b unhealthy bit index
        flags_orbitAlm, ///< @b orbitAlm bit index
        flags_orbitAop, ///< @b orbitAop bit index
        flags_smoothed, ///< @b smoothed bit index
        flags_numOfValues ///< number of available bits
    };

    /// @brief Use this enumeration to access member fields of @ref block bundle.
    enum {
        block_chn, ///< index of @ref chn member field.
        block_svid, ///< index of @ref svid member field.
        block_flags, ///< index of @ref flags member field.
        block_quality, ///< index of @ref quality member field.
        block_cno, ///< index of @ref cno member field.
        block_elev, ///< index of @ref elev member field.
        block_azim, ///< index of @ref azim member field.
        block_prRes, ///< index of @ref prRes member field.
        block_numOfValues ///< number of available member fields.
    };

    /// @brief Definition of "iTOW" field.
    using iTOW = field::nav::iTOW;

    /// @brief Definition of "numCh" field.
    using numCh = field::nav::numCh;

    /// @brief Definition of "chipGen" member field of @ref globalFlags bitfield.
    using chipGen =
        field::common::EnumT<
            ChipGen,
            comms::option::FixedBitLength<3>,
            comms::option::ValidNumValueRange<0, (int)ChipGen::NumOfValues - 1>
        >;

    /// @brief Definition of "globalFlags" field.
    using globalFlags =
        field::common::BitfieldT<
            std::tuple<
                chipGen,
                field::common::res1T<comms::option::FixedBitLength<5> >
            >
        >;

    /// @brief Definition of "reserved2" field.
    using reserved2 = field::common::res2;

    /// @brief Definition of "chn" field.
    using chn = field::common::U1;

    /// @brief Definition of "svid" field.
    using svid = field::nav::svid;

    /// @brief Definition of "flags" field.
    using flags = field::common::X1;

    /// @brief Definition of "quality" field.
    using quality =
        field::common::EnumT<
            QualityInd,
            comms::option::ValidNumValueRange<0, (int)QualityInd::NumOfValues - 1>
        >;

    /// @brief Definition of "cno" field.
    using cno = field::common::U1;

    /// @brief Definition of "elev" field.
    using elev = field::common::I1;

    /// @brief Definition of "azim" field.
    using azim = field::common::I2;

    /// @brief Definition of "prRes" field.
    using prRes = field::common::I4T<field::common::Scaling_cm2m>;

    /// @brief Definition of a block field repeated multiple times in @ref
    ///     data list.
    using block =
        field::common::BundleT<
            std::tuple<
                chn,
                svid,
                flags,
                quality,
                cno,
                elev,
                azim,
                prRes
            >
        >;

    /// @brief Definition of "data" field as list of blocks (@ref block).
    using data =
        field::common::ListT<
            block,
            comms::option::SequenceSizeForcingEnabled
        >;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        iTOW,
        numCh,
        globalFlags,
        reserved2,
        data
    >;
};

/// @brief Definition of NAV-SVINFO message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref NavSvinfoFields and for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class NavSvinfo : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_SVINFO>,
        comms::option::FieldsImpl<NavSvinfoFields::All>,
        comms::option::MsgType<NavSvinfo<TMsgBase> >,
        comms::option::DispatchImpl,
        comms::option::MsgDoRead,
        comms::option::MsgDoRefresh
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_SVINFO>,
        comms::option::FieldsImpl<NavSvinfoFields::All>,
        comms::option::MsgType<NavSvinfo<TMsgBase> >,
        comms::option::DispatchImpl,
        comms::option::MsgDoRead,
        comms::option::MsgDoRefresh
    > Base;
public:

#ifdef FOR_DOXYGEN_DOC_ONLY
    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_iTOW, ///< @b iTOW field, see @ref NavSvinfoFields::iTOW
        FieldIdx_numCh, ///< @b numCh field, see @ref NavSvinfoFields::numCh
        FieldIdx_globalFlags, ///< @b globalFlags field, see @ref NavSvinfoFields::globalFlags
        FieldIdx_reserved2, ///< @b reserved2 field, see @ref NavSvinfoFields::reserved2
        FieldIdx_data, ///< @b data field, see @ref NavSvinfoFields::data
        FieldIdx_numOfValues ///< number of available fields
    };

    /// @brief Access to fields bundled as a struct
    struct FieldsAsStruct
    {
        NavSvinfoFields::iTOW& iTOW; ///< @b iTOW field, see @ref NavSvinfoFields::iTOW
        NavSvinfoFields::numCh& numCh; ///< @b numCh field, see @ref NavSvinfoFields::numCh
        NavSvinfoFields::globalFlags& globalFlags; ///< @b globalFlags field, see @ref NavSvinfoFields::globalFlags
        NavSvinfoFields::reserved2& reserved2; ///< @b reserved2 field, see @ref NavSvinfoFields::reserved2
        NavSvinfoFields::data& data; ///< @b data field, see @ref NavSvinfoFields::data
    };

    /// @brief Access to @b const fields bundled as a struct
    struct ConstFieldsAsStruct
    {
        const NavSvinfoFields::iTOW& iTOW; ///< @b iTOW field, see @ref NavSvinfoFields::iTOW
        const NavSvinfoFields::numCh& numCh; ///< @b numCh field, see @ref NavSvinfoFields::numCh
        const NavSvinfoFields::globalFlags& globalFlags; ///< @b globalFlags field, see @ref NavSvinfoFields::globalFlags
        const NavSvinfoFields::reserved2& reserved2; ///< @b reserved2 field, see @ref NavSvinfoFields::reserved2
        const NavSvinfoFields::data& data; ///< @b data field, see @ref NavSvinfoFields::data
    };

    /// @brief Get access to fields bundled into a struct
    FieldsAsStruct fieldsAsStruct();

    /// @brief Get access to @b const fields bundled into a struct
    ConstFieldsAsStruct fieldsAsStruct() const;

#else
    COMMS_MSG_FIELDS_ACCESS(Base, iTOW, numCh, globalFlags, reserved2, data);
#endif // #ifdef FOR_DOXYGEN_DOC_ONLY

    /// @brief Default constructor
    NavSvinfo() = default;

    /// @brief Copy constructor
    NavSvinfo(const NavSvinfo&) = default;

    /// @brief Move constructor
    NavSvinfo(NavSvinfo&& other) = default;

    /// @brief Destructor
    virtual ~NavSvinfo() = default;

    /// @brief Copy assignment
    NavSvinfo& operator=(const NavSvinfo&) = default;

    /// @brief Move assignment
    NavSvinfo& operator=(NavSvinfo&&) = default;

    /// @brief Provides custom read functionality.
    /// @details The number of blocks in @b data (@ref NavSvinfoFields::data)
    ///     list is determined by the value of @b numCh (@ref NavSvinfoFields::numCh)
    ///     field.
    template <typename TIter>
    comms::ErrorStatus doRead(TIter& iter, std::size_t len)
    {
        auto es = Base::template readFieldsUntil<FieldIdx_data>(iter, len);
        if (es != comms::ErrorStatus::Success) {
            return es;
        }

        auto& allFields = Base::fields();
        auto& numChField = std::get<FieldIdx_numCh>(allFields);
        auto& dataField = std::get<FieldIdx_data>(allFields);
        dataField.forceReadElemCount(numChField.value());

        return Base::template readFieldsFrom<FieldIdx_data>(iter, len);
    }

    /// @brief Provides custom refresh functionality
    /// @details The value of @b numCh (@ref NavSvinfoFields::numCh) field is
    ///     determined by number of blocks stored in @b data (@ref NavSvinfoFields::data)
    ///     list.
    /// @return @b true in case the value of "numCh" field was modified, @b false otherwise
    bool doRefresh()
    {
        auto& allFields = Base::fields();
        auto& numChField = std::get<FieldIdx_numCh>(allFields);
        auto& dataField = std::get<FieldIdx_data>(allFields);
        if (numChField.value() == dataField.value().size()) {
            return false;
        }

        numChField.value() = dataField.value().size();
        return true;
    }

};


}  // namespace message

}  // namespace ublox





