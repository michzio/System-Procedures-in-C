//
// Created by Michal Ziobro on 29.05.2017.
//
#include <stdio.h>
#include <windows.h>
#include "windows.h"

char *front_window_owner(void) {

    char wnd_title[256];
    char *token = malloc(256*sizeof(char));

    // get handle to currently active window
    HWND hwnd = GetForegroundWindow();
    GetWindowText(hwnd, wnd_title, sizeof(wnd_title));
    char *next_token = strtok(wnd_title, "-");

    do {
        strcpy(token, next_token);
        //printf("%s\n", token);
    } while((next_token = strtok(NULL, "-")) != NULL);

    printf("%s\n", token);

    // trim leading spaces
    while(isspace((unsigned char ) *token)) token++;

    // if all white spaces return empty string
    if(*token == 0) return token;

    // discard trailing white spaces
    char *t = token + strlen(token) -1;
    while(isspace((unsigned char ) *t)) t--;

    // terminate just after first word
    *(t+1) = '\0';

    return token;
}