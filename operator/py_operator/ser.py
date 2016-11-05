# arch -i386 python ser.py

# import sys
import Skype4Py
import serial

# This variable will get its actual value in OnCall handler
CallStatus = 0

# Here we define a set of call statuses that indicate a call has been either aborted or finished
CallIsFinished = set([Skype4Py.clsFailed, Skype4Py.clsFinished, Skype4Py.clsMissed, Skype4Py.clsRefused, Skype4Py.clsBusy, Skype4Py.clsCancelled])


def AttachmentStatusText(status):
    return skype.Convert.AttachmentStatusToText(status)


def CallStatusText(status):
    return skype.Convert.CallStatusToText(status)


# This handler is fired when status of Call object has changed
def OnCall(call, status):
    global CallStatus
    CallStatus = status
    print 'Call status: ' + CallStatusText(status)


# This handler is fired when Skype attatchment status changes
def OnAttach(status):
    print 'API attachment status: ' + AttachmentStatusText(status)
    if status == Skype4Py.apiAttachAvailable:
        skype.Attach()

skype = Skype4Py.Skype()
skype.OnAttachmentStatus = OnAttach
skype.OnCallStatus = OnCall

if not skype.Client.IsRunning:
    print 'Starting Skype..'
    skype.Client.Start()

print 'Connecting to Skype..'
skype.Attach()


ser = serial.Serial('/dev/tty.usbmodem1411', 9600)
no = ''

while True:
    # print ser.read()
    inByte = ser.read()
    print inByte

    if inByte == '.':
        no = ''
    else:
        no += inByte

    print no

    if len(no) > 9:
        callno = '+1' + no
        print 'Calling ' + callno + '..'
        currentCall = skype.PlaceCall(callno)
        no = ''

        while not CallStatus in CallIsFinished:
            inByte2 = ser.read()
            # print inByte2
            if inByte2 == '.':
                currentCall.Finish()
                break
            pass
