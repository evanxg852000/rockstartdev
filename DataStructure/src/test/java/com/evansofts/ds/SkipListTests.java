package com.evansofts.ds;

import com.evansofts.ds.caching.Cache;
import com.evansofts.ds.skiplist.SkipList;
import org.junit.Test;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNull;

public class SkipListTests {

    @Test
    public void checkSkipList() {
        SkipList<String, Object> list =  new SkipList<>(10);
        list.put("name", "Jane");
        list.put("age", "23");
        list.put("color", "Blue");

        assertEquals(list.get("name"), "Jane");
        assertEquals(list.get("age"), "23");

        // make some update
        list.put("color", "Orange");
        list.put("age", "25");

        assertEquals(list.get("name"), "Jane");
        assertEquals(list.get("age"), "25");
        assertEquals(list.get("color"), "Orange");

        assertNull(list.get("notExist"));

        // remove
        list.remove("color");
        list.remove("age");

        assertNull(list.get("color"));
        assertNull(list.get("age"));

        assertEquals(list.entries().toString(), "[name=Jane]");
    }

}
