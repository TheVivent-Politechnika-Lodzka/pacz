package com.ad.sudoku.view.sounds;

import java.util.ListResourceBundle;

public class SoundsBundle_pl extends ListResourceBundle {

    private final Object[][] resources = {
            {"author1", "Adam Kapuściński PL"},
            {"author2", "Damian Szczeciński"},
            {"sound", "com/ad/sudoku/view/sounds/polski.wav"}
    };

    @Override
    protected Object[][] getContents() {
        return resources;
    }
}
