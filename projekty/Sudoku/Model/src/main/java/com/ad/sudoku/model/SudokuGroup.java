package com.ad.sudoku.model;

import com.google.common.base.MoreObjects;
import com.google.common.base.Objects;
import java.util.Arrays;

public abstract class SudokuGroup implements Cloneable {

    protected SudokuField[] group;

    @Override
    public boolean equals(Object o) {
        if (this == o) {
            return true;
        }
        if (o == null || getClass() != o.getClass()) {
            return false;
        }
        SudokuGroup that = (SudokuGroup) o;
        return Arrays.equals(group, that.group);
    }

    @Override
    public int hashCode() {
        return Objects.hashCode(group);
    }

    @Override
    public String toString() {
        return MoreObjects.toStringHelper(this)
                .add("group", group)
                .toString();
    }

    public SudokuGroup(SudokuField[] group) {
        this.group = new SudokuField[group.length];
        for (int i = 0; i < group.length; i++) {
            try {
                this.group[i] = (SudokuField) group[i].clone();
            } catch (CloneNotSupportedException e) {
                e.printStackTrace();
            }
        }
    }

    public boolean verify() {
        int[] numberCounter = new int[10];
        for (SudokuField x : group) {
            if (x.getValue() == 0) {
                continue;
            }
            if (numberCounter[x.getValue()] == 1) {
                return false;
            }
            numberCounter[x.getValue()]++;
        }
        return true;
    }

    @Override
    protected SudokuGroup clone() throws CloneNotSupportedException {
        return (SudokuGroup) super.clone();
    }
}
