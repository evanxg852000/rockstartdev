package com.evansofts.ds.radix;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class Node<T> {
    String prefix;
    LeafNode<T> leaf;
    List<Edge<T>> edges;

    public Node() {
        prefix = "";
    }

    public Node(String prefix) {
        this.prefix = prefix;
    }

    public Node(String prefix, LeafNode<T> leaf) {
        this.prefix = prefix;
        this.leaf = leaf;
    }

    public boolean isLeaf() {
        return leaf != null;
    }

    public void addEdge(Edge e) {
        if(edges == null)
            edges = new ArrayList<>();
        edges.add(e);
        //TODO: may not be needed
        //this.edges.sort(Comparator.comparing(Edge::getLabel));
    }

    public void updateEdge(char label, Node node) {
        int idx = Collections.binarySearch(edges, new Edge<>(label));
        if(idx == -1) {
            throw new RuntimeException("replacing missing edge");
        }
        this.edges.get(idx).node = node;
    }

    public Node<T> getEdge(char label) {
        int idx = Collections.binarySearch(edges, new Edge<>(label));
        if(idx == -1) {
            return null;
        }
        return edges.get(idx).node;
    }

    public void deleteEdge(char label) {
        int idx = Collections.binarySearch(edges, new Edge<>(label));
        if(idx == -1) {
            return;
        }
        edges.remove(idx);
        if(edges.size() == 0)
            edges = null;
    }

    public void mergeChild() {
        Edge<T> e = edges.get(0);
        Node<T> child = e.node;
        prefix = prefix + child.prefix;
        leaf = child.leaf;
        edges = child.edges;
    }

}