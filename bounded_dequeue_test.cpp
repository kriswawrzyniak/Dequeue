//
////Dequeue Test
//Kris Wawrzyniak
//

#include <iostream>
//#include "dequeue.h"
#include "bounded_dequeue.h"
#include "dequeue.h"
#define DEBUG

using namespace myDequeue;

int const values [] = {0, 1, 2, 3, 4, 5 , 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};

//-----------------------------------------------
template <typename E>
bool test_contents(Dequeue<E>& dequeue, E const * expected, size_t count){
	if (dequeue.length() != count){
		std::cout << "Failed: |DQ| == " << dequeue.length() << " expected length == " << count << std::endl;
		return false;
	}
	E* const contents = dequeue.contents_as_array();
	for (int i = 0; i != count; ++i){
		if(contents[i] != expected[i]){
			std::cout << "Failed: DQ[" << i << "] == " << contents[i] << " expected DQ [" << i << "] == " << expected[i] << std::endl;
			return false;
		}
	}
	return true;
}

//-----------------------------------------------
bool test_size_0_dequeue(Dequeue<int>& dequeue){
	
	dequeue.clear();
	
	//bool passed = (dequeue.length() == 0);
	if(! dequeue.is_empty()){std:: cout << "testing" << std::endl; return false;}
	if(! dequeue.is_full()) {std:: cout << "testing1" << std::endl; return false;}
	
	try{
		dequeue.push_front(1);
		return false;
	}
	catch (std::runtime_error const & e) {}
	
	try{
		dequeue.push_back(1);
		return false;
	}
	catch (std::runtime_error const & e){}
	
	try{
		dequeue.pop_front();
		return false;
	}
	catch (std::runtime_error const & e){}
	
	try{
		dequeue.pop_back();
		return false;
	}
	catch (std::runtime_error const & e){}
	
	try{
		dequeue.peek_front();
		return false;
	}
	catch (std::runtime_error const & e){}
	
	try{
		dequeue.peek_back();
		return false;
	}
	catch (std::runtime_error const & e){}
	
	

	return true;
}

//-----------------------------------------------
bool test_size_1_dequeue(Dequeue<int>& dequeue){
	dequeue.clear();
	
	//DQ is empty, size 1
	if (dequeue.length() != 0) return false;
	if (dequeue.is_empty() == false) return false;
	if (dequeue.is_full() == true) return false;
	
	//Test push_front(size_t)
	dequeue.push_front(1);
	if (dequeue.length() != 1) return false;
	if (dequeue.is_empty()) return false;
	if (!dequeue.is_full()) return false;
	if(!test_contents<int>(dequeue, values+1, 1)) return false;
	try{
		dequeue.push_front(2);
	}
	catch (std::runtime_error const & e){}
	try{
		dequeue.push_back(2);
		return false;
	}
	catch(std::runtime_error const & e){}
	
	dequeue.pop_back();
	if (!dequeue.is_empty()) return false;
	
	dequeue.clear();
	
	//Test push_back(size_t)
	dequeue.push_back(1);
	if (dequeue.length() != 1) return false;
	if (dequeue.is_empty()) return false;
	if (!dequeue.is_full()) return false;
	if(!test_contents<int>(dequeue, values+1, 1)) return false;
	try{
		dequeue.push_front(2);
		return false;
	}
	catch (std::runtime_error const & e){}
	try{
		dequeue.push_back(2);
	}
	catch(std::runtime_error const & e){}
	
	dequeue.pop_front();
	if(!dequeue.is_empty()) return false;
	
	dequeue.clear();
	
	//test pop_front
	try{
		dequeue.pop_front();
		return false;
	}
	catch (std::runtime_error const & e){}
	
	//test pop_back
	try{
		dequeue.pop_back();
		return false;
	}
	catch (std::runtime_error const & e){}
	
	
	//Do some other shit probably here for the wrapping
	return true;
}

//-----------------------------------------------
bool test_size_5_dequeue(Dequeue<int>& dequeue){
	dequeue.clear();

	//DQ is empty, size 5
	if (dequeue.length() != 0) return false;
	if (dequeue.is_empty() == false) return false;
	if (dequeue.is_full() == true) return false;
	
	
	dequeue.push_front(5);
	dequeue.push_front(4);
	dequeue.push_front(3);
	dequeue.push_front(2);
	dequeue.push_front(1);
	

	if(dequeue.peek_front() != 1) return false;
	if(dequeue.peek_back() != 5) return false;
	
	if(dequeue.length() != 5) return false;
	if(!dequeue.is_full()) return false;
	if(dequeue.is_empty()) return false;
	
	
	if(!test_contents<int>(dequeue, values+1, 5)) return false;
	
	try{
		dequeue.push_front(0);
	}
	catch (std::runtime_error const & e){}
	try{
		dequeue.push_back(6);
		return false;
	}
	catch(std::runtime_error const & e){}
	
	dequeue.pop_back();
	if(dequeue.length() != 4) return false;
	if(!test_contents<int>(dequeue, values+1, 4)) return false;
	
	dequeue.pop_back();
	if(dequeue.length() != 3) return false;
	if(!test_contents<int>(dequeue, values+1, 3)) return false;
	
	dequeue.push_back(4);
	dequeue.push_back(5);
	if(dequeue.length() != 5) return false;
	if(!dequeue.is_full()) return false;
	if(dequeue.is_empty()) return false;
	if(!test_contents<int>(dequeue, values+1, 5)) return false;
	
	dequeue.pop_front();
	if(dequeue.length() != 4) return false;
	if(!test_contents<int>(dequeue, values+2, 4)) return false;
	
	dequeue.pop_front();
	if(dequeue.length() != 3) return false;
	if(!test_contents<int>(dequeue, values+3, 3)) return false;
	
	dequeue.push_back(6);
	if(dequeue.length() != 4) return false;
	if(!test_contents<int>(dequeue, values+3, 4)) return false;
	
	dequeue.push_back(7);
	if(dequeue.length() != 5) return false;
	if(!test_contents<int>(dequeue, values+3, 5)) return false;
	if(!dequeue.is_full()) return false;
	if(dequeue.is_empty()) return false;
	
	dequeue.clear();
	if (dequeue.length() != 0) return false;
	if (dequeue.is_empty() == false) return false;
	if (dequeue.is_full() == true) return false;
	
	return true;
}

template <typename T>
bool test_queue (void){
	bool all = true;
	std::cout << "~ Bounded_Queue ~" << std::endl;
	
	T t0(0);
	bool passed = test_size_0_dequeue(t0);
	all = all && passed;
	std::cout << (passed ? "PASSED" : "FAILED") << " test: size 0 dequeue" << std::endl;
	
	T t1(1);
	 passed = test_size_1_dequeue(t1);
	all = all && passed;
	std::cout << (passed ? "PASSED" : "FAILED") << " test: size 1 dequeue" << std::endl;
	
	T t5(5);
	 passed = test_size_5_dequeue(t5);
	all = all && passed;
	std::cout << (passed ? "PASSED" : "FAILED") << " test: size 5 dequeue" << std::endl;
	
	return all;
	
}

int main (void){
	
	bool all = test_queue <myDequeue::Bounded_Dequeue<int>>();
	
	std::cout << "-----------------------------------------------" << std::endl;
	std::cout << (all ? "*** ALL TESTS PASSED" : "*** AT LEAST ONE TEST FAILED") << std::endl;
	
	return 0;
}

