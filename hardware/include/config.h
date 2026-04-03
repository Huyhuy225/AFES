#ifndef CONFIG_H
#define CONFIG_H

#define ssid "Thành's iPhone"
#define password "khongbiet"
// Use broker host/IP only (without ":port").
#define mqtt_server "4.144.181.249"
#define mqtt_port 1883
#define mqtt_user "Flame_Detection_System"
#define mqtt_password "123"

// === TOPICS ===
#define TOPIC_FLAME "yolo_uno/sensors/flame"
#define TOPIC_DHT20 "yolo_uno/sensors/dht20"
#define TOPIC_SMOKE "yolo_uno/sensors/smoke"
#define TOPIC_CONTROL "yolo_uno/control"

// === MQ-2 (smoke / combustible gas — MQGasKit estimated ppm, not lab-grade) ===
// Tune MQ2_SMOKE_ALERT_THRESHOLD_PPM together with the dashboard after field calibration.
#define MQ2_SMOKE_ALERT_THRESHOLD_PPM 45.0f
#define MQ2_PPM_SANITY_MAX 10000.0f
#define MQ2_ADC_RAIL_LOW 5
#define MQ2_ADC_RAIL_HIGH 4090
#define MQ2_WARMUP_MS 7000UL
#define MQ2_SAMPLE_DELAY_MS 30UL
#define MQ2_TASK_INTERVAL_MS 3000UL

#endif