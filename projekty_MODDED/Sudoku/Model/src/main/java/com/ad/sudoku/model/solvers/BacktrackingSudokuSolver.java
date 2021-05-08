package com.ad.sudoku.model.solvers;

import com.ad.sudoku.model.SudokuBoard;
import com.google.common.base.MoreObjects;
import com.google.common.base.Objects;
import java.io.Serializable;
import java.util.Collections;
import java.util.Iterator;
import java.util.Stack;

public class BacktrackingSudokuSolver implements SudokuSolver, Serializable {

    SudokuBoard tmpBoard;

    @Override
    public boolean equals(Object o) {
        if (this == o) {
            return true;
        }
        if (o == null || getClass() != o.getClass()) {
            return false;
        }
        return true;
    }

    @Override
    public int hashCode() {
        return Objects.hashCode(this.getClass());
    }

    @Override
    public String toString() {
        return MoreObjects.toStringHelper(this)
                .add("type", this.getClass())
                .toString();
    }

    private Stack randomTmpArray() {
        Stack<Integer> stack = new Stack<>();
        for (int i = 0; i < SudokuBoard.SIZE; i++) {
            stack.push(i + 1);
        }
        Collections.shuffle(stack);
        return stack;
    }

    private boolean fillGaps(int row, int col) {
        //jezeli badany element jest "predefiniowany"
        if (tmpBoard.get(row, col) != 0) {
            if (col == 8 && row == 8) {
                return true;
            }
            if (col == 8) {
                return fillGaps(row + 1, 0);
            } else {
                return fillGaps(row, col + 1);
            }
        }

        //jak jest zerem, czyli pusty
        Iterator value = randomTmpArray().iterator();
        while (value.hasNext()) {
            tmpBoard.set(row, col, (int) value.next());
            if (tmpBoard.getRow(row).verify()
                    && tmpBoard.getColumn(col).verify()
                    && tmpBoard.getBox(row, col).verify()
            ) {

                if (col == 8 && row == 8) {
                    return true;
                }
                if (col == 8 && fillGaps(row + 1, 0)) {
                    return true;
                }
                if (col != 8 && fillGaps(row, col + 1)) {
                    return true;
                }
            }
        }
        tmpBoard.set(row, col, 0);
        return false;
    }

    @Override
    public boolean solve(SudokuBoard board) {
        this.tmpBoard = board;
        if (!fillGaps(0, 0)) {
            return false;
        }

        int test = 0;
        for (int i = 0; i < SudokuBoard.SIZE; i++) {
            for (int j = 0; j < SudokuBoard.SIZE; j++) {
                if (board.getRow(j).verify()) {
                    test++;
                }
                if (board.getColumn(i).verify()) {
                    test++;
                }
                if (board.getBox(i, j).verify()) {
                    test++;
                }
            }
        }
        return test == 3 * 81;
    }

}
