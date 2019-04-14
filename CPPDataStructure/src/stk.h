#include <algorithm>
#include <memory>

template<typename T>
class DoublyLinkedList;

template<typename T>
class Stack {
private:
	std::unique_ptr<DoublyLinkedList<T>> items;

public:
	Stack() {
		this->items = std::make_unique<DoublyLinkedList<T>>();
	}

	virtual ~Stack() {}

	void push(T value){
		this->items->push_front(value);
	}

	T pop (){
		auto value = this->items->front();
		this->items->pop_front();
		return value;
	}

	T top(){
		return this->items->front();
	}

	int size(){
		return this->items->count();
	}
};
