/// @file runeape_style.hpp

/**
 * Copyright (c) 2020 Sri Lakshmi Kanthan P
 * 
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
 **/

#ifndef RUNEAPE_STYLE
#define RUNEAPE_STYLE

#include "algorithm"
#include "exception"
#include "runeape_config.hpp"

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
         * @struct  basic_runeape_base_style
         * @brief   abstract class for style types used by runeape
         *          class
         * @tparam  Runeapeconfig type of runeape_config
         **/
        template <typename Runeapeconfig>
        struct basic_runeape_base_style
        {
            using runeape_config = Runeapeconfig;

            basic_runeape_base_style()                                       = default;
            basic_runeape_base_style( const basic_runeape_base_style & )     = default;
            basic_runeape_base_style( basic_runeape_base_style && ) noexcept = default;
            virtual ~basic_runeape_base_style()                              = default;

            basic_runeape_base_style &operator=( const basic_runeape_base_style & ) = default;
            basic_runeape_base_style &operator=( basic_runeape_base_style && ) noexcept = default;

            /**
             * @brief clears the contents
             **/
            virtual void clear() = 0;

            /**
             * @brief  used to set runeape_config, call this before 
             *         any other operation.
             * @param  config runeape_config
             **/
            virtual void set_config( const runeape_config &config ) = 0;

            /**
             * @brief  used to get runeape_image asper the style
             * @param  rimgs vector of runeape_image
             * @return runeape_image
             **/
            virtual typename runeape_config::runeape_image
            operator()( const typename runeape_config::template vector_type<
                        typename runeape_config::runeape_image> &rimgs ) = 0;
        };

        /**
         * @class  basic_runeape_untouched_style
         * @brief  untouched style for runeape class
         * @tparam Runeapeconfig type of runeape_config
         **/
        template <typename Runeapeconfig>
        class basic_runeape_untouched_style : public basic_runeape_base_style<Runeapeconfig>
        {
           protected:
            using base = basic_runeape_base_style<Runeapeconfig>;

           public:
            using runeape_config = Runeapeconfig;

           private:
            using char_type     = typename runeape_config::char_type;
            using size_type     = typename runeape_config::size_type;
            using string_type   = typename runeape_config::string_type;
            using shrink_type   = typename runeape_config::shrink;
            using runeape_image = typename runeape_config::runeape_image;
            template <typename T>
            using vector_type = typename runeape_config::template vector_type<T>;

           public:
            /**
             * @brief shrink level of this style is level_0
             **/
            static constexpr shrink_type shrink_level = shrink_type::level_0;

           private:
            /**
             * @brief stores runeape_config
             **/
            runeape_config config;

            /**
             * @brief converts ascii text of std::string to
             *        string_type
             **/
            static string_type cvt( const std::string &str )
            {
                return string_type( str.begin(), str.end() );
            }

            /**
             * @brief checks Height equal or not
             * @param img runeape_image
             **/
            void error_check( const runeape_image &img ) const
            {
                if ( img.size() != this->config.Height )
                {
                    throw std::runtime_error( "Height should be equal" );
                }
            }

            /**
             * @brief removes HardBlank
             * @param rimg runeape_image
             **/
            void remove_hardblank( runeape_image &rimg )
            {
                for ( size_type i = 0; i < this->config.Height; i++ )
                {
                    std::replace( rimg[i].begin(), rimg[i].end(), this->config.HardBlank, ' ' );
                }
            }

           public:
            basic_runeape_untouched_style()                                            = default;
            basic_runeape_untouched_style( const basic_runeape_untouched_style & )     = default;
            basic_runeape_untouched_style( basic_runeape_untouched_style && ) noexcept = default;
            virtual ~basic_runeape_untouched_style()                                   = default;

            basic_runeape_untouched_style &operator=( const basic_runeape_untouched_style & ) = default;
            basic_runeape_untouched_style &operator=( basic_runeape_untouched_style && ) noexcept = default;

            /**
             * @brief clears the content
             **/
            void clear() override
            {
                this->config.clear();
            }

            /**
             * @brief swaps object
             * @param obj object to swap
             **/
            void swap( basic_runeape_untouched_style &obj )
            {
                using std::swap;
                swap( this->config, obj.config );
            }

            /**
             * @brief sets config
             * @param config runeapeconfig
             **/
            void set_config( const runeape_config &config ) override
            {
                this->config = config;
            }

            /**
             * @brief  used to get runeape_image asper the style
             * @param  rimgs vector of runeape_image
             * @return runeape_image
             **/
            runeape_image operator()( const vector_type<runeape_image> &rimgs ) override
            {
                runeape_image rimg( this->config.Height, string_type() );

                for ( const auto &ri : rimgs )
                {
                    this->error_check( ri );
                }

                for ( size_type i = 0; i < this->config.Height; i++ )
                {
                    for ( const auto &ri : rimgs )
                    {
                        rimg[i] += ri[i];
                    }
                }

                remove_hardblank( rimg );

                return rimg;
            }
        };

        /**
         * @brief swap two objects
         * @param lhs object one to swap
         * @param rhs object two to swap
         **/
        template <typename Runeapeconfig>
        void swap( basic_runeape_untouched_style<Runeapeconfig> &lhs,
                   basic_runeape_untouched_style<Runeapeconfig> &rhs )
        {
            lhs.swap( rhs );
        }

        /**
         * @class  basic_runeape_kerning_style
         * @brief  Kerning style for runeape class
         * @tparam kerning space
         * @tparam Runeapeconfig type of runeape_config
         **/
        template <unsigned int Kerning, typename Runeapeconfig>
        class basic_runeape_kerning_style : public basic_runeape_base_style<Runeapeconfig>
        {
           protected:
            using base = basic_runeape_base_style<Runeapeconfig>;

           public:
            using runeape_config = Runeapeconfig;

           private:
            using char_type     = typename runeape_config::char_type;
            using size_type     = typename runeape_config::size_type;
            using string_type   = typename runeape_config::string_type;
            using shrink_type   = typename runeape_config::shrink;
            using runeape_image = typename runeape_config::runeape_image;
            template <typename T>
            using vector_type = typename runeape_config::template vector_type<T>;

           public:
            /**
             * @brief shrink level of this style is level_1
             **/
            static constexpr shrink_type shrink_level = shrink_type::level_1;

           private:
            runeape_config     config;
            const unsigned int kerning_space = Kerning;
            char_type          null { '\0' };

            /**
             * @brief converts ascii text of std::string to
             *        string_type
             **/
            static string_type cvt( const std::string &str )
            {
                return string_type( str.begin(), str.end() );
            }

            /**
             * @brief checks Height equal or not
             * @param img runeape_image
             **/
            void error_check( const runeape_image &img ) const
            {
                if ( img.size() != this->config.Height )
                {
                    throw std::runtime_error( "Height should be equal" );
                }
            }

            /**
             * @brief removes HardBlank
             * @param rimg runeape_image
             **/
            void remove_hardblank( runeape_image &rimg )
            {
                for ( size_type i = 0; i < this->config.Height; i++ )
                {
                    std::replace( rimg[i].begin(), rimg[i].end(), this->config.HardBlank, ' ' );
                }
            }

            /**
             * @brief add null to last non white space char of 
             *        runeape_image
             * @param img runeape_image
             **/
            void append_null( runeape_image &img )
            {
                for ( size_type i = 0; i < config.Height; i++ )
                {
                    size_type p = img[i].find_last_not_of( ' ' );

                    if ( p == string_type::npos )
                    {
                        img[i] = string_type( 1, null ) + img[i];
                    }
                    else
                    {
                        img[i].insert( p + 1, 1, null );
                    }
                }
            }

            /**
             * @brief appends runeape_image
             * @param img1 runeape_image
             * @param img2 runeape_image
             **/
            void append_img( runeape_image &img1, const runeape_image &img2 )
            {
                for ( size_type i = 0; i < config.Height; i++ )
                {
                    img1[i] += img2[i];
                }
            }

            /**
             * @brief finds minspace between null
             *        and non whitespace
             * @param img runeape_image
             **/
            size_type minspace( runeape_image &img )
            {
                vector_type<size_type> nos( this->config.Height, 0 );

                for ( size_type i = 0; i < this->config.Height; i++ )
                {
                    size_type p = img[i].find_first_of( null );

                    while ( ( ++p < img[i].size() ) && ( img[i][p] == ' ' ) )
                    {
                        ++nos[i];
                    }
                }

                return *std::min_element( nos.begin(), nos.end() );
            }

            /**
             * @brief deos the kerning process
             * @param img runeape_image 
             * @param minspace minspace
             **/
            void kerning_process( runeape_image &img, size_type minspace )
            {
                if ( minspace == this->kerning_space )
                {
                    for ( size_type i = 0; i < this->config.Height; i++ )
                    {
                        size_type p = img[i].find_first_of( null );
                        img[i].erase( p, 1 );
                    }
                }
                else if ( minspace > kerning_space )
                {
                    size_type witdh = minspace - kerning_space;
                    for ( size_type i = 0; i < this->config.Height; i++ )
                    {
                        size_type p = img[i].find_first_of( null );
                        img[i].erase( p, ( witdh + 1 ) );
                    }
                }
                else
                {
                    size_type witdh = kerning_space - minspace;
                    for ( size_type i = 0; i < this->config.Height; i++ )
                    {
                        size_type p = img[i].find_first_of( null );
                        img[i].erase( p, 1 );
                        img[i].insert( p, witdh, ' ' );
                    }
                }
            }

            /**
             * @brief does kening in runeape_image and runeape_image
             * @param img1 runeape_image
             * @param img2 runeape_image
             **/
            void kerning( runeape_image &img1, const runeape_image &img2 )
            {
                append_null( img1 );
                append_img( img1, img2 );
                kerning_process( img1, minspace( img1 ) );
            }

           public:
            basic_runeape_kerning_style()                                          = default;
            basic_runeape_kerning_style( const basic_runeape_kerning_style & )     = default;
            basic_runeape_kerning_style( basic_runeape_kerning_style && ) noexcept = default;
            virtual ~basic_runeape_kerning_style()                                 = default;

            basic_runeape_kerning_style &operator=( const basic_runeape_kerning_style & ) = default;
            basic_runeape_kerning_style &operator=( basic_runeape_kerning_style && ) noexcept = default;

            /**
             * @brief clears the content
             **/
            void clear() override
            {
                this->config.clear();
            }

            /**
             * @brief swaps object
             * @param obj object to swap
             **/
            void swap( basic_runeape_kerning_style &obj )
            {
                using std::swap;
                swap( this->config, obj.config );
            }

            /**
             * @brief sets config
             * @param config runeapeconfig
             **/
            void set_config( const runeape_config &config ) override
            {
                this->config = config;
            }

            /**
             * @brief  used to get runeape_image asper the style
             * @param  rimgs vector of runeape_image
             * @return runeape_image
             **/
            runeape_image operator()( const vector_type<runeape_image> &rimgs ) override
            {
                runeape_image rimg( this->config.Height, string_type() );

                for ( const auto &ri : rimgs )
                {
                    this->error_check( ri );
                }

                for ( const auto &ri : rimgs )
                {
                    kerning( rimg, ri );
                }

                remove_hardblank( rimg );

                return rimg;
            }
        };

        /**
         * @brief swap two objects
         * @param lhs object one to swap
         * @param rhs object two to swap
         **/
        template <unsigned int Kerning, typename Runeapeconfig>
        void swap( basic_runeape_kerning_style<Kerning, Runeapeconfig> &lhs,
                   basic_runeape_kerning_style<Kerning, Runeapeconfig> &rhs )
        {
            lhs.swap( rhs );
        }
    } // namespace art

} // namespace srilakshmikanthanp

#endif