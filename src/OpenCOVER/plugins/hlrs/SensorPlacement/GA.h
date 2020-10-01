#pragma once
#include <openGA.h>
#include <Sensor.h>
#include <Zone.h>

#include <fstream>

struct Solution{

    std::vector<Orientation*> sensors;
    // std::vector<SensorZone*> sensorZones;
};

struct MiddleCost{

    double objective;
};

struct SensorPool
{
public:
    SensorPool();
    Orientation* getRandomOrientation(int pos, const std::function<double(void)> &rnd01) const; 

private:
    std::vector<SensorPosition*> m_Sensors;
    std::vector<SensorZone*> m_SensorZones;
};

enum class FitnessFunctionType
{
    MaxCoverage1,
    MaxCoverage2
};

struct PropertiesMaxCoverage1
{
    float weightingFactorPRIO1{3.0};
    //float PenaltyFactorPRIO1{1.0};      //not necessary ?
    //float PenaltyFactorPRIO2{1.0};      //not necessary ?
    float thresholdVisibility{0.5};     //the sum(all Vismats)/ RequiredSensorsForThisPoint > thresholdVisibility
};

struct PropertiesMaxCoverage2
{
    float m_PenaltyConstant;
    float m_RequiredCoverage{0.8};  
    float m_ThresholdVisibility{0.5};
};

class GA
{
public:
    using FitnessFunction = std::function<bool(const Solution& p, MiddleCost &c)>;
    GA(FitnessFunctionType fitness);

    float m_CrossoverRate{0.7};
    float m_MutationRate{0.3};
    int m_PopulationSize{3000};
    int m_MaxGeneration{1000};
    bool m_DynamicThreading{false};

    std::vector<Orientation> getFinalOrientations() const;


private:
    FitnessFunction m_FitnessFunction; 
    std::ofstream m_Results;

    SensorPool m_SensorPool{};
    int m_NumberOfSensors;
    int m_NumberOfObservationPoints;
    int m_NumberOfPrio1Points;
    std::vector<int> m_RequiredSensorsPerPoint; 
    
    PropertiesMaxCoverage1 m_PropsMaxCoverage1;
    PropertiesMaxCoverage2 m_PropsMaxCoverage2;

    typedef EA::Genetic<Solution,MiddleCost> GA_Type;
    typedef EA::GenerationType<Solution,MiddleCost> Generation_Type;
    GA_Type ga_obj;

    // GA functions
    void init_genes(Solution& p,const std::function<double(void)> &rnd01);
    Solution mutate(const Solution& X_base,const std::function<double(void)> &rnd01,double shrink_scale);
    Solution crossover(const Solution& X1, const Solution& X2,const std::function<double(void)> &rnd01);
    double calculate_SO_total_fitness(const GA_Type::thisChromosomeType &X);
    void SO_report_generation(int generation_number,const EA::GenerationType<Solution,MiddleCost> &last_generation,const Solution& best_genes);
    bool optimizationStrategy(const Solution& p, MiddleCost &c);

    // available Fitness Functions
    bool maxCoverage1(const Solution& p, MiddleCost &c);
    bool maxCoverage2(const Solution& p, MiddleCost &c);

    int coverEachPointWithMin1Sensor(std::vector<int>& nbrOfCameras, std::vector<float> &sumVisMat); 
    int sumOfCoveredPrio1Points(const std::vector<int>& sensorsPerPoint, const std::vector<int>& requiredSensorsPerPoint, const std::vector<float>& sumVisMat) const;
    
    
    const Orientation* getRandomSensor(int sensorPosition ,const std::function<double(void)> &rnd01)const;
    void calcZonePriorities();
};

