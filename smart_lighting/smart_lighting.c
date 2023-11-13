

/*
Requirements:
1. User Input Time Scheduling (SNTP,WIFI,MQTT)
2. Low Light Detection
3. Relay
4. Bulb/LED
*/


#include <mqttm.h>
#include <wifim.h>
#include <sntp.h>

#include <esp_log.h>
#include <esp_err.h>

#include <time.h>

struct tm alarm_time[2] = {0};

esp_err_t sl_set_on_off_timing(bool onoff, time_t time)
{
    if(time <= currentOnOffTime || onoff >= 2)
    {
        return ESP_INVALID_ARG;
    }

    currentOnOffTime[onoff] = time;
    return ESP_OK;
}

esp_err_t sl_get_on_time(time_t *ontime)
{
    ESP_CHECK_PARAM(ontime);

    (*ontime) = currentOnOffTime[0];
    return ESP_OK;
}

esp_err_t sl_get_off_time(time_t *offtime)
{
    ESP_CHECK_PARAM(offtime);

    (*offtime) = currentOnOffTime[1];
    return ESP_OK;
}

/*
if led/buld is on, check the off timing and ldr reading 
if led/bulb is off, check the on timing and ldr reading
*/
void sl_task(void *parameters)
{
    (void)parameters;

    for( ; ; )
    {
        // reading led status
        if(led_get_status() == 1) //TODO: write right api to get the led status.
        {
            if(sntp_get_current_time() > 
        }
    } 
}