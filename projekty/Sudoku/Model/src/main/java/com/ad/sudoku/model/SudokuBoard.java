package com.ad.sudoku.model;

import com.ad.sudoku.model.actionevents.SudokuActionEvent;
import com.ad.sudoku.model.exceptions.SudokuArrayIndexOutOfBoundsException;
import com.ad.sudoku.model.solvers.BacktrackingSudokuSolver;
import com.ad.sudoku.model.solvers.SudokuSolver;
import com.google.common.base.MoreObjects;
import com.google.common.base.Objects;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import java.io.Serializable;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.persistence.CascadeType;
import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.Id;
import javax.persistence.OneToMany;
import javax.persistence.Table;
import javax.persistence.Transient;

@Entity
@Table
public class SudokuBoard implements PropertyChangeListener, Serializable, Cloneable {
    //    "stała"
    public static final int SIZE = 9;

    // logger
    private static final Logger logger = Logger.getLogger(SudokuBoard.class.getName(),
            "com.ad.sudoku.model.lang.sudokuLoggerLocale");

    @Id
    @GeneratedValue
    private long id;

    @Column(unique = true)
    private String name;

    @Transient
    private final SudokuSolver solver;

    private boolean autoCheck = false;

    @Transient
    private transient List<ActionListener> actionListeners = new ArrayList<>();

    @OneToMany(cascade = CascadeType.ALL)
    private final List<SudokuField> board = Arrays.asList(new SudokuField[81]);
    //private final List<List<SudokuField>> board = Arrays.asList(new List[9]);


    public SudokuBoard() {
        logger.finest("SudokuBoard.constructor.creating");
        this.solver = new BacktrackingSudokuSolver();
        for (int i = 0; i < SIZE * SIZE; i++) {
            board.set(i, new SudokuField());
            board.get(i).addPropertyChangeListener(this);
            board.get(i).setBoard(this);
        }
        /*for (int i = 0; i < SIZE; i++) {
            board.set(i, Arrays.asList(new SudokuField[9]));
            for (int j = 0; j < SIZE; j++) {
                board.get(i).set(j, new SudokuField());
                board.get(i).get(j).addPropertyChangeListener(this);
            }
        }*/
        logger.finest("SudokuBoard.constructor.created");
    }

    public SudokuBoard(SudokuSolver solver) {
        logger.finest("SudokuBoard.constructor.creating");
        this.solver = solver;
        for (int i = 0; i < SIZE * SIZE; i++) {
            board.set(i, new SudokuField());
            board.get(i).addPropertyChangeListener(this);
            board.get(i).setBoard(this);
        }
        /*for (int i = 0; i < SIZE; i++) {
            board.set(i, Arrays.asList(new SudokuField[9]));
            for (int j = 0; j < SIZE; j++) {
                board.get(i).set(j, new SudokuField());
                board.get(i).get(j).addPropertyChangeListener(this);
            }
        }*/
        logger.finest("SudokuBoard.constructor.created");
    }

    @Override
    public String toString() {
        return MoreObjects.toStringHelper(this)
                .add("solver", solver)
                .add("name", name)
                .add("autoCheck", autoCheck)
                .add("board", board)
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
        SudokuBoard that = (SudokuBoard) o;
        return autoCheck == that.autoCheck
                && Objects.equal(solver, that.solver)
                && Objects.equal(board, that.board);
    }

    @Override
    public int hashCode() {
        return Objects.hashCode(solver, autoCheck, board);
    }

    @Override
    public void propertyChange(PropertyChangeEvent evt) {
        //tutaj obsługa eventu
        if (!autoCheck) {
            return;
        }

        int oldValue = (int) evt.getOldValue();
        int newValue = (int) evt.getNewValue();

        SudokuField field = (SudokuField) evt.getSource();
        int i;
        int j = 0;
        outerloop:
        for (i = 0; i < SudokuBoard.SIZE; i++) {
            for (j = 0; j < SudokuBoard.SIZE; j++) {
                if (this.getField(i, j) == field) {
                    break outerloop;
                }
            }
        }
        logger.log(Level.FINE, "SudokuBoard.propertyChange",
                new Object[]{oldValue, newValue, i, j});

        setAutoCheck(false);
        for (ActionListener a : actionListeners) {
            a.actionPerformed(new SudokuActionEvent(
                    this, ActionEvent.ACTION_FIRST, "SudokuNotSolvable",
                    i, j, checkBoard()));
        }
        setAutoCheck(true);
    }

    public void addActionListener(ActionListener actionListener) {
        actionListeners.add(actionListener);
    }

    public void clearBoard() {
        logger.fine("SudokuBoard.clearBoard.cleaning");
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                set(i, j, 0);
            }
        }
        logger.fine("SudokuBoard.clearBoard.cleaned");
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public long getId() {
        return id;
    }

    public void setId(long id) {
        this.id = id;
    }

    public void setAutoCheck(boolean autoCheck) {
        logger.log(Level.INFO, "SudokuBoard.setAutoCheck",
                new Object[]{this.autoCheck, autoCheck});
        this.autoCheck = autoCheck;
    }

    public boolean isAutoCheck() {
        return autoCheck;
    }

    public SudokuField getField(int row, int col) {
        if (row < 0 || row > 8 || col < 0 || col > 8) {
            ArrayIndexOutOfBoundsException e = new ArrayIndexOutOfBoundsException();
            SudokuArrayIndexOutOfBoundsException wrapper =
                    new SudokuArrayIndexOutOfBoundsException(
                            "SudokuArrayIndexOutOfBoundsException.both", row, col, e);

            logger.log(Level.SEVERE, "SudokuBoard.ArrayIndexOutOfBoundsException.communicate",
                    new Object[]{row, col});
            logger.log(Level.SEVERE, "SudokuBoard.ArrayIndexOutOfBoundsException.exception", e);
            throw wrapper;
        }

        return board.get(row * 9 + col);
    }

    public int get(int row, int col) {
        if (row < 0 || row > 8 || col < 0 || col > 8) {
            ArrayIndexOutOfBoundsException e = new ArrayIndexOutOfBoundsException();
            SudokuArrayIndexOutOfBoundsException wrapper =
                    new SudokuArrayIndexOutOfBoundsException(
                            "SudokuArrayIndexOutOfBoundsException.both", row, col, e);

            logger.log(Level.SEVERE, "SudokuBoard.ArrayIndexOutOfBoundsException.communicate",
                    new Object[]{row, col});
            logger.log(Level.SEVERE, "SudokuBoard.ArrayIndexOutOfBoundsException.exception", e);
            throw wrapper;
        }

        return board.get(row * 9 + col).getValue();
    }

    public void set(int row, int col, int number) {
        if (row < 0 || row > 8 || col < 0 || col > 8) {
            ArrayIndexOutOfBoundsException e = new ArrayIndexOutOfBoundsException();
            SudokuArrayIndexOutOfBoundsException wrapper =
                    new SudokuArrayIndexOutOfBoundsException(
                            "SudokuArrayIndexOutOfBoundsException.both", row, col, e);

            logger.log(Level.FINE, "SudokuBoard.ArrayIndexOutOfBoundsException.communicate",
                    new Object[]{row, col});
            logger.log(Level.FINE, "SudokuBoard.ArrayIndexOutOfBoundsException.exception", e);
            throw wrapper;
        }
        board.get(row * 9 + col).setValue(number);
    }

    public SudokuRow getRow(int y) {

        if (y < 0 || y > 8) {
            ArrayIndexOutOfBoundsException e = new ArrayIndexOutOfBoundsException();
            SudokuArrayIndexOutOfBoundsException wrapper =
                    new SudokuArrayIndexOutOfBoundsException(
                            "SudokuArrayIndexOutOfBoundsException.row", y, e);

            logger.log(Level.FINE, "SudokuBoard.ArrayIndexOutOfBoundsException.row.communicate",
                    new Object[]{y});
            logger.log(Level.FINE, "SudokuBoard.ArrayIndexOutOfBoundsException.row.exception", e);
            throw wrapper;
        }

        SudokuField[] tmp = new SudokuField[SIZE];

        for (int i = 0; i < SIZE; i++) {
            tmp[i] = board.get(y * 9 + i);
            //tmp[i] = board.get(y).get(i);
        }

        return new SudokuRow(tmp);
    }

    public SudokuColumn getColumn(int x) {
        if (x < 0 || x > 8) {
            ArrayIndexOutOfBoundsException e = new ArrayIndexOutOfBoundsException();
            SudokuArrayIndexOutOfBoundsException wrapper =
                    new SudokuArrayIndexOutOfBoundsException(
                            "SudokuArrayIndexOutOfBoundsException.col", x, e);

            logger.log(Level.FINE, "SudokuBoard.ArrayIndexOutOfBoundsException.col.communicate",
                    new Object[]{x});
            logger.log(Level.FINE, "SudokuBoard.ArrayIndexOutOfBoundsException.col.exception", e);
            throw wrapper;
        }

        SudokuField[] tmp = new SudokuField[SIZE];

        for (int i = 0; i < SIZE; i++) {
            tmp[i] = board.get(i * 9 + x);
            //tmp[i] = board.get(i).get(x);
        }
        return new SudokuColumn(tmp);

    }

    public SudokuBox getBox(int x, int y) {

        if (x < 0 || x > 8 || y < 0 || y > 8) {
            ArrayIndexOutOfBoundsException e = new ArrayIndexOutOfBoundsException();
            SudokuArrayIndexOutOfBoundsException wrapper =
                    new SudokuArrayIndexOutOfBoundsException(
                            "SudokuArrayIndexOutOfBoundsException.both", x, y, e);

            logger.log(Level.FINE, "SudokuBoard.ArrayIndexOutOfBoundsException.communicate",
                    new Object[]{x, y});
            logger.log(Level.FINE, "SudokuBoard.ArrayIndexOutOfBoundsException.exception", e);
            throw wrapper;
        }

        SudokuField[] tmp = new SudokuField[SIZE];

        x = x - (x % 3);
        y = y - (y % 3);

        int k = 0;
        for (int i = x; i < x + 3; i++) {
            for (int j = y; j < y + 3; j++) {
                tmp[k++] = this.getField(i, j);
            }
        }

        return new SudokuBox(tmp);
    }

    public boolean checkBoard() {
        logger.info("SudokuBoard.checkBoard");
        SudokuBoard clonedBoard = this.clone();
        return clonedBoard.solveGame();
    }

    public boolean solveGame() {
        logger.info("SudokuBoard.solveGame");
        return solver.solve(this);
    }

    //    przepisanie, aby nie móc nadpisywać
    public int[][] getBoard() {
        int[][] copy = new int[SIZE][SIZE];
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                copy[i][j] = board.get(i * 9 + j).getValue();
                //copy[i][j] = board.get(i).get(j).getValue();
            }
        }
        return copy;
    }

    @Override
    public SudokuBoard clone() {
        SudokuBoard tmp = new SudokuBoard(this.solver);

        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                tmp.set(i, j, this.get(i, j));
            }
        }
        tmp.setAutoCheck(this.isAutoCheck());

        return tmp;
    }
}
