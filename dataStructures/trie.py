from hashtable import HashSet

class Node(object):
    def __init__(self):
        self.keys = HashSet()
        self.is_word = False

    def end():
        self.is_word = true

class Trie(object):
    def __init__(self, word=None):
        self.root = Node()
        self.size += 1

    def add(self, word, node=None):
        if node = None :
            node = self.root
        if len(word) == 0:
            node.end()
            return
        if node.keys.has(word[0]) == False:
            self.keys.put(word[0], Node())
        self.add(word[1:], self.keys.get(word[0])

    def dict(self):
        for w in self.__search('', self.root):
            yield w

    def has(self, word, node = None):
        if node == None:
            node = self.root
        if len(word) == 0:
            return node.is_word
        if node.keys.has(word[0]) == False:
            return False
        return self.has(word[1:], node.keys.get(word[0]))

    def suggest(self, prefix):
        pass

    def __search(self, word, node):
        words = []
        if node.keys.count() != 0:
            for pair in node.keys.items():
                self.__search(word+pair.key, pair.val)
            if node.is_word == True:
                words.append(word)
        else:
            if len(word) > 0:
                words.append(word)



