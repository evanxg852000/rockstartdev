#include <algorithm>
#include <memory>


template<typename T>
class DoublyLinkedList {
private:
	struct Node{
		T data;
		std::shared_ptr<Node> prev;
		std::shared_ptr<Node> next;
		Node(T data){
			this->data = data;
			this->prev = nullptr;
			this->next = nullptr;
		}
	};

	std::shared_ptr<Node> head;
	std::shared_ptr<Node> tail;
	int size;

public:

	void push_front(T value){
		auto node = std::make_shared<Node>(value);
		if(this->size == 0){
			this->head = this->tail = node;
			this->size++;
			return;
		}

		this->size++;
		node.get()->next = this->head;
		this->head.get()->prev = node;
		this->head = node;
	}

	void  push_back(T value){
		auto node = std::make_shared<Node>(value);
		if(this->size == 0){
			this->head = this->tail = node;
			this->size++;
			return;
		}

		this->size++;
		this->tail.get()->next = node;
		node.get()->prev = this->tail;
		this->tail = node;
	}

	T front() {
		if(!this->head)
			throw std::out_of_range ("Out of range exception");
		return this->head.get()->data;
	}

	T back() {
		if(!this->tail)
			throw std::out_of_range ("Out of range exception");
		return this->tail.get()->data;

	}

	void pop_front(){
		if(this->size == 0)
			throw std::out_of_range ("Out of range exception");

		this->size--;
		if(this->size == 1){
			this->head = this->tail = nullptr;
			return;
		}

		auto temp = this->head.get()->next;
		temp.get()->prev = nullptr;
		this->head = temp;
	}

	void pop_back(){
		if(this->size == 0)
			throw std::out_of_range ("Out of range exception");

		this->size--;
		if(this->size == 1){
			this->head = this->tail = nullptr;
		}

		auto temp = this->tail.get()->prev;
		temp.get()->next = nullptr;
		this->tail = temp;
	}

	int search(T value){
		auto idx = 0;
		auto curr = this->head;
		while(curr){
			if(curr.get()->data == value){
				return idx;
			}
			curr = curr.get()->next;
			idx++;
		}
		return -1;
	}

	int count(){
		return this->size;
	}

};

