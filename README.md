# 🐳 Taller de Docker

Este es el taller de Docker terminado. Consiste en un ejercicio de contenedores en el que usamos **RabbitMQ** para transmitir mensajes por colas, con la ayuda de **3 consumidores** y **3 productores** en **Python, C y JavaScript**.

### 🔹 Escenarios Implementados
1. **Una sola máquina:** RabbitMQ, productores y consumidores en la misma máquina.
2. **Dos máquinas:** RabbitMQ en una máquina independiente y los productores/consumidores en otra.
3. **Tres máquinas:** RabbitMQ en una máquina, y los productores/consumidores distribuidos en dos máquinas diferentes.

## 📂 Estructura del Repositorio

La estructura del repositorio está organizada en tres carpetas principales:

```
📁 Taller-Docker
 ├── 📁 Productores  # Código y Dockerfiles de los productores (Python, C, JS)
 ├── 📁 Consumidores # Código y Dockerfiles de los consumidores (Python, C, JS)
 ├── 📁 Compose      # Archivos docker-compose para cada escenario
```

- En **Productores** y **Consumidores** encontrarás el código necesario junto con sus respectivos Dockerfiles.
- En **Compose** están los archivos `docker-compose.yml`, organizados según la cantidad de máquinas en las que se ejecutará el taller.

> **Nota:** No es necesario crear las imágenes manualmente, ya que están subidas en **Docker Hub**. Los `docker-compose.yml` ya están configurados para utilizarlas directamente.

## 🚀 Procedimiento

El procedimiento para cualquiera de los tres escenarios es básicamente el mismo:

1. **Ubica el archivo `docker-compose.yml` adecuado:**
   - Para **una máquina**, hay un solo `docker-compose.yml`.
   - Para **dos o tres máquinas**, encontrarás carpetas con archivos separados según la máquina en la que deben ejecutarse.

2. **Modificar la dirección de RabbitMQ:**
   - Abre el archivo con:
     ```bash
     nano docker-compose.yml
     ```
   - Busca la línea:
     ```yaml
     environment:
       - RABBITMQ_HOST=10.6.101.124
     ```
   - Reemplaza `10.6.101.124` con la **IP de la máquina donde está alojado RabbitMQ**.
   - Realiza este cambio en **los 6 servicios de productores y consumidores**.

3. **Ejecutar `docker-compose up` según el número de máquinas:**
   - **Una máquina:** Ejecuta el siguiente comando una sola vez:
     ```bash
     docker-compose up
     ```
   - **Dos máquinas:**
     1. Ejecuta en la máquina que alojará RabbitMQ:
        ```bash
        docker-compose up
        ```
     2. Ejecuta en la otra máquina (donde estarán productores/consumidores):
        ```bash
        docker-compose up
        ```
   - **Tres máquinas:**
     1. Ejecuta en la máquina de RabbitMQ:
        ```bash
        docker-compose up
        ```
     2. Ejecuta en la máquina `servicios1`:
        ```bash
        docker-compose up
        ```
     3. Ejecuta en la máquina `servicios2`:
        ```bash
        docker-compose up
        ```
 Cabe resaltar que, si por ejemplo, el RabbitMQ de host para los escenarios de 2 y 3 máquinas al tiempo deben detenerse y eliminarse los contenedores que tendrían el mismo nombre (esto también aplica para pasar del escenario 2 a 3, en la segunda máquina virtual donde se ejecuten todos los servicios, a la hora de ejecutarlo en el tercer escenario estos deben ser detenidos y eliminados) o bien, realizar el despliegue con
 ```bash
docker-compose up -d
```
y revisar los logs con 
```bash
docker-compose logs -f
```

## 📄 Notas Finales

- Para detener los contenedores, usa `Ctrl + C` o ejecuta:
  ```bash
  docker-compose down
  ```
- Si quieres reconstruir los contenedores sin usar las imágenes de Docker Hub:
  ```bash
  docker-compose build --no-cache
  ```

¡Listo! Ahora el taller de Docker está más claro y fácil de leer. 🚀🐳

