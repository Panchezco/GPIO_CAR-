#include <esp_wifi.h>
#include <esp_event.h>
#include <esp_log.h>
#include <esp_system.h>
#include <nvs_flash.h>
#include <sys/param.h>
#include "esp_netif.h"
#include "esp_eth.h"
#include "protocol_examples_common.h"
#include <esp_https_server.h>
#include "esp_tls.h"
#include <string.h>
//#include "driver/gpio.h"
#include "gpio.h"
#include <stdio.h>


// LOS PINES PARA EL CARRO SON POR DEFECTO
// PARA HACER CAMBIOS ES EN EL ARCHIVO bsp.h
// AQUI SOLO SON DE REFERENCIA.
//#define GPIO_UP 2
//#define GPIO_DOWN 4
//#define GPIO_UP2 16
//#define GPIO_DOWN2 17
//#define LED_CAR 5

int8_t gpio_up_state = 0;
int8_t gpio_down_state = 0;
int8_t gpio_left_state = 0;
int8_t gpio_right_state = 0;

static const char *TAG = "main";

/* An HTTP GET handler */
static esp_err_t root_get_handler(httpd_req_t *req)
{
    // Llama a la función start_CAR al inicio del manejador de peticiones de movimiento
    start_CAR();

    // Variables para cargar el contenido HTML de la página
    extern unsigned char view_start[] asm("_binary_view_html_start");
    extern unsigned char view_end[] asm("_binary_view_html_end");
    size_t view_len = view_end - view_start;
    char viewHtml[view_len];
    memcpy(viewHtml, view_start, view_len);

    // Log de la URI solicitada
    ESP_LOGI(TAG, "URI: %s", req->uri);

    // Manejo de diferentes acciones basadas en la URI
    if (strcmp(req->uri, "/?action=right") == 0)
    {
        MOTOR_RIGHT();
    }
    if (strcmp(req->uri, "/?action=up") == 0)
    {
        MOTOR_UP();
    }
    if (strcmp(req->uri, "/?action=down") == 0)
    {
        MOTOR_DOWN();
    }
    if (strcmp(req->uri, "/?action=left") == 0)
    {
        MOTOR_LEFT();
    }
    if (strcmp(req->uri, "/?action=stop") == 0)
    {
        MOTOR_STOP();
    }
    if (strcmp(req->uri, "/?action=light") == 0)
    {
        MOTOR_LED_ON();
    }
    if (strcmp(req->uri, "/?action=off") == 0)
    {
        MOTOR_LED_OFF();
    }

    // Actualiza el contenido HTML con el estado de los pines GPIO
    char *viewHtmlUpdated;
    int formattedStrResult = asprintf(&viewHtmlUpdated, viewHtml,
                                      gpio_up_state ? "ON" : "OFF",
                                      gpio_down_state ? "ON" : "OFF",
                                      gpio_left_state ? "ON" : "OFF",
                                      gpio_right_state ? "ON" : "OFF");

    // Configura la respuesta como HTML
    httpd_resp_set_type(req, "text/html");

    // Envía la respuesta actualizada o la original en caso de error
    if (formattedStrResult > 0)
    {
        httpd_resp_send(req, viewHtmlUpdated, view_len);
        free(viewHtmlUpdated);
    }
    else
    {
        ESP_LOGE(TAG, "Error updating variables");
        httpd_resp_send(req, viewHtml, view_len);
    }

    return ESP_OK;
}

// Define la URI raíz y asigna el manejador
static const httpd_uri_t root = {
    .uri = "/",
    .method = HTTP_GET,
    .handler = root_get_handler
};

// Inicia el servidor web
static httpd_handle_t start_webserver(void)
{
    httpd_handle_t server = NULL;

    // Inicia el servidor HTTP
    ESP_LOGI(TAG, "Starting server");

    httpd_ssl_config_t conf = HTTPD_SSL_CONFIG_DEFAULT();
    conf.transport_mode = HTTPD_SSL_TRANSPORT_INSECURE;
    esp_err_t ret = httpd_ssl_start(&server, &conf);
    if (ESP_OK != ret)
    {
        ESP_LOGI(TAG, "Error starting server!");
        return NULL;
    }

    // Registra los manejadores de URI
    ESP_LOGI(TAG, "Registering URI handlers");
    httpd_register_uri_handler(server, &root);
    return server;
}

// Detiene el servidor web
static void stop_webserver(httpd_handle_t server)
{
    httpd_ssl_stop(server);
}

// Manejador de desconexiones
static void disconnect_handler(void *arg, esp_event_base_t event_base,
                               int32_t event_id, void *event_data)
{
    httpd_handle_t *server = (httpd_handle_t *)arg;
    if (*server)
    {
        stop_webserver(*server);
        *server = NULL;
    }
}

// Manejador de conexiones
static void connect_handler(void *arg, esp_event_base_t event_base,
                            int32_t event_id, void *event_data)
{
    httpd_handle_t *server = (httpd_handle_t *)arg;
    if (*server == NULL)
    {
        *server = start_webserver();
    }
}

// Función principal del programa
void app_main(void)
{
    static httpd_handle_t server = NULL;
    ESP_ERROR_CHECK(nvs_flash_init());  // Inicializa el almacenamiento no volátil
    ESP_ERROR_CHECK(esp_netif_init());  // Inicializa la red
    ESP_ERROR_CHECK(esp_event_loop_create_default());  // Crea el bucle de eventos por defecto
    ESP_ERROR_CHECK(esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &connect_handler, &server));  // Registra el manejador de conexiones
    ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, WIFI_EVENT_STA_DISCONNECTED, &disconnect_handler, &server));  // Registra el manejador de desconexiones
    ESP_ERROR_CHECK(example_connect());  // Conecta a la red Wi-Fi
}
