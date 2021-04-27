package com.ad.sudoku.model.exceptions;

import java.util.MissingResourceException;
import java.util.ResourceBundle;

public class SudokuException extends RuntimeException {

    public SudokuException(String message) {
        super(message);
    }

    public SudokuException(String message, Throwable cause) {
        super(message, cause);
    }

    @Override
    public String getMessage() {
        ResourceBundle rb = ResourceBundle.getBundle(
                "com.ad.sudoku.model.lang.sudokuExceptionLocale");
        try {
            return rb.getString(super.getMessage());
        } catch (MissingResourceException e) {
            return super.getMessage();
        }
    }

}
