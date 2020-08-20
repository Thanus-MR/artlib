<!--
 Copyright (c) 2020 Sri Lakshmi Kanthan P
 
 This software is released under the MIT License.
 https://opensource.org/licenses/MIT
-->

# **artlib**

## Make arts with artlib

~~~~~artlib
            _   _ _ _
  __ _ _ __| |_| (_) |__  
 / _` | '__| __| | | '_ \
| (_| | |  | |_| | | |_) |
 \__,_|_|   \__|_|_|_.__/

 Generate art with artlib
~~~~~

Genarate art known as ascii-art or art with artlib easily.

## anixt

use anixt to generate text arts known as FIGLET

## runeape

use runeape to generate image arts

## Fonts

anixt currently able to read from json file type and that json font file looks like

~~~~~json
{
    "anixt_config"   :
    {
        "Height"     : "Height of font characters in uint",
        "HardBlank"  : "HardBlank of font characters in uint",
        "Shrink"     : "Shrink level of font, possible values are 0, 1, 2
                         If you use 0 then the font support untouched style
                         only, 2 is for both untouched and Kerning style,
                         3 for all untouched, Kerning, smushed style"
    },

    "anixt_letter"   :
    {
        "keycharacter" :
        [
            "anixtletter"
        ]
    }
}
~~~~~

### Available Fonts

- [straight](1.fonts%20-%20json/straight.json)
- [slant](1.fonts%20-%20json/slant.json)
- [bubble](1.fonts%20-%20json/bubble.json)

## Galleries

runeape currently able to read from json file type.

~~~~~json
{
    "runeape_config"   :
    {
        "Height"     : "Height of images in the gallery in uint",
        "HardBlank"  : "HardBlank images in the gallery in uint",
        "Shrink"     : "Shrink level of images in the gallery,
                         possible values are 0, 1. If you use
                         0 then the gallery support untouched style
                         only, 2 is for both untouched and Kerning style"
    },

    "runeape_image"   :
    {
        "imagename" :
        [
            "image"
        ]
    }
}
~~~~~

### Available Galleries

- [logos](2.galleries%20-%20json/logos.json)

## Library Implemented Languages

- [c++](artlib%20-%20c++)

## Thanks

- Thanking to [Thanus MR](https://github.com/Thanus-MR) for him support.

-----

Copyright (c) 2020 Sri Lakshmi Kanthan P

This software is released under the [MIT](https://opensource.org/licenses/MIT) License
