/*  Hydruino: Simple automation controller for hydroponic grow systems.
    Copyright (C) 2022-2003 NachtRaveVL     <nachtravevl@gmail.com>
    Hydruino Attachment Points
*/

#include "Hydruino.h"

template <class U>
inline void HydroActuatorAttachmentInterface::setActuator(U actuator)
{
    getParentActuator(false).setObject(actuator);
}

template <class U>
inline SharedPtr<U> HydroActuatorAttachmentInterface::getActuator(bool resolve)
{
    return getParentActuator(resolve).template getObject<U>();
}

template <class U>
inline void HydroSensorAttachmentInterface::setSensor(U sensor)
{
    getParentSensor(false).setObject(sensor);
}

template <class U>
inline SharedPtr<U> HydroSensorAttachmentInterface::getSensor(bool resolve)
{
    return getParentSensor(resolve).template getObject<U>();
}

template <class U>
inline void HydroCropAttachmentInterface::setCrop(U crop)
{
    getParentCrop(false).setObject(crop);
}

template <class U>
inline SharedPtr<U> HydroCropAttachmentInterface::getCrop(bool resolve)
{
    return getParentCrop(resolve).template getObject<U>();
}

template <class U>
inline void HydroReservoirAttachmentInterface::setReservoir(U reservoir)
{
    getParentReservoir(false).setObject(reservoir);
}

template <class U>
inline SharedPtr<U> HydroReservoirAttachmentInterface::getReservoir(bool resolve)
{
    return getParentReservoir(resolve).template getObject<U>();
}

template <class U>
inline void HydroRailAttachmentInterface::setRail(U rail)
{
    getParentRail(false).setObject(rail);
}

template <class U>
inline SharedPtr<U> HydroRailAttachmentInterface::getRail(bool resolve)
{
    return getParentRail(resolve).template getObject<U>();
}

inline bool HydroBalancerObjectInterface::isBalanced() const
{
    return getBalancerState() == Hydro_BalancerState_Balanced;
}

template <class U>
inline void HydroPumpObjectInterface::setInputReservoir(U reservoir)
{
    getParentReservoir(false).setObject(reservoir);
}

template <class U>
inline SharedPtr<U> HydroPumpObjectInterface::getInputReservoir(bool resolve)
{
    return getParentReservoir(resolve).template getObject<U>();
}

template <class U>
inline void HydroPumpObjectInterface::setOutputReservoir(U reservoir)
{
    getDestinationReservoir(false).setObject(reservoir);
}

template <class U>
inline SharedPtr<U> HydroPumpObjectInterface::getOutputReservoir(bool resolve)
{
    return getDestinationReservoir(resolve).template getObject<U>();
}

template <class U>
inline void HydroFeedReservoirAttachmentInterface::setFeedReservoir(U reservoir)
{
    getFeedingReservoir(false).setObject(reservoir);
}

template <class U>
inline SharedPtr<U> HydroFeedReservoirAttachmentInterface::getFeedReservoir(bool resolve)
{
    return getFeedingReservoir(resolve).template getObject<U>();
}

template <class U>
inline void HydroFlowSensorAttachmentInterface::setFlowRateSensor(U sensor)
{
    getFlowRate(false).setObject(sensor);
}

template <class U>
inline SharedPtr<U> HydroFlowSensorAttachmentInterface::getFlowRateSensor(bool poll)
{
    return static_pointer_cast<U>(getFlowRate(poll).getObject());
}

template <class U>
inline void HydroVolumeSensorAttachmentInterface::setWaterVolumeSensor(U sensor)
{
    getWaterVolume(false).setObject(sensor);
}

template <class U>
inline SharedPtr<U> HydroVolumeSensorAttachmentInterface::getWaterVolumeSensor(bool poll)
{
    return static_pointer_cast<U>(getWaterVolume(poll).getObject());
}

template <class U>
inline void HydroPowerSensorAttachmentInterface::setPowerUsageSensor(U sensor)
{
    getPowerUsage(false).setObject(sensor);
}

template <class U>
inline SharedPtr<U> HydroPowerSensorAttachmentInterface::getPowerUsageSensor(bool poll)
{
    return static_pointer_cast<U>(getPowerUsage(poll).getObject());
}

template <class U>
inline void HydroWaterTemperatureSensorAttachmentInterface::setWaterTemperatureSensor(U sensor)
{
    getWaterTemperature(false).setObject(sensor);
}

template <class U>
inline SharedPtr<U> HydroWaterTemperatureSensorAttachmentInterface::getWaterTemperatureSensor(bool poll)
{
    return static_pointer_cast<U>(getWaterTemperature(poll).getObject());
}

template <class U>
inline void HydroWaterPHSensorAttachmentInterface::setWaterPHSensor(U sensor)
{
    getWaterPH(false).setObject(sensor);
}

template <class U>
inline SharedPtr<U> HydroWaterPHSensorAttachmentInterface::getWaterPHSensor(bool poll)
{
    return static_pointer_cast<U>(getWaterPH(poll).getObject());
}

template <class U>
inline void HydroWaterTDSSensorAttachmentInterface::setWaterTDSSensor(U sensor)
{
    getWaterTDS(false).setObject(sensor);
}

template <class U>
inline SharedPtr<U> HydroWaterTDSSensorAttachmentInterface::getWaterTDSSensor(bool poll)
{
    return static_pointer_cast<U>(getWaterTDS(poll).getObject());
}

template <class U>
inline void HydroSoilMoistureSensorAttachmentInterface::setSoilMoistureSensor(U sensor)
{
    getSoilMoisture(false).setObject(sensor);
}

template <class U>
inline SharedPtr<U> HydroSoilMoistureSensorAttachmentInterface::getSoilMoistureSensor(bool poll)
{
    return static_pointer_cast<U>(getSoilMoisture(poll).getObject());
}

template <class U>
inline void HydroAirTemperatureSensorAttachmentInterface::setAirTemperatureSensor(U sensor)
{
    getAirTemperature(false).setObject(sensor);
}

template <class U>
inline SharedPtr<U> HydroAirTemperatureSensorAttachmentInterface::getAirTemperatureSensor(bool poll)
{
    return static_pointer_cast<U>(getAirTemperature(poll).getObject());
}

template <class U>
inline void HydroAirHumiditySensorAttachmentInterface::setAirHumiditySensor(U sensor)
{
    getAirHumidity(false).setObject(sensor);
}

template <class U>
inline SharedPtr<U> HydroAirHumiditySensorAttachmentInterface::getAirHumiditySensor(bool poll)
{
    return static_pointer_cast<U>(getAirHumidity(poll).getObject());
}

template <class U>
inline void HydroAirCO2SensorAttachmentInterface::setAirCO2Sensor(U sensor)
{
    getAirCO2(false).setObject(sensor);
}

template <class U>
inline SharedPtr<U> HydroAirCO2SensorAttachmentInterface::getAirCO2Sensor(bool poll)
{
    return static_pointer_cast<U>(getAirCO2(poll).getObject());
}
