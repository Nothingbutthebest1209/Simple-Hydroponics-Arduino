// Simple-Hydroponics-Arduino Vertical Nutrient Film Technique (NFT) Example
// TODO

#include <Hydroponics.h>

// Pins & Class Instances
#define SETUP_PIEZO_BUZZER_PIN      -1              // Piezo buzzer pin, else -1
#define SETUP_EEPROM_DEVICE_SIZE    I2C_DEVICESIZE_24LC256 // EEPROM bit storage size (use I2C_DEVICESIZE_* defines), else 0
#define SETUP_SD_CARD_CS_PIN        SS              // SD card CS pin, else -1
#define SETUP_CTRL_INPUT_PINS       {31.33,30,32}   // Control input pin ribbon, else {-1}
#define SETUP_EEPROM_I2C_ADDR       B000            // EEPROM address
#define SETUP_RTC_I2C_ADDR          B000            // RTC i2c address (only B000 can be used atm)
#define SETUP_LCD_I2C_ADDR          B000            // LCD i2c address
#define SETUP_I2C_WIRE_INST         Wire            // I2C wire class instance
#define SETUP_I2C_SPEED             400000U         // I2C speed, in Hz
#define SETUP_SD_CARD_SPI_SPEED     4000000U        // SD card SPI speed, in Hz (ignored if on Teensy)
#define SETUP_WIFI_INST             WiFi            // WiFi class instance

// System Settings
#define SETUP_SYSTEM_MODE           Recycling       // System run mode (Recycling, DrainToWaste)
#define SETUP_MEASURE_MODE          Imperial        // System measurement mode (Default, Imperial, Metric, Scientific)
#define SETUP_LCD_OUT_MODE          Disabled        // System LCD output mode (Disabled, 20x4LCD, 20x4LCD_Swapped, 16x2LCD, 16x2LCD_Swapped)
#define SETUP_CTRL_IN_MODE          Disabled        // System control input mode (Disabled, 2x2Matrix, 4xButton, 6xButton, RotaryEncoder)
#define SETUP_SYS_NAME              "Hydruino"      // System name
#define SETUP_SYS_TIMEZONE          +0              // System timezone offset
#define SETUP_CONFIG_FILE           "hydruino.cfg"  // System config file name

// WiFi Settings
#define SETUP_ENABLE_WIFI           false           // If WiFi is enabled
#define SETUP_WIFI_SSID             "CHANGE_ME"     // WiFi SSID
#define SETUP_WIFI_PASS             "CHANGE_ME"     // WiFi password

// Logging & Data Publishing Settings
#define SETUP_LOG_SD_ENABLE         true            // If system logging is enabled to SD card
#define SETUP_LOG_FILE_PREFIX       "logs/hy"       // System logs file prefix (appended with YYMMDD.txt)
#define SETUP_DATA_SD_ENABLE        true            // If system data publishing is enabled to SD card
#define SETUP_DATA_FILE_PREFIX      "data/hy"       // System data publishing files prefix (appended with YYMMDD.csv)

// Base Setup
#define SETUP_FEED_RESERVOIR_SIZE   4               // Reservoir size, in default measurement units
#define SETUP_AC_POWER_RAIL_TYPE    AC110V          // Rail power type used for AC rail (AC110V, AC220V)
#define SETUP_DC_POWER_RAIL_TYPE    DC12V           // Rail power type used for peristaltic pump rail (DC5V, DC12V)
#define SETUP_AC_SUPPLY_POWER       0               // Maximum AC supply power wattage, else 0 if not known (-> use simple rails)
#define SETUP_DC_SUPPLY_POWER       0               // Maximum DC supply power wattage, else 0 if not known (-> use simple rails)

// Device Setup
#define SETUP_PH_METER_PIN          A0              // pH meter sensor pin (analog), else -1
#define SETUP_TDS_METER_PIN         A1              // TDS meter sensor pin (analog), else -1
#define SETUP_CO2_SENSOR_PIN        -1              // CO2 meter sensor pin (analog), else -1
#define SETUP_POWER_SENSOR_PIN      -1              // Power meter sensor pin (analog), else -1
#define SETUP_FLOW_RATE_SENSOR_PIN  -1              // Main feed pump flow rate sensor pin (analog/PWM), else -1
#define SETUP_DS18_WTEMP_PIN        3               // DS18* water temp sensor data pin (digital), else -1
#define SETUP_DHT_ATEMP_PIN         4               // DHT* air temp sensor data pin (digital), else -1
#define SETUP_DHT_SENSOR_TYPE       DHT12           // DHT sensor type enum (use DHT* defines)
#define SETUP_VOL_FILLED_PIN        -1              // Water level filled indicator pin (digital/ISR), else -1
#define SETUP_VOL_EMPTY_PIN         -1              // Water level empty indicator pin (digital/ISR), else -1
#define SETUP_GROW_LIGHTS_PIN       22              // Grow lights relay pin (digital), else -1
#define SETUP_WATER_AERATOR_PIN     24              // Aerator relay pin (digital), else -1
#define SETUP_FEED_PUMP_PIN         26              // Water level low indicator pin, else -1
#define SETUP_WATER_HEATER_PIN      28              // Water heater relay pin (digital), else -1
#define SETUP_WATER_SPRAYER_PIN     -1              // Water sprayer relay pin (digital), else -1
#define SETUP_FAN_EXHAUST_PIN       -1              // Fan exhaust relay pin (digital/PWM), else -1
#define SETUP_NUTRIENT_MIX_PIN      23              // Nutrient premix peristaltic pump relay pin (digital), else -1
#define SETUP_FRESH_WATER_PIN       25              // Fresh water peristaltic pump relay pin (digital), else -1
#define SETUP_PH_UP_PIN             27              // pH up solution peristaltic pump relay pin (digital), else -1
#define SETUP_PH_DOWN_PIN           29              // pH down solution peristaltic pump relay pin (digital), else -1

// Crop Setup
#define SETUP_CROP_ON_TIME          15              // Minutes feeding pumps are to be turned on for
#define SETUP_CROP_OFF_TIME         45              // Minutes feeding pumps are to be turned off for
#define SETUP_CROP1_TYPE            Lettuce         // Type of crop planted at position 1, else Undefined
#define SETUP_CROP1_SUBSTRATE       ClayPebbles     // Type of crop substrate at position 1
#define SETUP_CROP1_SOW_DATE        DateTime(2022, 5, 21) // Date that crop was planted at position 1
#define SETUP_CROP1_SOILM_PIN       -1              // Soil moisture sensor for crop at position 1 pin (analog), else -1
#define SETUP_CROP2_TYPE            Lettuce         // Type of crop planted at position 2, else Undefined
#define SETUP_CROP2_SUBSTRATE       ClayPebbles     // Type of crop substrate at position 2
#define SETUP_CROP2_SOW_DATE        DateTime(2022, 5, 21) // Date that crop was planted at position 2
#define SETUP_CROP2_SOILM_PIN       -1              // Soil moisture sensor for crop at position 2 pin (analog), else -1
#define SETUP_CROP3_TYPE            Lettuce         // Type of crop planted at position 3, else Undefined
#define SETUP_CROP3_SUBSTRATE       ClayPebbles     // Type of crop substrate at position 3
#define SETUP_CROP3_SOW_DATE        DateTime(2022, 5, 21) // Date that crop was planted at position 3
#define SETUP_CROP3_SOILM_PIN       -1              // Soil moisture sensor for crop at position 3 pin (analog), else -1
#define SETUP_CROP4_TYPE            Lettuce         // Type of crop planted at position 4, else Undefined
#define SETUP_CROP4_SUBSTRATE       ClayPebbles     // Type of crop substrate at position 4
#define SETUP_CROP4_SOW_DATE        DateTime(2022, 5, 21) // Date that crop was planted at position 4
#define SETUP_CROP4_SOILM_PIN       -1              // Soil moisture sensor for crop at position 4 pin (analog), else -1
#define SETUP_CROP5_TYPE            Lettuce         // Type of crop planted at position 5, else Undefined
#define SETUP_CROP5_SUBSTRATE       ClayPebbles     // Type of crop substrate at position 5
#define SETUP_CROP5_SOW_DATE        DateTime(2022, 5, 21) // Date that crop was planted at position 5
#define SETUP_CROP5_SOILM_PIN       -1              // Soil moisture sensor for crop at position 5 pin (analog), else -1


byte _SETUP_CTRL_INPUT_PINS[] = SETUP_CTRL_INPUT_PINS;
Hydroponics hydroController(SETUP_PIEZO_BUZZER_PIN,
                            SETUP_EEPROM_DEVICE_SIZE,
                            SETUP_SD_CARD_CS_PIN,
                            _SETUP_CTRL_INPUT_PINS[0],
                            SETUP_EEPROM_I2C_ADDR,
                            SETUP_RTC_I2C_ADDR,
                            SETUP_LCD_I2C_ADDR,
                            SETUP_I2C_WIRE_INST,
                            SETUP_I2C_SPEED,
                            SETUP_SD_CARD_SPI_SPEED,
                            SETUP_WIFI_INST);

#if SETUP_GROW_LIGHTS_PIN >= 0 || SETUP_WATER_AERATOR_PIN >= 0 ||  SETUP_FEED_PUMP_PIN >= 0 || SETUP_WATER_HEATER_PIN >= 0 || SETUP_WATER_SPRAYER_PIN >= 0 || SETUP_FAN_EXHAUST_PIN >= 0
#define SETUP_USE_AC_RAIL
#endif
#if SETUP_NUTRIENT_MIX_PIN >= 0 || SETUP_FRESH_WATER_PIN >= 0 ||  SETUP_PH_UP_PIN >= 0 || SETUP_PH_DOWN_PIN >= 0 || SETUP_FAN_EXHAUST_PIN >= 0
#define SETUP_USE_DC_RAIL
#endif
#if defined(ARDUINO_ARCH_SAM) || defined(ARDUINO_ARCH_SAMD)
#define SETUP_USE_ANALOG_BITRES     12
#else
#define SETUP_USE_ANALOG_BITRES     8
#endif
#define SETUP_USE_DIGITAL_BITRES    12

void setup() {
    #ifdef HYDRUINO_ENABLE_DEBUG_OUTPUT
        Serial.begin(115200);           // Begin USB Serial interface
        while(!Serial) { ; }            // Wait for USB Serial to connect (remove in production)
    #endif
    #if SETUP_ENABLE_WIFI
        String wifiSSID = F(SETUP_WIFI_SSID);
        String wifiPassword = F(SETUP_WIFI_SSID);
    #endif
    if (isValidPin(_SETUP_CTRL_INPUT_PINS[0])) {
        hydroController.setControlInputPinMap(_SETUP_CTRL_INPUT_PINS);
    }
    
    // Sets system config name used in any of the following inits.
    hydroController.setSystemConfigFile(F(SETUP_CONFIG_FILE));

    // Initializes controller with first initialization method that successfully returns.
    if (!(false
        #if SETUP_SD_CARD_CS_PIN >= 0
            || hydroController.initFromSDCard()
        #endif
        #if SETUP_EEPROM_DEVICE_SIZE
            || hydroController.initFromEEPROM()
        #endif
        #if SETUP_ENABLE_WIFI
            //|| hydroController.initFromURL(wifiSSID, wifiPassword, TODO)
        #endif
        )) {
        // First time running controller, set up default initial empty environment.
        hydroController.init(JOIN(Hydroponics_SystemMode,SETUP_SYSTEM_MODE),
                             JOIN(Hydroponics_MeasurementMode,SETUP_MEASURE_MODE),
                             JOIN(Hydroponics_DisplayOutputMode,SETUP_LCD_OUT_MODE),
                             JOIN(Hydroponics_ControlInputMode,SETUP_CTRL_IN_MODE));

        // Set Settings
        hydroController.setSystemName(F(SETUP_SYS_NAME));
        hydroController.setTimeZoneOffset(SETUP_SYS_TIMEZONE);
        #if SETUP_LOG_SD_ENABLE
            hydroController.enableSysLoggingToSDCard(F(SETUP_LOG_FILE_PREFIX));
        #endif
        #if SETUP_DATA_SD_ENABLE
            hydroController.enableDataPublishingToSDCard(F(SETUP_DATA_FILE_PREFIX));
        #endif
        #if SETUP_ENABLE_WIFI
            hydroController.setWiFiConnection(wifiSSID, wifiPassword);
            hydroController.getWiFi();      // Forces start, may block for a while
        #endif

        // Base Objects
        #ifdef SETUP_USE_AC_RAIL
            #if SETUP_AC_SUPPLY_POWER
                auto acRelayPower = hydroController.addRegulatedPowerRail(JOIN(Hydroponics_RailType,SETUP_AC_POWER_RAIL_TYPE),SETUP_AC_SUPPLY_POWER);
            #else
                auto acRelayPower = hydroController.addSimplePowerRail(JOIN(Hydroponics_RailType,SETUP_AC_POWER_RAIL_TYPE));
            #endif
        #endif
        #ifdef SETUP_USE_DC_RAIL
            #if SETUP_DC_SUPPLY_POWER
                auto dcRelayPower = hydroController.addRegulatedPowerRail(JOIN(Hydroponics_RailType,SETUP_DC_POWER_RAIL_TYPE),SETUP_DC_SUPPLY_POWER);
            #else
                auto dcRelayPower = hydroController.addSimplePowerRail(JOIN(Hydroponics_RailType,SETUP_DC_POWER_RAIL_TYPE));
            #endif
        #endif
        auto feedReservoir = hydroController.addFeedWaterReservoir(SETUP_FEED_RESERVOIR_SIZE, hydroController.getSystemMode() != Hydroponics_SystemMode_DrainToWaste);
        auto drainagePipe = hydroController.getSystemMode() == Hydroponics_SystemMode_DrainToWaste ? hydroController.addDrainagePipe() : shared_ptr<HydroponicsInfiniteReservoir>();

        // Analog Sensors
        #if SETUP_PH_METER_PIN >= 0
        {   auto phMeter = hydroController.addAnalogPhMeter(SETUP_PH_METER_PIN, SETUP_USE_ANALOG_BITRES);
            phMeter->setReservoir(feedReservoir);
            feedReservoir->setWaterPHSensor(phMeter);
        }
        #endif
        #if SETUP_TDS_METER_PIN >= 0
        {   auto tdsElectrode = hydroController.addAnalogTDSElectrode(SETUP_TDS_METER_PIN, SETUP_USE_ANALOG_BITRES);
            tdsElectrode->setReservoir(feedReservoir);
            feedReservoir->setWaterTDSSensor(tdsElectrode);
        }
        #endif
        #if SETUP_CO2_SENSOR_PIN >= 0
        {   auto co2Sensor = hydroController.addAnalogCO2Sensor(SETUP_CO2_SENSOR_PIN, SETUP_USE_ANALOG_BITRES);
            co2Sensor->setReservoir(feedReservoir);
            feedReservoir->setAirCO2Sensor(co2Sensor);
        }
        #endif
        #if SETUP_POWER_SENSOR_PIN
        {   auto powerMeter = hydroController.addPowerUsageMeter(SETUP_POWER_SENSOR_PIN, SETUP_USE_ANALOG_BITRES);
            powerMeter->setReservoir(feedReservoir);
            #if SETUP_DC_SUPPLY_POWER
                dcRelayPower->setPowerSensor(powerMeter);
            #endif
        }
        #endif
        #if SETUP_FLOW_RATE_SENSOR_PIN >= 0
        {   auto flowSensor = hydroController.addAnalogPWMPumpFlowSensor(SETUP_FLOW_RATE_SENSOR_PIN, SETUP_USE_ANALOG_BITRES);
            flowSensor->setReservoir(feedReservoir);
            // will be set to main feed pump later via delayed ref
        }
        #endif

        // Digital Sensors
        #if SETUP_DS18_WTEMP_PIN >= 0
        {   auto dsTempSensor = hydroController.addDSTemperatureSensor(SETUP_DS18_WTEMP_PIN, SETUP_USE_DIGITAL_BITRES);
            dsTempSensor->setReservoir(feedReservoir);
            feedReservoir->setWaterTempSensor(dsTempSensor);
        }
        #endif
        #if SETUP_DHT_ATEMP_PIN >= 0
        {   auto dhtTempSensor = hydroController.addDHTTempHumiditySensor(SETUP_DHT_ATEMP_PIN, SETUP_DHT_SENSOR_TYPE);
            dhtTempSensor->setReservoir(feedReservoir);
            feedReservoir->setAirTempSensor(dhtTempSensor);
        }
        #endif

        // Binary->Volume Sensors
        #if SETUP_VOL_FILLED_PIN >= 0
        {   auto filledIndicator = hydroController.addLevelIndicator(SETUP_VOL_FILLED_PIN);
            filledIndicator->setReservoir(feedReservoir);
            feedReservoir->setFilledTrigger(new HydroponicsMeasurementValueTrigger(filledIndicator, 0.5, false));
        }
        #endif
        #if SETUP_VOL_EMPTY_PIN >= 0
        {   auto emptyIndicator = hydroController.addLevelIndicator(SETUP_VOL_EMPTY_PIN);
            emptyIndicator->setReservoir(feedReservoir);
            feedReservoir->setEmptyTrigger(new HydroponicsMeasurementValueTrigger(emptyIndicator, 0.5, false));
        }
        #endif

        // Distance->Volume Sensors
        // TODO: ultrasonic distance
        // TODO: water height meter

        // AC-Based Actuators
        #if SETUP_GROW_LIGHTS_PIN >= 0
        {   auto growLights = hydroController.addGrowLightsRelay(SETUP_GROW_LIGHTS_PIN);
            growLights->setRail(acRelayPower);
            growLights->setReservoir(feedReservoir);
        }
        #endif
        #if SETUP_WATER_AERATOR_PIN >= 0
        {   auto aerator = hydroController.addWaterAeratorRelay(SETUP_WATER_AERATOR_PIN);
            aerator->setRail(acRelayPower);
            aerator->setReservoir(feedReservoir);
        }
        #endif
        #if SETUP_FEED_PUMP_PIN >= 0
        {   auto feedPump = hydroController.addWaterPumpRelay(SETUP_FEED_PUMP_PIN);
            feedPump->setRail(acRelayPower);
            feedPump->setReservoir(feedReservoir);
            #if SETUP_FLOW_RATE_SENSOR_PIN >= 0
                feedPump->setFlowRateSensor(HydroponicsIdentity(Hydroponics_SensorType_WaterPumpFlowSensor, 1)); // delayed ref (auto-resolves on launch)
            #endif
            if (hydroController.getSystemMode() == Hydroponics_SystemMode_DrainToWaste) {
                feedPump->setOutputReservoir(drainagePipe);
            } else {
                feedPump->setOutputReservoir(feedReservoir);
            }
            // TODO: set ballpark continuous pump rate based on pump size branding
        }
        #endif
        #if SETUP_WATER_HEATER_PIN >= 0
        {   auto heater = hydroController.addWaterHeaterRelay(SETUP_WATER_HEATER_PIN);
            heater->setRail(acRelayPower);
            heater->setReservoir(feedReservoir);
        }
        #endif
        #if SETUP_WATER_SPRAYER_PIN >= 0
        {   auto sprayer = hydroController.addWaterSprayerRelay(SETUP_WATER_SPRAYER_PIN);
            sprayer->setRail(acRelayPower);
            sprayer->setReservoir(feedReservoir);
        }
        #endif
        #if SETUP_FAN_EXHAUST_PIN >= 0
        if (checkPinIsPWMOutput(SETUP_FAN_EXHAUST_PIN)) {
            auto fanExhaust = hydroController.addAnalogPWMFanExhaust(SETUP_FAN_EXHAUST_PIN, SETUP_USE_ANALOG_BITRES);
            fanExhaust->setRail(dcRelayPower);          // PWM fans use DC relay
            fanExhaust->setReservoir(feedReservoir);
        } else {
            auto fanExhaust = hydroController.addFanExhaustRelay(SETUP_FAN_EXHAUST_PIN);
            fanExhaust->setRail(acRelayPower);
            fanExhaust->setReservoir(feedReservoir);
        }
        #endif

        // DC-Based Peristaltic Pumps
        #if SETUP_NUTRIENT_MIX_PIN >= 0
        {   auto nutrientMix = hydroController.addFluidReservoir(Hydroponics_ReservoirType_NutrientPremix, 1, true);
            auto nutrientPump = hydroController.addPeristalticPumpRelay(SETUP_NUTRIENT_MIX_PIN);
            nutrientPump->setRail(dcRelayPower);
            nutrientPump->setReservoir(nutrientMix);
            nutrientPump->setOutputReservoir(feedReservoir);
            // TODO: set ballpark continuous peristaltic pump rate
        }
        #endif
        #if SETUP_FRESH_WATER_PIN >= 0
        {   auto freshWater = hydroController.addFluidReservoir(Hydroponics_ReservoirType_FreshWater, 1, true);
            auto dilutionPump = hydroController.addPeristalticPumpRelay(SETUP_NUTRIENT_MIX_PIN);
            dilutionPump->setRail(dcRelayPower);
            dilutionPump->setReservoir(freshWater);
            dilutionPump->setOutputReservoir(feedReservoir);
            // TODO: set ballpark continuous peristaltic pump rate
        }
        #endif
        #if SETUP_PH_UP_PIN >= 0
        {   auto phUpSolution = hydroController.addFluidReservoir(Hydroponics_ReservoirType_PhUpSolution, 1, true);
            auto pHUpPump = hydroController.addPeristalticPumpRelay(SETUP_NUTRIENT_MIX_PIN);
            pHUpPump->setRail(dcRelayPower);
            pHUpPump->setReservoir(phUpSolution);
            pHUpPump->setOutputReservoir(feedReservoir);
            // TODO: set ballpark continuous peristaltic pump rate
        }
        #endif
        #if SETUP_PH_DOWN_PIN >= 0
        {   auto phDownSolution = hydroController.addFluidReservoir(Hydroponics_ReservoirType_PhDownSolution, 1, true);
            auto pHDownPump = hydroController.addPeristalticPumpRelay(SETUP_NUTRIENT_MIX_PIN);
            pHDownPump->setRail(dcRelayPower);
            pHDownPump->setReservoir(phDownSolution);
            pHDownPump->setOutputReservoir(feedReservoir);
            // TODO: set ballpark continuous peristaltic pump rate
        }
        #endif

        {   auto cropType = JOIN(Hydroponics_CropType,SETUP_CROP1_TYPE);
            if (cropType != Hydroponics_CropType_Undefined) {
                #if SETUP_CROP1_SOILM_PIN >= 0
                    auto moistureSensor = hydroController.addAnalogMoistureSensor(SETUP_CROP1_SOILM_PIN, SETUP_USE_ANALOG_BITRES);
                    auto crop = hydroController.addAdaptiveFedCrop(JOIN(Hydroponics_CropType,SETUP_CROP1_TYPE),
                                                                   JOIN(Hydroponics_SubstrateType,SETUP_CROP1_SUBSTRATE),
                                                                   SETUP_CROP1_SOW_DATE);
                    moistureSensor->setCrop(crop);
                    crop->setMoistureSensor(moistureSensor);
                #else
                    auto crop = hydroController.addTimerFedCrop(JOIN(Hydroponics_CropType,SETUP_CROP1_TYPE),
                                                                JOIN(Hydroponics_SubstrateType,SETUP_CROP1_SUBSTRATE),
                                                                SETUP_CROP1_SOW_DATE,
                                                                SETUP_CROP_ON_TIME,
                                                                SETUP_CROP_OFF_TIME);
                    crop->setFeedReservoir(feedReservoir);
                #endif
            }
        }
        {   auto cropType = JOIN(Hydroponics_CropType,SETUP_CROP2_TYPE);
            if (cropType != Hydroponics_CropType_Undefined) {
                #if SETUP_CROP2_SOILM_PIN >= 0
                    auto moistureSensor = hydroController.addAnalogMoistureSensor(SETUP_CROP2_SOILM_PIN, SETUP_USE_ANALOG_BITRES);
                    auto crop = hydroController.addAdaptiveFedCrop(JOIN(Hydroponics_CropType,SETUP_CROP2_TYPE),
                                                                   JOIN(Hydroponics_SubstrateType,SETUP_CROP2_SUBSTRATE),
                                                                   SETUP_CROP2_SOW_DATE);
                    moistureSensor->setCrop(crop);
                    crop->setMoistureSensor(moistureSensor);
                #else
                    auto crop = hydroController.addTimerFedCrop(JOIN(Hydroponics_CropType,SETUP_CROP2_TYPE),
                                                                JOIN(Hydroponics_SubstrateType,SETUP_CROP2_SUBSTRATE),
                                                                SETUP_CROP2_SOW_DATE,
                                                                SETUP_CROP_ON_TIME,
                                                                SETUP_CROP_OFF_TIME);
                    crop->setFeedReservoir(feedReservoir);
                #endif
            }
        }
        {   auto cropType = JOIN(Hydroponics_CropType,SETUP_CROP3_TYPE);
            if (cropType != Hydroponics_CropType_Undefined) {
                #if SETUP_CROP3_SOILM_PIN >= 0
                    auto moistureSensor = hydroController.addAnalogMoistureSensor(SETUP_CROP3_SOILM_PIN, SETUP_USE_ANALOG_BITRES);
                    auto crop = hydroController.addAdaptiveFedCrop(JOIN(Hydroponics_CropType,SETUP_CROP3_TYPE),
                                                                   JOIN(Hydroponics_SubstrateType,SETUP_CROP3_SUBSTRATE),
                                                                   SETUP_CROP3_SOW_DATE);
                    moistureSensor->setCrop(crop);
                    crop->setMoistureSensor(moistureSensor);
                #else
                    auto crop = hydroController.addTimerFedCrop(JOIN(Hydroponics_CropType,SETUP_CROP3_TYPE),
                                                                JOIN(Hydroponics_SubstrateType,SETUP_CROP3_SUBSTRATE),
                                                                SETUP_CROP3_SOW_DATE,
                                                                SETUP_CROP_ON_TIME,
                                                                SETUP_CROP_OFF_TIME);
                    crop->setFeedReservoir(feedReservoir);
                #endif
            }
        }
        {   auto cropType = JOIN(Hydroponics_CropType,SETUP_CROP4_TYPE);
            if (cropType != Hydroponics_CropType_Undefined) {
                #if SETUP_CROP4_SOILM_PIN >= 0
                    auto moistureSensor = hydroController.addAnalogMoistureSensor(SETUP_CROP4_SOILM_PIN, SETUP_USE_ANALOG_BITRES);
                    auto crop = hydroController.addAdaptiveFedCrop(JOIN(Hydroponics_CropType,SETUP_CROP4_TYPE),
                                                                   JOIN(Hydroponics_SubstrateType,SETUP_CROP4_SUBSTRATE),
                                                                   SETUP_CROP4_SOW_DATE);
                    moistureSensor->setCrop(crop);
                    crop->setMoistureSensor(moistureSensor);
                #else
                    auto crop = hydroController.addTimerFedCrop(JOIN(Hydroponics_CropType,SETUP_CROP4_TYPE),
                                                                JOIN(Hydroponics_SubstrateType,SETUP_CROP4_SUBSTRATE),
                                                                SETUP_CROP4_SOW_DATE,
                                                                SETUP_CROP_ON_TIME,
                                                                SETUP_CROP_OFF_TIME);
                    crop->setFeedReservoir(feedReservoir);
                #endif
            }
        }
        {   auto cropType = JOIN(Hydroponics_CropType,SETUP_CROP5_TYPE);
            if (cropType != Hydroponics_CropType_Undefined) {
                #if SETUP_CROP5_SOILM_PIN >= 0
                    auto moistureSensor = hydroController.addAnalogMoistureSensor(SETUP_CROP5_SOILM_PIN, SETUP_USE_ANALOG_BITRES);
                    auto crop = hydroController.addAdaptiveFedCrop(JOIN(Hydroponics_CropType,SETUP_CROP5_TYPE),
                                                                   JOIN(Hydroponics_SubstrateType,SETUP_CROP5_SUBSTRATE),
                                                                   SETUP_CROP5_SOW_DATE);
                    moistureSensor->setCrop(crop);
                    crop->setMoistureSensor(moistureSensor);
                #else
                    auto crop = hydroController.addTimerFedCrop(JOIN(Hydroponics_CropType,SETUP_CROP5_TYPE),
                                                                JOIN(Hydroponics_SubstrateType,SETUP_CROP5_SUBSTRATE),
                                                                SETUP_CROP5_SOW_DATE,
                                                                SETUP_CROP_ON_TIME,
                                                                SETUP_CROP_OFF_TIME);
                    crop->setFeedReservoir(feedReservoir);
                #endif
            }
        }
    }

    // TODO: UI initialization, other setup options

    // Launches controller into main operation.
    hydroController.launch();
}

void loop()
{
    // Hydruino will manage most updates for us.
    hydroController.update();
}
