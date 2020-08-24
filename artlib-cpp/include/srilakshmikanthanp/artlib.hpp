/// @file artlib.hpp

/**
 * Copyright (c) 2020 Sri Lakshmi Kanthan P
 * 
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
 **/

#ifndef ARTLIB_HEADER
#define ARTLIB_HEADER

#include "algorithm"
#include "source/anixt_config.hpp"
#include "source/anixt_font.hpp"
#include "source/anixt_style.hpp"
#include "source/basic_anixt.hpp"
#include "source/basic_runeape.hpp"
#include "source/runeape_config.hpp"
#include "source/runeape_gallery.hpp"
#include "source/runeape_style.hpp"

/**
 * @mainpage artlib
 * @version  0.1.0
 * @author   Sri Lakshmi Kanthan p
 **/

// clang-format off
/**
 * @namespace srilakshmikanthanp
 * @brief outer namespace
 **/
namespace srilakshmikanthanp
{
    /**
     * @namespace art
     * @brief contains art classes and functions
     **/
    namespace art
    {
        /**
         * @brief json_font type for anixt class
         **/
        using anixt_json_font           =     basic_anixt_json_font<anixt_config<char>>;
        
        /**
         * @brief anixt_untouched_style type for anixt class
         **/
        using anixt_untouched_style     =     basic_anixt_untouched_style<anixt_config<char>>;

        /**
         * @brief  anixt_kerning_style type for anixt class
         * @tparam Kerning Kerning space
         **/
        template <unsigned int Kerning>
        using anixt_kerning_style       =     basic_anixt_kerning_style<Kerning, anixt_config<char>>;

        /**
         * @brief  anixt_smushed_style type for anixt class
         **/
        using anixt_smushed_style       =     basic_anixt_smushed_style<anixt_config<char>>;

        /**
         * @brief  anixt
         * @tparam StyleT style type
         * @tparam FontT font type, defaults anixt_json_font
         **/
        template <typename StyleT, typename FontT = anixt_json_font>
        using anixt                     =     basic_anixt<StyleT, FontT, anixt_config<char>>;

        /**
         * @brief json_gallery type for runeape class
         **/
        using runeape_json_gallery      =     basic_runeape_json_gallery<runeape_config<char>>;

       /**
         * @brief runeape_untouched_style type for runeape class
         **/
        using runeape_untouched_style   =     basic_runeape_untouched_style<runeape_config<char>>;

        /**
         * @brief  runeape_kerning_style type for runeape class
         * @tparam Kerning Kerning space
         **/
        template <unsigned int Kerning>
        using runeape_kerning_style     =     basic_runeape_kerning_style<Kerning, runeape_config<char>>;

        /**
         * @brief  runeape
         * @tparam StyleT style type
         * @tparam GalleryT type, defaults runeape_json_gallery
         **/
        template <typename StyleT, typename GalleryT = runeape_json_gallery>
        using runeape                   =     basic_runeape<StyleT, GalleryT, runeape_config<char>>;

    } // namespace art

} // namespace srilakshmikanthanp

// clang-format on
namespace srilakshmikanthanp
{
    namespace art
    {
        /**
         * @brief frmes the anixt_string or runeape_image
         * @param obj value
         * @param hor horizontal character
         * @param ver vertical character
         * @return modified value
         **/
        template <typename Type, typename CharT>
        auto frame( const Type &obj, CharT hor, CharT ver )
        {
            Type ret;

            if ( obj.size() )
            {
                typename Type::string_type str( ( obj[0].size() + 4 ), hor );

                ret.push_back( str );

                for ( const auto &i : obj )
                {
                    typename Type::string_type font;
                    typename Type::string_type back;

                    font.push_back( ver );
                    font.push_back( ' ' );
                    back.push_back( ' ' );
                    back.push_back( ver );

                    ret.push_back( font + i + back );
                }

                ret.push_back( str );
            }

            return ret;
        }

        /**
         * @brief adds a line in top in anixt_strng or runeape_image
         * @param obj value
         * @param n   lines, defults to 1
         * @return modified value
         **/
        template <typename Type>
        auto addtopline( const Type &obj, size_t n = 1 )
        {
            Type ret;

            if ( obj.size() )
            {
                typename Type::string_type str( obj[0].size(), ' ' );

                for ( size_t i = 0; i < n; i++ )
                {
                    ret.push_back( str );
                }

                for ( const auto &i : obj )
                {
                    ret.push_back( i );
                }
            }

            return ret;
        }

        /**
         * @brief adds a line in bottom in anixt_strng or runeape_image
         * @param obj value
         * @param n   lines, defults to 1
         * @return modified value
         **/
        template <typename Type>
        auto addbottomline( const Type &obj, size_t n = 1 )
        {
            Type ret;

            if ( obj.size() )
            {
                typename Type::string_type str( obj[0].size(), ' ' );

                for ( const auto &i : obj )
                {
                    ret.push_back( i );
                }

                for ( size_t i = 0; i < n; i++ )
                {
                    ret.push_back( str );
                }
            }

            return ret;
        }

        /**
         * @brief appends a anixt_string or runeape_image in right
         * @param obj Runeape
         * @param value value
         * @return modified value
         **/
        template <typename Runeape, typename Type>
        auto appendright( const Runeape &obj, const Type &value )
        {
            typename Runeape::runeape_config::runeape_image ret;
            typename Runeape::runeape_config::runeape_image rimg;
            Type                                            val;

            rimg = obj.get_runeape_image();
            val  = value;

            if ( rimg.size() < val.size() )
            {
                size_t diff = val.size() - rimg.size();
                rimg        = addbottomline( rimg, diff );
            }
            else if ( rimg.size() > val.size() )
            {
                size_t diff = rimg.size() - val.size();
                val         = addbottomline( val, diff );
            }

            std::vector<typename Runeape::runeape_config::runeape_image> rimgs;
            rimgs.resize( 2, typename Runeape::runeape_config::runeape_image() );

            for ( const auto &i : rimg )
            {
                rimgs[0].push_back( i );
            }

            for ( const auto &i : val )
            {
                rimgs[1].push_back( i );
            }

            typename Runeape::style_type     style;
            typename Runeape::runeape_config config;
            config           = obj.get_runeape_config();
            config.HardBlank = '\0';
            config.Height    = rimg.size();

            style.set_config( config );

            ret = style( rimgs );

            return ret;
        }

        /**
         * @brief appends a anixt_string or runeape_image in left
         * @param obj Runeape
         * @param value value
         * @return modified value
         **/
        template <typename Runeape, typename Type>
        auto appendleft( const Runeape &obj, const Type &value )
        {
            typename Runeape::runeape_config::runeape_image ret;
            typename Runeape::runeape_config::runeape_image rimg;
            Type                                            val;

            rimg = obj.get_runeape_image();
            val  = value;

            if ( rimg.size() < val.size() )
            {
                size_t diff = val.size() - rimg.size();
                rimg        = addbottomline( rimg, diff );
            }
            else if ( rimg.size() > val.size() )
            {
                size_t diff = rimg.size() - val.size();
                val         = addbottomline( val, diff );
            }

            std::vector<typename Runeape::runeape_config::runeape_image> rimgs;
            rimgs.resize( 2, typename Runeape::runeape_config::runeape_image() );

            for ( const auto &i : rimg )
            {
                rimgs[1].push_back( i );
            }

            for ( const auto &i : val )
            {
                rimgs[0].push_back( i );
            }

            typename Runeape::style_type     style;
            typename Runeape::runeape_config config;
            config           = obj.get_runeape_config();
            config.HardBlank = '\0';
            config.Height    = rimg.size();

            style.set_config( config );

            ret = style( rimgs );

            return ret;
        }

    } // namespace art

} // namespace srilakshmikanthanp

#endif