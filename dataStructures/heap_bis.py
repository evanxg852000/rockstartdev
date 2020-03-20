import unittest

class BinaryHeap:

    def __init__(self, is_min=True):
        self.heapList = [0]
        self.size = 0
        if is_min == True:
            self.comp = lambda a, b: a < b
            self.pickChild = min
        else:
             self.comp = lambda a, b: a > b
             self.pickChild = max
    
    def push(self, val):
        self.heapList.append(val)
        self.size += 1
        self._percolateUp(self.size)

    def pop(self):
        if self.size == 0:
            return None
        elem = self.heapList[1]
        self.heapList[1] = self.heapList[self.size]
        self.heapList.pop()
        self.size -= 1
        self._percolateDown(1)
        return elem

    def _percolateUp(self, i):
        parentIdx = i // 2
        while parentIdx > 0:
            if self.comp(self.heapList[i], self.heapList[parentIdx]):
                temp = self.heapList[i]
                self.heapList[i] = self.heapList[parentIdx]
                self.heapList[parentIdx] = temp
            parentIdx = parentIdx // 2

    def _percolateDown(self, i):
        while (2 * i) <= self.size:
            maxChildIdx = 2 * i
            if (2*i) + 1 <= self.size:
                otherChildIdx = (2 * i) + 1
                if self.pickChild(self.heapList[maxChildIdx], 
                    self.heapList[otherChildIdx]) == self.heapList[otherChildIdx]:
                    maxChildIdx = otherChildIdx
            
            if self.comp(self.heapList[maxChildIdx], self.heapList[i]):
                temp = self.heapList[maxChildIdx]
                self.heapList[maxChildIdx] = self.heapList[i]
                self.heapList[i] = temp
            i = maxChildIdx


class TestBinHeap(unittest.TestCase):

    def test_minheap(self):
        min_heap = BinaryHeap()
        min_heap.push(3)
        min_heap.push(20)
        min_heap.push(12)
        min_heap.push(4)
        min_heap.push(11)
        min_heap.push(8)
        self.assertEqual(min_heap.size, 6)
        
        l = [] 
        while True:
            top = min_heap.pop()
            if top == None:
                break
            l.append(top)
        self.assertEqual(l, [3, 4, 8, 11, 12, 20])

    def test_maxheap(self):
        max_heap = BinaryHeap(False)
        max_heap.push(3)
        max_heap.push(20)
        max_heap.push(12)
        max_heap.push(4)
        max_heap.push(11)
        max_heap.push(8)
        self.assertEqual(max_heap.size, 6)
        
        l = [] 
        while True:
            top = max_heap.pop()
            if top == None:
                break
            l.append(top)
        self.assertEqual(l, [20, 12, 11, 8, 4, 3])


if __name__ == '__main__':
    unittest.main()