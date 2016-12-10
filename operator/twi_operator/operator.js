// var ring = new Audio('ring.wav');
// var ringing = false;
// ring.addEventListener('ended', function() {
//   if (ringing){
//     this.currentTime = 0;
//     this.play();
//   }
// }, false);

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

  // ringing = true;
  // ring.play();
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
      // ring.pause();
      // ringing = false;
      connection = conn;
      socket.emit('inUse', true);
      console.log('Successfully established call!');
    });

    Twilio.Device.disconnect(function (conn) {
      socket.emit('inUse', false);
      console.log('Call ended.');
    });

    // Twilio.Device.incoming(function (conn) {
    //   incoming = conn;
    //   ringing = true;
    //   ring.play();


    //   var intervalCount = 0;
    //   function acceptInbound(){
    //     intervalCount++;
    //     if (conn.status() == 'closed' || intervalCount == 100){
    //       clearInterval(a);
    //     } else if (plugged){
    //       conn.accept();
    //       clearInterval(a);
    //     }
    //   }
      
    //   console.log('Incoming connection from ' + conn.parameters.From);
    //   if (!plugged){
    //     socket.emit('incoming', conn.parameters.From);
    //     var a = setInterval(acceptInbound, 100);

    //   } else {
    //     conn.reject();
    //   }
    // });

  })
  .fail(function () {
    console.log('Could not get a token from server!');
  });

});
