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

#ifndef UNTITLED3_H
#define UNTITLED3_H

namespace EsriRuntimeQt
{
class MapGraphicsView;
class Map;
class ArcGISLocalTiledLayer;
class ArcGISTiledMapServiceLayer;
class ArcGISDynamicMapServiceLayer;
class ArcGISFeatureLayer;
class GraphicsLayer;
class FeatureLayer;
}

//Uncomment if needed
#include "LocalMapService.h"
#include "LocalFeatureService.h"

#include <QMainWindow>

class Untitled3 : public QMainWindow
{
    Q_OBJECT
public:
    Untitled3 (QWidget *parent = 0);
    ~Untitled3 ();
    int x = -13000000;
    int y = 4000000;

public slots:
      void onMapReady();
      void onMousePress(QMouseEvent& event);
     // void onFeatureServiceInfoComplete(const EsriRuntimeQt::FeatureServiceInfo& serviceInfo);
    //  void onLocalServiceCreationSuccess(const QString& url, const QString& name);
    //  void onLocalServiceCreationFailure(const QString& name);
    //  void onFeatureServiceCreationSuccess(const QString& url, const QString& name);
    //  void onFeatureServiceCreationFailure(const QString& name);

private:
    EsriRuntimeQt::Map* m_map;
    EsriRuntimeQt::MapGraphicsView* m_mapGraphicsView;
      EsriRuntimeQt::ArcGISLocalTiledLayer* m_tiledLayer;
    EsriRuntimeQt::ArcGISTiledMapServiceLayer* m_tiledServiceLayer;
      EsriRuntimeQt::ArcGISDynamicMapServiceLayer* m_dynamicServiceLayer;
      EsriRuntimeQt::LocalMapService m_localMapService;
      EsriRuntimeQt::ArcGISDynamicMapServiceLayer* m_dynamicLocalServiceLayer;
      EsriRuntimeQt::LocalFeatureService m_localFeatureService;
      EsriRuntimeQt::ArcGISFeatureLayer* m_localFeatureLayer;
      EsriRuntimeQt::GraphicsLayer* m_graphicsLayer;
      EsriRuntimeQt::FeatureLayer* m_featureLayer;
};

#endif // UNTITLED3_H

