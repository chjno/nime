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

function colorClass(arr, index, color) {
  for (var i = 0; i < arr[index].length; i++) {
    arr[index][i].style.color = color;
  }

  if (index > 0) {
    // console.log(arr[index - 1]);
    // for (var j = 0; j < arr[index - 1].length; j++) {
    //   arr[index - 1][i].style.color = 'black';
    // }
  }

  // if (index == 0) {
  //   for (var j = 0; j < obj[obj.length - 1].length; j++) {
  //     obj[index][i].style.color = 'black';
  //   }  
  // } else {
  //   for (var j = 0; j < obj[index - 1].length; j++) {
  //     obj[index][i].style.color = 'black';
  //   }
  // }
}

var pattern = new Tone.Pattern(function(time, note){
  if (this.index == 0) {
    colorClass(finalWordSpans, finalWordSpans.length - 1, 'black');
  } else {
    colorClass(finalWordSpans, this.index - 1, 'black');
  }
  switch (note[0]) {
    case 'Noun':
      bass.start();
      colorClass(finalWordSpans, this.index, 'cornflowerblue');
      break;
    case 'Verb':
      tap.start();
      colorClass(finalWordSpans, this.index, 'chartreuse');
      break;
    case 'Other':
      hihat.start();
      colorClass(finalWordSpans, this.index, 'orange');
      break;
  }
}, array);
pattern.interval = '4n'

var notes = [];

function genNotes(string) {
  // console.log('string ' + string);
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
    // interimSpans[this.index].style.color = getRandomColor();
    interimSpans[this.index].style.color = 'red';
    if (this.index == 0) {
      interimSpans[interimSpans.length - 1].style.color = 'gray';
    } else {
      interimSpans[this.index - 1].style.color = 'gray';
    }
  } else {
    // console.log(finalSpans[this.index]);
    // finalSpans[this.index].style.color = getRandomColor();
    finalSpans[this.index].style.color = 'red';
    if (this.index == 0) {
      finalSpans[finalSpans.length - 1].style.color = 'black';
    } else {
      finalSpans[this.index - 1].style.color = 'black';
    }
  }
  if (dict.hasOwnProperty(note)) {
    synth.triggerAttackRelease(dict[note]);
  }
  // console.log(note);
}, notes);
pattern2.interval = '8n'