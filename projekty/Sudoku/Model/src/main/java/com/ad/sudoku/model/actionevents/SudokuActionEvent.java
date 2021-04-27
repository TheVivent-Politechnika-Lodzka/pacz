package com.ad.sudoku.model.actionevents;

import java.awt.event.ActionEvent;

public class SudokuActionEvent extends ActionEvent {

    private int row;
    private int col;
    private boolean isInsertedValueCorrect;

    public SudokuActionEvent(Object source, int id, String command,
                             int row, int col, boolean isInsertedValueCorrect) {
        super(source, id, command);
        this.row = row;
        this.col = col;
        this.isInsertedValueCorrect = isInsertedValueCorrect;
    }

    public int getRow() {
        return row;
    }

    public int getCol() {
        return col;
    }

    public boolean isInsertedValueCorrect() {
        return isInsertedValueCorrect;
    }
}
