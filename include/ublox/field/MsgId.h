//
// Copyright 2015 (C). Alex Robenko. All rights reserved.
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


#pragma once

#include <algorithm>
#include "comms/comms.h"
#include "ublox/MsgId.h"

namespace ublox
{

namespace field
{

namespace details
{

inline
bool validateAck(ublox::MsgId id)
{
    return (ublox::MsgId_ACK_NAK <= id) && (id <= MsgId_ACK_ACK);
}

struct MsgIdValueValidator
{
    template <typename TField>
    bool operator()(const TField& field) const
    {
        typedef bool (*ValidateFunc)(ublox::MsgId);

        static const ValidateFunc Funcs[] = {
            &validateAck
        };

        ublox::MsgId id = field.value();
        return std::any_of(
            std::begin(Funcs), std::end(Funcs),
            [id](ValidateFunc func) -> bool
            {
                return func(id);
            });
    }
};

}  // namespace details

using MsgId =
    comms::field::EnumValue<
        comms::Field<comms::option::BigEndian>,
        ublox::MsgId,
        comms::option::ContentsValidator<details::MsgIdValueValidator>
    >;

}  // namespace field

}  // namespace ublox


