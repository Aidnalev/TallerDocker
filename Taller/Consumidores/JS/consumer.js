const amqp = require('amqplib');
const rabbitmqHost = process.env.RABBITMQ_HOST;
async function consume() {
    const connection = await amqp.connect(`amqp://${rabbitmqHost}`);
    const channel = await connection.createChannel();

    await channel.assertQueue("hello", { durable: false });

    console.log(" [*] Esperando mensajes en la cola 'hello'. Ctrl+C para salir.");

    channel.consume("hello", (msg) => {
        console.log(` [x] Recibido: ${msg.content.toString()}`);
    }, { noAck: true });
}

consume().catch(console.error);
