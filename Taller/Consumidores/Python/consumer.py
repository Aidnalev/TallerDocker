import os
import pika
import sys
rabbitmq_host = os.getenv("RABBITMQ_HOST")
QUEUE_NAME = "hello"

def callback(ch, method, properties, body):
    print(f"[x] Recibido: {body.decode()}", flush=True)  # Forzar salida inmediata

def main():
    try:
        # Configurar conexión a RabbitMQ
        connection = pika.BlockingConnection(pika.ConnectionParameters(host=rabbitmq_host))
        channel = connection.channel()

        # Declarar la cola
        channel.queue_declare(queue=QUEUE_NAME, durable=False)

        print("[*] Esperando mensajes. Para salir, presiona CTRL+C", flush=True)

        # Consumir mensajes
        channel.basic_consume(queue=QUEUE_NAME, on_message_callback=callback, auto_ack=True)

        # Evitar buffering de salida
        sys.stdout.flush()
        channel.start_consuming()

    except Exception as e:
        print(f"Error al conectar con RabbitMQ: {e}", flush=True)

if __name__ == "__main__":
    main()

