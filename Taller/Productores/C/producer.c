#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <amqp.h>
#include <amqp_tcp_socket.h>

#define QUEUE_NAME "hello"
#define RABBITMQ_PORT 5672

void error_handler(const char *context, amqp_rpc_reply_t reply) {
    if (reply.reply_type != AMQP_RESPONSE_NORMAL) {
        fprintf(stderr, "Error en %s\n", context);
        exit(1);
    }
}

int main() {
    const char *rabbitmq_host = getenv("RABBITMQ_HOST");
    amqp_connection_state_t conn;
    amqp_socket_t *socket = NULL;
    conn = amqp_new_connection();
    socket = amqp_tcp_socket_new(conn);

    if (!socket) {
        fprintf(stderr, "Error creando socket\n");
        return 1;
    }

    if (amqp_socket_open(socket, rabbitmq_host, RABBITMQ_PORT)) {
        fprintf(stderr, "No se pudo conectar a RabbitMQ en %s:%d\n", rabbitmq_host, RABBITMQ_PORT);
        return 1;
    }

    error_handler("Login", amqp_login(conn, "/", 0, 131072, 0, AMQP_SASL_METHOD_PLAIN, "guest", "guest"));
    amqp_channel_open(conn, 1);
    error_handler("Abrir canal", amqp_get_rpc_reply(conn));

    amqp_queue_declare(conn, 1, amqp_cstring_bytes(QUEUE_NAME), 0, 0, 0, 0, amqp_empty_table);
    error_handler("Declarar cola", amqp_get_rpc_reply(conn));

    printf("[*] Enviando mensajes cada 3 segundos...\n");
    fflush(stdout);
    while (1) {
        char message[50];
        snprintf(message, sizeof(message), "¡Hola desde el productor en C!");

        amqp_basic_publish(conn, 1, amqp_empty_bytes, amqp_cstring_bytes(QUEUE_NAME), 0, 0, NULL, amqp_cstring_bytes(message));
        printf("[x] Enviado: '%s'\n", message);
	fflush(stdout);
        sleep(3); // Espera 3 segundos antes de enviar otro mensaje
    }

    amqp_channel_close(conn, 1, AMQP_REPLY_SUCCESS);
    amqp_connection_close(conn, AMQP_REPLY_SUCCESS);
    amqp_destroy_connection(conn);
    return 0;
}
