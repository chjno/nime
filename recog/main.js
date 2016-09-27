var nlp = window.nlp_compromise





socket.on('sentiment', function(obj) {
  // console.log(obj);
});

var finalSpans = [];
var interimSpans = [];

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
    interim_transcript = '';
    var newFinal = false;
    var newInterim = false;
    var finalHTML = '';

    for (var i = event.resultIndex; i < event.results.length; ++i) {
      if (event.results[i].isFinal) {
        final_transcript = event.results[i][0].transcript.trim() + ' ';
        interim_transcript = '';
        newFinal = true;
        newInterim = true;
      } else {
        interim_transcript += event.results[i][0].transcript.trim() + ' ';
        newInterim = true;
      }
    }
    final_transcript = capitalize(final_transcript);
    // final_span.innerHTML = linebreak(final_transcript);
    // interim_span.innerHTML = linebreak(interim_transcript);


    if (newFinal) {
      socket.emit('new final', final_transcript);

      for (var j = 0; j < finalSpans.length; j++) {
        results.removeChild(finalSpans[j]);
      }

      var nlpObj = nlp.sentence(final_transcript);
      finalSplit = [];
      finalPos = [];
      for (var m = 0; m < nlpObj.terms.length; m++) {
        finalSplit.push(nlpObj.terms[m].text);
        if ('Noun' in nlpObj.terms[m].pos) {
          finalPos.push('Noun');
        } else if ('Verb' in nlpObj.terms[m].pos) {
          finalPos.push('Verb');
        } else {
          finalPos.push('Other');
        }
      }

      // console.log(nlpObj);
      // console.log(finalSplit);
      // console.log(finalPos);

      finalSpans = [];
      for (var i = 0; i < finalSplit.length; i++) {
        var span = document.createElement('span');
        span.className = 'final';
        span.innerHTML = finalSplit[i];
        finalSpans.push(span);
        results.insertBefore(span, divider);
      }
      genBeat(finalPos);
      newFinal = false;
    }

    if (newInterim) {
      socket.emit('new interim', interim_transcript);

      for (var k = 0; k < interimSpans.length; k++) {
        results.removeChild(interimSpans[k]);
      }
      interimSpans = [];
      // interimSplit = interim_transcript.split(' ');
      if (interim_transcript != '') {
        interimSplit = interim_transcript.trim().match(/(?=\S*['-])([a-zA-Z'-]+)|\w+|\W/g);
        for (var l = 0; l < interim_transcript.length; l++) {
          var span = document.createElement('span');
          span.className = 'interim';
          span.innerHTML = interim_transcript[l];
          interimSpans.push(span);
          results.appendChild(span);
        }
        genNotes(interim_transcript);
      } else {
        // pattern2.stop();
        // synth.triggerRelease(synth.now());
      }
      // console.log(interimSplit);
      // console.log(interimSpans);
  
      newInterim = false;
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