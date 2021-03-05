package com.evansofts.ds.radix;

public class Edge<T> implements Comparable<Edge<T>> {
    char label;
    Node<T> node;

    public Edge(char label) {
        this.label = label;
        this.node = null;
    }

    public Edge(char label, Node<T> node) {
        this.label = label;
        this.node = node;
    }

    public char getLabel() {
        return label;
    }

    public void setLabel(char label) {
        this.label = label;
    }

    public Node<T> getNode() {
        return node;
    }

    public void setNode(Node<T> node) {
        this.node = node;
    }

    public int compareTo(Edge e) {
        if(this.label > e.label)
            return 1;
        else if(this.label < e.label)
            return -1;
        else
            return 0;

    }
}
