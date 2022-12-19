#include "cgi.h"

const struct cgi cgi_cmds[] = {
    {"info", &getDeviceInfo},
    {"wifi", &configWifi},
    {"stream", &setStream},
    {"status", &getStreamStatus},
    {"control", &configStream},
    {"factoryReset", &factoryReset},
    {"videoInfo", &getVideoInfo}};

API_FUNC cgi_filename_match(char *path_info) {
    int i;

    // LOG_I(lwip_socket_example, "[HTTPD] cgi_filename_match() - path_info = %s\n", path_info);

    for (i = 0; i < (sizeof(cgi_cmds) / sizeof(struct cgi)); i++) {
        if (!strcmp(cgi_cmds[i].name, path_info)) {
            // LOG_I(common, "Function name: %s\n", cgi_cmds[i].name);
            return cgi_cmds[i].func;
        }
    }
    // LOG_I(common, "Path info name: %s\n", path_info);
    return NULL;
}

void addToResponseJSON(cJSON *json_file, const char *object, const char *item) {
    cJSON *new_item;
    new_item = cJSON_CreateString(item);

    cJSON_AddItemToObject(json_file, object, new_item);
}

void jsonAdd_NumberItemToObj(cJSON *json_file, const char *object, const int number) {
    cJSON *new_item;
    new_item = cJSON_CreateNumber(number);

    cJSON_AddItemToObject(json_file, object, new_item);
}

int getObjectValueFromJson(cJSON *json, char *obj, cJSON_Value *val) {
    if (cJSON_HasObjectItem(json, obj)) {
        if (cJSON_IsString(cJSON_GetObjectItem(json, obj))) {
            val->string_val = cJSON_GetStringValue(cJSON_GetObjectItem(json, obj));
            val->number_val = 0;
        }
        if (cJSON_IsNumber(cJSON_GetObjectItem(json, obj))) {
            val->number_val = cJSON_GetObjectItem(json, obj)->valueint;
        }
    } else {
        printf("json has no obj %s\n", obj);
        return -1;
    }
    return FUNC_OK;
}

static cJSON *createJsonResponse(struct cgi_para *para) {
    cJSON *temp = cJSON_CreateObject();

    cJSON *recv_cmd = cJSON_Parse(para->APIs_recv);
    cJSON_Value url;
    getObjectValueFromJson(recv_cmd, "url", &url);
    addToResponseJSON(temp, "url", url.string_val);
    cJSON_Delete(recv_cmd);
    cJSON_AddNullToObject(temp, "status");
    return temp;
}

static int procDeviceName(char *name){
    strcpy(name, "XSTREAM_");
    char *mac_address = "00:04:40:56:6a:d9";
    strcat(name, mac_address);
    printf("product name: %s\n", name);
    return FUNC_OK;
}

static int procDeviceCode(char *device_code){
    char *mac_address = "00:04:40:56:6a:d9";
    char temp[32] = {0};

    int count = 0;
    for (int i = strlen(mac_address); i >= 0; i--) {
        if (':' == mac_address[i]) {
            temp[count] = toupper(mac_address[i + 1]);
            temp[count + 1] = toupper(mac_address[i + 2]);
            count += 2;
        }
        if (0 == i) {
            temp[count] = toupper(mac_address[i]);
            temp[count + 1] = toupper(mac_address[i + 1]);
        }
    }
    strcpy(device_code, temp);
    return FUNC_OK;
}

static void getDeviceInfo(struct cgi_para *para) {
    /* Create Json response */
    cJSON *response_json = createJsonResponse(para);
    /* Create data child */
    cJSON *data = cJSON_CreateObject();

    /* Handle data */
    // Device Name
    char productName[32] = {0};
    para->status = procDeviceName(productName);
    if(FUNC_OK != para->status){
        return;
    }
    addToResponseJSON(data, "productName", productName);

    // Device Code
    char productCode[32] = {0};
    para->status = procDeviceCode(productCode);
    if(FUNC_OK != para->status){
        return;
    }
    addToResponseJSON(data, "productCode", productCode);

    char mac_address[] = "00:04:40:56:6a:d9";
    addToResponseJSON(data, "deviceMac", mac_address);

    /* Add "data" to json */
    cJSON_AddItemReferenceToObject(response_json, "data", data);
    
    /* Convert cJSON to string, printf debuf */
    para->APIs_send = cJSON_Print(response_json);

    cJSON_Delete(data);
    cJSON_Delete(response_json);
    para->status = API_OK;
}

static void configWifi(struct cgi_para *para) {
}

static void configStream(struct cgi_para *para) {
}

static void setStream(struct cgi_para *para) {
}

static void getStreamStatus(struct cgi_para *para) {
}

static void getVideoInfo(struct cgi_para *para) {
}

static void factoryReset(struct cgi_para *para) {
}
