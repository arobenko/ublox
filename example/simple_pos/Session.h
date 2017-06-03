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

#include <cstdint>
#include <vector>

#include "comms/CompileControl.h"

CC_DISABLE_WARNINGS()
#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QTimer>
#include <QtSerialPort/QSerialPort>
CC_ENABLE_WARNINGS()

#include "ublox/ublox.h"
#include "ublox/message/NavPosllh.h"

class Session : public QObject
{
    Q_OBJECT
    using Base = QObject;

    using InMessage =
        ublox::MessageT<
            comms::option::ReadIterator<const std::uint8_t*>,
            comms::option::Handler<Session> // Dispatch to this object
        >;

    using OutBuffer = std::vector<std::uint8_t>;
    using OutMessage =
        ublox::MessageT<
            comms::option::IdInfoInterface,
            comms::option::WriteIterator<std::back_insert_iterator<OutBuffer> >,
            comms::option::LengthInfoInterface
        >;

    using InNavPosllh = ublox::message::NavPosllh<InMessage>;

public:
    explicit Session(const QString& dev);
    ~Session();

    bool start();

    void handle(InNavPosllh& msg);

    void handle(InMessage& msg);

private slots:
    void performRead();
    void errorOccurred(QSerialPort::SerialPortError err);
    void sendPosPoll();

private:

    using AllInMessages =
        std::tuple<
            InNavPosllh
        >;

    using ProtStack = ublox::Stack<InMessage, AllInMessages>;

    void sendMessage(const OutMessage& msg);
    void configureUbxOutput();

    QSerialPort m_serial;
    QTimer m_pollTimer;
    std::vector<std::uint8_t> m_inData;
    ProtStack m_stack;
};
