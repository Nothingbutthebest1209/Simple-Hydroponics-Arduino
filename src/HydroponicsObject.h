/*  Hydruino: Simple automation controller for hydroponic grow systems.
    Copyright (C) 2022 NachtRaveVL          <nachtravevl@gmail.com>
    Hydroponics Object
*/

#ifndef HydroponicsObject_H
#define HydroponicsObject_H

struct HydroponicsIdentity;
class HydroponicsObject;
class HydroponicsSubObject;

struct HydroponicsObjectData;

#include "Hydroponics.h"
#include "HydroponicsData.h"

// Creates object from passed object data (return ownership transfer - user code *must* delete returned object)
extern HydroponicsObject *newObjectFromData(const HydroponicsData *dataIn);

// Shortcut to get shared pointer for object with static pointer cast built-in.
template<class T = HydroponicsObjInterface> inline SharedPtr<T> getSharedPtr(const HydroponicsObjInterface *obj) { return obj ? hy_reinterpret_ptr_cast<T>(obj->getSharedPtr()) : nullptr; }


// Simple class for referencing an object in the Hydroponics system.
// This class is mainly used to simplify object key generation, which is used when we
// want to uniquely refer to objects in the Hydroponics system.
struct HydroponicsIdentity {
    enum : signed char { Actuator, Sensor, Crop, Reservoir, Rail, Unknown = -1 } type; // Object type (custom RTTI)
    inline bool isActuatorType() const { return type == Actuator; }
    inline bool isSensorType() const { return type == Sensor; }
    inline bool isCropType() const { return type == Crop; }
    inline bool isReservoirType() const { return type == Reservoir; }
    inline bool isRailType() const { return type == Rail; }
    inline bool isUnknownType() const { return type <= Unknown; }

    union {
        Hydroponics_ActuatorType actuatorType;              // As actuator type enumeration
        Hydroponics_SensorType sensorType;                  // As sensor type enumeration
        Hydroponics_CropType cropType;                      // As crop type enumeration
        Hydroponics_ReservoirType reservoirType;            // As reservoir type enumeration
        Hydroponics_RailType railType;                      // As rail type enumeration
    } objTypeAs;                                            // Enumeration type union
    Hydroponics_PositionIndex posIndex;                     // Position index
    String keyString;                                       // String key
    Hydroponics_KeyType key;                                // UInt Key

    // Default constructor (incomplete id)
    HydroponicsIdentity();

    // Copy key (incomplete id)
    HydroponicsIdentity(Hydroponics_KeyType key);

    // Copy into keyStr (incomplete id)
    HydroponicsIdentity(const char *idKeyStr);
    // Copy into keyStr (incomplete id)
    HydroponicsIdentity(String idKey);

    // Copy id with new position index
    HydroponicsIdentity(const HydroponicsIdentity &id,
                        Hydroponics_PositionIndex positionIndex);

    // Actuator id constructor
    HydroponicsIdentity(Hydroponics_ActuatorType actuatorType,
                        Hydroponics_PositionIndex positionIndex = HYDRUINO_POS_SEARCH_FROMBEG);
    // Sensor id constructor
    HydroponicsIdentity(Hydroponics_SensorType sensorType,
                        Hydroponics_PositionIndex positionIndex = HYDRUINO_POS_SEARCH_FROMBEG);
    // Crop id constructor
    HydroponicsIdentity(Hydroponics_CropType cropType,
                        Hydroponics_PositionIndex positionIndex = HYDRUINO_POS_SEARCH_FROMBEG);
    // Reservoir id constructor
    HydroponicsIdentity(Hydroponics_ReservoirType reservoirType,
                        Hydroponics_PositionIndex positionIndex = HYDRUINO_POS_SEARCH_FROMBEG);
    // Rail id constructor
    HydroponicsIdentity(Hydroponics_RailType railType,
                        Hydroponics_PositionIndex positionIndex = HYDRUINO_POS_SEARCH_FROMBEG);

    // Data constructor
    HydroponicsIdentity(const HydroponicsData *dataIn);

    // Used to update key value after modification, returning new key by convenience
    Hydroponics_KeyType regenKey();

    inline operator bool() const { return key != (Hydroponics_KeyType)-1; }
    inline bool operator==(const HydroponicsIdentity &otherId) const { return key == otherId.key; }
    inline bool operator!=(const HydroponicsIdentity &otherId) const { return key != otherId.key; }
};


// Hydroponic Object Base
// A simple base class for referring to objects in the Hydroponics system.
class HydroponicsObject : public HydroponicsObjInterface {
public:
    inline bool isActuatorType() const { return _id.isActuatorType(); }
    inline bool isSensorType() const { return _id.isSensorType(); }
    inline bool isCropType() const { return _id.isCropType(); }
    inline bool isReservoirType() const { return _id.isReservoirType(); }
    inline bool isRailType() const { return _id.isRailType(); }
    inline bool isUnknownType() const { return _id.isUnknownType(); }

    HydroponicsObject(HydroponicsIdentity id);              // Standard constructor
    HydroponicsObject(const HydroponicsData *dataIn);       // Data constructor
    virtual ~HydroponicsObject();                           // Destructor

    virtual void update();                                  // Called over intervals of time by runloop
    virtual void handleLowMemory();                         // Called upon low memory condition to try and free memory up

    HydroponicsData *newSaveData();                         // Saves object state to proper backing data

    void allocateLinkages(size_t size = 1);                 // Allocates linkage list of specified size (reallocates)
    virtual bool addLinkage(HydroponicsObject *obj) override; // Adds linkage to this object, returns true upon initial add
    virtual bool removeLinkage(HydroponicsObject *obj) override; // Removes linkage from this object, returns true upon last remove
    bool hasLinkage(HydroponicsObject *obj) const;          // Checks object linkage to this object

    // Returns the linkages this object contains, along with refcount for how many times it has registered itself as linked (via attachment points).
    // Objects are considered strong pointers, since existence -> SharedPtr ref to this instance exists.
    inline Pair<uint8_t, Pair<HydroponicsObject *, int8_t> *> getLinkages() const { return make_pair(_linksSize, _links); }

    virtual HydroponicsIdentity getId() const override;     // Returns the unique Identity of the object
    virtual Hydroponics_KeyType getKey() const override;    // Returns the unique key of the object
    virtual String getKeyString() const override;           // Returns the key string of the object
    virtual SharedPtr<HydroponicsObjInterface> getSharedPtr() const override; // Returns the SharedPtr instance of the object

#ifdef HYDRUINO_USE_VIRTMEM
    static void* operator new(size_t size);
    static void operator delete(void*);
#endif

protected:
    HydroponicsIdentity _id;                                // Object id
    uint8_t _linksSize;                                     // Size of object linkages
    Pair<HydroponicsObject *, int8_t> *_links;              // Object linkages (owned, lazily allocated)

    virtual HydroponicsData *allocateData() const;          // Only up to base type classes (sensor, crop, etc.) does this need overriden
    virtual void saveToData(HydroponicsData *dataOut);      // *ALL* derived classes must override and implement

private:
    HydroponicsObject() = default;                          // Private constructor to disable derived/public access
};


// Hydroponics Sub Object Base
// A base class for sub objects that are typically found embedded in bigger main objects,
// but want to replicate some of the same functionality. Not required to be inherited from.
class HydroponicsSubObject : public HydroponicsObjInterface {
public:
    virtual HydroponicsIdentity getId() const override;
    virtual Hydroponics_KeyType getKey() const override;
    virtual String getKeyString() const override;
    virtual SharedPtr<HydroponicsObjInterface> getSharedPtr() const override;

    virtual bool addLinkage(HydroponicsObject *obj) override;
    virtual bool removeLinkage(HydroponicsObject *obj) override;

#ifdef HYDRUINO_USE_VIRTMEM
    static void* operator new(size_t size);
    static void operator delete(void*);
#endif
};


// Hydroponics Object Data Intermediate
// Intermediate data class for object data.
struct HydroponicsObjectData : public HydroponicsData {
    char name[HYDRUINO_NAME_MAXSIZE];

    HydroponicsObjectData();
    virtual void toJSONObject(JsonObject &objectOut) const override;
    virtual void fromJSONObject(JsonObjectConst &objectIn) override;
};

#endif // /ifndef HydroponicsObject_H
