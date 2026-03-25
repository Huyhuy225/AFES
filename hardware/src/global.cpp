#include "global.h"

float smoke[2][3] = {{0, 0, 0}, {0, 0, 0}};
float flame[2] = {0, 0}; // [flame1, flame2]
//dht20
float glob_temperature = 0.0f;
SemaphoreHandle_t xMqttMutex = NULL;
SemaphoreHandle_t xWifiMutex = NULL;
SemaphoreHandle_t xSensorMutex = NULL;
volatile bool pump_on = false;
volatile bool fire_alert = false;
volatile bool ledbuzzon = false;
volatile bool smoke_alert = false;
volatile bool manual_pump_on = false;
volatile bool manual_alarm_on = false;
volatile bool manual_emergency_on = false;
volatile uint32_t manual_pump_until_ms = 0;
volatile uint32_t manual_alarm_until_ms = 0;
volatile uint32_t manual_emergency_until_ms = 0;