package com.ad.sudoku.view;

public enum TextFieldBackgroundColor {

    DEFAULT_WHITE("-fx-control-inner-background: white;"),
    DEFAULT_GREY("-fx-control-inner-background: lightgrey;"),
    ZERO("-fx-control-inner-background: yellow;"),
    CORRECT("-fx-control-inner-background: green;"),
    WRONG("-fx-control-inner-background: red;");


    private final String text;

    TextFieldBackgroundColor(String text) {
        this.text = text;
    }

    @Override
    public String toString() {
        return this.text;
    }
}
