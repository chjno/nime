socket.on('sentiment', function(obj) {
  // console.log(obj);
});

var finalSpans = [];

if (!('webkitSpeechRecognition' in window)) {
  alert("webkitSpeechRecognition isn't here");
} else {
  var recording = false;
  var recog = new webkitSpeechRecognition();
  recog.continuous = true;
  recog.interimResults = true;

  recog.onstart = function() {}
  recog.onresult = function(event) {
    // console.log(event);
    var interim_transcript = '';
    var newFinal = false;
    var finalHTML = '';

    for (var i = event.resultIndex; i < event.results.length; ++i) {
      if (event.results[i].isFinal) {
        final_transcript = event.results[i][0].transcript.trim() + ' ';
        newFinal = true;
      } else {
        interim_transcript += event.results[i][0].transcript.trim() + ' ';
      }
    }
    final_transcript = capitalize(final_transcript);
    // final_span.innerHTML = linebreak(final_transcript);
    interim_span.innerHTML = linebreak(interim_transcript);


    if (newFinal) {
      socket.emit('new final', final_transcript);

      for (var j = 0; j < finalSpans.length; j++) {
        results.removeChild(finalSpans[j]);
      }
      finalSpans = [];
      for (var i = 0; i < final_transcript.length; i++) {
        var span = document.createElement('span');
        span.className = 'final';
        span.innerHTML = final_transcript[i];
        finalSpans.push(span);
        results.insertBefore(span, interim_span);
      }
      genNotes(final_transcript);
      newFinal = false;
    }
  };
  recog.onerror = function(event) {}
  recog.onend = function() {}
}

var start_button = document.getElementById("start_button");
start_button.addEventListener("click", function(event) {
  recording = !recording;
  if (recording) {
    start_button.innerHTML = 'stop';
    final_transcript = '';
    recog.lang = "en-US";
    recog.start();
  } else {
    start_button.innerHTML = 'start';
    recog.stop();
  }
});

var first_char = /\S/;
function capitalize(s) {
  return s.replace(first_char, function(m) { return m.toUpperCase(); });
}

var two_line = /\n\n/g;
var one_line = /\n/g;
function linebreak(s) {
  return s.replace(two_line, '<p></p>').replace(one_line, '<br>');
}