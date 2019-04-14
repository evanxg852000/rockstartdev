/* Catch2 tutorial:
 * https://mariusbancila.ro/blog/2018/03/29/writing-cpp-unit-tests-with-catch2
 * https://www.youtube.com/watch?v=grC0S6ZK59U
*/
#define CATCH_CONFIG_MAIN

#include "catch2.h"
#include "misc.h"
#include "list.h"
#include "sll.h"
#include "dll.h"
#include "stk.h"
#include "que.h"
#include "sort.h"
#include "search.h"
#include "str.h"
#include "btree.h"
#include "hashtable.h"


TEST_CASE("Miscelaenous funtions", "[misc]"){
	REQUIRE(generate_random(2, 10) >= 2);
	//REQUIRE(generate_random(0, 10) < 10);
}

TEST_CASE("Test List", "[list]"){
	List<int> l{2};
	l.insert(3);
	l.insert(4);

	REQUIRE(l.count() == 2);

	l.insert(5);
	l.insert(1);
	l.insert(3);

	REQUIRE(l.count() == 5);
	REQUIRE(l.get(2) == 5);

	l.remove(2);

	REQUIRE(l.count() == 4);
	REQUIRE(l.search(3) == 0);
	REQUIRE(l.search(1) == 3);
	REQUIRE(l.search(5) == -1);

	CHECK_THROWS(l.get(5));
	CHECK_THROWS(l.remove(-6));
}

TEST_CASE("Test Singly LinkedList", "[sll]") {

	SinglyLinkedList<int> sll{};
	sll.push_back(5);
	sll.push_front(4);
	sll.push_back(7);
	sll.push_front(9);
	sll.push_back(11);

   REQUIRE(sll.count() == 5);
   REQUIRE(sll.front() == 9);
   REQUIRE(sll.back() == 11);

   REQUIRE(sll.search(12) == -1);
   REQUIRE(sll.search(7) == 3);

   sll.pop_front();
   sll.pop_back();
   REQUIRE(sll.front() == 4);
   REQUIRE(sll.back() == 7);
   REQUIRE(sll.count() == 3);

   sll.reverse();
   REQUIRE(sll.front() == 7);
   REQUIRE(sll.back() == 4);
   REQUIRE(sll.count() == 3);
   REQUIRE(sll.search(5) == 1);

}

TEST_CASE("Test Doubly LinkedList", "[dll]"){
	DoublyLinkedList<int> dll{};
		dll.push_back(5);
		dll.push_front(4);
		dll.push_back(7);
		dll.push_front(9);
		dll.push_back(11);

		REQUIRE(dll.count() == 5);
		REQUIRE(dll.front() == 9);
		REQUIRE(dll.back() == 11);

		REQUIRE(dll.search(5) == 2);
		REQUIRE(dll.search(12) == -1);

		dll.pop_front();
		dll.pop_back();

		REQUIRE(dll.count() == 3);
		REQUIRE(dll.front() == 4);
		REQUIRE(dll.back() == 7);

}

TEST_CASE("Test Stack", "[stk]"){
	Stack<int> stk{};
	stk.push(3);
	stk.push(5);
	stk.push(2);

	REQUIRE(stk.top() == 2);
	stk.push(4);

	REQUIRE(stk.size() == 4);
	REQUIRE(stk.top() == 4);

	stk.pop();
	stk.pop();

	REQUIRE(stk.size() == 2);
	REQUIRE(stk.top() == 5);
}

TEST_CASE("Test Queue", "[que]"){
	Queue<int> que{};
	que.enqueue(3);
	que.enqueue(5);
	que.enqueue(2);

	REQUIRE(que.front() == 3);
	que.enqueue(4);

	REQUIRE(que.size() == 4);
	REQUIRE(que.front() == 3);

	que.dequeue();
	que.dequeue();

	REQUIRE(que.size() == 2);
	REQUIRE(que.front() == 2);
}

TEST_CASE("Test Sort", "[sort]"){
	int arr[] = {12, 2 ,7, 4, 3, 5, 13,19};

	bubleSort<int>(arr, 8);

	REQUIRE(arr[0] == 2);

}

TEST_CASE("Test Search", "[search]"){
	int arr[] = {12, 2 ,7, 4, 3, 5, 13,19};

	int r = linearSearch<int>(arr, 8,  3);
	REQUIRE(r == 4);

	int a[] = {2,3,4,5,7,12,13,19};
	r = binarySearch(a, 3, 0, 7);
	REQUIRE(r == 1);
	r = binarySearch(a, 6, 0, 7);
	REQUIRE(r == -1);
}

TEST_CASE("Test String", "[string]"){
	REQUIRE(isAnagram("Elbow", "Below") == true);
	REQUIRE(isAnagram("Elbow", "low") == false);

	REQUIRE(isPalindrome("Racecar") == true);
	REQUIRE(isPalindrome("Civic") == true);
	REQUIRE(isPalindrome("Dare") == false);

	REQUIRE(decimalToBinary(0) == "0");
	REQUIRE(decimalToBinary(9) == "1001");
	REQUIRE(decimalToBinary(3) == "11");

	REQUIRE(binaryToDecimal("0") == 0);
	REQUIRE(binaryToDecimal("1001") == 9);
	REQUIRE(binaryToDecimal("11") == 3);
}

TEST_CASE("Test Trees", "[trees]"){
	BinaryTree<int> bt;
	bt.insert(23);
	bt.insert(12);
	bt.insert(31);
	bt.insert(3);
	bt.insert(15);
	bt.insert(29);
	bt.insert(88);
	bt.insert(7);
	bt.insert(53);

	REQUIRE(bt.getSize() == 9);
	REQUIRE(bt.find(3) == true);
	REQUIRE(bt.find(14) == false);
	REQUIRE(bt.min() == 3);
	REQUIRE(bt.max() == 88);

	auto v = bt.inOrderItems();
	REQUIRE(v.size() == 9);
	REQUIRE(v.at(0)== 3);
	REQUIRE(v.at(7)== 53);
	REQUIRE(v.at(8)== 88);

	//bt.remove(3);
	//REQUIRE(bt.getSize() == 8);
}


TEST_CASE("Test HashTable", "[hashtable]"){
	HashTable<int> ht{5}; // small capacity to cause collision
	ht.put("Evance", 22);
	ht.put("Alex", 26);
	ht.put("Axel", 10);

	REQUIRE(ht.exist("Evance") == true);
	REQUIRE(ht.get("Evance") == 22);
	REQUIRE(ht.exist("Ali") == false);
	REQUIRE(ht.length() == 3);
	REQUIRE(ht.exist("Axel") == true);
	REQUIRE(ht.get("Axel") == 10);

	ht.put("Axel", 21); // check update
	REQUIRE(ht.get("Axel") == 21);
	REQUIRE(ht.remove("NOT") == false);
	REQUIRE(ht.remove("Axel") == true);
	REQUIRE(ht.length() == 2);
	REQUIRE(ht.exist("Axel") == false);
	REQUIRE_THROWS(ht.get("Axel"));

}



