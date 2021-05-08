package com.ad.sudoku.view;

import java.io.FileInputStream;
import java.io.IOException;
import java.util.ResourceBundle;
import java.util.logging.Level;
import java.util.logging.LogManager;
import java.util.logging.Logger;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;

public class Main extends Application {

    private static final Logger logger = Logger.getLogger(Main.class.getName(),
            "com.ad.sudoku.view.lang.sudokuLoggerLocale");

    @Override
    public void start(Stage primaryStage) throws Exception {

        ResourceBundle bundle = ResourceBundle.getBundle("com.ad.sudoku.view.lang.sudokuLocale");

        FXMLLoader primaryLoader = new FXMLLoader();
        primaryStage.setTitle("AD Sudoku");
        primaryStage.setScene(new Scene(
                primaryLoader.load(getClass().getResource("/Window.fxml"), bundle))
        );
        primaryStage.setResizable(false);

        primaryStage.show();
    }

    public static void main(String[] args) {

        try {
            FileInputStream configFile = new FileInputStream("logging.properties");
            LogManager.getLogManager().readConfiguration(configFile);
        } catch (IOException ex) {
            logger.log(Level.WARNING, "Could not open configuration file");
            logger.log(Level.WARNING, "Logging not configured (console output only)");
        }

        Application.launch(args);
    }

}
