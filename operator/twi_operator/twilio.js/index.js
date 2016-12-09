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
  id: '',
  inUse: false,
  dialed: '',
  browser: 'google chrome'
};
var phone2 = {
  ready: false,
  id: '',
  inUse: false,
  dialed: '',
  browser: 'firefox'
};

// Create Express webapp
var app = express();
app.use(express.static(path.join(__dirname, '/')));
app.use(bodyParser.urlencoded({ extended: false }));

/*
Generate a Capability Token for a Twilio Client user - it generates a random
username for the client requesting a token.
*/
app.get('/token', function(request, response) {
  var identity = randomUsername();
  
  var capability = new twilio.Capability(config.TWILIO_ACCOUNT_SID,
    config.TWILIO_AUTH_TOKEN);
  capability.allowClientOutgoing(config.TWILIO_TWIML_APP_SID);
  capability.allowClientIncoming(identity);
  var token = capability.generate();

  // Include identity and token in a JSON response
  response.send({
    identity: identity,
    token: token
  });
});

app.post('/voice', function (req, res) {
  // Create TwiML response
  var twiml = new twilio.TwimlResponse();
  var cid;

  if(req.body.To) {

    if (!phone1.inUse){
      cid = config.TWILIO_CALLER_ID[0];
      twiml.dial({ callerId: cid}, function() {
        // wrap the phone number or client name in the appropriate TwiML verb
        // by checking if the number given has only digits and format symbols
        if (/^[\d\+\-\(\) ]+$/.test(req.body.To)) {
          this.number(req.body.To);
        } else {
          this.client(req.body.To);
        }
      });
    } else if (!phone2.inUse){
      cid = config.TWILIO_CALLER_ID[1];
      twiml.dial({ callerId: cid}, function() {
        // wrap the phone number or client name in the appropriate TwiML verb
        // by checking if the number given has only digits and format symbols
        if (/^[\d\+\-\(\) ]+$/.test(req.body.To)) {
          this.number(req.body.To);
        } else {
          this.client(req.body.To);
        }
      });
    }

  } else {
    twiml.say("Thanks for calling!");
  }

  res.set('Content-Type', 'text/xml');
  res.send(twiml.toString());
});

// Create http server and run it
var server = http.createServer(app);
var port = 3000;
// var port = process.env.PORT || 3000;
// server.listen(port, function() {





var osc = require('node-osc');

var oscServer = new osc.Server(3333, '127.0.0.1');

oscServer.on('pickup', function(msg, rinfo){
  // console.log(msg);

  if (msg[1] == 1){
    io.to(phone1.id).emit('pickup');
    console.log('pickup ' + phone1.id);
    phone1.dialed = '';
    phone1.inUse = false;
  } else if (msg[1] == 2){
    io.to(phone2.id).emit('pickup');
    console.log('pickup ' + phone2.id);
    phone1.dialed = '';
    phone2.inUse = false;
  }
});

oscServer.on('hangup', function(msg, rinfo){
  // console.log(msg);

  if (msg[1] == 1){
    io.to(phone1.id).emit('hangup');
    console.log('hangup ' + phone1.id);
    phone1.dialed = '';
    phone1.inUse = false;
  } else if (msg[1] == 2){
    io.to(phone2.id).emit('hangup');
    console.log('hangup ' + phone2.id);
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

  if (phone1.id === ''){
    phone1.id = socket.id;
    thisPhone = phone1;
  } else if (phone2.id === ''){
    phone2.id = socket.id;
    thisPhone = phone2;
  } else {
    return;
  }

  // io.to(socket.id).emit('news', socket.id);
  console.log('connected ');
  console.log(thisPhone);
  console.log('');

  socket.on('ready', function(msg){
    thisPhone.ready = true;
    console.log('ready ' + thisPhone.id);
    console.log('');
  });

  socket.on('inUse', function(msg){
    thisPhone.inUse = msg;

    if (msg){
      console.log('call started ' + thisPhone.id);
    } else {
      thisPhone.inUse = false;
      console.log('call ended ' + thisPhone.id);
    }
    console.log('');
  });

  socket.on('disconnect', function(){
    if (phone1.id == socket.id){
      phone1.id = '';
      phone1.ready = false;
      phone1.inUse = false;
      phone1.dialed = '';
    } else if (phone2.id == socket.id){
      phone2.id = '';
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

opn('http://localhost:3000', {app: 'google chrome'});
opn('http://localhost:3000', {app: 'firefox'});
