import unittest

class Node:
    def __init__(self, k, v):
        self.key = k
        self.value = v
        self.left = None
        self.right = None
        self.height = 0
        
class AVLTree():

    def __init__(self):
        self.root = None
        self.size = 0

    def __len__(self):
        return self.size

    def insert(self, k, v):
        self.root = self._insert(self.root, k, v)

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
        # TODO: same as bst remove + balance
        pass

    def _insert(self, root, k, v):
        if root == None:
            self.size += 1
            return Node(k,v)
        elif k == root.key:
            root.value = v
            return root
        elif k < root.key:
            root.left = self._insert(root.left, k, v)
        else:
            root.right= self._insert(root.right, k, v)
        
        # update height & balance
        self._updateHeight(root)
        return self._balance(root)

    def _balance(self, root):
        if self._isLeftHeavy(root):
            if self._getBalanceFactor(root.left) < 0:
                root.left = self._leftRotate(root.left)
            return self._rightRotate(root)
            
        if self._isRightHeavy(root):
            if self._getBalanceFactor(root.right) > 0:
                root.right = self._rightRotate(root.right)
            return self._leftRotate(root)

        return root

    def _getHeight(self, n):
        return n.height if n != None else 0
    
    def _updateHeight(self, n):
        n.height = max(self._getHeight(n.left), self._getHeight(n.right) ) + 1
    
    def _getBalanceFactor(self, n):
        return 0 if n == None else self._getHeight(n.left) - self._getHeight(n.right)

    def _isLeftHeavy(self, n):
        return self._getBalanceFactor(n) > 1

    def _isRightHeavy(self, n):
        return self._getBalanceFactor(n) < -1
    
    def _leftRotate(self, root):
        newRoot = root.right
        root.right = newRoot.left
        newRoot.left = root
        
        self._updateHeight(root)
        self._updateHeight(newRoot)
        return newRoot

    def _rightRotate(self, root):
        newRoot = root.left
        root.left = newRoot.right
        newRoot.right = root

        self._updateHeight(root)
        self._updateHeight(newRoot)
        return newRoot


class TestAVLTree(unittest.TestCase):

    def test_bt(self):
        bst = AVLTree()
        bst.insert('a', 12)
        bst.insert('b', 3)
        bst.insert('c', 25)
        bst.insert('d', 13)
        bst.insert('e', 13)

        self.assertEqual(len(bst), 5)
        self.assertEqual(bst.get('c'), 25)
        # self.assertEqual(bst.get('u'), None)

        # bst.insert('b', 10)
        # bst.insert('u', 5)
        # bst.insert('z', 7)
        # bst.insert('t', 9)
        # self.assertEqual(len(bst), 7)
        
        # bst.remove('u')
        # self.assertEqual(len(bst), 6)
        # self.assertEqual(bst.get('u'), None)


if __name__ == '__main__':
    unittest.main()