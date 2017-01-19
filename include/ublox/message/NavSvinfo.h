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

    /// @brief Base class of @ref globalFlags field
    using globalFlagsBase =
        field::common::BitfieldT<
            std::tuple<
                chipGen,
                field::common::res1T<comms::option::FixedBitLength<5> >
            >
        >;

    /// @brief Definition of "globalFlags" field.
    struct globalFlags : public globalFlagsBase
    {
        /// @brief Allow access to internal fields.
        /// @details See definition of @b COMMS_FIELD_MEMBERS_ACCESS macro
        ///     related to @b comms::field::Bitfield class from COMMS library
        ///     for details.
        COMMS_FIELD_MEMBERS_ACCESS(globalFlagsBase, chipGen, reserved);
    };

    /// @brief Definition of "reserved2" field.
    using reserved2 = field::common::res2;

    /// @brief Definition of "chn" field.
    using chn = field::common::U1;

    /// @brief Definition of "svid" field.
    using svid = field::nav::svid;

    /// @brief Definition of "flags" field.
    struct flags : public field::common::X1
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS(svUsed, diffCorr, orbitAvail, orbitEph, unhealthy, orbitAlm, orbitAop, smoothed);
    };

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

    /// @brief Base class of @ref block field.
    using blockBase =
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

    /// @brief Definition of a block field repeated multiple times in @ref
    ///     data list.
    struct block : public blockBase
    {
        /// @brief Allow access to internal fields.
        /// @details See definition of @b COMMS_FIELD_MEMBERS_ACCESS macro
        ///     related to @b comms::field::Bitfield class from COMMS library
        ///     for details.
        COMMS_FIELD_MEMBERS_ACCESS(blockBase, chn, svid, flags, quality, cno, elev, azim, prRes);
    };

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
///     See @ref NavSvinfoFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class NavSvinfo : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_SVINFO>,
        comms::option::FieldsImpl<NavSvinfoFields::All>,
        comms::option::MsgType<NavSvinfo<TMsgBase> >,
        comms::option::HasDoRefresh
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_SVINFO>,
        comms::option::FieldsImpl<NavSvinfoFields::All>,
        comms::option::MsgType<NavSvinfo<TMsgBase> >,
        comms::option::HasDoRefresh
    > Base;
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b iTOW for @ref NavSvinfoFields::iTOW field
    ///     @li @b numCh for @ref NavSvinfoFields::numCh field
    ///     @li @b globalFlags for @ref NavSvinfoFields::globalFlags field
    ///     @li @b reserved2 for @ref NavSvinfoFields::reserved2 field
    ///     @li @b data for @ref NavSvinfoFields::data field
    COMMS_MSG_FIELDS_ACCESS(Base, iTOW, numCh, globalFlags, reserved2, data);

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





