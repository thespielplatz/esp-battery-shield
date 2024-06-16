#include "BatteryMeter.h"
#include <Arduino.h>

BatteryMeter::BatteryMeter(float R1, float R2, int adcPin, float vmin, float vmax) {
  this->R1 = R1;
  this->R2 = R2;
  this->adcPin = adcPin;
  this->vmin = vmin;
  this->vmax = vmax;
}

float BatteryMeter::getAnalogRead() {
  return analogRead(adcPin);
}

float BatteryMeter::getVoltage() {
  float analogValue = getAnalogRead();
  float pinVoltage = convertAnalogReadToPinVoltage(analogValue);
  return convertPinVoltageToBatteryVoltage(pinVoltage);
}

float BatteryMeter::getPercentage() {
  float batteryVoltage = getVoltage();
  return convertBatteryVoltageToPercentage(batteryVoltage);
}

BatteryMeter::BatteryData BatteryMeter::getBatteryData() {
  BatteryData data;
  data.analogRead = getAnalogRead();
  data.pinVoltage = convertAnalogReadToPinVoltage(data.analogRead);
  data.batteryVoltage = convertPinVoltageToBatteryVoltage(data.pinVoltage);
  data.percentage = convertBatteryVoltageToPercentage(data.batteryVoltage);
  return data;
}

// Convert analog reading to voltage (12-bit ADC)
float BatteryMeter::convertAnalogReadToPinVoltage(float analogValue) {
  return analogValue * (3.3 / 4095.0);
}

// Revert the voltage divider to battery voltage
float BatteryMeter::convertPinVoltageToBatteryVoltage(float pinVoltage) {
  return pinVoltage / R2 * (R1 + R2);
}

float BatteryMeter::convertBatteryVoltageToPercentage(float batteryVoltage) {
  if (batteryVoltage < vmin) batteryVoltage = vmin;
  if (batteryVoltage > vmax) batteryVoltage = vmax;
  return (batteryVoltage - vmin) / (vmax - vmin) * 100.0;
}