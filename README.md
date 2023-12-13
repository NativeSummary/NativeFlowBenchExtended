# NativeFlowBenchExtended

NativeFlowExtended is an extended native code benchmark with 10 apps.
Apps in `NativeFlowBench` and `JucifyBench` mainly focus on Java-side manipulation of native code. Actually, native methods of most test cases have exact translations of Java code, which is completely not the case in real-world apps.
Based on our investigation of real-world apps, we found the following common JNI usage patterns that `NativeFlowBench` and `JucifyBench` did not cover, which are added in the benchmark by us:

- **Native copy**: The app converts a Java string into a C string, copies it to heap-allocated memory using a `for` loop, creates and returns a new Java string. To handle this case, the analyzer should model the heap allocation functions, e.g., `malloc`.

- **Native copy strdup**: Same as above, but the app directly uses `strdup` to copy C string.

- **Native encode**: It is similar to native copy, but it uses `base64` encoding instead of direct copying. To handle it, the analyzer should discover the dataflow of the encoding process.

- **Native file leak, and native socket leak**: Apps use different native-specific APIs to leak information.

- **Native global ID**: 
The app pre-calculates the Method IDs and Class IDs used in JNI calls in `JNI\_OnLoad`. It requires the analyzer to be able to handle cross-function data flow using global variables. This pattern is widely used in native libraries (e.g., a popular graphics library `libgdx`) to increase performance.

- **Native handle**: 
In this case, pointers to the native heap can be passed to the Java side by converting it to `jlong`. A sample comes from our investigation of the source code of `android-gif-drawable`.

- **Native array region, native array elements, and native direct buffer**:
Each app uses `GetByteArrayRegion`, `GetByteArrayElements` and `GetDirectBufferAddress` to pass data, respectively. 
JNI allows native code to direct access the internal buffer of `nio.ByteBuffer`, modifications of the buffer are directly visible. 


Verified and tested on a realworld Android 9 phone

### naitve socket leak

on PC, connect phone in adb and listen on 3000 before launch the app.
```
adb reverse tcp:3000 tcp:3000
nc -l 3000
```
