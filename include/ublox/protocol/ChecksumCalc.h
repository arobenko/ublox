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

/// @file
/// @brief Contains definition of checksum calculator class.

#pragma once

#include <cstdint>
#include <limits>

namespace ublox
{

namespace protocol
{

/// @brief Checksum calculator.
/// @details Provided to
///     <a href="https://dl.dropboxusercontent.com/u/46999418/comms_champion/comms/html/classcomms_1_1protocol_1_1ChecksumLayer.html">comms::protocol::ChecksumLayer</a>
///     when defining protocol stack (@ref ublox::Stack).
struct ChecksumCalc
{
    template <typename TIter>
    std::uint16_t operator()(TIter& iter, std::size_t len) const
    {
        std::uint8_t ckA = 0;
        std::uint8_t ckB = 0;
        for (auto idx = 0U; idx < len; ++idx) {
            ckA += *iter;
            ckB += ckA;
            ++iter;
        }

        return
            (static_cast<std::uint16_t>(ckB) << std::numeric_limits<std::uint8_t>::digits) |
            ckA;
    }
};

}  // namespace protocol

}  // namespace ublox


