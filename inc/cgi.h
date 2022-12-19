#include "cJSON.h"
#include "common.h"

typedef enum {
    FUNC_OK = 0,
    API_OK = 0,
} API_STATUS;

typedef enum {
    CMD_WRONG_FORMAT = 400,
    CMD_INVALID_URL,
} CLIENT_ERRORS;

struct cgi_para {
    int socket_id;         // socket id
    bool need_restart;
    char *APIs_send;  // data send to client/mobile app
    char *APIs_recv;  // data recv from client/mobile app
    int status;
};

typedef void (*API_FUNC)(struct cgi_para *para);

struct cgi {
    char *name;
    API_FUNC func;
};

typedef struct cJSON_Value {
    char *string_val;
    int number_val;
} cJSON_Value;

API_FUNC cgi_filename_match(char *path_info);

int getObjectValueFromJson(cJSON *json, char *obj, cJSON_Value *val);

/**
 * @brief Get the Device Info object
 *
 * @param para
 * @return int
 */
static void getDeviceInfo(struct cgi_para *para);

static void configWifi(struct cgi_para *para);

static void configStream(struct cgi_para *para);

static void setStream(struct cgi_para *para);

static void getStreamStatus(struct cgi_para *para);

static void getVideoInfo(struct cgi_para *para);

static void factoryReset(struct cgi_para *para);
