var socket = io();
// socket.on('news', function(msg){console.log(msg);});

var connection;

socket.on('call', function(num){
  console.log(num);
  call(num);
});
socket.on('digit', function(num){
  console.log(num);
  connection.sendDigits(num);
});
socket.on('hangup', function(){
  hangup();
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
  console.log('Requesting Capability Token...');
  $.getJSON('/token').done(function (data) {

    console.log('Got a token.');
    console.log('Token: ' + data.token);

    // Setup Twilio.Device
    Twilio.Device.setup(data.token);

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
      console.log('Incoming connection from ' + conn.parameters.From);
      var archEnemyPhoneNumber = '+12099517118';

      if (conn.parameters.From === archEnemyPhoneNumber) {
        conn.reject();
        console.log('It\'s your nemesis. Rejected call.');
      } else {
        // accept the incoming connection and start two-way audio
        conn.accept();
      }
    });
  })
  .fail(function () {
    console.log('Could not get a token from server!');
  });

});
