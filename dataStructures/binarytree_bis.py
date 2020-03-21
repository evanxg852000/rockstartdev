import unittest

class Node:
    def __init__(self, k, v):
        self.key = k
        self.value = v
        self.left = None
        self.right = None

class BinaryTree:

    def __init__(self):
        self.root = None
        self.size = 0

    def __len__(self):
        return self.size

    def insert(self, k, v):
        nn = Node(k,v)
        if self.root == None:
            self.root = nn
            self.size += 1
            return

        cn = self.root
        while True:  
            if k == cn.key:
                cn.value = v
                break
            elif k < cn.key:
                if cn.left != None:
                    cn = cn.left
                else:
                    cn.left = nn
                    self.size += 1
                    break
            else:
                if cn.right != None:
                    cn = cn.right
                else:
                    cn.right = nn
                    self.size += 1
                    break

    def get(self, k):
        cn = self.root
        while cn != None:
            if k == cn.key:
                return  cn.value
            elif k < cn.key:
                cn = cn.left
            else:
                cn = cn.right
        return None

    def remove(self, k):
        self.root = self._remove(self.root, k)

    def _remove(self, root, k):
        if root == None:
            return None
        elif k < root.key:
            root.left = self._remove(root.left, k)
        elif k > root.key:
            root.right = self._remove(root.right, k)
        else:
            if root.left == None and root.right == None:
                self.size -= 1
                return None
            elif root.left != None:
                self.size -= 1
                root = root.left
                return root
            elif root.right != None:
                self.size -= 1
                root = root.right
                return root
            else:
                #find min of the right subtree
                temp = root.right
                while temp.left != None:
                    temp = temp.left
                root.key = temp.key
                root.value = temp.value
                root.right = self._remove(root.right, temp.key)
                return root


    def _findMax(self, n):
        while n.right != None:
            n = n.right
        return n

class TestBinaryTree(unittest.TestCase):

    def test_bt(self):
        bst = BinaryTree()
        bst.insert('k', 12)
        bst.insert('a', 3)
        bst.insert('m', 25)
        bst.insert('k', 13)

        self.assertEqual(len(bst), 3)
        self.assertEqual(bst.get('k'), 13)
        self.assertEqual(bst.get('u'), None)

        bst.insert('b', 10)
        bst.insert('u', 5)
        bst.insert('z', 7)
        bst.insert('t', 9)
        self.assertEqual(len(bst), 7)
        
        bst.remove('u')
        self.assertEqual(len(bst), 6)
        self.assertEqual(bst.get('u'), None)


if __name__ == '__main__':
    unittest.main()