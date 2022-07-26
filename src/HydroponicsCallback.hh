// Copied and slightly modified from: https://github.com/tomstewart89/Callback

#ifndef CALLBACK_H
#define CALLBACK_H

enum SlotType { Function, Method };

// The Slot base class, its template parameter indicates the datatype of the parameters it expects to receive. Slots can only
// be connected to Signals with identical ParameterTypes.
template <class ParameterType> class Slot {
protected:
    SlotType _slotType;

    Slot(SlotType slotType) : _slotType(slotType) { }

public:
    virtual ~Slot() { }

    // Allows the slot to be called by the signal during firing.
    virtual void operator()(ParameterType param) const = 0;

    // Allows the slot to be removed via comparison.
    virtual bool operator==(const Slot<ParameterType>* slot) const = 0;

    // Allows the signal to take a copy of the slot so that it can maintain an internal reference to it upon connection.
    // Essentially a virtual copy consructor.
    virtual Slot<ParameterType>* clone() const = 0;

    // Provides roughly the same mechanism as RTTI.
    SlotType slotType() const {
        return _slotType;
    }
};

// The Signal class, we can implant these into ends and allow means to connect their members to them should they want to
// receive callbacks from their children means. Ofcourse it's possible that these callbacks are made within the context of
// an interrupt so the receipient will want to be fairly quick about how they process it.
template <class ParameterType, int Slots = 8> class Signal {
    Slot<ParameterType>* _connections[Slots];
	int _nextSlot;

public:
    Signal() : _connections{nullptr}, _nextSlot(0) { }

    // Since the signal takes copies of all the input slots via clone() it needs to clean up after itself when being destroyed.
    virtual ~Signal() {
        for(int i = 0; i < _nextSlot; ++i)
            delete _connections[i];
    }

    // Adds slot to list of connections.
    void attach(const Slot<ParameterType>& slot) {
        if (_nextSlot < Slots) {
            // Connect it up and away we go
            _connections[_nextSlot++] = slot.clone();
        }
	}

    // Removes slot from list of connections.
    void detach(const Slot<ParameterType>& slot) {
        for (int i = _nextSlot - 1; i >= 0; --i) {
            if (slot == _connections[i]) {
                delete _connections[i];
                --_nextSlot;

                for (int j = i; j < _nextSlot; ++j)
                    _connections[j] = _connections[j + 1];
                _connections[_nextSlot] = NULL;
            }
        }
    }

    // Visits each of its listeners and executes them via operator().
    void fire(ParameterType param) const {
        for(int i = 0; i < _nextSlot; ++i)
            (*_connections[i])(param);
    }
};

// FunctionSlot is a subclass of Slot for use with function pointers. In truth there's not really any need to wrap up free
// standing function pointers into slots since any function in C/C++ is happy to accept a raw function pointer and execute it.
// However this system allows free standing functions to be used alongside member functions or even arbitrary functor objects.
template <class ParameterType> class FunctionSlot : public Slot<ParameterType> {
    typedef void (*FunctPtr)(ParameterType);

    // A free standing function pointer.
    FunctPtr _funct;

public:
    FunctionSlot(FunctPtr funct) : Slot<ParameterType>(Function), _funct(funct) { }

    // Copy the slot
    Slot<ParameterType> *clone() const {
        return new FunctionSlot<ParameterType>(_funct);
    }

    // Execute the slot.
    void operator() (ParameterType param) const {
        return (_funct)(param);
    }

    // Test the slot.
    inline operator bool() const { return _funct; }

    // Function access.
    inline FunctPtr getFunct() const { return _funct; }

    // Compares the slot.
    bool operator==(const Slot<ParameterType>* slot) const {
        if (slot && slot->slotType() == Slot<ParameterType>::_slotType) {
            const FunctionSlot<ParameterType>* functSlot = reinterpret_cast<const FunctionSlot<ParameterType>*>(slot);
            return functSlot && functSlot->_funct == _funct;
        }
        return false;
    }
};

// MethodSlot is a subclass of Slot that allows member function pointers to be used as slots. While free standing
// pointers to functions are relatively intuitive here, Members functions need an additional template parameter, the
// owner object type and they are executed via the ->* operator.
template <class ObjectType, class ParameterType> class MethodSlot : public Slot<ParameterType> {
    typedef void (ObjectType::*FunctPtr)(ParameterType);

    // The function pointer's owner object.
    ObjectType *_obj;

    // A function-pointer-to-method of class ObjectType.
    FunctPtr _funct;

public:
    MethodSlot(ObjectType *obj, FunctPtr funct) : Slot<ParameterType>(Method), _obj(obj), _funct(funct) { }
    template <class T> MethodSlot(const MethodSlot<T, ParameterType> &slot)
        : Slot<ParameterType>(Method), _obj(reinterpret_cast<ObjectType *>(slot.getObject())), _funct(reinterpret_cast<FunctPtr>(slot.getFunct())) { }

    // Copy the slot.
    Slot<ParameterType> *clone() const {
        return new MethodSlot<ObjectType, ParameterType>(_obj, _funct);
    }

    // Execute the slot.
    void operator() (ParameterType param) const {
        return (_obj->*_funct)(param);
    }

    // Test the slot.
    inline operator bool() const { return _obj && _funct; }

    // Object access.
    inline ObjectType *getObject() const { return _obj; }

    // Function access.
    inline FunctPtr getFunct() const { return _funct; }

    // Compare the slot.
    bool operator==(const Slot<ParameterType>* slot) const {
        if (slot && slot->slotType() == Slot<ParameterType>::_slotType) {
            const MethodSlot<ObjectType, ParameterType>* methSlot = reinterpret_cast<const MethodSlot<ObjectType, ParameterType>*>(slot);
            return methSlot && methSlot->_obj == _obj && methSlot->_funct == _funct;
        }
        return false;
    }
};

#endif // CALLBACK_H
