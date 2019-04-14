#include <algorithm>
#include <vector>
#include <list>
#include <string>
#include <cmath>


template<typename T>
class HashTable {
private:
	class Item{
	public:
		std::string key;
		T value;
		Item(std::string k, T v): key{k}, value{v} {
		}
	};

	using Chain = std::list<Item>;
	std::vector<Chain> bucket;
	int capacity;
	int size;

	int hash(std::string key){
		const int LARGE_PRIME = 151;
		const int n = key.length();

		long hash = 0;
		for(size_t i=0; i < n; i++){
			hash = (long) std::pow(LARGE_PRIME, n -(i+1)) * key.at(i);
			hash %= capacity;
		}
		return (int) hash;
	}

public:
	HashTable(int cap): bucket{}, capacity{cap}, size{0} {
		this->bucket.reserve(capacity);
		this->bucket.assign(capacity, Chain{});
	}

	void put(std::string k, T v){
		int idx = this->hash(k);
		auto it = std::find_if(this->bucket[idx].begin(), this->bucket[idx].end(),
								[k](Item itm) -> bool{ return itm.key == k; });
		//if exit? just update value
		if(it != this->bucket[idx].end()){
			it->value = v;
			return;
		}
		this->size++;
		this->bucket[idx].push_front(Item{k, v});
	}

	bool exist(std::string k){
		int idx = this->hash(k);
		auto it = std::find_if(this->bucket.at(idx).begin(), this->bucket.at(idx).end(),
								[k](Item itm) -> bool{ return itm.key == k; });
		return (it != this->bucket[idx].end());
	}

	T get(std::string k){
		int idx = this->hash(k);
		auto it = std::find_if(this->bucket[idx].begin(), this->bucket[idx].end(),
								[k](Item itm) -> bool{ return itm.key == k; });
		if(it == this->bucket[idx].end()){
			throw std::out_of_range ("Key not found exception");
		}
		return it->value;
	}

	bool remove(std::string k){
		if(!this->exist(k))
			return false;

		int idx = this->hash(k);
		this->bucket[idx].remove_if([&k](Item itm) -> bool { return itm.key == k; });
		this->size--;
		return true;
	}

	int length(){
		return this->size;
	}
};
