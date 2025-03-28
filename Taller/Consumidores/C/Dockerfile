# Imagen base con herramientas necesarias
FROM debian:latest

# Instalar dependencias
RUN apt-get update && apt-get install -y librabbitmq-dev gcc make cmake

# Crear directorio de trabajo
WORKDIR /app

# Copiar el código fuente
COPY consumer.c .

# Compilar el código
RUN gcc -o consumer consumer.c -lrabbitmq

# Comando de inicio
CMD ["./consumer"]
