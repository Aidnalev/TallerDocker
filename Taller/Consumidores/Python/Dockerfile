FROM python:3.9-slim

WORKDIR /app

# Instalar las dependencias
RUN pip install pika

# Copiar el código fuente
COPY consumer.py .

# Ejecutar el consumidor
CMD ["python", "consumer.py"]
