package com.ad.sudoku.model;

import java.util.Random;
import java.util.ResourceBundle;

public enum Difficulty {

    EASY("difficulty.easy", 5),
    MEDIUM("difficulty.medium", 10),
    HARD("difficulty.hard", 15),
    SUPERHARD("difficulty.superhard", 30);

    private final String text;
    private final int emptyFields;

    Difficulty(String text, int emptyFields) {
        this.text = text;
        this.emptyFields = emptyFields;
    }

    public int getEmptyFields() {
        return emptyFields;
    }

    @Override
    public String toString() {
        ResourceBundle bundle = ResourceBundle.getBundle(
                "com.ad.sudoku.model.lang.sudokuDifficultyLocale");
        return bundle.getString(text);
    }

    public void startGame(SudokuBoard board) {
        Random r = new Random();

        board.solveGame();
        while (countEmptySpaces(board) != emptyFields) {
            board.set(r.nextInt(9), r.nextInt(9), 0);
        }
    }

    private int countEmptySpaces(SudokuBoard board) {
        int result = 0;
        for (int i = 0; i < SudokuBoard.SIZE; i++) {
            for (int j = 0; j < SudokuBoard.SIZE; j++) {
                if (board.get(i, j) == 0) {
                    result++;
                }
            }
        }
        return result;
    }

}
