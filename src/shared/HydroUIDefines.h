/*  Hydruino: Simple automation controller for hydroponic grow systems.
    Copyright (C) 2022-2023 NachtRaveVL     <nachtravevl@gmail.com>
    Hydruino UI Defines
*/

#ifndef HydroUIDefines_H
#define HydroUIDefines_H

#if F_SPD >= 48000000                                       // Resolve an appropriate UI update speed (1-10)
#define HYDRO_UI_UPDATE_SPEED           10
#elif F_SPD >= 32000000
#define HYDRO_UI_UPDATE_SPEED           5
#elif F_SPD >= 16000000
#define HYDRO_UI_UPDATE_SPEED           2
#endif

// The following sizes only matter for architectures that do not have STL support (AVR/SAM)
#define HYDRO_UI_REMOTECONTROLS_MAXSIZE 2                   // Maximum array size for remote controls list (max # of remote controls)

#define HYDRO_UI_RENDERER_BUFFERSIZE    30                  // Default buffer size for display renderer
#define HYDRO_UI_I2CLCD_BASEADDR        0x20                // Base address of I2C LiquidCrystalIO LCDs (bitwise or'ed with passed address)
#define HYDRO_UI_KEYREPEAT_SPEED        20                  // Default key press repeat speed
#define HYDRO_UI_REMOTESERVER_PORT      3333                // Default remote control server's listening port
#define HYDRO_UI_3X4MATRIX_KEYS         "123456789*0#"      // Default 3x4 matrix keyboard keys
#define HYDRO_UI_4X4MATRIX_KEYS         "123A456B789C*0#D"  // Default 4x4 matrix keyboard keys
#define HYDRO_UI_NX4MATRIX_ACTIONS      "*#AB"              // Default next char, back char, enter char, and delete char on keyboard
#define HYDRO_UI_GFXTFT_USES_AN_SLIDER  true                // Default analog slider usage for AdafruitGFX/TFTe_SPI displays
#define HYDRO_UI_TFTTOUCH_USES_RAW      false               // Default raw touch usage for TFTTouch

// Default graphical display theme base (CoolBlue, DarkMode)
#define HYDRO_UI_GFX_DISP_THEME_BASE    CoolBlue            
#define HYDRO_UI_GFX_DISP_THEME_SMLMED  SM
#define HYDRO_UI_GFX_DISP_THEME_MEDLRG  ML


// ST77XX Device Tab
enum Hydro_ST7735Tab : signed char {
    Hydro_ST7735Tab_Green               = 0x00,             // Green tag
    Hydro_ST7735Tab_Red                 = 0x01,             // Red tag
    Hydro_ST7735Tab_Black               = 0x02,             // Black tag
    Hydro_ST7735Tab_Green144            = 0x01,             // Green144 tag
    Hydro_ST7735Tab_Mini160x80          = 0x04,             // Mini160x80 tag
    Hydro_ST7735Tab_Hallowing           = 0x05,             // Hallowing tag
    Hydro_ST7735Tab_Mini160x80_Plugin   = 0x06,             // Mini160x80_Plugin tag

    Hydro_ST7735Tab_Undefined           = (int8_t)0xff      // Placeholder
};

// Display Orientation
enum Hydro_DisplayOrientation : signed char {
    Hydro_DisplayOrientation_R0,                            // Standard landscape orientation
    Hydro_DisplayOrientation_R1,                            // 90 degree clockwise rotation
    Hydro_DisplayOrientation_R2,                            // 180 degree clockwise rotation
    Hydro_DisplayOrientation_R3,                            // 270 degree clockwise rotation
    Hydro_DisplayOrientation_HorzMirror,                    // Horizontally mirrored (if supported)
    Hydro_DisplayOrientation_VertMirror,                    // Vertically mirrored (if supported)

    Hydro_DisplayOrientation_Count,                         // Placeholder
    Hydro_DisplayOrientation_Undefined = -1                 // Placeholder
};

// Display Theme
enum Hydro_DisplayTheme : signed char {
    Hydro_DisplayTheme_CoolBlue_ML,                         // Cool blue theme for medium to large color displays (larger fonts/more padding)
    Hydro_DisplayTheme_CoolBlue_SM,                         // Cool blue theme for small to medium color displays (smaller fonts/less padding)
    Hydro_DisplayTheme_DarkMode_ML,                         // Dark mode theme for medium to large color displays (larger fonts/more padding)
    Hydro_DisplayTheme_DarkMode_SM,                         // Dark mode theme for small to medium color displays (smaller fonts/less padding)
    Hydro_DisplayTheme_MonoOLED,                            // Monochrome/OLED theme for small to medium monochrome displays, /w standard border
    Hydro_DisplayTheme_MonoOLED_Inv,                        // Monochrome/OLED theme for small to medium monochrome displays, /w inverted colors

    Hydro_DisplayTheme_Count,                               // Placeholder
    Hydro_DisplayTheme_Undefined = -1                       // Placeholder
};

// Remote Control
enum Hydro_RemoteControl : signed char {
    Hydro_RemoteControl_Disabled,                           // Disabled remote control
    Hydro_RemoteControl_Serial,                             // Remote control by Serial or Bluetooth AT, requires UART setup
    Hydro_RemoteControl_Simhub,                             // Remote control by Simhub serial connector, requires UART setup
    Hydro_RemoteControl_WiFi,                               // Remote control by WiFi, requires enabled WiFi
    Hydro_RemoteControl_Ethernet,                           // Remote control by Ethernet, requires enabled Ethernet

    Hydro_RemoteControl_Count,                              // Placeholder
    Hydro_RemoteControl_Undefined = -1                      // Placeholder
};

// Rotary Encoder Speed
enum Hydro_EncoderSpeed : signed char {
    Hydro_EncoderSpeed_FullCycle,                           // Detent after every full cycle of both signals, A and B
    Hydro_EncoderSpeed_HalfCycle,                           // Detent on every position where A == B
    Hydro_EncoderSpeed_QuarterCycle,                        // Detent after every signal change, A or B

    Hydro_EncoderSpeed_Undefined = -1                       // Placeholder
};

// ESP32 Touch Key High Reference Voltage
enum Hydro_ESP32Touch_HighRef : signed char {
    Hydro_ESP32Touch_HighRef_Keep,                          // No change
    Hydro_ESP32Touch_HighRef_V_2V4,                         // 2.4v
    Hydro_ESP32Touch_HighRef_V_2V5,                         // 2.5v
    Hydro_ESP32Touch_HighRef_V_2V6,                         // 2.6v
    Hydro_ESP32Touch_HighRef_V_2V7,                         // 2.7v
    Hydro_ESP32Touch_HighRef_Max,                           // Max voltage

    Hydro_ESP32Touch_HighRef_Undefined = -1                 // Placeholder
};

// ESP32 Touch Key Low Reference Voltage
enum Hydro_ESP32Touch_LowRef : signed char {
    Hydro_ESP32Touch_LowRef_Keep,                           // No change
    Hydro_ESP32Touch_LowRef_V_0V5,                          // 0.5v
    Hydro_ESP32Touch_LowRef_V_0V6,                          // 0.6v
    Hydro_ESP32Touch_LowRef_V_0V7,                          // 0.7v
    Hydro_ESP32Touch_LowRef_V_0V8,                          // 0.8v
    Hydro_ESP32Touch_LowRef_Max,                            // Max voltage

    Hydro_ESP32Touch_LowRef_Undefined = -1                  // Placeholder
};

// ESP32 Touch Key High Ref Volt Attenuation
enum Hydro_ESP32Touch_HighRefAtten : signed char {
    Hydro_ESP32Touch_HighRefAtten_Keep,                     // No change
    Hydro_ESP32Touch_HighRefAtten_V_1V5,                    // 1.5v
    Hydro_ESP32Touch_HighRefAtten_V_1V,                     // 1v
    Hydro_ESP32Touch_HighRefAtten_V_0V5,                    // 0.5v
    Hydro_ESP32Touch_HighRefAtten_V_0V,                     // 0v
    Hydro_ESP32Touch_HighRefAtten_Max,                      // Max voltage

    Hydro_ESP32Touch_HighRefAtten_Undefined = -1            // Placeholder
};

// LCD Backlight Mode
enum Hydro_BacklightMode : signed char {
    Hydro_BacklightMode_Normal,                             // The backlight is active HIGH
    Hydro_BacklightMode_Inverted,                           // The backlight is active LOW
    Hydro_BacklightMode_PWM,                                // The backlight is connected directly to a PWM pin

    Hydro_BacklightMode_Undefined = -1                      // Placeholder
};


class HydruinoBaseUI;
class HydroDisplayDriver;
class HydroInputDriver;
class HydroRemoteControl;
struct HydroUIData;

#endif // /ifndef HydroUIDefines_H
