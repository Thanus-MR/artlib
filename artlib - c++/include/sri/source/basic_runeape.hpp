/// @file basic_runeape.hpp

/**
 * Copyright (c) 2020 Sri Lakshmi Kanthan P
 * 
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
 **/

#ifndef BASIC_RUNEAPE
#define BASIC_RUNEAPE

#include "filesystem"
#include "runeape_config.hpp"

/**
 * @namespace sri
 * @brief outer namespace
 **/
namespace sri
{
    /**
     * @namespace art
     * @brief contains art classes and functions
     **/
    namespace art
    {
        /**
         * @class  basic_runeape
         * @brief  primary class for runeape library
         * @tparam StyleT style_type
         * @tparam GalleryT gallery_type
         * @tparam Runeapeconfig runeape_config
         **/
        template <typename StyleT, typename GalleryT, typename Runeapeconfig>
        class basic_runeape
        {
           public:
            using style_type     = StyleT;
            using gallery_type   = GalleryT;
            using runeape_config = Runeapeconfig;

           private:
            using char_type     = typename runeape_config::char_type;
            using size_type     = typename runeape_config::size_type;
            using string_type   = typename runeape_config::string_type;
            using shrink_type   = typename runeape_config::shrink;
            using runeape_image = typename runeape_config::runeape_image;
            template <typename T>
            using vector_type = typename runeape_config::template vector_type<T>;

           private:
            mutable style_type       style;
            mutable gallery_type     gallery;
            runeape_config           config;
            vector_type<string_type> imgnames;

            /**
             * @brief converts ascii character of std::string
             *        to anixt_config::string_type
             **/
            string_type cvt( const std::string &str )
            {
                return string_type( str.begin(), str.end() );
            }

           public:
            basic_runeape()                            = default;
            basic_runeape( const basic_runeape & )     = delete;
            basic_runeape( basic_runeape && ) noexcept = default;
            ~basic_runeape()                           = default;

            basic_runeape &operator=( const basic_runeape & ) = delete;
            basic_runeape &operator=( basic_runeape && ) = default;

            /**
             * @brief constructor
             * @param fp full path to file
             **/
            basic_runeape( const std::filesystem::path &fp )
            {
                this->clear();
                this->gallery.set_gallery( fp );
                this->config = this->gallery.get_runeape_config();
                this->style.set_config( this->config );

                if ( !( style_type::shrink_level <= this->config.Shrink ) )
                {
                    throw std::runtime_error( "style not supported" );
                }
            }

            /**
             * @brief clears the contents
             **/
            void clear()
            {
                this->style.clear();
                this->gallery.clear();
                this->config.clear();
                this->imgnames.clear();
            }

            /**
             * @brief swap two basic_runeape
             * @param obj object to swap
             **/
            void swap( basic_runeape &obj )
            {
                using std::swap;
                swap( this->style, obj.style );
                swap( this->gallery, obj.gallery );
                swap( this->config, obj.config );
                swap( this->imgnames, obj.imgnames );
            }

            /**
             * @brief used to set gallery file
             * @param fp full path to gallery file
             **/
            void set_gallery( const std::filesystem::path &fp )
            {
                this->clear();
                this->gallery.set_gallery( fp );
                this->config = this->gallery.get_runeape_config();
                this->style.set_config( this->config );

                if ( !( style_type::shrink_level <= this->config.Shrink ) )
                {
                    throw std::runtime_error( "style not supported" );
                }
            }

            /**
             * @brief saves(append) imagename
             * @param imagname image name
             **/
            basic_runeape &load( const string_type &imgname )
            {
                this->imgnames.push_back( imgname );
                return *this;
            }

            /**
             * @brief return current image names
             * @return image names as vector_type<string_type>
             **/
            vector_type<string_type> operator()() const
            {
                return this->imgnames;
            }

            /**
             * @brief clears existing images and add imgname
             * @param imgname image name
             **/
            basic_runeape &operator()( const string_type &imgname )
            {
                this->imgnames.clear();
                this->imgnames.push_back( imgname );
                return *this;
            }

            /**
             * @brief return configuration
             * @return runeape_config
             **/
            runeape_config get_runeape_config() const
            {
                return this->config;
            }

            /**
             * @brief returns runeape_image
             * @return runeape_image
             **/
            runeape_image get_runeape_image() const
            {
                vector_type<runeape_image> images;
                runeape_image              image;

                for ( const auto &i : this->imgnames )
                {
                    images.push_back( this->gallery( i ) );
                }

                image = this->style( images );

                return image;
            }
        };

        /**
         * @brief swap two object
         * @param lhs object one to swap
         * @param rhs object two to swap
         **/
        template <typename StyleT, typename GalleryT, typename Runeapeconfig>
        void swap( basic_runeape<StyleT, GalleryT, Runeapeconfig> &lhs,
                   basic_runeape<StyleT, GalleryT, Runeapeconfig> &rhs )
        {
            lhs.swap( rhs );
        }

    } // namespace art

} // namespace sri

#endif