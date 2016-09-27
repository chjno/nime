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

var notes = [];

function genNotes(string) {
  notes = string.split('');
  pattern.values = notes;
  pattern.start();
}

var pattern = new Tone.Pattern(function(time, note){
  finalSpans[this.index].style.color = 'red';
  if (this.index == 0) {
    finalSpans[finalSpans.length - 1].style.color = 'black';
  } else {
    finalSpans[this.index - 1].style.color = 'black';
  }
  if (dict.hasOwnProperty(note)) {
    tap.start();
  } else if (note.match(/[.,\/#!$%\^&\*;:{}=\-_`'~()]/) != null) {
    hihat.start();
  } else if (note == ' ') {

  } else if (note == note.toUpperCase()) {
    bass.start();
  }
  // console.log(note);
}, notes);
pattern.interval = '2n'