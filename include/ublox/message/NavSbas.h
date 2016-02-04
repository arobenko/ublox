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

    /// @brief Bits access enumeration for bits in @b service bitmask field
    enum
    {
        service_Ranging, ///< @b Ranging bit index
        service_Corrections, ///< @b Corrections bit index
        service_Integrity, ///< @b Integrity bit index
        service_Testmode,///< @b Testmode bit index
        service_NumOfValues ///< number of available bits
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
    using service =
        field::common::X1T<
            comms::option::BitmaskReservedBits<0xf0, 0>
        >;

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
    using block =
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
        >;

    /// @brief Definition of the list of data blocks (@ref block).
    using data =
        field::common::ListT<
            block,
            comms::option::SequenceSizeForcingEnabled
        >;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        iTOW,
        geo,
        mode,
        sys,
        service,
        cnt,
        reserved0,
        data
    >;
};

/// @brief Definition of NAV-SBAS message
/// @details Inherits from
///     <a href="https://dl.dropboxusercontent.com/u/46999418/comms_champion/comms/html/classcomms_1_1MessageBase.html">comms::MessageBase</a>
///     while providing @b TMsgBase as common interface class as well as
///     @b comms::option::StaticNumIdImpl, @b comms::option::FieldsImpl, and
///     @b comms::option::DispatchImpl as options. @n
///     See @ref NavSbasFields and for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class NavSbas : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_SBAS>,
        comms::option::FieldsImpl<NavSbasFields::All>,
        comms::option::DispatchImpl<NavSbas<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_SBAS>,
        comms::option::FieldsImpl<NavSbasFields::All>,
        comms::option::DispatchImpl<NavSbas<TMsgBase> >
    > Base;
public:

    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_iTOW, ///< @b iTOW field, see @ref NavSbasFields::iTOW
        FieldIdx_geo, ///< @b geo field, see @ref NavSbasFields::geo
        FieldIdx_mode, ///< @b mode field, see @ref NavSbasFields::mode
        FieldIdx_sys, ///< @b sys field, see @ref NavSbasFields::sys
        FieldIdx_service, ///< @b service field, see @ref NavSbasFields::service
        FieldIdx_cnt, ///< @b cnt field, see @ref NavSbasFields::cnt
        FieldIdx_reserved0, ///< @b reserved0 field, see @ref NavSbasFields::reserved0
        FieldIdx_data, ///< @b data field, see @ref NavSbasFields::data
        FieldIdx_numOfValues ///< number of available fields
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

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

protected:

    /// @brief Overrides read functionality provided by the base class.
    /// @details The number of blocks (@ref NavSbasFields::block) in
    ///     the @b data (@ref NavSbasFields::data) list is determined by the
    ///     value of @b cnt (@ref NavSbasFields::cnt) field.
    virtual comms::ErrorStatus readImpl(
        typename Base::ReadIterator& iter,
        std::size_t len) override
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

    /// @brief Overrides default refreshing functionality provided by the interface class.
    /// @details The value of @b cnt (@ref NavSbasFields::cnt) field is
    ///     determined by the amount of elements (blocks) stored in
    ///     the @b data (@ref NavSbasFields::data) list.
    /// @return @b true in case the value of "cnt" field was modified, @b false otherwise
    virtual bool refreshImpl() override
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





