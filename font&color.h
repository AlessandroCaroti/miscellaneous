#include <ostream>

namespace Color {
    enum Code {
    	   //foreground
        FG_BLACK	= 30,
        FG_RED      = 31,
        FG_GREEN    = 32,
        FG_YELLOW	= 33,
        FG_BLUE     = 34,
        FG_MAGENTA	= 35,
        FG_CYAN	= 36,
        FG_L_GRAY	= 37,
        FG_DEFAULT  = 39,
        
        BG_BLACK	= 40,
        BG_RED      = 41,
        BG_GREEN    = 42,
        BG_YELLOW	= 43,
        BG_BLUE     = 44,
        BG_MAGENTA	= 45,
        BG_CYAN	= 46,
        BG_L_GRAY	= 47,
        BG_DEFAULT  = 49,
        
        FG_D_GRAY	= 90,
        FG_L_RED	= 91,
        FG_L_GREEN	= 92,
        FG_L_YELLOW	= 93,
        FG_L_BLUE	= 94,
        FG_L_MAGENTA= 95,
        FG_L_CYAN	= 96,
        FG_WHITE	= 97,
        //background
        BG_D_GRAY	= 100,
        BG_L_RED	= 101,
        BG_L_GREEN	= 102,
        BG_L_YELLOW	= 103,
        BG_L_BLUE	= 104,
        BG_L_MAGENTA= 105,
        BG_L_CYAN	= 106,
        BG_WHITE	= 107
    };
    class Modifier {
        Code code;
    public:
        Modifier(Code pCode) : code(pCode) {}
        friend std::ostream&
        operator<<(std::ostream& os, const Modifier& mod) {
            return os << "\033[" << mod.code << "m";
        }
    };
}


/*	ESEMPIO
#include "colormod.h" // namespace Color
#include <iostream>
using namespace std;
int main() {
    Color::Modifier red(Color::FG_RED);
    Color::Modifier def(Color::FG_DEFAULT);
    cout << "This ->" << red << "word" << def << "<- is red." << endl;
}

*/
