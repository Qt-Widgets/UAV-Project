// Copyright 2015 ESRI
//
// All rights reserved under the copyright laws of the United States
// and applicable international laws, treaties, and conventions.
//
// You may freely redistribute and use this sample code, with or
// without modification, provided you include the original copyright
// notice and use restrictions.
//
// See the Sample code usage restrictions document for further information.
//

#include "Untitled3.h"

#include "MapGraphicsView.h"
#include "Map.h"
#include "ArcGISRuntime.h"

// Uncomment if needed
#include "ArcGISLocalTiledLayer.h"
#include "ArcGISTiledMapServiceLayer.h"
#include "ArcGISDynamicMapServiceLayer.h"
#include "ArcGISFeatureLayer.h"
#include "GraphicsLayer.h"
#include "Graphic.h"
#include "SimpleMarkerSymbol.h"
#include "Point.h"
#include "ServiceInfoTask.h"
#include "GeodatabaseFeatureServiceTable.h"
#include "FeatureLayer.h"

int x = 2000000, y = 1000000;
Untitled3::Untitled3(QWidget *parent)
    : QMainWindow(parent)
{
    m_map = new EsriRuntimeQt::Map(this);

    //// connect to signal that is emitted when the map is ready
    //// the mapReady signal is emitted when the Map has obtained a
    //// spatial reference from an added layer
    connect(m_map, SIGNAL(mapReady()), this, SLOT(onMapReady()));
    connect(m_map, SIGNAL(mousePress(QMouseEvent&)), this, SLOT(onMousePress(QMouseEvent&)));

    m_mapGraphicsView = EsriRuntimeQt::MapGraphicsView::create(m_map, this);
    setCentralWidget(m_mapGraphicsView);
    m_map->setWrapAroundEnabled(true);

    QString path = EsriRuntimeQt::ArcGISRuntime::installDirectory();
    path.append("/sdk/samples/data");
    QDir dataDir(path); // using QDir to convert to correct file separator
    QString pathSampleData = dataDir.path() + QDir::separator();

    //// ArcGIS Online Tiled Basemap Layer
    m_tiledServiceLayer = new EsriRuntimeQt::ArcGISTiledMapServiceLayer("http://services.arcgisonline.com/ArcGIS/rest/services/World_Topo_Map/MapServer", this);
    m_map->addLayer(m_tiledServiceLayer);

    //// Local Tiled Basemap Layer using: sdk/samples/data/tpks/Topographic.tpk
    //QString tiledBaseMapLayer = pathSampleData + "tpks" + QDir::separator() + "Topographic.tpk";
    //m_tiledLayer = new EsriRuntimeQt::ArcGISLocalTiledLayer(tiledBaseMapLayer, this);
    //m_map->addLayer(m_tiledLayer);

    //// ArcGIS Online Dynamic Map Service Layer
    //m_dynamicServiceLayer = new EsriRuntimeQt::ArcGISDynamicMapServiceLayer("http://sampleserver1.arcgisonline.com/ArcGIS/rest/services/Specialty/ESRI_StateCityHighway_USA/MapServer", this);
    //m_map->addLayer(m_dynamicServiceLayer);

    //Local Dynamic Layer using: sdk/samples/data/mpks/USCitiesStates.mpk
    /*
  QString dataPath = pathSampleData + "mpks" + QDir::separator() + "USCitiesStates.mpk";
  m_localMapService = EsriRuntimeQt::LocalMapService(dataPath);

  // connect to signal that is emitted when the service is created successfully
  connect(&m_localMapService, SIGNAL(serviceCreationSuccess(const QString&, const QString&)), this, SLOT(onLocalServiceCreationSuccess(const QString&, const QString&)));

  // connect to signal that is emitted when the service failed
  connect(&m_localMapService, SIGNAL(serviceCreationFailure(const QString&)), this, SLOT(onLocalServiceCreationFailure(const QString&)));

  // start the service and the Local Server
  m_localMapService.start();
  */

    // Feature service using: sdk/samples/data/mpks/USCitiesStates.mpk
    /*
  QString localFeatureService = pathSampleData + "mpks" + QDir::separator() + "USCitiesStates.mpk";
  m_localFeatureService = EsriRuntimeQt::LocalFeatureService(localFeatureService);
  m_localFeatureService.setMaximumRecords(3000);

  // connect to signal that is emitted when the service is created successfully
  connect(&m_localFeatureService, SIGNAL(serviceCreationSuccess(const QString&, const QString&)), this, SLOT(onFeatureServiceCreationSuccess(const QString&, const QString&)));

  // connect to signal that is emitted when the service failed
  connect(&m_localFeatureService, SIGNAL(serviceCreationFailure(const QString&)), this, SLOT(onFeatureServiceCreationFailure(const QString&)));

  // start the service and the Local Server
  m_localFeatureService.start();
  */

    m_graphicsLayer = new EsriRuntimeQt::GraphicsLayer(this);
}

Untitled3::~Untitled3()
{
    // stop the Local Map Service
    /*
  if(m_localMapService.status() == EsriRuntimeQt::LocalServiceStatus::Running)
     m_localMapService.stopAndWait();
  */

    // stop the Local Feature Service
    /*
  if(m_localFeatureService.status() == EsriRuntimeQt::LocalServiceStatus::Running)
    m_localFeatureService.stopAndWait();
  */

    // stop the Local Server Instance for local service
    /*
  if (EsriRuntimeQt::LocalServer::instance().isRunning())
    EsriRuntimeQt::LocalServer::instance().shutdownAndWait();
  */
}


void Untitled3::onMapReady()
{
  // set the map extent
  m_map->setExtent(EsriRuntimeQt::Envelope(-13500000, 3500000, -12500000, 4500000, EsriRuntimeQt::SpatialReference(4326)));

  //// Feature Layer
  //// Initialize the FeatureLayer with a GeodatabaseFeatureServiceTable after the Map has
  //// obtained a spatial reference so its features can be projected correctly

  //// specify the URL to create a Service Info Task to get a specific layer by name or id
  //EsriRuntimeQt::ServiceInfoTask* serviceTaskInfo = new EsriRuntimeQt::ServiceInfoTask("http://sampleserver1.arcgisonline.com/ArcGIS/rest/services/Demographics/ESRI_Census_USA/MapServer", this);
  //connect(serviceTaskInfo, SIGNAL(featureServiceInfoComplete(const EsriRuntimeQt::FeatureServiceInfo&)), this, SLOT(onFeatureServiceInfoComplete(const EsriRuntimeQt::FeatureServiceInfo&)));
  //serviceTaskInfo->featureServiceInfo();
}

void Untitled3::onMousePress(QMouseEvent& event)
{
    // Graphics Layer
  m_graphicsLayer->removeGraphics(m_graphicsLayer->graphicIds());
  EsriRuntimeQt::Graphic* graphic1;
  for(int i = 0; i < 50; i++){
    if(i != 0){
    m_graphicsLayer->removeGraphic(m_graphicsLayer->graphicIds()[0]);
    }

    EsriRuntimeQt::Point point1(x, y, EsriRuntimeQt::SpatialReference(4326));
    EsriRuntimeQt::SimpleMarkerSymbol redCircle(Qt::red, 10, EsriRuntimeQt::SimpleMarkerSymbolStyle::Circle);
    graphic1 = new EsriRuntimeQt::Graphic(point1, redCircle);

    m_graphicsLayer->addGraphic(graphic1);
    m_map->addLayer(m_graphicsLayer);

    x += 100; y += 20;
  }
}
/*
void Untitled3::onFeatureServiceInfoComplete(const EsriRuntimeQt::FeatureServiceInfo& serviceInfo)
{
  QList<EsriRuntimeQt::FeatureLayerInfo*> layerInfoList = serviceInfo.layers("states");

  if(!layerInfoList.isEmpty() && !layerInfoList.at(0)->url().isEmpty())
  {
    // give the feature service table the URL to the feature service layer
    EsriRuntimeQt::GeodatabaseFeatureServiceTable* featureServiceTable = new EsriRuntimeQt::GeodatabaseFeatureServiceTable(layerInfoList.at(0)->url(), this);
    // initialize the feature layer with the feature service table as its feature source
    m_featureLayer = new EsriRuntimeQt::FeatureLayer(featureServiceTable, this);
    m_map->addLayer(m_featureLayer);
  }
}
*/

/*
void Untitled3::onLocalServiceCreationSuccess(const QString& url, const QString& name)
{
  Q_UNUSED(url);
  Q_UNUSED(name);

   // create the ArcGISDynamicMapServiceLayer using the LocalMapService's url
   m_dynamicLocalServiceLayer = new EsriRuntimeQt::ArcGISDynamicMapServiceLayer(m_localMapService.urlMapService(), this);
   m_map->addLayer(m_dynamicLocalServiceLayer);
}
*/

/*
void Untitled3::onLocalServiceCreationFailure(const QString& name)
{
  qWarning() << name + " failed to start";
  qWarning() << m_localMapService.error().what();
}
*/

/*
void Untitled3::onFeatureServiceCreationSuccess(const QString& url, const QString& name)
{
  Q_UNUSED(url);
  Q_UNUSED(name);

  QString serviceUrl;
  EsriRuntimeQt::FeatureServiceInfo featureServiceInfo = m_localFeatureService.featureServiceInfo();
  QList<EsriRuntimeQt::FeatureLayerInfo*> layerInfoList= featureServiceInfo.layers("Cities");

  if(!layerInfoList.isEmpty())
    serviceUrl = layerInfoList.at(0)->url();

  if (serviceUrl.isEmpty())
  {
    qWarning() << "The required layer does not exist";
    return;
  }

  m_localFeatureLayer = new EsriRuntimeQt::ArcGISFeatureLayer(serviceUrl, this);
  m_map->addLayer(m_localFeatureLayer);
}
*/

/*
void Untitled3::onFeatureServiceCreationFailure(const QString& name)
{
  qWarning() << name + " failed to start";
  qWarning() << m_localFeatureService.error().what();
}
*/

