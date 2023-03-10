/*  Hydruino: Simple automation controller for hydroponic grow systems.
    Copyright (C) 2022-2023 NachtRaveVL     <nachtravevl@gmail.com>
    Hydruino Base UI
*/

#include <Hydruino.h>
#ifdef HYDRO_USE_GUI
#ifndef HydroBaseUI_H
#define HydroBaseUI_H

#include "HydroUIDefines.h"
#include "HydroUIInlines.hh"

// tcMenu Plugin Adaptations
#include "tcMenu_Display_AdaFruitGfx.h"
#include "tcMenu_Display_LiquidCrystal.h"
#include "tcMenu_Display_TfteSpi.h"
#include "tcMenu_Display_U8g2.h"
#include "tcMenu_Input_AdaTouchDriver.h"
#include "tcMenu_Remote_EthernetTransport.h"
#include "tcMenu_Remote_SerialTransport.h"
#include "tcMenu_Remote_SimhubConnector.h"
#include "tcMenu_Remote_WiFiTransport.h"
#include "tcMenu_Theme_CoolBlueModern.h"
#include "tcMenu_Theme_CoolBlueTraditional.h"
#include "tcMenu_Theme_DarkModeModern.h"
#include "tcMenu_Theme_DarkModeTraditional.h"
#include "tcMenu_Theme_MonoBordered.h"
#include "tcMenu_Theme_MonoInverse.h"

#include "HydroDisplayDrivers.h"
#include "HydroInputDrivers.h"
#include "HydroRemoteControls.h"

// Base UI
// The base class that manages interaction with the tcMenu UI system.
class HydruinoBaseUI : public HydroUIInterface {
public:
    HydruinoBaseUI(UIControlSetup uiControlSetup = UIControlSetup(),        // UI control input setup
                   UIDisplaySetup uiDisplaySetup = UIDisplaySetup(),        // UI display output setup 
                   bool isActiveLowIO = true,                               // Logic level usage for control & display IO pins
                   bool allowInterruptableIO = true,                        // Allows interruptable pins to interrupt, else forces polling
                   bool enableTcUnicodeFonts = true);                       // Enables tcUnicode UTF8 fonts usage instead of library fonts
    virtual ~HydruinoBaseUI();

    void init(uint8_t updatesPerSec,                                        // Updates per second (1 to 10)
              Hydro_DisplayTheme displayTheme,                              // Display theme to apply
              bool analogSlider = false);                                   // Slider usage for analog items
    void init();                                                            // Standard initializer

    void addRemote(Hydro_RemoteControl rcType,                              // Type of remote control
                   UARTDeviceSetup rcSetup = UARTDeviceSetup(),             // Remote control serial setup (if serial based), else ignored
                   uint16_t rcServerPort = HYDRO_UI_REMOTESERVER_PORT);     // Remote control server listening port (if networking based), else ignored

    virtual bool begin() override;                                          // Begins UI

    virtual void setNeedsLayout() override;

    virtual bool isFullUI() = 0;
    inline bool isMinUI() { return !isFullUI(); }

protected:
    const bool _isActiveLow;                                // IO pins use active-low signaling logic
    const bool _allowISR;                                   // Perform ISR checks to determine ISR eligibility
    const bool _utf8Fonts;                                  // Using tcUnicode library fonts
    const bool _gfxOrTFT;                                   // Display is Adafruit_GFX or TFT_eSPI

    MenuItem *_menuRoot;                                    // Menu root item (strong)
    HydroInputDriver *_input;                               // Input driver (owned)
    HydroDisplayDriver *_display;                           // Display driver (owned)
    TcMenuRemoteServer *_remoteServer;                      // Remote control server (owned)
    Vector<HydroRemoteControl *, HYDRO_UI_REMOTECONTROLS_MAXSIZE> _remotes; // Remote controls list (owned)
};


// UI Serialization Data
struct HydroUIData : public HydroData {
    uint8_t updatesPerSec;                                  // Updates per second (1-10, default: HYDRO_UI_UPDATE_SPEED)
    Hydro_DisplayTheme displayTheme;                        // Display theme (if supported)
    float joystickCalib[3];                                 // Joystick calibration ({midX,midY,zeroTol}, default: {0.5,0.5,0.05})

    HydroUIData();
    virtual void toJSONObject(JsonObject &objectOut) const override;
    virtual void fromJSONObject(JsonObjectConst &objectIn) override;
};

#include "tcMenu_Display_AdaFruitGfx.hpp"
#include "HydroDisplayDrivers.hpp"

#endif // /ifndef HydroBaseUI_H
#endif
