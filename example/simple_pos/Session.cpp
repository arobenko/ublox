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

#include "Session.h"

#include <iostream>
#include <cassert>

#include "comms/CompileControl.h"

CC_DISABLE_WARNINGS()
#include <QtCore/QCoreApplication>
CC_ENABLE_WARNINGS()

#include "ublox/message/CfgPrtUsb.h"
#include "ublox/message/NavPosllhPoll.h"

Session::Session(const QString &dev)
  : m_serial(dev)
{
    connect(
        &m_serial, SIGNAL(error(QSerialPort::SerialPortError)),
        this, SLOT(errorOccurred(QSerialPort::SerialPortError)));

    connect(
        &m_serial, SIGNAL(readyRead()),
        this, SLOT(performRead()));

    connect(
        &m_pollTimer, SIGNAL(timeout()),
        this, SLOT(sendPosPoll()));
}

Session::~Session() = default;

bool Session::start()
{
    if (!m_serial.open(QSerialPort::ReadWrite)) {
        std::cerr << "ERROR: Failed to open " << m_serial.portName().toStdString() << std::endl;
        return false;
    }

    m_serial.setBaudRate(115200);
    m_serial.setDataBits(QSerialPort::Data8);
    m_serial.setParity(QSerialPort::NoParity);
    m_serial.setStopBits(QSerialPort::OneStop);
    m_serial.setFlowControl(QSerialPort::NoFlowControl);

    configureUbxOutput();
    sendPosPoll();
    m_pollTimer.setSingleShot(false);
    m_pollTimer.setInterval(1000); // poll every second
    m_pollTimer.start();
    return true;
}

void Session::handle(InNavPosllh& msg)
{
    std::cout << "POS: lat=" << comms::units::getDegrees<double>(msg.field_lat()) <<
        "; lon=" << comms::units::getDegrees<double>(msg.field_lon()) <<
        "; alt=" << comms::units::getMeters<double>(msg.field_height()) << std::endl;
}

void Session::handle(InMessage& msg)
{
    static_cast<void>(msg); // ignore
}

void Session::performRead()
{
    auto data = m_serial.readAll();
    auto dataBegIter = data.constData();
    auto dataEndIter = dataBegIter + data.size();
    m_inData.insert(m_inData.end(), dataBegIter, dataEndIter);

    std::size_t consumed = 0U;
    while (consumed < m_inData.size()) {
        // Smart pointer to the message object.
        ProtStack::MsgPtr msgPtr;
        // Type of the message interface class
        using MsgType = ProtStack::MsgPtr::element_type;

        // Get the iterator for reading
        auto begIter = comms::readIteratorFor<MsgType>(&m_inData[0] + consumed);
        auto iter = begIter;
        // Do the read
        auto es = m_stack.read(msgPtr, iter, m_inData.size() - consumed);
        if (es == comms::ErrorStatus::NotEnoughData) {
            break; // Not enough data in the buffer, stop processing
        }

        if (es == comms::ErrorStatus::ProtocolError) {
            // Something is not right with the data, remove one character and try again
           ++consumed;
            continue;
        }
        if (es == comms::ErrorStatus::Success) {
            assert(msgPtr); // If read is successful, msgPtr is expected to hold a valid pointer
            msgPtr->dispatch(*this); // Dispatch message for handling
        }
        // The iterator for reading has been advanced, update the difference
        consumed += std::distance(begIter, iter);
    }

    m_inData.erase(m_inData.begin(), m_inData.begin() + consumed);
}

void Session::errorOccurred(QSerialPort::SerialPortError err)
{
    if (err == QSerialPort::NoError) {
        return;
    }
    std::cerr << "ERROR: " << m_serial.errorString().toStdString() << std::endl;
    m_serial.close();
    if (!start()) {
        qApp->quit();
    }
}

void Session::sendPosPoll()
{
    using OutNavPosllhPoll = ublox::message::NavPosllhPoll<OutMessage>;
    sendMessage(OutNavPosllhPoll());
}

void Session::sendMessage(const OutMessage& msg)
{
    OutBuffer buf;
    buf.reserve(m_stack.length(msg)); // Reserve enough space
    auto iter = std::back_inserter(buf);
    auto es = m_stack.write(msg, iter, buf.max_size());
    if (es == comms::ErrorStatus::UpdateRequired) {
        auto* updateIter = &buf[0];
        es = m_stack.update(updateIter, buf.size());
    }
    static_cast<void>(es);
    assert(es == comms::ErrorStatus::Success); // do not expect any error
    m_serial.write(reinterpret_cast<const char*>(&buf[0]), buf.size());
    m_serial.flush();
}

void Session::configureUbxOutput()
{
    using OutCfgPrtUsb = ublox::message::CfgPrtUsb<OutMessage>;

    OutCfgPrtUsb msg;
    auto& outProtoMaskField = msg.field_outProtoMask();

    using OutProtoMaskField = typename std::decay<decltype(outProtoMaskField)>::type;
    outProtoMaskField.setBitValue(OutProtoMaskField::BitIdx_outUbx, true);
    outProtoMaskField.setBitValue(OutProtoMaskField::BitIdx_outNmea, false);

    auto& inProtoMaskField = msg.field_inProtoMask();
    using InProtoMaskField = typename std::decay<decltype(inProtoMaskField)>::type;
    inProtoMaskField.setBitValue(InProtoMaskField::BitIdx_inUbx, true);
    inProtoMaskField.setBitValue(InProtoMaskField::BitIdx_inNmea, false);

    sendMessage(msg);
}
