#include <algorithm>
#include <memory>

template<typename T>
class DoublyLinkedList;

template<typename T>
class Queue {
private:
	std::unique_ptr<DoublyLinkedList<T>> items;

public:
	Queue() {
		this->items = std::make_unique<DoublyLinkedList<T>>();
	}

	virtual ~Queue() {}

	void enqueue(T value){
		this->items->push_back(value);
	}

	T dequeue (){
		auto value = this->items->front();
		this->items->pop_front();
		return value;
	}

	T front(){
		return this->items->front();
	}

	int size(){
		return this->items->count();
	}
};
