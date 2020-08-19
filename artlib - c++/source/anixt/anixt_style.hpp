///@file basic_style.hpp

/** 
 * Copyright (c) 2020 Sri Lakshmi Kanthan P
 * 
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
 */

#ifndef BASIC_STYLE_HEADER
#define BASIC_STYLE_HEADER

#include "anixt_config.hpp"

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
         * @struct  basic_anixt_base_style
         * @brief   abstract class for style types used by anixt
         *          class
         * @tparam  Anixtconfig type of anixt_config
         **/
        template <typename Anixtconfig>
        struct basic_anixt_base_style
        {
            using anixt_config = Anixtconfig;

            basic_anixt_base_style()                                     = default;
            basic_anixt_base_style( const basic_anixt_base_style & )     = default;
            basic_anixt_base_style( basic_anixt_base_style && ) noexcept = default;
            virtual ~basic_anixt_base_style()                            = default;

            basic_anixt_base_style &operator=( const basic_anixt_base_style & ) = default;
            basic_anixt_base_style &operator=( basic_anixt_base_style && ) noexcept = default;

            /**
             * @brief clears the contents
             **/
            virtual void clear() = 0;

            /**
             * @brief  used to set anixt config, call this before 
             *         any other operation.
             * @param  config anixt_config
             **/
            virtual void set_config( const anixt_config &config ) = 0;

            /**
             * @brief  used to get anixt_string asper the style
             * @param  anixtletters vector of anixt_letters
             * @return anixt_string
             **/
            virtual typename anixt_config::anixt_string
            operator()( const typename anixt_config::template vector_type<
                        typename anixt_config::anixt_letter>
                            &anixtletters ) = 0;
        };

        /**
         * @class  basic_anixt_untouched_style
         * @brief  untouched style for anixt class
         * @tparam Anixtconfig anixt_config
         **/
        template <typename Anixtconfig>
        class basic_anixt_untouched_style : public basic_anixt_base_style<Anixtconfig>
        {
           protected:
            using base = basic_anixt_base_style<Anixtconfig>;

           public:
            using anixt_config = typename base::anixt_config;

           private:
            using char_type    = typename base::anixt_config::char_type;
            using size_type    = typename base::anixt_config::size_type;
            using string_type  = typename base::anixt_config::string_type;
            using shrink_type  = typename base::anixt_config::shrink;
            using anixt_letter = typename base::anixt_config::anixt_letter;
            using anixt_string = typename base::anixt_config::anixt_string;
            template <typename T>
            using vector_type = typename base::anixt_config::template vector_type<T>;

           public:
            /**
             * shrink level use by the style is level_0
             **/
            static constexpr shrink_type shrink_level = shrink_type::level_0;

           private:
            anixt_config config;

            /**
             * @brief converts ascii character of std::string
             *        to anixt_config::string_type
             **/
            static string_type cvt( const std::string &str )
            {
                return string_type( str.begin(), str.end() );
            }

            /**
             * @brief checks the height are equal
             * @param anixtletter obj of anixt_letter
             **/
            void error_check( const anixt_letter &anixtletter ) const
            {
                if ( anixtletter.size() != this->config.Height )
                {
                    throw std::runtime_error( "Height is not equal" );
                }
            }

            /**
             * @brief removes Hardblank
             * @param as obj of anixt_string
             **/
            void remove_hardblank( anixt_string &as ) const
            {
                for ( size_type i = 0; i < config.Height; i++ )
                {
                    std::replace( as[i].begin(), as[i].end(), this->config.HardBlank, ' ' );
                }
            }

           public:
            basic_anixt_untouched_style()                                          = default;
            basic_anixt_untouched_style( const basic_anixt_untouched_style & )     = default;
            basic_anixt_untouched_style( basic_anixt_untouched_style && ) noexcept = default;
            virtual ~basic_anixt_untouched_style()                                 = default;

            basic_anixt_untouched_style &operator=( const basic_anixt_untouched_style & ) = default;
            basic_anixt_untouched_style &operator=( basic_anixt_untouched_style && ) noexcept = default;

            /**
             * @brief clears the contents
             **/
            void clear() noexcept override
            {
                this->config.clear();
            }

            /**
             * @brief swap two anixt_config
             * @param obj object to swap
             **/
            void swap( basic_anixt_untouched_style &obj ) noexcept
            {
                using std::swap;
                swap( this->config, obj.config );
            }

            /**
             * @brief  used to set anixt config, call this before 
             *         other operation.
             * @param  config anixt_config
             **/
            void set_config( const anixt_config &config ) noexcept override
            {
                this->config = config;
            }

            /**
             * @brief  used to get anixt_string in untouched style
             * @param  anixtletters vector of anixt_letters
             * @return anixt_string
             **/
            anixt_string operator()( const vector_type<anixt_letter> &anixtletters ) override
            {
                anixt_string as( this->config.Height, cvt( "" ) );

                for ( const auto &al : anixtletters )
                {
                    error_check( al );
                }

                for ( size_type i = 0; i < this->config.Height; i++ )
                {
                    for ( const auto &al : anixtletters )
                    {
                        as[i] += al[i];
                    }
                }

                remove_hardblank( as );

                return as;
            }
        };

        /**
         * @brief swap two basic_anixt_untouched_style
         * @param lhs object one to swap
         * @param rhs object two to swap
         **/
        template <typename Anixtconfig>
        void swap( basic_anixt_untouched_style<Anixtconfig> &lhs,
                   basic_anixt_untouched_style<Anixtconfig> &rhs ) noexcept
        {
            lhs.swap( rhs );
        }

        /**
         * @class  basic_anixt_kerning_style
         * @brief  fitted style for anixt
         * @tparam Kerning space
         * @tparam Anixtconfig type of anixt_config
         **/
        template <unsigned int Kerning, typename Anixtconfig>
        class basic_anixt_kerning_style : public basic_anixt_base_style<Anixtconfig>
        {
           protected:
            using base = basic_anixt_base_style<Anixtconfig>;

           public:
            using anixt_config = typename base::anixt_config;

           private:
            using char_type    = typename base::anixt_config::char_type;
            using size_type    = typename base::anixt_config::size_type;
            using string_type  = typename base::anixt_config::string_type;
            using shrink_type  = typename base::anixt_config::shrink;
            using anixt_letter = typename base::anixt_config::anixt_letter;
            using anixt_string = typename base::anixt_config::anixt_string;
            template <typename T>
            using vector_type = typename base::anixt_config::template vector_type<T>;

           public:
            /**
             * shrink level use by the style is level_1
             **/
            static constexpr shrink_type shrink_level = shrink_type::level_1;

           private:
            const char_type null { '\0' };
            const unsigned int kerning_space = Kerning;
            anixt_config    config;

            /**
             * @brief converts ascii character of std::string
             *        to anixt_config::string_type
             **/
            static string_type cvt( const std::string &str )
            {
                return string_type( str.begin(), str.end() );
            }

            /**
             * @brief checks the height are equal
             * @param anixtletter obj of anixt_letter
             **/
            void error_check( const anixt_letter &anixtletter ) const
            {
                if ( anixtletter.size() != this->config.Height )
                {
                    throw std::runtime_error( "Height is not equal" );
                }
            }

            /**
             * @brief removes Hardblank
             * @param as obj of anixt_string
             **/
            void remove_hardblank( anixt_string &as ) const
            {
                for ( size_type i = 0; i < config.Height; i++ )
                {
                    std::replace( as[i].begin(), as[i].end(), this->config.HardBlank, ' ' );
                }
            }

            /**
             * @brief add null to last non white space char of 
             *        anixt_string
             * @param as anixt_string
             **/
            void append_null_to_anixt_string( anixt_string &as )
            {
                for ( size_type i = 0; i < config.Height; i++ )
                {
                    size_type p = as[i].find_last_not_of( ' ' );

                    if ( p == string_type::npos )
                    {
                        as[i] = string_type( 1, null ) + as[i];
                    }
                    else
                    {
                        as[i].insert( p + 1, 1, null );
                    }
                }
            }

            /**
             * @brief appends anixt_letter to anixt_string
             * @param as anixt_string
             * @param al anixt_letter
             **/
            void append_anixt_letter( anixt_string &as, anixt_letter al )
            {
                for ( size_type i = 0; i < config.Height; i++ )
                {
                    as[i] += al[i];
                }
            }

            /**
             * @brief finds minspace between null
             *        and non whitespace
             * @param as anixt_string
             **/
            size_type minspace( anixt_string &as )
            {
                vector_type<size_type> nos( this->config.Height, 0 );

                for ( size_type i = 0; i < this->config.Height; i++ )
                {
                    size_type p = as[i].find_first_of( null );

                    while ( ( ++p < as[i].size() ) && ( as[i][p] == ' ' ) )
                    {
                        ++nos[i];
                    }
                }

                return *std::min_element( nos.begin(), nos.end() );
            }

            /**
             * @brief does the kerning process
             * @param as anixt_string 
             * @param ms minspace
             **/
            void kerning_process( anixt_string &as, size_type ms )
            {
                if ( minspace == this->kerning_space )
                {
                    for ( size_type i = 0; i < this->config.Height; i++ )
                    {
                        size_type p = as[i].find_first_of( null );
                        as[i].erase( p, 1 );
                    }
                }
                else if ( minspace > kerning_space )
                {
                    size_type witdh = minspace - kerning_space;
                    for ( size_type i = 0; i < this->config.Height; i++ )
                    {
                        size_type p = as[i].find_first_of( null );
                        as[i].erase( p, ( witdh + 1 ) );
                    }
                }
                else
                {
                    size_type witdh = kerning_space - minspace;
                    for ( size_type i = 0; i < this->config.Height; i++ )
                    {
                        size_type p = as[i].find_first_of( null );
                        as[i].erase( p, 1 );
                        as[i].insert( p, witdh, ' ' );
                    }
                }
            }

            /**
             * @brief does kening in anixt string and anixt letter
             * @param as anixt_string
             * @param al anixt_letter
             **/
            void fit_anixt_string_and_anixt_letter( anixt_string &as, anixt_letter al )
            {
                append_null_to_anixt_string( as );
                append_anixt_letter( as, al );
                kerning_process( as, minspace( as ) );
            }

           public:
            basic_anixt_kerning_style()                                       = default;
            basic_anixt_kerning_style( const basic_anixt_kerning_style & )     = default;
            basic_anixt_kerning_style( basic_anixt_kerning_style && ) noexcept = default;
            virtual ~basic_anixt_kerning_style()                              = default;

            basic_anixt_kerning_style &operator=( const basic_anixt_kerning_style & ) = default;
            basic_anixt_kerning_style &operator=( basic_anixt_kerning_style && ) noexcept = default;

            /**
             * @brief clears the contents
             **/
            void clear() noexcept override
            {
                this->config.clear();
            }

            /**
             * @brief swap two anixt_config
             * @param obj object to swap
             **/
            void swap( basic_anixt_kerning_style &obj ) noexcept
            {
                using std::swap;
                swap( this->config, obj.config );
            }

            /**
             * @brief  used to set anixt config, call this before 
             *         other operation.
             * @param  config anixt_config
             **/
            void set_config( const anixt_config &config ) noexcept override
            {
                this->config = config;
            }

            /**
             * @brief  used to get anixt_string in the fitted style
             * @param  anixtletters vector of anixt_letters
             * @return anixt_string
             **/
            anixt_string operator()( const vector_type<anixt_letter> &anixtletters ) override
            {
                anixt_string as( this->config.Height, cvt( "" ) );

                for ( const auto &al : anixtletters )
                {
                    error_check( al );
                }

                for ( const auto &al : anixtletters )
                {
                    fit_anixt_string_and_anixt_letter( as, al );
                }

                remove_hardblank( as );

                return as;
            }
        };

        /**
         * @brief swap two basic_anixt_kerning_style
         * @param lhs object one to swap
         * @param rhs object two to swap
         **/
        template <unsigned int Kerning, typename Anixtconfig>
        void swap( basic_anixt_kerning_style<Kerning, Anixtconfig> &lhs,
                   basic_anixt_kerning_style<Kerning, Anixtconfig> &rhs ) noexcept
        {
            lhs.swap( rhs );
        }

        /**
         * @class  basic_anixt_smushed_style
         * @brief  smushed style for anixt
         * @tparam Anixtconfig type of anixt_config
         **/
        template <typename Anixtconfig>
        class basic_anixt_smushed_style : public basic_anixt_base_style<Anixtconfig>
        {
           protected:
            using base = basic_anixt_base_style<Anixtconfig>;

           public:
            using anixt_config = typename base::anixt_config;

           private:
            using char_type    = typename base::anixt_config::char_type;
            using size_type    = typename base::anixt_config::size_type;
            using string_type  = typename base::anixt_config::string_type;
            using shrink_type  = typename base::anixt_config::shrink;
            using anixt_letter = typename base::anixt_config::anixt_letter;
            using anixt_string = typename base::anixt_config::anixt_string;
            template <typename T>
            using vector_type = typename base::anixt_config::template vector_type<T>;

           public:
            /**
             * shrink level use by the style is level_2
             **/
            static constexpr shrink_type shrink_level = shrink_type::level_2;

           private:
            const char_type null { '0' };
            anixt_config    config;

            /**
             * @brief converts ascii character of std::string
             *        to anixt_config::string_type
             **/
            static string_type cvt( const std::string &str )
            {
                return string_type( str.begin(), str.end() );
            }

            /**
             * @brief checks the height are equal
             * @param anixtletter obj of anixt_letter
             **/
            void error_check( const anixt_letter &anixtletter ) const
            {
                if ( anixtletter.size() != this->config.Height )
                {
                    throw std::runtime_error( "Height is not equal" );
                }
            }

            /**
             * @brief removes Hardblank
             * @param as obj of anixt_string
             **/
            void remove_hardblank( anixt_string &as ) const
            {
                for ( size_type i = 0; i < config.Height; i++ )
                {
                    std::replace( as[i].begin(), as[i].end(), this->config.HardBlank, ' ' );
                }
            }

            /**
             * @brief smush rules
             * @param lc left character
             * @param rc right character
             * @return smushed character
             **/
            char_type smush_rules( char_type lc, char_type rc )
            {
                //()
                if ( lc == ' ' )
                {
                    return rc;
                }

                if ( rc == ' ' )
                {
                    return lc;
                }

                //(Equal character smush )
                if ( lc == rc )
                {
                    return rc;
                }

                //(Underscores smush)
                if ( lc == '_' &&
                     cvt( "|/\\[]{}()<>" ).find( rc ) != string_type::npos )
                {
                    return rc;
                }

                if ( rc == '_' &&
                     cvt( "|/\\[]{}()<>" ).find( lc ) != string_type::npos )
                {
                    return lc;
                }

                //(Hierarchy Smushing)
                auto find_class = []( char_type ch ) -> size_type {
                    if ( ch == '|' )
                    {
                        return 1;
                    }

                    if ( ch == '/' || ch == '\\' )
                    {
                        return 3;
                    }

                    if ( ch == '[' || ch == ']' )
                    {
                        return 4;
                    }

                    if ( ch == '{' || ch == '}' )
                    {
                        return 5;
                    }

                    if ( ch == '(' || ch == ')' )
                    {
                        return 6;
                    }

                    return 0;
                };

                size_type c_lc = find_class( lc );
                size_type c_rc = find_class( rc );

                if ( c_lc > c_rc )
                {
                    return lc;
                }

                if ( c_rc > c_lc )
                {
                    return rc;
                }

                //(Opposite smush)
                if ( lc == '[' && rc == ']' )
                {
                    return '|';
                }

                if ( lc == ']' && rc == '[' )
                {
                    return '|';
                }

                if ( lc == '{' && rc == '}' )
                {
                    return '|';
                }

                if ( lc == '}' && rc == '{' )
                {
                    return '|';
                }

                if ( lc == '(' && rc == ')' )
                {
                    return '|';
                }

                if ( lc == ')' && rc == '(' )
                {
                    return '|';
                }

                //(Big X smush)
                if ( lc == '/' && rc == '\\' )
                {
                    return '|';
                }

                if ( lc == '\\' && rc == '/' )
                {
                    return 'Y';
                }

                if ( lc == '>' && rc == '<' )
                {
                    return 'X';
                }

                //(universel smush)
                return lc;
            }

            /**
             * @brief add null to last non white space of 
             *        anixt_string
             * @param as anixt_string
             **/
            void append_null_to_anixt_string( anixt_string &as )
            {
                for ( size_type i = 0; i < config.Height; i++ )
                {
                    size_type p = as[i].find_last_not_of( ' ' );

                    if ( p == string_type::npos )
                    {
                        as[i] = string_type( 1, null ) + as[i];
                    }
                    else
                    {
                        as[i].insert( p + 1, 1, null );
                    }
                }
            }

            /**
             * @brief add null to anixt_letter after first non
             *        whitespace
             * @param al anixt_letter
             **/
            void append_null_to_anixt_letter( anixt_letter &al )
            {
                for ( size_type i = 0; i < this->config.Height; i++ )
                {
                    size_type p = al[i].find_first_not_of( ' ' );

                    if ( p == string_type::npos )
                    {
                        al[i] = al[i] + string_type( 1, '0' );
                    }
                    else
                    {
                        al[i].insert( p + 1, 1, '0' );
                    }
                }
            }

            /**
             * @brief appends anixt_letter to anixt_string
             * @param as anixt_string
             * @param al anixt_letter
             **/
            void append_anixt_letter( anixt_string &as, anixt_letter al )
            {
                for ( size_type i = 0; i < config.Height; i++ )
                {
                    as[i] += al[i];
                }
            }

            /**
             * @brief finds minspace between null
             *        and non whitespace
             * @param as anixt_string
             **/
            size_type minspace( anixt_string &as )
            {
                vector_type<size_type> nos( this->config.Height, 0 );

                for ( size_type i = 0; i < this->config.Height; i++ )
                {
                    size_type p = as[i].find_first_of( null );

                    while ( ( ++p < as[i].size() ) && ( as[i][p] == ' ' ) )
                    {
                        ++nos[i];
                    }
                }

                return *std::min_element( nos.begin(), nos.end() );
            }

            /**
             * @brief removes minspace and null
             * @param as anixt_string 
             * @param ms minspace
             **/
            void remove_null_and_minspace( anixt_string &as, size_type ms )
            {
                for ( size_type i = 0; i < this->config.Height; i++ )
                {
                    size_type p = as[i].find_first_of( null );
                    as[i].erase( p, ( ms + 1 ) );
                }
            }

            /**
             * @brief do's the smushing work
             **/
            void do_smushing_work_in_anixt_string( anixt_string &as )
            {
                vector_type<std::pair<size_type, size_type>> cp;

                for ( size_type i = 0; i < this->config.Height; i++ )
                {
                    std::pair<size_type, size_type> charpos;
                    size_type                       nullpos;
                    nullpos        = as[i].find_last_of( null );
                    charpos.first  = nullpos - 2;
                    charpos.second = nullpos - 1;
                    as[i].erase( nullpos, 1 );
                    cp.push_back( charpos );
                }

                for ( size_type i = 0; i < this->config.Height; i++ )
                {
                    try
                    {
                        char_type hb = this->config.HardBlank;
                        char_type lc = as[i].at( cp[i].first );
                        char_type rc = as[i].at( cp[i].second );

                        if ( ( lc == hb || rc == hb ) && ( lc != rc ) )
                        {
                            throw "";
                        }
                    }
                    catch ( ... )
                    {
                        return;
                    }
                }

                for ( size_type i = 0; i < this->config.Height; i++ )
                {
                    char_type lc = as[i][cp[i].first];
                    char_type rc = as[i][cp[i].second];
                    char_type sm = smush_rules( lc, rc );
                    as[i].erase( cp[i].first, 2 );
                    as[i].insert( cp[i].first, 1, sm );
                }
            }

            /**
             * @brief smush anixt string and anixt letter
             * @param as anixt_string
             * @param al anixt_letter
             **/
            void smush_anixt_string_and_anixt_letter( anixt_string &as, anixt_letter al )
            {
                append_null_to_anixt_string( as );
                append_null_to_anixt_letter( al );
                append_anixt_letter( as, al );
                remove_null_and_minspace( as, minspace( as ) );
                do_smushing_work_in_anixt_string( as );
            }

           public:
            basic_anixt_smushed_style()                                        = default;
            basic_anixt_smushed_style( const basic_anixt_smushed_style & )     = default;
            basic_anixt_smushed_style( basic_anixt_smushed_style && ) noexcept = default;
            virtual ~basic_anixt_smushed_style()                               = default;

            basic_anixt_smushed_style &operator=( const basic_anixt_smushed_style & ) = default;
            basic_anixt_smushed_style &operator=( basic_anixt_smushed_style && ) noexcept = default;

            /**
             * @brief clears the contents
             **/
            void clear() noexcept override
            {
                this->config.clear();
            }

            /**
             * @brief swap two object
             * @param obj object to swap
             **/
            void swap( basic_anixt_smushed_style &obj ) noexcept
            {
                using std::swap;
                swap( this->config, obj.config );
            }

            /**
             * @brief  used to set anixt config
             * @param  config anixt_config
             **/
            void set_config( const anixt_config &config ) noexcept override
            {
                this->config = config;
            }

            /**
             * @brief  used to get anixt_string in the smushed style
             * @param  anixtletters vector of anixt_letters
             * @return anixt_string
             **/
            anixt_string operator()( const vector_type<anixt_letter> &anixtletters ) override
            {
                anixt_string as( this->config.Height, cvt( "" ) );

                for ( const auto &al : anixtletters )
                {
                    error_check( al );
                }

                for ( const auto &al : anixtletters )
                {
                    smush_anixt_string_and_anixt_letter( as, al );
                }

                remove_hardblank( as );

                return as;
            }
        };

        /**
         * @brief swap two basic_anixt_smushed_style
         * @param lhs object one to swap
         * @param rhs object two to swap
         **/
        template <typename Anixtconfig>
        void swap( basic_anixt_smushed_style<Anixtconfig> &lhs,
                   basic_anixt_smushed_style<Anixtconfig> &rhs ) noexcept
        {
            lhs.swap( rhs );
        }

    } // namespace art

} // namespace sri

#endif