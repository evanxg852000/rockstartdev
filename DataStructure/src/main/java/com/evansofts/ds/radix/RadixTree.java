package com.evansofts.ds.radix;

import java.util.AbstractMap;
import java.util.HashMap;
import java.util.Map;

public class RadixTree<T> {
    Node<T> root;
    int size;

    public RadixTree(){
        root = new Node<>();
        size = 0;
    }

    public static <V> RadixTree<V> from(Map<String, V> entries) {
        RadixTree<V> tree = new RadixTree<>();
        if(entries == null)
            return tree;
        for(Map.Entry<String, V> entry : entries.entrySet()) {
            tree.insert(entry.getKey(), entry.getValue());
        }
        return tree;
    }

    public int size() {
        return size;
    }

    public boolean insert(String key, T value) {
        Node<T> parent = null;
        Node<T> node = root;
        String search = key;

        while (true) {
            //handle key exhaustion
            if(search.length() == 0) {
                if(node.isLeaf()) {
                    node.leaf.setValue(value);
                    return true;
                }

                node.leaf = new LeafNode<>(key, value);
                size++;
                return false;
            }

            //look for corresponding edge
            parent = node;
            node = node.getEdge(search.charAt(0));

            //no edge, create on
            if(node == null) {
                Edge<T> e = new Edge<>(search.charAt(0));
                e.node = new Node<>(search, new LeafNode<>(key, value));
                parent.addEdge(e);
                size++;
                return false;
            }

            // Determine longest prefix of the search key on match
            int commonPrefix = this.commonPrefix(search, node.prefix);
            if(commonPrefix == node.prefix.length()) {
                search = search.substring(commonPrefix);
                continue;
            }

            //split the node
            size++;
            Node<T> child = new Node<>(search.substring(0, commonPrefix));
            parent.updateEdge(search.charAt(0), child);



            // Restore the existing node
            child.addEdge(new Edge<>(node.prefix.charAt(commonPrefix), node));
            node.prefix = node.prefix.substring(commonPrefix);

            // Create a new leaf node
            LeafNode<T> leaf = new LeafNode<>(key, value);

            // If the new key is a subset, add to this node
            search = search.substring(commonPrefix);
            if(search.length() == 0){
                child.leaf = leaf;
                return false;
            }

            // Create a new edge for the node
            child.addEdge(new Edge<>(search.charAt(0), new Node<>(search, leaf)));
            return false;
        }
    }

    public boolean delete(String key){
        Node<T> parent = null;
        char label = 0;
        Node<T> node = root;
        String search = key;
        boolean found = false;

        while (true) {
            //check for key exhaustion
            if(search.length() == 0){
                if(node.isLeaf())
                    found = true;
                break;
            }

            // look for an edge
            parent = node;
            label = search.charAt(0);
            node = node.getEdge(label);
            if(node == null) {
                break;
            }

            // consume the search prefix
            if(search.startsWith(node.prefix)) {
                search = search.substring(node.prefix.length());
            } else {
                break;
            }
        }
        if(!found)
            return false;

        // delete the leaf
        LeafNode<T> leaf = node.leaf;
        node.leaf = null;
        size--;

        // check if we should delete this node from the parent
        if(parent != null && node.edges.size() == 0){
            parent.deleteEdge(label);
        }

        // check if we should merge this node
        if(node != root && node.edges.size() == 1) {
            node.mergeChild();
        }

        // check if we should merge the parent's other child
        if(parent != null && parent != root && parent.edges.size() == 1 && !parent.isLeaf()) {
            parent.mergeChild();
        }

        return true;
    }

    public T get(String key) {
        Node<T> node = root;
        String search = key;

        while (true) {
            //check key exhaustion
            if(search.length() ==0 ){
                if(node.isLeaf())
                    return node.leaf.getValue();
                break;
            }

            // look for an edge
            node = node.getEdge(search.charAt(0));
            if(node == null) {
                break;
            }

            // consume the search prefix
            if(search.startsWith(node.prefix)){
                search = search.substring(node.prefix.length());
            } else {
                break;
            }
        }
        return null;
    }

    public Map.Entry<String, T> longestPrefix(String key) {
        LeafNode<T> last = null;
        Node<T> node = root;
        String search = key;

        while(true) {
            // look for leaf node
            if(node.isLeaf()) {
                last = node.leaf;
            }

            // check for key exhaustion
            if(search.length() == 0) {
                break;
            }

            // look for an edge
            node = node.getEdge(search.charAt(0));
            if(node == null) {
                break;
            }

            // consume the search prefix
            if(search.startsWith(node.prefix)) {
                search = search.substring(node.prefix.length());
            } else {
                break;
            }
        }

        if(last != null)
            return new AbstractMap.SimpleEntry<>(last.getKey(), last.getValue());
        return null;
    }

    public Map.Entry<String, T> maximum() {
        Node<T> node = root;
        while (true) {
            if(node.isLeaf()){
                return new AbstractMap.SimpleEntry(node.leaf.getKey(), node.leaf.getValue());
            }
            int numEdge = node.edges.size();
            if(numEdge > 0) {
                node = node.edges.get(numEdge-1).node;
                continue;
            }
            break;
        }
        return null;
    }

    public Map.Entry<String, T> minimum() {
        Node<T> node = root;
        while (true) {
            if(node.isLeaf()){
                return new AbstractMap.SimpleEntry(node.leaf.getKey(), node.leaf.getValue());
            }

            if(node.edges.size() > 0) {
                node = node.edges.get(01).node;
                continue;
            }
            break;
        }
        return null;
    }

    // Walk is used to walk the tree
    public void walk(Walker<T> walker) {
        recursiveWalk(root, walker);
    }

    // WalkPrefix is used to walk the tree under a prefix
    public void walkPrefix(String prefix, Walker<T> walker) {
        Node<T> node = root;
        String search = prefix;
        while(true) {
            // check for key exhaustion
            if(search.length() == 0) {
                recursiveWalk(node, walker);
                return;
            }

            // look for an edge
            node = node.getEdge(search.charAt(0));
            if(node == null)
                return;

            // consume the search prefix
            if(search.startsWith(node.prefix)) {
                search = search.substring(node.prefix.length());
            } else if(node.prefix.startsWith(search)) { // child may be under our prefix
                recursiveWalk(node, walker);
                return;
            } else {
                break;
            }
        }
    }

    /* WalkPath is used to walk the tree, but only visiting nodes
     * from the root down to a given leaf. Where WalkPrefix walks
     * all the entries *under* the given prefix, this walks the
     * entries *above* the given prefix.
     */
    public void walkPath(String path, Walker<T> walker) {
        Node<T> node = root;
        String search = path;

        while (true) {
            // visit the leaf values if any
            if(node.isLeaf() && walker.walk(node.leaf.getKey(), node.leaf.getValue())){
                return;
            }

            // check for key exhaustion
            if(search.length() == 0) {
                return;
            }

            // look for an edge
            node = node.getEdge(search.charAt(0));
            if(node == null)
                return;

            if(search.startsWith(node.prefix)) {
                search = search.substring(node.prefix.length());
            } else {
                break;
            }
        }
    }

    public Map<String, T> toMap() {
        Map<String, T> output = new HashMap<>();
        this.walk((k, v) -> {
            output.put(k,v);
            return false;
        });
        return output;
    }

    private int commonPrefix(String k1, String k2) {
        int n = 0;
        while (n < k1.length() && n < k2.length()) {
            if(k1.charAt(n) != k1.charAt(n))
                break;
            n++;
        }
        return n;
    }

    /* recursiveWalk is used to do a pre-order walk of a node recursively.
    * Returns true if the walk should be stop
    */
    private boolean recursiveWalk(Node<T> node, Walker<T> walker) {
        // visit the leaf values if any
        if(node.isLeaf() && walker.walk(node.leaf.getKey(), node.leaf.getValue())) {
            return true;
        }

        // Recurse on the children
        for(Edge<T> edge : node.edges) {
            if(recursiveWalk(edge.node, walker)) {
                return true;
            }
        }
        return false;
    }

    public interface Walker<T> {
        boolean walk(String k, T v);
    }

}
