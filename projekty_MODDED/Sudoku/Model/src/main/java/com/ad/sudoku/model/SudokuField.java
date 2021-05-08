package com.ad.sudoku.model;

import com.ad.sudoku.model.exceptions.SudokuFieldException;
import com.ad.sudoku.model.exceptions.SudokuNullPointerException;
import com.google.common.base.MoreObjects;
import com.google.common.base.Objects;
import java.beans.PropertyChangeListener;
import java.beans.PropertyChangeSupport;
import java.io.Serializable;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.Id;
import javax.persistence.JoinColumn;
import javax.persistence.ManyToOne;
import javax.persistence.Table;
import javax.persistence.Transient;

@Entity
@Table
public class SudokuField implements Serializable, Comparable<SudokuField>, Cloneable {

    @Id
    @GeneratedValue
    private long id;

    @ManyToOne
    @JoinColumn(name = "sudokuboard_id")
    private SudokuBoard board;

    private int value = 0;

    @Transient
    private PropertyChangeSupport notifier;
    private static final Logger logger = Logger.getLogger(SudokuField.class.getName(),
            "com.ad.sudoku.model.lang.sudokuLoggerLocale");

    public SudokuField() {
        logger.finest("SudokuField.constructor.creating");
        this.notifier = new PropertyChangeSupport(this);
        logger.finest("SudokuField.constructor.created");
    }

    public long getId() {
        return id;
    }

    public void setId(long id) {
        this.id = id;
    }

    public void setBoard(SudokuBoard board) {
        this.board = board;
    }

    public void addPropertyChangeListener(PropertyChangeListener listener) {
        notifier.addPropertyChangeListener(listener);
    }

    public void removePropertyChangeListener(PropertyChangeListener listener) {
        notifier.removePropertyChangeListener(listener);
    }

    public int getValue() {
        return value;
    }

    public void setValue(int value) {

        if (value < 0 || value > 9) {
            SudokuFieldException e = new SudokuFieldException(
                    "SudokuFieldException.val", value);
            logger.log(Level.SEVERE, "SudokuField.setValue.failure.communicate",
                    new Object[]{value});
            logger.log(Level.SEVERE, "SudokuField.setValue.failure.exception", e);
            throw e;
        }

        int oldValue = this.value;
        this.value = value;
        notifier.firePropertyChange("value", oldValue, value);

        logger.log(Level.INFO, "SudokuField.setValue.success.communicate",
                new Object[]{oldValue, value});

    }

    @Override
    public String toString() {
        return MoreObjects.toStringHelper(this)
                .add("value", value)
                .toString();
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) {
            return true;
        }
        if (o == null || getClass() != o.getClass()) {
            return false;
        }
        SudokuField that = (SudokuField) o;
        return value == that.value;
    }

    @Override
    public int hashCode() {
        return Objects.hashCode(value);
    }

    @Override
    public int compareTo(SudokuField o) {
        try {
            return Integer.compare(this.getValue(), o.getValue());
        } catch (NullPointerException e) {
            SudokuNullPointerException wrapper =
                    new SudokuNullPointerException("SudokuNullPointerException.compare", e);
            logger.log(Level.SEVERE, "SudokuField.comapareTo.NullPointerException", e);
            throw wrapper;
        }
    }

    @Override
    public SudokuField clone() throws CloneNotSupportedException {
        return (SudokuField) super.clone();
    }
}
