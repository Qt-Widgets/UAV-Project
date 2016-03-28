var map = L.map("map").setView([34.227, -118.307], 13);

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

////////UAV Stuff

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

var n = 0; //number of UAVs
var UAVs = [];
var UAVPolylines = [];
var UAVNames = [];
var UAVPaths = [];
var UAVSpeeds = [];







addUAV("UAV One", [[34.227, -118.307],[34.2, -118.45]], 10000);
appendDestination("UAV One", [34.25, -118.306]);
addUAV("UAV Two", [[34.23, -118.300],[34.31, -118.36]], 100000);
changeDestination("UAV Two", [34.25, -118.23]);







//name {string}, path {[lat, lng], [lat, lng] , ... , [lat, lng]}, speed {number}
function addUAV(name, path, speed) {
  UAVNames[n] = name;
  UAVPaths[n] = path;
  UAVSpeeds[n] = speed;
  UAVs[n] = L.Marker.movingMarker(UAVPaths[n], [UAVSpeeds[n]], {icon: uavIcon})
                        .addTo(map)
                        .bindPopup(UAVNames[n]);
  UAVPolylines[n] = L.polyline(UAVPaths[n]).addTo(map);
  UAVs[n].start();
  n++;
}
function getUAVIndexFromName(name) {
  for(var i = 0; i < UAVNames.length; i++) {
    if(UAVNames[i] == name)
      return i;
  }
  return -1;
}
//changeDestination(uav, [34.2, -118.3]);
//uav is a movingMarker, destination is [lat, lng]
function appendDestination(name, destination) {
  var u = getUAVIndexFromName(name);
  if(u != -1) {
    UAVPaths[u].push(destination);
    UAVs[u].addLatLng(destination, UAVSpeeds[u]);
    map.removeLayer(UAVPolylines[u]);
    UAVPolylines[u] = L.polyline(UAVPaths[u]).addTo(map);
  }
}
function changeDestination(name, destination) {
  var u = getUAVIndexFromName(name);
  if(u != -1) {
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
function stopFlight(name) {
  var u = getUAVIndexFromName(name);
  if(u != -1)
    UAVs[u].pause();
}
function startFlight(name) {
  var u = getUAVIndexFromName(name);
  if(u != -1)
    UAVs[u].resume();
}
function beginFlight(name) {
  var u = getUAVIndexFromName(name);
  if(u != -1)
    UAVs[u].start();
}
