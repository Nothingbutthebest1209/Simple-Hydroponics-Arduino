/*  Hydruino: Simple automation controller for hydroponic grow systems.
    Copyright (C) 2022 NachtRaveVL          <nachtravevl@gmail.com>
    Hydroponics Power Rails 
*/

#include "Hydroponics.h"

HydroponicsRail *newRailObjectFromData(const HydroponicsRailData *dataIn)
{
    if (dataIn && dataIn->id.object.idType == -1) return nullptr;
    HYDRUINO_SOFT_ASSERT(dataIn && dataIn->isObjectData(), F("Invalid data"));

    if (dataIn && dataIn->isObjectData()) {
        switch(dataIn->id.object.classType) {
            case 0: // Simple
                return new HydroponicsSimpleRail((const HydroponicsSimpleRailData *)dataIn);
            case 1: // Regulated
                return new HydroponicsRegulatedRail((const HydroponicsRegulatedRailData *)dataIn);
            default: break;
        }
    }

    return nullptr;
}


HydroponicsRail::HydroponicsRail(Hydroponics_RailType railType, Hydroponics_PositionIndex railIndex, int classTypeIn)
    : HydroponicsObject(HydroponicsIdentity(railType, railIndex)), classType((typeof(classType))classTypeIn)
{ ; }

HydroponicsRail::HydroponicsRail(const HydroponicsRailData *dataIn)
    : HydroponicsObject(dataIn), classType((typeof(classType))(dataIn->id.object.classType))
{ ; }

HydroponicsRail::~HydroponicsRail()
{
    //discardFromTaskManager(&_capacitySignal);
}

void HydroponicsRail::update()
{
    HydroponicsObject::update();
}

void HydroponicsRail::resolveLinks()
{
    HydroponicsObject::resolveLinks();
}

void HydroponicsRail::handleLowMemory()
{
    HydroponicsObject::handleLowMemory();
}

bool HydroponicsRail::addActuator(HydroponicsActuator *actuator)
{
    return addLinkage(actuator);
}

bool HydroponicsRail::removeActuator(HydroponicsActuator *actuator)
{
    return removeLinkage(actuator);
}

bool HydroponicsRail::hasActuator(HydroponicsActuator *actuator) const
{
    return hasLinkage(actuator);
}

arx::map<Hydroponics_KeyType, HydroponicsObject *, HYDRUINO_OBJ_LINKS_MAXSIZE> HydroponicsRail::getActuators() const
{
    return linksFilterActuators(_links);
}

bool HydroponicsRail::addSensor(HydroponicsSensor *sensor)
{
    return addLinkage(sensor);
}

bool HydroponicsRail::removeSensor(HydroponicsSensor *sensor)
{
    return removeLinkage(sensor);
}

bool HydroponicsRail::hasSensor(HydroponicsSensor *sensor) const
{
    return hasLinkage(sensor);
}

arx::map<Hydroponics_KeyType, HydroponicsObject *, HYDRUINO_OBJ_LINKS_MAXSIZE> HydroponicsRail::getSensors() const
{
    return linksFilterSensors(_links);
}

Hydroponics_RailType HydroponicsRail::getRailType() const
{
    return _id.objTypeAs.railType;
}

Hydroponics_PositionIndex HydroponicsRail::getRailIndex() const
{
    return _id.posIndex;
}

Signal<HydroponicsRail *> &HydroponicsRail::getCapacitySignal()
{
    return _capacitySignal;
}

HydroponicsData *HydroponicsRail::allocateData() const
{
    return _allocateDataForObjType((int8_t)_id.type, (int8_t)classType);
}

void HydroponicsRail::saveToData(HydroponicsData *dataOut)
{
    HydroponicsObject::saveToData(dataOut);

    dataOut->id.object.classType = (int8_t)classType;
}


HydroponicsSimpleRail::HydroponicsSimpleRail(Hydroponics_RailType railType,
                                             Hydroponics_PositionIndex railIndex,
                                             int maxActiveAtOnce,
                                             int classType)
    : HydroponicsRail(railType, railIndex, classType), _activeCount(0), _maxActiveAtOnce(maxActiveAtOnce)
{ ; }

HydroponicsSimpleRail::HydroponicsSimpleRail(const HydroponicsSimpleRailData *dataIn)
    : HydroponicsRail(dataIn), _activeCount(0), _maxActiveAtOnce(dataIn->maxActiveAtOnce)
{ ; }

HydroponicsSimpleRail::~HydroponicsSimpleRail()
{
    {   auto actuators = getActuators();
        for (auto iter = actuators.begin(); iter != actuators.end(); ++iter) { removeActuator((HydroponicsActuator *)(iter->second)); }
    }
}

bool HydroponicsSimpleRail::canActivate(HydroponicsActuator *actuator)
{
    return _activeCount < _maxActiveAtOnce;
}

float HydroponicsSimpleRail::getCapacity() const
{
    return _activeCount / (float)_maxActiveAtOnce;
}

bool HydroponicsSimpleRail::addActuator(HydroponicsActuator *actuator)
{
    if (HydroponicsRail::addActuator(actuator)) {
        auto methodSlot = MethodSlot<typeof(*this), HydroponicsActuator *>(this, &handleActivation);
        actuator->getActivationSignal().attach(methodSlot);
        return true;
    }
    return false;
}

bool HydroponicsSimpleRail::removeActuator(HydroponicsActuator *actuator)
{
    if (HydroponicsRail::removeActuator(actuator)) {
        auto methodSlot = MethodSlot<typeof(*this), HydroponicsActuator *>(this, &handleActivation);
        actuator->getActivationSignal().detach(methodSlot);
        return true;
    }
    return false;
}

int HydroponicsSimpleRail::getActiveCount()
{
    return _activeCount;
}

void HydroponicsSimpleRail::saveToData(HydroponicsData *dataOut)
{
    HydroponicsRail::saveToData(dataOut);

    ((HydroponicsSimpleRailData *)dataOut)->maxActiveAtOnce = _maxActiveAtOnce;
}

void HydroponicsSimpleRail::handleActivation(HydroponicsActuator *actuator)
{
    bool hadSpaceBefore = _activeCount < _maxActiveAtOnce;

    if (actuator->getIsEnabled()) {
        _activeCount++;
    } else {
        _activeCount--;
    }

    bool hasSpaceAfter = _activeCount < _maxActiveAtOnce;

    if (hadSpaceBefore != hasSpaceAfter) {
        scheduleSignalFireOnce<HydroponicsRail *>(getSharedPtr(), _capacitySignal, this);
    }
}


HydroponicsRegulatedRail::HydroponicsRegulatedRail(Hydroponics_RailType railType,
                             Hydroponics_PositionIndex railIndex,
                             float maxPower,
                             int classType = Regulated)
    : HydroponicsRail(railType, railIndex, classType), _maxPower(maxPower), _powerUnits(Hydroponics_UnitsType_Power_Wattage), _needsPowerUpdate(true)
{ ; }

HydroponicsRegulatedRail::HydroponicsRegulatedRail(const HydroponicsRegulatedRailData *dataIn)
    : HydroponicsRail(dataIn), _needsPowerUpdate(true),
      _maxPower(dataIn->maxPower), _powerUnits(dataIn->powerUnits),
      _powerSensor(dataIn->powerSensorName), _limitTrigger(newTriggerObjectFromSubData(&(dataIn->limitTrigger)))
{
    if (_limitTrigger) { attachLimitTrigger(); }
}

HydroponicsRegulatedRail::~HydroponicsRegulatedRail()
{
    if (_powerSensor) { detachPowerSensor(); }
    if (_limitTrigger) { detachLimitTrigger(); delete _limitTrigger; _limitTrigger = nullptr; }
}

void HydroponicsRegulatedRail::update()
{
    HydroponicsRail::update();

    if (_limitTrigger) { _limitTrigger->update(); }

    if (_needsPowerUpdate && getPowerSensor()) {
        handlePowerMeasure(_powerSensor->getLatestMeasurement());
    }
}

void HydroponicsRegulatedRail::resolveLinks()
{
    HydroponicsRail::resolveLinks();

    if (_powerSensor.needsResolved()) { getPowerSensor(); }
    if (_limitTrigger) { _limitTrigger->resolveLinks(); }
}

void HydroponicsRegulatedRail::handleLowMemory()
{
    HydroponicsRail::handleLowMemory();

    if (_limitTrigger) { _limitTrigger->handleLowMemory(); }
}

bool HydroponicsRegulatedRail::canActivate(HydroponicsActuator *actuator)
{
    return _limitTrigger ? _limitTrigger->getTriggerState() != Hydroponics_TriggerState_Triggered : true;
}

float HydroponicsRegulatedRail::getCapacity() const
{
    return _powerDraw.value / _maxPower;
}

void HydroponicsRegulatedRail::setPowerUnits(Hydroponics_UnitsType powerUnits)
{
    if (_powerUnits != powerUnits) {
        _powerUnits = powerUnits;

        convertStdUnits(&_powerDraw.value, &_powerDraw.units, _powerUnits);
    }
}

Hydroponics_UnitsType HydroponicsRegulatedRail::getPowerUnits() const
{
    return _powerUnits;
}

void HydroponicsRegulatedRail::setPowerSensor(HydroponicsIdentity powerSensorId)
{
    if (_powerSensor != powerSensorId) {
        if (_powerSensor) { detachPowerSensor(); }
        _powerSensor = powerSensorId;
        _needsPowerUpdate = true;
    }
}

void HydroponicsRegulatedRail::setPowerSensor(shared_ptr<HydroponicsSensor> powerSensor)
{
    if (_powerSensor != powerSensor) {
        if (_powerSensor) { detachPowerSensor(); }
        _powerSensor = powerSensor;
        if (_powerSensor) { attachPowerSensor(); }
        _needsPowerUpdate = true;
    }
}

shared_ptr<HydroponicsSensor> HydroponicsRegulatedRail::getPowerSensor()
{
    if (_powerSensor.resolveIfNeeded()) { attachPowerSensor(); }
    return _powerSensor.getObj();
}

void HydroponicsRegulatedRail::setPowerDraw(float powerDraw, Hydroponics_UnitsType powerDrawUnits)
{
    _powerDraw.value = powerDraw;
    _powerDraw.units = powerDrawUnits != Hydroponics_UnitsType_Undefined ? powerDrawUnits
                                                                         : (_powerUnits != Hydroponics_UnitsType_Undefined ? _powerUnits
                                                                                                                           : Hydroponics_UnitsType_Power_Wattage);
    _powerDraw.updateTimestamp();
    _powerDraw.updateFrame(1);

    convertStdUnits(&_powerDraw.value, &_powerDraw.units, _powerUnits);
}

void HydroponicsRegulatedRail::setPowerDraw(HydroponicsSingleMeasurement powerDraw)
{
    _powerDraw = powerDraw;

    convertStdUnits(&_powerDraw.value, &_powerDraw.units, _powerUnits);
}

const HydroponicsSingleMeasurement &HydroponicsRegulatedRail::getPowerDraw()
{
    if (_needsPowerUpdate && getPowerSensor()) {
        handlePowerMeasure(_powerSensor->getLatestMeasurement());
    }
    return _powerDraw;
}

void HydroponicsRegulatedRail::setLimitTrigger(HydroponicsTrigger *limitTrigger)
{
    if (_limitTrigger != limitTrigger) {
        if (_limitTrigger) { detachLimitTrigger(); delete _limitTrigger; }
        _limitTrigger = limitTrigger;
        if (_limitTrigger) { attachLimitTrigger(); }
    }
}

const HydroponicsTrigger *HydroponicsRegulatedRail::getLimitTrigger() const
{
    return _limitTrigger;
}

float HydroponicsRegulatedRail::getMaxPower() const
{
    return _maxPower;
}

void HydroponicsRegulatedRail::saveToData(HydroponicsData *dataOut)
{
    HydroponicsRail::saveToData(dataOut);

    ((HydroponicsRegulatedRailData *)dataOut)->maxPower = _maxPower;
    ((HydroponicsRegulatedRailData *)dataOut)->powerUnits = _powerUnits;
    if (_powerSensor.getId()) {
        strncpy(((HydroponicsRegulatedRailData *)dataOut)->powerSensorName, _powerSensor.getId().keyStr.c_str(), HYDRUINO_NAME_MAXSIZE);
    }
    if (_limitTrigger) {
        _limitTrigger->saveToData(&(((HydroponicsRegulatedRailData *)dataOut)->limitTrigger));
    }
}

void HydroponicsRegulatedRail::attachPowerSensor()
{
    HYDRUINO_SOFT_ASSERT(_powerSensor, F("Power sensor not linked, failure attaching"));
    if (_powerSensor) {
        auto methodSlot = MethodSlot<typeof(*this), const HydroponicsMeasurement *>(this, &handlePowerMeasure);
        _powerSensor->getMeasurementSignal().attach(methodSlot);
    }
}

void HydroponicsRegulatedRail::detachPowerSensor()
{
    HYDRUINO_SOFT_ASSERT(_powerSensor, F("Power sensor not linked, failure detaching"));
    if (_powerSensor) {
        auto methodSlot = MethodSlot<typeof(*this), const HydroponicsMeasurement *>(this, &handlePowerMeasure);
        _powerSensor->getMeasurementSignal().detach(methodSlot);
    }
}

void HydroponicsRegulatedRail::handlePowerMeasure(const HydroponicsMeasurement *measurement)
{
    if (measurement && measurement->frame) {
        _needsPowerUpdate = false;
        setPowerDraw(singleMeasurementAt(measurement, 0, _maxPower, _powerUnits)); // TODO: Correct row reference, based on sensor
    }
}

void HydroponicsRegulatedRail::attachLimitTrigger()
{
    HYDRUINO_SOFT_ASSERT(_limitTrigger, F("Limit trigger not linked, failure attaching"));
    if (_limitTrigger) {
        auto methodSlot = MethodSlot<typeof(*this), Hydroponics_TriggerState>(this, &handleLimitTrigger);
        _limitTrigger->getTriggerSignal().attach(methodSlot);
    }
}

void HydroponicsRegulatedRail::detachLimitTrigger()
{
    HYDRUINO_SOFT_ASSERT(_limitTrigger, F("Limit trigger not linked, failure detaching"));
    if (_limitTrigger) {
        auto methodSlot = MethodSlot<typeof(*this), Hydroponics_TriggerState>(this, &handleLimitTrigger);
        _limitTrigger->getTriggerSignal().detach(methodSlot);
    }
}

void HydroponicsRegulatedRail::handleLimitTrigger(Hydroponics_TriggerState triggerState)
{
    if (triggerState != Hydroponics_TriggerState_Undefined) {
        scheduleSignalFireOnce<HydroponicsRail *>(getSharedPtr(), _capacitySignal, this);
    }
}


HydroponicsRailData::HydroponicsRailData()
    : HydroponicsObjectData()
{
    _size = sizeof(*this);
}

void HydroponicsRailData::toJSONObject(JsonObject &objectOut) const
{
    HydroponicsObjectData::toJSONObject(objectOut);
}

void HydroponicsRailData::fromJSONObject(JsonObjectConst &objectIn)
{
    HydroponicsObjectData::fromJSONObject(objectIn);
}

HydroponicsSimpleRailData::HydroponicsSimpleRailData()
    : HydroponicsRailData(), maxActiveAtOnce(2)
{
    _size = sizeof(*this);
}

void HydroponicsSimpleRailData::toJSONObject(JsonObject &objectOut) const
{
    HydroponicsRailData::toJSONObject(objectOut);

    if (maxActiveAtOnce != 2) { objectOut[F("maxActiveAtOnce")] = maxActiveAtOnce; }
}

void HydroponicsSimpleRailData::fromJSONObject(JsonObjectConst &objectIn)
{
    HydroponicsRailData::fromJSONObject(objectIn);

    maxActiveAtOnce = objectIn[F("maxActiveAtOnce")] | maxActiveAtOnce;
}

HydroponicsRegulatedRailData::HydroponicsRegulatedRailData()
    : HydroponicsRailData(), maxPower(0), powerUnits{Hydroponics_UnitsType_Undefined}, powerSensorName{0}
{
    _size = sizeof(*this);
}

void HydroponicsRegulatedRailData::toJSONObject(JsonObject &objectOut) const
{
    HydroponicsRailData::toJSONObject(objectOut);

    objectOut[F("maxPower")] = maxPower;
    if (powerUnits != Hydroponics_UnitsType_Undefined) { objectOut[F("powerUnits")] = powerUnits; }
    if (powerSensorName[0]) { objectOut[F("powerSensorName")] = stringFromChars(powerSensorName, HYDRUINO_NAME_MAXSIZE); }
    if (limitTrigger.type != -1) {
        JsonObject limitTriggerObj = objectOut.createNestedObject(F("limitTrigger"));
        limitTrigger.toJSONObject(limitTriggerObj);
    }
}

void HydroponicsRegulatedRailData::fromJSONObject(JsonObjectConst &objectIn)
{
    HydroponicsRailData::fromJSONObject(objectIn);

    maxPower = objectIn[F("maxPower")] | maxPower;
    powerUnits = objectIn[F("powerUnits")] | powerUnits;
    const char *powerSensorNameStr = objectIn[F("powerSensorName")];
    if (powerSensorNameStr && powerSensorNameStr[0]) { strncpy(powerSensorName, powerSensorNameStr, HYDRUINO_NAME_MAXSIZE); }
    JsonObjectConst limitTriggerObj = objectIn[F("limitTrigger")];
    if (!limitTriggerObj.isNull()) { limitTrigger.fromJSONObject(limitTriggerObj); }
}
