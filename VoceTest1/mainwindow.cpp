#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <voce.h>
#include <QtCore>
#include <QtGui>
#include <string>
#include <sstream>

//DANIELS GRAMMAR STUFF
#include <QString>
#include <QDebug>
#include <QStringList>
#include <cmath>
#include <stdlib.h>
#include <sstream>

//MAP STUFF

#include <QGridLayout>
#include "MapGraphicsView.h"
#include "Map.h"
#include "ArcGISRuntime.h"
#include "MapGraphicsView.h"
#include "Map.h"
#include "ArcGISRuntime.h"

// Uncomment if needed
//#include "ArcGISLocalTiledLayer.h"
#include "ArcGISTiledMapServiceLayer.h"
//#include "ArcGISDynamicMapServiceLayer.h"
//#include "ArcGISFeatureLayer.h"
//#include "GraphicsLayer.h"
//#include "Graphic.h"
//#include "SimpleMarkerSymbol.h"
//#include "Point.h"
//#include "ServiceInfoTask.h"
//#include "GeodatabaseFeatureServiceTable.h"
//#include "FeatureLayer.h"
//*****************************

#ifdef WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

//DANIELS GRAMMAR STUFF *********************************************************************************************************************************

int height = 0;
double latitude = 0;
double longitude = 0;
using namespace std;
std::string s;

QString getFirstWord(QString x){
    QStringList list1 = x.split(QRegExp("\\s"));
    x = list1[0];
    return x;
}
QString removeFirstWord(QString x){
    QStringList list1 = x.split(QRegExp("\\s"));
    x = "";
    for(int i = 0; i < list1.count()-1;i++)
    {
        x += list1[i+1]+" ";
    }
    return x;
}
int arr2int(QStringList nums,int arr[]){
    int number = 0;
    for(int i= 0; i< nums.count() ;i++){
        number += arr[i] * pow(10, nums.count() - i - 1);
    }
    return number;
}

void transformNums(QStringList nums){
    int *arr = new int [nums.count()];
    for(int i= 0; i < nums.count(); i++){                                                       //populate the int array
        if(nums[i] == "one"){
            arr[i] = 1;
        }
        else if(nums[i] == "two"){
            arr[i] = 2;
        }
        else if(nums[i] == "three"){
            arr[i] = 3;
        }
        else if(nums[i] == "four"){
            arr[i] = 4;
        }
        else if(nums[i] == "five"){
            arr[i] = 5;
        }
        else if(nums[i] == "six"){
            arr[i] = 6;
        }
        else if(nums[i] == "seven"){
            arr[i] = 7;
        }
        else if(nums[i] == "eight"){
            arr[i] = 8;
        }
        else if(nums[i] == "nine"){
            arr[i] = 9;
        }
    }
    height = arr2int(nums,arr);
    delete [] arr;
}
double transformNums(QStringList nums, string x){
    double *arr = new double [nums.count()];
    for(int i= 0; i < nums.count(); i++){
        if(nums[i] == "one"){
            arr[i] = 1;
        }
        else if(nums[i] == "two"){
            arr[i] = 2;
        }
        else if(nums[i] == "three"){
            arr[i] = 3;
        }
        else if(nums[i] == "four"){
            arr[i] = 4;
        }
        else if(nums[i] == "five"){
            arr[i] = 5;
        }
        else if(nums[i] == "six"){
            arr[i] = 6;
        }
        else if(nums[i] == "seven"){
            arr[i] = 7;
        }
        else if(nums[i] == "eight"){
            arr[i] = 8;
        }
        else if(nums[i] == "nine"){
            arr[i] = 9;
        }
        else if(nums[i] == "zero"){
            arr[i] = 0;
        }
        else{arr[i] = -99999;}
    }
    double number = 0;
    for(int i= 0; i< nums.count() ;i++){
        number += arr[i] * pow(10, nums.count() - i - 1);
        //cout<< "arr[i] * pow(10, nums.count() - i - 1) is "<<arr[i] * pow(10, nums.count() - i - 1) <<endl;
        //cout<<"arr[i] is " << arr[i]<<endl;
        //cout<<number<<endl;
    }
    //cout<<number<<endl;
    delete [] arr;
    return number;
}

void transformL(QStringList L,boolean lat, boolean lon){
    boolean execute = false;
    if(L.count() == 10){
        execute = true;
    }
    if(execute)
    {
    //qDebug()<<"this is the qstring before everything"<<L;
    boolean minus = false;
    if(L[0] == "minus"){
        minus = true;
    }
    L.removeFirst();
    QStringList bL;
    QStringList aL;
    bL.append(L[0]);
    bL.append(L[1]);
    double b = transformNums(bL,"");
    //qDebug()<<"THE SIZE OF AL before population"<<aL.count();
    aL.append(L[3]);
    aL.append(L[4]);
    aL.append(L[5]);
    aL.append(L[6]);
    aL.append(L[7]);
    L[8].chop(1);
    aL.append(L[8]);
    //qDebug()<<"the L[8] is "<<L[8];
    //qDebug()<<"THE SIZE OF AL after population"<<aL.count();
    double a = transformNums(aL,"");
    //cout<<transformNums(aL,"");
    //cout<<a;
    a = a * .000001;
    //cout<<a;
    double d = a+b;
    //qDebug()<<bL;
    //qDebug()<<aL;
   // cout<<b<<endl;
    //cout<<a<<endl;
    cout.precision(8);
    if(minus){
        d -= d*2;
    }
    cout<<"YOU HAVE SET IT TO "<<d;
    if(lat){
        latitude = d;
    }
    if(lon){
        longitude = d;
    }
  }else{
    cout<<"Invalid input. Format = +/- dd.dddddd";
  }
}

void manipCommand(QString qs){
    //first step search for the word 2
    //after the word 'to' will be the number except the last word
    //the last word is the measure
    boolean to = false;
    QStringList qsl = qs.split(QRegExp("\\s"));
    QStringList nums;
    for(int i = 0; i < qsl.count(); i++){
        if(qsl[i] == "to"){
         to = true;
         continue;
        }
        else if(i == qsl.count() -1 ){
         to = false;
         continue;
        }
        else if(to){
            nums += qsl[i];
            //qDebug()<<qsl[i];
        }
    }
    transformNums(nums);

}
void manipReport(QString str){
    QStringList list1 = str.split(QRegExp("\\s"));             //split it by every space and store each word into QStringList
    if(list1[1] == "height"){
    int xx = height;
    std::stringstream ss;   //convert the int height to a string
        ss << xx;
        string str1;
            ss >> str1;

    string j = "        The height is " + str1 + " feet ";
    //cout<<j;
    //ui->textBrowser->QTextBrowser::append("Cayley: " + QString::fromStdString(j));

    voce::synthesize(j);
    }
    if(list1[1] == "latitude"){
    double xx = latitude;
    std::stringstream ss;   //convert the int height to a string
        ss << xx;
        string str1;
            ss >> str1;

    string j = "        The latitude is " + str1 + " feet ";
    cout<<j;
    voce::synthesize(j);
    }
    if(list1[1] == "longitude"){
    double xx = longitude;
    std::stringstream ss;   //convert the int height to a string
        ss << xx;
        string str1;
            ss>> str1;

    string j = "        The longitude is " + str1 + " feet ";
    cout<<j;
    voce::synthesize(j);
    }


}
void manipSet(QString str){
    boolean latitude = false;
    boolean longitude = false;
    str = removeFirstWord(str);
    QStringList qsl = str.split(QRegExp("\\s"));
    if(qsl[0] == "latitude"){latitude = true;}
    if(qsl[0] == "longitude"){longitude = true;}
    QString L = "";
    for(int i = 0; i<qsl.count()-2;i++)
    {
        L += qsl[i+2]+" ";
        if(i == qsl.count()-3)
        {
            L.chop(2);
            L +=".";
        }
    }
    transformL(L.split(QRegExp("\\s")),latitude,longitude);
}

string Out(QStringList strL){
    //this function we will be recieving the QSlist and making the sentence past tense
    //returns the string in past tense and std string format.

    //DELETE THE LAST LETTER OF A QSTRING with this if statement
    if(strL[0][strL[0].count()-1] == 'e'){
        strL[0].chop(1);
    }
    //create the past tense output
    QString x = "       Roger that " + strL[0] + "ing";
    for(int i = 1; i < strL.count(); i++){
        x += (" " + strL[i]);
    }
    return x.toStdString();
}

void manipString(QString x){
    QString word = getFirstWord(x);
    if      (word == "emergency"){}
    else if (word == "change"||word == "fly"||word == "ascend"||word == "descend"){
        QStringList list1 = x.split(QRegExp("\\s"));             //split it by every space and store each word into QStringList
        string pTense = Out(list1);
        cout<<pTense<<endl;
        voce::synthesize(pTense);
        manipCommand(x);
    }
    else if (word == "report"){
        manipReport(x);
    }
    else if(word == "set"){manipSet(x);}
}
//*********************************************************************************************************************************

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButton->setText("Speak");
    ui->textEdit->installEventFilter(this);
    ui->label->setText("Type Command Here:");

    voce::init("C:/Users/Ernest Curioso/Documents/Voce/voce-0.9.1/voce-0.9.1/lib", true, true,
               "file:/C:/Users/Ernest Curioso/Documents/GitHub/teamcayley/VOCE/lib", "digits");
    voce::setRecognizerEnabled(false);
    voce::synthesize("Hello there. I'm Cayley.");

    //MAP STUFF ************************************************

    m_map = new EsriRuntimeQt::Map(this);

    //// connect to signal that is emitted when the map is ready
    //// the mapReady signal is emitted when the Map has obtained a
    //// spatial reference from an added layer
    // connect(m_map, SIGNAL(mapReady()), this, SLOT(onMapReady()));

    m_mapGraphicsView = EsriRuntimeQt::MapGraphicsView::create(m_map, this);
    //setCentralWidget(m_mapGraphicsView);
    ui->verticalLayout->addWidget(m_mapGraphicsView);
    m_map->setWrapAroundEnabled(false);

    QString path = EsriRuntimeQt::ArcGISRuntime::installDirectory();
    path.append("/sdk/samples/data");
    QDir dataDir(path); // using QDir to convert to correct file separator
    QString pathSampleData = dataDir.path() + QDir::separator();

    //// ArcGIS Online Tiled Basemap Layer
    m_tiledServiceLayer = new EsriRuntimeQt::ArcGISTiledMapServiceLayer("http://services.arcgisonline.com/ArcGIS/rest/services/World_Topo_Map/MapServer", this);
    m_map->addLayer(m_tiledServiceLayer);

    //// Local Tiled Basemap Layer using: sdk/samples/data/tpks/Topographic.tpk
    QString tiledBaseMapLayer = pathSampleData + "tpks" + QDir::separator() + "Topographic.tpk";
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

    // Graphics Layer
    /*
  EsriRuntimeQt::Point point1(0, 0, m_map->spatialReference());
  EsriRuntimeQt::SimpleMarkerSymbol redCircle(Qt::red, 10, EsriRuntimeQt::SimpleMarkerSymbolStyle::Circle);
  EsriRuntimeQt::Graphic* graphic1 = new EsriRuntimeQt::Graphic(point1, redCircle);
  m_graphicsLayer = new EsriRuntimeQt::GraphicsLayer(this);
  m_graphicsLayer->addGraphic(graphic1);
  m_map->addLayer(m_graphicsLayer);
  */

  //*******************************************************

}

MainWindow::~MainWindow()
{
    delete ui;
    voce::destroy();
}

void MainWindow::on_pushButton_pressed()
{
    voce::stopSynthesizing();
    voce::setRecognizerEnabled(true);
}

void MainWindow::on_pushButton_released()
{
    #ifdef WIN32
        ::Sleep(1500);
    #else
        usleep(1500);
    #endif

    s = voce::popRecognizedString();
    voce::setRecognizerEnabled(false);
    voce::stopSynthesizing();
    if (s.empty() == false)
    {
    ui->textBrowser->QTextBrowser::append("You said: " + QString::fromStdString(s));
    manipString(QString::fromStdString(s));
    }
}

bool MainWindow::eventFilter(QObject *object, QEvent *event)
{
    if (object == ui->textEdit && event->type() == QEvent::KeyPress)
    {
        voce::stopSynthesizing();

        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);

        if (keyEvent->key() == Qt::Key_Return)
        {
            QString r = ui->textEdit->toPlainText();
            s = r.toStdString();

            if (s != "")
            {
                QStringList list = r.split("\n");
                int length = list.length();

                for (int i = 0; i < length; i++)
                {
                    if (list[i] != "")
                    {
                        QStringList list2 = list[i].split(" ");
                        int length2 = list2.length();

                        for (int j = 0; j < length; j++)
                        {
                            if (list2[j] != "")
                            {
                                ui->textBrowser->QTextBrowser::append("You typed: " + QString::fromStdString(s));
                                manipString(QString::fromStdString(s));
                                ui->textEdit->QTextEdit::setText("");

                                return true;
                            }
                        }
                    }
                }
            }
            ui->textEdit->QTextEdit::setText("");
        }
        else
        {
            return QMainWindow::eventFilter(object, event);
        }
    }
    else
    {
        return QMainWindow::eventFilter(object, event);
    }
}
