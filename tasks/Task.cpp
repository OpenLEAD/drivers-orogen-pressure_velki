/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "Task.hpp"

#include <pressure_velki/Packet.hpp>

using namespace pressure_velki;

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
