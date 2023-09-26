#include <dht.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#if defined(CONFIG_EXAMPLE_TYPE_DHT11)
#define SENSOR_TYPE DHT_TYPE_DHT11
#endif
#if defined(CONFIG_EXAMPLE_TYPE_AM2301)
#define SENSOR_TYPE DHT_TYPE_AM2301
#endif
#if defined(CONFIG_EXAMPLE_TYPE_SI7021)
#define SENSOR_TYPE DHT_TYPE_SI7021
#endif

static const char *TAG = "dht";

#define DHT_TEMPERATURE_THRESHOLD ((float)(40))
#define DHT_HUMIDITY_THRESHOLD ((flaot)(80))

esp_err_t dht_reading(void *parameter)
{
    float temperature, humidity;

#ifdef CONFIG_EXAMPLE_INTERNAL_PULLUP
    gpio_set_pull_mode(dht_gpio, GPIO_PULLUP_ONLY);
#endif

    for (;;)
    {
        if (dht_read_float_data(SENSOR_TYPE, CONFIG_EXAMPLE_DATA_GPIO, &humidity, &temperature) == ESP_OK)
        {
            ESP_LOGD(TAG, "Humidity: %.1f%% Temp: %.1fC\n", humidity, temperature);
            
            if (humidity > DHT_HUMIDITY_THRESHOLD || temperature > DHT_TEMPERATURE_THRESHOLD)
            {
                ESP_LOGW(TAG, "Humidity: %.1f%% Temp: %.1fC is HIGH", humidity, temperature);
            }
        }
        else
        {
            ESP_LOGD(TAG, "Could not read data from sensor\n");
        }
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

void app_main()
{
    xTaskCreate(dht_test, "dht_test", configMINIMAL_STACK_SIZE * 3, NULL, 5, NULL);
}
