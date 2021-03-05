package com.evansofts.ds;

import com.evansofts.ds.caching.Cache;
import org.junit.Test;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNull;


public class CacheTests {

    @Test
    public void checkLRU() {
        Cache<String, Object> cache =  Cache.LRUFrom(3);
        cache.put("name", "Jhon");
        cache.put("age", "23");
        cache.put("color", "Blue");

        assertEquals(cache.get("name"), "Jhon");
        assertEquals(cache.get("age"), "23");

        //make some update
        cache.put("color", "Orange");
        cache.put("age", "25");

        assertEquals(cache.get("name"), "Jhon");
        assertEquals(cache.get("age"), "25");
        assertEquals(cache.get("color"), "Orange");

        cache.put("sex", "M");
        assertNull(cache.get("name"));
    }

    @Test
    public void checkMRU() {
        Cache<String, Object> cache =  Cache.MRUFrom(3);
        cache.put("name", "Jhon");
        cache.put("age", "23");
        cache.put("color", "Blue");

        assertEquals(cache.get("name"), "Jhon");
        assertEquals(cache.get("age"), "23");

        //make some update
        cache.put("color", "Orange");
        cache.put("age", "25");

        assertEquals(cache.get("name"), "Jhon");
        assertEquals(cache.get("age"), "25");
        assertEquals(cache.get("color"), "Orange");

        cache.put("sex", "M");
        assertNull(cache.get("color"));
    }


}




