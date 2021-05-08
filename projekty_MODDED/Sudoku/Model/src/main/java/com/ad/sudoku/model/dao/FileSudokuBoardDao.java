package com.ad.sudoku.model.dao;

import com.ad.sudoku.model.SudokuBoard;
import com.ad.sudoku.model.exceptions.SudokuClassNotFoundException;
import com.ad.sudoku.model.exceptions.SudokuIOexception;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.util.logging.Level;
import java.util.logging.Logger;

public class FileSudokuBoardDao implements Dao<SudokuBoard> {

    private static final Logger logger = Logger.getLogger(FileSudokuBoardDao.class.getName(),
            "com.ad.sudoku.model.lang.sudokuLoggerLocale");

    String fileName;

    public FileSudokuBoardDao(String fileName) {
        this.fileName = fileName;
    }

    @Override
    public SudokuBoard read() {
        try (FileInputStream fis = new FileInputStream(fileName);
             ObjectInputStream ois = new ObjectInputStream(fis)) {

            return (SudokuBoard) ois.readObject();

        } catch (IOException e) {
            SudokuIOexception wrapper =
                    new SudokuIOexception("SudokuIOException.FileDao", e);
            logger.log(Level.SEVERE, "FileSudokuBoardDao.read.IOException", e);

            throw wrapper;
        } catch (ClassNotFoundException e) {
            SudokuClassNotFoundException wrapper =
                    new SudokuClassNotFoundException("SudokuClassNotFoundException.FileDao", e);
            logger.log(Level.SEVERE, "FileSudokuBoardDao.read.ClassNotFoundException");
            throw wrapper;
        }
    }

    @Override
    public void write(SudokuBoard obj) {
        try (FileOutputStream fos = new FileOutputStream(fileName);
             ObjectOutputStream oos = new ObjectOutputStream(fos)) {

            oos.writeObject(obj);

        } catch (IOException e) {
            SudokuIOexception wrapper =
                    new SudokuIOexception("SudokuIOException.FileDao", e);
            logger.log(Level.SEVERE, "FileSudokuBoardDao.write.IOException", e);
            throw wrapper;
        }
    }

    //    @Override
    //    protected void finalize() throws Throwable {
    //        super.finalize();
    //    }
}
