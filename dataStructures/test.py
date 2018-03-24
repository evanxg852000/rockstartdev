import unittest

from linkedlist import LinkedList
from stack import Stack
from queue import Queue
from set import Set
from hashtable import HashTable, HashSet
from binarytree import BinaryTree

class LinkedListTest(unittest.TestCase):
    def test_features(self):
        ll = LinkedList()
        self.assertEqual(ll.front(), None)
        self.assertEqual(ll.back(), None)

        ll = LinkedList(3)
        self.assertEqual(ll.front().data, 3)
        self.assertEqual(ll.back().data, 3)

        ll.add_front(12)
        ll.add_front(22)
        ll.add_back(14)
        ll.add_back(7)

        self.assertEqual(ll.front().data, 22)
        self.assertEqual(ll.back().data, 7)

        self.assertEqual(ll.find(11), None)
        self.assertNotEqual(ll.find(7), None)

        self.assertEqual(ll.count(), 5)
        ll.delete(ll.find(7))
        self.assertEqual(ll.back().data, 14)
        self.assertEqual(ll.count(), 4)

        self.assertEqual([x.data for x in ll.items()], [22, 12, 3, 14])


class StackTest(unittest.TestCase):
    def test_features(self):
        stk = Stack()
        stk.push(3)
        stk.push(12)
        stk.push(5)
        stk.push(17)
        self.assertEqual(stk.count(), 4)
        self.assertEqual(stk.peek(), 17)
        self.assertEqual(stk.pop(),17)
        self.assertEqual(stk.count(), 3)

class QueueTest(unittest.TestCase):
    def test_features(self):
        qe = Queue()
        qe.enqueue(3)
        qe.enqueue(12)
        qe.enqueue(5)
        qe.enqueue(17)
        self.assertEqual(qe.count(), 4)
        self.assertEqual(qe.peek(), 3)
        self.assertEqual(qe.dequeue(),3)
        self.assertEqual(qe.dequeue(),12)
        self.assertEqual(qe.count(), 2)
        self.assertEqual([x for x in qe.items()], [5,17])

class SetTest(unittest.TestCase):
    def test_features(self):
        st = Set()
        st.add(3)
        st.add(5)
        st.add(3)
        st.add(12)
        st.add(15)
        self.assertEqual(st.count(), 4)
        self.assertEqual(st.has(5), True)
        self.assertEqual(st.has(8), False)
        self.assertEqual([x for x in st.items()], [3,5,12, 15])
        st1 = Set()
        st1.add(3)
        st1.add(5)
        self.assertEqual(st1.is_subset(st), True)
        self.assertEqual([x for x in (st.union(st1)).items()], [3,5,12,15])
        self.assertEqual([x for x in (st.intersect(st1)).items()], [3,5])
        self.assertEqual([x for x in (st.diff(st1)).items()], [12,15])

class HashTableTest(unittest.TestCase):
    def test_feautures(self):
        ht = HashTable()
        ht.put('Evance', 13)
        ht.put('Alex', 18)
        ht.put('Frank', 15)
        ht.put('Liz', 13)
        ht.put('Frank', 14)
        self.assertEqual(ht.count(), 5)
        self.assertEqual(ht.has('Frank'), True)
        self.assertEqual([(x.key, x.val) for x in ht.get('Frank')], [('Frank', 15),('Frank', 14)])
        ht.delete('Frank')
        self.assertEqual(ht.count(), 3)
        self.assertEqual(ht.has('Frank'), False)

class HashSetTest(unittest.TestCase):
    def test_features(self):
        hs = HashSet()
        hs.put('Evance', 13)
        hs.put('Alex', 18)
        hs.put('Frank', 15)
        hs.put('Liz', 13)
        hs.put('Frank', 14)
        self.assertEqual(hs.count(), 4)
        self.assertEqual(hs.has('Frank'), True)
        self.assertEqual((hs.get('Frank').key, hs.get('Frank').val), ('Frank', 15))
        hs.delete('Frank')
        self.assertEqual(hs.count(), 3)
        self.assertEqual(hs.has('Frank'), False)

class BinaryTreeTest(unittest.TestCase):
    def test_features(self):
        bt = BinaryTree(10)
        bt.add(6)
        bt.add(18)
        bt.add(4)
        bt.add(8)
        bt.add(15)
        bt.add(21)

        self.assertEqual(bt.count(), 7)
        self.assertEqual(bt.min(), 4)
        self.assertEqual(bt.max(), 21)
        self.assertEqual(bt.has(8), True)
        self.assertEqual(bt.has(11), False)
        self.assertNotEqual(bt.find(15), None)
        self.assertEqual(bt.find(11), None)
        bt.delete(10)
        self.assertEqual(bt.root.data, 15)
        self.assertEqual(bt.find(10), None)
        self.assertEqual(bt.count(), 6)
        self.assertEqual([x for x in bt.items()], [4, 6, 8, 15, 18, 21])
        self.assertEqual([x for x in bt.items('pre')], [15, 6, 4, 8, 18, 21])
        self.assertEqual([x for x in bt.items('post')], [4, 8, 6, 21, 18, 15])


if __name__ == '__main__':
    unittest.main()
