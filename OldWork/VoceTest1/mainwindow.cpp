#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <voce.h>
#include <QtCore>
#include <QtGui>
#include <string>
#include <sstream>

// ***** GRAMMAR *****
#include "place.h"
#include <QString>
#include <QDebug>
#include <QStringList>
#include <cmath>
#include <stdlib.h>
#include <sstream>

// ***** MAP *****
#include <QGridLayout>
#include "MapGraphicsView.h"
#include "Map.h"
#include "ArcGISRuntime.h"
#include "MapGraphicsView.h"
#include "Map.h"
#include "ArcGISRuntime.h"
#include <QTimer>

// Uncomment if needed
//#include "ArcGISLocalTiledLayer.h"
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

//*****************************

#ifdef WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

// ***** GRAMMAR ***************

int height1 = 0;
double latitude = 0;
double longitude = 0;
using namespace std;
std::string s;
vector<string> strings;//global variable for all the strings spoken
bool nine = false;
bool eight = false;
bool set = false;
bool landCounter = false;
//int setD = 0;

void ELP()
{
//    const int arraysize = 3;
//    place arr[arraysize];
//    arr[0].name = "california";
//    arr[1].name = "texas";
//    arr[2].name = "florida";

//    arr[0].percent = rand() % 100;
//    arr[1].percent = rand() % 100;
//    arr[2].percent = rand() % 100;

//    int highestindex = 0;
//    if(arr[0].percent < arr[1].percent)
//        highestindex = 1;
//    if(arr[1].percent < arr[2].percent)
//        highestindex = 2;

//    boolean land = false;
//    boolean been = false;
//    int i = 1;

//    while(!land){
//        if(!been){
//        string out = "the aircraft is now landing to " + arr[highestindex].name.toStdString() + " because it has " + QString::number(arr[highestindex].percent).toStdString() + " percent  chance of landing. Should it land? Say Yes or Enter 0 to land enter 9 or say no for other percentages";
//     cout<<out<<endl;
//     voce::synthesize(out);
//     been = true;
//        }
//        string j = voce::popRecognizedString();
//        cout<<j;

//        //cin>>i;
//     if(i == 0 || j == "yes"){
//         land = true;
//         cout<<" \nThank you now landing";
//         voce::synthesize(" Thank you now landing");
//        }
//     else if(i == 9|| j == "no"){
//         for(int i = 0; i < arraysize; i++){
//             qDebug()<< "place: " <<arr[i].name;
//             qDebug()<< "percent: "<<arr[i].percent;
//             cout<<endl;
//      }
//    }
//  }
}

QString getFirstWord(QString x)
{
    QStringList list1 = x.split(QRegExp("\\s"));
    x = list1[0];
    return x;
}

QString removeFirstWord(QString x)
{
    QStringList list1 = x.split(QRegExp("\\s"));
    x = "";

    for(int i = 0; i < list1.count()-1;i++)
    {
        x += list1[i+1]+" ";
    }

    return x;
}

int arr2int(QStringList nums,int arr[])
{
    int number = 0;

    for(int i= 0; i< nums.count() ;i++)
    {
        number += arr[i] * pow(10, nums.count() - i - 1);
    }

    return number;
}

void transformNums(QStringList nums)
{
    int *arr = new int [nums.count()];

    for(int i= 0; i < nums.count(); i++)
    {                                       //populate the int array
        if(nums[i] == "one")
        {
            arr[i] = 1;
        }
        else if(nums[i] == "two")
        {
            arr[i] = 2;
        }
        else if(nums[i] == "three")
        {
            arr[i] = 3;
        }
        else if(nums[i] == "four")
        {
            arr[i] = 4;
        }
        else if(nums[i] == "five")
        {
            arr[i] = 5;
        }
        else if(nums[i] == "six")
        {
            arr[i] = 6;
        }
        else if(nums[i] == "seven")
        {
            arr[i] = 7;
        }
        else if(nums[i] == "eight")
        {
            arr[i] = 8;
        }
        else if(nums[i] == "nine")
        {
            arr[i] = 9;
        }
        else if(nums[i] == "zero")
        {
            arr[i] = 0;
        }
    }

    height1 = arr2int(nums,arr);
    delete [] arr;
}

double transformNums(QStringList nums, string x)
{
    double *arr = new double [nums.count()];

    for(int i= 0; i < nums.count(); i++)
    {
        if(nums[i] == "one")
        {
            arr[i] = 1;
        }
        else if(nums[i] == "two")
        {
            arr[i] = 2;
        }
        else if(nums[i] == "three")
        {
            arr[i] = 3;
        }
        else if(nums[i] == "four")
        {
            arr[i] = 4;
        }
        else if(nums[i] == "five")
        {
            arr[i] = 5;
        }
        else if(nums[i] == "six")
        {
            arr[i] = 6;
        }
        else if(nums[i] == "seven")
        {
            arr[i] = 7;
        }
        else if(nums[i] == "eight")
        {
            arr[i] = 8;
        }
        else if(nums[i] == "nine")
        {
            arr[i] = 9;
        }
        else if(nums[i] == "zero")
        {
            arr[i] = 0;
        }
        else
        {
            arr[i] = -99999;
        }
    }

    double number = 0;

    for(int i= 0; i< nums.count() ;i++)
    {
        number += arr[i] * pow(10, nums.count() - i - 1);
        //cout<< "arr[i] * pow(10, nums.count() - i - 1) is "<<arr[i] * pow(10, nums.count() - i - 1) <<endl;
        //cout<<"arr[i] is " << arr[i]<<endl;
        //cout<<number<<endl;
    }

    //cout<<number<<endl;
    delete [] arr;
    return number;
}

void transformL(QStringList L,boolean lat, boolean lon)
{
    //setD++;
    //either two digits before the decimal or three digits before the decimal
    boolean execute2,execute10,execute11 = false;

    if(L.count() == 3)
    {
        execute2 = true;
    }
    if(L.count() == 10)
    {
        execute10 = true;
    }
    if(L.count() == 11)
    {
        execute11 = true;
    }
    if(execute2)
    {
        //qDebug()<<"this is the qstring before everything"<<L;
        boolean minus = false;

        if(L[0] == "minus")
        {
            minus = true;
            qDebug()<<L[0];
        }

        L.removeFirst();
        QStringList bL;
        bL.append(L[0]);
        L[1].chop(1);
        bL.append(L[1]);
        double b = transformNums(bL,"");
        qDebug()<<L[0];
        qDebug()<<L[1];

        //cout<<a;
        double d = b;
        //qDebug()<<bL;
        //qDebug()<<aL;
        //cout<<b<<endl;
        //cout<<a<<endl;

        if(minus)
        {
            d -= d*2;
        }

        cout<<"YOU HAVE SET IT TO "<<d;
        voce::synthesize("it has been set");

        if(lat)
        {
            latitude = d;
        }
        if(lon)
        {
            longitude = d;
        }
    }

    if(execute10)
    {
        //qDebug()<<"this is the qstring before everything"<<L;
        boolean minus = false;

        if(L[0] == "minus")
        {
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
        //cout<<b<<endl;
        //cout<<a<<endl;
        cout.precision(8);

        if(minus)
        {
            d -= d*2;
        }

        cout<<"YOU HAVE SET IT TO "<<d;
        voce::synthesize("it has been set");
        if(lat)
        {
            latitude = d;
        }

        if(lon)
        {
            longitude = d;
        }
    }

    //**********************************************************

    if(execute11)
    {
        //qDebug()<<"this is the qstring before everything"<<L;
        boolean minus = false;

        if(L[0] == "minus")
        {
            minus = true;
        }

        L.removeFirst();
        QStringList bL;
        QStringList aL;
        bL.append(L[0]);
        bL.append(L[1]);
        bL.append(L[2]);
        double b = transformNums(bL,"");
        //qDebug()<<"THE SIZE OF AL before population"<<aL.count();
        aL.append(L[4]);
        aL.append(L[5]);
        aL.append(L[6]);
        aL.append(L[7]);
        aL.append(L[8]);
        L[9].chop(1);
        aL.append(L[9]);
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
        //cout<<b<<endl;
        //cout<<a<<endl;
        cout.precision(9);

        if(minus)
        {
            d -= d*2;
        }

        cout<<"YOU HAVE SET IT TO "<<d;
        voce::synthesize("it has been set");

        if(lat)
        {
            latitude = d;
        }

        if(lon)
        {
            longitude = d;
        }
    }

    //**********************************************************

    else
    {
        cout<<"Invalid input. Format = +/- dd.dddddd";
    }

    if(longitude != 0 && latitude != 0)
    {
        //CALL THE SETDESTINATION ON THE MAP
        cout<<"setDEST()";
        set = true;
        //MainWindow::land = false;
        //MainWindow::coord(latitude,longitude);
    }
}

void manipCommand(QString qs)
{
    //first step search for the word 2
    //after the word 'to' will be the number except the last word
    //the last word is the measure
    boolean to = false;
    QStringList qsl = qs.split(QRegExp("\\s"));
    QStringList nums;

    for(int i = 0; i < qsl.count(); i++)
    {
        if(qsl[i] == "to")
        {
            to = true;
            continue;
        }
        else if(i == qsl.count() -1 )
        {
            to = false;
            continue;
        }
        else if(to)
        {
            nums += qsl[i];
            //qDebug()<<qsl[i];
        }
    }

    transformNums(nums);
}

string manipReport(QString str)
{
    boolean minuss = false;
    QStringList list1 = str.split(QRegExp("\\s"));             //split it by every space and store each word into QStringList

    if(list1[1] == "height")
    {
        int xx = height1;
        std::stringstream ss;   //convert the int height1 to a string
        ss << xx;
        string str1;
        ss >> str1;

        string j = "The height is " + str1 + " feet ";
        cout<<j<<endl;
        voce::synthesize(j);

        return j;
    }    
    else if(list1[1] == "latitude")
    {
        double xx = latitude;
        std::stringstream ss;   //convert the int height1 to a string
        ss << xx;
        string str1;
        ss >> str1;

        string j = "The latitude is " + str1 + " feet ";
        cout<<j<<endl;
        voce::synthesize(j);

        return j;
    }
    else if(list1[1] == "longitude")
    {
        double xx = longitude;
        std::stringstream ss;   //convert the int height1 to a string
        ss << xx;
        string str1;
        ss>> str1;

        string j = "The longitude is " + str1 + " feet ";
        cout<<j<<endl;
        voce::synthesize(j);

        return j;
    }
    else if(list1[1] == "destination")
    {
        cout<<latitude<<" "<<longitude;
        double xx = latitude;
        std::stringstream ss;   //convert the int height1 to a string
        ss << xx;
        string str1;
        ss >> str1;

        double xy = longitude;

        if(longitude < 0)
        {
            minuss = true;
        }

        std::stringstream sy;   //convert the int height1 to a string
        sy << xy;
        string stry;
        sy >> stry;

        string j = "The latitude is " + str1 + " degrees " + "\n The longitude is" + stry + " degrees.";

        if(minuss)
        {
             j = "The latitude is " + str1 + " degrees " + "\n The longitude is negative" + stry + " degrees.";
        }

        cout<<j<<endl;
        voce::synthesize(j);

        return j;
    }

    return "Invalid report input.";
}

void manipSet(QString str)
{
    boolean latitude = false;
    boolean longitude = false;
    str = removeFirstWord(str);
    QStringList qsl = str.split(QRegExp("\\s"));

    if(qsl[0] == "latitude")
    {
         latitude = true;
    }

    if(qsl[0] == "longitude")
    {
        longitude = true;
    }

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

string Out(QStringList strL)
{
    //this function we will be recieving the QSlist and making the sentence past tense
    //returns the string in past tense and std string format.

    //DELETE THE LAST LETTER OF A QSTRING with this if statement
    if(strL[0][strL[0].count()-1] == 'e')
    {
        strL[0].chop(1);
    }

    //create the past tense output
    QString x = "Roger that. " + strL[0] + "ing";

    for(int i = 1; i < strL.count(); i++)
    {
        x += (" " + strL[i]);
    }
    return x.toStdString();
}

string manipString(QString x)
{
    QString word = getFirstWord(x);

    if (word == "emergency")
    {
        voce::synthesize("E L P not configured.");
        return "ELP not configured.";
    }
    else if (word == "change"||word == "fly"||word == "ascend"||word == "descend")
    {
        QStringList list1 = x.split(QRegExp("\\s"));    //split it by every space and store each word into QStringList
        string pTense = Out(list1);
        cout<<pTense<<endl;
        voce::synthesize(pTense);
        manipCommand(x);
        return pTense;
    }
    else if (word == "report")
    {
        qDebug()<<"made it here";
        string temp = manipReport(x);
        qDebug()<<"made it here";
        voce::synthesize(temp);
        qDebug()<<"made it here";
        qDebug()<<QString::fromStdString(temp);
        return temp;
    }
    else if(word == "set")
    {
        manipSet(x);
        return " ";
    }
    else
    {
        voce::synthesize("Invalid input.");
        return "Invalid input.";
    }
}

//***** Main Window ***************************************************************

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->textEdit->installEventFilter(this);

    this->setStyleSheet("background-color: black;");

    ui->label->setText("Type Command Here:");
    ui->label->setStyleSheet("color: #33FF00;");

    ui->title->setStyleSheet("color: #33FF00;"
                             "background-color: #585858;");

    ui->pushButton->setStyleSheet("background-color: #FF0000;");
    ui->pushButton->setIcon(QIcon("C:/Users/Ernest Curioso/Downloads/Microphone 1"));
    ui->pushButton->setIconSize(QSize(30,30));

    ui->textEdit->setStyleSheet("background-color: #585858;"
                                "color: yellow;");

    ui->textBrowser->setStyleSheet("background-color: #585858;"
                                   "color: yellow;");

    ui->textBrowser_2->setStyleSheet("background-color: #585858;"
                                     "color: yellow;");

    voce::init("C:/Users/Ernest Curioso/Documents/Voce/voce-0.9.1/voce-0.9.1/lib", true, true,
               "file:/C:/Users/Ernest Curioso/Documents/GitHub/teamcayley/VOCE/lib", "digits");
    voce::setRecognizerEnabled(false);
    voce::synthesize("Hello there. I'm Cayley.");

    //**************** MAP ************************************************

    m_map = new EsriRuntimeQt::Map(this);

    //// connect to signal that is emitted when the map is ready
    //// the mapReady signal is emitted when the Map has obtained a
    //// spatial reference from an added layer
    connect(m_map, SIGNAL(mapReady()), this, SLOT(onMapReady()));

    //add qtimer
    QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(20);

    m_mapGraphicsView = EsriRuntimeQt::MapGraphicsView::create(m_map, this);
    //setCentralWidget(m_mapGraphicsView);
    ui->verticalLayout->addWidget(m_mapGraphicsView);
    m_map->setWrapAroundEnabled(false);

    QString path = EsriRuntimeQt::ArcGISRuntime::installDirectory();
    path.append("/sdk/samples/data");
    QDir dataDir(path); // using QDir to convert to correct file separator
    QString pathSampleData = dataDir.path() + QDir::separator();

    //// ArcGIS Online Tiled Basemap Layer
    //m_tiledServiceLayer = new EsriRuntimeQt::ArcGISTiledMapServiceLayer("http://services.arcgisonline.com/ArcGIS/rest/services/World_Topo_Map/MapServer", this);
    m_tiledServiceLayer = new EsriRuntimeQt::ArcGISTiledMapServiceLayer("http://services.arcgisonline.com/arcgis/rest/services/ESRI_StreetMap_World_2D/MapServer", this);
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

    // Graphics Layer

    //EsriRuntimeQt::Point point1(0, 0, m_map->spatialReference());
    //EsriRuntimeQt::SimpleMarkerSymbol redCircle(Qt::red, 10, EsriRuntimeQt::SimpleMarkerSymbolStyle::Circle);
    //EsriRuntimeQt::Graphic* graphic1 = new EsriRuntimeQt::Graphic(point1, redCircle);
    m_graphicsLayer = new EsriRuntimeQt::GraphicsLayer(this);
    //m_graphicsLayer->addGraphic(graphic1);
    //m_map->addLayer(m_graphicsLayer);

    //***** END MAP ********************************************************************************************
}

void MainWindow::onMapReady()
{
    //locationSymbol(EsriRuntimeQt::PictureMarkerSymbol(QImage(":/new/prefix1/airplane.png")));
    m_map->setExtent(EsriRuntimeQt::Envelope(-130, 55, -60, 20, m_map->spatialReference()));

    EsriRuntimeQt::Graphic *graphic1;
    EsriRuntimeQt::Point point1(-118, 34, m_map->spatialReference());
    EsriRuntimeQt::SimpleMarkerSymbol redCircle(Qt::red, 10, EsriRuntimeQt::SimpleMarkerSymbolStyle::Circle);
    //EsriRuntimeQt::PictureMarkerSymbol locationSymbol(QUrl ("qrc:/new/prefix1/airplane.png"));
    graphic1 = new EsriRuntimeQt::Graphic(point1,redCircle);

    m_graphicsLayer->addGraphic(graphic1);
    m_map->addLayer(m_graphicsLayer);
}

void MainWindow::move()
{
    ui->textBrowser_2->QTextBrowser::setText("Height: " + QString::number(height1)+
                                             "\n" "Destination Lat: " + QString::number(latitude)+
                                             "\n" "Destination Lon: " +QString::number(longitude)+
                                             "\n" "\n" + "Latitude: " + QString::number(y) +
                                             "\n" "Longitude: " + QString::number(x));

    /*
    qDebug() << height1;
    qDebug() << latitude;
    qDebug() << longitude;
    */

    if(set)
    {
       // coord(latitude,longitude);
        setDestination(longitude,latitude);
        set = false;
        land = false;
    }

    //qDebug()<<(x < newX);
    int var_x = (int)x;
    int var_x2 = (int)newX;
    int var_y = (int)y;
    int var_y2 = (int)newY;

    if(var_x == var_x2 && var_y == var_y2)
    {
        land = true;
        qDebug()<<"INSIDE";

        if(!landCounter)
        {
            latitude = 0;
            longitude = 0;
        }

        landCounter = true;
    }

    if(!land)
    {
        landCounter = false;
        // Graphics Layer

        EsriRuntimeQt::Graphic *graphic1;
        //qDebug() << m_map->spatialReference().wkid();

        if(steps >= 0)
        {
            m_graphicsLayer->removeGraphics(m_graphicsLayer->graphicIds());
            EsriRuntimeQt::Point point1(x, y, m_map->spatialReference());
            //qDebug() << x + " " + y;
            EsriRuntimeQt::SimpleMarkerSymbol redCircle(Qt::red, 10, EsriRuntimeQt::SimpleMarkerSymbolStyle::Circle);
            graphic1 = new EsriRuntimeQt::Graphic(point1, redCircle);

            m_graphicsLayer->addGraphic(graphic1);
            m_map->addLayer(m_graphicsLayer);
            //qDebug()<<"x is "<<QString::number(x);
            //qDebug()<<"y is "<<QString::numer(y);
            //qDebug()<<"newY is "<<newY;
            //qDebug()<<"newX is "<<newX;
            //qDebug() << height1;

           // x += .1; y += SLOPE*(.1);
            x += xStep; y += yStep;
        }

        steps--;

        if(steps == 0)
        {
            land = true;
            qDebug()<<"INSIDE";

            if(!landCounter)
            {
                latitude = 0;
                longitude = 0;
            }

            landCounter = true;
        }
    }
}

 void MainWindow::coord(double lat, double lon)
{
    newY = lat;
    newX = lon;
    qDebug()<<"coord has been called";
    SLOPE = (latitude - y) / (lon - x);
}

 void MainWindow::setDestination(double destX, double destY)
{
     //destX = long, destY = lat
     steps = 450;//greater = faster, smaller = slower
     dx = destX;
     dy = destY;
     //double totalDist = sqrt(pow((dx - x),2) + pow((dy - y),2));
     xStep = (dx-x)/steps;
     yStep = (dy-y)/steps;
}


MainWindow::~MainWindow()
{
    delete ui;
    voce::destroy();
}

void MainWindow::on_pushButton_pressed()
{
    ui->pushButton->setStyleSheet("background-color: #33ff00;");
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

    ui->pushButton->setStyleSheet("background-color: #FF0000;");
    s = voce::popRecognizedString();
    voce::setRecognizerEnabled(false);
    voce::stopSynthesizing();

    if (s.empty() == false)
    {
        ui->textBrowser->QTextBrowser::append("You said: " + QString::fromStdString(s));
        string temp = manipString(QString::fromStdString(s));
        ui->textBrowser->QTextBrowser::append("Cayley: " + QString::fromStdString(temp));
    }
    else
    {
        ui->textBrowser->QTextBrowser::append("Cayley: I didn't hear what you said.");
        voce::synthesize("I didn't hear what you said.");
    }
}

bool MainWindow::eventFilter(QObject *object, QEvent *event)
{
    if (object == ui->textEdit && event->type() == QEvent::KeyPress)
    {
        voce::stopSynthesizing();

        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);

        if ((keyEvent->key() == Qt::Key_Return) || (keyEvent->key() == Qt::Key_Enter))
        {
            QString r = ui->textEdit->toPlainText();
            s = r.toStdString();

            ui->textBrowser->QTextBrowser::append("You typed: " + QString::fromStdString(s));
            ui->textEdit->QTextEdit::setText("");
            string temp = manipString(QString::fromStdString(s));
            ui->textBrowser->QTextBrowser::append("Cayley: " + QString::fromStdString(temp));

            return true;
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

    return QMainWindow::eventFilter(object, event);
}
