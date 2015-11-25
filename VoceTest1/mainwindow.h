#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
//#include "LocalMapService.h"
//#include "LocalFeatureService.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    //  void onMapReady();
    //  void onFeatureServiceInfoComplete(const EsriRuntimeQt::FeatureServiceInfo& serviceInfo);
    //  void onLocalServiceCreationSuccess(const QString& url, const QString& name);
    //  void onLocalServiceCreationFailure(const QString& name);
    //  void onFeatureServiceCreationSuccess(const QString& url, const QString& name);
    //  void onFeatureServiceCreationFailure(const QString& name);

private slots:

    void on_pushButton_pressed();

    void on_pushButton_released();

protected:
    bool eventFilter(QObject *, QEvent *);

private:
    EsriRuntimeQt::Map* m_map;
    EsriRuntimeQt::MapGraphicsView* m_mapGraphicsView;
    //  EsriRuntimeQt::ArcGISLocalTiledLayer* m_tiledLayer;
    EsriRuntimeQt::ArcGISTiledMapServiceLayer* m_tiledServiceLayer;
    //  EsriRuntimeQt::ArcGISDynamicMapServiceLayer* m_dynamicServiceLayer;
    //  EsriRuntimeQt::LocalMapService m_localMapService;
    //  EsriRuntimeQt::ArcGISDynamicMapServiceLayer* m_dynamicLocalServiceLayer;
    //  EsriRuntimeQt::LocalFeatureService m_localFeatureService;
    //  EsriRuntimeQt::ArcGISFeatureLayer* m_localFeatureLayer;
    //  EsriRuntimeQt::GraphicsLayer* m_graphicsLayer;
    //  EsriRuntimeQt::FeatureLayer* m_featureLayer;

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
