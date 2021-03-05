package com.evansofts.ds.skiplist;

import java.util.*;

public class SkipList<K extends Comparable, V> {
    private int maxLevel;
    private Random random;
    private Node<K, V> head;
    private Node<K, V> tail;


    public SkipList(int maxLevel) {
        this.maxLevel = maxLevel;
        random = new Random(System.currentTimeMillis());
        head = new Node<>(null, null, maxLevel);
        tail = new Node<>(null, null, maxLevel);
        // create links between head -> tail
        for(int i = 0; i < maxLevel; i++) {
            head.nextLinks[i] = tail;
            tail.previous = head;
        }
    }

    public void put(K k, V v) {
        //find node or lowest level of insertion
        Node<K, V> currentNode = findTerminal(k);
        if(currentNode.key != null && currentNode.key.equals(k)){
            currentNode.value = v;
            return;
        }

        // insert tower after found terminal
        int level = chooseLevel();
        Node<K, V> newNode = new Node<>(k, v, level);
        int currentLevel = 0;
        while(currentLevel < level) {
            // if current tower is lower then
            // find higher tower before it (currentNode)
            while(currentNode.nextLinks.length - 1 < currentLevel){
                currentNode = currentNode.previous;
            }

            // wire up doubly link
            newNode.nextLinks[currentLevel] = currentNode.nextLinks[currentLevel];
            currentNode.nextLinks[currentLevel].previous = newNode;
            newNode.previous = currentNode;
            currentNode.nextLinks[currentLevel] = newNode;

            currentLevel += 1;
        }
    }

    public V get(K k) {
        Node<K, V> currentNode = findTerminal(k);
        if(currentNode.key != null && currentNode.key.equals(k))
            return currentNode.value;
        return null;
    }

    public void remove(K k){
        Node<K, V> currentNode = findTerminal(k);
        if(currentNode.key != null && !currentNode.key.equals(k))
            return;

        int currentLevel = 0;
        int level = currentNode.nextLinks.length;
        while(currentLevel < level) {
            currentNode.previous.nextLinks[currentLevel] = currentNode.nextLinks[currentLevel];
            currentNode.nextLinks[currentLevel].previous = currentNode.previous;
            currentLevel += 1;
        }
    }

    public List<AbstractMap.SimpleEntry> entries() {
        List<AbstractMap.SimpleEntry> output = new ArrayList<>();
        Node<K, V> currentNode = head;
        while (currentNode != null) {
            if(currentNode.key != null) {
                output.add(new AbstractMap.SimpleEntry(currentNode.key, currentNode.value));
            }
            currentNode  = currentNode.nextLinks[0];
        }
        return output;
    }


    private int chooseLevel() {
        int level = 1;
        while(random.nextInt(2) != 1 && level < maxLevel)
            level++;
        return level;
    }

    private Node<K, V> findTerminal(K k){
        int currentLevel = maxLevel - 1;
        Node<K, V> currentNode = head;
        while(currentLevel >= 0) {
            if(currentNode.nextLinks[currentLevel].key != null &&
                    currentNode.nextLinks[currentLevel].key.equals(tail.key)) {
                currentLevel -= 1;
                continue;
            }

            if(currentNode.nextLinks[currentLevel].key != null &&
                    currentNode.nextLinks[currentLevel].key.compareTo(k) <= 0) {
                currentNode = currentNode.nextLinks[currentLevel];
                continue;
            }

            currentLevel -= 1;
        }
        return currentNode;
    }

    private class Node<K, V> {
        private K key;
        private V value;
        private Node<K, V>[] nextLinks;
        private Node<K, V> previous;

        public Node(K k, V v, int level) {
            key = k;
            value = v;
            nextLinks = new Node[level];
        }
    }
}
