//
//  WindowsShutterAccessory.cpp
//  HKTester
//
//  Created by Lukas Jezny on 10/02/2019.
//  Copyright © 2019 Lukas Jezny. All rights reserved.
//

#include "WindowsShutterAccessory.h"

#include "homekit/HKConnection.h"

#include <set>

#ifdef PARTICLE_COMPAT
#include "../example/HKTester/HKTester/Particle_Compat/particle_compat.h"
#else
#include <Particle.h>
#endif
#include "homekit/HKLog.h"

#define COVER_OPEN_TO_CLOSE_MS 60000
#define TILT_OPEN_TO_CLOSE_MS 1000

intCharacteristics *positionState;
intCharacteristics *currentPosition;
intCharacteristics *currentTiltAngle;

void shutterIdentity(bool oldValue, bool newValue, HKConnection *sender) {
    HKLogger.printf("Shutter identify\n");
}

void WindowsShutterAccessory::handle() {
    
}

void setTargetPosition (int oldValue, int newValue, HKConnection *sender) {
    HKLogger.printf("setTargetPosition %d\n",newValue);
}

void setTargetTiltAngle (int oldValue, int newValue, HKConnection *sender) {
    HKLogger.printf("setTargetTiltAngle %d\n",newValue);
}

void WindowsShutterAccessory::initAccessorySet() {
    Accessory *shutterAccessory = new Accessory();

    AccessorySet *accSet = &AccessorySet::getInstance();
    addInfoServiceToAccessory(shutterAccessory, "Shutter name", "Vendor name", "Model  name", "1", &shutterIdentity);
    accSet->addAccessory(shutterAccessory);

    Service *windowsCoverService = new Service(serviceType_windowCover);
    shutterAccessory->addService(windowsCoverService);

    stringCharacteristics *nameCharacteristic = new stringCharacteristics(charType_serviceName, premission_read, 0);
    nameCharacteristic->characteristics::setValue("Window name");
    shutterAccessory->addCharacteristics(windowsCoverService, nameCharacteristic);

    intCharacteristics *targetPosition = new intCharacteristics(charType_targetPosition, premission_read|premission_write|premission_notify, 0, 100, 1, unit_percentage);
    targetPosition->characteristics::setValue("0");
    targetPosition->valueChangeFunctionCall = &setTargetPosition;
    shutterAccessory->addCharacteristics(windowsCoverService, targetPosition);

    currentPosition = new intCharacteristics(charType_currentPosition, premission_read|premission_notify, 0, 100, 1, unit_percentage);
    currentPosition->characteristics::setValue("0");
    shutterAccessory->addCharacteristics(windowsCoverService, currentPosition);

    positionState = new intCharacteristics(charType_positionState, premission_read|premission_notify, 0, 2, 1, unit_percentage);
    positionState->characteristics::setValue("2");
    shutterAccessory->addCharacteristics(windowsCoverService, positionState);

    intCharacteristics *targetHorizontalTiltAngle = new intCharacteristics(charType_targetHorizontalTiltAngle, premission_read|premission_write|premission_notify, -90, 0, 10, unit_arcDegree);
    targetHorizontalTiltAngle->characteristics::setValue("0");
    targetHorizontalTiltAngle->valueChangeFunctionCall = &setTargetTiltAngle;
    shutterAccessory->addCharacteristics(windowsCoverService, targetHorizontalTiltAngle);
    
    currentTiltAngle = new intCharacteristics(charType_currentPosition, premission_read|premission_notify, 0, 100, 1, unit_percentage);
    currentTiltAngle->characteristics::setValue("0");
    shutterAccessory->addCharacteristics(windowsCoverService, currentTiltAngle);
};