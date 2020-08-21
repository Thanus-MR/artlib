#include "iostream"
#include "artlib.hpp"
#include "string"

#define FONTDIR "path to font dir"

using namespace sri::art;

int main()
{
    anixt<anixt_smushed_style> myanixt;
    int                        col_code{0};

    myanixt.set_font(FONTDIR "straight.json");

    col_code = 31;
    for (const auto &i : myanixt("Color").get_anixt_string())
    {
        std::cout << "\e[" + std::to_string(col_code) + "m" << i << "\e[0m" << std::endl;
        ++col_code;
    }

    col_code = 31;
    for (const auto &i : myanixt("ColorBg").get_anixt_string())
    {
        std::cout << "\e[" + std::to_string(col_code) + ";47m" << i << "\e[0m" << std::endl;
        ++col_code;
    }

    return 0;
}