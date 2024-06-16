// BatteryMeter.h

#ifndef BATTERY_METER_H
#define BATTERY_METER_H

class BatteryMeter {
  public:

  struct BatteryData {
    float analogRead;
    float pinVoltage;
    float batteryVoltage;
    float percentage;
  };

  BatteryMeter(float R1, float R2, int adcPin, float vmin, float vmax);
  float getAnalogRead();
  float getVoltage();
  float getPercentage();
  BatteryData getBatteryData();

private:
  float R1;
  float R2;
  int adcPin; 
  float vmin;
  float vmax;

  float convertAnalogReadToPinVoltage(float analogValue);
  float convertPinVoltageToBatteryVoltage(float pinVoltage);
  float convertBatteryVoltageToPercentage(float batteryVoltage);
};

#endif