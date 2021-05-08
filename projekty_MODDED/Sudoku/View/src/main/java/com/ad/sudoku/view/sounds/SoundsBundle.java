package com.ad.sudoku.view.sounds;

import java.util.ListResourceBundle;

public class SoundsBundle extends ListResourceBundle {

    private final Object[][] resources = {
            {"author1", "Adam Kapuściński"},
            {"author2", "Damian Szczeciński"},
            {"sound", "/com/ad/sudoku/view/sounds/english.wav"}
    };

    @Override
    protected Object[][] getContents() {
        return resources;
    }
}
