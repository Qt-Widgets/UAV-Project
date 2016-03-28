var map = L.map("map").setView([34.222, -118.49], 12);

L.tileLayer('http://server.arcgisonline.com/ArcGIS/rest/services/World_Topo_Map/MapServer/tile/{z}/{y}/{x}',
{
  maxNativeZoom: 18,
  maxZoom: 24,
  reuseTiles: true,
  unloadInvisibleTiles: true
}).addTo(map);


d3.select(".leaflet-control-attribution").remove();

map.on("mousemove", function(e) {
    d3.select("#mouseLatLng").html(
      Math.round(e.latlng.lat * 1000)/1000 + "&deg, " +
      Math.round(e.latlng.lng * 1000)/1000 + "&deg");
});

var uavBaseIcon = L.Icon.extend({
    options: {
        shadowUrl: "Map_Icons/blank.png",
        iconSize:     [64, 64],
        shadowSize:   [2, 2],
        iconAnchor:   [32, 32],
        shadowAnchor: [1, 1],
        popupAnchor:  [0, -24]
    }
});

var uavIcon = new uavBaseIcon({iconUrl: "Map_Icons/uav-icon.png"});



////////UAV Stuff

var n = 1; //number of UAVs
var UAVs = [];
var UAVPolylines = [];
var UAVNames = [];
var UAVPaths = [];
var UAVSpeeds = [];
var UAVListenerArray = [];

//name {string}, path {[lat, lng], [lat, lng] , ... , [lat, lng]}, speed {number}
function addUAV(name, path, speed) {
  UAVNames[n] = name;
  UAVPaths[n] = path;
  UAVSpeeds[n] = speed;
  UAVs[n] = L.Marker.movingMarker(UAVPaths[n], [UAVSpeeds[n]], {icon: uavIcon})
                        .addTo(map)
                        .bindPopup(UAVNames[n]);
  UAVPolylines[n] = L.polyline(UAVPaths[n]).addTo(map);
  //UAVs[n].start();

  var tempStr = "listener";
  var tempStr2 = tempStr.concat(n.toString());
     var fn = window[tempStr2];
      if (typeof fn === "function") fn();
  n++;
}

function start() {
    for (i=1; i<=n; i++) {
        UAVs[i].start();
    }
}

//Click listeners for each UAV
function listener1 () {
    UAVs[1].on('click', function() {
        JSBridge.showUAVWindow(UAVNames[1], 1);
    });
}
function listener2 () {
    UAVs[2].on('click', function() {
        JSBridge.showUAVWindow(UAVNames[2], 2);
    });
}
function listener3 () {
    UAVs[3].on('click', function() {
        JSBridge.showUAVWindow(UAVNames[3], 3);
    });
}
function listener4 () {
    UAVs[4].on('click', function() {
        JSBridge.showUAVWindow(UAVNames[4], 4);
    });
}
function listener5 () {
    UAVs[5].on('click', function() {
        JSBridge.showUAVWindow(UAVNames[5], 5);
    });
}
function listener6 () {
    UAVs[6].on('click', function() {
        JSBridge.showUAVWindow(UAVNames[6], 6);
    });
}
function listener7 () {
    UAVs[7].on('click', function() {
        JSBridge.showUAVWindow(UAVNames[7], 7);
    });
}
function listener8 () {
    UAVs[8].on('click', function() {
        JSBridge.showUAVWindow(UAVNames[8], 8);
    });
}
function listener9 () {
    UAVs[9].on('click', function() {
        JSBridge.showUAVWindow(UAVNames[9], 9);
    });
}
function listener10 () {
    UAVs[10].on('click', function() {
        JSBridge.showUAVWindow(UAVNames[10], 10);
    });
}
//END Listeners

// Popup updaters
function popup(i, status) {
    if (UAVs[i].isRunning()) {
        UAVs[i].bindPopup(status).openPopup();
    }
}

function focus(lat, lng) {
    map.setView([lat,lng]);
    map.setZoom(15);
}


function getUAVIndexFromName(name) {
  for(var i = 0; i < UAVNames.length; i++) {
    if(UAVNames[i] == name)
      return i;
  }
  return -1;
}

function getLatLng(index) {
    var latlng = UAVs[index].getLatLng();
    return latlng.toString();
}

function startFlight(name) {
  var u = getUAVIndexFromName(name);
  if(u != 0)
    UAVs[u].start();
}

function stopFlight(name) {
  var u = getUAVIndexFromName(name);
  if(u != 0 && UAVs[u].isRunning())
      UAVs[u].stop();
}

function pauseFlight(name) {
    var u = getUAVIndexFromName(name);
    if(u != 0)
        UAVs[u].pause();
}

function resumeFlight(name) {
  var u = getUAVIndexFromName(name);
  if(u != 0)
    UAVs[u].resume();
}

function reroute (name, newDestination, speed) {
    var u = getUAVIndexFromName(name);
    UAVs[u].moveTo(newDestination, speed);
}

function isStarted(name) {
    var u = getUAVIndexFromName(name);
    return UAVs[u].isStarted();
}

function isRunning (name) {
    var u = getUAVIndexFromName(name);
    return UAVs[u].isRunning();
}

function isPaused (name) {
    var u = getUAVIndexFromName(name);
    return UAVs[u].isPaused;
}

function isStopped(name) {
    var u = getUAVIndexFromName(name);
    return UAVs[u].isEnded();
}



// Follinwing have not been tested.


//changeDestination(uav, [34.2, -118.3]);
//uav is a movingMarker, destination is [lat, lng]
function appendDestination(name, destination) {
  var u = getUAVIndexFromName(name);
  if(u != 0) {
    UAVPaths[u].push(destination);
    UAVs[u].addLatLng(destination, UAVSpeeds[u]);
    map.removeLayer(UAVPolylines[u]);
    UAVPolylines[u] = L.polyline(UAVPaths[u]).addTo(map);
  }
}

function changeDestination(name, destination) {
  var u = getUAVIndexFromName(name);
  if(u != 0) {
    UAVPaths[u] = [UAVs[u].getLatLng(), destination];

    map.removeLayer(UAVs[u]);
    UAVs[u] = L.Marker.movingMarker(UAVPaths[u], [UAVSpeeds[u]], {icon: uavIcon})
            .addTo(map)
            .bindPopup(UAVNames[u]);

    map.removeLayer(UAVPolylines[u]);
    UAVPolylines[u] = L.polyline(UAVPaths[u]).addTo(map);

    UAVs[u].start();
  }
}

var USPS = [];
USPS[0] = L.marker([34.243689,-118.535640]).addTo(map);
USPS[1] = L.marker([34.210034,-118.571521]).addTo(map);
USPS[2] = L.marker([34.265814,-118.526196]).addTo(map);
USPS[3] = L.marker([34.273601,-118.554922]).addTo(map);
USPS[4] = L.marker([34.203311,-118.535677]).addTo(map);
USPS[5] = L.marker([34.256726,-118.600793]).addTo(map);
USPS[6] = L.marker([34.218416,-118.598400]).addTo(map);
USPS[7] = L.marker([34.236373,-118.466520]).addTo(map);
USPS[8] = L.marker([34.172675,-118.541652]).addTo(map);
USPS[9] = L.marker([34.176279,-118.519337]).addTo(map);
USPS[10] = L.marker([34.200541,-118.630173]).addTo(map);
USPS[11] = L.marker([34.268628,-118.468120]).addTo(map);
USPS[12] = L.marker([34.202057,-118.476116]).addTo(map);
USPS[13] = L.marker([34.170057,-118.608636]).addTo(map);
USPS[14] = L.marker([34.224525,-118.447225]).addTo(map);
USPS[15] = L.marker([34.160040,-118.500507]).addTo(map);
USPS[16] = L.marker([34.189540,-118.448980]).addTo(map);
USPS[17] = L.marker([34.282136,-118.442553]).addTo(map);
USPS[18] = L.marker([34.154324,-118.641864]).addTo(map);
USPS[19] = L.marker([34.164363,-118.458005]).addTo(map);
USPS[20] = L.marker([34.164719,-118.404642]).addTo(map);
USPS[21] = L.marker([34.187314,-118.398483]).addTo(map);
USPS[22] = L.marker([34.198664,-118.397087]).addTo(map);
USPS[23] = L.marker([34.241801,-118.425418]).addTo(map);
USPS[24] = L.marker([34.262476,-118.427655]).addTo(map);
USPS[25] = L.marker([34.142350,-118.394123]).addTo(map);
USPS[26] = L.marker([34.152470,-118.350381]).addTo(map);
USPS[27] = L.marker([34.167841,-118.377927]).addTo(map);
USPS[28] = L.marker([34.187958,-118.348218]).addTo(map);
USPS[29] = L.marker([34.217020,-118.368881]).addTo(map);
USPS[30] = L.marker([34.180514,-118.309706]).addTo(map);
