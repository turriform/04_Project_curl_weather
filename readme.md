### Curl Installation
`sudo apt-get install libcurl4`

`sudo apt-get install libcurl4-openssl-dev`

Makefile 

`LIBS+= -lcurl`

### JSON

Using cJSON lib for JSON

https://github.com/DaveGamble/cJSON

Makefile 

`INCLUDE+= -I./third_party/cJSON/include/` 

Source for on-the-fly compilation

`C_JSON_SRC = ./third_party/cJSON/src/cJSON.c`

Parsed data is written to the Weather struct

```
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
```

