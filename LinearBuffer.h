
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
	size_t set(const T* data);
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
	size_t set(const T* data, size_t size);
	/**
	 * @brief      Gets up to size number of numbers from the buffer.
	 *
	 * @param      data  Pointer to the array where the numbers will be stored.
	 * @param[in]  size  The size of the buffer. May also be smaller to limit the number of bytes retrieved.
	 *
	 * @return     Number of numbers stored. Zero indicates an empty buffer.
	 */
	size_t get(T* data, size_t size);
	/**
	 * @brief      Clears all elements in buffer.
	 */
	void clearAll();
	/**
	 * @brief      Copies behavior of an normal array.
	 *
	 * @param[in]  idx   The index to access.
	 *
	 * @return     Value at idx.
	 */
	T& operator[](size_t idx);
	/**
	 * @brief      Copies behavior of an normal array.
	 *
	 * @param[in]  idx   The index to access.
	 *
	 * @return     Value at idx.
	 */
	T operator[](size_t idx) const;
	template<size_t otherSize>
	LinearBuffer& operator=(LinearBuffer<T, otherSize> other){
		size_t copySize = (currentIndex < other.currentIndex ? currentIndex : other.currentIndex);
		for (int i = 0; i < copySize; ++i){
			storedData[i] = other.storedData[i];
		}
		return *this;
	}
	/**
	 * @brief      Finds a sequence of data in the buffer.
	 *
	 * @param[in]  c     The pattern it needs to search for
	 * @param[in]  size  The size of the pattern.
	 *
	 * @return     @p true if found. @p false otherwise.
	 */
	bool findSequence(const T* c, size_t size);
	LinearBuffer& operator=(LinearBuffer<T, bufferSize> other);
	/**
	 * @brief      Gets how many numbers are stored in the buffer.
	 *
	 * @return     Amount of numbers stored.
	 */
	size_t getStored();
	/**
	 * @brief      Gets free places in buffer.
	 *
	 * @return     Free space.
	 */
	unsigned int getFree();
	/**
	 * @brief      Determines if full.
	 *
	 * @return     True if full, False otherwise.
	 */
	bool isFull();
	/**
	 * @brief      Determines if empty.
	 *
	 * @return     True if empty, False otherwise.
	 */
	bool isEmpty();
private:
	T storedData[bufferSize];
	size_t currentIndex = 0;
};

#endif //_LINEARBUFFER_H_

template<typename T, size_t bufferSize>
size_t LinearBuffer<T, bufferSize>::set(const T* data){
	if(isFull() == false){
		storedData[currentIndex++] = *data;
		return 1;
	}
	else
		return 0;
}
template<typename T, size_t bufferSize>
size_t LinearBuffer<T, bufferSize>::set(const T* data, size_t size){
	size_t currentFree = getFree();
	if(size > currentFree)
		size = currentFree;
	for (unsigned int i = 0; i < size; ++i){
		storedData[currentIndex++] = data[i];
	}
	return size;
}
template<typename T, size_t bufferSize>
size_t LinearBuffer<T, bufferSize>::get(T* data, size_t size){
	if(size > currentIndex){
		size = currentIndex;
	}
	for (int i = 0; i < size; ++i){
		data[i] = storedData[i];
	}
	return size;
}
template<typename T, size_t bufferSize>
void LinearBuffer<T, bufferSize>::clearAll(){
	currentIndex = 0;
}
template<typename T, size_t bufferSize>
T& LinearBuffer<T, bufferSize>::operator[](size_t idx){
	if(idx < currentIndex)
		return storedData[idx];
	else{
		return storedData[0];
	}
}
template<typename T, size_t bufferSize>
T LinearBuffer<T, bufferSize>::operator[](size_t idx) const{
	if(idx < currentIndex)
		return storedData[idx];
	else{
		return storedData[0];
	}
}
template<typename T, size_t bufferSize>
bool LinearBuffer<T, bufferSize>::findSequence(const T* c, size_t size){
	if(size > getStored()){
		return false;
	}
	else{
		size_t itemsSearched = 0;
		size_t itemsFound = 0;
		while(itemsSearched < getStored()){
			if(storedData[itemsSearched] == c[itemsFound]){
				itemsFound++;
			}
			else{
				itemsFound = 0;
			}
			itemsSearched++;
			if(itemsFound == size){
				return true;
			}
		}
		return false;
	}
}
template<typename T, size_t bufferSize>
LinearBuffer<T, bufferSize>& LinearBuffer<T, bufferSize>::operator=(LinearBuffer<T, bufferSize> other){
	size_t copySize = (currentIndex < other.currentIndex ? currentIndex : other.currentIndex);
	for (unsigned int i = 0; i < copySize; ++i){
		storedData[i] = other.storedData[i];
	}
	return *this;
}
template<typename T, size_t bufferSize>
size_t LinearBuffer<T, bufferSize>::getStored(){
	return currentIndex;
}
template<typename T, size_t bufferSize>
unsigned int LinearBuffer<T, bufferSize>::getFree(){
	return bufferSize - currentIndex;
}
template<typename T, size_t bufferSize>
bool LinearBuffer<T, bufferSize>::isFull(){
	return (currentIndex == bufferSize);
}
template<typename T, size_t bufferSize>
bool LinearBuffer<T, bufferSize>::isEmpty(){
	return (currentIndex == 0);
}
