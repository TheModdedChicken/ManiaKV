#pragma once

typedef enum MenuScreen {
    KEYBOARD, SETTINGS
} MenuScreen;

typedef enum HandState {
    IDLE, KEY1, KEY2, KEY1_2, KEY3, KEY4, KEY3_4
} HandState;

typedef int (*IntFunctionNP) ();