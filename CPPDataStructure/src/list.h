#include <algorithm>
#include <memory>

template<typename T>
class List {
private:
	int capacity;
	int size;
	std::unique_ptr<T[]> items;

	void _reserve(){
		this->capacity = this->capacity * 2;
		auto temp = std::move(this->items);
		this->items = std::make_unique<T[]>(this->capacity);
		std::copy(temp.get(), temp.get() + this->size, this->items.get());
	}

public:
	List(int capacity = 10) {
		this->capacity = capacity;
		this->size = 0 ;
		this->items = std::make_unique<T[]>(this->capacity);
	}

	virtual ~List(){

	}

	T get(int idx){
		if(idx < 0  || idx >= this->size){
			throw std::out_of_range ("Out of range exception");
		}
		return this->items[idx];
	}

	void insert(T value){
		if(this->size == this->capacity){
			this->_reserve();
		}
		this->items[this->size] = value;
		this->size++;
	}

	int search(T value){
		for(int i = 0; i < this->size; i++){
			if(this->items[i] == value) return i;
		}
		return -1;
	}

	void remove(int idx){
		if(idx < 0 || idx >= this->size){
			throw std::out_of_range ("Out of range exception");
		}
		//swap with last & discard
		std::swap(this->items[idx], this->items[this->size-1]);
		this->size--;
	}

	int count(){
		return this->size;
	}

};
