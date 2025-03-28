import os
import pika  
import time  

rabbitmq_host = os.getenv("RABBITMQ_HOST")
# Conectar a RabbitMQ
connection = pika.BlockingConnection(pika.ConnectionParameters(host=rabbitmq_host))
channel = connection.channel()

# Declarar la cola
channel.queue_declare(queue="hello", durable=False)
print(" [*] Enviando mensajes cada 3 segundos. Presiona Ctrl+C para detener.", flush=True)

try:
    while True:
        message = "¡Hola desde el productor en Python!"
        channel.basic_publish(exchange="", routing_key="hello", body=message)
        print(f" [x] Enviado: {message}",flush=True)
        time.sleep(3)  # Espera 3 segundos antes de enviar otro mensaje

except KeyboardInterrupt:
    print("\n [!] Deteniendo el productor.")
    connection.close()

