#include "artlib.hpp"
#include "iostream"
#include "string"

#define FONTDIR     "path to font"
#define GALLERYDIR  "path to gallery"

using namespace sri::art;

int main()
{
    anixt<anixt_smushed_style>         myanixt;
    runeape<runeape_kerning_style<10>> myruneape;

    myanixt.set_font( FONTDIR "straight.json" );
    myruneape.set_gallery( GALLERYDIR "logos.json" );

    myanixt << "LINUX";
    myruneape.load( "linux" );

    for(const auto &i : frame( appendleft( myruneape, addtopline( myanixt.get_anixt_string(), 10 ) ), '=', '#' ))
    {
        std::cout << "\e[35;47m" << i << "\e[0m" << std::endl;
    }
}