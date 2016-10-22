var creds = require('./creds.js')

// Download the Node helper library from twilio.com/docs/node/install
// These vars are your accountSid and authToken from twilio.com/user/account
var accountSid = creds.id;
var authToken = creds.token;
var client = require('twilio')(accountSid, authToken);

client.calls.create({
    url: "http://demo.twilio.com/docs/voice.xml",
    to: "+14155551212",
    from: "+13476258884"
}, function(err, call) {
    process.stdout.write(call.sid);
});
