from hashtable import HashSet

class Node(object):
    def __init__(self):
        self.keys = HashSet()
        self.is_word = False

    def end(self):
        self.is_word = True

class Trie(object):
    def __init__(self, word=None):
        self.root = Node()
        self.size = 0
        if word != None:
            self.add(word)

    def add(self, word, node=None):
        if node == None :
            node = self.root
        if len(word) == 0:
            self.size += 1
            node.end()
            return
        if node.keys.has(word[0]) == False:
            node.keys.put(word[0], Node())
        self.add(word[1:], node.keys.get(word[0]).val)


    def has(self, word, node = None):
        if node == None:
            node = self.root
        if len(word) == 0:
            return node.is_word
        if node.keys.has(word[0]) == False:
            return False
        return self.has(word[1:], node.keys.get(word[0]).val)

    def count(self):
        return self.size

    def suggest(self, prefix):
        pass

    def dict(self):
        pass

    def s(self, word, node):
        pass
