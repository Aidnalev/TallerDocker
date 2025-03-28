FROM gcc:latest
WORKDIR /app

# Instalar librería de RabbitMQ C
RUN apt-get update && apt-get install -y librabbitmq-dev

# Copiar los archivos del productor
COPY producer.c .

# Compilar el código fuente
RUN gcc -o producer producer.c -lrabbitmq

# Ejecutar el productor
CMD ["./producer"]
