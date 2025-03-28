#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <amqp.h>
#include <amqp_tcp_socket.h>

#define RABBITMQ_PORT 5672
#define RABBITMQ_QUEUE "hello"

void error_die(const char *message, amqp_rpc_reply_t x) {
    fprintf(stderr, "%s\n", message);
    exit(1);
}

int main() {
    const char *rabbitmq_host = getenv("RABBITMQ_HOST");
    amqp_connection_state_t conn;
    amqp_socket_t *socket = NULL;
    amqp_rpc_reply_t reply;

    conn = amqp_new_connection();
    socket = amqp_tcp_socket_new(conn);
    if (!socket) {
        fprintf(stderr, "Error al crear socket\n");
        return 1;
    }

    if (amqp_socket_open(socket, rabbitmq_host, RABBITMQ_PORT)) {
        fprintf(stderr, "Error al conectar con RabbitMQ\n");
        return 1;
    }

    reply = amqp_login(conn, "/", 0, 131072, 0, AMQP_SASL_METHOD_PLAIN, "guest", "guest");
    if (reply.reply_type != AMQP_RESPONSE_NORMAL) {
        error_die("Error en la autenticación", reply);
    }

    amqp_channel_open(conn, 1);
    reply = amqp_get_rpc_reply(conn);
    if (reply.reply_type != AMQP_RESPONSE_NORMAL) {
        error_die("Error al abrir el canal", reply);
    }

    amqp_queue_declare(conn, 1, amqp_cstring_bytes(RABBITMQ_QUEUE), 0, 0, 0, 0, amqp_empty_table);
    reply = amqp_get_rpc_reply(conn);
    if (reply.reply_type != AMQP_RESPONSE_NORMAL) {
        fprintf(stderr, "Error al declarar la cola: %s\n", RABBITMQ_QUEUE);
    } else {
        printf("Conectado a RabbitMQ en %s:%d\n", rabbitmq_host, RABBITMQ_PORT);
    }

    amqp_basic_consume(conn, 1, amqp_cstring_bytes(RABBITMQ_QUEUE), amqp_empty_bytes, 0, 1, 0, amqp_empty_table);
    reply = amqp_get_rpc_reply(conn);
    if (reply.reply_type != AMQP_RESPONSE_NORMAL) {
        error_die("Error al iniciar el consumo", reply);
    }

    printf("Iniciando consumidor...\n");

    while (1) {
        amqp_envelope_t envelope;
        amqp_maybe_release_buffers(conn);
        reply = amqp_consume_message(conn, &envelope, NULL, 0);

        if (reply.reply_type == AMQP_RESPONSE_NORMAL) {
            printf(" [x] Recibido: %.*s\n", (int)envelope.message.body.len, (char *)envelope.message.body.bytes);
            fflush(stdout); // Asegura que se imprima inmediatamente
            usleep(100000); // Pausa de 100ms para procesar mensajes más suavemente
            amqp_destroy_envelope(&envelope);
        }
    }

    amqp_channel_close(conn, 1, AMQP_REPLY_SUCCESS);
    amqp_connection_close(conn, AMQP_REPLY_SUCCESS);
    amqp_destroy_connection(conn);
    return 0;
}

