
class Node(object):
    def __init__(self, data = None, prev = None, nxt = None):
        self.data = data
        self.prev = prev
        self.next = nxt

class LinkedList(object):

    def __init__(self, data = None):
        self.size = 0
        self.head = self.tail = None
        if (data != None):
            self.size +=1
            self.head = self.tail = Node(data)

    def front(self):
        return self.head

    def back(self):
        return self.tail

    def add_front(self, data):
        temp = Node(data)
        self.size +=1
        if(self.head == None):
            self.head = self.tail = temp
        else:
            temp.next = self.head
            self.head.prev = temp
            self.head = temp

    def add_back(self, data):
        self.size +=1
        temp = Node(data)
        if(self.tail == None):
            self.head = self.tail = temp
        else:
            temp.prev = self.tail
            self.tail.next = temp
            self.tail = temp

    def insert_before(self, node, data):
        self.size +=1
        temp = Node(data)
        temp.next = node
        temp.prev = node.prev
        node.prev = temp

    def insert_after(self, node, data):
        self.size +=1
        temp = Node(data)
        temp.prev = node
        temp.next = node.next
        node.next = temp

    def delete(self, node):
        self.size -=1
        if(node.prev != None):
            node.prev.next = node.next
        if (node.next != None):
            node.next.prev = node.prev
        if(node == self.head):
            self.head = node.next
        if(node == self.tail):
            self.tail = node.prev

    def find(self, data):
        target = self.head
        while (target != None) :
            if (target.data == data):
                break
            target = target.next
        return target

    def count(self):
        return self.size

    def items(self):
        target = self.head
        while (target != None):
            yield target
            target = target.next

