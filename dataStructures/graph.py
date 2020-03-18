# https://runestone.academy/runestone/books/published/pythonds/index.html#

import unittest

import collections


class Node:
    def __init__(self, l, w):
        self.label = l
        self.weigth = w

class Graph:

    def __init__(self, directed=False):
        self.vertices = {}
        self.adjacencyList = {}
        self.directed = directed

    def AddVertex(self, l, w=None):
        self.vertices[l] = Node(l,w)
        self.adjacencyList[l] = []
    
    def removeVertex(self, l):
        if l in self.vertices:
            del self.vertices[l]
            del self.adjacencyList[l]
        
    def addEdge(self, frm, to):
        if frm not in self.adjacencyList:
            return
        if to not in self.adjacencyList:
            return

        # could check 
        self.adjacencyList[frm] += [self.vertices[to]]
        if self.directed == False:
            self.adjacencyList[to] += [self.vertices[frm]]

    def removeEdge(self, frm, to):
        if frm not in self.adjacencyList:
            return
        if to not in self.adjacencyList:
            return

        self.adjacencyList[frm] = [x for x in self.adjacencyList[frm] if x.label != to]
        if self.directed == False:
            self.adjacencyList[to] = [x for x in self.adjacencyList[to] if x.label != frm]

    def deathFirsTraversal(self):
        s = []
        stk = []
        visited = set()
        for node in self.vertices.values():
            stk.append(node)
            while len(stk) != 0:
                tnode = stk.pop()
                if tnode.label in visited:
                    continue
                visited.add(tnode.label)
                s.append(tnode.label)
                for tnode in self.adjacencyList[tnode.label]:
                    stk.append(tnode)
        return s

    def breadFirsTraversal(self):
        s = []
        que = collections.deque([])
        visited = set()
        for node in self.vertices.values():
            que.append(node)
            while len(que) != 0:
                tnode = que.popleft()
                if tnode.label in visited:
                    continue
                visited.add(tnode.label)
                s.append(tnode.label)
                for tnode in self.adjacencyList[tnode.label]:
                    que.append(tnode)
        return s

    def topologicalSort(self):
        stk = []
        visited = set()
        for node in self.vertices.values():
            self._topologicalSorthelper(node, stk, visited)
        
        s = []
        while len(stk) != 0:
            s.append(stk.pop())

        return '->'.join(s)
        
    def hasCycle(self):
        all = set([x.label for x in self.vertices.values()])
        visiting = set()
        visited = set()
        while len(all) != 0:
            n = list(all)[0]
            if self._hasCycle(n, all, visiting, visited):
                return True
        return False


    def _topologicalSorthelper(self, node, stk, visited):
        if node.label in visited:
            return

        visited.add(node.label)
        for tnode in self.adjacencyList[node.label]:
            self._topologicalSorthelper(tnode, stk, visited)
        
        stk.append(node.label)

    def _hasCycle(self, node, all, visiting, visited):
        all.remove(node)
        visiting.add(node)
        for n in self.adjacencyList[node]:
            if n.label in visited:
                continue
            if n.label in visiting:
                return True
            
            if self._hasCycle(n.label, all, visiting, visited) == True:
                return True

        visiting.remove(node)
        visited.add(node)
        return False
        
    def print(self):
        s = ''
        for l in self.vertices.keys():
            al = ','.join([n.label for n in self.adjacencyList[l]])
            s += f'{l} -> [{al}]\n'

        return s 


class TestGraph(unittest.TestCase):

    def test_init(self):
        g = Graph()
        g.AddVertex('A')
        g.AddVertex('B')
        g.AddVertex('C')
        g.AddVertex('D')

        self.assertEqual(len(g.vertices.keys()), 4)
        self.assertEqual(len(g.adjacencyList.keys()), 4)

        g.addEdge('A', 'C')
        g.addEdge('A', 'D')
        g.addEdge('B', 'D')

        self.assertEqual(g.deathFirsTraversal(), ['A', 'D', 'B', 'C'])
        self.assertEqual(g.breadFirsTraversal(), ['A', 'C', 'D', 'B'])


    def test_topologicalSort(self):
        g = Graph(True)
        g.AddVertex('X')
        g.AddVertex('A')
        g.AddVertex('B')
        g.AddVertex('P')

        g.addEdge('X', 'A')
        g.addEdge('X', 'B')
        g.addEdge('A', 'P')
        g.addEdge('B', 'P')

        self.assertEqual(g.topologicalSort(), 'X->B->A->P')

    def test_cycle(self):
        g = Graph(True)
        g.AddVertex('A')
        g.AddVertex('B')
        g.AddVertex('C')
        self.assertEqual(g.hasCycle(), False)

        g.addEdge('A', 'B')
        g.addEdge('B', 'C')
        g.addEdge('A', 'C')
        self.assertEqual(g.hasCycle(), False)

        g.removeEdge('A', 'C')
        g.addEdge('C', 'A')
        self.assertEqual(g.hasCycle(), True)

        

if __name__ == '__main__':
    unittest.main()