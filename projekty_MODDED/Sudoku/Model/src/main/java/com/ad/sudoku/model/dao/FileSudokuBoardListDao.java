package com.ad.sudoku.model.dao;

import com.ad.sudoku.model.SudokuBoard;
import com.ad.sudoku.model.exceptions.SudokuClassNotFoundException;
import com.ad.sudoku.model.exceptions.SudokuIOexception;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;

public class FileSudokuBoardListDao implements Dao<List<SudokuBoard>> {

    private static final Logger logger = Logger.getLogger(FileSudokuBoardListDao.class.getName(),
            "com.ad.sudoku.model.lang.sudokuLoggerLocale");

    private String fileName;

    public FileSudokuBoardListDao(String fileName) {
        this.fileName = fileName;
    }

    @Override
    public List<SudokuBoard> read() {
        try (FileInputStream fis = new FileInputStream(fileName);
             ObjectInputStream ois = new ObjectInputStream(fis)) {

            return (List<SudokuBoard>) ois.readObject();

        } catch (IOException e) {
            SudokuIOexception wrapper =
                    new SudokuIOexception("SudokuIOException.FileDao", e);
            logger.log(Level.SEVERE, "FileSudokuBoardListDao.read.IOException", e);

            throw wrapper;
        } catch (ClassNotFoundException e) {
            SudokuClassNotFoundException wrapper =
                    new SudokuClassNotFoundException("SudokuClassNotFoundException.FileDao", e);
            logger.log(Level.SEVERE, "FileSudokuBoardListDao.read.ClassNotFoundException");
            throw wrapper;
        }
    }

    @Override
    public void write(List<SudokuBoard> obj) {
        try (FileOutputStream fos = new FileOutputStream(fileName);
             ObjectOutputStream oos = new ObjectOutputStream(fos)) {

            oos.writeObject(obj);

        } catch (IOException e) {
            SudokuIOexception wrapper =
                    new SudokuIOexception("SudokuIOException.FileDao", e);
            logger.log(Level.SEVERE, "FileSudokuBoardListDao.write.IOException", e);
            throw wrapper;
        }
    }

    @Override
    public void close() throws Exception {

    }
}
