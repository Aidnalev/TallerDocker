const amqp = require('amqplib');
const rabbitmqHost = process.env.RABBITMQ_HOST;
async function sendMessage() {
    try {
        // Conectar a RabbitMQ
        const conn = await amqp.connect(`amqp://${rabbitmqHost}`);
        const channel = await conn.createChannel();
        const queue = 'hello';

        // Declarar la cola con durable: false
        await channel.assertQueue(queue, { durable: false });
        console.log(" [*] Enviando mensajes cada 3 segundos...");

        while (true) {
            let message = "¡Hola desde el productor en JS!";
            channel.sendToQueue(queue, Buffer.from(message));
            console.log(" [x] Enviado:", message);
            await new Promise(resolve => setTimeout(resolve, 3000));
        }
    } catch (error) {
        console.error(" [!] Error en el productor:", error);
    }
}

sendMessage();
