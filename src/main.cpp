#include <Arduino.h>
#include "BatteryMeter.h"

const int batteryPin = 36;
const float R1 = 4710.0;
const float R2 = 10050.0;
const float vmin = 3.0;
const float vmax = 4.2;

BatteryMeter *batteryMeter = new BatteryMeter(R1, R2, batteryPin, vmin, vmax);

void setup() {
  Serial.begin(115200);
  delay(1000); // Wait for serial monitor to open
}

void loop() {
  BatteryMeter::BatteryData batteryData = batteryMeter->getBatteryData();

  Serial.print("Analog Reading: ");
  Serial.print(batteryData.analogRead);
  Serial.print(" Pin Voltage: ");
  Serial.print(batteryData.pinVoltage);
  Serial.print(" V, Battery Voltage: ");
  Serial.print(batteryData.batteryVoltage);
  Serial.print(" V, Battery Percentage: ");
  Serial.print(batteryData.percentage);
  Serial.println(" %");

  delay(1000); // Update every second
}