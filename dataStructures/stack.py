from linkedlist import LinkedList

class Stack(object):
    def __init__(self):
        self._store = LinkedList()

    def push(self, data):
        self._store.add_back(data)

    def pop(self):
        if(self._store.back() != None):
            data = self._store.back().data
            self._store.delete(self._store.back())
        return data

    def peek(self):
        if(self._store.back() != None):
            return self._store.back().data
        return None

    def items(self):
        for i in self._store.items():
            yield i.data

    def count(self):
        return self._store.count()
