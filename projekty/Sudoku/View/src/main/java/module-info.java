module ViewProject {
    requires javafx.controls;
    requires javafx.graphics;
    requires javafx.fxml;
    requires ModelProject;
    requires java.desktop;
    requires java.logging;

    opens com.ad.sudoku.view;
}