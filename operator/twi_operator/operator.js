var socket = io();
// socket.on('news', function(msg){console.log(msg);});

var connection;

var plugged = false;

socket.on('call', function(num){
  console.log(num);
  call(num);
});
socket.on('digit', function(num){
  console.log(num);
  connection.sendDigits(num.toString());
});
socket.on('pickup', function(msg){
  console.log('picked up');
  plugged = true;
});
socket.on('hangup', function(){
  hangup();
  plugged = false;
});

var call = function (num) {
  var params = {
    To: num
  };

  console.log('Calling ' + params.To + '...');
  Twilio.Device.connect(params);
};

var hangup = function () {
  console.log('Hanging up...');
  Twilio.Device.disconnectAll();
};

$(function () {

  var isFirefox = typeof InstallTrigger !== 'undefined';
  var isChrome = !!window.chrome && !!window.chrome.webstore;

  if (isChrome){
    socket.emit('browser', 'google chrome');
  } else if (isFirefox){
    socket.emit('browser', 'firefox');
  }

  console.log('Requesting Capability Token...');
  $.getJSON('/token').done(function (data) {

    console.log('Got a token.');
    console.log('Token: ' + data.token);

    // Setup Twilio.Device
    Twilio.Device.setup(data.token);
    Twilio.Device.sounds.incoming(false);
    Twilio.Device.sounds.outgoing(false);
    Twilio.Device.sounds.disconnect(false);

    Twilio.Device.ready(function (device) {
      console.log('Twilio.Device Ready!');
      socket.emit('ready', true);
    });

    Twilio.Device.error(function (error) {
      console.log('Twilio.Device Error: ' + error.message);
    });

    Twilio.Device.connect(function (conn) {
      connection = conn;
      socket.emit('inUse', true);
      console.log('Successfully established call!');
    });

    Twilio.Device.disconnect(function (conn) {
      socket.emit('inUse', false);
      console.log('Call ended.');
    });

    Twilio.Device.incoming(function (conn) {
      incoming = conn;
      
      console.log('Incoming connection from ' + conn.parameters.From);
      // if (!plugged){
      //   socket.emit('incoming', conn.parameters.From);
      // } else {
      //   conn.reject();
      // }

      conn.accept();
    });

  })
  .fail(function () {
    console.log('Could not get a token from server!');
  });

});
