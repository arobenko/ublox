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
/// @brief Contains definition of MON-HW2 message and its fields.

#pragma once

#include <algorithm>

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the MON-HW2 message fields.
/// @see MonHw2
struct MonHw2Fields
{
    /// @brief Value enumeration for @ref cfgSource field.
    enum class CfgSource : std::uint8_t
    {
        FlashImage = 102, ///< flash image
        OTP = 111, ///< OTP
        ConfigPins = 112, ///< config pins
        ROM = 114 ///< ROM
    };

    /// @brief Custom value validator for @ref cfgSource field.
    struct CfgSourceValidator
    {
        template <typename TField>
        bool operator()(const TField& field) const
        {
            static const CfgSource Values[] = {
                CfgSource::FlashImage,
                CfgSource::OTP,
                CfgSource::ConfigPins,
                CfgSource::ROM
            };

            auto value = field.value();
            auto iter = std::lower_bound(std::begin(Values), std::end(Values), value);
            return (iter != std::end(Values)) && (*iter == value);
        }
    };

    /// @brief Definition of "ofsI" field.
    using ofsI = field::common::I1;

    /// @brief Definition of "magI" field.
    using magI = field::common::U1;

    /// @brief Definition of "ofsQ" field.
    using ofsQ = field::common::I1;

    /// @brief Definition of "magQ" field.
    using magQ = field::common::U1;

    /// @brief Definition of "cfgSource" field.
    using cfgSource =
        field::common::EnumT<
            CfgSource,
            comms::option::ContentsValidator<CfgSourceValidator>
        >;

    /// @brief Definition of "reserved0" field.
    using reserved0 = field::common::res3;

    /// @brief Definition of "lowLevelCfg" field.
    using lowLevelCfg = field::common::U4;

    /// @brief Definition of "reserved1" field.
    using reserved1 =
        field::common::BundleT<
            std::tuple<
                field::common::res4,
                field::common::res4
            >
        >;

    /// @brief Definition of "postStatus" field.
    using postStatus = field::common::U4;

    /// @brief Definition of "reserved2" field.
    using reserved2 = field::common::res4;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        ofsI,
        magI,
        ofsQ,
        magQ,
        cfgSource,
        reserved0,
        lowLevelCfg,
        reserved1,
        postStatus,
        reserved2
    >;
};

/// @brief Definition of MON-HW2 message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref MonHw2Fields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class MonHw2 : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_MON_HW2>,
        comms::option::FieldsImpl<MonHw2Fields::All>,
        comms::option::MsgType<MonHw2<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_MON_HW2>,
        comms::option::FieldsImpl<MonHw2Fields::All>,
        comms::option::MsgType<MonHw2<TMsgBase> >
    > Base;
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b ofsI for @ref MonHw2Fields::ofsI field
    ///     @li @b magI for @ref MonHw2Fields::magI field
    ///     @li @b ofsQ for @ref MonHw2Fields::ofsQ field
    ///     @li @b magQ for @ref MonHw2Fields::magQ field
    ///     @li @b cfgSource for @ref MonHw2Fields::cfgSource field
    ///     @li @b reserved0 for @ref MonHw2Fields::reserved0 field
    ///     @li @b lowLevelCfg for @ref MonHw2Fields::lowLevelCfg field
    ///     @li @b reserved1 for @ref MonHw2Fields::reserved1 field
    ///     @li @b postStatus for @ref MonHw2Fields::postStatus field
    ///     @li @b reserved2 for @ref MonHw2Fields::reserved2 field
    COMMS_MSG_FIELDS_ACCESS(
        ofsI,
        magI,
        ofsQ,
        magQ,
        cfgSource,
        reserved0,
        lowLevelCfg,
        reserved1,
        postStatus,
        reserved2
    );

    /// @brief Default constructor
    MonHw2() = default;

    /// @brief Copy constructor
    MonHw2(const MonHw2&) = default;

    /// @brief Move constructor
    MonHw2(MonHw2&& other) = default;

    /// @brief Destructor
    ~MonHw2() = default;

    /// @brief Copy assignment
    MonHw2& operator=(const MonHw2&) = default;

    /// @brief Move assignment
    MonHw2& operator=(MonHw2&&) = default;
};


}  // namespace message

}  // namespace ublox

