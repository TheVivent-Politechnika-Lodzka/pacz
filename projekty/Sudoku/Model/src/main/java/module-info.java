module ModelProject {
    requires com.google.common;
    requires java.desktop;
    requires java.logging;
    requires java.sql;
    requires java.persistence;
    requires net.bytebuddy;
    requires com.fasterxml.classmate;
    requires java.xml.bind;

    opens com.ad.sudoku.model;

    exports com.ad.sudoku.model;
    exports com.ad.sudoku.model.dao;
    exports com.ad.sudoku.model.actionevents;
    exports com.ad.sudoku.model.solvers;
    exports com.ad.sudoku.model.exceptions;
}