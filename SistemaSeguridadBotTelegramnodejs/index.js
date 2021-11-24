const TelegramBot = require('node-telegram-bot-api');

const token = '2088882507:AAE46TBIT8rFzXsdf84pcGHem8uHcl06lvY';

const bot = new TelegramBot(token, {polling: true});

bot.onText(/\/echo (.+)/, (msg, match) => {

  const chatId = msg.chat.id;
  const resp = match[1];

  bot.sendMessage(chatId, resp);
});

bot.on('message', (msg) => {
  const chatId = msg.chat.id;
  var mensaje = msg.text;

bot.sendMessage(chatId, 'Hola soy SeggurBot y sere tu mano derecha...');

  if (mensaje == "Hola") {
    console.log("Hola, como te va?...");
    bot.sendMessage(chatId, 'Hola, como te va?...');
  }
});
