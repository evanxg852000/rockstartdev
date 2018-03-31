
class Heap(object):

    def __init__(self, data = None):
        self._size = 0
        self._store = []
        if data != None:
            self.insert(data)

    def insert(self, data):
        self._store.append(data)
        self._size += 1
        #heapify up
        i = self._size - 1
        while i > 0 :
            p = self._parent(i)
            if self._store[i] > self._store[p]:
                temp = self._store[p]
                self._store[p] = self._store[i]
                self._store[i] = temp
                i = p
            else:
                break

    def peek(self):
        return self._store[0]

    def remove(self):
        data = self.peek()
        #swap root with last
        temp = self._store[0]
        self._store[0] = self._store[self._size-1]
        self._store[self._size-1] = temp
        self._store = self._store[:-1]
        self._size -= 1
        #heapify up
        i = 0
        import pdb
        while i < self._size:
            #pdb.set_trace()
            l = i
            if self._left(i) < self._size and self._store[self._left(i)] > self._store[l]:
                l = self._left(i)
            if self._right(i) < self._size and self._store[self._right(i)] > self._store[l]:
                l = self._right(i)
            if l != i :
                temp = self._store[l]
                self._store[l] = self._store[i]
                self._store[i] = temp
                i = l
            else:
                break
        return data

    def isEmpty(self):
        return self._size == 0

    def count(self):
        return self._size

    def _parent(self, i):
        return int((i - 1) / 2)

    def _left(self, i):
        return (2 * i) + 1

    def _right(self, i):
        return (2 * i) + 2
