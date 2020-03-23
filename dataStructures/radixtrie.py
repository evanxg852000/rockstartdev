import unittest

class Node:

    def __init(self, k, v):
        self.prefix = None
        self.kv = (k, v)
        self.parent = None
        self.children = {}
        
    def isLeaf(self):
        return len(self.children.keys) == 0
    
    def keyWithLongestCommonPrefix(self, key):
        pass

class RadixTree:

    def __init__(self):
        self.root = Node(None, None)

    def put(self, k, v):
        cn = self.root
        rem = k
        while True:
            pfx = cn.keyWithLongestCommonPrefix(rem)
            if pfx == None:
                cn.nodes[k] = Node(k, v, cn)
                break
            else:
                if len(rem) > len(pfx): 
                    # kepp going down the tree
                    rem = rem.replace(pfx, '')
                    cn = cn.nodes[pfx]
                elif len(rem) < len(pfx): 
                    # need to make room for this node
                    oldPfx = pfx.replace(rem, '')
                    oldNode = cn.nodes[pfx]
                    newNode = Node(k, v)
                    newNode.children[oldPfx] = oldNode
                    del cn.nodes[pfx]
                    cn.nodes[rem] = newNode
                    break;
                else:
                    #update the value
                    cn.nodes[pfx].kv = (k, v)
                    break

            




        self._put(self.root, newNode, k)


        

        parent = self.root
        
        while cn != None and cn.isLeaf() == False:
            rem = k.replace(pf, '')
            pf, cn = self.longest_prefix(cn.nodes, rem)
    
    def _put(self, node, newNode, rem):
        (pf, cn) = self.longest_prefix(node.nodes, rem)
        if cn == None:
            node.nodes.append(newNode)


        (pf, cn) = self.longest_prefix(node.nodes, rem)
        if cn == None:
            node.nodes.append(newNode)
            return nodes
        else:
            cn = self._put(self, cn, newNode, rem.replace(pf, '')):


    def get(self, k):
        pass

    def remove(self, k):
        pass


    def longest_prefix(self, nodes, key):
        lpfx = ''
        filtered_nodes = []
        for i in range(len(key)):
            lpfx = key[:i+1]
            nodes = [n for n in nodes if n.prefix.startswith(lpfx)]
            if len(nodes) > 0:
                filtered_nodes = nodes
            else:
                lpfx = lpfx[:-1]
                break

        filtered_nodes = [n for n in filtered_nodes if n.prefix.startswith(lpfx)]
        return (lpfx, filtered_nodes[0]) if len(filtered_nodes) > 0 else (None, None)


    

class TestRadixTrie(unittest.TestCase):

    def test_init(self):
        rdx = RadixTrie()
        self.assertEqual(rdx.root.prefix, '')
        self.assertEqual(rdx.root.nodes, [])

    def test_put(self):
        rdx = RadixTrie()
        rdx.put('plan', 1)
        rdx.put('plato', 1)
        rdx.put('plant', 1)
        print(rdx)

    def test_longest_prefix(self):
        rdx = RadixTrie()
        (lpfx, n) = rdx.longest_prefix([Node('plan'), Node('plato')], 'plant')
        self.assertEqual(lpfx, 'plan')
        self.assertEqual(n.prefix, 'plan')

        (lpfx, n) = rdx.longest_prefix([Node('plant'), Node('plan')], 'plato')
        self.assertEqual(lpfx, 'pla')
        self.assertEqual(n.prefix.startswith('plan'), True)

        (lpfx, n) = rdx.longest_prefix([Node('plant'), Node('plan')], 'plantin')
        self.assertEqual(lpfx, 'plant')
        self.assertEqual(n.prefix, 'plant')


if __name__ == '__main__':
    unittest.main()