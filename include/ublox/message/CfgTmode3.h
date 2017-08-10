//
// Copyright 2017 (C). Alex Robenko. All rights reserved.
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
/// @brief Contains definition of CFG-TMODE3 message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"
#include "CfgTmode2.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the CFG-TMODE3 message fields.
/// @see CfgTmode3
struct CfgTmode3Fields
{
    /// @brief Definition of "version" field.
    using version =
        field::common::U1T<
            comms::option::ValidNumValueRange<0, 0>
        >;

    /// @brief Definition of "reserved1" field
    using reserved1 = field::common::res1;

    /// @brief Value enumeration for @ref timeMode field.
    /// @details Same as for CFG-TMODE2 message.
    using TimeMode = CfgTmode2Fields::TimeMode;

    /// @brief Definition of "timeMode" field.
    /// @details Same as for CFG-TMODE2 message.
    using timeMode = CfgTmode2Fields::timeMode;

    /// @brief Definition of "flags" field.
    struct flags : public
        field::common::X2T<
            comms::option::BitmaskReservedBits<0xfffe, 0>
        >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS_SEQ macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS_SEQ(lla);
    };

    /// @brief Definition of "ecefX" field.
    using ecefX =
        field::common::OptionalT<
            field::common::I4T<comms::option::UnitsCentimeters>
        >;

    /// @brief Definition of "lat" field.
    using lat =
        field::common::OptionalT<
            field::common::I4T<
                comms::option::ScalingRatio<1, 10000000L>,
                comms::option::UnitsDegrees
            >
        >;

    /// @brief Definition of "ecefY" field.
    using ecefY = ecefX;

    /// @brief Definition of "lon" field.
    using lon = lat;

    /// @brief Definition of "ecefZ" field.
    using ecefZ = ecefX;

    /// @brief Definition of "alt" field.
    using alt =
        field::common::OptionalT<
            field::common::I4T<comms::option::UnitsCentimeters>
        >;

    /// @brief Definition of "ecefXHP" field.
    using ecefXHP =
        field::common::OptionalT<
            field::common::I1T<
                comms::option::UnitsMillimeters,
                comms::option::ScalingRatio<1, 10>
            >
        >;

    /// @brief Definition of "latHP" field.
    using latHP =
        field::common::OptionalT<
            field::common::I1T<
                comms::option::ScalingRatio<1, 1000000000L>,
                comms::option::UnitsDegrees
            >
        >;

    /// @brief Definition of "ecefYHP" field.
    using ecefYHP = ecefXHP;

    /// @brief Definition of "lonHP" field.
    using lonHP = latHP;

    /// @brief Definition of "ecefZHP" field.
    using ecefZHP = ecefXHP;

    /// @brief Definition of "altHP" field.
    using altHP =
        field::common::OptionalT<
            field::common::I1T<
                comms::option::UnitsMillimeters,
                comms::option::ScalingRatio<1, 10>
            >
        >;

    /// @brief Definition of "reserved1" field.
    using reserved2 = field::common::res1;

    /// @brief Definition of "fixedPosAcc" field.
    using fixedPosAcc =
        field::common::U4T<
            comms::option::UnitsMillimeters,
            comms::option::ScalingRatio<1, 10>
        >;

    /// @brief Definition of "svinMinDur" field.
    using svinMinDur = field::common::U4T<comms::option::UnitsSeconds>;

    /// @brief Definition of "svinAccLimit" field.
    using svinAccLimit =
        field::common::U4T<
            comms::option::UnitsMillimeters,
            comms::option::ScalingRatio<1, 10>
        >;

    /// @brief Definition of "reserved3" field.
    using reserved3 = field::common::res3;

    /// @brief Definition of "reserved3" field.
    using reserved4 = field::common::res4;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        version,
        reserved1,
        timeMode,
        flags,
        ecefX,
        lat,
        ecefY,
        lon,
        ecefZ,
        alt,
        ecefXHP,
        latHP,
        ecefYHP,
        lonHP,
        ecefZHP,
        altHP,
        reserved2,
        fixedPosAcc,
        svinMinDur,
        svinAccLimit,
        reserved3,
        reserved4
    >;
};

/// @brief Definition of AID-TMODE3 message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref CfgTmode3Fields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
///
///     @b NOTE, that Ublox binary protocol specification reinterprets value of
///     some fields based on the value of @b lla bit in @b flags (see @ref CfgTmode3Fields::flags)
///     field. It also combines the dual meaning of the field in a single name, such as
///     @b ecefXOrLat, @b ecefYOrLon, @b ecefZOrAlt, @b ecefXofLatHP, etc... @n
///     The implementation of this message splits these names into two separate
///     fields: @b ecefX + @b lat, @b ecefY + @b lon, @b ecefZ + @b alt, @b ecefXHP + @b latHP, etc...
///     These fields are @b optional (see @ref field::common::OptionalT), and
///     marked as @b missing or @b existing based on the value of @b lla bit
///     in @b flags (see @ref CfgTmode3Fields::flags) field.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class CfgTmode3 : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_TMODE3>,
        comms::option::FieldsImpl<CfgTmode3Fields::All>,
        comms::option::MsgType<CfgTmode3<TMsgBase> >,
        comms::option::HasDoRefresh
    >
{
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b version for @ref CfgTmode3Fields::version field
    ///     @li @b reserved1 for @ref CfgTmode3Fields::reserved1 field
    ///     @li @b timeMode for @ref CfgTmode3Fields::timeMode field
    ///     @li @b flags for @ref CfgTmode3Fields::flags field
    ///     @li @b ecefX for @ref CfgTmode3Fields::ecefX field
    ///     @li @b lat for @ref CfgTmode3Fields::lat field
    ///     @li @b ecefY for @ref CfgTmode3Fields::ecefY field
    ///     @li @b lon for @ref CfgTmode3Fields::lon field
    ///     @li @b ecefZ for @ref CfgTmode3Fields::ecefZ field
    ///     @li @b alt for @ref CfgTmode3Fields::alt field
    ///     @li @b ecefXHP for @ref CfgTmode3Fields::ecefXHP field
    ///     @li @b latHP for @ref CfgTmode3Fields::latHP field
    ///     @li @b ecefYHP for @ref CfgTmode3Fields::ecefYHP field
    ///     @li @b lonHP for @ref CfgTmode3Fields::lonHP field
    ///     @li @b ecefZHP for @ref CfgTmode3Fields::ecefZHP field
    ///     @li @b altHP for @ref CfgTmode3Fields::altHP field
    ///     @li @b reserved2 for @ref CfgTmode3Fields::reserved2 field
    ///     @li @b fixedPosAcc for @ref CfgTmode3Fields::fixedPosAcc field
    ///     @li @b svinMinDur for @ref CfgTmode3Fields::svinMinDur field
    ///     @li @b svinAccLimit for @ref CfgTmode3Fields::svinAccLimit field
    ///     @li @b reserved3 for @ref CfgTmode3Fields::reserved3 field
    ///     @li @b reserved4 for @ref CfgTmode3Fields::reserved4 field
    COMMS_MSG_FIELDS_ACCESS(
        version,
        reserved1,
        timeMode,
        flags,
        ecefX,
        lat,
        ecefY,
        lon,
        ecefZ,
        alt,
        ecefXHP,
        latHP,
        ecefYHP,
        lonHP,
        ecefZHP,
        altHP,
        reserved2,
        fixedPosAcc,
        svinMinDur,
        svinAccLimit,
        reserved3,
        reserved4
    );


    /// @brief Default constructor
    /// @details The existing/missing mode of the optional fields is determined
    ///     by the default value of the @b flags (see @ref CfgTmode3Fields::flags)
    ///     field, i.e. the @ref CfgTmode3Fields::ecefX, @ref CfgTmode3Fields::ecefY,
    ///     and @ref CfgTmode3Fields::ecefZ fields are marked as @b existing, while
    ///     @ref CfgTmode3Fields::lat, @ref CfgTmode3Fields::lon, and
    ///     @ref CfgTmode3Fields::alt are marked as @b missing.
    CfgTmode3()
    {
        field_ecefX().setExists();
        field_ecefY().setExists();
        field_ecefZ().setExists();
        field_ecefXHP().setExists();
        field_ecefYHP().setExists();
        field_ecefZHP().setExists();

        field_lat().setMissing();
        field_lon().setMissing();
        field_alt().setMissing();
        field_latHP().setMissing();
        field_lonHP().setMissing();
        field_altHP().setMissing();
    }

    /// @brief Copy constructor
    CfgTmode3(const CfgTmode3&) = default;

    /// @brief Move constructor
    CfgTmode3(CfgTmode3&& other) = default;

    /// @brief Destructor
    ~CfgTmode3() = default;

    /// @brief Copy assignment
    CfgTmode3& operator=(const CfgTmode3&) = default;

    /// @brief Move assignment
    CfgTmode3& operator=(CfgTmode3&&) = default;

    /// @brief Provides custom read functionality.
    /// @details This function performs read of the first fields up to the
    ///     @b flags (see @ref CfgTmode3Fields::flags). Based on the value of
    ///     @b lla bit, the relevant optional fields are marked as either
    ///     @b existing or @b missing and the read continues until the end.
    template <typename TIter>
    comms::ErrorStatus doRead(TIter& iter, std::size_t len)
    {
        using Base = typename std::decay<decltype(comms::toMessageBase(*this))>::type;
        auto es = Base::template readFieldsUntil<FieldIdx_ecefX>(iter, len);
        if (es != comms::ErrorStatus::Success) {
            return es;
        }

        auto cartesianMode = comms::field::OptionalMode::Exists;
        auto geodeticMode = comms::field::OptionalMode::Missing;
        if (field_flags().getBitValue_lla()) {
            std::swap(cartesianMode, geodeticMode);
        }

        field_ecefX().setMode(cartesianMode);
        field_ecefY().setMode(cartesianMode);
        field_ecefZ().setMode(cartesianMode);
        field_ecefXHP().setMode(cartesianMode);
        field_ecefYHP().setMode(cartesianMode);
        field_ecefZHP().setMode(cartesianMode);


        field_lat().setMode(geodeticMode);
        field_lon().setMode(geodeticMode);
        field_alt().setMode(geodeticMode);
        field_latHP().setMode(geodeticMode);
        field_lonHP().setMode(geodeticMode);
        field_altHP().setMode(geodeticMode);

        return Base::template readFieldsFrom<FieldIdx_ecefX>(iter, len);
    }

    /// @brief Provides custom refresh functionality
    /// @details The function checks the value of @b lla bit in the @b flags
    ///     (see @ref CfgTmode3Fields::flags) field and modifies mode of relevant
    ///     @b optional fields accordingly.
    /// @return @b true in case the mode of any optional field was modified, @b false otherwise
    bool doRefresh()
    {
        auto cartesianMode = comms::field::OptionalMode::Exists;
        auto geodeticMode = comms::field::OptionalMode::Missing;
        if (field_flags().getBitValue_lla()) {
            std::swap(cartesianMode, geodeticMode);
        }

        if ((field_ecefX().getMode() == cartesianMode) &&
            (field_ecefY().getMode() == cartesianMode) &&
            (field_ecefZ().getMode() == cartesianMode) &&
            (field_ecefXHP().getMode() == cartesianMode) &&
            (field_ecefYHP().getMode() == cartesianMode) &&
            (field_ecefZHP().getMode() == cartesianMode) &&
            (field_lat().getMode() == geodeticMode) &&
            (field_lon().getMode() == geodeticMode) &&
            (field_alt().getMode() == geodeticMode) &&
            (field_latHP().getMode() == geodeticMode) &&
            (field_lonHP().getMode() == geodeticMode) &&
            (field_altHP().getMode() == geodeticMode)) {
            return false;
        }

        field_ecefX().setMode(cartesianMode);
        field_ecefY().setMode(cartesianMode);
        field_ecefZ().setMode(cartesianMode);
        field_ecefXHP().setMode(cartesianMode);
        field_ecefYHP().setMode(cartesianMode);
        field_ecefZHP().setMode(cartesianMode);

        field_lat().setMode(geodeticMode);
        field_lon().setMode(geodeticMode);
        field_alt().setMode(geodeticMode);
        field_latHP().setMode(geodeticMode);
        field_lonHP().setMode(geodeticMode);
        field_altHP().setMode(geodeticMode);
        return true;
    }
};

}  // namespace message

}  // namespace ublox

