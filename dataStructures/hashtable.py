
from linkedlist import LinkedList

class Pair(object):
    def __init__(self, key, val):
        self.key = key
        self.val = val

    def __eq__(self, other):
        return self.key == other.key

class HashTable(object):
    def __init__(self, buckets = 100):
        self._buckets = buckets
        self._store = [LinkedList()] * buckets
        self._count = 0

    def put(self, key, val):
        idx = self.__hash(key)
        self._store[idx].add_back(Pair(key, val))
        self._count += 1

    def get(self, key):
        return [node.data for node in self.__get(key)]

    def has(self, key):
        return len(self.__get(key)) != 0

    def delete(self, key):
        idx = self.__hash(key)
        nodes = self.__get(key)
        for node in nodes:
            self._store[idx].delete(node)
        self._count -= len(nodes)

    def items(self):
        for idx in range(self._buckets):
            for node in self._store[idx].items():
                yield node.data

    def count(self):
        return self._count

    def __get(self, key):
        idx = self.__hash(key)
        nodes = []
        for node in self._store[idx].items():
            if node.data.key == key:
                nodes.append(node)
        return nodes

    def __hash(self, key):
        acc = 0
        for i in [ord(c) for c in str(key)]:
            acc += i
        return acc % self._buckets


class HashSet(HashTable):
    def __init__(self, buckets=100):
        super(HashSet, self).__init__(buckets)

    def put(self, key, val):
        if super(HashSet, self).has(key):
            return
        super(HashSet, self).put(key, val)

    def get(self, key):
        rst = super(HashSet, self).get(key)
        return None if len(rst) == 0 else rst[0]

