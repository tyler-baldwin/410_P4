#include <string>
#include <thread>
#include "pthread.h"
#include "stdlib.h"
#include "../includes/externs.h"
#include "../includes/waiter.h"

using namespace std;
//ID is just a number used to identify this particular baker
//(used with PRINT statements)
//filename is what waiter reads in orders from
Waiter::Waiter(int id, std::string filename) :
		id(id), myIO(filename) {
	//b_WaiterIsFinished = false;
}

Waiter::~Waiter() {
	//b_WaiterIsFinished = true;

}

//gets next Order from file_IO
//if return == SUCCESS then anOrder
//contains new order
//otherwise return contains fileIO error
int Waiter::getNext(ORDER &anOrder) {
	return myIO.getNext(anOrder);
}
//contains a loop that will get orders from filename one at a time
//then puts them in order_in_Q then signals baker(s) using cv_order_inQ
//so they can be consumed by baker(s)
//when finished exits loop and signals baker(s) using cv_order_inQ that
//it is done using b_WaiterIsFinished
void Waiter::beWaiter() {
	//this_thread::sleep_for(chrono::milliseconds(2000));

	//Tyler Baldwin did this
	ORDER ord;
	{
	unique_lock<mutex> lck(mutex_order_inQ);
	b_WaiterIsFinished = false;
	//cout << "waiter is awake" << endl;
	}
	while (true) {
		int result = getNext(ord);
		if (result != SUCCESS) {
			break;
		}
		unique_lock<mutex> lck(mutex_order_inQ);
		order_in_Q.push(ord);
		lck.unlock();
		//cout << "waiter added an order" << ord.order_number << endl;
		//this_thread::sleep_for(chrono::milliseconds(200));
		cv_order_inQ.notify_all();
	}
	{
		unique_lock<mutex> lck(mutex_order_inQ);
		b_WaiterIsFinished = true;
		cv_order_inQ.notify_all();

	}
//	while(!order_in_Q.empty()){
////		unique_lock<mutex> lck(mutex_order_inQ);
////		cv_order_inQ.wait(lck);
//	}
//	b_WaiterIsFinished = false;


}

