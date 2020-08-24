///@file basic_font.hpp

/**
 * Copyright (c) 2020 Sri Lakshmi Kanthan P
 * 
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
 */

#ifndef BASIC_FONT_HEADER
#define BASIC_FONT_HEADER

#include "anixt_config.hpp"
#include "filesystem"
#include "fstream"
#include "third_party/json/json.hpp"
#include "map"

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
         * @struct basic_anixt_base_font
         * @brief  abstract class for font types that used
         *         by anixt class
         * @tparam Anixtconfig type of anixt_config
         **/
        template <typename Anixtconfig>
        struct basic_anixt_base_font
        {
            using anixt_config = Anixtconfig;

            basic_anixt_base_font()                                    = default;
            basic_anixt_base_font( const basic_anixt_base_font & )     = default;
            basic_anixt_base_font( basic_anixt_base_font && ) noexcept = default;
            virtual ~basic_anixt_base_font()                           = default;

            basic_anixt_base_font &operator=( const basic_anixt_base_font & ) = default;
            basic_anixt_base_font &operator=( basic_anixt_base_font && ) noexcept = default;

            /**
             * @brief clears the contents
             **/
            virtual void clear() noexcept = 0;

            /**
             * @brief used to set font file, call this before 
             *        any other operation.
             * @param fp full path to font file
             **/
            virtual void set_font( const std::filesystem::path &fp ) = 0;

            /**
             * @brief  used to get anixt config from font file
             * @return anixt_config
             **/
            virtual anixt_config get_anixt_config() = 0;

            /**
             * @brief used to get key equivalent of anixt_letter
             *        from font
             * @param key key letter
             * @return anixt_letter
             **/
            virtual typename anixt_config::anixt_letter
            operator()( typename anixt_config::char_type key ) = 0;
        };

        /**
         * @class  basic_anixt_json_font
         * @brief  This class reads font for anixt class
         *         from json file
         * @tparam Anixtconfig type of anixt_config
         **/
        template <typename Anixtconfig>
        class basic_anixt_json_font : public basic_anixt_base_font<Anixtconfig>
        {
           protected:
            using base = basic_anixt_base_font<Anixtconfig>;

           public:
            using anixt_config = typename base::anixt_config;

           private:
            using char_type    = typename base::anixt_config::char_type;
            using size_type    = typename base::anixt_config::size_type;
            using traits_type  = typename base::anixt_config::traits_type;
            using string_type  = typename base::anixt_config::string_type;
            using shrink_type  = typename base::anixt_config::shrink;
            using anixt_letter = typename base::anixt_config::anixt_letter;
            template <typename T>
            using alloc_type = typename base::anixt_config::template alloc_type<T>;
            using json_type  = nlohmann::basic_json<std::map, std::vector,
                                                   string_type, bool, int64_t,
                                                   size_type, double, alloc_type>;

           private:
            /**
             * @brief stores font file.
             **/
            json_type json_font;

            /**
             * @brief converts ascii character of std::string
             *        to anixt_config::string_type
             **/
            static string_type cvt( const std::string &str )
            {
                return string_type( str.begin(), str.end() );
            }

           public:
            basic_anixt_json_font()                                    = default;
            basic_anixt_json_font( const basic_anixt_json_font & )     = default;
            basic_anixt_json_font( basic_anixt_json_font && ) noexcept = default;
            ~basic_anixt_json_font()                                   = default;

            basic_anixt_json_font &operator=( const basic_anixt_json_font & ) = default;
            basic_anixt_json_font &operator=( basic_anixt_json_font && ) noexcept = default;

            /**
             * @brief clears the contents
             **/
            void clear() noexcept override
            {
                this->json_font.clear();
            }

            /**
             * @brief swap contents
             * @param obj object to swap
             **/
            void swap( basic_anixt_json_font &obj )
            {
                using std::swap;
                swap( this->json_font, obj.json_font );
            }

            /**
             * @brief used to set font file, call this before 
             *        any other operation.
             * @param fp full path to font file
             **/
            void set_font( const std::filesystem::path &fp ) override
            {
                std::basic_ifstream<char_type, traits_type> font_file { fp };

                if ( fp.extension() != ".json" )
                {
                    throw std::runtime_error( "File should be json" );
                }

                if ( !font_file.is_open() )
                {
                    throw std::runtime_error( "Unable to open file" );
                }

                font_file >> this->json_font;
            }

            /**
             * @brief  used to get anixt_config
             * @return anixt_config
             **/
            anixt_config get_anixt_config() override
            {
                anixt_config ret;

                ret.HardBlank = this->json_font[cvt( "anixt_config" )][cvt( "HardBlank" )]
                                    .template get<size_type>();
                ret.Height    = this->json_font[cvt( "anixt_config" )][cvt( "Height" )]
                                    .template get<size_type>();
                ret.Shrink    = this->json_font[cvt( "anixt_config" )][cvt( "Shrink" )]
                                    .template get<shrink_type>();

                return ret;
            }

            /**
             * @brief used to get anixt_letter from font
             * @param key key letter
             * @return anixt_letter
             **/
            anixt_letter operator()( char_type key )
            {
                return this->json_font[cvt( "anixt_letter" )][string_type( 1, key )]
                           .template get<anixt_letter>();
            }
        };

        /**
         * @brief swap two anixt_config
         * @param lhs object one to swap
         * @param rhs object two to swap
         **/
        template <typename Anixtconfig>
        void swap( basic_anixt_json_font<Anixtconfig> &lhs,
                   basic_anixt_json_font<Anixtconfig> &rhs ) noexcept
        {
            lhs.swap( rhs );
        }

    } // namespace art

} // namespace srilakshmikanthanp

#endif