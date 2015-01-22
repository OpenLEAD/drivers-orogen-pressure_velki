/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "Task.hpp"

#include <pressure_velki/Packet.hpp>

#include <base/samples/RigidBodyState.hpp>

using namespace pressure_velki;

const double bar2meter = 10.1972;

Task::Task(std::string const& name)
    : TaskBase(name)
{
    _id.set(Packet::ADDRESS_POINT_TO_POINT);
}

Task::Task(std::string const& name, RTT::ExecutionEngine* engine)
    : TaskBase(name, engine)
{
    _id.set(Packet::ADDRESS_POINT_TO_POINT);
}

Task::~Task()
{
}



/// The following lines are template definitions for the various state machine
// hooks defined by Orocos::RTT. See Task.hpp for more detailed
// documentation about them.

bool Task::configureHook()
{
    if (!_io_port.value().empty())
        m_driver.openURI(_io_port.get());

    setDriver(&m_driver);

    if (! TaskBase::configureHook())
        return false;

    DeviceInfo info = m_driver.initialize(_id.get());
    _info.set(info);
    return true;
}
bool Task::startHook()
{
    if (! TaskBase::startHook())
        return false;

    return true;
}
void Task::updateHook()
{
    base::Pressure p = m_driver.readPressure(_channel.get(), _id.get());
    _pressure_samples.write(
        base::samples::Pressure(base::Time::now(), p)
    );
    
    base::samples::RigidBodyState depth_sample;
    //conversion from pressure to meters
    depth_sample.position =  Eigen::Vector3d(0, 0, bar2meter*p.toBar());
    depth_sample.orientation = base::Orientation::Identity();
    depth_sample.time = base::Time::now();
    depth_sample.sourceFrame = _world_frame.get();
    depth_sample.targetFrame = _sensor_frame.get();
    _depth_samples.write(depth_sample);
    
    TaskBase::updateHook();
}
void Task::processIO()
{
}
void Task::errorHook()
{
    TaskBase::errorHook();
}
void Task::stopHook()
{
    TaskBase::stopHook();
}
void Task::cleanupHook()
{
    TaskBase::cleanupHook();
}
