#include "framework.h"
#include "weather_get.h"
#include "weather_type.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Please provide location!\n");
        return EXIT_SUCCESS;
    }

    printf("\nLooking for weather in %s...\n", argv[1]);

    char url_init[STR_MAX_LEN] = "https://wttr.in/";
    strncat(url_init, argv[1], strlen(argv[1]));
    strcat(url_init, "?format=j1");

    curl_memory_t *chunk = (curl_memory_t *)malloc(sizeof(curl_memory_t));

    // grabing the chunk from the website response

    int curl_init = curl_init_local(url_init, chunk);

    if (curl_init != 0)
    {

        free(chunk->memory);
        free(chunk);
        perror("Error with curl occured \n");
        return EXIT_FAILURE;
    }

    weather_t *weather = weather_create();
    // building weather
    weather_json_parse(weather, chunk->memory);

    weather->print(weather);
    weather->dtor(weather);

    free(chunk->memory);
    free(chunk);

    return 0;
}