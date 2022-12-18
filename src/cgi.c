#include "cgi.h"

const struct cgi cgi_cmds[] = {
    {"info", &getDeviceInfor},
    {"wifi", &configWifi},
    {"stream", &setStream},
    {"status", &getStreamStatus},
    {"control", &configStream},
    {"factoryReset", &factoryReset},
    {"videoInfor", &getVideoInfor}};

CGI_FUNC cgi_filename_match(char *path_info) {
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

void jsonAdd_StrItemToObj(cJSON *json_file, const char *object, const char *item) {
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
        }
        if (cJSON_IsNumber(cJSON_GetObjectItem(json, obj))) {
            val->number_val = cJSON_GetObjectItem(json, obj)->valueint;
        }
        // printf("val->string_val: %s val->number_val %d\n", val->string_val, val->number_val);
    } else {
        printf("json has no obj %s\n", obj);
        return -1;
    }
    return FUNC_OK;
}

static int getDeviceInfor(struct cgi_para *para) {
    // cJSON *response_json = cJSON_CreateObject();

    // // cJSON *recv_cmd = cJSON_Parse(para->APIs_recv);
    // // cJSON_Value url = {};
    // // getObjectValueFromJson(recv_cmd, "url", &url);
    // // jsonAdd_StrItemToObj(response_json, "url", url.string_val);
    // // cJSON_Delete(recv_cmd);

    // cJSON_AddNullToObject(response_json, "status");
    
    // // cJSON *data = cJSON_CreateObject();

    // // jsonAdd_StrItemToObj(data, "productName", "hehehehe");
    // // jsonAdd_StrItemToObj(data, "productCode", "heheheh123123e");

    // // cJSON_AddItemReferenceToObject(response_json, "data", data);
    // // cJSON_Delete(data);

    // char *temp = cJSON_PrintUnformatted(response_json);
    // printf("%s\n", temp);
    
    // cJSON_free(temp);

    // cJSON_Delete(response_json);
    return API_OK;
}

static int configWifi(struct cgi_para *para) {
}

static int configStream(struct cgi_para *para) {
}

static int setStream(struct cgi_para *para) {
}

static int getStreamStatus(struct cgi_para *para) {
}

static int getVideoInfor(struct cgi_para *para) {
}

static int factoryReset(struct cgi_para *para) {
}
