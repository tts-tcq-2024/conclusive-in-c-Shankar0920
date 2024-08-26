#include <gtest/gtest.h>
#include "typewise-alert.h"

// Test case: when temperature is below lower limit
TEST(TypeWiseAlertTestSuite, InfersBreachBelowLowerLimits) {
    BatteryCharacter batteryChar = { PASSIVE_COOLING, "Test" };
    checkAndAlert(TO_CONTROLLER, batteryChar, -10.0); // Temperature below 0°C
}

// Test case: when temperature is above upper limit
TEST(TypeWiseAlertTestSuite, InfersBreachAboveUpperLimits) {
    BatteryCharacter batteryChar = { PASSIVE_COOLING, "Test" };
    checkAndAlert(TO_CONTROLLER, batteryChar, 45.0); // Temperature above 35°C
}

// Test case: when temperature is exactly on the lower limit
TEST(TypeWiseAlertTestSuite, InfersBreachOnLowerLimit) {
    BatteryCharacter batteryChar = { PASSIVE_COOLING, "Test" };
    checkAndAlert(TO_CONTROLLER, batteryChar, 0.0); // Temperature exactly at 0°C
}

// Test case: Infers breach when temperature is exactly on the upper limit
TEST(TypeWiseAlertTestSuite, InfersBreachOnUpperLimit) {
    BatteryCharacter batteryChar = { PASSIVE_COOLING, "Test" };
    checkAndAlert(TO_CONTROLLER, batteryChar, 35.0); // Temperature exactly at 35°C
}

// Test case: Check the output when temperature is within normal limits
TEST(TypeWiseAlertTestSuite, CheckNormalTemperatureToController) {
    BatteryCharacter batteryChar = { PASSIVE_COOLING, "Test" };
    checkAndAlert(TO_EMAIL, batteryChar, 21.0); // Temperature within 0°C to 35°C
}

// Test case: Check the output when temperature is too low and send email
TEST(TypeWiseAlertTestSuite, CheckTooLowTemperatureToEmail) {
    BatteryCharacter batteryChar = { PASSIVE_COOLING, "Test" };
    checkAndAlert(TO_EMAIL, batteryChar, -5.0); // Temperature below 0°C
}

// Test case: Check the output when temperature is too high and send email
TEST(TypeWiseAlertTestSuite, CheckTooHighTemperatureToEmail) {
    BatteryCharacter batteryChar = { PASSIVE_COOLING, "Test" };
    checkAndAlert(TO_EMAIL, batteryChar, 60.0); // Temperature above 35°C
}
