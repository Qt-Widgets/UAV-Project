/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

import QtQuick 2.4
import QtQuick.Window 2.2
import QtPositioning 5.5
import QtLocation 5.5



Window{
    width: 700
    height: 500
    visible: true

    //set a view of the US
    property variant topLeftUS: QtPositioning.coordinate(47.6097,-122.3331)
    property variant bottomRightUS: QtPositioning.coordinate(25.7753,-80.2089)
    property variant viewOfUS: QtPositioning.rectangle(topLeftUS, bottomRightUS)

    //set travel coordinates
    property variant losAngeles: QtPositioning.coordinate(34.0500,-118.2500)
    property variant newYork: QtPositioning.coordinate(40.7127,-74.0059)
    property variant houston: QtPositioning.coordinate(29.7604,-95.3698)

    //create a Map and plane
    Map{
        id: mapOfUS
        anchors.centerIn: parent
        anchors.fill: parent
        plugin: Plugin{
            name: "osm"
        }

        Plane{
            id: planeOne
            pilotName: "CSUN UAV_1"
            coordinate: losAngeles2NY.position

            SequentialAnimation{
                id: planeOneAnimation
                property real rotationDirection: 0;

                NumberAnimation {
                    target: planeOne
                    property: "bearing"; duration: 3000
                    easing.type: Easing.InOutQuad
                    to: planeOneAnimation.rotationDirection
                }
                //qmlPlane
                CoordinateAnimation {
                    id: coordinateAnimation; duration: 9000
                    target: losAngeles2NY; property: "position"
                    easing.type: Easing.InOutQuad
                }

                onStopped: {
                    if (coordinateAnimation.to === losAngeles)
                        planeOne.showMessage(qsTr("Hello Los Angeles!"))
                    else if (coordinateAnimation.to === newYork)
                        planeOne.showMessage(qsTr("Hello New Yok!"))
                }
                onStarted: {
                    if (coordinateAnimation.from === newYork)
                        planeOne.showMessage(qsTr("see you New York!"))
                    else if (coordinateAnimation.from === losAngeles)
                        planeOne.showMessage(qsTr("See you Los Angeles!"))
                }
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    if (planeOneAnimation.running) {
                        console.log("Plane still in the air.");
                        return;
                    }

                    if (losAngeles2NY.position === losAngeles) {
                        coordinateAnimation.from = losAngeles;
                        coordinateAnimation.to = newYork;
                    } else if (losAngeles2NY.position === newYork) {
                        coordinateAnimation.from = newYork;
                        coordinateAnimation.to = losAngeles;
                    }

                    planeOneAnimation.rotationDirection = losAngeles2NY.position.azimuthTo(coordinateAnimation.to)
                    planeOneAnimation.start()
                }
            }
            Component.onCompleted: {
                losAngeles2NY.position = losAngeles;
            }
        }

        //! [CppPlane1]
        Plane {
            id: cppPlane
            pilotName: "CSUN UAV_2"
            coordinate: newYork2Houston.position

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    if (cppPlaneAnimation.running || newYork2Houston.isFlying()) {
                        console.log("Plane still in the air.");
                        return;
                    }

                    newYork2Houston.swapDestinations();
                    cppPlaneAnimation.rotationDirection = newYork2Houston.position.azimuthTo(newYork2Houston.to)
                    cppPlaneAnimation.start();
                    cppPlane.departed();
                }
            }
        //! [CppPlane1]
            //! [CppPlane3]
            SequentialAnimation {
                id: cppPlaneAnimation
                property real rotationDirection : 0;
                NumberAnimation {
                    target: cppPlane; property: "bearing"; duration: 2000
                    easing.type: Easing.InOutQuad
                    to: cppPlaneAnimation.rotationDirection
                }
                ScriptAction { script: newYork2Houston.startFlight() }
            }
            //! [CppPlane3]

            Component.onCompleted: {
                newYork2Houston.position = newYork;
                newYork2Houston.to = houston;
                newYork2Houston.from = newYork;
                newYork2Houston.arrived.connect(arrived)
            }

            function arrived(){
                if (newYork2Houston.to === newYork)
                    cppPlane.showMessage(qsTr("Hello NewYork!"))
                else if (newYork2Houston.to === houston)
                    cppPlane.showMessage(qsTr("Hello Houston!"))
            }

            function departed(){
                if (newYork2Houston.from === newYork)
                    cppPlane.showMessage(qsTr("See you NewYork!"))
                else if (newYork2Houston.from === houston)
                    cppPlane.showMessage(qsTr("See you Houston!"))
            }
        //! [CppPlane2]
        }



        visibleRegion: viewOfUS
    }
}

