
#ifndef _LINEARBUFFER_H_
#define _LINEARBUFFER_H_

#include <stddef.h>

/**
 * @brief      Class for a linear buffer.
 *
 *             This type of class can only append data and when needed can only
 *             be cleared totally.
 *
 * @tparam     T           Type to buffer
 * @tparam     bufferSize  size of buffer
 */
template<typename T, size_t bufferSize>
class LinearBuffer
{
public:
	/**
	 * @brief      Stores one number in the buffer.
	 *
	 * @param[in]  data  Pointer to the new value to be stored.
	 *
	 * @return     Number of numbers retrieved from buffer.(1 or 0 when full)
	 */
	size_t set(const T* data){
		if(isFull() == false){
			storedData[currentIndex++] = *data;
			return 1;
		}
		else
			return 0;
	}
	/**
	 * @brief      Stores up to size numbers in the buffer.
	 *
	 * @note       This function will never store more numbers that available in
	 *             buffer.
	 *
	 * @param[in]  data  Pointer to then numbers to be stored.
	 * @param[in]  size  The size
	 *
	 * @return     Number of numbers actually stored. Smaller that size
	 *             indicates a full buffer.
	 */
	size_t set(const T* data, size_t size){
		size_t currentFree = getFree();
		if(size > currentFree)
			size = currentFree;
		for (unsigned int i = 0; i < size; ++i){
			storedData[currentIndex++] = data[i];
		}
		return size;
	}
	/**
	 * @brief      Gets up to size number of numbers from the buffer.
	 *
	 * @param      data  Pointer to the array where the numbers will be stored.
	 * @param[in]  size  The size of the buffer. May also be smaller to limit the number of bytes retrieved.
	 *
	 * @return     Number of numbers stored. Zero indicates an empty buffer.
	 */
	size_t get(T* data, size_t size){
		if(size > currentIndex){
			size = currentIndex;
		}
		for (int i = 0; i < size; ++i){
			data[i] = storedData[i];
		}
		return size;
	}
	void clearAll(){
		currentIndex = 0;
	}
	/**
	 * @brief      Copies behavior of an normal array.
	 *
	 * @param[in]  idx   The index to access.
	 *
	 * @return     Value at idx.
	 */
	T operator[](size_t idx){
		if(idx < currentIndex)
			return storedData[idx];
		else{
			return 0;
		}
	}
	template<size_t otherSize>
	LinearBuffer& operator=(LinearBuffer<T, otherSize> other){
		size_t copySize = (currentIndex < other.currentIndex ? currentIndex : other.currentIndex);
		for (int i = 0; i < copySize; ++i){
			storedData[i] = other.storedData[i];
		}
	}
	LinearBuffer& operator=(LinearBuffer<T, bufferSize> other){
		size_t copySize = (currentIndex < other.currentIndex ? currentIndex : other.currentIndex);
		for (int i = 0; i < copySize; ++i){
			storedData[i] = other.storedData[i];
		}
	}
	/**
	 * @brief      Gets how many numbers are stored in the buffer.
	 *
	 * @return     Amount of numbers stored.
	 */
	size_t getStored(){
		return currentIndex;
	}
	/**
	 * @brief      Gets free places in buffer.
	 *
	 * @return     Free space.
	 */
	unsigned int getFree(){
		return bufferSize - currentIndex;
	}
	/**
	 * @brief      Determines if full.
	 *
	 * @return     True if full, False otherwise.
	 */
	bool isFull(){
		return (currentIndex == bufferSize);
	}
	/**
	 * @brief      Determines if empty.
	 *
	 * @return     True if empty, False otherwise.
	 */
	bool isEmpty(){
		return (currentIndex == 0);
	}
private:
	T storedData[bufferSize];
	size_t currentIndex = 0;
};

#endif //_LINEARBUFFER_H_
