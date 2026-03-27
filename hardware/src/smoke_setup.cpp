#include <MQGasKit.h>
#include "smoke_setup.h"
#include "global.h"
#include "config.h"

static float averagePpm(MQGasKit& sensor, const char* gasType) {
    const int samples = 5;
    float sum = 0.0f;
    int validCount = 0;
    for (int i = 0; i < samples; ++i) {
        float value = sensor.getPPM(gasType);
        if (!isnan(value) && isfinite(value) && value >= 0.0f && value <= MQ2_PPM_SANITY_MAX) {
            sum += value;
            validCount++;
        }
        vTaskDelay(pdMS_TO_TICKS(MQ2_SAMPLE_DELAY_MS));
    }
    return (validCount > 0) ? (sum / validCount) : NAN;
}

void vTaskSmoke(void *pvParameter) {
    MQGasKit mq2_1(MQ2_ANALOG_PIN_A, MQ2);
    MQGasKit mq2_2(MQ2_ANALOG_PIN_B, MQ2);

    pinMode(MQ2_ANALOG_PIN_A, INPUT);
    pinMode(MQ2_ANALOG_PIN_B, INPUT);

    mq2_1.calibrate();
    mq2_2.calibrate();
    const uint32_t warmupStart = millis();

    while (1) {
        if (xSensorMutex != NULL && xSemaphoreTake(xSensorMutex, portMAX_DELAY) == pdPASS) {
            if (millis() - warmupStart < MQ2_WARMUP_MS) {
                smoke[0][0] = smoke[0][1] = smoke[0][2] = 0.0f;
                smoke[1][0] = smoke[1][1] = smoke[1][2] = 0.0f;
                smoke_alert = false;
                Serial.printf("\nMQ2 warmup... ignoring first %.1fs data", MQ2_WARMUP_MS / 1000.0f);
                xSemaphoreGive(xSensorMutex);
                vTaskDelay(pdMS_TO_TICKS(MQ2_TASK_INTERVAL_MS));
                continue;
            }

            const int raw1 = analogRead(MQ2_ANALOG_PIN_A);
            const int raw2 = analogRead(MQ2_ANALOG_PIN_B);
            float smoke1 = averagePpm(mq2_1, "Smoke");
            float smoke2 = averagePpm(mq2_2, "Smoke");

            if (isnan(smoke1) || isnan(smoke2)) {
                Serial.print("\n Value is unreadable!");
                smoke_alert = false;
            } else {
                if (raw1 <= MQ2_ADC_RAIL_LOW || raw1 >= MQ2_ADC_RAIL_HIGH ||
                    raw2 <= MQ2_ADC_RAIL_LOW || raw2 >= MQ2_ADC_RAIL_HIGH) {
                    smoke[0][0] = smoke[0][1] = smoke[0][2] = 0.0f;
                    smoke[1][0] = smoke[1][1] = smoke[1][2] = 0.0f;
                    smoke_alert = false;
                    Serial.printf("\nMQ2 ADC at rail (raw1=%d raw2=%d), readings cleared", raw1, raw2);
                    xSemaphoreGive(xSensorMutex);
                    vTaskDelay(pdMS_TO_TICKS(MQ2_TASK_INTERVAL_MS));
                    continue;
                }

                smoke[0][0] = averagePpm(mq2_1, "CO");
                smoke[0][1] = averagePpm(mq2_1, "LPG");
                smoke[0][2] = smoke1;

                smoke[1][0] = averagePpm(mq2_2, "CO");
                smoke[1][1] = averagePpm(mq2_2, "LPG");
                smoke[1][2] = smoke2;

                const float mq2_1_total = smoke[0][0] + smoke[0][1] + smoke[0][2];
                const float mq2_2_total = smoke[1][0] + smoke[1][1] + smoke[1][2];
                const float smoke_total = mq2_1_total + mq2_2_total;

                Serial.printf("\nCO1: %.2f | LPG1: %.2f | Smoke1: %.2f ppm", smoke[0][0], smoke[0][1], smoke[0][2]);
                Serial.printf("\nCO2 %.2f | LPG2: %.2f | Smoke2: %.2f ppm", smoke[1][0], smoke[1][1], smoke[1][2]);

                smoke_alert = smoke_total > MQ2_SMOKE_ALERT_THRESHOLD_PPM;
            }
            xSemaphoreGive(xSensorMutex);
        }

        vTaskDelay(pdMS_TO_TICKS(MQ2_TASK_INTERVAL_MS));
    }
}
