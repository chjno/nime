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

# Let's see if we were started with a command line parameter..
# try:
#     CmdLine = '+1' + sys.argv[1]
# except:
#     print 'Missing command line parameter'
#     sys.exit()

# Creating Skype object and assigning event handlers..
skype = Skype4Py.Skype()
skype.OnAttachmentStatus = OnAttach
skype.OnCallStatus = OnCall

# Starting Skype if it's not running already..
if not skype.Client.IsRunning:
    print 'Starting Skype..'
    skype.Client.Start()

# Attatching to Skype..
print 'Connecting to Skype..'
skype.Attach()

# Make the call
# print 'Calling ' + CmdLine + '..'
# skype.PlaceCall(CmdLine)


no = ''
listening = True

ser = serial.Serial('/dev/tty.usbmodem1411', 9600)
while listening:
    # print ser.readline()
    # print ser.read()
    no += ser.read()
    print no

    if len(no) > 9:
        listening = False
        callno = '+1' + no
        skype.PlaceCall(callno)

        # Loop until CallStatus gets one of "call terminated" values in OnCall handler
        while not CallStatus in CallIsFinished:
            pass


FIXME
# don't pay attention to input while phone call is active
# once "Call status: Finished" start listening for input again
