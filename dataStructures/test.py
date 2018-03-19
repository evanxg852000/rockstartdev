import unittest

from linkedlist import LinkedList

class LinkedListTest(unittest.TestCase):
    def test_insert(self):
        ll = LinkedList()
        self.assertEqual(ll.front(), None)
        self.assertEqual(ll.back(), None)

        ll.add_front(12)
        ll.add_front(22)
        ll.add_back(14)
        ll.add_back(7)

        self.assertEqual(ll.front().data, 22)
        self.assertEqual(ll.back().data, 7)

        self.assertEqual(ll.find(11), None)
        self.assertNotEqual(ll.find(7), None)

        self.assertEqual(ll.count(), 4)
        ll.delete(ll.find(7))
        self.assertEqual(ll.back().data, 14)
        self.assertEqual(ll.count(), 3)

        self.assertEqual([x.data for x in ll.items()], [22, 12, 14])







if __name__ == '__main__':
    unittest.main()
