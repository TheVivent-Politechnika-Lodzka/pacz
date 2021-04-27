import com.ad.sudoku.model.exceptions.SudokuException;
import com.ad.sudoku.model.exceptions.SudokuNullPointerException;
import com.ad.sudoku.model.solvers.BacktrackingSudokuSolver;
import com.ad.sudoku.model.SudokuBoard;
import com.ad.sudoku.model.SudokuField;
import org.junit.jupiter.api.Test;
import org.junit.platform.commons.logging.LoggerFactory;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.logging.LogRecord;
import java.util.logging.Logger;

import static org.junit.jupiter.api.Assertions.*;

public class SudokuFieldTest {

    @Test
    void setValueTest(){

        SudokuField field = new SudokuField();

        //negative
        assertThrows(SudokuException.class, () -> field.setValue(10));
        assertThrows(SudokuException.class, () -> field.setValue(-1));

        //positive
        assertDoesNotThrow(()->field.setValue(0));
        assertDoesNotThrow(()->field.setValue(1));
        assertDoesNotThrow(()->field.setValue(9));

        assertEquals(field.getValue(), 9);
    }

    @Test
    void toStringTest() throws SudokuException {
        SudokuField field = new SudokuField();
        field.setValue(1);

        assertTrue(field.toString().length()>0);
    }

    @Test
    void equalsTest() throws SudokuException {
        SudokuField field1 = new SudokuField();
        SudokuField field2 = field1;
        SudokuField field3 = new SudokuField();

        //sprawdzenie czy w jakikolwiek sposób metody działają jak powinny
        assertEquals(field2, field1);
        assertEquals(field2.hashCode(), field1.hashCode());

        SudokuBoard board = new SudokuBoard(new BacktrackingSudokuSolver());
        field1.setValue(1);
        field2.setValue(1);
        field3.setValue(1);
        field1.addPropertyChangeListener(board);
        field2.addPropertyChangeListener(board);
        field3.addPropertyChangeListener(board);

        //test zwrotności
        assertEquals(field1, field1);

        //test symetryczności
        assertEquals(field2, field1);
        assertEquals(field1, field2);

        //test przechodniości
        assertEquals(field2, field1);
        assertEquals(field3, field2);
        assertEquals(field1, field3);

        //test na null (negative)
        assertNotEquals(field1, null);

        //test porównania z obiektem innej klasy (negative)
        String test = "lol";
        assertNotEquals(field1, test);

        //test negatywny
        field3.setValue(2);
        assertNotEquals(field3, field1);
    }

    @Test
    void hashCodeTest(){
        SudokuField field1 = new SudokuField();
        SudokuField field2 = field1;
        SudokuField field3 = new SudokuField();
        field3.setValue(2);

        //test hashCode(sprawdza tylko value w Field)
        assertEquals(field2.hashCode(), field1.hashCode());
        assertNotEquals(field3.hashCode(), field1.hashCode());

    }

    @Test
    public void cloneTest() throws CloneNotSupportedException, SudokuException {
        SudokuField field = new SudokuField();
        field.setValue(3);
        SudokuField clonedField = field.clone();

        assertEquals(clonedField, field);

        field.setValue(5);
        assertNotEquals(clonedField, field);

    }

    @Test
    void naturalOrderTest() throws SudokuException {
        // wygeneruj listę z SudokuFieldami 0-9
        List<SudokuField> field = new ArrayList<>();
        for(int i=0 ;i<10;i++){
            field.add(new SudokuField());
            field.get(i).setValue(i);
        }

        // przetasuj ją i upewnij się, że się przetasowała
        Collections.shuffle(field);
        int test;
        for(test=0;test<10;test++) {
            if (field.get(test).getValue() != test) break;
        }
        assertNotEquals(test, 9);

        // posortuj ją i sprawdź czy jest dobrze posortowana
        Collections.sort(field);
        for(int i=0 ;i<10;i++){
            assertEquals(field.get(i).getValue(), i);
        }
    }

    @Test
    void isCompareToThrowingOnNULL(){
        SudokuField field = new SudokuField();
        assertThrows(SudokuNullPointerException.class, () -> field.compareTo(null));
    }


}
