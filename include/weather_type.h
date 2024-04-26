#if !defined(L_WEATHER_TYPE_H_)
#define L_WEATHER_TYPE_H_
#include "framework.h"
#include "cJSON.h"

#define COPY_STR(a, b) \
    memcpy((a), (b), strlen(b) * sizeof(char) + 1);

typedef struct Weather
{
    struct Weather *self;
    char area[STR_MAX_LEN];
    char country[STR_MAX_LEN];
    char weather_c[STR_MAX_LEN];
    char wind[STR_MAX_LEN];
    char wind_direction[STR_MAX_LEN];
    char desctiption[STR_MAX_LEN];
    void (*print)(struct Weather *);
    void (*dtor)(struct Weather *);

} weather_t;

void weather_print(weather_t *self)
{
    printf("\n%s, %s\n", self->area, self->country);
    printf("The weather is %s C\n", self->weather_c);
    printf("%s \n", self->desctiption);
    printf("The wind is %s Km/h, direction is %s\n\n", self->wind, self->wind_direction);
}

void weather_destory(weather_t *self)
{

    free(self);
}
weather_t *weather_create()
{
    weather_t *weather = (weather_t *)malloc(sizeof(weather_t));

    weather->print = weather_print;
    weather->dtor = weather_destory;
    return weather;
}

void weather_json_parse(weather_t *weather, char *response_body)
{

    cJSON *json = cJSON_Parse(response_body);
    cJSON *current_condition_obj;
    cJSON *temp_C;
    cJSON *wind;
    cJSON *direction;
    cJSON *description_top;
    cJSON *description;
    cJSON *nearest_area;
    cJSON *area;
    cJSON *country;

    current_condition_obj = cJSON_GetObjectItem(json, "current_condition");

    temp_C = cJSON_GetObjectItem(current_condition_obj->child, "temp_C");
    wind = cJSON_GetObjectItem(current_condition_obj->child, "windspeedKmph");
    direction = cJSON_GetObjectItem(current_condition_obj->child, "winddir16Point");
    description_top = cJSON_GetObjectItem(current_condition_obj->child, "weatherDesc");
    description = cJSON_GetObjectItem(description_top->child, "value");

    nearest_area = cJSON_GetObjectItem(json, "nearest_area");
    country = cJSON_GetObjectItem(nearest_area->child, "country");
    if (country)
    {

        COPY_STR(weather->country, country->child->child->valuestring)
    }

    area = cJSON_GetObjectItem(nearest_area->child, "region");
    if (area)
    {

        COPY_STR(weather->area, area->child->child->valuestring)
    }

    if (temp_C)
    {
        COPY_STR(weather->weather_c, temp_C->valuestring)
    }

    if (wind)
    {
        COPY_STR(weather->wind, wind->valuestring)
    }
    if (direction)
    {
        COPY_STR(weather->wind_direction, direction->valuestring)
    }
    if (description)
    {
        COPY_STR(weather->desctiption, description->valuestring)
    }

    cJSON_Delete(json);
}

#endif // L_WEATHER_TYPE_H_
