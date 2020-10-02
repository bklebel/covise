
#include "UI.h"
#include "Helper.h"

#include "DataManager.h"
#include "Factory.h"
#include "GA.h"
#include "SensorPlacement.h"

using namespace opencover;

bool UI::m_DeleteStatus{false};
bool UI::m_showOrientations{true};
bool UI::m_showAverageUDPPositions{false};
bool UI::m_showShortestUDPPositions{true};


UI::UI() : ui::Owner("SensorPlacementUI", cover->ui)
{
   // Main menu-------------------------------------------------------------------------------
    m_MainMenu = new ui::Menu("SensorPlacement",this);

    m_AddCamera = new ui::Action(m_MainMenu,"AddCamera");
    m_AddCamera-> setText("Add Camera");
    m_AddCamera-> setCallback([]()
    {
       DataManager::AddSensor(createSensor(SensorType::Camera));
    }
    );

    m_AddSafetyZonePrio1 = new ui::Action(m_MainMenu,"AddSafetyZonePRIO1");
    m_AddSafetyZonePrio1-> setText("Add PRIO1 Zone");
    m_AddSafetyZonePrio1-> setCallback([]()
    {
       osg::Matrix m;
       m.setTrans(osg::Vec3(20,20,20));
       DataManager::AddSafetyZone(createSafetyZone(SafetyZone::Priority::PRIO1));
    }
    );

    m_AddSafetyZonePrio2 = new ui::Action(m_MainMenu,"AddSafetyZonePRIO2");
    m_AddSafetyZonePrio2-> setText("Add PRIO2 Zone");
    m_AddSafetyZonePrio2-> setCallback([]()
    {
       osg::Matrix m;
       m.setTrans(osg::Vec3(20,20,20));
       DataManager::AddSafetyZone(createSafetyZone(SafetyZone::Priority::PRIO2));
    }
    );

    m_AddSensorZone = new ui::Action(m_MainMenu,"AddSensorZone");
    m_AddSensorZone-> setText("Add Sensor Zone");
    m_AddSensorZone-> setCallback([this]()
    {
       osg::Matrix m;
       m.setTrans(osg::Vec3(20,20,20));
       DataManager:: AddSensorZone(createSensorZone());
    }
    );

    m_Delete = new ui::Button(m_MainMenu,"Delete");
    m_Delete->setText("Remove");
    m_Delete->setState(m_DeleteStatus);
    m_Delete->setCallback([this](bool state)
    {
      m_DeleteStatus = state;
      if(m_DeleteStatus)
         std::cout<<"Delete Status"<<m_DeleteStatus<<std::endl;
    });

   // Sensor Menu-------------------------------------------------------------------------------
   m_SensorProps = new ui::Menu(m_MainMenu,"SensorProps");
   m_SensorProps->setText("Sensor Properties");

   m_ShowOrientations = new ui::Button(m_SensorProps,"ShowOrientations");
   m_ShowOrientations->setText("Show Orientations");
   m_ShowOrientations->setState(m_showOrientations);
   m_ShowOrientations->setCallback([this](bool state)
   {
      m_showOrientations = state;
   });

   // Camera Menu------------------------------------------------------------------------------------
    m_CameraProps = new ui::Menu(m_SensorProps,"CameraProps");
    m_CameraProps->setText("Camera Properties");

    m_Visibility = new ui::Slider(m_CameraProps,"Visibility");
    m_Visibility->setText("Visibility [ % ]");
    m_Visibility->setBounds(10., 100.);
    m_Visibility->setCallback([](double value, bool released)
    {

    });

   //Optimization Menu-------------------------------------------------------------------------------
   m_Optimization = new ui::Menu(m_MainMenu, "Optimization");
   m_Optimization->setText("Optimization");
   
   m_MaxCoverage1 = new ui::Action(m_Optimization,"MaxCoverage1");
   m_MaxCoverage1-> setText("MaxCoverage1");
   m_MaxCoverage1-> setCallback([this]()
   {
      optimize(FitnessFunctionType::MaxCoverage1); 
   });
   

   m_MaxCoverage2 = new ui::Action(m_Optimization,"MaxCoverage2");
   m_MaxCoverage2-> setText("MaxCoverage2");
   m_MaxCoverage2-> setCallback([this]()
   {
      optimize(FitnessFunctionType::MaxCoverage2);
   });


    //UDP Menu-------------------------------------------------------------------------------
   m_UDP = new ui::Menu(m_MainMenu, "UDP");
   m_UDP->setText("UDP");


   m_showAverageUDPObjectionPosition = new ui::Button(m_UDP,"Average_positions");
   m_showAverageUDPObjectionPosition->setText("Average positions");
   m_showAverageUDPObjectionPosition->setState(m_showAverageUDPPositions);
   m_showAverageUDPObjectionPosition->setCallback([this](bool state)
   {
      m_showAverageUDPPositions = state;
   });

   m_showShortestUDPObjectionPosition = new ui::Button(m_UDP,"Shortest_positions");
   m_showShortestUDPObjectionPosition->setText("Shortest positions");
   m_showShortestUDPObjectionPosition->setState(m_showShortestUDPPositions);
   m_showShortestUDPObjectionPosition->setCallback([this](bool state)
   {
      m_showShortestUDPPositions = state;
   });



};

