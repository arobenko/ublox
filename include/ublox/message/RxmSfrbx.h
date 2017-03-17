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
/// @brief Contains definition of RXM-SFRBX message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the RXM-SFRBX message fields.
/// @see RxmSfrbx
struct RxmSfrbxFields
{
    /// @brief Definition of "gnssId" field.
    using gnssId = field::common::gnssId;

    /// @brief Definition of "svId" field.
    using svId = field::common::U1;

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res1;

    /// @brief Definition of "freqId" field.
    using freqId = field::common::U1T<comms::option::ValidNumValueRange<0, 13> >;

    /// @brief Definition of "numWords" field.
    using numWords = field::common::U1T<comms::option::ValidNumValueRange<0, 16> >;

    /// @brief Definition of "chn" field.
    using chn = field::common::U1;

    /// @brief Definition of "version" field.
    using version =
        field::common::U1T<
            comms::option::ValidNumValueRange<1, 2>,
            comms::option::DefaultNumValue<2>
        >;

    /// @brief Definition of "reserved2" field.
    using reserved2 = field::common::res1;

    /// @brief Definition of "dword" field.
    /// @tparam TOpt Extra option(s)
    template <typename TOpt = comms::option::EmptyOption>
    using dwrd =
        field::common::ListT<
            field::common::U4,
            TOpt
        >;

    /// @brief All the fields bundled in std::tuple.
    /// @tparam TOpt Extra option(s) for @ref dwrd field
    template <typename TOpt>
    using All = std::tuple<
        gnssId,
        svId,
        reserved1,
        freqId,
        numWords,
        chn,
        version,
        reserved2,
        dwrd<TOpt>
    >;
};

/// @brief Definition of RXM-SFRBX message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref RxmSfrbxFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
/// @tparam TDwrdOpt Extra option(s) for @b bytes field
template <typename TMsgBase = Message, typename TDwrdOpt = comms::option::EmptyOption>
class RxmSfrbx : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_RXM_SFRBX>,
        comms::option::FieldsImpl<RxmSfrbxFields::All<TDwrdOpt> >,
        comms::option::MsgType<RxmSfrbx<TMsgBase, TDwrdOpt> >,
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
    ///     @li @b gnssId for @ref RxmSfrbxFields::gnssId field
    ///     @li @b svId for @ref RxmSfrbxFields::svId field
    ///     @li @b reserved1 for @ref RxmSfrbxFields::reserved1 field
    ///     @li @b freqId for @ref RxmSfrbxFields::freqId field
    ///     @li @b numWords for @ref RxmSfrbxFields::numWords field
    ///     @li @b chn for @ref RxmSfrbxFields::chn field
    ///     @li @b version for @ref RxmSfrbxFields::version field
    ///     @li @b reserved2 for @ref RxmSfrbxFields::reserved2 field
    ///     @li @b dwrd for @ref RxmSfrbxFields::dwrd field
    COMMS_MSG_FIELDS_ACCESS(
        gnssId,
        svId,
        reserved1,
        freqId,
        numWords,
        chn,
        version,
        reserved2,
        dwrd
    );

    /// @brief Default constructor
    RxmSfrbx() = default;

    /// @brief Copy constructor
    RxmSfrbx(const RxmSfrbx&) = default;

    /// @brief Move constructor
    RxmSfrbx(RxmSfrbx&& other) = default;

    /// @brief Destructor
    virtual ~RxmSfrbx() = default;

    /// @brief Copy assignment
    RxmSfrbx& operator=(const RxmSfrbx&) = default;

    /// @brief Move assignment
    RxmSfrbx& operator=(RxmSfrbx&&) = default;

    /// @brief Provides custom read functionality.
    /// @details Number of elements in @ref RxmSfrbxFields::dwrd depends on
    ///     the value in @ref RxmSfrbxFields::numWords
    template <typename TIter>
    comms::ErrorStatus doRead(TIter& iter, std::size_t len)
    {
        typedef typename std::decay<decltype(comms::toMessageBase(*this))>::type Base;
        auto es = Base::template readFieldsUntil<FieldIdx_dwrd>(iter, len);
        if (es != comms::ErrorStatus::Success) {
            return es;
        }

        field_dwrd().forceReadElemCount(field_numWords().value());
        return Base::template readFieldsFrom<FieldIdx_dwrd>(iter, len);
    }

    /// @brief Provides custom refresh functionality
    /// @details The value of @ref RxmSfrbxFields::numWords field depends on
    ///     actual number of elements in @ref RxmSfrbxFields::dwrd.
    bool doRefresh()
    {
        if (field_numWords().value() == field_dwrd().value().size()) {
            return false;
        }

        field_numWords().value() = field_dwrd().value().size();
        return true;
    }
};


}  // namespace message

}  // namespace ublox





