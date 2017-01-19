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
/// @brief Contains definition of CFG-TMODE2 message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the CFG-TMODE2 message fields.
/// @see CfgTmode2
struct CfgTmode2Fields
{
    /// @brief Value enumeration for @ref timeMode field.
    enum class TimeMode : std::uint8_t
    {
        Disabled, ///< Disabled
        SurveyIn, ///< Survey in
        FixedMode, ///< Fixed mode
        NumOfValues ///< number of available values
    };

    /// @brief Definition of "timeMode" field.
    using timeMode =
        field::common::EnumT<
            TimeMode,
            comms::option::ValidNumValueRange<0, (int)TimeMode::NumOfValues - 1>
        >;

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res1;

    /// @brief Definition of "flags" field.
    struct flags : public
        field::common::X2T<
            comms::option::BitmaskReservedBits<0xfffc, 0>
        >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS(lla, altInv);
    };

    /// @brief Definition of "ecefX" field.
    using ecefX =
        field::common::OptionalT<
            field::common::I4T<field::common::Scaling_cm2m>
        >;

    /// @brief Definition of "lat" field.
    using lat =
        field::common::OptionalT<
            field::common::I4T<comms::option::ScalingRatio<1, 10000000L> >
        >;

    /// @brief Definition of "ecefY" field.
    using ecefY =
        field::common::OptionalT<
            field::common::I4T<field::common::Scaling_cm2m>
        >;

    /// @brief Definition of "lon" field.
    using lon =
        field::common::OptionalT<
            field::common::I4T<comms::option::ScalingRatio<1, 10000000L> >
        >;

    /// @brief Definition of "ecefZ" field.
    using ecefZ =
        field::common::OptionalT<
            field::common::I4T<field::common::Scaling_cm2m>
        >;

    /// @brief Definition of "alt" field.
    using alt =
        field::common::OptionalT<
            field::common::I4T<field::common::Scaling_cm2m>
        >;

    /// @brief Definition of "fixedPosAcc" field.
    using fixedPosAcc =
        field::common::U4T<
            field::common::Scaling_mm2m
        >;

    /// @brief Definition of "svinMinDur" field.
    using svinMinDur = field::common::U4;

    /// @brief Definition of "svinAccLimit" field.
    using svinAccLimit =
        field::common::U4T<
            field::common::Scaling_mm2m
        >;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        timeMode,
        reserved1,
        flags,
        ecefX,
        lat,
        ecefY,
        lon,
        ecefZ,
        alt,
        fixedPosAcc,
        svinMinDur,
        svinAccLimit
    >;
};

/// @brief Definition of AID-TMODE2 message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref CfgTmode2Fields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
///
///     @b NOTE, that Ublox binary protocol specification reinterprets value of
///     some fields based on the value of @b lla bit in @b flags (see @ref CfgTmode2Fields::flags)
///     field. It also combines the dual meaning of the field in a single name, such as
///     @b ecefXOrLat, @b ecefYOrLon, @b ecefZOrAlt. @n
///     The implementation of this message splits these names into two separate
///     fields: @b ecefX + @b lat, @b ecefY + @b lon, @b ecefZ + @b alt.
///     These fields are @b optional (see @ref field::common::OptionalT), and
///     marked as @b missing or @b existing based on the value of @b lla bit
///     in @b flags (see @ref CfgTmode2Fields::flags) field.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class CfgTmode2 : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_TMODE2>,
        comms::option::FieldsImpl<CfgTmode2Fields::All>,
        comms::option::MsgType<CfgTmode2<TMsgBase> >,
        comms::option::HasDoRefresh
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_TMODE2>,
        comms::option::FieldsImpl<CfgTmode2Fields::All>,
        comms::option::MsgType<CfgTmode2<TMsgBase> >,
        comms::option::HasDoRefresh
    > Base;
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b timeMode for @ref CfgTmode2Fields::timeMode field
    ///     @li @b reserved1 for @ref CfgTmode2Fields::reserved1 field
    ///     @li @b flags for @ref CfgTmode2Fields::flags field
    ///     @li @b ecefX for @ref CfgTmode2Fields::ecefX field
    ///     @li @b lat for @ref CfgTmode2Fields::lat field
    ///     @li @b ecefY for @ref CfgTmode2Fields::ecefY field
    ///     @li @b lon for @ref CfgTmode2Fields::lon field
    ///     @li @b ecefZ for @ref CfgTmode2Fields::ecefZ field
    ///     @li @b alt for @ref CfgTmode2Fields::alt field
    ///     @li @b fixedPosAcc for @ref CfgTmode2Fields::fixedPosAcc field
    ///     @li @b svinMinDur for @ref CfgTmode2Fields::svinMinDur field
    ///     @li @b svinAccLimit for @ref CfgTmode2Fields::svinAccLimit field
    COMMS_MSG_FIELDS_ACCESS(Base,
        timeMode,
        reserved1,
        flags,
        ecefX,
        lat,
        ecefY,
        lon,
        ecefZ,
        alt,
        fixedPosAcc,
        svinMinDur,
        svinAccLimit
    );


    /// @brief Default constructor
    /// @details The existing/missing mode of the optional fields is determined
    ///     by the default value of the @b flags (see @ref CfgTmode2Fields::flags)
    ///     field, i.e. the @ref CfgTmode2Fields::ecefX, @ref CfgTmode2Fields::ecefY,
    ///     and @ref CfgTmode2Fields::ecefZ fields are marked as @b existing, while
    ///     @ref CfgTmode2Fields::lat, @ref CfgTmode2Fields::lon, and
    ///     @ref CfgTmode2Fields::alt are marked as @b missing.
    CfgTmode2()
    {
        auto& allFields = Base::fields();

        auto& ecefXField = std::get<FieldIdx_ecefX>(allFields);
        auto& ecefYField = std::get<FieldIdx_ecefY>(allFields);
        auto& ecefZField = std::get<FieldIdx_ecefZ>(allFields);

        ecefXField.setExists();
        ecefYField.setExists();
        ecefZField.setExists();

        auto& latField = std::get<FieldIdx_lat>(allFields);
        auto& lonField = std::get<FieldIdx_lon>(allFields);
        auto& altField = std::get<FieldIdx_alt>(allFields);

        latField.setMissing();
        lonField.setMissing();
        altField.setMissing();
    }

    /// @brief Copy constructor
    CfgTmode2(const CfgTmode2&) = default;

    /// @brief Move constructor
    CfgTmode2(CfgTmode2&& other) = default;

    /// @brief Destructor
    virtual ~CfgTmode2() = default;

    /// @brief Copy assignment
    CfgTmode2& operator=(const CfgTmode2&) = default;

    /// @brief Move assignment
    CfgTmode2& operator=(CfgTmode2&&) = default;

    /// @brief Provides custom read functionality.
    /// @details This function performs read of the first fields up to the
    ///     @b flags (see @ref CfgTmode2Fields::flags). Based on the value of
    ///     @b lla bit, the relevant optional fields are marked as either
    ///     @b existing or @b missing and the read continues until the end.
    template <typename TIter>
    comms::ErrorStatus doRead(TIter& iter, std::size_t len)
    {
        auto es = Base::template readFieldsUntil<FieldIdx_ecefX>(iter, len);
        if (es != comms::ErrorStatus::Success) {
            return es;
        }

        auto& allFields = Base::fields();
        auto& flagsField = std::get<FieldIdx_flags>(allFields);

        auto cartesianMode = comms::field::OptionalMode::Exists;
        auto geodeticMode = comms::field::OptionalMode::Missing;
        if (flagsField.getBitValue(CfgTmode2Fields::flags::BitIdx_lla)) {
            std::swap(cartesianMode, geodeticMode);
        }

        auto& ecefXField = std::get<FieldIdx_ecefX>(allFields);
        auto& ecefYField = std::get<FieldIdx_ecefY>(allFields);
        auto& ecefZField = std::get<FieldIdx_ecefZ>(allFields);
        ecefXField.setMode(cartesianMode);
        ecefYField.setMode(cartesianMode);
        ecefZField.setMode(cartesianMode);

        auto& latField = std::get<FieldIdx_lat>(allFields);
        auto& lonField = std::get<FieldIdx_lon>(allFields);
        auto& altField = std::get<FieldIdx_alt>(allFields);
        latField.setMode(geodeticMode);
        lonField.setMode(geodeticMode);
        altField.setMode(geodeticMode);

        return Base::template readFieldsFrom<FieldIdx_ecefX>(iter, len);
    }

    /// @brief Provides custom refresh functionality
    /// @details The function checks the value of @b lla bit in the @b flags
    ///     (see @ref CfgTmode2Fields::flags) field and modifies mode of relevant
    ///     @b optional fields accordingly.
    /// @return @b true in case the mode of any optional field was modified, @b false otherwise
    bool doRefresh()
    {
        auto& allFields = Base::fields();
        auto& flagsField = std::get<FieldIdx_flags>(allFields);

        auto cartesianMode = comms::field::OptionalMode::Exists;
        auto geodeticMode = comms::field::OptionalMode::Missing;
        if (flagsField.getBitValue(CfgTmode2Fields::flags::BitIdx_lla)) {
            std::swap(cartesianMode, geodeticMode);
        }

        auto& ecefXField = std::get<FieldIdx_ecefX>(allFields);
        auto& ecefYField = std::get<FieldIdx_ecefY>(allFields);
        auto& ecefZField = std::get<FieldIdx_ecefZ>(allFields);
        auto& latField = std::get<FieldIdx_lat>(allFields);
        auto& lonField = std::get<FieldIdx_lon>(allFields);
        auto& altField = std::get<FieldIdx_alt>(allFields);

        if ((ecefXField.getMode() == cartesianMode) &&
            (ecefYField.getMode() == cartesianMode) &&
            (ecefZField.getMode() == cartesianMode) &&
            (latField.getMode() == geodeticMode) &&
            (lonField.getMode() == geodeticMode) &&
            (altField.getMode() == geodeticMode)) {
            return false;
        }

        ecefXField.setMode(cartesianMode);
        ecefYField.setMode(cartesianMode);
        ecefZField.setMode(cartesianMode);
        latField.setMode(geodeticMode);
        lonField.setMode(geodeticMode);
        altField.setMode(geodeticMode);
        return true;
    }
};

}  // namespace message

}  // namespace ublox

