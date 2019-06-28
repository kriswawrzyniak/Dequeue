//Bounded Dequeue
//Kris Wawrzyniak
//

#ifndef _BOUNDED_DEQUEUE_H_
#define _BOUNDED_DEQUEUE_H_
#include "dequeue.h"
#include <stdexcept>

namespace myDequeue{
template <typename E>
class Bounded_Dequeue : public Dequeue<E> {
public:
	Bounded_Dequeue (size_t s);
	~Bounded_Dequeue() override;
	
	void push_front(E element) override;
	void push_back(E element) override;
	void pop_front(void) override;
	void pop_back(void) override;
	E peek_front(void) override;
	E peek_back(void) override;
	bool is_empty(void) override;
	bool is_full(void) override;
	size_t length(void) override;
	void clear(void) override;
	
#ifdef DEBUG
	E * const contents_as_array() override;
#endif
	
private:
	size_t size;
	E * const data; // Pointer to the container to hold the data
	size_t head = -1;
	size_t tail = -1;
	size_t next_index(size_t i);
	
};

//	Constructor/Destructor
//-----------------------------------------------
//

template <typename E>
	Bounded_Dequeue <E> :: Bounded_Dequeue(size_t s) : size(s), data(new E[s]){}

template <typename E>
	Bounded_Dequeue <E> :: ~Bounded_Dequeue() {
	delete [] data;
}

//	Operations
//-----------------------------------------------
//

//	push_front
template <typename E>
void Bounded_Dequeue <E> :: push_front( E element){
	if (is_full())
		throw std::runtime_error("Bounded_Dequeue<E>.push_front(): full");
	
	if(head == -1){
		head = 0;
		tail = 0;
	}
	else if(head == 0){
		head = size-1;
	}
	else{
		head = head-1;
	}
	data[head] = element;
	
}

//	push_back

template <typename E>
void Bounded_Dequeue <E> :: push_back(E element){
	if (is_full())
		throw std::runtime_error("Bounded_Dequeue<E>.push_back(): full");
	
	if(head == -1){
		head = 0;
		tail = 0;
	}
	else if(tail == size-1){
		tail = 0;
	}
	else{
		tail++;
	}
	data[tail] = element;
	
}

//	pop_front

template <typename E>
void Bounded_Dequeue <E> :: pop_front(){
	if(is_empty())
		throw std::runtime_error("Bounded_Dequeue<E>.pop_front(): empty");
	
	if(head==tail){
		head = -1;
		tail = -1;
	}
	else
		if(head == size-1)
			head = 0;
		else
			head = head+1;
	
}

//	pop_back

template <typename E>
void Bounded_Dequeue <E> :: pop_back(){
	if(is_empty())
		throw std::runtime_error("Bounded_Dequeue<E>.pop_back(): empty");
	
	if(head == tail){
		head = -1;
		tail = -1;
	}
	else if (tail == 0){
		tail = size-1;
	}
	else
		tail--;
	
}

//	peek_front

template <typename E>
E Bounded_Dequeue <E> :: peek_front(){
	if(is_empty())
		throw std::runtime_error("Bounded_Dequeue<E>.pop_front(): empty");
	
	return data[head];
}

//	peek_back

template <typename E>
E Bounded_Dequeue <E> :: peek_back(){
	if(is_empty())
		throw std::runtime_error("Bounded_Dequeue<E>.pop_front(): empty");
	
	return data[tail];
}

//	is_empty

template <typename E>
bool Bounded_Dequeue <E> :: is_empty(){
	return (head==-1);
}

//	is_full

template <typename E>
bool Bounded_Dequeue <E> :: is_full(){
	//return ((head == 0 && tail == size-1) || head == next_index(tail));
	
	return ((head==0 && tail==(size-1)) || head == (tail+1) || size==0);
}

//	length

template <typename E>
size_t Bounded_Dequeue <E> :: length(){
	if(head == -1)
		return 0;
	else if (head <= tail)
		return ((tail - head) + 1);
	else
		return (tail + (size-head) + 1);
}

//	clear

template <typename E>
void Bounded_Dequeue <E> :: clear(){
	head=-1;
	tail=0;
}

// next_index
template<typename E>
size_t Bounded_Dequeue <E> :: next_index(size_t i){
	
	if (++i == size){
		i = 0;
	}
	return i;
}

#ifdef DEBUG
template <typename E>
E * const Bounded_Dequeue <E> :: contents_as_array() {
	size_t const arr_length = length();
	E * const array = new E[arr_length];
	
	if (head == -1) return array;
	size_t j = head;
	for(size_t i = 0; i<=arr_length; ++i, j=next_index(j)){
		array[i] = data[j];
	}
	return array;
}
#endif
	
}
#endif
