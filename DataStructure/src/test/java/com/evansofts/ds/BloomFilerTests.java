package com.evansofts.ds;
import com.evansofts.ds.caching.BloomFilter;
import org.junit.Test;

import static org.junit.Assert.*;


public class BloomFilerTests {

    @Test
    public void checkBloomFilter() {
        BloomFilter<String> bloomFilter = new BloomFilter<>(100, 3);
        bloomFilter.put("name");
        bloomFilter.put("color");
        bloomFilter.put("age");
        bloomFilter.put("height");
        bloomFilter.put("size");

        assertTrue(bloomFilter.mightContain("name"));
        assertTrue(bloomFilter.mightContain("size"));
        assertTrue(bloomFilter.mightContain("age"));

        assertFalse(bloomFilter.mightContain("gea"));
        assertFalse(bloomFilter.mightContain("length"));
    }

}
