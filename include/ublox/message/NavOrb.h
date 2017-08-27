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
/// @brief Contains definition of NAV-ORB message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/nav.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the NAV-ORB message fields.
/// @see NavOrb
struct NavOrbFields
{
    /// @brief Definition of "iTOW" field.
    using iTOW = field::nav::iTOW;

    /// @brief Definition of "version" field.
    using version =
        field::common::U1T<
            comms::option::ValidNumValueRange<1, 1>,
            comms::option::DefaultNumValue<1>
        >;

    /// @brief Definition of "numSv" field.
    using numSv = field::common::U1;

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res2;

    /// @brief Definition of "gnssId" field.
    using gnssId = field::common::gnssId;

    /// @brief Definition of "svId" field.
    using svId = field::common::U1;

    /// @brief Value enumeration for @ref health field.
    enum class Health : std::uint8_t
    {
        Unknwon, ///< Unknwon
        Healthy, ///< Healthy
        NotHealthy, ///< Not healthy
        NumOfValues /// number of available values
    };

    /// @brief Definition of "health" member field of @ref svFlag bitfield.
    using health =
        field::common::EnumT<
            Health,
            comms::option::ValidNumValueRange<0, (int)Health::NumOfValues - 1>,
            comms::option::FixedBitLength<2>
        >;

    /// @brief Value enumeration for @ref visibility field.
    enum class Visibility : std::uint8_t
    {
        Unknwon, ///< Unknwon
        BelowHorizon, ///< Below horizon
        AboveHorizon, ///< Above horizon
        BelowElevationMask, ///< Below elevation mask
        NumOfValues /// number of available values
    };

    /// @brief Definition of "visibility" member field of @ref svFlag bitfield.
    using visibility =
        field::common::EnumT<
            Visibility,
            comms::option::ValidNumValueRange<0, (int)Visibility::NumOfValues - 1>,
            comms::option::FixedBitLength<2>
        >;

    /// @brief Definition of a "svFlag" field.
    struct svFlag : public
        field::common::BitfieldT<
            std::tuple<
                health,
                visibility,
                field::common::res1T<comms::option::FixedBitLength<4> >
            >
        >
    {
        /// @brief Allow access to internal fields.
        /// @details See definition of @b COMMS_FIELD_MEMBERS_ACCESS macro
        ///     related to @b comms::field::Bitfield class from COMMS library
        ///     for details.
        COMMS_FIELD_MEMBERS_ACCESS(health, visibility, reserved);
    };

    /// @brief Definition of "ephUsability" member field of @ref eph bitfield.
    using ephUsability =
        field::common::U1T<
            comms::option::FixedBitLength<5>
        >;


    /// @brief Value enumeration for @ref ephSource and @ref almSource fields.
    enum class Source : std::uint8_t
    {
        NotAvailable, ///< Not available
        GnssTransmission, ///< GNSS transmission
        ExternalAiding, ///< External aiding
        NumOfValues /// number of available values
    };

    /// @brief Definition of "ephSource" member field of @ref eph bitfield.
    using ephSource =
        field::common::EnumT<
            Source,
            comms::option::ValidNumValueRange<0, (int)Source::NumOfValues - 1>,
            comms::option::FixedBitLength<3>
        >;


    /// @brief Definition of a "eph" field.
    struct eph : public
        field::common::BitfieldT<
            std::tuple<
                ephUsability,
                ephSource
            >
        >
    {
        /// @brief Allow access to internal fields.
        /// @details See definition of @b COMMS_FIELD_MEMBERS_ACCESS macro
        ///     related to @b comms::field::Bitfield class from COMMS library
        ///     for details.
        COMMS_FIELD_MEMBERS_ACCESS(ephUsability, ephSource);
    };

    /// @brief Definition of "almUsability" member field of @ref alm bitfield.
    using almUsability = ephUsability;

    /// @brief Definition of "almSource" member field of @ref alm bitfield.
    using almSource = ephSource;

    /// @brief Definition of a "alm" field.
    struct alm : public
        field::common::BitfieldT<
            std::tuple<
                almUsability,
                almSource
            >
        >
    {
        /// @brief Allow access to internal fields.
        /// @details See definition of @b COMMS_FIELD_MEMBERS_ACCESS macro
        ///     related to @b comms::field::Bitfield class from COMMS library
        ///     for details.
        COMMS_FIELD_MEMBERS_ACCESS(almUsability, almSource);
    };

    /// @brief Definition of "anoAopUsability" member field of @ref otherOrb bitfield.
    using anoAopUsability =
        field::common::U1T<
            comms::option::FixedBitLength<5>
        >;

    /// @brief Value enumeration for @ref type field.
    enum class OrbType : std::uint8_t
    {
        NoData, ///< No orbit data available
        OfflineData, ///< Assist now offline data
        AutonomousData, ///< Assist now autonomous data
        NumOfValues /// number of available values
    };

    /// @brief Definition of "type" member field of @ref otherOrb bitfield.
    using type =
        field::common::EnumT<
            OrbType,
            comms::option::ValidNumValueRange<0, (int)OrbType::NumOfValues - 1>,
            comms::option::FixedBitLength<3>
        >;


    /// @brief Definition of a "otherOrb" field.
    struct otherOrb : public
        field::common::BitfieldT<
            std::tuple<
                anoAopUsability,
                type
            >
        >
    {
        /// @brief Allow access to internal fields.
        /// @details See definition of @b COMMS_FIELD_MEMBERS_ACCESS macro
        ///     related to @b comms::field::Bitfield class from COMMS library
        ///     for details.
        COMMS_FIELD_MEMBERS_ACCESS(anoAopUsability, type);
    };



    /// @brief Definition of a block field repeated multiple times in @ref
    ///     data list.
    struct block : public
        field::common::BundleT<
            std::tuple<
                gnssId,
                svId,
                svFlag,
                eph,
                alm,
                otherOrb
            >
        >
    {
        /// @brief Allow access to internal fields.
        /// @details See definition of @b COMMS_FIELD_MEMBERS_ACCESS macro
        ///     related to @b comms::field::Bundle class from COMMS library
        ///     for details.
        COMMS_FIELD_MEMBERS_ACCESS(gnssId, svId, svFlag, eph, alm, otherOrb);
    };

    /// @brief Definition of "data" field as list of blocks (@ref block).
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
        version,
        numSv,
        reserved1,
        data<TOpt>
    >;
};

/// @brief Definition of NAV-ORB message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref NavOrbFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
/// @tparam TDataOpt Extra option(s) for @b data field
template <typename TMsgBase = Message, typename TDataOpt = comms::option::EmptyOption>
class NavOrb : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_ORB>,
        comms::option::FieldsImpl<NavOrbFields::All<TDataOpt> >,
        comms::option::MsgType<NavOrb<TMsgBase, TDataOpt> >,
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
    ///     @li @b iTOW for @ref NavOrbFields::iTOW field
    ///     @li @b version for @ref NavOrbFields::version field
    ///     @li @b numSv for @ref NavOrbFields::numSv field
    ///     @li @b reserved1 for @ref NavOrbFields::reserved1 field
    ///     @li @b data for @ref NavOrbFields::data field
    COMMS_MSG_FIELDS_ACCESS(
        iTOW,
        version,
        numSv,
        reserved1,
        data
    );

    /// @brief Default constructor
    NavOrb() = default;

    /// @brief Copy constructor
    NavOrb(const NavOrb&) = default;

    /// @brief Move constructor
    NavOrb(NavOrb&& other) = default;

    /// @brief Destructor
    ~NavOrb() = default;

    /// @brief Copy assignment
    NavOrb& operator=(const NavOrb&) = default;

    /// @brief Move assignment
    NavOrb& operator=(NavOrb&&) = default;

    /// @brief Provides custom read functionality.
    /// @details The number of blocks in @b data (@ref NavOrbFields::data)
    ///     list is determined by the value of @b numSv (@ref NavOrbFields::numSv)
    ///     field.
    template <typename TIter>
    comms::ErrorStatus doRead(TIter& iter, std::size_t len)
    {
        using Base = typename std::decay<decltype(comms::toMessageBase(*this))>::type;
        auto es = Base::template readFieldsUntil<FieldIdx_data>(iter, len);
        if (es != comms::ErrorStatus::Success) {
            return es;
        }

        field_data().forceReadElemCount(field_numSv().value());
        return Base::template readFieldsFrom<FieldIdx_data>(iter, len);
    }

    /// @brief Provides custom refresh functionality
    /// @details The value of @b numSv (@ref NavOrbFields::numSv) field is
    ///     determined by number of blocks stored in @b data (@ref NavOrbFields::data)
    ///     list.
    /// @return @b true in case the value of "numSv" field was modified, @b false otherwise
    bool doRefresh()
    {
        if (field_numSv().value() == field_data().value().size()) {
            return false;
        }

        field_numSv().value() = field_data().value().size();
        return true;
    }

};


}  // namespace message

}  // namespace ublox





