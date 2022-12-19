#include "cgi.h"
#include "common.h"

static int protocolSend(struct cgi_para *para) {
    if (para->status != API_OK) {
        printf("%s\nlength: %lu\n", para->APIs_send, strlen(para->APIs_send));
    }
    printf("%s\nlength: %lu\n", para->APIs_send, strlen(para->APIs_send));
    return API_OK;
}

static int proccgi_lwip(int socket_id, char *cmd) {
    struct cgi_para para;
    API_FUNC api_func;

    cJSON *json;
    json = cJSON_Parse(cmd);

    if (!json) {
        para.status = CMD_WRONG_FORMAT;
    } else {
        cJSON_Value url;
        para.status = getObjectValueFromJson(json, "url", &url);
        if (FUNC_OK == para.status) {
            api_func = cgi_filename_match(url.string_val);
            if (NULL != api_func) {
                para.socket_id = socket_id;
                para.APIs_recv = cmd;
                para.need_restart = false;
                api_func(&para);
            } else {
                para.status = CMD_INVALID_URL;
            }
        }
    }
    protocolSend(&para);
    cJSON_Delete(json);
    return FUNC_OK;
}

int main() {
    int socket_id = 1;
    while (1) {
        char *cmd = "{\"url\":\"info\"}";
        char *cmd_2 = "{\"url\":qwe}";
        printf("Client request: %s\n", cmd);
        proccgi_lwip(socket_id, cmd);
    }
    return 0;
}
