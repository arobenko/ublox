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
/// @brief Contains definition of NAV-VELNED message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/nav.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the NAV-VELNED message fields.
/// @see NavVelned
struct NavVelnedFields
{
    /// @brief Definition of "iTOW" field.
    using iTOW = field::nav::iTOW;

    /// @brief Definition of "velN" field.
    using velN = field::common::I4T<field::common::Scaling_cm2m>;;

    /// @brief Definition of "velE" field.
    using velE = velN;

    /// @brief Definition of "velD" field.
    using velD = velN;

    /// @brief Definition of "speed" field.
    using speed = field::common::U4T<field::common::Scaling_cm2m>;

    /// @brief Definition of "gSpeed" field.
    using gSpeed = field::common::U4T<field::common::Scaling_cm2m>;

    /// @brief Definition of "heading" field.
    using heading = field::nav::heading;

    /// @brief Definition of "sAcc" field.
    using sAcc = field::nav::sAcc;

    /// @brief Definition of "cAcc" field.
    using cAcc =
        field::common::U4T<comms::option::ScalingRatio<1, 100000> >;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        iTOW,
        velN,
        velE,
        velD,
        speed,
        gSpeed,
        heading,
        sAcc,
        cAcc
    >;
};

/// @brief Definition of NAV-VELNED message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref NavVelnedFields and for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class NavVelned : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_VELNED>,
        comms::option::FieldsImpl<NavVelnedFields::All>,
        comms::option::MsgType<NavVelned<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_VELNED>,
        comms::option::FieldsImpl<NavVelnedFields::All>,
        comms::option::MsgType<NavVelned<TMsgBase> >
    > Base;
public:

#ifdef FOR_DOXYGEN_DOC_ONLY
    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_iTOW, ///< @b iTOW field, see @ref NavVelnedFields::iTOW
        FieldIdx_velN, ///< @b velN field, see @ref NavVelnedFields::velN
        FieldIdx_velE, ///< @b velE field, see @ref NavVelnedFields::velE
        FieldIdx_velD, ///< @b velD field, see @ref NavVelnedFields::velD
        FieldIdx_speed, ///< @b speed field, see @ref NavVelnedFields::speed
        FieldIdx_gSpeed, ///< @b gSpeed field, see @ref NavVelnedFields::gSpeed
        FieldIdx_heading, ///< @b heading field, see @ref NavVelnedFields::heading
        FieldIdx_sAcc, ///< @b sAcc field, see @ref NavVelnedFields::sAcc
        FieldIdx_cAcc, ///< @b cAcc field, see @ref NavVelnedFields::cAcc
        FieldIdx_numOfValues ///< number of available fields
    };

    /// @brief Access to fields bundled as a struct
    struct FieldsAsStruct
    {
        NavVelnedFields::iTOW& iTOW; ///< @b iTOW field, see @ref NavVelnedFields::iTOW
        NavVelnedFields::velN& velN; ///< @b velN field, see @ref NavVelnedFields::velN
        NavVelnedFields::velE& velE; ///< @b velE field, see @ref NavVelnedFields::velE
        NavVelnedFields::velD& velD; ///< @b velD field, see @ref NavVelnedFields::velD
        NavVelnedFields::speed& speed; ///< @b speed field, see @ref NavVelnedFields::speed
        NavVelnedFields::gSpeed& gSpeed; ///< @b gSpeed field, see @ref NavVelnedFields::gSpeed
        NavVelnedFields::heading& heading; ///< @b heading field, see @ref NavVelnedFields::heading
        NavVelnedFields::sAcc& sAcc; ///< @b sAcc field, see @ref NavVelnedFields::sAcc
        NavVelnedFields::cAcc& cAcc; ///< @b cAcc field, see @ref NavVelnedFields::cAcc
    };

    /// @brief Access to @b const fields bundled as a struct
    struct ConstFieldsAsStruct
    {
        const NavVelnedFields::iTOW& iTOW; ///< @b iTOW field, see @ref NavVelnedFields::iTOW
        const NavVelnedFields::velN& velN; ///< @b velN field, see @ref NavVelnedFields::velN
        const NavVelnedFields::velE& velE; ///< @b velE field, see @ref NavVelnedFields::velE
        const NavVelnedFields::velD& velD; ///< @b velD field, see @ref NavVelnedFields::velD
        const NavVelnedFields::speed& speed; ///< @b speed field, see @ref NavVelnedFields::speed
        const NavVelnedFields::gSpeed& gSpeed; ///< @b gSpeed field, see @ref NavVelnedFields::gSpeed
        const NavVelnedFields::heading& heading; ///< @b heading field, see @ref NavVelnedFields::heading
        const NavVelnedFields::sAcc& sAcc; ///< @b sAcc field, see @ref NavVelnedFields::sAcc
        const NavVelnedFields::cAcc& cAcc; ///< @b cAcc field, see @ref NavVelnedFields::cAcc
    };

    /// @brief Get access to fields bundled into a struct
    FieldsAsStruct fieldsAsStruct();

    /// @brief Get access to @b const fields bundled into a struct
    ConstFieldsAsStruct fieldsAsStruct() const;

#else
    COMMS_MSG_FIELDS_ACCESS(Base, iTOW, velN, velE, velD, speed, gSpeed, heading, sAcc, cAcc);
#endif // #ifdef FOR_DOXYGEN_DOC_ONLY

    /// @brief Default constructor
    NavVelned() = default;

    /// @brief Copy constructor
    NavVelned(const NavVelned&) = default;

    /// @brief Move constructor
    NavVelned(NavVelned&& other) = default;

    /// @brief Destructor
    virtual ~NavVelned() = default;

    /// @brief Copy assignment
    NavVelned& operator=(const NavVelned&) = default;

    /// @brief Move assignment
    NavVelned& operator=(NavVelned&&) = default;
};


}  // namespace message

}  // namespace ublox





