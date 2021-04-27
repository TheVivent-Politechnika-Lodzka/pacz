package com.ad.sudoku.model.exceptions;

public class SudokuFieldException extends SudokuException {

    private Integer value;

    public SudokuFieldException(String message, Integer value) {
        super(message);
        this.value = value;
    }

    @Override
    public String getMessage() {
        return super.getMessage().replace("{0}", value.toString());
    }
}
