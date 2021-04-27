package com.ad.sudoku.model.dao;


import com.ad.sudoku.model.SudokuBoard;
import java.util.List;

public class SudokuBoardDaoFactory {

    private static SudokuBoardDaoFactory Singleton = null;

    private SudokuBoardDaoFactory() {
    }

    public static SudokuBoardDaoFactory getInstance() {
        if (Singleton == null) {
            Singleton = new SudokuBoardDaoFactory();
        }
        return Singleton;
    }

    public static FileSudokuBoardDao getSudokuBoardFileDao(String fileName) {
        return new FileSudokuBoardDao(fileName);
    }

    public static JpaSudokuBoardDao getSudokuBoardJdbcDao(String name) {
        return new JpaSudokuBoardDao(name);
    }

    public static Dao<List<SudokuBoard>> getSudokuBoardListFileDao(String fileName) {
        return new FileSudokuBoardListDao(fileName);
    }
}
