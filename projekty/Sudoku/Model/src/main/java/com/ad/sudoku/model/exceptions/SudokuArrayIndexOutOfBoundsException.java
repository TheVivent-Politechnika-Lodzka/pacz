package com.ad.sudoku.model.exceptions;

public class SudokuArrayIndexOutOfBoundsException extends SudokuException {

    private Integer row;
    private Integer col = 0;

    public SudokuArrayIndexOutOfBoundsException(String message, int row, int col, Throwable cause) {
        super(message, cause);
        this.row = row;
        this.col = col;
    }

    public SudokuArrayIndexOutOfBoundsException(String message, int row, Throwable cause) {
        super(message, cause);
        this.row = row;
    }

    @Override
    public String getMessage() {
        return super.getMessage()
                .replace("{0}", row.toString())
                .replace("{1}", col.toString());
    }
}
