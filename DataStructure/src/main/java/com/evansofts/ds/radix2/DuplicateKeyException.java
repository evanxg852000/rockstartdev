package com.evansofts.ds.radix2;


public class DuplicateKeyException extends RuntimeException {
    private static final long serialVersionUID = 3141795907493885706L;

    public DuplicateKeyException(String msg){
        super(msg);
    }
}