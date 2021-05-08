package com.ad.sudoku.model;

import com.ad.sudoku.model.dao.JpaSudokuBoardDao;
import com.ad.sudoku.model.dao.SudokuBoardDaoFactory;
import com.ad.sudoku.model.solvers.BacktrackingSudokuSolver;
import java.io.FileInputStream;
import java.io.IOException;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.LogManager;
import java.util.logging.Logger;

public class Main {

    private static final Logger logger = Logger.getLogger(Main.class.getName(),
            "com.ad.sudoku.model.lang.sudokuLoggerLocale");

    public static void main(String[] args) throws InterruptedException {

        try {
            FileInputStream configFile = new FileInputStream("logging.properties");
            LogManager.getLogManager().readConfiguration(configFile);
        } catch (IOException ex) {
            logger.log(Level.WARNING, "Could not open configuration file");
            logger.log(Level.WARNING, "Logging not configured (console output only)");
        }

    }
}
