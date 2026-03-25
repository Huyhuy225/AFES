#ifndef GLOBAL_H
#define GLOBAL_H

#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

/** Analog inputs for the two MQ-2 modules (same net names as schematic). */
#define MQ2_ANALOG_PIN_A A0
#define MQ2_ANALOG_PIN_B A1
#define FLAME1_DIGIPIN 17
#define FLAME1_ANAPIN 3
#define FLAME2_DIGIPIN 18
#define FLAME2_ANAPIN 4

#define PUMP_PIN   6
#define BUZZER_PIN 8
#define LED_PIN    10
#define BUTTON_PIN 21
//-------------DHT20+LCD
#define SDA_PIN   11
#define SCL_PIN   12
/** Per sensor: [0]=CO ppm, [1]=LPG ppm, [2]=Smoke ppm (MQGasKit getPPM). */
extern float smoke[2][3];
extern float flame[2]; // [Flame1, Flame2]
//DHT20_value
extern float glob_temperature;
extern volatile bool pump_on;
extern volatile bool fire_alert;
extern volatile bool ledbuzzon;
/** True when either MQ-2 smoke channel exceeds MQ2_SMOKE_ALERT_THRESHOLD_PPM. */
extern volatile bool smoke_alert;
extern volatile bool manual_pump_on;
extern volatile bool manual_alarm_on;
extern volatile bool manual_emergency_on;
extern volatile uint32_t manual_pump_until_ms;
extern volatile uint32_t manual_alarm_until_ms;
extern volatile uint32_t manual_emergency_until_ms;
extern SemaphoreHandle_t xMqttMutex;
extern SemaphoreHandle_t xWifiMutex;
extern SemaphoreHandle_t xSensorMutex;
#endif