package com.ad.sudoku.model;

public class SudokuColumn extends SudokuGroup implements Cloneable {

    public SudokuColumn(SudokuField[] group) {
        super(group);
    }

    @Override
    protected SudokuColumn clone() throws CloneNotSupportedException {
        return (SudokuColumn) super.clone();
    }
}
