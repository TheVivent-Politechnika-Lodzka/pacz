import com.ad.sudoku.model.solvers.BacktrackingSudokuSolver;
import com.ad.sudoku.model.Difficulty;
import com.ad.sudoku.model.SudokuBoard;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

public class DifficultyTest {

    @Test
    public void toStringTest() {
        assertTrue(Difficulty.EASY.toString().length() > 0);
        assertNotEquals(Difficulty.EASY.toString(), Difficulty.EASY.name());
    }

    @Test
    public void startGameTest() {
        SudokuBoard board = new SudokuBoard(new BacktrackingSudokuSolver());

        Difficulty.EASY.startGame(board);
        int zeros = 0;
        for (int i = 0; i < SudokuBoard.SIZE; i++) {
            for (int j = 0; j < SudokuBoard.SIZE; j++) {
                if (board.get(i, j) == 0) {
                    zeros++;
                }
            }
        }
        assertEquals(Difficulty.EASY.getEmptyFields(), zeros);
    }

}
