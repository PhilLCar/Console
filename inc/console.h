#ifndef INC_CONSOLE
#define INC_CONSOLE

#define ESCAPE 0x001b

#include <iostream>
#include <vector>

class Console {
public:
    enum BoxDrawing {
        LINE = 0,
        LINE_DOUBLE,
        LINE_BOLD,
        LINE_NONE,
        LINE_HORIZONTAL = 0x2500,
        LINE_HORIZONTAL_BOLD,
        LINE_VERTICAL,
        LINE_VERTICAL_BOLD,
        LINE_HORIZONTAL_DOT3,
        LINE_HORIZONTAL_DOT3_BOLD,
        LINE_VERTICAL_DOT3,
        LINE_VERTICAL_DOT3_BOLD,
        LINE_HORIZONTAL_DOT4,
        LINE_HORIZONTAL_DOT4_BOLD,
        LINE_VERTICAL_DOT4,
        LINE_VERTICAL_DOT4_BOLD,
        CORNER_TOP_LEFT,
        CORNER_TOP_BOLD_LEFT,
        CORNER_TOP_LEFT_BOLD,
        CORNER_TOP_BOLD_LEFT_BOLD,
        CORNER_TOP_RIGHT,
        CORNER_TOP_BOLD_RIGHT,
        CORNER_TOP_RIGHT_BOLD,
        CORNER_TOP_BOLD_RIGHT_BOLD,
        CORNER_BOTTOM_LEFT,
        CORNER_BOTTOM_BOLD_LEFT,
        CORNER_BOTTOM_LEFT_BOLD,
        CORNER_BOTTOM_BOLD_LEFT_BOLD,
        CORNER_BOTTOM_RIGHT,
        CORNER_BOTTOM_BOLD_RIGHT,
        CORNER_BOTTOM_RIGHT_BOLD,
        CORNER_BOTTOM_BOLD_RIGHT_BOLD,
        TEE_TOP_BOTTOM_RIGHT,
        TEE_TOP_BOTTOM_RIGHT_BOLD,
        TEE_TOP_BOLD_BOTTOM_RIGHT,
        TEE_TOP_BOTTOM_BOLD_RIGHT,
        TEE_TOP_BOLD_BOTTOM_BOLD_RIGHT,
        TEE_TOP_BOLD_BOTTOM_RIGHT_BOLD,
        TEE_TOP_BOTTOM_BOLD_RIGHT_BOLD,
        TEE_TOP_BOLD_BOTTOM_BOLD_RIGHT_BOLD,
        TEE_TOP_BOTTOM_LEFT,
        TEE_TOP_BOTTOM_LEFT_BOLD,
        TEE_TOP_BOLD_BOTTOM_LEFT,
        TEE_TOP_BOTTOM_BOLD_LEFT,
        TEE_TOP_BOLD_BOTTOM_BOLD_LEFT,
        TEE_TOP_BOLD_BOTTOM_LEFT_BOLD,
        TEE_TOP_BOTTOM_BOLD_LEFT_BOLD,
        TEE_TOP_BOLD_BOTTOM_BOLD_LEFT_BOLD,
        TEE_BOTTOM_LEFT_RIGHT,
        TEE_BOTTOM_LEFT_BOLD_RIGHT,
        TEE_BOTTOM_LEFT_RIGHT_BOLD,
        TEE_BOTTOM_LEFT_BOLD_RIGHT_BOLD,
        TEE_BOTTOM_BOLD_LEFT_RIGHT,
        TEE_BOTTOM_BOLD_LEFT_BOLD_RIGHT,
        TEE_BOTTOM_BOLD_LEFT_RIGHT_BOLD,
        TEE_BOTTOM_BOLD_LEFT_BOLD_RIGHT_BOLD,
        TEE_TOP_LEFT_RIGHT,
        TEE_TOP_LEFT_BOLD_RIGHT,
        TEE_TOP_LEFT_RIGHT_BOLD,
        TEE_TOP_LEFT_BOLD_RIGHT_BOLD,
        TEE_TOP_BOLD_LEFT_RIGHT,
        TEE_TOP_BOLD_LEFT_BOLD_RIGHT,
        TEE_TOP_BOLD_LEFT_RIGHT_BOLD,
        TEE_TOP_BOLD_LEFT_BOLD_RIGHT_BOLD,
        CROSS,
        CROSS_LEFT_BOLD,
        CROSS_RIGHT_BOLD,
        CROSS_LEFT_BOLD_RIGHT_BOLD,
        CROSS_TOP_BOLD,
        CROSS_BOTTOM_BOLD,
        CROSS_TOP_BOLD_BOTTOM_BOLD,
        CROSS_TOP_BOLD_LEFT_BOLD,
        CROSS_TOP_BOLD_RIGHT_BOLD,
        CROSS_BOTTOM_BOLD_LEFT_BOLD,
        CROSS_BOTTOM_BOLD_RIGHT_BOLD,
        CROSS_TOP_BOLD_LEFT_BOLD_RIGHT_BOLD,
        CROSS_BOTTOM_BOLD_LEFT_BOLD_RIGHT_BOLD,
        CROSS_TOP_BOLD_BOTTOM_BOLD_LEFT_BOLD,
        CROSS_TOP_BOLD_BOTTOM_BOLD_RIGHT_BOLD,
        CROSS_BOLD,
        LINE_HORIZONTAL_DOT2,
        LINE_HORIZONTAL_DOT2_BOLD,
        LINE_VERTICAL_DOT2,
        LINE_VERTICAL_DOT2_BOLD,
        LINE_HORIZONTAL_DOUBLE,
        LINE_VERTICAL_DOUBLE,
        CORNER_TOP_DOUBLE_LEFT,
        CORNER_TOP_LEFT_DOUBLE,
        CORNER_TOP_DOUBLE_LEFT_DOUBLE,
        CORNER_TOP_DOUBLE_RIGHT,
        CORNER_TOP_RIGHT_DOUBLE,
        CORNER_TOP_DOUBLE_RIGHT_DOUBLE,
        CORNER_BOTTOM_DOUBLE_LEFT,
        CORNER_BOTTOM_LEFT_DOUBLE,
        CORNER_BOTTOM_DOUBLE_LEFT_DOUBLE,
        CORNER_BOTTOM_DOUBLE_RIGHT,
        CORNER_BOTTOM_RIGHT_DOUBLE,
        CORNER_BOTTOM_DOUBLE_RIGHT_DOUBLE,
        TEE_TOP_BOTTOM_RIGHT_DOUBLE,
        TEE_TOP_DOUBLE_BOTTOM_DOUBLE_RIGHT,
        TEE_TOP_DOUBLE_BOTTOM_DOUBLE_RIGHT_DOUBLE,
        TEE_TOP_BOTTOM_LEFT_DOUBLE,
        TEE_TOP_DOUBLE_BOTTOM_DOUBLE_LEFT,
        TEE_TOP_DOUBLE_BOTTOM_DOUBLE_LEFT_DOUBLE,
        TEE_BOTTOM_LEFT_DOUBLE_RIGHT_DOUBLE,
        TEE_BOTTOM_DOUBLE_LEFT_RIGHT,
        TEE_BOTTOM_DOUBLE_LEFT_DOUBLE_RIGHT_DOUBLE,
        TEE_TOP_LEFT_DOUBLE_RIGHT_DOUBLE,
        TEE_TOP_DOUBLE_LEFT_RIGHT,
        TEE_TOP_DOUBLE_LEFT_DOUBLE_RIGHT_DOUBLE,
        CROSS_LEFT_DOUBLE_RIGHT_DOUBLE,
        CROSS_TOP_DOUBLE_BOTTOM_DOUBLE,
        CROSS_DOUBLE,
        CORNER_ROUND_TOP_LEFT,
        CORNER_ROUND_TOP_RIGHT,
        CORNER_ROUND_BOTTOM_RIGHT,
        CORNER_ROUND_BOTTOM_LEFT,
        LINE_DIAGONAL_POSITIVE,
        LINE_DIAGONAL_NEGATIVE,
        CROSS_DIAGONAL,
        HALFLINE_LEFT,
        HALFLINE_TOP,
        HALFLINE_RIGHT,
        HALFLINE_BOTTOM,
        HALFLINE_LEFT_BOLD,
        HALFLINE_TOP_BOLD,
        HALFLINE_RIGHT_BOLD,
        HALFLINE_BOTTOM_BOLD,
        LINE_RIGHT_BOLD,
        LINE_BOTTOM_BOLD,
        LINE_LEFT_BOLD,
        LINE_TOP_BOLD
    };

    enum BlockElement {
        BOX_TOP_4_8 = 0x2580,
        BOX_BOTTOM_1_8,
        BOX_BOTTOM_2_8,
        BOX_BOTTOM_3_8,
        BOX_BOTTOM_4_8,
        BOX_BOTTOM_5_8,
        BOX_BOTTOM_6_8,
        BOX_BOTTOM_7_8,
        BOX,
        BOX_LEFT_7_8,
        BOX_LEFT_6_8,
        BOX_LEFT_5_8,
        BOX_LEFT_4_8,
        BOX_LEFT_3_8,
        BOX_LEFT_2_8,
        BOX_LEFT_1_8,
        BOX_RIGHT_4_8,
        BOX_LIGHT,
        BOX_MEDIUM,
        BOX_DARK,
        BOX_TOP_1_8,
        BOX_RIGHT_1_8,
        BOX_BOTTOM_LEFT,
        BOX_BOTTOM_RIGHT,
        BOX_TOP_LEFT,
        BOX_BUT_TOP_RIGHT,
        BOX_TOP_LEFT_AND_BOTTOM_RIGHT,
        BOX_BUT_BOTTOM_RIGHT,
        BOX_BUT_BOTTOM_LEFT,
        BOX_TOP_RIGHT,
        BOX_TOP_RIGHT_AND_BOTTOM_LEFT,
        BOX_BUT_TOP_LEFT,
    };

    enum Arrow {

    };

    enum GeometricShape {

    };

    enum Color {
        COLOR_RESET = 0,
        COLOR_BOLD,
        COLOR_UNDERLINE = 4,
        COLOR_REVERSED = 7,
        COLOR_BLACK = 30,
        COLOR_RED,
        COLOR_GREEN,
        COLOR_YELLOW,
        COLOR_BLUE,
        COLOR_MAGENTA,
        COLOR_CYAN,
        COLOR_WHITE,
        COLOR_BACKGROUND_BLACK = 40,
        COLOR_BACKGROUND_RED,
        COLOR_BACKGROUND_GREEN,
        COLOR_BACKGROUND_YELLOW,
        COLOR_BACKGROUND_BLUE,
        COLOR_BACKGROUND_MAGENTA,
        COLOR_BACKGROUND_CYAN,
        COLOR_BACKGROUND_WHITE
    };

    enum CursorMovement {
        UP = 'A',
        DOWN,
        FORWARD,
        BACKWARD
    };

public:
    static void color(Color, bool = false);
    static void clear();
    static void drawBox(int, int, int, int, std::vector<Color>, BoxDrawing = LINE);
    static void drawTitleBox(int, int, int, int, std::string, std::vector<Color>, BoxDrawing = LINE);
    static void drawTextBox(int, int, int, int, std::string, std::vector<Color>, BoxDrawing = LINE);
    static void drawTitleTextBox(int, int, int, int, std::string, std::string, std::vector<Color>, BoxDrawing = LINE);
    static void drawSymbol(int, int, GeometricShape, std::vector<Color>);
    static void drawLabel(int, int, std::string, std::vector<Color>);

private:
    static int utf8_to_unicode(std::string);
    static std::string unicode_to_utf8(int);
    static void move(int, int);
    static void move(int, CursorMovement);
    static void save();
    static void restore();
};

#endif