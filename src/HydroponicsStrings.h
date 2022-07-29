/*  Hydruino: Simple automation controller for hydroponic grow systems.
    Copyright (C) 2022 NachtRaveVL          <nachtravevl@gmail.com>
    Hydroponics Strings
*/

#ifndef HydroponicsStrings_H
#define HydroponicsStrings_H

// Strings Enumeration Table
enum Hydroponics_String {
    HStr_ColonSpace,
    HStr_Count,
    HStr_DoubleSpace,
    HStr_csv,
    HStr_dat,
    HStr_Disabled,
    HStr_txt,
    HStr_Undefined,
    HStr_null,

    HStr_Err_AllocationFailure,
    HStr_Err_AlreadyInitialized,
    HStr_Err_AssertionFailure,
    HStr_Err_ExportFailure,
    HStr_Err_ImportFailure,
    HStr_Err_InitializationFailure,
    HStr_Err_InvalidParameter,
    HStr_Err_InvalidPinOrType,
    HStr_Err_MeasurementFailure,
    HStr_Err_MissingLinkage,
    HStr_Err_NoPositionsAvailable,
    HStr_Err_NotYetInitialized,
    HStr_Err_OperationFailure,
    HStr_Err_UnsupportedOperation,

    HStr_Log_AirReport,
    HStr_Log_CalculatedPumping,
    HStr_Log_FeedingSequence,
    HStr_Log_HasBegan,
    HStr_Log_HasDisabled,
    HStr_Log_HasEnabled,
    HStr_Log_HasEnded,
    HStr_Log_LightingSequence,
    HStr_Log_MeasuredPumping,
    HStr_Log_PreFeedBalancing,
    HStr_Log_PreFeedTopOff,
    HStr_Log_PreLightSpraying,
    HStr_Log_SystemDataSaved,
    HStr_Log_SystemUptime,

    HStr_Log_Field_pH_Setpoint,
    HStr_Log_Field_TDS_Setpoint,
    HStr_Log_Field_Temp_Setpoint,
    HStr_Log_Field_CO2_Setpoint,
    HStr_Log_Field_Time_Calculated,
    HStr_Log_Field_Vol_Calculated,
    HStr_Log_Field_pH_Measured,
    HStr_Log_Field_TDS_Measured,
    HStr_Log_Field_Temp_Measured,
    HStr_Log_Field_CO2_Measured,
    HStr_Log_Field_Time_Measured,
    HStr_Log_Field_Vol_Measured,
    HStr_Log_Field_Time_Start,
    HStr_Log_Field_Time_Finish,

    HStr_Key_ActiveLow,
    HStr_Key_AdditiveName,
    HStr_Key_AirReportInterval,
    HStr_Key_AirTempRange,
    HStr_Key_AirTemperatureSensor,
    HStr_Key_AlwaysFilled,
    HStr_Key_AutosaveEnabled,
    HStr_Key_AutosaveInterval,
    HStr_Key_BaseFeedMultiplier,
    HStr_Key_CO2Levels,
    HStr_Key_CO2Sensor,
    HStr_Key_CalibUnits,
    HStr_Key_ComputeHeatIndex,
    HStr_Key_ContFlowRate,
    HStr_Key_ContPowerUsage,
    HStr_Key_CropName,
    HStr_Key_CropType,
    HStr_Key_CtrlInMode,
    HStr_Key_DHTType,
    HStr_Key_DailyLightHours,
    HStr_Key_DataFilePrefix,
    HStr_Key_DetriggerTol,
    HStr_Key_DispOutMode,
    HStr_Key_EmptyTrigger,
    HStr_Key_FeedReservoir,
    HStr_Key_FeedTimingMins,
    HStr_Key_FeedingTrigger,
    HStr_Key_FeedingWeight,
    HStr_Key_FilledTrigger,
    HStr_Key_Flags,
    HStr_Key_FlowRateSensor,
    HStr_Key_FlowRateUnits,
    HStr_Key_Id,
    HStr_Key_InputBitRes,
    HStr_Key_InputInversion,
    HStr_Key_InputPin,
    HStr_Key_Invasive,
    HStr_Key_Large,
    HStr_Key_LastChangeDate,
    HStr_Key_LastFeedingDate,
    HStr_Key_LastPruningDate,
    HStr_Key_LifeCycleWeeks,
    HStr_Key_LimitTrigger,
    HStr_Key_LogFilePrefix,
    HStr_Key_LogLevel,
    HStr_Key_LogToSDCard,
    HStr_Key_Logger,
    HStr_Key_MaxActiveAtOnce,
    HStr_Key_MaxPower,
    HStr_Key_MaxVolume,
    HStr_Key_MeasureMode,
    HStr_Key_MeasurementRow,
    HStr_Key_MeasurementUnits,
    HStr_Key_MoistureSensor,
    HStr_Key_MoistureUnits,
    HStr_Key_Multiplier,
    HStr_Key_NightlyFeedRate,
    HStr_Key_NumFeedingsToday,
    HStr_Key_Offset,
    HStr_Key_OutputBitRes,
    HStr_Key_OutputPin,
    HStr_Key_OutputReservoir,
    HStr_Key_PHRange,
    HStr_Key_PHSensor,
    HStr_Key_Perennial,
    HStr_Key_PhaseDurationWeeks,
    HStr_Key_PollingInterval,
    HStr_Key_PowerSensor,
    HStr_Key_PowerUnits,
    HStr_Key_PreFeedAeratorMins,
    HStr_Key_PreLightSprayMins,
    HStr_Key_Pruning,
    HStr_Key_PublishToSDCard,
    HStr_Key_Publisher,
    HStr_Key_PullupPin,
    HStr_Key_RailName,
    HStr_Key_ReservoirName,
    HStr_Key_ReservoirType,
    HStr_Key_Revision,
    HStr_Key_Scheduler,
    HStr_Key_SensorName,
    HStr_Key_SowDate,
    HStr_Key_Spraying,
    HStr_Key_State,
    HStr_Key_StdDosingRates,
    HStr_Key_SubstrateType,
    HStr_Key_SystemMode,
    HStr_Key_SystemName,
    HStr_Key_TDSRange,
    HStr_Key_TDSSensor,
    HStr_Key_TDSUnits,
    HStr_Key_TemperatureSensor,
    HStr_Key_TempUnits,
    HStr_Key_TimeZoneOffset,
    HStr_Key_Timestamp,
    HStr_Key_ToleranceHigh,
    HStr_Key_ToleranceLow,
    HStr_Key_ToleranceUnits,
    HStr_Key_Tolerance,
    HStr_Key_TotalFeedingsDay,
    HStr_Key_TotalGrowWeeks,
    HStr_Key_Toxic,
    HStr_Key_TriggerBelow,
    HStr_Key_TriggerOutside,
    HStr_Key_Type,
    HStr_Key_Units,
    HStr_Key_UsingISR,
    HStr_Key_Value,
    HStr_Key_Version,
    HStr_Key_Viner,
    HStr_Key_VolumeSensor,
    HStr_Key_VolumeUnits,
    HStr_Key_WaterTemperatureRange,
    HStr_Key_WaterTemperatureSensor,
    HStr_Key_WeeklyDosingRates,
    HStr_Key_WiFiPasswordSeed,
    HStr_Key_WiFiPassword,
    HStr_Key_WiFiSSID,
    HStr_Key_WireDevAddress,
    HStr_Key_WirePosIndex,

    Hydroponics_Strings_Count
};

// Returns memory resident string from PROGMEM (Flash) string enumeration.
extern String stringFromPGM(Hydroponics_String strNum);
#define SFP(strNum) stringFromPGM((strNum))

// Makes Strings lookup go through EEPROM, with specified data begin address.
extern void beginStringsFromEEPROM(uint16_t dataAddress);

// Makes Strings lookup go through SD Card strings file at file prefix.
extern void beginStringsFromSDCard(String dataFilePrefix);

#endif // /ifndef HydroponicsStrings_H
