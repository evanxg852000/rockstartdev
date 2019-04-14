#include <memory>
#include <algorithm>

template<typename T>
class SinglyLinkedList {
private:
	struct Node{
			T data;
			std::shared_ptr<Node> next;
			Node(T data){
				this->data = data;
				this->next = nullptr;
			}
	};

	std::shared_ptr<Node> head;
	std::shared_ptr<Node> tail;
	int size;

	std::shared_ptr<Node>  _reverse(std::shared_ptr<Node>  node){
		if(!node)
			return nullptr;

		if(!node.get()->next){
			this->head.get()->next = nullptr;
			this->tail = this->head;
			this->head = node;
			return node;
		}

		auto temp = this->_reverse(node.get()->next);
		node.get()->next = nullptr;
		temp.get()->next = node;

		return node;
	}

public:
	SinglyLinkedList<T>(){
		this->size = 0;
		this->head = nullptr;
		this->tail = nullptr;
	}

	T get(int idx){
		int ctr = 0;
		auto curr = this->head;
		while(curr){
			if(ctr == idx) return curr->get().data;
			curr = curr->get().next;
			ctr++;
		}
		throw std::out_of_range ("Out of range exception");
	}

	T front(){
		if(!this->head)
			throw std::out_of_range ("Out of range exception");
		return this->head.get()->data;
	}

	T back(){
		if(!this->tail)
			throw std::out_of_range ("Out of range exception");
		return this->tail.get()->data;
	}

	void push_front(T value){
		this->size++;
		auto node = std::make_shared<Node>(value);
		if(!this->head || !this->tail) {
			this->head = this->tail = node;
			return;
		}
		node.get()->next = this->head;
		this->head = node;
	}

	void push_back(T value){
		this->size++;
		auto node = std::make_shared<Node>(value);
		if(!this->head || !this->tail){
			this->head = this->tail = node;
			return;
		}
		this->tail.get()->next = node;
		this->tail = node;
	}

	void push(int idx, T value){
		if(this->size == 0) // empty?
			throw std::out_of_range ("Out of range exception");

		int ctr = 0;
		auto bp = this->head;
		auto fp = this->head->get().next;
		while(fp){
			if(ctr == idx){
				auto node = std::make_shared<Node>(value);
				this->size++;
				node->get().next = bp->get().next;
				bp->get().next = node;
				break;
			}
			bp = bp->get().next;
			fp = fp->get().next;
			ctr++;
		}
		throw std::out_of_range ("Out of range exception");
	}

	void pop_front() {
		if(this->size == 0) // empty?
			throw std::out_of_range ("Out of range exception");
		if(this->size == 1) { // size 1
			this->head = this->tail = nullptr;
			this->size--;
			return;
		}

		this->size--;
		this->head = this->head.get()->next;
	}

	void pop_back(){
		if(this->size == 0) // empty?
			throw std::out_of_range ("Out of range exception");

		if(this->size == 1) { // size 1
			this->head = this->tail = nullptr;
			this->size--;
			return;
		}

		this->tail = this->head;
		auto fp = this->head.get()->next;
		while(fp.get()->next){
			this->tail = this->tail.get()->next;
			fp = fp.get()->next;
		}
		this->size--;
		this->tail.get()->next = nullptr;
	}

	void pop(int idx){
		if(this->size == 0) // empty?
			throw std::out_of_range ("Out of range exception");

		if(this->size == 1) { // size 1
			if(idx != 0)
				throw std::out_of_range ("Out of range exception");

			this->head = this->tail = nullptr;
			this->size--;
			return;
		}

		int ctr = 0;
		auto bp = this->head;
		auto fp = this->head->get().next;
		while(fp){
			if(ctr == idx){
				this->size--;
				if(fp->get().next) //is not last?
					bp->get().next = fp->get().next;
				 else{
					this->tail = bp;
					this->tail->get().next = nullptr;
				 }
				break;
			}
			bp = bp->get().next;
			fp = fp->get().next;
			ctr++;
		}
		throw std::out_of_range ("Out of range exception");
	}

	int search(T value){
		int ctr = 0;
		auto curr = this->head;
		while(curr){
			if(curr.get()->data == value) return ctr;
			curr = curr.get()->next;
			ctr++;
		}
		return -1;
	}

	void reverse(){
		this->_reverse(this->head);
	}

	int count(){
		return this->size;
	}

};
