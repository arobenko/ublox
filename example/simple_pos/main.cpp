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

#include <iostream>

#include "comms/CompileControl.h"

CC_DISABLE_WARNINGS()
#include <QtCore/QCoreApplication>
#include <QtCore/QCommandLineParser>
CC_ENABLE_WARNINGS()

#include "Session.h"

namespace
{
const QString DevStr("dev");
#ifdef WIN32
const QString DefaultDevStr("COM1");
#else
const QString DefaultDevStr("/dev/ttyUSB0");
#endif

void prepareCommandLineOptions(QCommandLineParser& parser)
{
    parser.addHelpOption();

    QCommandLineOption devOpt(
        QStringList() << "d" << DevStr,
        "Specify u-blox USB device. Default is " + DefaultDevStr,
        QCoreApplication::translate("main", "name/path"),
        DefaultDevStr
    );
    parser.addOption(devOpt);
}

} // namespace

int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);

    QCommandLineParser parser;
    prepareCommandLineOptions(parser);
    parser.process(app);

    Session session(parser.value(DevStr));
    if (!session.start()) {
        std::cerr << "ERROR: Failed to start" << std::endl;
        return -1;
    }

    return app.exec();
}
