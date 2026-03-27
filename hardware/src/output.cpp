#include "output.h"
#include "global.h"

static bool heartbeatWave(uint32_t periodMs) {
    const uint32_t t = millis();
    return ((t % periodMs) < (periodMs / 2UL));
}

static bool updateBlinkFromTrigger(
    bool trigger,
    bool& wasTriggered,
    bool& outputState,
    uint32_t& lastTransitionMs,
    uint32_t onMs,
    uint32_t offMs,
    uint32_t nowMs
) {
    if (!trigger) {
        wasTriggered = false;
        outputState = false;
        return false;
    }

    if (!wasTriggered) {
        // Start with a full ON pulse exactly at trigger time.
        wasTriggered = true;
        outputState = true;
        lastTransitionMs = nowMs;
        return true;
    }

    const uint32_t holdMs = outputState ? onMs : offMs;
    if (nowMs - lastTransitionMs >= holdMs) {
        outputState = !outputState;
        lastTransitionMs = nowMs;
    }
    return outputState;
}

static bool isHighTemp() {
    return glob_temperature > 45.0f;
}

void led_init(uint8_t pin_adc, uint8_t pin_led, int threshold){
    (void)pin_adc;
    (void)pin_led;
    (void)threshold;
    pinMode(LED_PIN, OUTPUT);
    pinMode(LED_STATUS_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);
    digitalWrite(LED_STATUS_PIN, LOW);
}

void led_task(void* pv){
    (void)pv;
    led_init(0, 0, 0);
    bool emergencyWasTriggered = false;
    bool emergencyLedState = false;
    uint32_t emergencyLastTransitionMs = 0;
    while (1) {
        const uint32_t nowMs = millis();
        if (manual_alarm_on && manual_alarm_until_ms > 0 && nowMs > manual_alarm_until_ms) {
            manual_alarm_on = false;
            manual_alarm_until_ms = 0;
        }
        if (manual_emergency_on && manual_emergency_until_ms > 0 && nowMs > manual_emergency_until_ms) {
            manual_emergency_on = false;
            manual_emergency_until_ms = 0;
        }

        const bool autoTrigger = fire_alert && smoke_alert && isHighTemp();
        const bool trigger = autoTrigger || manual_alarm_on || manual_emergency_on;
        emergencyLedState = updateBlinkFromTrigger(
            trigger,
            emergencyWasTriggered,
            emergencyLedState,
            emergencyLastTransitionMs,
            450UL,
            450UL,
            nowMs
        );
        const bool statusLedState = heartbeatWave(1000UL);
        digitalWrite(LED_PIN, emergencyLedState ? HIGH : LOW);
        digitalWrite(LED_STATUS_PIN, statusLedState ? HIGH : LOW);
        ledbuzzon = trigger;
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void buzz_init(uint8_t pin_adc, uint8_t pin_buzz, int threshold){
    (void)pin_adc;
    (void)pin_buzz;
    (void)threshold;
    pinMode(BUZZER_PIN, OUTPUT);
    digitalWrite(BUZZER_PIN, LOW);
}

void buzz_task(void* pv)
{
    (void)pv;
    buzz_init(0, 0, 0);
    bool buzzerWasTriggered = false;
    bool buzzerState = false;
    uint32_t buzzerLastTransitionMs = 0;
    while (1) {
        const uint32_t nowMs = millis();
        if (manual_alarm_on && manual_alarm_until_ms > 0 && nowMs > manual_alarm_until_ms) {
            manual_alarm_on = false;
            manual_alarm_until_ms = 0;
        }
        if (manual_emergency_on && manual_emergency_until_ms > 0 && nowMs > manual_emergency_until_ms) {
            manual_emergency_on = false;
            manual_emergency_until_ms = 0;
        }

        const bool autoTrigger = fire_alert && smoke_alert && isHighTemp();
        const bool trigger = autoTrigger || manual_alarm_on || manual_emergency_on;
        buzzerState = updateBlinkFromTrigger(
            trigger,
            buzzerWasTriggered,
            buzzerState,
            buzzerLastTransitionMs,
            300UL,
            350UL,
            nowMs
        );
        digitalWrite(BUZZER_PIN, buzzerState ? HIGH : LOW);
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void button_task(void* pv) {
    (void)pv;
    pinMode(BUTTON_PIN, INPUT_PULLUP);

    bool lastStableState = digitalRead(BUTTON_PIN);
    bool lastReading = lastStableState;
    uint32_t lastDebounceTime = millis();

    while (1) {
        const bool reading = digitalRead(BUTTON_PIN);
        const uint32_t nowMs = millis();

        if (reading != lastReading) {
            lastDebounceTime = nowMs;
            lastReading = reading;
        }

        if ((nowMs - lastDebounceTime) > 50UL && reading != lastStableState) {
            lastStableState = reading;

            // Button is active LOW when using INPUT_PULLUP.
            if (lastStableState == LOW) {
                const bool turnOn = !manual_emergency_on;
                manual_emergency_on = turnOn;
                manual_pump_on = turnOn;
                manual_alarm_on = turnOn;
                manual_emergency_until_ms = 0;
                manual_pump_until_ms = 0;
                manual_alarm_until_ms = 0;
                Serial.println(turnOn ? "[BUTTON] emergency toggled ON"
                                      : "[BUTTON] emergency toggled OFF");
            }
        }

        vTaskDelay(pdMS_TO_TICKS(20));
    }
}