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
/// @brief Contains definition of NAV-SOL message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/nav.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the NAV-SOL message fields.
/// @see NavSol
struct NavSolFields
{
    /// @brief Bits access enumeration for bits in @b flags fields
    enum
    {
        flags_GPSfixOK, ///< @b GPSfixOK bit index
        flags_DiffSoln, ///< @b DiffSoln bit index
        flags_WKNSET, ///< @b WKNSET bit index
        flags_TOWSET, ///< @b TOWSET bit index
        flags_numOfValues ///< number of available bits
    };

    /// @brief Definition of "iTOW" field.
    using iTOW = field::nav::iTOW;

    /// @brief Definition of "fTOW" field.
    using fTOW = field::nav::fTOW;

    /// @brief Definition of "week" field.
    using week = field::nav::week;

    /// @brief Definition of "gpsFix" field.
    using gpsFix = field::nav::gpsFix;

    /// @brief Definition of "flags" field.
    using flags =
        field::common::X1T<
            comms::option::BitmaskReservedBits<0xf0, 0>
        >;

    /// @brief Definition of "ecefX" field.
    using ecefX = field::nav::ecefX;

    /// @brief Definition of "ecefY" field.
    using ecefY = field::nav::ecefY;

    /// @brief Definition of "ecefZ" field.
    using ecefZ = field::nav::ecefZ;

    /// @brief Definition of "pAcc" field.
    using pAcc = field::nav::pAcc;

    /// @brief Definition of "ecefVX" field.
    using ecefVX = field::nav::ecefVX;

    /// @brief Definition of "ecefVY" field.
    using ecefVY = field::nav::ecefVY;

    /// @brief Definition of "ecefVZ" field.
    using ecefVZ = field::nav::ecefVZ;

    /// @brief Definition of "sAcc" field.
    using sAcc = field::nav::sAcc;

    /// @brief Definition of "pDOP" field.
    using pDOP = field::nav::pDOP;

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res1;

    /// @brief Definition of "numSV" field.
    using numSV = field::nav::numSV;

    /// @brief Definition of "reserved2" field.
    using reserved2 = field::common::res4;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        iTOW,
        fTOW,
        week,
        gpsFix,
        flags,
        ecefX,
        ecefY,
        ecefZ,
        pAcc,
        ecefVX,
        ecefVY,
        ecefVZ,
        sAcc,
        pDOP,
        reserved1,
        numSV,
        reserved2
    >;
};

/// @brief Definition of NAV-SOL message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref NavSolFields and for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class NavSol : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_SOL>,
        comms::option::FieldsImpl<NavSolFields::All>,
        comms::option::MsgType<NavSol<TMsgBase> >,
        comms::option::DispatchImpl
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_SOL>,
        comms::option::FieldsImpl<NavSolFields::All>,
        comms::option::MsgType<NavSol<TMsgBase> >,
        comms::option::DispatchImpl
    > Base;
public:

#ifdef FOR_DOXYGEN_DOC_ONLY

    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_iTOW, ///< @b iTOW field, see @ref NavSolFields::iTOW
        FieldIdx_fTOW, ///< @b fTOW field, see @ref NavSolFields::fTOW
        FieldIdx_week, ///< @b week field, see @ref NavSolFields::week
        FieldIdx_gpsFix, ///< @b gpsFix field, see @ref NavSolFields::gpsFix
        FieldIdx_flags, ///< @b flags field, see @ref NavSolFields::flags
        FieldIdx_ecefX, ///< @b ecefX field, see @ref NavSolFields::ecefX
        FieldIdx_ecefY, ///< @b ecefY field, see @ref NavSolFields::ecefY
        FieldIdx_ecefZ, ///< @b ecefZ field, see @ref NavSolFields::ecefZ
        FieldIdx_pAcc, ///< @b pAcc field, see @ref NavSolFields::pAcc
        FieldIdx_ecefVX, ///< @b ecefVX field, see @ref NavSolFields::ecefVX
        FieldIdx_ecefVY, ///< @b ecefVY field, see @ref NavSolFields::ecefVY
        FieldIdx_ecefVZ, ///< @b ecefVZ field, see @ref NavSolFields::ecefVZ
        FieldIdx_sAcc, ///< @b sAcc field, see @ref NavSolFields::sAcc
        FieldIdx_pDOP, ///< @b pDop field, see @ref NavSolFields::pDOP
        FieldIdx_reserved1, ///< @b reserved1 field, see @ref NavSolFields::reserved1
        FieldIdx_numSV, ///< @b numSV field, see @ref NavSolFields::numSV
        FieldIdx_reserved2, ///< @b reserved2 field, see @ref NavSolFields::reserved2
        FieldIdx_numOfValues ///< number of available fields
    };


    /// @brief Access to fields bundled as a struct
    struct FieldsAsStruct
    {
        NavSolFields::iTOW& iTOW; ///< @b iTOW field, see @ref NavSolFields::iTOW
        NavSolFields::fTOW& fTOW; ///< @b fTOW field, see @ref NavSolFields::fTOW
        NavSolFields::week& week; ///< @b week field, see @ref NavSolFields::week
        NavSolFields::gpsFix& gpsFix; ///< @b gpsFix field, see @ref NavSolFields::gpsFix
        NavSolFields::flags& flags; ///< @b flags field, see @ref NavSolFields::flags
        NavSolFields::ecefX& ecefX; ///< @b ecefX field, see @ref NavSolFields::ecefX
        NavSolFields::ecefY& ecefY; ///< @b ecefY field, see @ref NavSolFields::ecefY
        NavSolFields::ecefZ& ecefZ; ///< @b ecefZ field, see @ref NavSolFields::ecefZ
        NavSolFields::pAcc& pAcc; ///< @b pAcc field, see @ref NavSolFields::pAcc
        NavSolFields::ecefVX& ecefVX; ///< @b ecefVX field, see @ref NavSolFields::ecefVX
        NavSolFields::ecefVY& ecefVY; ///< @b ecefVY field, see @ref NavSolFields::ecefVY
        NavSolFields::ecefVZ& ecefVZ; ///< @b ecefVZ field, see @ref NavSolFields::ecefVZ
        NavSolFields::sAcc& sAcc; ///< @b sAcc field, see @ref NavSolFields::sAcc
        NavSolFields::pDop& pDop; ///< @b pDop field, see @ref NavSolFields::pDOP
        NavSolFields::reserved1& reserved1; ///< @b reserved1 field, see @ref NavSolFields::reserved1
        NavSolFields::numSV& numSV; ///< @b numSV field, see @ref NavSolFields::numSV
        NavSolFields::reserved2& reserved2; ///< @b reserved2 field, see @ref NavSolFields::reserved2
    };

    /// @brief Access to @b const fields bundled as a struct
    struct ConstFieldsAsStruct
    {
        NavSolFields::iTOW& iTOW; ///< @b iTOW field, see @ref NavSolFields::iTOW
        NavSolFields::fTOW& fTOW; ///< @b fTOW field, see @ref NavSolFields::fTOW
        NavSolFields::week& week; ///< @b week field, see @ref NavSolFields::week
        NavSolFields::gpsFix& gpsFix; ///< @b gpsFix field, see @ref NavSolFields::gpsFix
        NavSolFields::flags& flags; ///< @b flags field, see @ref NavSolFields::flags
        NavSolFields::ecefX& ecefX; ///< @b ecefX field, see @ref NavSolFields::ecefX
        NavSolFields::ecefY& ecefY; ///< @b ecefY field, see @ref NavSolFields::ecefY
        NavSolFields::ecefZ& ecefZ; ///< @b ecefZ field, see @ref NavSolFields::ecefZ
        NavSolFields::pAcc& pAcc; ///< @b pAcc field, see @ref NavSolFields::pAcc
        NavSolFields::ecefVX& ecefVX; ///< @b ecefVX field, see @ref NavSolFields::ecefVX
        NavSolFields::ecefVY& ecefVY; ///< @b ecefVY field, see @ref NavSolFields::ecefVY
        NavSolFields::ecefVZ& ecefVZ; ///< @b ecefVZ field, see @ref NavSolFields::ecefVZ
        NavSolFields::sAcc& sAcc; ///< @b sAcc field, see @ref NavSolFields::sAcc
        NavSolFields::pDop& pDop; ///< @b pDop field, see @ref NavSolFields::pDOP
        NavSolFields::reserved1& reserved1; ///< @b reserved1 field, see @ref NavSolFields::reserved1
        NavSolFields::numSV& numSV; ///< @b numSV field, see @ref NavSolFields::numSV
        NavSolFields::reserved2& reserved2; ///< @b reserved2 field, see @ref NavSolFields::reserved2
    };

    /// @brief Get access to fields bundled into a struct
    FieldsAsStruct fieldsAsStruct();

    /// @brief Get access to @b const fields bundled into a struct
    ConstFieldsAsStruct fieldsAsStruct() const;

#else
    COMMS_MSG_FIELDS_ACCESS(Base,
        iTOW,
        fTOW,
        week,
        gpsFix,
        flags,
        ecefX,
        ecefY,
        ecefZ,
        pAcc,
        ecefVX,
        ecefVY,
        ecefVZ,
        sAcc,
        pDOP,
        reserved1,
        numSV,
        reserved2
    );
#endif // #ifdef FOR_DOXYGEN_DOC_ONLY

    /// @brief Default constructor
    NavSol() = default;

    /// @brief Copy constructor
    NavSol(const NavSol&) = default;

    /// @brief Move constructor
    NavSol(NavSol&& other) = default;

    /// @brief Destructor
    virtual ~NavSol() = default;

    /// @brief Copy assignment
    NavSol& operator=(const NavSol&) = default;

    /// @brief Move assignment
    NavSol& operator=(NavSol&&) = default;
};


}  // namespace message

}  // namespace ublox





