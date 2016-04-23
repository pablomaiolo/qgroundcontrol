/*=====================================================================
 
 QGroundControl Open Source Ground Control Station
 
 (c) 2009 - 2016 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 
 This file is part of the QGROUNDCONTROL project
 
 QGROUNDCONTROL is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 QGROUNDCONTROL is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with QGROUNDCONTROL. If not, see <http://www.gnu.org/licenses/>.
 
 ======================================================================*/

#pragma once

#include <QObject>
#include <QElapsedTimer>

#include "QGCToolbox.h"

/**
 ** class RTCMMavlink
 * Receives RTCM updates and sends them via MAVLINK to the device
 */
class RTCMMavlink : public QObject
{
    Q_OBJECT
public:
    RTCMMavlink(QGCToolbox& toolbox);
    //TODO: API to select device(s)?

public slots:
    void RTCMDataUpdate(QByteArray message);

private:
    QGCToolbox& _toolbox;
    QElapsedTimer _bandwidthTimer;
    int _bandwidthByteCounter = 0;
};