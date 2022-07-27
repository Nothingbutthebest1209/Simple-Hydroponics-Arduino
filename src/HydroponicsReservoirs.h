/*  Hydruino: Simple automation controller for hydroponic grow systems.
    Copyright (C) 2022 NachtRaveVL          <nachtravevl@gmail.com>
    Hydroponics Reservoirs
*/

#ifndef HydroponicsReservoirs_H
#define HydroponicsReservoirs_H

class HydroponicsReservoir;
class HydroponicsFluidReservoir;
class HydroponicsFeedReservoir;
class HydroponicsInfiniteReservoir;

struct HydroponicsReservoirData;
struct HydroponicsFluidReservoirData;
struct HydroponicsFeedReservoirData;
struct HydroponicsInfiniteReservoirData;

#include "Hydroponics.h"
#include "HydroponicsTriggers.h"

// Creates reservoir object from passed reservoir data (return ownership transfer - user code *must* delete returned object)
extern HydroponicsReservoir *newReservoirObjectFromData(const HydroponicsReservoirData *dataIn);


// Hydroponics Reservoir Base
// This is the base class for all reservoirs, which defines how the reservoir is
// identified, where it lives, what's attached to it, if it is full or empty, and
// who can activate under it.
class HydroponicsReservoir : public HydroponicsObject, public HydroponicsReservoirObjectInterface {
public:
    const enum { Fluid, Feed, Pipe, Unknown = -1 } classType; // Reservoir class type (custom RTTI)
    inline bool isFluidClass() const { return classType == Fluid; }
    inline bool isFeedClass() const { return classType == Feed; }
    inline bool isPipeClass() const { return classType == Pipe; }
    inline bool isAnyFluidClass() const { return isFluidClass() || isFeedClass(); }
    inline bool isUnknownClass() const { return classType <= Unknown; }

    HydroponicsReservoir(Hydroponics_ReservoirType reservoirType,
                         Hydroponics_PositionIndex reservoirIndex,
                         int classType = Unknown);
    HydroponicsReservoir(const HydroponicsReservoirData *dataIn);

    virtual void update() override;

    virtual bool canActivate(HydroponicsActuator *actuator);
    virtual bool isFilled() = 0;
    virtual bool isEmpty() = 0;

    virtual void setVolumeUnits(Hydroponics_UnitsType volumeUnits);
    virtual Hydroponics_UnitsType getVolumeUnits() const { return definedUnitsElse(_volumeUnits, defaultLiquidVolumeUnits()); }

    virtual HydroponicsSensorAttachment &getWaterVolume() = 0;

    inline Hydroponics_ReservoirType getReservoirType() const { return _id.objTypeAs.reservoirType; }
    inline Hydroponics_PositionIndex getReservoirIndex() const { return _id.posIndex; }

    Signal<HydroponicsReservoir *> &getFilledSignal();
    Signal<HydroponicsReservoir *> &getEmptySignal();

protected:
    Hydroponics_UnitsType _volumeUnits;                     // Volume units preferred

    Hydroponics_TriggerState _filledState;                  // Current filled state
    Hydroponics_TriggerState _emptyState;                   // Current empty state

    Signal<HydroponicsReservoir *> _filledSignal;           // Filled state signal
    Signal<HydroponicsReservoir *> _emptySignal;            // Empty state signal

    virtual HydroponicsData *allocateData() const override;
    virtual void saveToData(HydroponicsData *dataOut) override;

    virtual void handleFilledState(Hydroponics_TriggerState filledState);
    virtual void handleEmptyState(Hydroponics_TriggerState emptyState);
    friend class HydroponicsFluidReservoir;
};


// Simple Fluid Reservoir
// Basic fluid reservoir that contains a volume of liquid and the ability to track such.
// Crude, but effective.
class HydroponicsFluidReservoir : public HydroponicsReservoir, public HydroponicsVolumeSensorAttachmentInterface {
public:
    HydroponicsFluidReservoir(Hydroponics_ReservoirType reservoirType,
                              Hydroponics_PositionIndex reservoirIndex,
                              float maxVolume,
                              int classType = Fluid);
    HydroponicsFluidReservoir(const HydroponicsFluidReservoirData *dataIn);

    virtual void update() override;
    virtual void handleLowMemory() override;

    virtual bool isFilled() override;
    virtual bool isEmpty() override;

    virtual void setVolumeUnits(Hydroponics_UnitsType volumeUnits) override;

    virtual HydroponicsSensorAttachment &getWaterVolume() override;

    inline void setFilledTrigger(shared_ptr<HydroponicsTrigger> filledTrigger) { _filledTrigger = filledTrigger; }
    inline shared_ptr<HydroponicsTrigger> getFilledTrigger(bool force = false) { _filledTrigger.updateTriggerIfNeeded(force); return _filledTrigger.getObject(); }

    inline void setEmptyTrigger(shared_ptr<HydroponicsTrigger> emptyTrigger) { _emptyTrigger = emptyTrigger; }
    inline shared_ptr<HydroponicsTrigger> getEmptyTrigger(bool force = false) { _emptyTrigger.updateTriggerIfNeeded(force); return _emptyTrigger.getObject(); }

    inline float getMaxVolume() const { return _maxVolume; }

protected:
    float _maxVolume;                                       // Maximum volume
    HydroponicsSensorAttachment _waterVolume;               // Water volume sensor attachment
    HydroponicsTriggerAttachment _filledTrigger;            // Filled trigger (owned)
    HydroponicsTriggerAttachment _emptyTrigger;             // Empty trigger (owned)

    virtual void saveToData(HydroponicsData *dataOut) override;

    virtual void handleFilledState(Hydroponics_TriggerState filledState) override;
    virtual void handleEmptyState(Hydroponics_TriggerState filledState) override;
};


// Feed Water Reservoir
// The feed water reservoir can be thought of as an entire feeding channel hub, complete
// with sensors to automate the variety of tasks associated with feeding crops.
class HydroponicsFeedReservoir : public HydroponicsFluidReservoir, public HydroponicsWaterPHSensorAttachmentInterface, public HydroponicsWaterTDSSensorAttachmentInterface, public HydroponicsWaterTemperatureSensorAttachmentInterface,  public HydroponicsAirTemperatureSensorAttachmentInterface, public HydroponicsAirCO2SensorAttachmentInterface {
public:
    HydroponicsFeedReservoir(Hydroponics_PositionIndex reservoirIndex,
                             float maxVolume,
                             DateTime lastChangeDate = DateTime((uint32_t)unixNow()),
                             DateTime lastPruningDate = DateTime(),
                             int classType = Feed);
    HydroponicsFeedReservoir(const HydroponicsFeedReservoirData *dataIn);

    virtual void update() override;
    virtual void handleLowMemory() override;

    void setTDSUnits(Hydroponics_UnitsType tdsUnits);
    inline Hydroponics_UnitsType getTDSUnits() const { return definedUnitsElse(_tdsUnits, Hydroponics_UnitsType_Concentration_TDS); }

    void setTemperatureUnits(Hydroponics_UnitsType tempUnits);
    inline Hydroponics_UnitsType getTemperatureUnits() const { return definedUnitsElse(_tempUnits, defaultTemperatureUnits()); }

    virtual HydroponicsSensorAttachment &getWaterPH() override;

    virtual HydroponicsSensorAttachment &getWaterTDS() override;

    virtual HydroponicsSensorAttachment &getWaterTemperature() override;

    virtual HydroponicsSensorAttachment &getAirTemperature() override;

    virtual HydroponicsSensorAttachment &getAirCO2() override;

    shared_ptr<HydroponicsBalancer> setWaterPHBalancer(float phSetpoint, Hydroponics_UnitsType phSetpointUnits);
    inline void setWaterPHBalancer(shared_ptr<HydroponicsBalancer> phBalancer) { _waterPHBalancer.setObject(phBalancer); }
    inline shared_ptr<HydroponicsBalancer> getWaterPHBalancer(bool force = false) { _waterPHBalancer.updateBalancerIfNeeded(force); return _waterPHBalancer.getObject(); }

    shared_ptr<HydroponicsBalancer> setWaterTDSBalancer(float tdsSetpoint, Hydroponics_UnitsType tdsSetpointUnits);
    inline void setWaterTDSBalancer(shared_ptr<HydroponicsBalancer> tdsBalancer) { _waterTDSBalancer.setObject(tdsBalancer); }
    inline shared_ptr<HydroponicsBalancer> getWaterTDSBalancer(bool force = false) { _waterTDSBalancer.updateBalancerIfNeeded(force); return _waterTDSBalancer.getObject(); }

    shared_ptr<HydroponicsBalancer> setWaterTemperatureBalancer(float tempSetpoint, Hydroponics_UnitsType tempSetpointUnits);
    inline void setWaterTemperatureBalancer(shared_ptr<HydroponicsBalancer> waterTempBalancer) { _waterTempBalancer.setObject(waterTempBalancer); }
    inline shared_ptr<HydroponicsBalancer> getWaterTemperatureBalancer(bool force = false) { _waterTempBalancer.updateBalancerIfNeeded(force); return _waterTempBalancer.getObject(); }

    shared_ptr<HydroponicsBalancer> setAirTemperatureBalancer(float tempSetpoint, Hydroponics_UnitsType tempSetpointUnits);
    inline void setAirTemperatureBalancer(shared_ptr<HydroponicsBalancer> airTempBalancer) { _airTempBalancer.setObject(airTempBalancer); }
    inline shared_ptr<HydroponicsBalancer> getAirTemperatureBalancer(bool force = false) { _airTempBalancer.updateBalancerIfNeeded(force); return _airTempBalancer.getObject(); }

    shared_ptr<HydroponicsBalancer> setAirCO2Balancer(float co2Setpoint, Hydroponics_UnitsType co2SetpointUnits);
    inline void setAirCO2Balancer(shared_ptr<HydroponicsBalancer> co2Balancer) { _airCO2Balancer.setObject(co2Balancer); }
    inline shared_ptr<HydroponicsBalancer> getAirCO2Balancer(bool force = false) { _airCO2Balancer.updateBalancerIfNeeded(force); return _airCO2Balancer.getObject(); }

    inline Hydroponics_PositionIndex getChannelNumber() const { return _id.posIndex; }

    inline DateTime getLastWaterChangeDate() const { return DateTime((uint32_t)_lastChangeDate); }
    inline void notifyWaterChanged() { _lastChangeDate = unixNow(); }

    inline DateTime getLastPruningDate() const { return DateTime((uint32_t)_lastPruningDate); }
    inline void notifyPruningCompleted() { _lastPruningDate = unixNow(); }

    inline DateTime getLastFeeding() const { return DateTime((uint32_t)_lastFeedingDate); }
    inline int8_t getFeedingsToday() const { return _numFeedingsToday; }
    inline void notifyFeedingBegan() { _numFeedingsToday++; _lastFeedingDate = unixNow(); }
    inline void notifyFeedingEnded() { ; }
    inline void notifyDayChanged() { _numFeedingsToday = 0; }

protected:
    time_t _lastChangeDate;                                 // Last water change date (recycling systems only, UTC)
    time_t _lastPruningDate;                                // Last pruning date (pruning crops only, UTC)
    time_t _lastFeedingDate;                                // Last feeding date (UTC)
    int8_t _numFeedingsToday;                               // Number of feedings performed today

    Hydroponics_UnitsType _tdsUnits;                        // TDS units preferred
    Hydroponics_UnitsType _tempUnits;                       // Temperature units preferred

    HydroponicsSensorAttachment _waterPH;                   // Water PH sensor attachment
    HydroponicsSensorAttachment _waterTDS;                  // Water TDS sensor attachment
    HydroponicsSensorAttachment _waterTemp;                 // Water temp sensor attachment
    HydroponicsSensorAttachment _airTemp;                   // Air temp sensor attachment
    HydroponicsSensorAttachment _airCO2;                    // Air CO2 sensor attachment

    HydroponicsBalancerAttachment _waterPHBalancer;         // Water pH balancer (assigned by scheduler when needed)
    HydroponicsBalancerAttachment _waterTDSBalancer;        // Water TDS balancer (assigned by scheduler when needed)
    HydroponicsBalancerAttachment _waterTempBalancer;       // Water temperature balancer (assigned by scheduler when needed)
    HydroponicsBalancerAttachment _airTempBalancer;         // Air temperature balancer (assigned by user if desired)
    HydroponicsBalancerAttachment _airCO2Balancer;          // Air CO2 balancer (assigned by user if desired)

    virtual void saveToData(HydroponicsData *dataOut) override;
};


// Infinite Pipe Reservoir
// An infinite pipe reservoir is like your standard water main - it's not technically
// unlimited, but you can act like it is. Used for reservoirs that should behave as
// alwaysFilled (e.g. water mains) or not (e.g. drainage pipes).
class HydroponicsInfiniteReservoir : public HydroponicsReservoir {
public:
    HydroponicsInfiniteReservoir(Hydroponics_ReservoirType reservoirType,
                                 Hydroponics_PositionIndex reservoirIndex,
                                 bool alwaysFilled = true,
                                 int classType = Pipe);
    HydroponicsInfiniteReservoir(const HydroponicsInfiniteReservoirData *dataIn);

    virtual bool isFilled() override;
    virtual bool isEmpty() override;

    virtual HydroponicsSensorAttachment &getWaterVolume() override;

protected:
    HydroponicsSensorAttachment _waterVolume;               // Water volume sensor attachment (defunct)
    bool _alwaysFilled;                                     // Always filled flag

    virtual void saveToData(HydroponicsData *dataOut) override;
};


// Reservoir Serialization Data
struct HydroponicsReservoirData : public HydroponicsObjectData {
    Hydroponics_UnitsType volumeUnits;

    HydroponicsReservoirData();
    virtual void toJSONObject(JsonObject &objectOut) const override;
    virtual void fromJSONObject(JsonObjectConst &objectIn) override;
};

// Fluid Reservoir Serialization Data
struct HydroponicsFluidReservoirData : public HydroponicsReservoirData {
    float maxVolume;
    char volumeSensor[HYDRUINO_NAME_MAXSIZE];
    HydroponicsTriggerSubData filledTrigger;
    HydroponicsTriggerSubData emptyTrigger;

    HydroponicsFluidReservoirData();
    virtual void toJSONObject(JsonObject &objectOut) const override;
    virtual void fromJSONObject(JsonObjectConst &objectIn) override;
};

// Feed Water Reservoir Serialization Data
struct HydroponicsFeedReservoirData : public HydroponicsFluidReservoirData {
    time_t lastChangeDate;
    time_t lastPruningDate;
    time_t lastFeedingDate;
    uint8_t numFeedingsToday;
    Hydroponics_UnitsType tdsUnits;
    Hydroponics_UnitsType tempUnits;
    char waterPHSensor[HYDRUINO_NAME_MAXSIZE];
    char waterTDSSensor[HYDRUINO_NAME_MAXSIZE];
    char waterTempSensor[HYDRUINO_NAME_MAXSIZE];
    char airTempSensor[HYDRUINO_NAME_MAXSIZE];
    char airCO2Sensor[HYDRUINO_NAME_MAXSIZE];

    HydroponicsFeedReservoirData();
    virtual void toJSONObject(JsonObject &objectOut) const override;
    virtual void fromJSONObject(JsonObjectConst &objectIn) override;
};

// Infinite Pipe Reservoir Serialization Data
struct HydroponicsInfiniteReservoirData : public HydroponicsReservoirData {
    bool alwaysFilled;

    HydroponicsInfiniteReservoirData();
    virtual void toJSONObject(JsonObject &objectOut) const override;
    virtual void fromJSONObject(JsonObjectConst &objectIn) override;
};

#endif // /ifndef HydroponicsReservoirs_H
