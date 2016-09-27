Tone.Transport.start();
var synth = new Tone.Synth().toMaster();

var tap = new Tone.Player({
  "url": 'tap.wav',
  "retrigger": true
}).toMaster();

var hihat = new Tone.Player({
  "url": 'hihat.wav',
  "retrigger": true
}).toMaster();

var bass = new Tone.Player({
  "url": 'bass.wav',
  "retrigger": true
}).toMaster();

var synth = new Tone.Synth({

}).toMaster();

var dict = {
  'a': 'C2',
  'b': 'D2',
  'c': 'E2',
  'd': 'F2',
  'e': 'G2',
  'f': 'A2',
  'g': 'B2',
  'h': 'C3',
  'i': 'D3',
  'j': 'E3',
  'k': 'F3',
  'l': 'G3',
  'm': 'A3',
  'n': 'B3',
  'o': 'C4',
  'p': 'D4',
  'q': 'E4',
  'r': 'F4',
  's': 'G4',
  't': 'A4',
  'u': 'B4',
  'v': 'C5',
  'w': 'D5',
  'x': 'E5',
  'y': 'F5',
  'z': 'G5'
}

function getRandomColor() {
  var letters = '0123456789ABCDEF';
  var color = '#';
  for (var i = 0; i < 6; i++ ) {
      color += letters[Math.floor(Math.random() * 16)];
  }
  return color;
}

var array = [];

function genBeat(array) {
  // console.log(array);
  pattern.values = array;
  pattern.start();
}

var pattern = new Tone.Pattern(function(time, note){
  // console.log(note);
  if (this.index == 0) {
    finalSpans[finalSpans.length - 1].style.color = 'black';
  } else {
    finalSpans[this.index - 1].style.color = 'black';
  }
  switch (note) {
    case 'Noun':
      bass.start();
      finalSpans[this.index].style.color = 'CornflowerBlue ';
      break;
    case 'Verb':
      tap.start();
      finalSpans[this.index].style.color = 'chartreuse';
      break;
    case 'Other':
      hihat.start();
      finalSpans[this.index].style.color = 'orange';
      break;
  }
}, array);
pattern.interval = '4n'

var notes = [];

function genNotes(string) {
  console.log('string ' + string);
  if (string != '') {
    notes = string.split('');
    // for (var i = 0; i < string.length; i++) {
    //   notes.push(dict[string[i]]);
    // }
    // console.log(notes);
    pattern2.values = notes;
    pattern2.start();
  } else {
    // pattern2.stop();
    // synth.triggerRelease(synth.now());
  }
}

var pattern2 = new Tone.Pattern(function(time, note){
  if (interimSpans.length > 0) {
    interimSpans[this.index].style.color = getRandomColor();
    if (this.index == 0) {
      interimSpans[interimSpans.length - 1].style.color = 'gray';
    } else {
      interimSpans[this.index - 1].style.color = 'gray';
    }
  }
  if (dict.hasOwnProperty(note)) {
    synth.triggerAttackRelease(dict[note]);
  }
  // console.log(note);
}, notes);
pattern2.interval = '8n'