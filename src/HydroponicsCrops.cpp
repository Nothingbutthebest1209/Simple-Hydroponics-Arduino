/*  Arduino Controller for Simple Hydroponics.
    Copyright (C) 2022 NachtRaveVL          <nachtravevl@gmail.com>
    Hydroponics Crops
*/

#include "HydroponicsCrops.h"

static bool _cropLibraryBuilt = false;

HydroponicsCropData::HydroponicsCropData()
    : _ident({'H','C','D'}), _version(1),
      cropType(Hydroponics_CropType_Undefined), plantName({'\0'}),
      growWeeksToHarvest(0), weeksBetweenHarvest(0),
      phaseBeginWeek({0}), lightHoursPerDay({0}),
      isInvasiveOrViner(false), isLargePlant(false), isPerennial(false),
      isPrunningRequired(false), isToxicToPets(false)
{
    memset(feedIntervalMins, 0, sizeof(feedIntervalMins));
    memset(phRange, 0, sizeof(phRange));
    memset(ecRange, 0, sizeof(ecRange));
    memset(waterTempRange, 0, sizeof(waterTempRange));
    memset(airTempRange, 0, sizeof(airTempRange));
}

HydroponicsCropData::HydroponicsCropData(const Hydroponics_CropType cropTypeIn)
    : _ident({'H','C','D'}), _version(1),
      cropType(cropTypeIn), plantName({'\0'}),
      growWeeksToHarvest(0), weeksBetweenHarvest(0),
      phaseBeginWeek({0}), lightHoursPerDay({0}),
      isInvasiveOrViner(false), isLargePlant(false), isPerennial(false),
      isPrunningRequired(false), isToxicToPets(false)
{
    memset(feedIntervalMins, 0, sizeof(feedIntervalMins));
    memset(phRange, 0, sizeof(phRange));
    memset(ecRange, 0, sizeof(ecRange));
    memset(waterTempRange, 0, sizeof(waterTempRange));
    memset(airTempRange, 0, sizeof(airTempRange));

    if (_cropLibraryBuilt) {
        *this = *(HydroponicsCropsLibrary::getInstance()->getCropData(this->cropType));
    }
}


HydroponicsCropsLibrary::HydroponicsCropsLibrary()
{
    buildLibrary();
}

HydroponicsCropsLibrary *HydroponicsCropsLibrary::getInstance()
{
    static HydroponicsCropsLibrary *_instance = new HydroponicsCropsLibrary();
    return _instance;
}

void HydroponicsCropsLibrary::buildLibrary()
{   
    _cropLibraryBuilt = false;

    {   HydroponicsCropData cropData(Hydroponics_CropType_AloeVera);
        strncpy(&cropData.plantName[0], "Aloe Vera", HYDRO_NAME_MAXSIZE);
        cropData.phRange[0][0] = 7.0; cropData.phRange[0][1] = 8.5;
        cropData.ecRange[0][0] = 1.8; cropData.ecRange[0][1] = 2.5;
        cropData.isPerennial = true;
        cropData.isToxicToPets = true;
        _cropData[Hydroponics_CropType_AloeVera] = cropData;
    }

    {   HydroponicsCropData cropData(Hydroponics_CropType_Anise);
        strncpy(&cropData.plantName[0], "Anise", HYDRO_NAME_MAXSIZE);
        cropData.phRange[0][0] = 5.8; cropData.phRange[0][1] = 6.4;
        cropData.ecRange[0][0] = 0.9; cropData.ecRange[0][1] = 1.4;
        _cropData[Hydroponics_CropType_Anise] = cropData;
    }

    {   HydroponicsCropData cropData(Hydroponics_CropType_Artichoke);
        strncpy(&cropData.plantName[0], "Artichoke", HYDRO_NAME_MAXSIZE);
        cropData.phRange[0][0] = 6.5; cropData.phRange[0][1] = 7.5;
        cropData.ecRange[0][0] = 0.8; cropData.ecRange[0][1] = 1.8;
        cropData.isPerennial = true;
        _cropData[Hydroponics_CropType_Artichoke] = cropData;
    }

    {   HydroponicsCropData cropData(Hydroponics_CropType_Arugula);
        strncpy(&cropData.plantName[0], "Arugula", HYDRO_NAME_MAXSIZE);
        cropData.phRange[0][0] = 6.0; cropData.phRange[0][1] = 7.5;
        cropData.ecRange[0][0] = 0.8; cropData.ecRange[0][1] = 1.8;
        _cropData[Hydroponics_CropType_Arugula] = cropData;
    }

    {   HydroponicsCropData cropData(Hydroponics_CropType_Asparagus);
        strncpy(&cropData.plantName[0], "Asparagus", HYDRO_NAME_MAXSIZE);
        cropData.phRange[0][0] = 6.0; cropData.phRange[0][1] = 6.8;
        cropData.ecRange[0][0] = 1.4; cropData.ecRange[0][1] = 1.8;
        cropData.isPerennial = true;
        _cropData[Hydroponics_CropType_Asparagus] = cropData;
    }

    {   HydroponicsCropData cropData(Hydroponics_CropType_Basil);
        strncpy(&cropData.plantName[0], "Basil", HYDRO_NAME_MAXSIZE);
        cropData.phRange[0][0] = 5.5; cropData.phRange[0][1] = 6.5;
        cropData.ecRange[0][0] = 1.0; cropData.ecRange[0][1] = 1.6;
        _cropData[Hydroponics_CropType_Basil] = cropData;
    }

    {   HydroponicsCropData cropData(Hydroponics_CropType_Bean);
        strncpy(&cropData.plantName[0], "Bean (common)", HYDRO_NAME_MAXSIZE);
        cropData.phRange[0][0] = 6.0;
        cropData.ecRange[0][0] = 1.8; cropData.ecRange[0][1] = 2.4; // alt: 2.0-4.0
        _cropData[Hydroponics_CropType_Bean] = cropData;
    }

    {   HydroponicsCropData cropData(Hydroponics_CropType_BeanBroad);
        strncpy(&cropData.plantName[0], "Bean (broad)", HYDRO_NAME_MAXSIZE);
        cropData.phRange[0][0] = 6.0; cropData.phRange[0][1] = 6.5;
        cropData.ecRange[0][0] = 1.8; cropData.ecRange[0][1] = 2.4; // alt: 1.8-2.2
        _cropData[Hydroponics_CropType_BeanBroad] = cropData;
    }

    {   HydroponicsCropData cropData(Hydroponics_CropType_Beetroot);
        strncpy(&cropData.plantName[0], "Beetroot", HYDRO_NAME_MAXSIZE);
        cropData.phRange[0][0] = 6.0; cropData.phRange[0][1] = 6.5;
        cropData.ecRange[0][0] = 0.8; cropData.ecRange[0][1] = 5.0;
        _cropData[Hydroponics_CropType_Beetroot] = cropData;
    }

    {   HydroponicsCropData cropData(Hydroponics_CropType_BlackCurrant);
        strncpy(&cropData.plantName[0], "Black Currant", HYDRO_NAME_MAXSIZE);
        cropData.phRange[0][0] = 6.0;
        cropData.ecRange[0][0] = 1.4; cropData.ecRange[0][1] = 1.8;
        _cropData[Hydroponics_CropType_BlackCurrant] = cropData;
    }

    {   HydroponicsCropData cropData(Hydroponics_CropType_Blueberry);
        strncpy(&cropData.plantName[0], "Blueberry", HYDRO_NAME_MAXSIZE);
        cropData.phRange[0][0] = 4.0; cropData.phRange[0][1] = 5.0;
        cropData.ecRange[0][0] = 1.8; cropData.ecRange[0][1] = 2.0;
        cropData.isPerennial = true;
        _cropData[Hydroponics_CropType_Blueberry] = cropData;
    }

    {   HydroponicsCropData cropData(Hydroponics_CropType_BokChoi);
        strncpy(&cropData.plantName[0], "Bok-choi", HYDRO_NAME_MAXSIZE);
        cropData.phRange[0][0] = 6.0; cropData.phRange[0][1] = 7.0;
        cropData.ecRange[0][0] = 1.5; cropData.ecRange[0][1] = 2.5;
        _cropData[Hydroponics_CropType_BokChoi] = cropData;
    }

    {   HydroponicsCropData cropData(Hydroponics_CropType_Broccoli);
        strncpy(&cropData.plantName[0], "Broccoli", HYDRO_NAME_MAXSIZE);
        cropData.phRange[0][0] = 6.0; cropData.phRange[0][1] = 6.5;
        cropData.ecRange[0][0] = 2.8; cropData.ecRange[0][1] = 3.5;
        _cropData[Hydroponics_CropType_Broccoli] = cropData;
    }

    {   HydroponicsCropData cropData(Hydroponics_CropType_BrussellSprouts);
        strncpy(&cropData.plantName[0], "Brussell Sprouts", HYDRO_NAME_MAXSIZE);
        cropData.phRange[0][0] = 6.5; cropData.phRange[0][1] = 7.5;
        cropData.ecRange[0][0] = 2.5; cropData.ecRange[0][1] = 3.0;
        _cropData[Hydroponics_CropType_BrussellSprouts] = cropData;
    }

    {   HydroponicsCropData cropData(Hydroponics_CropType_Cabbage);
        strncpy(&cropData.plantName[0], "Cabbage", HYDRO_NAME_MAXSIZE);
        cropData.phRange[0][0] = 6.5; cropData.phRange[0][1] = 7.0;
        cropData.ecRange[0][0] = 2.5; cropData.ecRange[0][1] = 3.0;
        _cropData[Hydroponics_CropType_Cabbage] = cropData;
    }

    {   HydroponicsCropData cropData(Hydroponics_CropType_Cannabis);
        strncpy(&cropData.plantName[0], "Cannabis (generic)", HYDRO_NAME_MAXSIZE);
        cropData.phRange[0][0] = 5.5; cropData.phRange[0][1] = 6.1;
        cropData.ecRange[0][0] = 1.0; cropData.ecRange[0][1] = 2.5;
        cropData.isLargePlant = true;
        _cropData[Hydroponics_CropType_Cannabis] = cropData;
    }

    {   HydroponicsCropData cropData(Hydroponics_CropType_Capiscum);
        strncpy(&cropData.plantName[0], "Capiscum", HYDRO_NAME_MAXSIZE);
        cropData.phRange[0][0] = 6.0; cropData.phRange[0][1] = 6.5;
        cropData.ecRange[0][0] = 1.8; cropData.ecRange[0][1] = 2.2;
        _cropData[Hydroponics_CropType_Capiscum] = cropData;
    }

    {   HydroponicsCropData cropData(Hydroponics_CropType_Carrots);
        strncpy(&cropData.plantName[0], "Carrots", HYDRO_NAME_MAXSIZE);
        cropData.phRange[0][0] = 6.3;
        cropData.ecRange[0][0] = 1.6; cropData.ecRange[0][1] = 2.0;
        _cropData[Hydroponics_CropType_Carrots] = cropData;
    }

    {   HydroponicsCropData cropData(Hydroponics_CropType_Catnip);
        strncpy(&cropData.plantName[0], "Catnip", HYDRO_NAME_MAXSIZE);
        cropData.phRange[0][0] = 5.5; cropData.phRange[0][1] = 6.5;
        cropData.ecRange[0][0] = 1.0; cropData.ecRange[0][1] = 1.6;
        _cropData[Hydroponics_CropType_Catnip] = cropData;
    }

    {   HydroponicsCropData cropData(Hydroponics_CropType_Cauliflower);
        strncpy(&cropData.plantName[0], "Cauliflower", HYDRO_NAME_MAXSIZE);
        cropData.phRange[0][0] = 6.0; cropData.phRange[0][1] = 7.0;
        cropData.ecRange[0][0] = 0.5; cropData.ecRange[0][1] = 2.0;
        _cropData[Hydroponics_CropType_Cauliflower] = cropData;
    }

    {   HydroponicsCropData cropData(Hydroponics_CropType_Celery);
        strncpy(&cropData.plantName[0], "Celery", HYDRO_NAME_MAXSIZE);
        cropData.phRange[0][0] = 6.3; cropData.phRange[0][1] = 6.7; // alt: 6.5
        cropData.ecRange[0][0] = 1.8; cropData.ecRange[0][1] = 2.4;
        _cropData[Hydroponics_CropType_Celery] = cropData;
    }

    {   HydroponicsCropData cropData(Hydroponics_CropType_Chamomile);
        strncpy(&cropData.plantName[0], "Chamomile", HYDRO_NAME_MAXSIZE);
        cropData.phRange[0][0] = 5.5; cropData.phRange[0][1] = 6.5;
        cropData.ecRange[0][0] = 1.0; cropData.ecRange[0][1] = 1.6;
        cropData.isToxicToPets = true;
        _cropData[Hydroponics_CropType_Chamomile] = cropData;
    }

    {   HydroponicsCropData cropData(Hydroponics_CropType_Chickory);
        strncpy(&cropData.plantName[0], "Chickory", HYDRO_NAME_MAXSIZE);
        cropData.phRange[0][0] = 5.5; cropData.phRange[0][1] = 6.0;
        cropData.ecRange[0][0] = 2.0; cropData.ecRange[0][1] = 2.4;
        _cropData[Hydroponics_CropType_Chickory] = cropData;
    }

    {   HydroponicsCropData cropData(Hydroponics_CropType_Chives);
        strncpy(&cropData.plantName[0], "Chives", HYDRO_NAME_MAXSIZE);
        cropData.phRange[0][0] = 6.0; cropData.phRange[0][1] = 6.5;
        cropData.ecRange[0][0] = 1.8; cropData.ecRange[0][1] = 2.4;
        cropData.isPerennial = true;
        cropData.isToxicToPets = true;
        _cropData[Hydroponics_CropType_Chives] = cropData;
    }

    {   HydroponicsCropData cropData(Hydroponics_CropType_Cilantro);
        strncpy(&cropData.plantName[0], "Cilantro", HYDRO_NAME_MAXSIZE);
        cropData.phRange[0][0] = 6.5; cropData.phRange[0][1] = 6.7;
        cropData.ecRange[0][0] = 1.3; cropData.ecRange[0][1] = 1.8;
        _cropData[Hydroponics_CropType_Cilantro] = cropData;
    }

    {   HydroponicsCropData cropData(Hydroponics_CropType_Coriander);
        strncpy(&cropData.plantName[0], "Coriander", HYDRO_NAME_MAXSIZE);
        cropData.phRange[0][0] = 5.8; cropData.phRange[0][1] = 6.4;
        cropData.ecRange[0][0] = 1.2; cropData.ecRange[0][1] = 1.8;
        _cropData[Hydroponics_CropType_Coriander] = cropData;
    }

    {   HydroponicsCropData cropData(Hydroponics_CropType_CornSweet);
        strncpy(&cropData.plantName[0], "Corn (sweet)", HYDRO_NAME_MAXSIZE);
        cropData.phRange[0][0] = 6.0;
        cropData.ecRange[0][0] = 1.6; cropData.ecRange[0][1] = 2.4;
        cropData.isLargePlant = true;
        cropData.isToxicToPets = true;
        _cropData[Hydroponics_CropType_CornSweet] = cropData;
    }

    {   HydroponicsCropData cropData(Hydroponics_CropType_Cucumber);
        strncpy(&cropData.plantName[0], "Cucumber", HYDRO_NAME_MAXSIZE);
        cropData.phRange[0][0] = 5.8; cropData.phRange[0][1] = 6.0;
        cropData.ecRange[0][0] = 1.7; cropData.ecRange[0][1] = 2.5; // alt: 1.5-3.0
        _cropData[Hydroponics_CropType_Cucumber] = cropData;
    }

    {   HydroponicsCropData cropData(Hydroponics_CropType_Dill);
        strncpy(&cropData.plantName[0], "Dill", HYDRO_NAME_MAXSIZE);
        cropData.phRange[0][0] = 5.5; cropData.phRange[0][1] = 6.4;
        cropData.ecRange[0][0] = 1.0; cropData.ecRange[0][1] = 1.6;
        _cropData[Hydroponics_CropType_Dill] = cropData;
    }

    {   HydroponicsCropData cropData(Hydroponics_CropType_Eggplant);
        strncpy(&cropData.plantName[0], "Eggplant", HYDRO_NAME_MAXSIZE);
        cropData.phRange[0][0] = 5.5; cropData.phRange[0][1] = 6.5;
        cropData.ecRange[0][0] = 2.5; cropData.ecRange[0][1] = 3.5;
        _cropData[Hydroponics_CropType_Eggplant] = cropData;
    }

    {   HydroponicsCropData cropData(Hydroponics_CropType_Endive);
        strncpy(&cropData.plantName[0], "Endive", HYDRO_NAME_MAXSIZE);
        cropData.phRange[0][0] = 5.5;
        cropData.ecRange[0][0] = 2.0; cropData.ecRange[0][1] = 2.4;
        _cropData[Hydroponics_CropType_Endive] = cropData;
    }

    {   HydroponicsCropData cropData(Hydroponics_CropType_Fennel);
        strncpy(&cropData.plantName[0], "Fennel", HYDRO_NAME_MAXSIZE);
        cropData.phRange[0][0] = 6.4; cropData.phRange[0][1] = 6.8;
        cropData.ecRange[0][0] = 1.0; cropData.ecRange[0][1] = 1.4;
        cropData.isPerennial = true;
        _cropData[Hydroponics_CropType_Fennel] = cropData;
    }

    {   HydroponicsCropData cropData(Hydroponics_CropType_Fodder);
        strncpy(&cropData.plantName[0], "Fodder", HYDRO_NAME_MAXSIZE);
        cropData.phRange[0][0] = 6.0;
        cropData.ecRange[0][0] = 1.8; cropData.ecRange[0][1] = 2.0;
        _cropData[Hydroponics_CropType_Fodder] = cropData;
    }

    {   HydroponicsCropData cropData(Hydroponics_CropType_Flowers);
        strncpy(&cropData.plantName[0], "Flowers (generic)", HYDRO_NAME_MAXSIZE);
        cropData.phRange[0][0] = 5.5; cropData.phRange[0][1] = 6.5;
        cropData.ecRange[0][0] = 1.5; cropData.ecRange[0][1] = 2.5;
        cropData.isToxicToPets = true;
        _cropData[Hydroponics_CropType_Flowers] = cropData;
    }

    {   HydroponicsCropData cropData(Hydroponics_CropType_Garlic);
        strncpy(&cropData.plantName[0], "Garlic", HYDRO_NAME_MAXSIZE);
        cropData.phRange[0][0] = 6.0;
        cropData.ecRange[0][0] = 1.4; cropData.ecRange[0][1] = 1.8;
        cropData.isPerennial = true;
        cropData.isToxicToPets = true;
        _cropData[Hydroponics_CropType_Garlic] = cropData;
    }

    {   HydroponicsCropData cropData(Hydroponics_CropType_Ginger);
        strncpy(&cropData.plantName[0], "Ginger", HYDRO_NAME_MAXSIZE);
        cropData.phRange[0][0] = 5.8; cropData.phRange[0][1] = 6.0;
        cropData.ecRange[0][0] = 2.0; cropData.ecRange[0][1] = 2.5;
        _cropData[Hydroponics_CropType_Ginger] = cropData;
    }

    {   HydroponicsCropData cropData(Hydroponics_CropType_Kale);
        strncpy(&cropData.plantName[0], "Kale", HYDRO_NAME_MAXSIZE);
        cropData.phRange[0][0] = 5.5; cropData.phRange[0][1] = 6.5;
        cropData.ecRange[0][0] = 1.25; cropData.ecRange[0][1] = 1.5;
        cropData.isPerennial = true;
        _cropData[Hydroponics_CropType_Kale] = cropData;
    }

    {   HydroponicsCropData cropData(Hydroponics_CropType_Lavender);
        strncpy(&cropData.plantName[0], "Lavender", HYDRO_NAME_MAXSIZE);
        cropData.phRange[0][0] = 6.4; cropData.phRange[0][1] = 6.8;
        cropData.ecRange[0][0] = 1.0; cropData.ecRange[0][1] = 1.4;
        cropData.isPerennial = true;
        cropData.isToxicToPets = true;
        _cropData[Hydroponics_CropType_Lavender] = cropData;
    }

    {   HydroponicsCropData cropData(Hydroponics_CropType_Leek);
        strncpy(&cropData.plantName[0], "Leek", HYDRO_NAME_MAXSIZE);
        cropData.phRange[0][0] = 6.5; cropData.phRange[0][1] = 7.0;
        cropData.ecRange[0][0] = 1.4; cropData.ecRange[0][1] = 1.8;
        cropData.isToxicToPets = true;
        _cropData[Hydroponics_CropType_Leek] = cropData;
    }

    {   HydroponicsCropData cropData(Hydroponics_CropType_LemonBalm);
        strncpy(&cropData.plantName[0], "LemonBalm", HYDRO_NAME_MAXSIZE);
        cropData.phRange[0][0] = 5.5; cropData.phRange[0][1] = 6.5;
        cropData.ecRange[0][0] = 1.0; cropData.ecRange[0][1] = 1.6;
        cropData.isPerennial = true;
        _cropData[Hydroponics_CropType_LemonBalm] = cropData;
    }

    {   HydroponicsCropData cropData(Hydroponics_CropType_Lettuce);
        strncpy(&cropData.plantName[0], "Lettuce", HYDRO_NAME_MAXSIZE);
        cropData.phRange[0][0] = 5.5; cropData.phRange[0][1] = 6.5;
        cropData.ecRange[0][0] = 0.8; cropData.ecRange[0][1] = 1.2;
        _cropData[Hydroponics_CropType_Lettuce] = cropData;
    }

    {   HydroponicsCropData cropData(Hydroponics_CropType_Marrow);
        strncpy(&cropData.plantName[0], "Marrow", HYDRO_NAME_MAXSIZE);
        cropData.phRange[0][0] = 6.0;
        cropData.ecRange[0][0] = 1.8; cropData.ecRange[0][1] = 2.4;
        _cropData[Hydroponics_CropType_Marrow] = cropData;
    }

    {   HydroponicsCropData cropData(Hydroponics_CropType_Melon);
        strncpy(&cropData.plantName[0], "Melon", HYDRO_NAME_MAXSIZE);
        cropData.phRange[0][0] = 5.5; cropData.phRange[0][1] = 6.0;
        cropData.ecRange[0][0] = 2.0; cropData.ecRange[0][1] = 2.5;
        cropData.isLargePlant = true;
        _cropData[Hydroponics_CropType_Melon] = cropData;
    }

    {   HydroponicsCropData cropData(Hydroponics_CropType_Mint);
        strncpy(&cropData.plantName[0], "Mint", HYDRO_NAME_MAXSIZE);
        cropData.phRange[0][0] = 5.5; cropData.phRange[0][1] = 6.0;
        cropData.ecRange[0][0] = 2.0; cropData.ecRange[0][1] = 2.4;
        cropData.isPerennial = true;
        cropData.isInvasiveOrViner = true;
        cropData.isToxicToPets = true;
        _cropData[Hydroponics_CropType_Mint] = cropData;
    }

    {   HydroponicsCropData cropData(Hydroponics_CropType_MustardCress);
        strncpy(&cropData.plantName[0], "Mustard Cress", HYDRO_NAME_MAXSIZE);
        cropData.phRange[0][0] = 6.0; cropData.phRange[0][1] = 6.5;
        cropData.ecRange[0][0] = 1.2; cropData.ecRange[0][1] = 2.4;
        _cropData[Hydroponics_CropType_MustardCress] = cropData;
    }

    {   HydroponicsCropData cropData(Hydroponics_CropType_Okra);
        strncpy(&cropData.plantName[0], "Okra", HYDRO_NAME_MAXSIZE);
        cropData.phRange[0][0] = 6.5;
        cropData.ecRange[0][0] = 2.0; cropData.ecRange[0][1] = 2.4;
        _cropData[Hydroponics_CropType_Okra] = cropData;
    }

    {   HydroponicsCropData cropData(Hydroponics_CropType_Onions);
        strncpy(&cropData.plantName[0], "Onions", HYDRO_NAME_MAXSIZE);
        cropData.phRange[0][0] = 6.0; cropData.phRange[0][1] = 6.7;
        cropData.ecRange[0][0] = 1.4; cropData.ecRange[0][1] = 1.8;
        cropData.isPerennial = true;
        cropData.isToxicToPets = true;
        _cropData[Hydroponics_CropType_Onions] = cropData;
    }

    {   HydroponicsCropData cropData(Hydroponics_CropType_Oregano);
        strncpy(&cropData.plantName[0], "Oregano", HYDRO_NAME_MAXSIZE);
        cropData.phRange[0][0] = 6.0; cropData.phRange[0][1] = 7.0;
        cropData.ecRange[0][0] = 1.8; cropData.ecRange[0][1] = 2.3;
        cropData.isPerennial = true;
        cropData.isToxicToPets = true;
        _cropData[Hydroponics_CropType_Oregano] = cropData;
    }

    {   HydroponicsCropData cropData(Hydroponics_CropType_PakChoi);
        strncpy(&cropData.plantName[0], "Pak-choi", HYDRO_NAME_MAXSIZE);
        cropData.phRange[0][0] = 7.0;
        cropData.ecRange[0][0] = 1.5; cropData.ecRange[0][1] = 2.0;
        _cropData[Hydroponics_CropType_PakChoi] = cropData;
    }

    {   HydroponicsCropData cropData(Hydroponics_CropType_Parsley);
        strncpy(&cropData.plantName[0], "Parsley", HYDRO_NAME_MAXSIZE);
        cropData.phRange[0][0] = 5.5; cropData.phRange[0][1] = 6.0;
        cropData.ecRange[0][0] = 0.8; cropData.ecRange[0][1] = 1.8;
        cropData.isPerennial = true;
        cropData.isToxicToPets = true;
        _cropData[Hydroponics_CropType_Parsley] = cropData;
    }

    {   HydroponicsCropData cropData(Hydroponics_CropType_Parsnip);
        strncpy(&cropData.plantName[0], "Parsnip", HYDRO_NAME_MAXSIZE);
        cropData.phRange[0][0] = 6.0;
        cropData.ecRange[0][0] = 1.4; cropData.ecRange[0][1] = 1.8;
        _cropData[Hydroponics_CropType_Parsnip] = cropData;
    }

    {   HydroponicsCropData cropData(Hydroponics_CropType_Pea);
        strncpy(&cropData.plantName[0], "Pea (common)", HYDRO_NAME_MAXSIZE);
        cropData.phRange[0][0] = 6.0; cropData.phRange[0][1] = 7.0;
        cropData.ecRange[0][0] = 0.8; cropData.ecRange[0][1] = 1.8;
        _cropData[Hydroponics_CropType_Pea] = cropData;
    }

    {   HydroponicsCropData cropData(Hydroponics_CropType_PeaSugar);
        strncpy(&cropData.plantName[0], "Pea (sugar)", HYDRO_NAME_MAXSIZE);
        cropData.phRange[0][0] = 6.0; cropData.phRange[0][1] = 6.8; // alt: 6.0-7.0
        cropData.ecRange[0][0] = 0.8; cropData.ecRange[0][1] = 1.9; // alt: 0.8-1.8
        cropData.isToxicToPets = true;
        _cropData[Hydroponics_CropType_PeaSugar] = cropData;
    }

    {   HydroponicsCropData cropData(Hydroponics_CropType_Pepino);
        strncpy(&cropData.plantName[0], "Pepino", HYDRO_NAME_MAXSIZE);
        cropData.phRange[0][0] = 6.0; cropData.phRange[0][1] = 6.5;
        cropData.ecRange[0][0] = 2.0; cropData.ecRange[0][1] = 5.0;
        _cropData[Hydroponics_CropType_Pepino] = cropData;
    }

    {   HydroponicsCropData cropData(Hydroponics_CropType_PeppersBell);
        strncpy(&cropData.plantName[0], "Peppers (bell)", HYDRO_NAME_MAXSIZE);
        cropData.phRange[0][0] = 6.0; cropData.phRange[0][1] = 6.5;
        cropData.ecRange[0][0] = 2.0; cropData.ecRange[0][1] = 2.5; // alt: 2.0-3.0
        _cropData[Hydroponics_CropType_PeppersBell] = cropData;
    }

    {   HydroponicsCropData cropData(Hydroponics_CropType_PeppersHot);
        strncpy(&cropData.plantName[0], "Peppers (hot)", HYDRO_NAME_MAXSIZE);
        cropData.phRange[0][0] = 6.0; cropData.phRange[0][1] = 6.5;
        cropData.ecRange[0][0] = 2.0; cropData.ecRange[0][1] = 3.5; // alt: 3.0-3.5
        _cropData[Hydroponics_CropType_PeppersHot] = cropData;
    }

    {   HydroponicsCropData cropData(Hydroponics_CropType_Potato);
        strncpy(&cropData.plantName[0], "Potato (common)", HYDRO_NAME_MAXSIZE);
        cropData.phRange[0][0] = 5.0; cropData.phRange[0][1] = 6.0;
        cropData.ecRange[0][0] = 2.0; cropData.ecRange[0][1] = 2.5;
        cropData.isPerennial = true;
        _cropData[Hydroponics_CropType_Potato] = cropData;
    }

    {   HydroponicsCropData cropData(Hydroponics_CropType_PotatoSweet);
        strncpy(&cropData.plantName[0], "Potato (sweet)", HYDRO_NAME_MAXSIZE);
        cropData.phRange[0][0] = 5.0; cropData.phRange[0][1] = 6.0;
        cropData.ecRange[0][0] = 2.0; cropData.ecRange[0][1] = 2.5;
        cropData.isPerennial = true;
        _cropData[Hydroponics_CropType_PotatoSweet] = cropData;
    }

    {   HydroponicsCropData cropData(Hydroponics_CropType_Pumpkin);
        strncpy(&cropData.plantName[0], "Pumpkin", HYDRO_NAME_MAXSIZE);
        cropData.phRange[0][0] = 5.5; cropData.phRange[0][1] = 7.5; // alt: 5.0-7.5
        cropData.ecRange[0][0] = 1.8; cropData.ecRange[0][1] = 2.4;
        cropData.isLargePlant = true;
        _cropData[Hydroponics_CropType_Pumpkin] = cropData;
    }

    {   HydroponicsCropData cropData(Hydroponics_CropType_Radish);
        strncpy(&cropData.plantName[0], "Radish", HYDRO_NAME_MAXSIZE);
        cropData.phRange[0][0] = 6.0; cropData.phRange[0][1] = 7.0;
        cropData.ecRange[0][0] = 1.6; cropData.ecRange[0][1] = 2.2;
        _cropData[Hydroponics_CropType_Radish] = cropData;
    }

    {   HydroponicsCropData cropData(Hydroponics_CropType_Rhubarb);
        strncpy(&cropData.plantName[0], "Rhubarb", HYDRO_NAME_MAXSIZE);
        cropData.phRange[0][0] = 5.0; cropData.phRange[0][1] = 6.0;
        cropData.ecRange[0][0] = 1.6; cropData.ecRange[0][1] = 2.0;
        cropData.isPerennial = true;
        cropData.isToxicToPets = true;
        _cropData[Hydroponics_CropType_Rhubarb] = cropData;
    }

    {   HydroponicsCropData cropData(Hydroponics_CropType_Rosemary);
        strncpy(&cropData.plantName[0], "Rosemary", HYDRO_NAME_MAXSIZE);
        cropData.phRange[0][0] = 5.5; cropData.phRange[0][1] = 6.0;
        cropData.ecRange[0][0] = 1.0; cropData.ecRange[0][1] = 1.6;
        cropData.isPerennial = true;
        _cropData[Hydroponics_CropType_Rosemary] = cropData;
    }

    {   HydroponicsCropData cropData(Hydroponics_CropType_Sage);
        strncpy(&cropData.plantName[0], "Sage", HYDRO_NAME_MAXSIZE);
        cropData.phRange[0][0] = 5.5; cropData.phRange[0][1] = 6.5;
        cropData.ecRange[0][0] = 1.0; cropData.ecRange[0][1] = 1.6;
        cropData.isPerennial = true;
        _cropData[Hydroponics_CropType_Sage] = cropData;
    }

    {   HydroponicsCropData cropData(Hydroponics_CropType_Silverbeet);
        strncpy(&cropData.plantName[0], "Silverbeet", HYDRO_NAME_MAXSIZE);
        cropData.phRange[0][0] = 6.0; cropData.phRange[0][1] = 7.0;
        cropData.ecRange[0][0] = 1.8; cropData.ecRange[0][1] = 2.3;
        _cropData[Hydroponics_CropType_Silverbeet] = cropData;
    }

    {   HydroponicsCropData cropData(Hydroponics_CropType_Spinach);
        strncpy(&cropData.plantName[0], "Spinach", HYDRO_NAME_MAXSIZE);
        cropData.phRange[0][0] = 5.5; cropData.phRange[0][1] = 6.6; // alt: 6.0-7.0
        cropData.ecRange[0][0] = 1.8; cropData.ecRange[0][1] = 2.3;
        _cropData[Hydroponics_CropType_Spinach] = cropData;
    }

    {   HydroponicsCropData cropData(Hydroponics_CropType_Squash);
        strncpy(&cropData.plantName[0], "Squash", HYDRO_NAME_MAXSIZE);
        cropData.phRange[0][0] = 5.0; cropData.phRange[0][1] = 6.5;
        cropData.ecRange[0][0] = 1.8; cropData.ecRange[0][1] = 2.4;
        cropData.isLargePlant = true;
        _cropData[Hydroponics_CropType_Squash] = cropData;
    }

    {   HydroponicsCropData cropData(Hydroponics_CropType_Sunflower);
        strncpy(&cropData.plantName[0], "Sunflower", HYDRO_NAME_MAXSIZE);
        cropData.phRange[0][0] = 5.5; cropData.phRange[0][1] = 6.5;
        cropData.ecRange[0][0] = 1.2; cropData.ecRange[0][1] = 1.8;
        _cropData[Hydroponics_CropType_Sunflower] = cropData;
    }

    {   HydroponicsCropData cropData(Hydroponics_CropType_Strawberries);
        strncpy(&cropData.plantName[0], "Strawberries", HYDRO_NAME_MAXSIZE);
        cropData.phRange[0][0] = 5.0; cropData.phRange[0][1] = 5.5;
        cropData.ecRange[0][0] = 1.0; cropData.ecRange[0][1] = 1.4;
        cropData.isPerennial = true;
        _cropData[Hydroponics_CropType_Strawberries] = cropData;
    }

    {   HydroponicsCropData cropData(Hydroponics_CropType_SwissChard);
        strncpy(&cropData.plantName[0], "Swiss Chard", HYDRO_NAME_MAXSIZE);
        cropData.phRange[0][0] = 6.0; cropData.phRange[0][1] = 6.5;
        cropData.ecRange[0][0] = 1.8; cropData.ecRange[0][1] = 2.3;
        _cropData[Hydroponics_CropType_SwissChard] = cropData;
    }

    {   HydroponicsCropData cropData(Hydroponics_CropType_Taro);
        strncpy(&cropData.plantName[0], "Taro", HYDRO_NAME_MAXSIZE);
        cropData.phRange[0][0] = 5.0; cropData.phRange[0][1] = 5.5;
        cropData.ecRange[0][0] = 2.5; cropData.ecRange[0][1] = 3.0;
        cropData.isToxicToPets = true;
        _cropData[Hydroponics_CropType_Taro] = cropData;
    }

    {   HydroponicsCropData cropData(Hydroponics_CropType_Tarragon);
        strncpy(&cropData.plantName[0], "Tarragon", HYDRO_NAME_MAXSIZE);
        cropData.phRange[0][0] = 5.5; cropData.phRange[0][1] = 6.5;
        cropData.ecRange[0][0] = 1.0; cropData.ecRange[0][1] = 1.8;
        cropData.isToxicToPets = true;
        _cropData[Hydroponics_CropType_Tarragon] = cropData;
    }

    {   HydroponicsCropData cropData(Hydroponics_CropType_Thyme);
        strncpy(&cropData.plantName[0], "Thyme", HYDRO_NAME_MAXSIZE);
        cropData.phRange[0][0] = 5.0; cropData.phRange[0][1] = 7.0;
        cropData.ecRange[0][0] = 0.8; cropData.ecRange[0][1] = 1.6;
        cropData.isPerennial = true;
        _cropData[Hydroponics_CropType_Thyme] = cropData;
    }

    {   HydroponicsCropData cropData(Hydroponics_CropType_Tomato);
        strncpy(&cropData.plantName[0], "Tomato", HYDRO_NAME_MAXSIZE);
        cropData.phRange[0][0] = 5.5; cropData.phRange[0][1] = 6.5; // alt: 5.5-6.0
        cropData.ecRange[0][0] = 2.0; cropData.ecRange[0][1] = 5.0;
        cropData.isToxicToPets = true;
        _cropData[Hydroponics_CropType_Tomato] = cropData;
    }

    {   HydroponicsCropData cropData(Hydroponics_CropType_Turnip);
        strncpy(&cropData.plantName[0], "Turnip", HYDRO_NAME_MAXSIZE);
        cropData.phRange[0][0] = 6.0; cropData.phRange[0][1] = 6.5;
        cropData.ecRange[0][0] = 1.8; cropData.ecRange[0][1] = 2.4;
        _cropData[Hydroponics_CropType_Turnip] = cropData;
    }

    {   HydroponicsCropData cropData(Hydroponics_CropType_Watercress);
        strncpy(&cropData.plantName[0], "Watercress", HYDRO_NAME_MAXSIZE);
        cropData.phRange[0][0] = 6.5; cropData.phRange[0][1] = 6.8;
        cropData.ecRange[0][0] = 0.4; cropData.ecRange[0][1] = 1.8;
        cropData.isPerennial = true;
        cropData.isToxicToPets = true;
        _cropData[Hydroponics_CropType_Watercress] = cropData;
    }

    {   HydroponicsCropData cropData(Hydroponics_CropType_Watermelon);
        strncpy(&cropData.plantName[0], "Watermelon (common)", HYDRO_NAME_MAXSIZE);
        cropData.phRange[0][0] = 5.8;
        cropData.ecRange[0][0] = 1.5; cropData.ecRange[0][1] = 2.4;
        cropData.isLargePlant = true;
        _cropData[Hydroponics_CropType_Watermelon] = cropData;
    }

    {   HydroponicsCropData cropData(Hydroponics_CropType_WatermelonBaby);
        strncpy(&cropData.plantName[0], "Watermelon (baby)", HYDRO_NAME_MAXSIZE);
        cropData.phRange[0][0] = 5.8;
        cropData.ecRange[0][0] = 1.5; cropData.ecRange[0][1] = 2.4;
        _cropData[Hydroponics_CropType_WatermelonBaby] = cropData;
    }

    {   HydroponicsCropData cropData(Hydroponics_CropType_Zucchini);
        strncpy(&cropData.plantName[0], "Zucchini", HYDRO_NAME_MAXSIZE);
        cropData.phRange[0][0] = 6.0;
        cropData.ecRange[0][0] = 1.8; cropData.ecRange[0][1] = 2.4;
        cropData.isLargePlant = true;
        _cropData[Hydroponics_CropType_Zucchini] = cropData;
    }

    validateEntries();

    _cropLibraryBuilt = true;
}

void HydroponicsCropsLibrary::validateEntries()
{
    for (Hydroponics_CropType cropTypeIndex = (Hydroponics_CropType)0; cropTypeIndex < Hydroponics_CropType_Count; cropTypeIndex = (Hydroponics_CropType)((int)cropTypeIndex + 1)) {
        Hydroponics_CropPhase cropPhaseIndex;

        // Ensure phase begin week is increasing
        for(cropPhaseIndex = (Hydroponics_CropPhase)1; cropPhaseIndex < Hydroponics_CropPhase_Count; cropPhaseIndex = (Hydroponics_CropPhase)((int)cropPhaseIndex + 1)) {
            if (_cropData[cropTypeIndex].phaseBeginWeek[cropPhaseIndex] <= _cropData[cropTypeIndex].phaseBeginWeek[cropPhaseIndex-1]) {
                _cropData[cropTypeIndex].phaseBeginWeek[cropPhaseIndex] = _cropData[cropTypeIndex].phaseBeginWeek[cropPhaseIndex-1] + 1;
            }
        }

        // Check for empty pH/EC second value entries
        for(cropPhaseIndex = (Hydroponics_CropPhase)0; cropPhaseIndex < Hydroponics_CropPhase_Count; cropPhaseIndex = (Hydroponics_CropPhase)((int)cropPhaseIndex + 1)) {
            if (_cropData[cropTypeIndex].phRange[cropPhaseIndex][0] > 0 &&
                _cropData[cropTypeIndex].phRange[cropPhaseIndex][1] == 0) {
                _cropData[cropTypeIndex].phRange[cropPhaseIndex][1] = _cropData[cropTypeIndex].phRange[cropPhaseIndex][0];
            }

            if (_cropData[cropTypeIndex].ecRange[cropPhaseIndex][0] > 0 &&
                _cropData[cropTypeIndex].ecRange[cropPhaseIndex][1] == 0) {
                _cropData[cropTypeIndex].ecRange[cropPhaseIndex][1] = _cropData[cropTypeIndex].ecRange[cropPhaseIndex][0];
            }
        }

        // Advance previous phase entries if later phase is empty
        for(cropPhaseIndex = (Hydroponics_CropPhase)1; cropPhaseIndex < Hydroponics_CropPhase_Count; cropPhaseIndex = (Hydroponics_CropPhase)((int)cropPhaseIndex + 1)) {
            if (_cropData[cropTypeIndex].lightHoursPerDay[cropPhaseIndex] == 0 &&
                _cropData[cropTypeIndex].lightHoursPerDay[cropPhaseIndex-1] > 0) {
                _cropData[cropTypeIndex].lightHoursPerDay[cropPhaseIndex] = _cropData[cropTypeIndex].lightHoursPerDay[cropPhaseIndex-1];
            }

            if (_cropData[cropTypeIndex].feedIntervalMins[cropPhaseIndex][0] == 0 &&
                _cropData[cropTypeIndex].feedIntervalMins[cropPhaseIndex][1] == 0 &&
                _cropData[cropTypeIndex].feedIntervalMins[cropPhaseIndex-1][0] > 0 &&
                _cropData[cropTypeIndex].feedIntervalMins[cropPhaseIndex-1][1] > 0) {
                _cropData[cropTypeIndex].feedIntervalMins[cropPhaseIndex][0] = _cropData[cropTypeIndex].feedIntervalMins[cropPhaseIndex-1][0];
                _cropData[cropTypeIndex].feedIntervalMins[cropPhaseIndex][1] = _cropData[cropTypeIndex].feedIntervalMins[cropPhaseIndex-1][1];
            }

            if (_cropData[cropTypeIndex].phRange[cropPhaseIndex][0] == 0 &&
                _cropData[cropTypeIndex].phRange[cropPhaseIndex][1] == 0 &&
                _cropData[cropTypeIndex].phRange[cropPhaseIndex-1][0] > 0 &&
                _cropData[cropTypeIndex].phRange[cropPhaseIndex-1][1] > 0) {
                _cropData[cropTypeIndex].phRange[cropPhaseIndex][0] = _cropData[cropTypeIndex].phRange[cropPhaseIndex-1][0];
                _cropData[cropTypeIndex].phRange[cropPhaseIndex][1] = _cropData[cropTypeIndex].phRange[cropPhaseIndex-1][1];
            }

            if (_cropData[cropTypeIndex].ecRange[cropPhaseIndex][0] == 0 &&
                _cropData[cropTypeIndex].ecRange[cropPhaseIndex][1] == 0 &&
                _cropData[cropTypeIndex].ecRange[cropPhaseIndex-1][0] > 0 &&
                _cropData[cropTypeIndex].ecRange[cropPhaseIndex-1][1] > 0) {
                _cropData[cropTypeIndex].ecRange[cropPhaseIndex][0] = _cropData[cropTypeIndex].ecRange[cropPhaseIndex-1][0];
                _cropData[cropTypeIndex].ecRange[cropPhaseIndex][1] = _cropData[cropTypeIndex].ecRange[cropPhaseIndex-1][1];
            }

            if (_cropData[cropTypeIndex].waterTempRange[cropPhaseIndex][0] == 0 &&
                _cropData[cropTypeIndex].waterTempRange[cropPhaseIndex][1] == 0 &&
                _cropData[cropTypeIndex].waterTempRange[cropPhaseIndex-1][0] > 0 &&
                _cropData[cropTypeIndex].waterTempRange[cropPhaseIndex-1][1] > 0) {
                _cropData[cropTypeIndex].waterTempRange[cropPhaseIndex][0] = _cropData[cropTypeIndex].waterTempRange[cropPhaseIndex-1][0];
                _cropData[cropTypeIndex].waterTempRange[cropPhaseIndex][1] = _cropData[cropTypeIndex].waterTempRange[cropPhaseIndex-1][1];
            }

            if (_cropData[cropTypeIndex].airTempRange[cropPhaseIndex][0] == 0 &&
                _cropData[cropTypeIndex].airTempRange[cropPhaseIndex][1] == 0 &&
                _cropData[cropTypeIndex].airTempRange[cropPhaseIndex-1][0] > 0 &&
                _cropData[cropTypeIndex].airTempRange[cropPhaseIndex-1][1] > 0) {
                _cropData[cropTypeIndex].airTempRange[cropPhaseIndex][0] = _cropData[cropTypeIndex].airTempRange[cropPhaseIndex-1][0];
                _cropData[cropTypeIndex].airTempRange[cropPhaseIndex][1] = _cropData[cropTypeIndex].airTempRange[cropPhaseIndex-1][1];
            }
        }
    }
}

const HydroponicsCropData *HydroponicsCropsLibrary::getCropData(Hydroponics_CropType cropType) const
{
    assert(!(cropType >= 0 && cropType < Hydroponics_CropType_Count && "Invalid parameters"));
    return &_cropData[cropType];
}

void HydroponicsCropsLibrary::setCustomCropData(const Hydroponics_CropType cropType, const HydroponicsCropData *cropData)
{
    assert(!(cropType >= Hydroponics_CropType_Custom1 && cropType <= Hydroponics_CropType_Custom5 && "Invalid parameters"));
    _cropData[cropType] = *cropData;
    validateEntries();
}


HydroponicsCrop::HydroponicsCrop(const Hydroponics_CropType cropType, const int positionIndex, const time_t sowDate)
    : _cropType(cropType), _positionIndex(positionIndex), _sowDate(sowDate),
      _cropData(NULL), _growWeek(0), _cropPhase(Hydroponics_CropPhase_Undefined)
{
    _cropData = HydroponicsCropsLibrary::getInstance()->getCropData(cropType);

    recalcGrowWeekAndPhase();
}

const Hydroponics_CropType HydroponicsCrop::getCropType() const
{
    return _cropType;
}

const HydroponicsCropData *HydroponicsCrop::getCropData() const
{
    return _cropData;
}

int HydroponicsCrop::getPositionIndex() const
{
    return _positionIndex;
}

time_t HydroponicsCrop::getSowDate() const
{
    return _sowDate;
}

int HydroponicsCrop::getGrowWeek() const
{
    return _growWeek;
}

Hydroponics_CropPhase HydroponicsCrop::getCropPhase() const
{
    return _cropPhase;
}

void HydroponicsCrop::update()
{
    // TODO
    recalcGrowWeekAndPhase();
}

void HydroponicsCrop::recalcGrowWeekAndPhase()
{
    // TODO
}
