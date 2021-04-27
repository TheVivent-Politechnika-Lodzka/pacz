import com.ad.sudoku.model.solvers.BacktrackingSudokuSolver;
import com.ad.sudoku.model.SudokuBoard;
import org.junit.jupiter.api.Test;
import java.util.Arrays;
import java.util.Random;
import static org.junit.jupiter.api.Assertions.*;

class BacktrackingSudokuSolverTest {

    @Test
    void areBoardsDifferent() {
        //sprawdz czy tablice są różne

        SudokuBoard board1 = new SudokuBoard(new BacktrackingSudokuSolver());
        SudokuBoard board2 = new SudokuBoard(new BacktrackingSudokuSolver());

        board1.solveGame();
        board2.solveGame();

        for (int i = 0; i < 9; i++) {
            assertFalse(Arrays.equals(board1.getBoard()[0], board2.getBoard()[0]));
        }
    }

    @Test
    void areBoardsCorrectlyFilled() {
        //sprawdź czy tablica jest poprawnie wypełniona

        SudokuBoard board = new SudokuBoard(new BacktrackingSudokuSolver());
        board.solveGame();
        int[][] array = board.getBoard();

        for (int row = 0; row < SudokuBoard.SIZE; row++) {
            for (int col = 0; col < SudokuBoard.SIZE; col++) {
                assertNotEquals(array[row][col], 0);
                int number = array[row][col];

                int numberInRow = 0;
                int numberInCol = 0;

                for (int i = 0; i < SudokuBoard.SIZE; i++) {
                    if (array[row][i] == number) {
                        numberInRow++;
                    }
                    if (array[i][col] == number) {
                        numberInCol++;
                    }
                }

                assertEquals(1, numberInRow);
//                assertEquals(1, numberInCol);

                int x = row - row % 3;
                int y = col - col % 3;

                int numberInQuad = 0;

                for (int i = x; i < x + 3; i++) {
                    for (int j = y; j < y + 3; j++) {
                        if (array[i][j] == number) {
                            numberInQuad++;
                        }
                    }
                }
                assertEquals(1, numberInQuad);
            }
        }
    }

    @Test
    void CanFixBoard() {
        SudokuBoard board = new SudokuBoard(new BacktrackingSudokuSolver());
        board.solveGame();

        Random rand = new Random();

        int saveLast = board.get(8, 8);
        int saveLastInRow = board.get(5, 8);

        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (rand.nextBoolean()) {
                    board.set(i, j, 0);
                }
            }
        }

        board.set(8, 8, saveLast);
        board.set(5, 8, saveLastInRow);

        assertTrue(board.solveGame());
    }

    @Test
    void hashCodeAndEqualsTest() {
        BacktrackingSudokuSolver solver = new BacktrackingSudokuSolver();
        BacktrackingSudokuSolver solver2 = new BacktrackingSudokuSolver();
        assertFalse(solver.equals(null));
        String test = "x";
        assertFalse(solver.equals(test));
        assertTrue(solver.equals(solver));
        assertTrue(solver.equals(solver2));


        assertEquals(solver.hashCode(), solver2.hashCode());

    }


    @Test
    void isToStringReturningString() {
        BacktrackingSudokuSolver solver = new BacktrackingSudokuSolver();
        assertTrue(solver.toString().length() > 0);
    }
}