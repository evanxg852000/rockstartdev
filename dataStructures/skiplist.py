# course: http://www.mathcs.emory.edu/~cheung/Courses/323/
# http://www.mathcs.emory.edu/~cheung/Courses/323/Syllabus/Map/skip-list.html
# https://www.cs.cmu.edu/~ckingsf/bioinfo-lectures/skiplists.pdf
import unittest 
import random
from datetime import datetime

class Node:
    def __init__(self, key, value, level):
        self.key = key
        self.value = value
        self.next = [None]*level
        self.prev = None

class SkipList:

    def __init__(self, maxLevel):
        self.maxLevel = maxLevel
        self.head = Node('min-inf', None, maxLevel)
        self.tail = Node('max-inf', None, maxLevel)
        random.seed(datetime.now())
        #create links between head->tail
        for i in range(maxLevel):
            self.head.next[i] = self.tail
            self.tail.prev = self.head

    def _pick_level(self):
        height = 1
        while random.randint(1,2) != 1 and height < self.maxLevel:
            height += 1
        return height

    def _find_terminal(self, key):
        cl = self.maxLevel - 1
        cn = self.head
        while  cl >= 0:
            if cn.next[cl].key == self.tail.key:
                cl -=1
                continue
            elif cn.next[cl].key <= key:
                cn = cn.next[cl]
                continue
            else:
                cl -= 1
        return cn

    def put(self, key, val):
        # find node or lowest level of insertion point
        cn = self._find_terminal(key)
        if cn.key == key: # update key
            cn.value = val
            return

        level = self._pick_level()
        node = Node(key, val, level)
        cl = 0
        while cl < level:
            node.next[cl] = cn.next[cl]
            cn.next[cl].prev = node
            node.prev = cn
            cn.next[cl] = node
            cl += 1
        
    def get(self, key):
        cn = self._find_terminal(key)
        if cn.key == key:
            return cn.value
        return None

    def remove(self, key):
        cn = self._find_terminal(key)
        if cn.key != key:
            return
        
        cl = 0
        level = len(cn.next)
        while cl < level:
            cn.prev.next[cl] = cn.next[cl]
            cn.next[cl].prev = cn.prev
            cl += 1


class SkipListTest(unittest.TestCase): 
  
    def test_init(self):
        sk = SkipList(12);
        self.assertEqual(sk.head.next[0].key, sk.tail.key) 
        self.assertEqual(sk.tail.prev.key, sk.head.key) 

    def test_find_terminal(self):
        sk = SkipList(12);
        tn = sk._find_terminal('test')
        self.assertEqual(tn.key, sk.head.key) 
        
    def test_put(self):
        sk = SkipList(12);
        sk.put('age', 23)
        inode = sk.head.next[0]
        self.assertEqual(inode.key, 'age')
        self.assertEqual(inode.value, 23)
        self.assertEqual(inode.prev.key, sk.head.key)
        self.assertEqual(inode.next[0].key, sk.tail.key) 
        self.assertEqual(inode.key, sk.tail.prev.key)

    def test_get(self):
        sk = SkipList(12);
        sk.put('name', 'jhone')
        sk.put('age', 23)
        self.assertEqual(sk.get('name'), 'jhone')
        self.assertEqual(sk.get('age'), 23)
        self.assertEqual(sk.get('force'), None)

    def test_delete(self):
        sk = SkipList(12);
        sk.put('name', 'jhone')
        sk.put('age', 23)
        sk.put('color', 'blue')
        sk.put('force', 98)

        sk.remove('age')
        self.assertEqual(sk.get('name'), 'jhone')
        self.assertEqual(sk.get('age'), None)
        self.assertEqual(sk.get('test'), None)
        self.assertEqual(sk.get('color'), 'blue')

        sk.remove('color')
        sk.remove('force')
        self.assertEqual(sk.get('color'), None)
        self.assertEqual(sk.get('force'), None)


if __name__ == '__main__': 
    unittest.main() 
