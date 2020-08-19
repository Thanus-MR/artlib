#include "artlib.hpp"
#include "iostream"

#define FONTDIR                                       \
    "/media/srilakshmikanthanp/My Drive/Source Code/" \
    "cross platform/Project/Arts/1 . anixt fonts - json/"

#define GALLERYDIR                                    \
    "/media/srilakshmikanthanp/My Drive/Source Code/" \
    "cross platform/Project/Arts/2 . runeape galleries - json/"

using namespace sri::art;

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