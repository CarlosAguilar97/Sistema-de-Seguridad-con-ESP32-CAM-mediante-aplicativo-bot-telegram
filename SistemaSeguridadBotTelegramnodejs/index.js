const TelegramBot = require('node-telegram-bot-api');

const token = '2088882507:AAE46TBIT8rFzXsdf84pcGHem8uHcl06lvY';

var opt = {polling: true};

const bot = new TelegramBot(token, opt);

const SerialPort = require('serialport')
var MiPuerto = new SerialPort('/dev/ttyACM7', {
  baudRate: 115200,
  autoOpen: true
});

var id = 1422002215;

bot.onText(/\/echo (.+)/, (msg, match) => {

  const chatId = msg.chat.id;
  const resp = match[1];

  bot.sendMessage(chatId, resp);
});

bot.on('message', (msg) => {
  const chatId = msg.chat.id;
  var mensaje = msg.text;
  console.log("Este es el ID del chat " + chatId);


  if (mensaje == "encender") {
    console.log("Encendido");
    bot.sendMessage(chatId, 'Sistema Activado');
    MiPuerto.write("H");
  }
  else if (mensaje == "apagar") {
    console.log("Apagando");
    bot.sendMessage(chatId, 'Sistema Desactivado');
    MiPuerto.write("L");
  }
});

MiPuerto.setEncoding('utf8');
MiPuerto.on('data',function(data){

  console.log("Lo que entro es "+ data);

    if (data[0] == "G") {
      bot.sendMessage(id, 'Se ha detectado el GAS en al cocina');
    }

    if (data[0] == "M") {
      bot.sendMessage(id, 'Se ha detectado el movimiento de la habitacion principal');
    }

    if (data[0] == "F") {
      bot.sendMessage(id, 'Se ha detectado fuego en la sala principal');
    }

    if (data[0] == "P") {
      bot.sendMessage(id, 'Se abrió la puerta principal');
    }

});
