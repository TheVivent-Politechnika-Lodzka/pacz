package com.ad.sudoku.view;

import com.ad.sudoku.model.Difficulty;
import com.ad.sudoku.model.SudokuBoard;
import com.ad.sudoku.model.SudokuField;
import com.ad.sudoku.model.actionevents.SudokuActionEvent;
import com.ad.sudoku.model.dao.SudokuBoardDaoFactory;
import com.ad.sudoku.model.exceptions.SudokuSQlException;
import com.ad.sudoku.model.solvers.BacktrackingSudokuSolver;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.IOException;
import java.net.URL;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Locale;
import java.util.Optional;
import java.util.ResourceBundle;
import javafx.beans.property.StringProperty;
import javafx.beans.property.adapter.JavaBeanIntegerProperty;
import javafx.beans.property.adapter.JavaBeanIntegerPropertyBuilder;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.CheckBox;
import javafx.scene.control.ChoiceBox;
import javafx.scene.control.ChoiceDialog;
import javafx.scene.control.SplitPane;
import javafx.scene.control.TextField;
import javafx.scene.control.TextInputDialog;
import javafx.scene.layout.GridPane;
import javafx.scene.text.Font;
import javafx.scene.text.FontWeight;
import javafx.stage.FileChooser;
import javafx.util.StringConverter;
import javafx.util.converter.IntegerStringConverter;



public class Window implements Initializable, ActionListener {

    @FXML
    private SplitPane root;
    @FXML
    private ChoiceBox<String> languageBox;
    @FXML
    private GridPane sudokuPane;
    @FXML
    private Button acceptBtn;
    @FXML
    private ChoiceBox<Difficulty> difficulty;
    @FXML
    private CheckBox tips;

    private final SudokuBoard board = new SudokuBoard(new BacktrackingSudokuSolver());
    private final SudokuBoard originalBoard = board.clone();
    private final List<List<TextField>> fields = Arrays.asList(new List[9]);
    private final List<JavaBeanIntegerProperty> integerProperties = new ArrayList<>();
    private final String sudokuFileExtension = "*.sudoku";
    private ResourceBundle bundle;

    public Window() {

        board.addActionListener(this);

        for (int i = 0; i < SudokuBoard.SIZE; i++) {
            fields.set(i, Arrays.asList(new TextField[9]));
            for (int j = 0; j < SudokuBoard.SIZE; j++) {
                TextField textField = new TextField();
                fields.get(i).set(j, textField);
                textField.setPrefColumnCount(1);
                textField.setFont(Font.font("Arial", FontWeight.MEDIUM, 20));
                textField.setMinSize(46, 44);
                textField.textProperty().addListener(
                        (observable, oldValue, newValue) -> {
                            if (!newValue.matches("[1-9]]?")) {
                                ((StringProperty) observable).set("");
                            }
                        });

                textField.setEditable(true);
                textField.setMouseTransparent(false);
                textField.setFocusTraversable(true);
                textField.setStyle(TextFieldBackgroundColor.DEFAULT_WHITE.toString());
                textField.setAlignment(Pos.CENTER);

            }
        }
        setBoxesColors();
    }

    @Override
    public void initialize(URL url, ResourceBundle resourceBundle) {

        bundle = resourceBundle;
        difficulty.getSelectionModel().select(0);

        StringConverter converter = new IntegerStringConverter();

        for (int i = 0; i < SudokuBoard.SIZE; i++) {
            for (int j = 0; j < SudokuBoard.SIZE; j++) {
                //I generate Sudoku board and TextFields in Constructor
                TextField textField = getTextField(i, j);
                SudokuField field = board.getField(i, j);

                JavaBeanIntegerPropertyBuilder builder = JavaBeanIntegerPropertyBuilder.create();
                JavaBeanIntegerProperty integerProperty = null;
                try {
                    integerProperty = builder.bean(field).name("value").build();
                } catch (NoSuchMethodException e) {
                    System.out.println("Ignoring NoSuchMethodException in " + this.getClass());
                }

                //i need to store JavaBeanIntegerProperty, otherwise GarbageCollector
                //destroys my connections
                integerProperties.add(integerProperty);

                //adding textField to GridPane
                sudokuPane.add(textField, i, j);
                textField.textProperty().bindBidirectional(integerProperty, converter);
            }
        }
    }

    private TextField getTextField(int x, int y) {
        return fields.get(x).get(y);
    }

    private void toggleDifficultyVisibility(boolean x) {
        acceptBtn.setDisable(!x);
        difficulty.setDisable(!x);
    }

    private void setBoxesColors() {
        for (int i = 0; i < SudokuBoard.SIZE; i++) {
            for (int j = 0; j < SudokuBoard.SIZE; j++) {
                getTextField(i, j).setStyle(TextFieldBackgroundColor.DEFAULT_WHITE.toString());
                if (
                        (i > 2 && i < 6 && (j < 3 || j > 5))
                                || ((i < 3 || i > 5) && (j > 2 && j < 6))
                ) {
                    getTextField(i, j).setStyle(TextFieldBackgroundColor.DEFAULT_GREY.toString());
                }
            }
        }
    }

    private void disableNonZeroTextFields() {
        setBoxesColors();
        for (int i = 0; i < SudokuBoard.SIZE; i++) {
            for (int j = 0; j < SudokuBoard.SIZE; j++) {
                boolean x = board.get(i, j) == 0;
                TextField textField = getTextField(i, j);
                textField.setEditable(x);
                textField.setMouseTransparent(!x);
                textField.setFocusTraversable(x);
                if (x) {
                    textField.setStyle(TextFieldBackgroundColor.ZERO.toString());
                }
            }
        }
    }

    public void acceptDifficutly(ActionEvent actionEvent) {
        // jeśli nie wybrano poziomu trudności to nic nie rób
        if (difficulty.getValue() == null) {
            return;
        }

        // wyłącz część interfejsu odpowiedzialną
        // za wybieranie poziomu trudności
        toggleDifficultyVisibility(false);

        // wyczyść planszę
        originalBoard.clearBoard();
        // wypełnij planszę
        difficulty.getValue().startGame(originalBoard);

        // przepisz oryginalną planszę na planszę do gry
        for (int i = 0; i < SudokuBoard.SIZE; i++) {
            for (int j = 0; j < SudokuBoard.SIZE; j++) {
                board.set(i, j, originalBoard.get(i, j));
            }
        }

        // tak jak nazwa funkcji mówi
        disableNonZeroTextFields();
    }

    public void solve(ActionEvent actionEvent) {
        board.solveGame();
    }

    public void tipsSwitched(ActionEvent actionEvent) {
        board.setAutoCheck(tips.isSelected());
    }

    public void giveUp(ActionEvent actionEvent) {
        board.clearBoard();
        disableNonZeroTextFields();
        toggleDifficultyVisibility(true);
    }

    @Override
    public void actionPerformed(java.awt.event.ActionEvent e) {
        if (e.getClass() != SudokuActionEvent.class) {
            return;
        }
        SudokuActionEvent event = (SudokuActionEvent) e;

        int i = event.getRow();
        int j = event.getCol();

        TextFieldBackgroundColor bg = (event.isInsertedValueCorrect()
                ? TextFieldBackgroundColor.CORRECT :
                TextFieldBackgroundColor.WRONG);
        getTextField(i, j).setStyle(bg.toString());

    }

    public void checkGame(ActionEvent actionEvent) {

        boolean zera = false;
        outerloop:
        for (int i = 0; i < SudokuBoard.SIZE; i++) {
            for (int j = 0; j < SudokuBoard.SIZE; j++) {
                if (board.get(i, j) == 0) {
                    zera = true;
                    break outerloop;
                }
            }
        }

        Alert alert = new Alert(Alert.AlertType.INFORMATION);
        alert.setTitle(bundle.getString("code.checkGame.title"));
        alert.setHeaderText(null);
        boolean rozwiazable = board.checkBoard();

        // Solvable: "{0}" \n filled: {1}

        alert.setContentText(bundle.getString("code.checkGame.content")
                .replace("{0}", rozwiazable ? bundle.getString("yes") : bundle.getString("no"))
                .replace("{1}", zera ? bundle.getString("no") : bundle.getString("yes")));

        alert.showAndWait();

    }

    public void setLang(ActionEvent actionEvent) {

        switch (languageBox.getValue()) {
            case "polski":
                Locale.setDefault(new Locale("pl"));
                break;
            case "日本人":
                Locale.setDefault(new Locale("ja"));
                break;
            case "english":
            default:
                Locale.setDefault(new Locale("en"));
                break;
        }

        ResourceBundle soundBundle = ResourceBundle.getBundle(
                "com.ad.sudoku.view.sounds.SoundsBundle");

        System.out.println(soundBundle.getString("author1"));
        System.out.println(soundBundle.getString("author2"));
        System.out.println(soundBundle.getString("sound"));

        //try {
        //    Clip clip = AudioSystem.getClip();
        //    AudioInputStream inputStream = AudioSystem.getAudioInputStream(
        //            getClass().getResourceAsStream("/com/ad/sudoku/view/sounds/polski.wav"));
        //    clip.open(inputStream);
        //    clip.start();
        //} catch (Exception e) {
        //    e.printStackTrace();
        //}

        ResourceBundle bundle = ResourceBundle.getBundle("com.ad.sudoku.view.lang.sudokuLocale");
        // to jest element główny całego fxml dzięki temu dostajemy główną scenę
        Scene rootScene = root.getScene();

        try {
            rootScene.setRoot(FXMLLoader.load(getClass().getResource("/Window.fxml"), bundle));
        } catch (IOException e) {
            e.printStackTrace();
        }

    }

    public void saveGameToFile(ActionEvent actionEvent) {
        // utwórz ten taki do zapisywania plików systemowy
        FileChooser fileChooser = new FileChooser();
        FileChooser.ExtensionFilter extFilter = new FileChooser.ExtensionFilter(
                "SudokuGame" + "(" + sudokuFileExtension + ")", sudokuFileExtension);
        fileChooser.getExtensionFilters().add(extFilter);

        // pobierz ścieżkę wybranego pliku
        File file = fileChooser.showSaveDialog(sudokuPane.getScene().getWindow());
        String filePath = file.getAbsolutePath();

        if (filePath.length() == 0) {
            return;
        }

        // klasa do obługi plików
        var fileDao = SudokuBoardDaoFactory.getSudokuBoardListFileDao(filePath);
        // pliki trzeba zapisać do listy i tą listę dopiero do pliku
        List<SudokuBoard> boards = List.of(board, originalBoard);
        fileDao.write(boards);
    }

    public void loadGameFromFile(ActionEvent actionEvent) {
        // utwórz ten taki do wczytywania plików systemowy
        FileChooser fileChooser = new FileChooser();
        FileChooser.ExtensionFilter extFilter = new FileChooser.ExtensionFilter(
                "SudokuGame" + "(" + sudokuFileExtension + ")", sudokuFileExtension);
        fileChooser.getExtensionFilters().add(extFilter);

        // pobierz ścieżkę wybranego pliku
        File file = fileChooser.showOpenDialog(sudokuPane.getScene().getWindow());
        String filePath = file.getAbsolutePath();

        if (filePath.length() == 0) {
            return;
        }

        // pobierz pliki do listy, a potem do odpowiednich zmiennyh (dla czytelności)
        var fileDao = SudokuBoardDaoFactory.getSudokuBoardListFileDao(filePath);
        List<SudokuBoard> tmpBoards = fileDao.read();
        SudokuBoard tmpBoard = tmpBoards.get(0);
        SudokuBoard tmpOriginalBoard = tmpBoards.get(1);

        // wczytaj orignalną planszę i ustaw blokady na odpowiednich polach
        for (int i = 0; i < SudokuBoard.SIZE; i++) {
            for (int j = 0; j < SudokuBoard.SIZE; j++) {
                originalBoard.set(i, j, tmpOriginalBoard.get(i, j));
                board.set(i, j, tmpOriginalBoard.get(i, j));
            }
        }
        disableNonZeroTextFields();

        // wczytaj planszę wypełnioną przez użytkownika
        for (int i = 0; i < SudokuBoard.SIZE; i++) {
            for (int j = 0; j < SudokuBoard.SIZE; j++) {
                board.set(i, j, tmpBoard.get(i, j));
            }
        }
    }

    public void saveGameToDatabase(ActionEvent actionEvent) {
        TextInputDialog dialog = new TextInputDialog();
        dialog.setTitle(bundle.getString("code.saveGameToDatabase.dialog.title"));
        dialog.setHeaderText(bundle.getString("code.saveGameToDatabase.dialog.header"));
        //dialog.setContentText(bundle.getString("code.saveGameToDatabase.dialog.content"));

        Optional<String> result = dialog.showAndWait();
        if (result.isEmpty()) {
            return;
        }

        //var databaseDao = SudokuBoardDaoFactory.getSudokuBoardJdbcDao(result.get());

        List<SudokuBoard> boards = List.of(board, originalBoard);
        try (var databaseDao = SudokuBoardDaoFactory.getSudokuBoardJdbcDao(result.get())) {
            databaseDao.write(boards);
        } catch (SudokuSQlException e) {
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setTitle(bundle.getString("code.saveGameToDatabase.alert.title"));
            alert.setHeaderText(bundle.getString("code.saveGameToDatabase.alert.content"));
            //alert.setContentText(bundle.getString("code.saveGameToDatabase.alert.content"));
            alert.showAndWait();
        }

    }

    public void loadGameFromDatabase(ActionEvent actionEvent) {

        List<String> saves = new ArrayList<>();
        for (SudokuBoard b : SudokuBoardDaoFactory.getSudokuBoardJdbcDao("").readAll()) {
            saves.add(b.getName());
        }

        ChoiceDialog<String> dialog = new ChoiceDialog<>("", saves);
        dialog.setTitle(bundle.getString("code.loadGameFromDatabase.dialog.title"));
        dialog.setHeaderText(bundle.getString("code.loadGameFromDatabase.dialog.header"));
        //dialog.setContentText("Choose your letter:");

        Optional<String> result = dialog.showAndWait();
        if (result.isEmpty()) {
            return;
        }

        List<SudokuBoard> tmpBoards;
        try (var fileDao = SudokuBoardDaoFactory.getSudokuBoardJdbcDao(result.get())) {
            tmpBoards = fileDao.read();
        }
        SudokuBoard tmpBoard = tmpBoards.get(0);
        SudokuBoard tmpOriginalBoard = tmpBoards.get(1);

        // wczytaj orignalną planszę i ustaw blokady na odpowiednich polach
        for (int i = 0; i < SudokuBoard.SIZE; i++) {
            for (int j = 0; j < SudokuBoard.SIZE; j++) {
                originalBoard.set(i, j, tmpOriginalBoard.get(i, j));
                board.set(i, j, tmpOriginalBoard.get(i, j));
            }
        }
        disableNonZeroTextFields();

        // wczytaj planszę wypełnioną przez użytkownika
        for (int i = 0; i < SudokuBoard.SIZE; i++) {
            for (int j = 0; j < SudokuBoard.SIZE; j++) {
                board.set(i, j, tmpBoard.get(i, j));
            }
        }
    }
}
