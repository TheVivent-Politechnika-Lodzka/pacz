package com.ad.sudoku.model;

import java.util.Arrays;

public class SudokuRow extends SudokuGroup implements Cloneable {

    public SudokuRow(SudokuField[] group) {
        super(group);
    }

    @Override
    public SudokuRow clone() throws CloneNotSupportedException {
        return (SudokuRow) super.clone();
    }
}
