///@file basic_anixt.hpp

/**
 * Copyright (c) 2020 Sri Lakshmi Kanthan P
 * 
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
 */

#ifndef BASIC_ANIXT_HEADER
#define BASIC_ANIXT_HEADER

#include "anixt_config.hpp"
#include "filesystem"
#include "json.hpp"
#include "ostream"
#include "sstream"

#define BASIC_ANIXT_BASE_PARAM       \
    typename Anixtconfig::char_type, \
        typename Anixtconfig::traits_type

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
         * @class  basic_anixt
         * @brief  primary class for anixt library
         * @tparam StyleT style_type
         * @tparam FontT font _type
         * @tparam Anixtconfig anixt_config
         **/
        template <typename StyleT, typename FontT, typename Anixtconfig>
        class basic_anixt : public std::basic_ostream<BASIC_ANIXT_BASE_PARAM>
        {
           protected:
            using base = std::basic_ostream<BASIC_ANIXT_BASE_PARAM>;

           public:
            using style_type   = StyleT;
            using font_type    = FontT;
            using anixt_config = Anixtconfig;

           private:
            using char_type    = typename anixt_config::char_type;
            using size_type    = typename anixt_config::size_type;
            using traits_type  = typename anixt_config::traits_type;
            using string_type  = typename anixt_config::string_type;
            using shrink_type  = typename anixt_config::shrink;
            using anixt_letter = typename anixt_config::anixt_letter;
            using anixt_string = typename anixt_config::anixt_string;
            template <typename T>
            using vector_type = typename anixt_config::template vector_type<T>;
            template <typename T>
            using alloc_type = typename anixt_config::template alloc_type<T>;

           public:
            using string_buff_type = std::basic_stringbuf<char_type, traits_type, alloc_type<char_type>>;

           private:
            string_buff_type   string_buff;
            anixt_config       config;
            mutable font_type  font;
            mutable style_type style;

            /**
             * @brief converts ascii character of std::string
             *        to anixt_config::string_type
             **/
            static string_type cvt( const std::string &str )
            {
                return string_type( str.begin(), str.end() );
            }

           public:
            /**
             * @brief default constructor
             **/
            basic_anixt()
                : base(),
                  string_buff( std::ios_base::out )
            {
                this->init( &string_buff );
            }

            /**
             * @brief copy constructor[deleted]
             **/
            basic_anixt( const basic_anixt & ) = delete;

            /**
             * @brief move constructor
             **/
            basic_anixt( basic_anixt &&obj ) noexcept
                : base( std::move( obj ) ),
                  string_buff( std::move( obj.string_buff ) )
            {
                base::set_rdbuf( &this->string_buff );
            }

            /**
             * @brief destructor
             **/
            virtual ~basic_anixt() = default;

            /**
             * @brief copy assignment[deleted]
             **/
            basic_anixt &operator=( const basic_anixt & ) = delete;

            /**
             * @brief move assignment
             **/
            basic_anixt &operator=( basic_anixt &&obj ) noexcept
            {
                base::operator    =( std::move( obj ) );
                this->string_buff = std::move( obj.string_buff );
                return *this;
            }

            /**
             * @brief constructor
             * @param mode buffer mode 
             **/
            explicit basic_anixt( std::ios_base::openmode mode )
                : base(),
                  string_buff( mode | std::ios_base::out )
            {
                this->init( &string_buff );
            }

            /**
             * @brief constructor
             * @param fp full path to file
             **/
            basic_anixt( const std::filesystem::path &fp )
                : base(),
                  string_buff( std::ios_base::out )
            {
                this->font.set_font( fp );
                this->config = this->font.get_anixt_config();
                this->style.set_anixt_config( this->config );
                this->init( &string_buff );

                if ( !( style_type::shrink_level <= this->config.Shrink ) )
                {
                    throw std::runtime_error( "Style is not supported" );
                }
            }

            /**
             * @brief clears the contents
             **/
            void clear() noexcept
            {
                this->operator()( "" );
                this->config.clear();
                this->font.clear();
                this->style.clear();
            }

            /**
             * @brief swap two anixt_config
             * @param obj object to swap
             **/
            void swap( basic_anixt &obj ) noexcept
            {
                using std::swap;
                base::swap( obj );
                string_buff.swap( obj.string_buff );
                swap( this->config, obj.config );
                swap( this->font, obj.font );
                swap( this->style, obj.style );
            }

            /**
             * @brief returns pointer to buffer
             * @return buffer pointer
             **/
            string_buff_type *rdbuf() const
            {
                return const_cast<string_buff_type *>( &string_buff );
            }

            /**
             * @brief  get string of buffer
             * @return copy of string buffer
             **/
            string_type operator()() const
            {
                return this->string_buff.str();
            }

            /**
             * @brief to set string of buffer
             * @param str string for buffer
             **/
            void operator()( const string_type &str )
            {
                this->string_buff.str( str );
            }

            /**
             * @brief used to set font file
             * @param fp full path to font file
             **/
            void set_font( const std::filesystem::path &fp )
            {
                this->clear();
                this->font.set_font( fp );
                this->config = this->font.get_anixt_config();
                this->style.set_config( this->config );

                if ( !( style_type::shrink_level <= this->config.Shrink ) )
                {
                    throw std::runtime_error( "Style is not supported" );
                }
            }

            /**
             * @brief return configuration
             * @return anixt_config
             **/
            anixt_config get_anixt_config()
            {
                return this->config;
            }

            /**
             * @brief returns anixt string
             * @return anixt_string
             **/
            anixt_string get_anixt_string() const
            {
                string_type               buff { this->operator()() };
                vector_type<anixt_letter> anixtletters;
                anixt_string              anixtstring;

                for ( auto i : buff )
                {
                    anixtletters.push_back( this->font( i ) );
                }

                anixtstring = style( anixtletters );

                return anixtstring;
            }
        };

        /**
         * @brief swap two object
         * @param lhs object one to swap
         * @param rhs object two to swap
         **/
        template <typename StyleT, typename FontT, typename Anixtconfig>
        void swap( basic_anixt<StyleT, FontT, Anixtconfig> &lhs,
                   basic_anixt<StyleT, FontT, Anixtconfig> &rhs )
        {
            lhs.swap( rhs );
        }

    } // namespace art

} // namespace sri

#undef BASIC_ANIXT_BASE_PARAM

#endif