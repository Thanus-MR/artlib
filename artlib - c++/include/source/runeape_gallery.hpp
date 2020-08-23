/// @file runeape_gallery.hpp

/**
 * Copyright (c) 2020 Sri Lakshmi Kanthan P
 * 
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
 **/

#ifndef RUNEAPE_GALLERY
#define RUNEAPE_GALLERY

#include "filesystem"
#include "fstream"
#include "third_party/json/json.hpp"
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
         * @struct basic_runeape_base_gallery
         * @brief  abstract type of gallery class the used
         *         by runeape
         * @tparam Runapeconfig type of runeape_config
         **/
        template <typename Runeapeconfig>
        struct basic_runeape_base_gallery
        {
            using runeape_config = Runeapeconfig;

            basic_runeape_base_gallery()                                         = default;
            basic_runeape_base_gallery( const basic_runeape_base_gallery & )     = default;
            basic_runeape_base_gallery( basic_runeape_base_gallery && ) noexcept = default;
            virtual ~basic_runeape_base_gallery()                                = default;

            basic_runeape_base_gallery &operator=( const basic_runeape_base_gallery & ) = default;
            basic_runeape_base_gallery &operator=( basic_runeape_base_gallery && ) noexcept = default;

            /**
             * @brief clears the contents
             **/
            virtual void clear() = 0;

            /**
             * @brief used to set gallery file, call this before 
             *        any other operation.
             * @param fp full path to gallery file
             **/
            virtual void set_gallery( const std::filesystem::path &fp ) = 0;

            /**
             * @brief  used to get runeape config from font file
             * @return runeape_config
             **/
            virtual runeape_config get_runeape_config() = 0;

            /**
             * @brief used to get runeape_image from gallery
             * @param imgname image name
             * @return uneape_image
             **/
            virtual typename runeape_config::runeape_image
            operator()( const typename runeape_config::string_type &imgname ) = 0;
        };

        /**
         * @class  basic_runeape_json_gallery
         * @brief  This class reads gallery for anixt class
         *         from json file
         * @tparam Runeapeconfig type of runeape_config
         **/
        template <typename Runeapeconfig>
        class basic_runeape_json_gallery : public basic_runeape_base_gallery<Runeapeconfig>
        {
           protected:
            using base = basic_runeape_base_gallery<Runeapeconfig>;

           public:
            using runeape_config = Runeapeconfig;

           private:
            using char_type   = typename base::runeape_config::char_type;
            using size_type   = typename base::runeape_config::size_type;
            using traits_type = typename base::runeape_config::traits_type;
            using shrink_type = typename base::runeape_config::shrink;
            template <typename T>
            using alloc_type  = typename base::runeape_config::template alloc_type<T>;
            using string_type = typename base::runeape_config::string_type;
            template <typename T>
            using vector_type   = typename base::runeape_config::template vector_type<T>;
            using runeape_image = typename base::runeape_config::runeape_image;
            using json_type     = nlohmann::basic_json<std::map, std::vector,
                                                   string_type, bool, int64_t,
                                                   size_type, double, alloc_type>;

           private:
            /**
             * @brief stores gallery file.
             **/
            json_type json_gallery;

            /**
             * @brief converts ascii character of std::string
             *        to anixt_config::string_type
             **/
            string_type cvt( const std::string &str )
            {
                return string_type( str.begin(), str.end() );
            }

           public:
            basic_runeape_json_gallery()                                         = default;
            basic_runeape_json_gallery( const basic_runeape_json_gallery & )     = default;
            basic_runeape_json_gallery( basic_runeape_json_gallery && ) noexcept = default;
            ~basic_runeape_json_gallery()                                        = default;

            basic_runeape_json_gallery &operator=( const basic_runeape_json_gallery & ) = default;
            basic_runeape_json_gallery &operator=( basic_runeape_json_gallery && ) noexcept = default;

            /**
             * @brief clears the contents
             **/
            void clear() override
            {
                this->json_gallery.clear();
            }

            /**
             * @brief swap contents
             * @param obj object to swap
             **/
            void swap( basic_runeape_json_gallery &obj )
            {
                using std::swap;
                swap( this->json_gallery, obj.json_gallery );
            }

            /**
             * @brief used to set gallery file, call this before 
             *        any other operation.
             * @param fp full path to gallery file
             **/
            void set_gallery( const std::filesystem::path &fp ) override
            {
                std::basic_ifstream<char_type, traits_type> gallery_file { fp };

                if ( fp.extension() != ".json" )
                {
                    throw std::runtime_error( "File should be json" );
                }

                if ( !gallery_file.is_open() )
                {
                    throw std::runtime_error( "Unable to open file" );
                }

                gallery_file >> this->json_gallery;
            }

            /**
             * @brief  used to get runeape_config
             * @return runeape_config
             **/
            runeape_config get_runeape_config() override
            {
                runeape_config ret;

                ret.HardBlank = this->json_gallery[cvt( "runeape_config" )][cvt( "HardBlank" )]
                                    .template get<size_type>();
                ret.Height    = this->json_gallery[cvt( "runeape_config" )][cvt( "Height" )]
                                    .template get<size_type>();
                ret.Shrink    = this->json_gallery[cvt( "runeape_config" )][cvt( "Shrink" )]
                                    .template get<shrink_type>();

                return ret;
            }

            /**
             * @brief used to get runeape_image from gallery
             * @param imgname image name
             * @return uneape_image
             **/
            runeape_image operator()( const string_type &imgname ) override
            {
                return this->json_gallery[cvt( "runeape_image" )][imgname]
                           .template get<runeape_image>();
            }
        };

        /**
         * @brief swap two objects
         * @param lhs object one to swap
         * @param rhs object two to swap
         **/
        template <typename Runeapeconfig>
        void swap( basic_runeape_json_gallery<Runeapeconfig> &lhs,
                   basic_runeape_json_gallery<Runeapeconfig> &rhs ) noexcept
        {
            lhs.swap( rhs );
        }

    } // namespace art

} // namespace sri

#endif