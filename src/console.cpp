#include <console.h>

void Console::color(Color color, bool bright)
{
    std::cout << unicode_to_utf8(ESCAPE);
    std::cout << "[" << color;
    if (bright) std::cout << ";1";
    std::cout << "m";
}

void Console::clear()
{
    std::cout << unicode_to_utf8(ESCAPE) << "[2J";
}

void Console::drawBox(int x, int y, int width, int height, std::vector<Color> colors, BoxDrawing line)
{
    if (width < 2 || height < 2) return;

    std::string tl, tr, bl, br, v, h;
    switch(line)
    {
        case LINE_DOUBLE:
            tl = unicode_to_utf8(CORNER_TOP_DOUBLE_LEFT_DOUBLE);
            tr = unicode_to_utf8(CORNER_TOP_DOUBLE_RIGHT_DOUBLE);
            bl = unicode_to_utf8(CORNER_BOTTOM_DOUBLE_LEFT_DOUBLE);
            br = unicode_to_utf8(CORNER_BOTTOM_DOUBLE_RIGHT_DOUBLE);
            v  = unicode_to_utf8(LINE_VERTICAL_DOUBLE);
            h  = unicode_to_utf8(LINE_HORIZONTAL_DOUBLE);
            break;
        case LINE_BOLD:
            tl = unicode_to_utf8(CORNER_TOP_BOLD_LEFT_BOLD);
            tr = unicode_to_utf8(CORNER_TOP_BOLD_RIGHT_BOLD);
            bl = unicode_to_utf8(CORNER_BOTTOM_BOLD_LEFT_BOLD);
            br = unicode_to_utf8(CORNER_BOTTOM_BOLD_RIGHT_BOLD);
            v  = unicode_to_utf8(LINE_VERTICAL_BOLD);
            h  = unicode_to_utf8(LINE_HORIZONTAL_BOLD);
            break;
        case LINE_NONE:
            tl = tr = bl = br = v = h = " ";
            break;
        case LINE:
        default:
            tl = unicode_to_utf8(CORNER_TOP_LEFT);
            tr = unicode_to_utf8(CORNER_TOP_RIGHT);
            bl = unicode_to_utf8(CORNER_BOTTOM_LEFT);
            br = unicode_to_utf8(CORNER_BOTTOM_RIGHT);
            v  = unicode_to_utf8(LINE_VERTICAL);
            h  = unicode_to_utf8(LINE_HORIZONTAL);
            break;
    }

    save();

    // Top
    move(x, y);
    for (Color c : colors) color(c);
    std::cout << tl;
    for (int i = 0; i < width - 2; i++) std::cout << h;
    std::cout << tr;

    // Sides
    for (int j = 1; j < height - 1; j++) {
        move(x, y + j);
        std::cout << v;
        for (int i = 0; i < width - 2; i++) std::cout << " ";
        std::cout << v;
    }

    // Bottom
    move(x, y + height - 1);
    std::cout << bl;
    for (int i = 0; i < width - 2; i++) std::cout << h;
    std::cout << br;

    color(COLOR_RESET);
    restore();
}

void Console::drawTitleBox(int x, int y, int width, int height, std::string title, std::vector<Color> colors, BoxDrawing line)
{
    if (width < 5 || height < 5) return;

    std::string tl, tr, bl, br, lt, rt, v, h;
    switch(line)
    {
        case LINE_DOUBLE:
            tl = unicode_to_utf8(CORNER_TOP_DOUBLE_LEFT_DOUBLE);
            tr = unicode_to_utf8(CORNER_TOP_DOUBLE_RIGHT_DOUBLE);
            bl = unicode_to_utf8(CORNER_BOTTOM_DOUBLE_LEFT_DOUBLE);
            br = unicode_to_utf8(CORNER_BOTTOM_DOUBLE_RIGHT_DOUBLE);
            lt = unicode_to_utf8(TEE_TOP_DOUBLE_BOTTOM_DOUBLE_RIGHT);
            rt = unicode_to_utf8(TEE_TOP_DOUBLE_BOTTOM_DOUBLE_LEFT);
            v  = unicode_to_utf8(LINE_VERTICAL_DOUBLE);
            h  = unicode_to_utf8(LINE_HORIZONTAL_DOUBLE);
            break;
        case LINE_BOLD:
            tl = unicode_to_utf8(CORNER_TOP_BOLD_LEFT_BOLD);
            tr = unicode_to_utf8(CORNER_TOP_BOLD_RIGHT_BOLD);
            bl = unicode_to_utf8(CORNER_BOTTOM_BOLD_LEFT_BOLD);
            br = unicode_to_utf8(CORNER_BOTTOM_BOLD_RIGHT_BOLD);
            lt = unicode_to_utf8(TEE_TOP_BOLD_BOTTOM_BOLD_RIGHT);
            rt = unicode_to_utf8(TEE_TOP_BOLD_BOTTOM_BOLD_LEFT);
            v  = unicode_to_utf8(LINE_VERTICAL_BOLD);
            h  = unicode_to_utf8(LINE_HORIZONTAL_BOLD);
            break;
        case LINE_NONE:
            tl = tr = bl = br = v = h = " ";
            lt = unicode_to_utf8(HALFLINE_RIGHT);
            rt = unicode_to_utf8(HALFLINE_LEFT);
            break;
        case LINE:
        default:
            tl = unicode_to_utf8(CORNER_TOP_LEFT);
            tr = unicode_to_utf8(CORNER_TOP_RIGHT);
            bl = unicode_to_utf8(CORNER_BOTTOM_LEFT);
            br = unicode_to_utf8(CORNER_BOTTOM_RIGHT);
            lt = unicode_to_utf8(TEE_TOP_BOTTOM_RIGHT);
            rt = unicode_to_utf8(TEE_TOP_BOTTOM_LEFT);
            v  = unicode_to_utf8(LINE_VERTICAL);
            h  = unicode_to_utf8(LINE_HORIZONTAL);
            break;
    }
    save();

    // Top
    move(x, y);
    for (Color c : colors) color(c);
    std::cout << tl;
    for (int i = 0; i < width - 2; i++) std::cout << h;
    std::cout << tr;

    // Title
    move(x, y + 1);
    std::cout << v;
    color(COLOR_BOLD);
    if (title.length() <= width - 2) {
        std::cout << title;
        for (int i = 0; i < width - 2 - title.length(); i++) std::cout << " ";
    } else {
        for (int i = 0; i < width - 5; i++) std::cout << title[i];
        std::cout << "...";
    }
    color(COLOR_RESET);
    for (Color c : colors) color(c);
    std::cout << v;
    move(x, y + 2);
    std::cout << lt;
    for (int i = 0; i < width - 2; i++) std::cout << unicode_to_utf8(LINE_HORIZONTAL);
    std::cout << rt;

    // Sides
    for (int j = 3; j < height - 1; j++) {
        move(x, y + j);
        std::cout << v;
        for (int i = 0; i < width - 2; i++) std::cout << " ";
        std::cout << v;
    }

    // Bottom
    move(x, y + height - 1);
    std::cout << bl;
    for (int i = 0; i < width - 2; i++) std::cout << h;
    std::cout << br;

    color(COLOR_RESET);
    restore();
}

void Console::drawTextBox(int x, int y, int width, int height, std::string content, std::vector<Color> colors, BoxDrawing line)
{
    if (width < 2 || height < 2) return;

    std::string tl, tr, bl, br, v, h;
    switch(line)
    {
        case LINE_DOUBLE:
            tl = unicode_to_utf8(CORNER_TOP_DOUBLE_LEFT_DOUBLE);
            tr = unicode_to_utf8(CORNER_TOP_DOUBLE_RIGHT_DOUBLE);
            bl = unicode_to_utf8(CORNER_BOTTOM_DOUBLE_LEFT_DOUBLE);
            br = unicode_to_utf8(CORNER_BOTTOM_DOUBLE_RIGHT_DOUBLE);
            v  = unicode_to_utf8(LINE_VERTICAL_DOUBLE);
            h  = unicode_to_utf8(LINE_HORIZONTAL_DOUBLE);
            break;
        case LINE_BOLD:
            tl = unicode_to_utf8(CORNER_TOP_BOLD_LEFT_BOLD);
            tr = unicode_to_utf8(CORNER_TOP_BOLD_RIGHT_BOLD);
            bl = unicode_to_utf8(CORNER_BOTTOM_BOLD_LEFT_BOLD);
            br = unicode_to_utf8(CORNER_BOTTOM_BOLD_RIGHT_BOLD);
            v  = unicode_to_utf8(LINE_VERTICAL_BOLD);
            h  = unicode_to_utf8(LINE_HORIZONTAL_BOLD);
            break;
        case LINE_NONE:
            tl = tr = bl = br = v = h = " ";
            break;
        case LINE:
        default:
            tl = unicode_to_utf8(CORNER_TOP_LEFT);
            tr = unicode_to_utf8(CORNER_TOP_RIGHT);
            bl = unicode_to_utf8(CORNER_BOTTOM_LEFT);
            br = unicode_to_utf8(CORNER_BOTTOM_RIGHT);
            v  = unicode_to_utf8(LINE_VERTICAL);
            h  = unicode_to_utf8(LINE_HORIZONTAL);
            break;
    }

    save();

    // Top
    move(x, y);
    for (Color c : colors) color(c);
    std::cout << tl;
    for (int i = 0; i < width - 2; i++) std::cout << h;
    std::cout << tr;

    // Sides
    int index = 0;
    for (int j = 1; j < height - 1; j++) {
        move(x, y + j);
        std::cout << v;
        if (j < height - 2 || content.length() - index <= width - 2) {
            for (int i = 0; i < width - 3; i++) std::cout << (index < content.length() ? content[index++] : ' ');
            if (index == content.length() - 1 || content[index] == ' ') {
                std::cout << content[index++];
            } else if (content[index + 1] == ' ') {
                std::cout << content[index++];
                while (content[index] == ' ') index++;
            } else if (index < content.length()) {
                std::cout << '-';
            } else {
                std::cout << ' ';
            }
        } else {
            for (int i = 0; i < width - 5; i++) std::cout << content[index++];
            std::cout << "...";
        }
        std::cout << v;
    }

    // Bottom
    move(x, y + height - 1);
    std::cout << bl;
    for (int i = 0; i < width - 2; i++) std::cout << h;
    std::cout << br;

    color(COLOR_RESET);
    restore();
}

void Console::drawTitleTextBox(int x, int y, int width, int height, std::string title, std::string content, std::vector<Color> colors, BoxDrawing line)
{
    if (width < 5 || height < 5) return;

    std::string tl, tr, bl, br, lt, rt, v, h;
    switch(line)
    {
        case LINE_DOUBLE:
            tl = unicode_to_utf8(CORNER_TOP_DOUBLE_LEFT_DOUBLE);
            tr = unicode_to_utf8(CORNER_TOP_DOUBLE_RIGHT_DOUBLE);
            bl = unicode_to_utf8(CORNER_BOTTOM_DOUBLE_LEFT_DOUBLE);
            br = unicode_to_utf8(CORNER_BOTTOM_DOUBLE_RIGHT_DOUBLE);
            lt = unicode_to_utf8(TEE_TOP_DOUBLE_BOTTOM_DOUBLE_RIGHT);
            rt = unicode_to_utf8(TEE_TOP_DOUBLE_BOTTOM_DOUBLE_LEFT);
            v  = unicode_to_utf8(LINE_VERTICAL_DOUBLE);
            h  = unicode_to_utf8(LINE_HORIZONTAL_DOUBLE);
            break;
        case LINE_BOLD:
            tl = unicode_to_utf8(CORNER_TOP_BOLD_LEFT_BOLD);
            tr = unicode_to_utf8(CORNER_TOP_BOLD_RIGHT_BOLD);
            bl = unicode_to_utf8(CORNER_BOTTOM_BOLD_LEFT_BOLD);
            br = unicode_to_utf8(CORNER_BOTTOM_BOLD_RIGHT_BOLD);
            lt = unicode_to_utf8(TEE_TOP_BOLD_BOTTOM_BOLD_RIGHT);
            rt = unicode_to_utf8(TEE_TOP_BOLD_BOTTOM_BOLD_LEFT);
            v  = unicode_to_utf8(LINE_VERTICAL_BOLD);
            h  = unicode_to_utf8(LINE_HORIZONTAL_BOLD);
            break;
        case LINE_NONE:
            tl = tr = bl = br = v = h = " ";
            lt = unicode_to_utf8(HALFLINE_RIGHT);
            rt = unicode_to_utf8(HALFLINE_LEFT);
            break;
        case LINE:
        default:
            tl = unicode_to_utf8(CORNER_TOP_LEFT);
            tr = unicode_to_utf8(CORNER_TOP_RIGHT);
            bl = unicode_to_utf8(CORNER_BOTTOM_LEFT);
            br = unicode_to_utf8(CORNER_BOTTOM_RIGHT);
            lt = unicode_to_utf8(TEE_TOP_BOTTOM_RIGHT);
            rt = unicode_to_utf8(TEE_TOP_BOTTOM_LEFT);
            v  = unicode_to_utf8(LINE_VERTICAL);
            h  = unicode_to_utf8(LINE_HORIZONTAL);
            break;
    }
    save();

    // Top
    move(x, y);
    for (Color c : colors) color(c);
    std::cout << tl;
    for (int i = 0; i < width - 2; i++) std::cout << h;
    std::cout << tr;

    // Title
    move(x, y + 1);
    std::cout << v;
    color(COLOR_BOLD);
    if (title.length() <= width - 2) {
        std::cout << title;
        for (int i = 0; i < width - 2 - title.length(); i++) std::cout << " ";
    } else {
        for (int i = 0; i < width - 5; i++) std::cout << title[i];
        std::cout << "...";
    }
    color(COLOR_RESET);
    for (Color c : colors) color(c);
    std::cout << v;
    move(x, y + 2);
    std::cout << lt;
    for (int i = 0; i < width - 2; i++) std::cout << unicode_to_utf8(LINE_HORIZONTAL);
    std::cout << rt;

    // Sides
    int index = 0;
    for (int j = 3; j < height - 1; j++) {
        move(x, y + j);
        std::cout << v;
        if (j < height - 2 || content.length() - index <= width - 2) {
            for (int i = 0; i < width - 3; i++) std::cout << (index < content.length() ? content[index++] : ' ');
            if (index == content.length() - 1 || content[index] == ' ') {
                std::cout << content[index++];
            } else if (content[index + 1] == ' ') {
                std::cout << content[index++];
                while (content[index] == ' ') index++;
            } else if (index < content.length()) {
                std::cout << '-';
            } else {
                std::cout << ' ';
            }
        } else {
            for (int i = 0; i < width - 5; i++) std::cout << content[index++];
            std::cout << "...";
        }
        std::cout << v;
    }

    // Bottom
    move(x, y + height - 1);
    std::cout << bl;
    for (int i = 0; i < width - 2; i++) std::cout << h;
    std::cout << br;

    color(COLOR_RESET);
    restore();
}

void Console::drawLabel(int x, int y, std::string s, std::vector<Color> colors)
{
    save();
    move(x, y);
    for (Color c : colors) color(c);
    std::cout << s;
    color(COLOR_RESET);
    restore();
}

//https://stackoverflow.com/questions/12015571/how-to-print-unicode-character-in-c
int Console::utf8_to_unicode(std::string utf8_code)
{
    unsigned utf8_size = utf8_code.length();
    int unicode = 0;

    for (unsigned p=0; p<utf8_size; ++p)
    {
        int bit_count = (p? 6: 8 - utf8_size - (utf8_size == 1? 0: 1)),
            shift = (p < utf8_size - 1? (6*(utf8_size - p - 1)): 0);

        for (int k=0; k<bit_count; ++k)
            unicode += ((utf8_code[p] & (1 << k)) << shift);
    }

    return unicode;
}

//https://stackoverflow.com/questions/12015571/how-to-print-unicode-character-in-c
std::string Console::unicode_to_utf8(int unicode)
{
    std::string s = "";

    if (unicode>=0 and unicode <= 0x7f)  // 7F(16) = 127(10)
    {
        s = static_cast<char>(unicode);
    }
    else if (unicode <= 0x7ff)  // 7FF(16) = 2047(10)
    {
        unsigned char c1 = 192, c2 = 128;

        for (int k=0; k<11; ++k)
        {
            if (k < 6)  c2 |= (unicode % 64) & (1 << k);
            else c1 |= (unicode >> 6) & (1 << (k - 6));
        }

        s = c1;    s += c2;
    }
    else if (unicode <= 0xffff)  // FFFF(16) = 65535(10)
    {
        unsigned char c1 = 224, c2 = 128, c3 = 128;

        for (int k=0; k<16; ++k)
        {
            if (k < 6)  c3 |= (unicode % 64) & (1 << k);
            else if (k < 12) c2 |= (unicode >> 6) & (1 << (k - 6));
            else c1 |= (unicode >> 12) & (1 << (k - 12));
        }

        s = c1;    s += c2;    s += c3;
    }
    else if (unicode <= 0x1fffff)  // 1FFFFF(16) = 2097151(10)
    {
        unsigned char c1 = 240, c2 = 128, c3 = 128, c4 = 128;

        for (int k=0; k<21; ++k)
        {
            if (k < 6)  c4 |= (unicode % 64) & (1 << k);
            else if (k < 12) c3 |= (unicode >> 6) & (1 << (k - 6));
            else if (k < 18) c2 |= (unicode >> 12) & (1 << (k - 12));
            else c1 |= (unicode >> 18) & (1 << (k - 18));
        }

        s = c1;    s += c2;    s += c3;    s += c4;
    }

    return s;
}

void Console::move(int x, int y)
{
    std::cout << unicode_to_utf8(ESCAPE) << "[" << y << ";" << x << "H";
}

void Console::move(int n, CursorMovement direction)
{
    std::cout << unicode_to_utf8(ESCAPE) << n << static_cast<char>(direction);
}

void Console::save()
{
    std::cout << unicode_to_utf8(ESCAPE) << "[s";
}

void Console::restore()
{
    std::cout << unicode_to_utf8(ESCAPE) << "[u";
}