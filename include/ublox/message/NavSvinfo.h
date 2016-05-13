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
/// @details Inherits from
///     <a href="https://dl.dropboxusercontent.com/u/46999418/comms_champion/comms/html/classcomms_1_1MessageBase.html">comms::MessageBase</a>
///     while providing @b TMsgBase as common interface class as well as
///     @b comms::option::StaticNumIdImpl, @b comms::option::FieldsImpl, and
///     @b comms::option::DispatchImpl as options. @n
///     See @ref NavSvinfoFields and for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class NavSvinfo : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_SVINFO>,
        comms::option::FieldsImpl<NavSvinfoFields::All>,
        comms::option::DispatchImpl<NavSvinfo<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_SVINFO>,
        comms::option::FieldsImpl<NavSvinfoFields::All>,
        comms::option::DispatchImpl<NavSvinfo<TMsgBase> >
    > Base;
public:

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

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

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

protected:

    /// @brief Overrides read functionality provided by the base class.
    /// @details The number of blocks in @b data (@ref NavSvinfoFields::data)
    ///     list is determined by the value of @b numCh (@ref NavSvinfoFields::numCh)
    ///     field.
    virtual comms::ErrorStatus readImpl(
        typename Base::ReadIterator& iter,
        std::size_t len) override
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

    /// @brief Overrides default refreshing functionality provided by the interface class.
    /// @details The value of @b numCh (@ref NavSvinfoFields::numCh) field is
    ///     determined by number of blocks stored in @b data (@ref NavSvinfoFields::data)
    ///     list.
    /// @return @b true in case the value of "numCh" field was modified, @b false otherwise
    virtual bool refreshImpl() override
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





