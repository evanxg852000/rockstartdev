from linkedlist import LinkedList

class Set(object):
    def __init__(self):
        self._store = LinkedList()

    def has(self, data):
        return (self._store.find(data) != None)

    def items(self):
        for i in self._store.items():
            yield i.data

    def add(self, data):
        if (self.has(data)):
            return False
        self._store.add_back(data)
        return True

    def remove(self, data):
       target = self._store.find(data)
       if(target == None):
           return False
       self._store.delete(target)

    def count(self):
        return self._store.count()

    def union(self, otherSet):
        union = Set()
        for i in self.items():
            union.add(i)
        for i in otherSet.items():
            union.add(i)
        return union

    def intersect(self, otherSet):
        intersect = Set()
        for i in self.items():
            if (otherSet.has(i)):
                intersect.add(i)
        return intersect

    def diff(self, otherSet):
        diff = Set()
        for i in self.items():
            if (not otherSet.has(i)):
                diff.add(i)
        for i in otherSet.items():
            if (not self.has(i)):
                diff.add(i)
        return diff

    def is_subset(self, otherSet):
        if self.count() > otherSet.count():
            return False
        for i in self.items():
            if not otherSet.has(i):
                return False
        return True

