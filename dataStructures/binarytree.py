from queue import Queue

class Node(object):
    def __init__(self, data = None, left = None, right = None):
        self.data = data
        self.left = left
        self.right = right

class BinaryTree(object):
    def __init__(self, data=None):
        self.size = 0
        self.root = None
        if data != None:
            self.size += 1
            self.root = Node(data)

    def add(self, data, node=None):
        if node == None:
            if self.root == None:
                self.size += 1
                self.root = Node(data)
                return
            else:
                self.add(data, self.root)
                return

        if data < node.data:
            if node.left == None:
                self.size += 1
                node.left = Node(data)
                return
            else:
                self.add(data, node.left)
                return

        if data > node.data:
            if node.right == None:
                self.size += 1
                node.right = Node(data)
                return
            else:
                self.add(data, node.right)
                return

    def delete(self, data):
        self.root = self.__delete(self.root, data)

    def find(self, data):
        curr = self.root
        while curr != None:
            if data == curr.data:
                return curr
            if data < curr.data :
                curr = curr.left
                continue
            if data > curr.data:
                curr = curr.right
        return curr

    def has(self, data):
        return self.find(data) != None

    def min(self):
        if self.root == None:
            return None
        curr = self.root
        while curr.left != None:
            curr = curr.left
        return curr.data

    def max(self):
        if self.root == None:
            return None
        curr = self.root
        while curr.right != None:
            curr = curr.right
        return curr.data

    def count(self):
        return self.size

    def items(self, mode='in'):
        if mode == 'lev':
            return self.__level_order(self.root)
        if mode == 'pre':
            return self.__pre_order(self.root)
        if mode == 'in':
            return self.__in_order(self.root)
        if mode == 'pos':
            return self.__post_order(self.root)

    def __delete(self, node, data):
        if node == None:
            return None
        if data == node.data:
            if node.left == None and node.right == None:
                self.size -= 1
                return None
            if node.left == None:
                self.size -= 1
                return node.right
            if node.right == None:
                self.size -= 1
                return node.left
            # Go rigth and follow left to swap data with the
            # left most leaf node and delete it
            temp = node.right
            while temp.left != None:
                temp = temp.left
            node.data = temp.data
            node.right = self.__delete(node.right, temp.data)
        if data < node.data :
            node.left = self.__delete(node.left, data)
            return node
        if data > node.data:
            node.right = self.__delete(node.right, data)
            return node

    def __height(self):
        pass

    def __level_order(self, root):
        q = Queue()
        q.enqueue(root)
        while q.count() != 0:
            node = q.dequeue()
            yield node.data
            if node.left != None:
                q.enqueue(node.left)
            if node.right != None:
                q.enqueue(node.right)

    def __pre_order(self, curr):
        if curr != None:
            yield curr.data
            yield from self.__pre_order(curr.left)
            yield from self.__pre_order(curr.right)

    def __in_order(self, curr):
        if curr != None:
            yield from self.__in_order(curr.left)
            yield curr.data
            yield from self.__in_order(curr.right)

    def __post_order(self, curr):
        if curr != None:
            yield from self.__post_order(curr.left)
            yield from self.__post_order(curr.right)
            yield curr.data

