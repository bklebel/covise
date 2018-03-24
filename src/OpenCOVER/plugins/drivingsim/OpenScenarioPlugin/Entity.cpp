#include "Entity.h"
#include "ReferencePosition.h"
using namespace std;

Entity::Entity(string entityName, string catalogReferenceName):
	name(entityName),
    catalogReferenceName(catalogReferenceName),
    totalDistance(0),
    visitedVertices(0),
    refPos(NULL),
    newRefPos(NULL),
    dt(0.0)
{
	directionVector.set(1, 0, 0);
}

void Entity::setInitEntityPosition(osg::Vec3 initPos)
{
	entityGeometry = new AgentVehicle(name, new CarGeometry(name, filepath, true));
	entityGeometry->setPosition(initPos, directionVector);
}

void Entity::setInitEntityPosition(Road *r)
{
    entityGeometry = new AgentVehicle(name, new CarGeometry(name, filepath, true),0,r,inits,laneId,speed,1);
    // Road r; s inits;
	auto vtrans = entityGeometry->getVehicleTransform();
	osg::Vec3 pos(vtrans.v().x(), vtrans.v().y(), vtrans.v().z());
	entityPosition = pos;
	entityGeometry->setPosition(pos, directionVector);
}

void Entity::setInitEntityPosition(ReferencePosition* init_refPos)
{
    entityGeometry = new AgentVehicle(name, new CarGeometry(name, filepath, true),0,init_refPos->road,init_refPos->s,init_refPos->laneId,speed,1);

    if(init_refPos->road != NULL)
    {
        auto vtrans = entityGeometry->getVehicleTransform();
        osg::Vec3 pos(vtrans.v().x(), vtrans.v().y(), vtrans.v().z());
        entityPosition = pos;
        entityGeometry->setTransform(vtrans,init_refPos->hdg);

    }
    else
    {
        entityPosition = init_refPos->xyz;

        directionVector[0] = cos(init_refPos->hdg);
        directionVector[1] = sin(init_refPos->hdg);


        entityGeometry->setPosition(entityPosition, directionVector);

    }

}


void Entity::moveLongitudinal()
{
    if(refPos->road != NULL)
    {
        float step_distance = speed*opencover::cover->frameDuration();
        double ds = 1.0;
        double dt = 0.0;

        refPos->move(ds,dt,step_distance);

        Transform vehicleTransform = refPos->road->getRoadTransform(refPos->s, refPos->t);
        entityGeometry->setTransform(vehicleTransform,refPos->hdg);
        //cout << name << " is driving on Road: " << refPos->roadId << endl;
    }
    else
    {
        entityGeometry->setPosition(refPos->xyz, directionVector);
    }

}

osg::Vec3 Entity::getPosition()
{
    return refPos->getPosition();
}

void Entity::setPosition(osg::Vec3 &newPosition)
{
	entityPosition = newPosition;
	entityGeometry->setPosition(newPosition, directionVector);
}

string &Entity::getName()
{
	return name;
}

void Entity::setSpeed(float speed_temp)
{
	speed = speed_temp;
}


float &Entity::getSpeed()
{
	return speed;
}

void Entity::setDirection(osg::Vec3 &dir)
{
    directionVector = dir;
    directionVector.normalize();

}

void Entity::setTrajectoryDirection()
{
    // entity is heading to targetPosition
    targetPosition = refPos->getPosition();
    totaldirectionVector = targetPosition - newRefPos->getPosition();
    totaldirectionVectorLength = totaldirectionVector.length();

    directionVector = totaldirectionVector;
    directionVector.normalize();
}


void Entity::setTrajSpeed(float deltat)
{

    // calculate length of targetvector

    speed = totaldirectionVectorLength/deltat;


}

void Entity::setTrajectoryDirectionOnRoad()
{
    targetPosition = newRefPos->getPosition();
    totaldirectionVector = targetPosition - refPos->getPosition();
    totaldirectionVectorLength = totaldirectionVector.length();

    directionVector = totaldirectionVector;
    directionVector.normalize();



}

void Entity::followTrajectoryOnRoad(int verticesCounter,std::list<Entity*> *activeEntityList)
{

    float step_distance = opencover::cover->frameDuration()*speed;

    if(totalDistance == 0)
    {
        totalDistance = totaldirectionVectorLength;
    }
    //calculate remaining distance
    totalDistance = totalDistance-step_distance;

    if(totalDistance <= 0)
    {
        cout << "Arrived at " << visitedVertices << endl;
        visitedVertices++;
        totalDistance = 0;
        if(visitedVertices == verticesCounter)
        {
            activeEntityList->remove(this);
        }
    }


    if(refPos->road != NULL)
    {
        double ds = newRefPos->s - refPos->s;
        double dt = newRefPos->t - refPos->t;

        refPos->move(ds,dt,step_distance);
        Transform vehicleTransform = refPos->road->getRoadTransform(refPos->s, refPos->t);
        entityGeometry->setTransform(vehicleTransform,refPos->hdg);
    }
    else
    {
        directionVector = newRefPos->getPosition() -refPos->getPosition();
        refPos->move(directionVector,step_distance);
        osg::Vec3 pos = refPos->getPosition();
        //directionVector[0] = directionVector[0]*cos(refPos->hdg);
        //directionVector[1] = directionVector[1]*sin(refPos->hdg);

        entityGeometry->setPosition(pos, directionVector);
    }
}

void Entity::longitudinalSpeedAction(std::list<Entity*> *activeEntityList, double init_targetSpeed, int shape)
{
    float targetSpeed = (float) init_targetSpeed;

    //linear
    if(shape == 0)
    {
        if (dt == 0)
        {
            old_speed = speed;

            if (targetSpeed>old_speed)
            {
                acceleration = 50;
            }
            else
            {
                acceleration = -50;
            }
        }
    }
    // step
    else
    {
        old_speed = targetSpeed;
        acceleration = 1000;
    }

    float frametime = opencover::cover->frameDuration();
    dt += frametime;

    cout << getName() << " is breaking! New speed: " << speed << endl;
    float t_end = (targetSpeed-old_speed)/acceleration;
    if(dt>=t_end)
    {
        speed = targetSpeed;
        activeEntityList->remove(this);
        dt = 0.0;
    }
    else
    {
        speed = acceleration*dt+old_speed;
    }


}
