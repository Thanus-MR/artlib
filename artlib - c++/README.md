<!--
 Copyright (c) 2020 Sri Lakshmi Kanthan P
 
 This software is released under the MIT License.
 https://opensource.org/licenses/MIT
-->

# **artlib - c++**

## Make arts with artlib

~~~~~artlib
            _   _ _ _
  __ _ _ __| |_| (_) |__  
 / _` | '__| __| | | '_ \
| (_| | |  | |_| | | |_) |
 \__,_|_|   \__|_|_|_.__/

 Generate art with artlib
~~~~~

artlib implementation for c++.

## anixt

use anixt to generate text arts known as FIGLET anixt is a template class
that accepts style type, currently available style types are untouched,
Kerning, smushed. kerning is itself a template class that accepts kerning
space. `Note : anixt class only supports charactes in font`

### untouched style (straight)

~~~~~artlib

               _                        _                _
 _   _  _ __  | |_   ___   _   _   ___ | |__    ___   __| |
| | | || '_ \ | __| / _ \ | | | | / __|| '_ \  / _ \ / _` |
| |_| || | | || |_ | (_) || |_| || (__ | | | ||  __/| (_| |
 \__,_||_| |_| \__| \___/  \__,_| \___||_| |_| \___| \__,_|

~~~~~

### kerning as 0 (straight)

~~~~~artlib

 _                       _
| | __ ___  _ __  _ __  (_) _ __    __ _
| |/ // _ \| '__|| '_ \ | || '_ \  / _` |
|   <|  __/| |   | | | || || | | || (_| |
|_|\_\\___||_|   |_| |_||_||_| |_| \__, |
                                   |___/

~~~~~

## smushed (straight)

~~~~~artlib
                         _              _
 ___ _ __ ___  _   _ ___| |__   ___  __| |
/ __| '_ ` _ \| | | / __| '_ \ / _ \/ _` |
\__ \ | | | | | |_| \__ \ | | |  __/ (_| |
|___/_| |_| |_|\__,_|___/_| |_|\___|\__,_|

~~~~~

## runeape

use runeape to generate image arts, it is a template class that accepts
style type, currently available type are untouched, kerning. kerning is itself
template class that accepts kerning space.

### anixt added to runeape and framed (logos and straight)

~~~~~artlib
========================================================================
#                                                                      #
#                                                                      #
#                                                                      #
#                                                                      #
#                                                                      #
#                                                       _nnnn_         #
#                                                      dGGGGMMb        #
#                                                     @p~qp~~qMb       #
#                                                     M|@||@) M|       #
#                                                     @,----.JM|       #
#            _     ___ _   _ _   ___  __             JS^\__/  qKL      #
#           | |   |_ _| \ | | | | \ \/ /            dZP        qKRb    #
#           | |    | ||  \| | | | |\  /            dZP          qKKb   #
#           | |___ | || |\  | |_| |/  \           fZP            SMMb  #
#           |_____|___|_| \_|\___//_/\_\          HZM            MMMM  #
#                                                 FqM            MMMM  #
#                                               __| ".        |\dS"qML #
#                                               |    `.       | `' \Zq #
#                                              _)      \.___.,|     .' #
#                                              \____   )MMMMMP|   .'   #
#                                                   `-'       `--'     #
#                                                                      #
#                                                                      #
#                                                                      #
#                                                                      #
#                                                                      #
========================================================================
~~~~~

## Examples

See [test](tests/) directory for example

## Documentation

[See Doxygen generated dodument](https://srilakshmikanthan-p.github.io/artlib/Doxygen/artlib%20-%20c%2B%2B/doc/html/index.html)

## Font Converter

A [Font Converter](fontcvt/fontcvt.cpp) Written in c++ will convert FIGLET font to anixt font,
`Note : Shrink value is not detected by Font Converter, It will Set it to 0`

---
Copyright (c) 2020 Sri Lakshmi Kanthan P

This software is released under the [MIT](https://opensource.org/licenses/MIT) License
