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
/// @brief Contains definition of AID-HUI message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the AID-HUI message fields.
/// @see AidHui
struct AidHuiFields
{
    /// @brief Definition of "health" field.
    using health = field::common::X4;

    /// @brief Definition of "utcA0" field.
    using utcA0 = field::common::R8;

    /// @brief Definition of "utcA1" field.
    using utcA1 = field::common::R8;

    /// @brief Definition of "utcTOW" field.
    using utcTOW = field::common::I4;

    /// @brief Definition of "utcWNT" field.
    using utcWNT = field::common::I2;

    /// @brief Definition of "utcLS" field.
    using utcLS = field::common::I2;

    /// @brief Definition of "utcWNF" field.
    using utcWNF = field::common::I2;

    /// @brief Definition of "utcDN" field.
    using utcDN = field::common::I2;

    /// @brief Definition of "utcLSF" field.
    using utcLSF = field::common::I2;

    /// @brief Definition of "utcSpare" field.
    using utcSpare = field::common::I2;

    /// @brief Definition of "klobA0" field.
    using klobA0 = field::common::R4;

    /// @brief Definition of "klobA1" field.
    using klobA1 = field::common::R4;

    /// @brief Definition of "klobA2" field.
    using klobA2 = field::common::R4;

    /// @brief Definition of "klobA3" field.
    using klobA3 = field::common::R4;

    /// @brief Definition of "klobB0" field.
    using klobB0 = field::common::R4;

    /// @brief Definition of "klobB1" field.
    using klobB1 = field::common::R4;

    /// @brief Definition of "klobB2" field.
    using klobB2 = field::common::R4;

    /// @brief Definition of "klobB3" field.
    using klobB3 = field::common::R4;

    /// @brief Definition of "flags" field.
    using flags =
        field::common::X4T<
            comms::option::BitmaskReservedBits<0xfffffff8, 0>
        >;

    /// @brief Enumerator to access bits in @ref flags bitmask field
    enum
    {
        flags_healthValid, ///< "healthValid" bit
        flags_utcValid, ///< "utcValid" bit
        flags_klobValid, ///< "klobValid" bit
        flags_numOfValues ///< number of available bits
    };

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        health,
        utcA0,
        utcA1,
        utcTOW,
        utcWNT,
        utcLS,
        utcWNF,
        utcDN,
        utcLSF,
        utcSpare,
        klobA0,
        klobA1,
        klobA2,
        klobA3,
        klobB0,
        klobB1,
        klobB2,
        klobB3,
        flags
    >;
};

/// @brief Definition of AID-HUI message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref AidHuiFields and for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class AidHui : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_AID_HUI>,
        comms::option::FieldsImpl<AidHuiFields::All>,
        comms::option::MsgType<AidHui<TMsgBase> >,
        comms::option::DispatchImpl
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_AID_HUI>,
        comms::option::FieldsImpl<AidHuiFields::All>,
        comms::option::MsgType<AidHui<TMsgBase> >,
        comms::option::DispatchImpl
    > Base;
public:

#ifdef FOR_DOXYGEN_DOC_ONLY
    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_health, ///< health field, see @ref AidHuiFields::health
        FieldIdx_utcA0, ///< utcA0 field, see @ref AidHuiFields::utcA0
        FieldIdx_utcA1, ///< utcA1 field, see @ref AidHuiFields::utcA1
        FieldIdx_utcTOW, ///< utcTOW field, see @ref AidHuiFields::utcTOW
        FieldIdx_utcWNT, ///< utcWNT field, see @ref AidHuiFields::utcWNT
        FieldIdx_utcLS, ///< utcLC field, see @ref AidHuiFields::utcLS
        FieldIdx_utcWNF, ///< utcWNF field, see @ref AidHuiFields::utcWNF
        FieldIdx_utcDN, ///< utcDN field, see @ref AidHuiFields::utcDN
        FieldIdx_utcLSF, ///< utcLSF field, see @ref AidHuiFields::utcLSF
        FieldIdx_utcSpare, ///< utcSpare field, see @ref AidHuiFields::utcSpare
        FieldIdx_klobA0, ///< klobA0 field, see @ref AidHuiFields::klobA0
        FieldIdx_klobA1, ///< klobA1 field, see @ref AidHuiFields::klobA1
        FieldIdx_klobA2, ///< klobA2 field, see @ref AidHuiFields::klobA2
        FieldIdx_klobA3, ///< klobA3 field, see @ref AidHuiFields::klobA3
        FieldIdx_klobB0, ///< klobB0 field, see @ref AidHuiFields::klobB0
        FieldIdx_klobB1, ///< klobB1 field, see @ref AidHuiFields::klobB1
        FieldIdx_klobB2, ///< klobB2 field, see @ref AidHuiFields::klobB2
        FieldIdx_klobB3, ///< klobB3 field, see @ref AidHuiFields::klobB3
        FieldIdx_flags, ///< flags field, see @ref AidHuiFields::flags
        FieldIdx_numOfValues ///< number of available fields
    };

    /// @brief Access to fields bundled as a struct
    struct FieldsAsStruct
    {
        AidHuiFields::health& health; ///< health field, see @ref AidHuiFields::health
        AidHuiFields::utcA0& utcA0; ///< utcA0 field, see @ref AidHuiFields::utcA0
        AidHuiFields::utcA1& utcA1; ///< utcA1 field, see @ref AidHuiFields::utcA1
        AidHuiFields::utcTOW& utcTOW; ///< utcTOW field, see @ref AidHuiFields::utcTOW
        AidHuiFields::utcWNT& utcWNT; ///< utcWNT field, see @ref AidHuiFields::utcWNT
        AidHuiFields::utcLC& utcLC; ///< utcLC field, see @ref AidHuiFields::utcLS
        AidHuiFields::utcWNF& utcWNF; ///< utcWNF field, see @ref AidHuiFields::utcWNF
        AidHuiFields::utcDN& utcDN; ///< utcDN field, see @ref AidHuiFields::utcDN
        AidHuiFields::utcLSF& utcLSF; ///< utcLSF field, see @ref AidHuiFields::utcLSF
        AidHuiFields::utcSpare& utcSpare; ///< utcSpare field, see @ref AidHuiFields::utcSpare
        AidHuiFields::klobA0& klobA0; ///< klobA0 field, see @ref AidHuiFields::klobA0
        AidHuiFields::klobA1& klobA1; ///< klobA1 field, see @ref AidHuiFields::klobA1
        AidHuiFields::klobA2& klobA2; ///< klobA2 field, see @ref AidHuiFields::klobA2
        AidHuiFields::klobA3& klobA3; ///< klobA3 field, see @ref AidHuiFields::klobA3
        AidHuiFields::klobB0& klobB0; ///< klobB0 field, see @ref AidHuiFields::klobB0
        AidHuiFields::klobB1& klobB1; ///< klobB1 field, see @ref AidHuiFields::klobB1
        AidHuiFields::klobB2& klobB2; ///< klobB2 field, see @ref AidHuiFields::klobB2
        AidHuiFields::klobB3& klobB3; ///< klobB3 field, see @ref AidHuiFields::klobB3
        AidHuiFields::flags& flags; ///< flags field, see @ref AidHuiFields::flags
    };

    /// @brief Access to @b const fields bundled as a struct
    struct ConstFieldsAsStruct
    {
        const AidHuiFields::health& health; ///< health field, see @ref AidHuiFields::health
        const AidHuiFields::utcA0& utcA0; ///< utcA0 field, see @ref AidHuiFields::utcA0
        const AidHuiFields::utcA1& utcA1; ///< utcA1 field, see @ref AidHuiFields::utcA1
        const AidHuiFields::utcTOW& utcTOW; ///< utcTOW field, see @ref AidHuiFields::utcTOW
        const AidHuiFields::utcWNT& utcWNT; ///< utcWNT field, see @ref AidHuiFields::utcWNT
        const AidHuiFields::utcLC& utcLC; ///< utcLC field, see @ref AidHuiFields::utcLS
        const AidHuiFields::utcWNF& utcWNF; ///< utcWNF field, see @ref AidHuiFields::utcWNF
        const AidHuiFields::utcDN& utcDN; ///< utcDN field, see @ref AidHuiFields::utcDN
        const AidHuiFields::utcLSF& utcLSF; ///< utcLSF field, see @ref AidHuiFields::utcLSF
        const AidHuiFields::utcSpare& utcSpare; ///< utcSpare field, see @ref AidHuiFields::utcSpare
        const AidHuiFields::klobA0& klobA0; ///< klobA0 field, see @ref AidHuiFields::klobA0
        const AidHuiFields::klobA1& klobA1; ///< klobA1 field, see @ref AidHuiFields::klobA1
        const AidHuiFields::klobA2& klobA2; ///< klobA2 field, see @ref AidHuiFields::klobA2
        const AidHuiFields::klobA3& klobA3; ///< klobA3 field, see @ref AidHuiFields::klobA3
        const AidHuiFields::klobB0& klobB0; ///< klobB0 field, see @ref AidHuiFields::klobB0
        const AidHuiFields::klobB1& klobB1; ///< klobB1 field, see @ref AidHuiFields::klobB1
        const AidHuiFields::klobB2& klobB2; ///< klobB2 field, see @ref AidHuiFields::klobB2
        const AidHuiFields::klobB3& klobB3; ///< klobB3 field, see @ref AidHuiFields::klobB3
        const AidHuiFields::flags& flags; ///< flags field, see @ref AidHuiFields::flags
    };

    /// @brief Get access to fields bundled into a struct
    FieldsAsStruct fieldsAsStruct();

    /// @brief Get access to @b const fields bundled into a struct
    ConstFieldsAsStruct fieldsAsStruct() const;

#else
    COMMS_MSG_FIELDS_ACCESS(Base,
        health,
        utcA0,
        utcA1,
        utcTOW,
        utcWNT,
        utcLS,
        utcWNF,
        utcDN,
        utcLSF,
        utcSpare,
        klobA0,
        klobA1,
        klobA2,
        klobA3,
        klobB0,
        klobB1,
        klobB2,
        klobB3,
        flags);
#endif // #ifdef FOR_DOXYGEN_DOC_ONLY

    /// @brief Default constructor
    AidHui() = default;

    /// @brief Copy constructor
    AidHui(const AidHui&) = default;

    /// @brief Move constructor
    AidHui(AidHui&& other) = default;

    /// @brief Destructor
    virtual ~AidHui() = default;

    /// @brief Copy assignment
    AidHui& operator=(const AidHui&) = default;

    /// @brief Move assignment
    AidHui& operator=(AidHui&&) = default;
};


}  // namespace message

}  // namespace ublox

