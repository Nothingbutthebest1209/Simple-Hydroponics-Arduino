/*  Hydruino: Simple automation controller for hydroponic grow systems.
    Copyright (C) 2022 NachtRaveVL          <nachtravevl@gmail.com>
    Hydroponics Object
*/

#include "Hydroponics.h"

HydroponicsObject *newObjectFromData(const HydroponicsData *dataIn)
{
    if (dataIn && dataIn->id.object.idType == -1) return nullptr;
    HYDRUINO_SOFT_ASSERT(dataIn && dataIn->isObjData(), F("Invalid data"));

    if (dataIn && dataIn->isObjData()) {
        switch (dataIn->id.object.idType) {
            case 0: // Actuator
                return newActuatorObjectFromData((HydroponicsActuatorData *)dataIn);
            case 1: // Sensor
                return newSensorObjectFromData((HydroponicsSensorData *)dataIn);
            case 2: // Crop
                return newCropObjectFromData((HydroponicsCropData *)dataIn);
            case 3: // Reservoir
                return newReservoirObjectFromData((HydroponicsReservoirData *)dataIn);
            case 4: // Rail
                return newRailObjectFromData((HydroponicsRailData *)dataIn);
            default: break;
        }
    }

    return nullptr;
}


HydroponicsIdentity::HydroponicsIdentity()
    : type(Unknown), typeAs{.actuatorType=(Hydroponics_ActuatorType)-1}, posIndex(-1), keyStr(), key((Hydroponics_KeyType)-1)
{ ; }

HydroponicsIdentity::HydroponicsIdentity(const HydroponicsIdentity &id, Hydroponics_PositionIndex positionIndex)
    : type(id.type), typeAs{.actuatorType=id.typeAs.actuatorType}, posIndex(positionIndex), keyStr(), key((Hydroponics_KeyType)-1)
{
    regenKey();
}

HydroponicsIdentity::HydroponicsIdentity(Hydroponics_ActuatorType actuatorTypeIn, Hydroponics_PositionIndex positionIndex)
    : type(Actuator), typeAs{.actuatorType=actuatorTypeIn}, posIndex(positionIndex), keyStr(), key((Hydroponics_KeyType)-1)
{
    regenKey();
}

HydroponicsIdentity::HydroponicsIdentity(Hydroponics_SensorType sensorTypeIn, Hydroponics_PositionIndex positionIndex)
    : type(Sensor), typeAs{.sensorType=sensorTypeIn}, posIndex(positionIndex), keyStr(), key((Hydroponics_KeyType)-1)
{
    regenKey();
}

HydroponicsIdentity::HydroponicsIdentity(Hydroponics_CropType cropTypeIn, Hydroponics_PositionIndex positionIndex)
    : type(Crop), typeAs{.cropType=cropTypeIn}, posIndex(positionIndex), keyStr(), key((Hydroponics_KeyType)-1)
{
    regenKey();
}

HydroponicsIdentity::HydroponicsIdentity(Hydroponics_ReservoirType reservoirTypeIn, Hydroponics_PositionIndex positionIndex)
    : type(Reservoir), typeAs{.reservoirType=reservoirTypeIn}, posIndex(positionIndex), keyStr(), key((Hydroponics_KeyType)-1)
{
    regenKey();
}

HydroponicsIdentity::HydroponicsIdentity(Hydroponics_RailType railTypeIn, Hydroponics_PositionIndex positionIndex)
    : type(Rail), typeAs{.railType=railTypeIn}, posIndex(positionIndex), keyStr(), key((Hydroponics_KeyType)-1)
{
    regenKey();
}

HydroponicsIdentity::HydroponicsIdentity(const HydroponicsData *data)
    : type((typeof(type))(data->id.object.idType)),
      typeAs{.actuatorType=(Hydroponics_ActuatorType)(data->id.object.objType)},
      posIndex(data->id.object.posIndex),
      keyStr(), key(-1)
{
    regenKey();
}

HydroponicsIdentity::HydroponicsIdentity(String name)
    : type(Unknown), typeAs{.actuatorType=(Hydroponics_ActuatorType)-1}, posIndex(-1), keyStr(name), key((Hydroponics_KeyType)-1)
{
    // TODO: Advanced string detokenization - may not be needed, tho
    regenKey();
}

Hydroponics_KeyType HydroponicsIdentity::regenKey()
{
    switch(type) {
        case Actuator:
            keyStr = actuatorTypeToString(typeAs.actuatorType, true) + positionIndexToString(posIndex, true);
            break;
        case Sensor:
            keyStr = sensorTypeToString(typeAs.sensorType, true) + positionIndexToString(posIndex, true);
            break;
        case Crop:
            keyStr = cropTypeToString(typeAs.cropType, true) + positionIndexToString(posIndex, true);
            break;
        case Reservoir:
            keyStr = reservoirTypeToString(typeAs.reservoirType, true) + positionIndexToString(posIndex, true);
            break;
        case Rail:
            keyStr = railTypeToString(typeAs.railType, true) + positionIndexToString(posIndex, true);
            break;
        default: break;
    }
    key = stringHash(keyStr);
    return key;
}


HydroponicsObject::HydroponicsObject(HydroponicsIdentity id)
    : _id(id), _links()
{ ; }

HydroponicsObject::HydroponicsObject(const HydroponicsData *data)
    : _id(data), _links()
{ ; }

HydroponicsObject::~HydroponicsObject()
{ ; }

void HydroponicsObject::update()
{ ; }

void HydroponicsObject::resolveLinks()
{ ; }

void HydroponicsObject::handleLowMemory()
{
    //_links.shrink_to_fit(); // not yet implemented library method
}

HydroponicsData *HydroponicsObject::saveToData()
{
    auto data = allocateData();
    if (data) { saveToData(data); }
    return data;
}

bool HydroponicsObject::hasLinkage(HydroponicsObject *obj) const
{
    return (_links.find(obj->_id) != _links.end());
}

const HydroponicsIdentity &HydroponicsObject::getId() const
{
    return _id;
}

const Hydroponics_KeyType HydroponicsObject::getKey() const
{
    return _id.key;
}

bool HydroponicsObject::addLinkage(HydroponicsObject *obj)
{
    return _links.insert(obj->getKey(), obj).second;
}

bool HydroponicsObject::removeLinkage(HydroponicsObject *obj)
{
    auto iter = _links.find(obj->_id);
    if (iter != _links.end()) {
        _links.erase(iter);
        return true;
    }
    return false;
}

HydroponicsData *HydroponicsObject::allocateData() const
{
    return new HydroponicsData();
}

void HydroponicsObject::saveToData(HydroponicsData *dataOut) const
{
    dataOut->id.object.idType = (int8_t)_id.type;
    dataOut->id.object.objType = (int8_t)_id.typeAs.actuatorType;
    dataOut->id.object.posIndex = (int8_t)_id.posIndex;
    if (_id.keyStr.length()) {
        strncpy(((HydroponicsObjectData *)dataOut)->name, _id.keyStr.c_str(), HYDRUINO_NAME_MAXSIZE);
    }
}


HydroponicsObjectData::HydroponicsObjectData()
    : HydroponicsData(), name{0}
{
    _size = sizeof(*this);
}

void HydroponicsObjectData::toJSONObject(JsonObject &objectOut) const
{
    HydroponicsData::toJSONObject(objectOut);

    if (name[0]) { objectOut[F("name")] = stringFromChars(name, HYDRUINO_NAME_MAXSIZE); }
}

void HydroponicsObjectData::fromJSONObject(JsonObjectConst &objectIn)
{
    HydroponicsData::fromJSONObject(objectIn);

    const char *nameStr = objectIn[F("name")];
    if (nameStr && nameStr[0]) { strncpy(name, nameStr, HYDRUINO_NAME_MAXSIZE); }
}
