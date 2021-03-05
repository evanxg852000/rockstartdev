package com.evansofts.ds.caching;

import java.util.BitSet;
import java.util.Random;

public class BloomFilter<K> {
    private BitSet data;
    private int[] seeds;
    private int size;

    public BloomFilter(int capacity, int hashNum) {
        data = new BitSet(capacity);
        seeds = new int[hashNum];
        Random random = new Random(System.currentTimeMillis());
        for(int i=0; i< hashNum; i++) {
            seeds[i] = random.nextInt();
        }
        size = capacity;
    }

    public void put(K key) {
        for(int i = 0; i < seeds.length; i++) {
            int idx = hash(key, seeds[i], size);
            data.set(idx);
        }
    }

    public boolean mightContain(K key) {
        for(int i = 0; i < seeds.length; i++) {
            int idx = hash(key, seeds[i], size);
            if(!data.get(idx))
                return false;
        }
        return true;
    }

    private int hash(K key, int seed, int size) {
        return Math.abs((key.hashCode() * seed) % size);
    }

}
