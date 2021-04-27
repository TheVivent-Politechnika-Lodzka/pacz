import com.ad.sudoku.model.*;
import com.ad.sudoku.model.exceptions.SudokuException;
import com.ad.sudoku.model.solvers.BacktrackingSudokuSolver;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;
import static org.junit.jupiter.api.Assertions.assertTrue;

public class SudokuGroupTest {

    @Test
    void equalsTest() {
        SudokuBoard board = new SudokuBoard(new BacktrackingSudokuSolver());
        board.solveGame();

        SudokuGroup row1 = board.getRow(1);
        SudokuGroup row2 = board.getRow(1);
        SudokuGroup row3 = board.getRow(2);
        SudokuGroup row4 = board.getRow(1);

        //test zwrotności
        assertEquals(row1, row1);

        //test symetryczności
        assertEquals(row2, row1);
        assertEquals(row1, row2);

        //test przechodniości
        assertEquals(row2, row1);
        assertEquals(row4, row2);
        assertEquals(row1, row4);

        //test na null (negative)
        assertNotEquals(row1, null);

        //test porównania z obiektem innej klasy (negative)
        String test = "lol";
        assertNotEquals(test, row1);

        //test negatywny
        assertNotEquals(row3, row1);
    }

    @Test
    void hashCodeTest(){
        SudokuBoard board = new SudokuBoard(new BacktrackingSudokuSolver());
        board.solveGame();

        SudokuGroup row1 = board.getRow(1);
        SudokuGroup row2 = board.getRow(1);
        SudokuGroup row3 = board.getRow(2);

        //test hashCode(sprawdza tylko value w Field)
        assertEquals(row2.hashCode(), row1.hashCode());
        assertNotEquals(row3.hashCode(), row1.hashCode());

    }

    @Test
    void toStringTest() {
        SudokuBoard board = new SudokuBoard(new BacktrackingSudokuSolver());
        board.solveGame();

        SudokuGroup row = board.getRow(1);
        assertTrue(row.toString().length() > 0);
    }

    @Test
    void cloneTest() throws CloneNotSupportedException {
        SudokuBoard board = new SudokuBoard(new BacktrackingSudokuSolver());
        board.solveGame();

        SudokuRow row = board.getRow(0);
        SudokuRow clonedRow = row.clone();
        assertEquals(board.getRow(0), clonedRow);
        board.set(0, 0, 0);
        assertNotEquals(board.getRow(0), clonedRow);
        board.solveGame();


        SudokuBox box = board.getBox(0, 0);
        SudokuBox clonedBox = box.clone();
        assertEquals(box, clonedBox);
        assertNotEquals(board.getBox(0, 0), clonedRow);
        board.solveGame();


        SudokuColumn col = board.getColumn(0);
        SudokuColumn clonedCol = board.getColumn(0);
        assertEquals(col, clonedCol);
        assertNotEquals(board.getColumn(0), clonedRow);

    }

    @Test
    public void verifyTest() {
        // utwórz i wypełnij tablice z SudokuFieldami
        SudokuField[] fields = new SudokuField[9];
        for(int i=0;i<9;i++){
            fields[i] = new SudokuField();
            fields[i].setValue(i+1);
        }

        // to powinno działać
        SudokuRow row = new SudokuRow(fields);
        assertTrue(row.verify());

        // tutaj jest 2 razy 1 więc nie będzie działać
        fields[8].setValue(1);
        row = new SudokuRow(fields);
        assertFalse(row.verify());

        // zera są ignorowane
        // wiec powinno działać
        fields[8].setValue(0);
        row = new SudokuRow(fields);
        assertTrue(row.verify());

    }
}
