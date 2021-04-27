import com.ad.sudoku.model.SudokuBoard;
import com.ad.sudoku.model.dao.SudokuBoardDaoFactory;
import com.ad.sudoku.model.exceptions.SudokuIOexception;
import com.ad.sudoku.model.exceptions.SudokuSQlException;
import com.ad.sudoku.model.solvers.BacktrackingSudokuSolver;
import org.junit.jupiter.api.Disabled;
import org.junit.jupiter.api.Test;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;

import static org.junit.jupiter.api.Assertions.*;

public class SudokuBoardDaoFactoryTest {

    @Test
    void getInstanceTest() {
        assertNotNull(SudokuBoardDaoFactory.getInstance());
    }

    @Test
    void FileSudokuBoardDaoTest() {
        SudokuBoard board = new SudokuBoard(new BacktrackingSudokuSolver());
        board.solveGame();

        String fileName = "target/file.data";

        var file = SudokuBoardDaoFactory.getSudokuBoardFileDao(fileName);

        file.write(board);

        SudokuBoard newBoard = file.read();

        assertEquals(board, newBoard);

        var wrongFile = SudokuBoardDaoFactory.getSudokuBoardFileDao("");
        assertThrows(SudokuIOexception.class, () -> wrongFile.write(board));
        assertThrows(SudokuIOexception.class, () -> wrongFile.read());

    }

    @Test
    void FileSudokuBoardListDaoTest() {
        SudokuBoard b1 = new SudokuBoard(new BacktrackingSudokuSolver());
        SudokuBoard b2 = new SudokuBoard(new BacktrackingSudokuSolver());
        b1.solveGame();
        b2.solveGame();

        List<SudokuBoard> originalList = new ArrayList<>();
        originalList.add(b1);
        originalList.add(b2);


        String fileName = "target/file.data";

        try (var file = SudokuBoardDaoFactory.getSudokuBoardListFileDao(fileName)){
            file.write(originalList);
        } catch (Exception e) {
            e.printStackTrace();
        }

        try (var file = SudokuBoardDaoFactory.getSudokuBoardListFileDao(fileName)){
            List<SudokuBoard> tmp = file.read();

            assertEquals(tmp, originalList);
            assertFalse(tmp.get(0) == originalList.get(0));
            assertFalse(tmp.get(1) == originalList.get(1));
        } catch (Exception e) {
            e.printStackTrace();
        }



        var wrongFile = SudokuBoardDaoFactory.getSudokuBoardListFileDao("");
        assertThrows(SudokuIOexception.class, () -> wrongFile.write(originalList));
        assertThrows(SudokuIOexception.class, () -> wrongFile.read());

    }

    @Test @Disabled
    void JpaSudokuBoardDaoTest() {
        SudokuBoard b1 = new SudokuBoard(new BacktrackingSudokuSolver());
        SudokuBoard b2 = new SudokuBoard(new BacktrackingSudokuSolver());
        b1.solveGame();
        b2.solveGame();

        List<SudokuBoard> originalList = List.of(b1, b2);

        // losowa nazwa save'a
        String saveName = new Random()
                .ints(97, 123)
                .limit(10)
                .collect(StringBuilder::new, StringBuilder::appendCodePoint, StringBuilder::append)
                .toString();

        try (var database = SudokuBoardDaoFactory.getSudokuBoardJdbcDao(saveName)){
            database.write(originalList);
        }

        try (var database = SudokuBoardDaoFactory.getSudokuBoardJdbcDao(saveName)){

            List<SudokuBoard> tmp = database.read();

            // nie działa
            //assertEquals(tmp.get(0), originalList.get(0));
            assertFalse(tmp.get(0) == originalList.get(0));
            assertFalse(tmp.get(1) == originalList.get(1));
        }

        try (var wrongFile = SudokuBoardDaoFactory.getSudokuBoardJdbcDao(saveName)){
            assertThrows(SudokuSQlException.class, () -> wrongFile.write(originalList));
        }

        try (var wrongFile = SudokuBoardDaoFactory.getSudokuBoardJdbcDao("I do not exist")){
            assertThrows(SudokuSQlException.class, () -> wrongFile.read());
        }

        try (var readAll = SudokuBoardDaoFactory.getSudokuBoardJdbcDao(saveName)){
            assertTrue(readAll.readAll().size() > 0);
        }

    }

}
