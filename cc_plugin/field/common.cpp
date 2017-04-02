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


#include "common.h"

#include <type_traits>

#include "comms_champion/comms_champion.h"

#include "ublox/field/common.h"

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace field
{

namespace common
{

namespace
{

QVariantMap createProps_reserved(unsigned idx)
{
    return
        cc::property::field::IntValue()
            .name(QString("reserved%1").arg(idx, 1, 10, QChar('0')))
            .asMap();
}

QVariantMap createProps_gnssId()
{
    auto props =
        cc::property::field::ForField<ublox::field::common::gnssId>()
            .name("gnssId")
            .add("GPS")
            .add("SBAS")
            .add("Galileo")
            .add("BeiDou")
            .add("IMES")
            .add("QZSS")
            .add("GLONASS");

    assert(props.values().size() == (int)ublox::field::common::GnssId::NumOfValues);
    return props.asMap();
}

}  // namespace

const QVariantList& emptyProperties()
{
    static const QVariantList Props;
    return Props;
}

const QVariantMap& props_iTOW()
{
    static const auto Props =
        cc::property::field::ForField<ublox::field::common::iTOW>()
            .name("iTOW")
            .asMap();
    return Props;
}

const QVariantMap& props_week()
{
    static const auto Props =
        cc::property::field::ForField<ublox::field::common::week>()
            .name("week")
            .asMap();

    return Props;
}

const QVariantMap& props_numSV()
{
    static const auto Props =
        cc::property::field::ForField<ublox::field::common::numSV>()
            .name("numSV")
            .asMap();
    return Props;
}

const QVariantMap& props_svid()
{
    static const auto Props =
        cc::property::field::ForField<ublox::field::common::svid>()
            .name("svid")
            .asMap();
    return Props;
}

const QVariantMap& props_reserved(unsigned idx)
{
    static const QVariantMap Props[] = {
        createProps_reserved(0),
        createProps_reserved(1),
        createProps_reserved(2),
        createProps_reserved(3),
        createProps_reserved(4),
        createProps_reserved(5),
        createProps_reserved(6),
        createProps_reserved(7),
        createProps_reserved(8),
        createProps_reserved(9),
        createProps_reserved(10),
        createProps_reserved(11),
        createProps_reserved(12),
        createProps_reserved(13),
        createProps_reserved(14),
        createProps_reserved(15)
    };

    static const auto MapSize = std::extent<decltype(Props)>::value;
    if (MapSize <= idx) {
        static const QVariantMap EmptyMap;
        return EmptyMap;
    }

    return Props[idx];
}

const QVariantMap& props_gnssId()
{
    static const auto Props = createProps_gnssId();
    return Props;
}

QVariantMap createProps_reservedBundle(unsigned resIdx, unsigned elemCount)
{
    auto props =
        cc::property::field::Bundle()
            .name(QString("reserved%1").arg(resIdx, 1, 10, QChar('0')));

    for (auto count = 0U; count < elemCount; ++count) {
        props.add(QVariantMap());
    }
    return props.asMap();
}

QVariantMap createProps_reservedBundleTwoParts(unsigned idx)
{
    return createProps_reservedBundle(idx, 2);
}

QVariantMap createProps_utcStandard(bool serialisedHidden)
{
    typedef ublox::field::common::utcStandard Field;
    auto props =
        cc::property::field::ForField<Field>()
            .name("utcStandard")
            .add("No info")
            .add("CRL")
            .add("NIST")
            .add("USNO")
            .add("BIPM")
            .add("European Lab")
            .add("SU")
            .add("NTSC")
            .add("Unknown", (int)Field::ValueType::Unknown);

    if (serialisedHidden) {
        props.serialisedHidden();
    }
    return props.asMap();
}

}  // namespace common

}  // namespace field

}  // namespace cc_plugin

}  // namespace ublox

