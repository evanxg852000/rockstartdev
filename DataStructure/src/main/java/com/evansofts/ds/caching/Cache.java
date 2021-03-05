package com.evansofts.ds.caching;

import java.util.*;

public class Cache<K, V> {
    private enum Policy { LRU, MRU }
    private int capacity;
    private Policy policy;
    private Map<K, V> data;
    private LinkedList<K> rank;


    Cache(int capacity, Policy policy) {
        this.capacity = capacity;
        this.policy = policy;
        this.data = new HashMap<>();
        this.rank = new LinkedList<>();
    }

    public static<K, V> Cache<K, V> LRUFrom(int capacity){
        return new Cache<>(capacity, Policy.LRU);
    }

    public static<K, V> Cache<K, V> MRUFrom(int capacity){
        return new Cache<>(capacity, Policy.MRU);
    }

    public synchronized void put(K key, V value) {
        if(data.containsKey(key)) {
            rank.remove(key);
            rank.addLast(key);
            data.put(key, value);
            return;
        }
        if(data.size() == capacity) {
            K e;
            if(policy == Policy.LRU)
                e = rank.removeFirst();
            else
                e = rank.removeLast();
            data.remove(e);
        }
        rank.addLast(key);
        data.put(key, value);
    }

    public synchronized V get(K key) {
        if(!data.containsKey(key))
            return null;
        rank.remove(key);
        rank.addLast(key);
        return data.get(key);
    }

}
