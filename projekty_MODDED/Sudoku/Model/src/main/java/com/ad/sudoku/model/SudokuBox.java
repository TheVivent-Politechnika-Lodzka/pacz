package com.ad.sudoku.model;

public class SudokuBox extends SudokuGroup implements Cloneable {

    public SudokuBox(SudokuField[] group) {
        super(group);
    }

    @Override
    public SudokuBox clone() throws CloneNotSupportedException {
        return (SudokuBox) super.clone();
    }
}
