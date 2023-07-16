# NativeFlowBenchExtended

Verified and tested on a realworld Android 9 phone

### naitve socket leak

on PC, connect phone in adb and listen on 3000 before launch the app.
```
adb reverse tcp:3000 tcp:3000
nc -l 3000
```
