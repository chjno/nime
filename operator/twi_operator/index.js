var http = require('http');
var path = require('path');
var twilio = require('twilio');
var express = require('express');
var bodyParser = require('body-parser');
var randomUsername = require('./randos');
var config = require('./config');
var opn = require('opn');

var phone1 = {
  ready: false,
  socketId: '',
  identity: '',
  inUse: false,
  dialed: '',
  browser: 'google chrome'
};
var phone2 = {
  ready: false,
  socketId: '',
  identity: '',
  inUse: false,
  dialed: '',
  browser: 'firefox'
};

var app = express();
app.use(express.static(path.join(__dirname, '/')));
app.use(bodyParser.urlencoded({ extended: false }));

var identities = [];
app.get('/token', function(request, response) {

  identities.push(randomUsername());

  var capability = new twilio.Capability(config.TWILIO_ACCOUNT_SID,
    config.TWILIO_AUTH_TOKEN);
  capability.allowClientOutgoing(config.TWILIO_TWIML_APP_SID);
  capability.allowClientIncoming(identities[identities.length - 1]);
  var token = capability.generate();

  response.send({
    identity: identities[identities.length - 1],
    token: token
  });
});

app.post('/voice', function (req, res) {

  var cid;
  if (req.body.From == 'client:' + phone1.identity){
    cid = config.TWILIO_CALLER_ID[0];
  } else if (req.body.From == 'client:' + phone2.identity){
    cid = config.TWILIO_CALLER_ID[1];
  }

  var twiml = new twilio.TwimlResponse();

  if(req.body.To) {

    twiml.dial({ callerId: cid}, function() {
      if (req.body.From[0] == 'c'){
        this.number(req.body.To);
      } else {
        if (!phone1.inUse){
          this.client(phone1.identity);
        } else if (!phone2.inUse){
          this.client(phone2.identity);
        } else {
          twiml.say("All lines are busy. Please try again later.");
        }
      }
    });

  } else {
    twiml.say("Thanks for calling!");
  }

  res.set('Content-Type', 'text/xml');
  res.send(twiml.toString());
});

var server = http.createServer(app);
var port = 3000;
// var port = process.env.PORT || 3000;
// server.listen(port, function() {



var osc = require('node-osc');

var oscServer = new osc.Server(3333, '127.0.0.1');

oscServer.on('pickup', function(msg, rinfo){
  // console.log(msg);

  if (msg[1] == 1){
    io.to(phone1.socketId).emit('pickup');
    console.log('pickup ' + phone1.socketId);
    phone1.dialed = '';
    phone1.inUse = false;
  } else if (msg[1] == 2){
    io.to(phone2.socketId).emit('pickup');
    console.log('pickup ' + phone2.socketId);
    phone1.dialed = '';
    phone2.inUse = false;
  }
});

oscServer.on('hangup', function(msg, rinfo){
  // console.log(msg);

  if (msg[1] == 1){
    io.to(phone1.socketId).emit('hangup');
    console.log('hangup ' + phone1.socketId);
    phone1.dialed = '';
    phone1.inUse = false;
  } else if (msg[1] == 2){
    io.to(phone2.socketId).emit('hangup');
    console.log('hangup ' + phone2.socketId);
    phone2.dialed = '';
    phone2.inUse = false;
  }
});

oscServer.on('num', function(msg, rinfo){
  // console.log(msg);

  if (msg[1] == 1){
    phone = phone1;
  } else if (msg[1] == 2){
    phone = phone2;
  }

  var num = msg[2];

  if (!phone.inUse){
    phone.dialed += num;
    console.log(phone.dialed);

    if (phone.dialed.length >= 10){
      io.to(phone.id).emit('call', phone.dialed);
      phone.inUse = true;
      phone.dialed = '';
    }
  } else {
    io.to(phone.id).emit('digit', num);
  }

});

var oscClient = new osc.Client('127.0.0.1', 3334);

var io = require('socket.io')(server);

io.on('connection', function(socket){

  var thisPhone;

  if (phone1.socketId === ''){
    phone1.socketId = socket.id;
    thisPhone = phone1;
  } else if (phone2.socketId === ''){
    phone2.socketId = socket.id;
    thisPhone = phone2;
  } else {
    return;
  }

  // io.to(socket.id).emit('news', socket.id);
  console.log('connected ' + socket.id);
  console.log();

  socket.on('ready', function(msg){
    if (thisPhone.identity === ''){
      thisPhone.identity = identities.pop();
    }

    thisPhone.ready = true;
    console.log('ready');
    console.log(thisPhone);
    console.log('');
  });

  socket.on('inUse', function(msg){
    thisPhone.inUse = msg;

    if (msg){
      console.log('call started ' + thisPhone.socketId);
    } else {
      thisPhone.inUse = false;
      console.log('call ended ' + thisPhone.socketId);
    }
    console.log('');
  });

  // socket.on('incoming', function(msg){

  // });

  socket.on('disconnect', function(){
    if (phone1.socketId == socket.id){
      phone1.socketId = '';
      phone1.ready = false;
      phone1.inUse = false;
      phone1.dialed = '';
    } else if (phone2.socketId == socket.id){
      phone2.socketId = '';
      phone2.ready = false;
      phone2.inUse = false;
      phone2.dialed = '';
    }
    console.log('disconnected: ' + socket.id);
    // FIXME
    // opn('http://localhost:3000', {app: 'google chrome'});
  });
});



server.listen(port, function() {
  console.log('Express server running on *:' + port);
});

// opn('http://localhost:3000', {app: 'google chrome'});
