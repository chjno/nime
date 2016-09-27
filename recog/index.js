var express = require('express');
var app = express();
var http = require('http').Server(app);
var io = require('socket.io')(http);
var sentiment = require('sentiment');

app.use(express.static('./'));

app.get('/', function (req, res) {
  // res.send('Hello World!');
  res.sendFile('/Users/chino/github/nime/recog/index.html');
});

http.listen(3000, function () {
  console.log('Example app listening on port 3000!');
});

// var r1 = sentiment('Cats are stupid.');
// console.dir(r1);  

io.on('connection', function(socket) {
  console.log('user connected');

  socket.on('new final', function(s) {
    var r1 = sentiment(s);
    // console.dir(r1);
    socket.emit('sentiment', r1);
  })

  socket.on('disconnect', function() {
    console.log('user disconnected');
  });
});