
class CircularBuffer(object):
    def __init__(self, size):
        self._store = [None]*size
        self._size = size
        self._low = 0
        self._high = 0
        self._count = 0

    def add(self, data):
        if self.isFull():
            self._low = (self._low + 1) % self._size
        else:
            self._count += 1
        self._store[self._high] = data
        self._high = (self._high + 1) % self._size

    def remove(self):
        if self.isEmpty():
            raise Exception('Cannot remove on empty buffer')
        value = self._store[self._low]
        self._low = (self._low + 1) % self._size
        self._count -= 1
        return value

    def isEmpty(self):
        return self._count == 0

    def isFull(self):
        return self._size == self._count

    def count(self):
        return self._count

    def items(self):
        idx = self._low
        num = self._count
        while num > 0:
            yield self._store[idx]
            idx = (idx + 1) % self._size
            num -= 1
