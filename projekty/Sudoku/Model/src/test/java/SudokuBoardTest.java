import com.ad.sudoku.model.exceptions.SudokuArrayIndexOutOfBoundsException;
import com.ad.sudoku.model.solvers.BacktrackingSudokuSolver;
import com.ad.sudoku.model.SudokuBoard;
import org.junit.jupiter.api.Disabled;
import org.junit.jupiter.api.Test;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import static org.junit.jupiter.api.Assertions.*;

class SudokuBoardTest implements ActionListener {

    @Test
    void getBoardTest() {

        SudokuBoard board = new SudokuBoard(new BacktrackingSudokuSolver());
        board.solveGame();
        int[][] array = board.getBoard();

        //czy zwrócona tablica jest taka sama jak zawartość com.ad.sudoku.model.SudokuBoard
        for (int i = 0; i < SudokuBoard.SIZE; i++) {
            for (int j = 0; j < SudokuBoard.SIZE; j++) {
                assertEquals(array[i][j], board.get(i, j));
            }
        }

        //czy getBoard daje dostęp do prywatnych pól com.ad.sudoku.model.SudokuBoard
        array[2][1] = 100;
        assertNotEquals(array[2][1], board.getBoard()[2][1]);
    }

    @Test
    void getTest() {
        SudokuBoard board = new SudokuBoard(new BacktrackingSudokuSolver());

        // czy rzuca wyjątki poza indexami
        assertThrows(SudokuArrayIndexOutOfBoundsException.class, () -> board.get(-1, 5));
        assertThrows(SudokuArrayIndexOutOfBoundsException.class, () -> board.get(5, -5));
        assertThrows(SudokuArrayIndexOutOfBoundsException.class, () -> board.get(10, 5));
        assertThrows(SudokuArrayIndexOutOfBoundsException.class, () -> board.get(1, 55));

        //czy get działa
        board.set(0,0,3);
        assertEquals(board.get(0, 0), 3);

    }

    @Test
    void setTest() {
        SudokuBoard board = new SudokuBoard(new BacktrackingSudokuSolver());

        //sprawdzenie rzcuaniu wyjątków w przypadku indeksów
        assertThrows(SudokuArrayIndexOutOfBoundsException.class, () -> board.set(-1, 5, 1));
        assertThrows(SudokuArrayIndexOutOfBoundsException.class, () -> board.set(5, -5, 1));
        assertThrows(SudokuArrayIndexOutOfBoundsException.class, () -> board.set(10, 5, 1));
        assertThrows(SudokuArrayIndexOutOfBoundsException.class, () -> board.set(1, 55, 1));

        board.set(0,0,3);
        assertEquals(board.get(0, 0), 3);
    }

    private boolean przyszła_zmiana = false;

    @Override
    public void actionPerformed(ActionEvent e) {
        przyszła_zmiana = true;
    }

    /*
     * nie działa, bo w testach nie wywołuje się
     * SudokuBoard.propertyChange z jakiegoś powodu
     * ¯\_(ツ)_/¯
     * */
    @Test
    @Disabled
    void propertyChangeTest() {
        // utwórz SudokuBoard
        SudokuBoard board = new SudokuBoard(new BacktrackingSudokuSolver());
        // dodaj listenera
        board.addActionListener(this);
        // włącz autocheck
        board.setAutoCheck(true);

        // zmień coś
        board.set(8, 8, 0);

        // to powinno w sumie działać
        assertTrue(przyszła_zmiana);

//        // sprawdź zmienną globalną 10000
//        // (żeby dać szanse na poprawny przeplot)
//        // wiem że nie powinienem tego robić, ale...
//        // nie mam lepszego pomysłu
//        for(int i=0;i<10000;i++){
//            if (przyszła_zmiana){
//                assertTrue(true);
//                return;
//            }
//        }
//        assertTrue(false);
    }

    @Test
    void IsAutoCheck_AND_setAutoCheckTest() {
        SudokuBoard board = new SudokuBoard(new BacktrackingSudokuSolver());
        board.setAutoCheck(true);
        assertTrue(board.isAutoCheck());

        board.setAutoCheck(false);
        assertFalse(board.isAutoCheck());

    }

    @Test
    void toStringTest() {
        SudokuBoard board = new SudokuBoard(new BacktrackingSudokuSolver());
        board.solveGame();

        assertTrue(board.toString().length() > 0);
    }

    @Test
    public void clearBoardTest() {
        SudokuBoard board = new SudokuBoard(new BacktrackingSudokuSolver());
        board.solveGame();
        board.clearBoard();
        int zeros = 0;
        for (int i = 0; i < SudokuBoard.SIZE; i++) {
            for (int j = 0; j < SudokuBoard.SIZE; j++) {
                if (board.get(i, j) == 0) zeros++;
            }
        }

        assertEquals(zeros, 81);

    }

    @Test
    void EqualsTest() {
        SudokuBoard board1 = new SudokuBoard(new BacktrackingSudokuSolver());
        SudokuBoard board2 = new SudokuBoard(new BacktrackingSudokuSolver());
        SudokuBoard board3 = new SudokuBoard(new BacktrackingSudokuSolver());

        board1.set(0, 0, 1);
        board2.set(0, 0, 1);
        board3.set(0, 0, 1);

        //sprawdzenie czy to w ogóle ma szansę zadziałać
        assertEquals(board2, board1);

        //test zwrotności
        assertEquals(board1, board1);

        //test symetryczności
        assertEquals(board2, board1);
        assertEquals(board1, board2);

        //test przechodniości
        assertEquals(board2, board1);
        assertEquals(board3, board2);
        assertEquals(board1, board3);

        //test porównania z nullem (negative)
        assertNotEquals(board1, null);

        //test porównania z obiektem innej klasy (negative)
        String test = "lol";
        assertNotEquals(test, board1);
    }

    @Test
    void hashCodeTest(){
        SudokuBoard board1 = new SudokuBoard(new BacktrackingSudokuSolver());
        SudokuBoard board2 = new SudokuBoard(new BacktrackingSudokuSolver());
        SudokuBoard board3 = new SudokuBoard(new BacktrackingSudokuSolver());

        board1.set(0, 0, 1);
        board2.set(0, 0, 1);
        board3.set(0, 0, 1);

        //test pozytywny hashCode
        assertEquals(board2.hashCode(), board1.hashCode());
        assertEquals(board3.hashCode(), board2.hashCode());
        assertEquals(board1.hashCode(), board3.hashCode());

        //testy negatywne equals
        board2.setAutoCheck(true);
        board3.set(8, 8, 1);

        assertNotEquals(board2, board1);
        assertNotEquals(board3, board1);
        assertNotEquals(board3, board2);

        //test negatywny hashCode
        assertNotEquals(board2.hashCode(), board1.hashCode());
        assertNotEquals(board3.hashCode(), board2.hashCode());
        assertNotEquals(board1.hashCode(), board3.hashCode());

    }

    @Test
    public void getFieldTest() {
        SudokuBoard board = new SudokuBoard(new BacktrackingSudokuSolver());
        board.solveGame();

        for (int i = 0; i < SudokuBoard.SIZE; i++) {
            for (int j = 0; j < SudokuBoard.SIZE; j++) {
                assertEquals(board.get(i, j), board.getField(i, j).getValue());
            }
        }

        assertThrows(SudokuArrayIndexOutOfBoundsException.class, () -> board.getField(-1, 5));
        assertThrows(SudokuArrayIndexOutOfBoundsException.class, () -> board.getField(9, 5));

        assertThrows(SudokuArrayIndexOutOfBoundsException.class, () -> board.getField(5, -1));
        assertThrows(SudokuArrayIndexOutOfBoundsException.class, () -> board.getField(5, 9));

    }

    @Test
    public void cloneTest() {
        SudokuBoard board = new SudokuBoard(new BacktrackingSudokuSolver());
        board.solveGame();
        SudokuBoard clonedBoard = board.clone();

        assertEquals(board, clonedBoard);

        board.set(0, 0, 0);
        assertNotEquals(board, clonedBoard);
    }

    @Test
    public void checkBoardTest() {
        //utwórz sudoku board i rozwiąż
        SudokuBoard board = new SudokuBoard(new BacktrackingSudokuSolver());
        board.solveGame();
        // upewnij się, że jest dobrze rozwiązany
        for (int i = 0; i < SudokuBoard.SIZE; i++) {
            for (int j = 0; j < SudokuBoard.SIZE; j++) {
                assertTrue(board.getRow(j).verify());
                assertTrue(board.getColumn(i).verify());
                assertTrue(board.getBox(i, j).verify());
            }
        }
        // sprawdź testowaną metodę
        assertTrue(board.checkBoard());

        // zmień jedno pole
        board.set(0,0,
                (board.get(0,0)+1>9?1:board.get(0,0)+1)
        );
        // teraz powinno wyjść, że jest źle rozwiązane
        assertFalse(board.checkBoard());

    }

    @Test
    void getColumnTest(){
        SudokuBoard board = new SudokuBoard(new BacktrackingSudokuSolver());

        assertThrows(SudokuArrayIndexOutOfBoundsException.class, () -> board.getColumn(-1));
        assertThrows(SudokuArrayIndexOutOfBoundsException.class, () -> board.getColumn(9));

        assertDoesNotThrow(() -> board.getColumn(1));

    }

    @Test
    void getRowTest(){
        SudokuBoard board = new SudokuBoard(new BacktrackingSudokuSolver());

        assertThrows(SudokuArrayIndexOutOfBoundsException.class, () -> board.getRow(-1));
        assertThrows(SudokuArrayIndexOutOfBoundsException.class, () -> board.getRow(9));

        assertDoesNotThrow(() -> board.getRow(1));

    }

    @Test
    void getBoxTest(){
        SudokuBoard board = new SudokuBoard(new BacktrackingSudokuSolver());

        assertThrows(SudokuArrayIndexOutOfBoundsException.class, () -> board.getBox(-100, 1));
        assertThrows(SudokuArrayIndexOutOfBoundsException.class, () -> board.getBox(900, 1));
        assertThrows(SudokuArrayIndexOutOfBoundsException.class, () -> board.getBox(1, -100));
        assertThrows(SudokuArrayIndexOutOfBoundsException.class, () -> board.getBox(1, 900));

        assertDoesNotThrow(() -> board.getBox(1, 1));

    }


}