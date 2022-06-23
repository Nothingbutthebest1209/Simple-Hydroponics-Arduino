/*  Hydruino: Simple automation controller for hydroponic grow systems.
    Copyright (C) 2022 NachtRaveVL          <nachtravevl@gmail.com>
    Hydroponics Triggers
*/

#include "Hydroponics.h"

HydroponicsTrigger::HydroponicsTrigger(int typeIn)
    : type((typeof(type))typeIn), _triggerState(Hydroponics_TriggerState_Disabled), _attached(false)
{ ; }

HydroponicsTrigger::~HydroponicsTrigger()
{
    if (_attached) { detach(); }
}

void HydroponicsTrigger::update()
{
    if (!_attached) { attach(); }
}

Hydroponics_TriggerState HydroponicsTrigger::getTriggerState() const
{
    return _triggerState;
}

Signal<Hydroponics_TriggerState> &HydroponicsTrigger::getTriggerSignal()
{
    return _triggerSignal;
}


HydroponicsMeasurementValueTrigger::HydroponicsMeasurementValueTrigger(shared_ptr<HydroponicsSensor> sensor, float tolerance, bool activeBelow, int measurementRow)
    : HydroponicsTrigger(MeasureValue), _sensor(sensor),
      _tolerance(tolerance), _toleranceUnits(Hydroponics_UnitsType_Undefined),
      _activeBelow(activeBelow), _measurementRow((int8_t)measurementRow)
{ ; }

HydroponicsMeasurementValueTrigger::~HydroponicsMeasurementValueTrigger()
{ ; }

void HydroponicsMeasurementValueTrigger::attach()
{
    if (!_attached) {
        auto methodSlot = MethodSlot<HydroponicsMeasurementValueTrigger, HydroponicsMeasurement *>(this, &handleSensorMeasure);
        _sensor->getMeasurementSignal().attach(methodSlot);
        _attached = true;
    }
}

void HydroponicsMeasurementValueTrigger::detach()
{
    if (_attached) {
        auto methodSlot = MethodSlot<HydroponicsMeasurementValueTrigger, HydroponicsMeasurement *>(this, &handleSensorMeasure);
        _sensor->getMeasurementSignal().detach(methodSlot);
        _attached = false;
    }
}

void HydroponicsMeasurementValueTrigger::setToleranceUnits(Hydroponics_UnitsType units)
{
    _toleranceUnits = units;
}

float HydroponicsMeasurementValueTrigger::getTolerance() const
{
    return _tolerance;
}

Hydroponics_UnitsType HydroponicsMeasurementValueTrigger::getToleranceUnits() const
{
    return _toleranceUnits;
}

bool HydroponicsMeasurementValueTrigger::getActiveBelow() const
{
    return _activeBelow;
}

shared_ptr<HydroponicsSensor> HydroponicsMeasurementValueTrigger::getSensor() const
{
    return _sensor;
}

void HydroponicsMeasurementValueTrigger::handleSensorMeasure(HydroponicsMeasurement *measurement)
{
    if (measurement) {
        bool fromDisabled = (_triggerState == Hydroponics_TriggerState_Disabled);
        bool newState = (_triggerState == Hydroponics_TriggerState_Triggered);

        if (measurement->isBinaryType()) {
            newState = ((HydroponicsBinaryMeasurement *)measurement)->state != _activeBelow;
        } else {
            float measurementValue = 0.0f;
            Hydroponics_UnitsType measurementUnits = Hydroponics_UnitsType_Undefined;

            if (measurement->isSingleType()) {
                measurementValue = ((HydroponicsSingleMeasurement *)measurement)->value;
                measurementUnits = ((HydroponicsSingleMeasurement *)measurement)->units;
            } else if (measurement->isDoubleType()) {
                measurementValue = ((HydroponicsDoubleMeasurement *)measurement)->value[_measurementRow];
                measurementUnits = ((HydroponicsDoubleMeasurement *)measurement)->units[_measurementRow];
            } else if (measurement->isTripleType()) {
                measurementValue = ((HydroponicsTripleMeasurement *)measurement)->value[_measurementRow];
                measurementUnits = ((HydroponicsTripleMeasurement *)measurement)->units[_measurementRow];
            }

            if (_toleranceUnits != Hydroponics_UnitsType_Undefined && measurementUnits != _toleranceUnits) {
                convertStdUnits(&measurementValue, &measurementUnits, _toleranceUnits);
                HYDRUINO_SOFT_ASSERT(measurementUnits == _toleranceUnits, "Failure converting measurement value to tolerance units");
            }

            if (_toleranceUnits == Hydroponics_UnitsType_Undefined || measurementUnits == _toleranceUnits) {
                newState = (_activeBelow ? measurementValue <= _tolerance + FLT_EPSILON
                                         : measurementValue >= _tolerance - FLT_EPSILON);
            }
        }

        if (newState != (_triggerState == Hydroponics_TriggerState_Triggered) || fromDisabled) {
            _triggerState = newState ? Hydroponics_TriggerState_Triggered : Hydroponics_TriggerState_NotTriggered;

            if (!fromDisabled) {
                scheduleSignalFireOnce<Hydroponics_TriggerState>(_triggerSignal, _triggerState);
            }
        }
    }
}


HydroponicsMeasurementRangeTrigger::HydroponicsMeasurementRangeTrigger(shared_ptr<HydroponicsSensor> sensor, float toleranceLow, float toleranceHigh, bool triggerOnOutside, int measurementRow)
    : HydroponicsTrigger(MeasureRange), _sensor(sensor),
      _toleranceHigh(toleranceHigh), _toleranceLow(toleranceLow),
      _triggerOnOutside(triggerOnOutside), _measurementRow(measurementRow)
{ ; }

HydroponicsMeasurementRangeTrigger::~HydroponicsMeasurementRangeTrigger()
{ ; }

void HydroponicsMeasurementRangeTrigger::attach()
{
    if (!_attached) {
        auto methodSlot = MethodSlot<HydroponicsMeasurementRangeTrigger, HydroponicsMeasurement *>(this, &handleSensorMeasure);
        _sensor->getMeasurementSignal().attach(methodSlot);
        _attached = true;
    }
}

void HydroponicsMeasurementRangeTrigger::detach()
{
    if (_attached) {
        auto methodSlot = MethodSlot<HydroponicsMeasurementRangeTrigger, HydroponicsMeasurement *>(this, &handleSensorMeasure);
        _sensor->getMeasurementSignal().detach(methodSlot);
        _attached = false;
    }
}

void HydroponicsMeasurementRangeTrigger::setToleranceUnits(Hydroponics_UnitsType units)
{
    _toleranceUnits = units;
}

shared_ptr<HydroponicsSensor> HydroponicsMeasurementRangeTrigger::getSensor() const
{
    return _sensor;
}

float HydroponicsMeasurementRangeTrigger::getToleranceLow() const
{
    return _toleranceLow;
}

float HydroponicsMeasurementRangeTrigger::getToleranceHigh() const
{
    return _toleranceHigh;
}

Hydroponics_UnitsType HydroponicsMeasurementRangeTrigger::getToleranceUnits() const
{
    return _toleranceUnits;
}

void HydroponicsMeasurementRangeTrigger::handleSensorMeasure(HydroponicsMeasurement *measurement)
{
    if (measurement) {
        bool fromDisabled = (_triggerState == Hydroponics_TriggerState_Disabled);
        bool newState = (_triggerState == Hydroponics_TriggerState_Triggered);
        float measurementValue = 0.0f;
        Hydroponics_UnitsType measurementUnits = Hydroponics_UnitsType_Undefined;

        if (measurement->isBinaryType()) {
            measurementValue = ((HydroponicsBinaryMeasurement *)measurement)->state * 1.0f;
            measurementUnits = Hydroponics_UnitsType_Raw_0_1;
        } else if (measurement->isSingleType()) {
            measurementValue = ((HydroponicsSingleMeasurement *)measurement)->value;
            measurementUnits = ((HydroponicsSingleMeasurement *)measurement)->units;
        } else if (measurement->isDoubleType()) {
            measurementValue = ((HydroponicsDoubleMeasurement *)measurement)->value[_measurementRow];
            measurementUnits = ((HydroponicsDoubleMeasurement *)measurement)->units[_measurementRow];
        } else if (measurement->isTripleType()) {
            measurementValue = ((HydroponicsTripleMeasurement *)measurement)->value[_measurementRow];
            measurementUnits = ((HydroponicsTripleMeasurement *)measurement)->units[_measurementRow];
        }

        if (_toleranceUnits != Hydroponics_UnitsType_Undefined && measurementUnits != _toleranceUnits) {
            convertStdUnits(&measurementValue, &measurementUnits, _toleranceUnits);
            HYDRUINO_SOFT_ASSERT(measurementUnits == _toleranceUnits, "Failure converting measurement value to tolerance units");
        }

        if (_toleranceUnits == Hydroponics_UnitsType_Undefined || measurementUnits == _toleranceUnits) {
            bool isInside = (measurementValue >= _toleranceLow - FLT_EPSILON &&
                             measurementValue <= _toleranceHigh + FLT_EPSILON);
            newState = _triggerOnOutside ? !isInside : isInside;
        }

        if (newState != (_triggerState == Hydroponics_TriggerState_Triggered) || fromDisabled) {
            _triggerState = newState ? Hydroponics_TriggerState_Triggered : Hydroponics_TriggerState_NotTriggered;

            if (!fromDisabled) {
                scheduleSignalFireOnce<Hydroponics_TriggerState>(_triggerSignal, _triggerState);
            }
        }
    }
}
