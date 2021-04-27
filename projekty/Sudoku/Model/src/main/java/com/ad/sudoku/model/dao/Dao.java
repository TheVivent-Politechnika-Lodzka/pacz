package com.ad.sudoku.model.dao;

import java.util.List;

public interface Dao<T> extends AutoCloseable {

    T read();

    void write(T obj);

    @Override
    default void close() throws Exception {
        //elo
    }

}
