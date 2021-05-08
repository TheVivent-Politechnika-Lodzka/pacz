package com.ad.sudoku.view.sounds;

import java.util.ListResourceBundle;

public class SoundsBundle_ja extends ListResourceBundle {

    private final Object[][] resources = {
            {"author1", "Adam Kapuściński JA"},
            {"author2", "Damian Szczeciński"},
            {"sound", "/com/ad/sudoku/view/sounds/nihon.wav"}
    };

    @Override
    protected Object[][] getContents() {
        return resources;
    }
}
