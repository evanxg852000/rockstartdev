# https://www.cs.cmu.edu/~ckingsf/bioinfo-lectures/skiplists.pdf
# TODO: needs to check null pointer issues & remove
import random
from datetime import datetime

import unittest

class Node:
    def __init__(self, height=0, data=(None, None), prev=None):
        self.next = [None]*height
        self.key = data[0]
        self.val = data[1]
        self.prev = None

class SkipList:
    
    def __init__(self, maxLevel):
        self.maxLevel = maxLevel
        self.head = Node(maxLevel)
        random.seed(datetime.now())

    def pickLevel(self):
        height = 1
        while random.randint(1,2) != 1 and height < self.maxLevel:
            height += 1
        return height

    def insert(self, key, val):
        # find node or lowest level insertion point
        cn = self._find_terminal(key)
        if cn.key == key: # update value
            cn.val = val
            return
        
        # insert node at each level from botom to top in stairs fashion
        cl = 0
        node = Node(self.pickLevel(), (key, val))
        while cl < len(node.next):
            # update linked list pointers
            if cn != None:
                node.next[cl] = cn.next[cl]

            if cn != None and cn.next[cl] != None:
                cn.next[cl].prev = node

            if cn != None:
                cn.next[cl] = node
            
            # make one stair step up if last height
            if cn != None and cn.next != None and cl == len(cn.next)-1: 
                cn = cn.prev
            cl += 1

    def find(self, key):
        cn = self._find_terminal(key)
        if cn.key == key:
            return cn.val
        return None
            
    def remove(self, key):
        # find the node
        cn = self._find_terminal(key)
        if cn == None:
            return
        elif cn.key != key:
            return
        
        # update all level pointers
        cl = 0
        while cl < len(cn.next):
            prev = None
            nxt = None
            if cn.next[cl] != None:
                prev = cn.next[cl].prev
                nxt = cn.next[cl].next[cl]

            if prev != None:
                prev.next[cl] = nxt
            if nxt != None:
                nxt.prev = prev
            cl += 1
        
        cn = None


    def _find_terminal(self, key):
        cl = len(self.head.next) - 1
        cn = self.head
        while  cl >= 0 :
            while cn.next != None and cn.next[cl] != None and cn.next[cl].key < key:
                cn = cn.next[cl]

            if cn.next[cl] != None and cn.next[cl].key == key:
                return cn.next[cl]
            else:
                cl -= 1
        return cn



class SkipListTest(unittest.TestCase):
    def test_features(self):
        skplst = SkipList(12)
        skplst.insert(1, 'evance')
        skplst.insert(3, 'alex')
        skplst.insert(2, 'karim')
        skplst.insert(5, 'jhon')

        self.assertEqual(skplst.find(1), 'evance')
        self.assertEqual(skplst.find(4), None)
        self.assertEqual(skplst.find(5), 'jhon')
        self.assertEqual(skplst.find(3), 'alex')

        skplst.remove(5)
        self.assertEqual(skplst.find(5), None)


if __name__ == '__main__':
    unittest.main()