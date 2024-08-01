# LinearBuffer
A simple buffer that can append a byte array or a single byte. After that is can be accessed like a normal array. 
Can only be cleared in total.
It can be used as a buffer for recieving packets from an interface.
Especially when the data could be recieved in chunks or byte by byte.
This could be the case for socket connections but also usb connections like a Arduino.

# Installation
For Linux you can add the library globally with the install script. Enter in the therminal
```
./install install
```
For removal use
```
./install remove
```
# Example code
```C++
/**
 * @file main.cpp
 * @author Jimmy van den Berg
 */

#include <iostream>
#include <LinearBuffer>

using namespace std;

int main(int argc, char** argv) {
    // Create two linear buffer objects.
    LinearBuffer<int, 10> buf;
    LinearBuffer<int, 10> buf2;

    // Print the number of available storage elements.
    cout << "Free = " << buf.getFree() << endl;

    // Initialize a test array.
    int arr[] = {5, 10, 3, -2, 5, 0, 0, 0, 0, 0};

    // Insert single elements using the set method.
    for (unsigned int i = 0; i < 10; ++i) {
        cout << "Actually set: " << buf.set(arr[i]) << endl;
        cout << "Free = " << buf.getFree() << endl;
    }

    // Clear the buffer.
    buf.clearAll();

    // Insert data in bulk from arr[5] to arr[9] twice.
    cout << "Actually set: " << buf.set(&arr[5], 5) << endl;
    cout << "Actually set: " << buf.set(&arr[5], 5) << endl;

    // Print the number of available storage elements.
    cout << "Free = " << buf.getFree() << endl;

    // Copy arr[0] to arr[4] into the second buffer.
    buf2.set(arr, 5);

    // Copy data from buf2 to buf.
    buf = buf2;

    // Print the content of buf.
    for (int i = 0; i < 10; ++i) {
        cout << buf[i] << endl;
    }

    return 0;
}
```
