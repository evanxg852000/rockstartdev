
class CircularBuffer(object):
    def __init__(self, size):
        self._store = [None]*size
        self._low = 0
        self._high = 0
        self._size = 0

    def push(self, data):
        if self._size < len(self._store):
            self._store[self._high]= data
            self._high += 1
            self._size += 1
        else:
            self._high = self._low
            self._low += 1
            self._store[self._high] = data

    def isEmpty(self):
        return self._size == 0

    def count(self):
        return self._size

    def items(self):
        if self._low < self._high:
            for data in self._store[self._low: self._high]:
                yield data
        else:
            for data in self._store[self._low:]:
                yield data
            for data in self._store[:self._high + 1]:
                yield data
