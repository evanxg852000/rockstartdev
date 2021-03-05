package com.evansofts.ds.radix2;

import java.util.ArrayList;
import java.util.List;

/**
 * Represents a node of a Radix tree {@link RadixTreeImpl}
 *
 * @author Tahseen Ur Rehman
 * @email tahseen.ur.rehman {at.spam.me.not} gmail.com
 * @param <T>
 */
class RadixTreeNode<T> {
    private String key;
    private List<RadixTreeNode<T>> childern;
    private boolean real;
    private T value;
    /**
     * intailize the fields with default values to avoid null reference checks
     * all over the places
     */
    public RadixTreeNode() {
        key = "";
        childern = new ArrayList<RadixTreeNode<T>>();
        real = false;
    }
    public T getValue() {
        return value;
    }
    public void setValue(T data) {
        this.value = data;
    }
    public String getKey() {
        return key;
    }
    public void setKey(String value) {
        this.key = value;
    }
    public boolean isReal() {
        return real;
    }
    public void setReal(boolean datanode) {
        this.real = datanode;
    }
    public List<RadixTreeNode<T>> getChildern() {
        return childern;
    }
    public void setChildern(List<RadixTreeNode<T>> childern) {
        this.childern = childern;
    }
    public int getNumberOfMatchingCharacters(String key) {
        int numberOfMatchingCharacters = 0;
        while (numberOfMatchingCharacters < key.length() && numberOfMatchingCharacters < this.getKey().length()) {
            if (key.charAt(numberOfMatchingCharacters) != this.getKey().charAt(numberOfMatchingCharacters)) {
                break;
            }
            numberOfMatchingCharacters++;
        }
        return numberOfMatchingCharacters;
    }
    @Override
    public String toString() {
        return key;
    }
}