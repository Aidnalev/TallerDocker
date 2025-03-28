# Usa la imagen oficial de Node.js
FROM node:18

# Establece el directorio de trabajo en el contenedor
WORKDIR /app

# Copia los archivos del productor al contenedor
COPY package.json ./
COPY producer.js ./

# Instala las dependencias
RUN npm install

# Comando para ejecutar el productor
CMD ["node", "producer.js"]
