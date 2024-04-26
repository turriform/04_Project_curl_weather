#if !defined(_L_WEATHER_GET_H)
#define _L_WEATHER_GET_H
#include "framework.h"
#include "cJSON.h"

typedef struct MemoryStruct
{
    char *memory;
    size_t size;
} curl_memory_t;

static size_t
callback(void *contents, size_t size, size_t nmemb, void *userp)
{

    size_t realsize = size * nmemb;
    curl_memory_t *mem = (curl_memory_t *)userp;

    char *ptr = realloc(mem->memory, mem->size + realsize + 1);
    if (!ptr)
    {
        printf("Bad memory allocation\n");
        return 0;
    }

    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}

int curl_init_local(char *url_init, curl_memory_t *chunk)
{
    CURL *curl_handle;
    CURLcode res;

    chunk->memory = malloc(1);
    chunk->size = 0;

    curl_global_init(CURL_GLOBAL_ALL);

    curl_handle = curl_easy_init();

    // curl main settings
    curl_easy_setopt(curl_handle, CURLOPT_URL, url_init);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, callback);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)chunk);
    curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");
    curl_easy_setopt(curl_handle, CURLOPT_PROTOCOLS_STR, "https");

    res = curl_easy_perform(curl_handle);

    if (res != CURLE_OK)
    {
        printf("Error occured with curl: %s\n",
               curl_easy_strerror(res));
        curl_easy_cleanup(curl_handle);
        curl_global_cleanup();
        return -1;
    }

    // cleaning up curl
    curl_easy_cleanup(curl_handle);
    curl_global_cleanup();
    return 0;
}

#endif