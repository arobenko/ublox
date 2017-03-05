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


#pragma once

#include "comms_champion/comms_champion.h"
#include "ublox/message/MgaIniEop.h"
#include "cc_plugin/Message.h"
#include "cc_plugin/ProtocolMessageBase.h"

namespace ublox
{

namespace cc_plugin
{

namespace message
{

class MgaIniEop : public
    ProtocolMessageBase<
        ublox::message::MgaIniEop<ublox::cc_plugin::Message>,
        MgaIniEop>
{
public:
    MgaIniEop();
    MgaIniEop(const MgaIniEop&) = delete;
    MgaIniEop(MgaIniEop&&) = delete;
    virtual ~MgaIniEop();

    MgaIniEop& operator=(const MgaIniEop&);
    MgaIniEop& operator=(MgaIniEop&&);

protected:
    virtual const char* nameImpl() const override;
    virtual const QVariantList& fieldsPropertiesImpl() const override;
};

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

extern template class ublox::message::MgaIniEop<ublox::cc_plugin::Message>;
extern template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::MgaIniEop<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::MgaIniEop>;

