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
/// @brief Contains definition of NAV-SBAS message and its fields.

#pragma once

#include <algorithm>

#include "ublox/Message.h"
#include "ublox/field/nav.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the NAV-SBAS message fields.
/// @see NavSbas
struct NavSbasFields
{
    /// @brief Value enumeration for @ref mode field.
    enum class Mode : std::uint8_t
    {
        Disabled, ///< disabled
        EnabledIntegrity, ///< enabled integrity
        EnabledTestmode = 3 ///< enabled testmode
    };

    /// @brief Value enumeration for @ref sys field.
    enum class Sys : std::int8_t
    {
        Unknown = -1, ///< Unknown
        WAAS = 0, ///< WAAS
        EGNOS = 1, ///< EGNOS
        MSAS = 2, ///< MSAS
        GPS = 16, ///< GPS
    };

    /// @brief Custom validator for @ref mode field.
    struct ModeValidator
    {
        template <typename TField>
        bool operator()(const TField& field) const
        {
            auto value = field.value();
            return
                (value == Mode::Disabled) ||
                (value == Mode::EnabledIntegrity) ||
                (value == Mode::EnabledTestmode);
        }
    };

    /// @brief Custom validator for @ref sys field.
    struct SysValidator
    {
        template <typename TField>
        bool operator()(const TField& field) const
        {
            static const Sys Values[] = {
                Sys::Unknown,
                Sys::WAAS,
                Sys::EGNOS,
                Sys::MSAS,
                Sys::GPS,
            };

            auto value = field.value();
            auto iter = std::lower_bound(std::begin(Values), std::end(Values), value);
            return (iter != std::end(Values)) && (*iter == value);
        }
    };

    /// @brief Definition of "iTOW" field.
    using iTOW = field::nav::iTOW;

    /// @brief Definition of "geo" field.
    using geo = field::common::U1;

    /// @brief Definition of "mode" field.
    using mode =
        field::common::EnumT<
            Mode,
            comms::option::ContentsValidator<ModeValidator>
        >;

    /// @brief Definition of "sys" field.
    using sys =
        field::common::EnumT<
            Sys,
            comms::option::ContentsValidator<SysValidator>
        >;

    /// @brief Definition of "service" field.
    struct service : public
        field::common::X1T<
            comms::option::BitmaskReservedBits<0xf0, 0>
        >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS(Ranging, Corrections, Integrity, Testmode);
    };

    /// @brief Definition of "cnt" field.
    using cnt = field::common::U1;

    /// @brief Definition of "reserved0" field.
    using reserved0 = field::common::res3;

    /// @brief Definition of "svid" field.
    using svid = field::nav::svid;

    /// @brief Definition of "flags" field.
    using flags = field::common::U1;

    /// @brief Definition of "udre" field.
    using udre = field::common::U1;

    /// @brief Definition of "svSys" field.
    using svSys = sys;

    /// @brief Definition of "svService" field.
    using svService = service;

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res1;

    /// @brief Definition of "prc" field.
    using prc = field::common::U2T<field::common::Scaling_cm2m>;

    /// @brief Definition of "reserved2" field.
    using reserved2 = field::common::res2;

    /// @brief Definition of "ic" field.
    using ic = field::common::U2T<field::common::Scaling_cm2m>;

    /// @brief Definition of the block of fields used in @ref data list
    struct block : public
        field::common::BundleT<
            std::tuple<
                svid,
                flags,
                udre,
                svSys,
                svService,
                reserved1,
                prc,
                reserved2,
                ic
            >
        >
    {
        /// @brief Allow access to internal fields.
        /// @details See definition of @b COMMS_FIELD_MEMBERS_ACCESS macro
        ///     related to @b comms::field::Bitfield class from COMMS library
        ///     for details.
        COMMS_FIELD_MEMBERS_ACCESS(svid, flags, udre, svSys, svService, reserved1, prc, reserved2, ic);
    };

    /// @brief Definition of the list of data blocks (@ref block).
    /// @tparam TOpt Extra option(s)
    template <typename TOpt = comms::option::EmptyOption>
    using data =
        field::common::ListT<
            block,
            comms::option::SequenceSizeForcingEnabled,
            TOpt
        >;

    /// @brief All the fields bundled in std::tuple.
    /// @tparam TOpt Extra option(s) for @ref data field
    template <typename TOpt>
    using All = std::tuple<
        iTOW,
        geo,
        mode,
        sys,
        service,
        cnt,
        reserved0,
        data<TOpt>
    >;
};

/// @brief Definition of NAV-SBAS message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref NavSbasFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
/// @tparam TDataOpt Extra option(s) for @b data field
template <typename TMsgBase = Message, typename TDataOpt = comms::option::EmptyOption>
class NavSbas : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_SBAS>,
        comms::option::FieldsImpl<NavSbasFields::All<TDataOpt> >,
        comms::option::MsgType<NavSbas<TMsgBase, TDataOpt> >,
        comms::option::HasDoRefresh
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_SBAS>,
        comms::option::FieldsImpl<NavSbasFields::All<TDataOpt> >,
        comms::option::MsgType<NavSbas<TMsgBase, TDataOpt> >,
        comms::option::HasDoRefresh
    > Base;
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b iTOW for @ref NavSbasFields::iTOW field
    ///     @li @b geo for @ref NavSbasFields::geo field
    ///     @li @b mode for @ref NavSbasFields::mode field
    ///     @li @b sys for @ref NavSbasFields::sys field
    ///     @li @b service for @ref NavSbasFields::service field
    ///     @li @b cnt for @ref NavSbasFields::cnt field
    ///     @li @b reserved0 for @ref NavSbasFields::reserved0 field
    ///     @li @b data for @ref NavSbasFields::data field
    COMMS_MSG_FIELDS_ACCESS(iTOW, geo, mode, sys, service, cnt, reserved0, data);

    /// @brief Default constructor
    NavSbas() = default;

    /// @brief Copy constructor
    NavSbas(const NavSbas&) = default;

    /// @brief Move constructor
    NavSbas(NavSbas&& other) = default;

    /// @brief Destructor
    virtual ~NavSbas() = default;

    /// @brief Copy assignment
    NavSbas& operator=(const NavSbas&) = default;

    /// @brief Move assignment
    NavSbas& operator=(NavSbas&&) = default;

    /// @brief Provides custom read functionality.
    /// @details The number of blocks (@ref NavSbasFields::block) in
    ///     the @b data (@ref NavSbasFields::data) list is determined by the
    ///     value of @b cnt (@ref NavSbasFields::cnt) field.
    template <typename TIter>
    comms::ErrorStatus doRead(TIter& iter, std::size_t len)
    {
        auto es = Base::template readFieldsUntil<FieldIdx_data>(iter, len);
        if (es != comms::ErrorStatus::Success) {
            return es;
        }

        auto& allFields = Base::fields();
        auto& cntField = std::get<FieldIdx_cnt>(allFields);
        auto& dataField = std::get<FieldIdx_data>(allFields);
        dataField.forceReadElemCount(cntField.value());

        return Base::template readFieldsFrom<FieldIdx_data>(iter, len);
    }

    /// @brief Provides custom refresh functionality
    /// @details The value of @b cnt (@ref NavSbasFields::cnt) field is
    ///     determined by the amount of elements (blocks) stored in
    ///     the @b data (@ref NavSbasFields::data) list.
    /// @return @b true in case the value of "cnt" field was modified, @b false otherwise
    bool doRefresh()
    {
        auto& allFields = Base::fields();
        auto& cntField = std::get<FieldIdx_cnt>(allFields);
        auto& dataField = std::get<FieldIdx_data>(allFields);
        if (cntField.value() == dataField.value().size()) {
            return false;
        }

        cntField.value() = dataField.value().size();
        return true;
    }

};


}  // namespace message

}  // namespace ublox





