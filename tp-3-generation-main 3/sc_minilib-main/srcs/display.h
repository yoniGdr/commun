#pragma once 

void init_display(int x, int y, int w, int h);
void end_display();
void print_frame();
void set_bold(bool x);
void print_char_at(int x, int y, char c);
void print_line(int y, const char *s);
void show_display();
void print_at(int x, int y, const char *s);
int get_input();
int getStr(char *str);
int myecho();
int mynoecho();
void mymove(int x, int y);
void print_line_int(int y, const char *s, int value);
void print_entier(int x, int y, const char *s, int value);