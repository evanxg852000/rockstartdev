#include <algorithm>
#include <vector>

template<typename T>
class BinaryTree {
private:
	struct Node{
		T data;
		std::shared_ptr<Node> left;
		std::shared_ptr<Node> right;
		std::shared_ptr<Node> parent;
		Node(T data){
			this->data = data;
			this->left = nullptr;
			this->right = nullptr;
			this->parent = nullptr;
		}
	};

public:
	std::shared_ptr<Node> root;
	int size;

	BinaryTree() :root{nullptr}, size{0} {
	}

	void insert(T data){
		auto node = std::make_shared<Node>(data);
		if(this->root == nullptr){
			this->root = node;
			this->size += 1;
			return;
		}

		auto walker = this->root;
		while(walker != nullptr){
			if(walker.get()->data > data){ //follow left
				if(walker.get()->left == nullptr){
					walker.get()->left = node;
					node.get()->parent = walker;
					this->size += 1;
					return;
				}
				walker = walker.get()->left;
			}

			if(walker.get()->data < data) { // follow right
				if(walker.get()->right == nullptr){
					walker.get()->right = node;
					node.get()->parent = walker;
					this->size += 1;
					return;
				}
				walker = walker.get()->right;
			}

			if(walker.get()->data == data)
				return; //already exist
		}


	}

	void remove(T data){
		auto walker = this->root;
		//find the node
		while(walker != nullptr){
			if(walker.get()->data == data)
				break;
			if(walker.get()->data > data) { //follow left
				walker = walker.get()->left;
				continue;
			}
			if(walker.get()->data < data) { //follow right
				walker = walker.get()->right;
				continue;
			}
		}

		if(walker == nullptr) // data was not found
			return;

		// left node
		if(walker.get()->left == nullptr && walker.get()->right == nullptr){
			auto parent = walker.get()->parent;
			walker.get()->parent = nullptr;
			if(parent.get()->left.get()->data == data)
				parent.get()->left = nullptr;
			if(parent.get()->right.get()->data == data)
				parent.get()->right = nullptr;
			return;
		}

		//one child left
		if(walker.get()->left != nullptr && walker.get()->right == nullptr){
			walker.get()->data = walker.get()->left.get()->data;
			walker.get()->left.get()->parent = nullptr;
			walker.get()->left = nullptr;
			return;
		}

		//one child right
		if(walker.get()->left == nullptr && walker.get()->right != nullptr){
			walker.get()->data = walker.get()->right.get()->data;
			walker.get()->right.get()->parent = nullptr;
			walker.get()->right = nullptr;
			return;
		}

		//two children
		auto target = walker.get()->right;
		while(target.get()->left != nullptr){
			target = target.get()->left;
		}
		target.get()->data = walker.get()->data;
		//TODO need to do this recursivelly




	}

	bool find(T data){
		auto walker = this->root;
		while(walker != nullptr){
			if(walker.get()->data == data){
				return true;
			}
			if(walker.get()->data > data) { //follow left
				walker = walker.get()->left;
				continue;
			}
			if(walker.get()->data < data) { //follow right
				walker = walker.get()->right;
				continue;
			}
		}
		return false;
	}

	T max(){
		if(this->size == 0){
			throw std::out_of_range("out of range exception");
		}
		auto walker = this->root;
		while(walker != nullptr && walker.get()->right != nullptr){
			walker = walker.get()->right;
		}
		return walker.get()->data;
	}

	T min(){
		if(this->size == 0){
			throw std::out_of_range("out of range exception");
		}
		auto walker = this->root;
		while(walker != nullptr && walker.get()->left != nullptr){
			walker = walker.get()->left;
		}
		return walker.get()->data;
	}

	std::vector<T> inOrderItems(){
		std::vector<T> rst;
		_inOrder(this->root, rst);
		return std::move(rst);
	}

	void _inOrder(std::shared_ptr<Node> root, std::vector<T> &rst){
		if(root == nullptr)
			return;
		_inOrder(root.get()->left, rst);
		rst.push_back(root.get()->data);
		_inOrder(root.get()->right, rst);
	}

	int getSize(){
		return this->size;
	}

};
