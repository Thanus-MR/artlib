#include "artlib.hpp"
#include "iostream"

#define FONTDIR     "path to font dir"
#define GALLERYDIR  "path to gallery dir"

using namespace srilakshmikanthanp::art;

int main()
{
    anixt<anixt_smushed_style>         myanixt;
    runeape<runeape_kerning_style<10>> myruneape;

    myanixt.set_font( FONTDIR "straight.json" );
    myruneape.set_gallery( GALLERYDIR "logos.json" );

    myanixt << "LINUX";
    myruneape.load( "linux" );

    std::cout << frame( appendleft( myruneape, addtopline( myanixt.get_anixt_string(), 10 ) ), '=', '#' );
}