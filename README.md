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
 * @author     Jimmy van den Berg
 */
#include <iostream>
#include <LinearBuffer>

using namespace std;

int main(int argc, char** argv){
	// Make two linear buffer objects.
	LinearBuffer<int, 10> buf;
	LinearBuffer<int, 10> buf2;
	// Print how many elements are currently available for storage
	cout << "Free = " << buf.getFree() << endl;
	// Make a test array used to play with.
	int arr[] = {5,10,3,-2,5,0,0,0,0,0};
	// Insert single element using set.
	for (unsigned int i = 0; i < 11; ++i)
	{
		cout << "Actually set: " << buf.set(arr) << endl;
		cout << "Free = " << buf.getFree() << endl;
	}
	// Clear the buffer. This is just setting the index to zero so it is really
	// quick.
	buf.clearAll();
	// Insert data in bulk. The data used is a pointer to arr[5]. This adds
	// effectively element [4] through element [9] two times making the whole
	// buffer zero.
	cout << "Actually set: " << buf.set(&arr[5], 5) << endl;
	cout << "Actually set: " << buf.set(&arr[5], 5) << endl;
	// Free buffer again.
	cout << "Free = " << buf.getFree() << endl;
	// Copy arr[0] to arr[4] into the buffer.
	buf2.set(arr, 5);
	// Copy data from buf2 to buf. It only copies as far as the least filled
	// buffer.
	buf = buf2;
	// Print content of buf.
	for (int i = 0; i < 10; ++i)
	{
		cout << buf[i] << endl;
	}
	return 0;
}
```
