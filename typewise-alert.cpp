#include "typewise-alert.h"
#include <stdio.h>
//Function pointer for AlertTarget
typedef void (*AlertFunction)(BreachType);

//Data Structure for temperature limit
typedef struct{
int lowerLimit;
int upperLimit;
}Temperature_Limit;

Temperature_Limit limitsTable[]=
{
    [PASSIVE_COOLING] = {0, 35},
    [HI_ACTIVE_COOLING] = {0, 45},
    [MED_ACTIVE_COOLING] = {0, 40}
};

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
  if(value < lowerLimit) {
    return TOO_LOW;
  }
  if(value > upperLimit) {
    return TOO_HIGH;
  }
  return NORMAL;
}

BreachType classifyTemperatureBreach(
    CoolingType coolingType, double temperatureInC) {
  int lowerLimit = 0;
  int upperLimit = 0;
  Temperature_Limit limits = limitsTable[coolingType];
  return inferBreach(temperatureInC, limits.lowerLimit, limits.upperLimit);
}

AlertFunction alertFunctions[] = {
    [TO_CONTROLLER] = sendToController,
    [TO_EMAIL] = sendToEmail
};

void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {
    if (alertTarget < 0 || alertTarget >= sizeof(alertFunctions) / sizeof(alertFunctions[0])) {
        printf("Invalid alert target!\n");
        return;
    }

    BreachType breachType = classifyTemperatureBreach(batteryChar.coolingType, temperatureInC);
    alertFunctions[alertTarget](breachType);
}

void sendToController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
}
//Data Structure for sending email message
typedef struct {
    char* message;
} EmailMessage;

EmailMessage emailMessages[] = {
    emailMessages[TOO_LOW] = {"Hi, the temperature is too low"},
    emailMessages[TOO_HIGH] = {"Hi, the temperature is too high"},
    emailMessages[NORMAL] = {""}
};

void sendToEmail(BreachType breachType) {
  const char* recepient = "a.b@c.com";
  if (emailMessages[breachType].message != NULL) {
        printf("To: %s\n", recepient);
        printf("%s\n", emailMessages[breachType].message);
    }
}
