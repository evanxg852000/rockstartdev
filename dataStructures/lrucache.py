import collections

import unittest


class RLUCache:
    def __init__(self, cap=10):
        self.keys = {}
        self.values = collections.deque([])
        self.cap = cap

    def __len__(self):
        return len(self.keys.keys())

    def put(self, k, v):
        node = (k, v)
        if len(self.keys.keys()) >= self.cap:
            front = self.values.popleft()
            del self.keys[front[0]]
        
        self.keys[k] = node
        self.values.append(node)

    def get(self, k):
        return self.keys[k][1] if k in self.keys else None

class TestLRUCache(unittest.TestCase):

    def test_cache(self):
        c = RLUCache(3)
        c.put('a', 12)
        c.put('b', 3)
        c.put('c', 25)
        
        self.assertEqual(len(c), 3)
        self.assertEqual(c.get('a'), 12)
        self.assertEqual(c.get('c'), 25)
        self.assertEqual(c.get('v'), None)

        c.put('d', 10)
        self.assertEqual(len(c), 3)
        self.assertEqual(c.get('a'), None)


if __name__ == '__main__':
    unittest.main()