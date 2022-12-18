#include "cgi.h"
#include "common.h"

static int proccgi_lwip(int socket_id, char *cmd) {
    struct cgi_para para;
    CGI_FUNC cgi_func;

    cJSON *json;
    json = cJSON_Parse(cmd);

    if (!json) {
        printf("error no json\n");
        cJSON_Delete(json);
        return -1;
    } else {
        cJSON_Value *url;
        if (FUNC_OK != getObjectValueFromJson(json, "url", url)) {
            return -1;
        }
        // cgi_func = cgi_filename_match(url->string_val);
        // if (NULL == cgi_func){
        //     return -1;
        // }
        para.sd = socket_id;
        para.APIs_recv = cmd;
        para.need_restart = false;
        // cgi_func(&para);
    }

    cJSON_Delete(json);
    return FUNC_OK;
}

int main() {
    int c = 1;
    while (1) {
        char *cmd = "{\"url\":\"info\"}";
        char *cmd_2 = "{\"url\":qwe}";
        printf("Client request: %s\n", cmd);
        proccgi_lwip(c, cmd);
        break;
    }
    return 0;
}
