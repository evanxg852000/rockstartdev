from linkedlist import LinkedList

class Queue(object):
    def __init__(self):
        self._store = LinkedList()

    def enqueue(self, data):
        self._store.add_back(data)

    def dequeue(self):
        if(self._store.front() != None):
            data = self._store.front().data
            self._store.delete(self._store.front())
            return data
        return None

    def peek(self):
        if(self._store.front() != None):
            return self._store.front().data
        return None

    def items(self):
        for i in self._store.items():
            yield i.data

    def count(self):
        return self._store.count()
