/**
 * Copyright (c) 2020 Sri Lakshmi Kanthan P
 * 
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
 */

#include "artlib.hpp"
#include "fstream"
#include "iostream"
#include "json.hpp"
#include "map"
#include "memory"
#include "string"
#include "type_traits"
#include "vector"

namespace srilakshmikanthanp
{
    namespace art
    {
        /**
         * @struct fontcvt
         * @brief  obj struct contains font converter
         * @tparam CharT   char_type
         * @tparam Traits  traits_type, defaults to std::char_traits<CharT>
         * @tparam Alloc   alloc_type, defaults to std::allocator
         **/
        template <typename CharT,
                  typename Traits                    = std::char_traits<CharT>,
                  template <typename> typename Alloc = std::allocator>
        struct fontcvt
        {
            // clang-format off
            using char_type     =   CharT;
            using size_type     =   size_t;
            using traits_type   =   Traits;
            template <typename T>
            using alloc_type    =   Alloc<T>;
            using string_type   =   std::basic_string<CharT, Traits, Alloc<CharT>>;
            template <typename T>
            using vector_type   =   std::vector<T, Alloc<T>>;
            template <typename K, typename V>
            using map_type      =   std::map<K, V, std::less<K>, Alloc<std::pair<const K, V>>>;
            using json_type     =   nlohmann::basic_json<std::map, std::vector, string_type, bool,
                                                   int64_t, uint64_t, double, alloc_type>;
            using istream_type  =   std::basic_istream<CharT, Traits>;
            using ostream_type  =   std::basic_ostream<CharT, Traits>;
            // clang-format on

            /**
             * @class flglettoanixt
             * @brief converts figlet to anixt
             **/
            class figlettoanixt
            {
               private:
                map_type<char_type, vector_type<string_type>> flf_char {};
                json_type                                     json_font {};
                char_type                                     HardBlank { 0 };
                size_type                                     Height { 0 };
                size_type                                     Shrink { 0 };

               public:
                figlettoanixt()                        = default;
                figlettoanixt( const figlettoanixt & ) = default;
                figlettoanixt( figlettoanixt && )      = default;
                ~figlettoanixt()                       = default;

                figlettoanixt &operator=( const figlettoanixt & ) = default;
                figlettoanixt &operator=( figlettoanixt && ) = default;

                /**
                 * @brief  operator>> inputs from stream
                 * @param  stream stream
                 * @param  obj object
                 * @return reference to stream 
                 **/
                friend istream_type &operator>>( istream_type &stream, figlettoanixt &obj )
                {
                    obj.readconfigandskipcomment( stream );

                    for ( char_type ch = ' '; ch <= '~'; ch++ )
                    {
                        obj.flf_char[ch] = obj.nextcharacter( stream );
                    }

                    return stream;
                }

                /**
                 * @brief  updates json_font
                 * @return returns reference to *obj
                 **/
                figlettoanixt &update()
                {
                    this->json_font[cvt( "anixt_config" )][cvt( "Height" )]    = this->Height;
                    this->json_font[cvt( "anixt_config" )][cvt( "HardBlank" )] = this->HardBlank;
                    this->json_font[cvt( "anixt_config" )][cvt( "Shrink" )]    = this->Shrink;

                    for ( char_type ch = ' '; ch <= '~'; ch++ )
                    {
                        justify( this->flf_char[ch] );
                    }

                    for ( char_type ch = ' '; ch <= '~'; ch++ )
                    {
                        this->json_font[cvt( "anixt_letter" )][string_type( 1, ch )] = this->flf_char[ch];
                    }

                    return *this;
                }

                /**
                 * @brief operator<< outputs to stream
                 * @param stream stream
                 * @param obj object
                 * @return reference to stream
                 **/
                friend ostream_type &operator<<( ostream_type &stream, figlettoanixt &obj )
                {
                    stream << obj.json_font;
                    return stream;
                }

               private:
                /**
                 * @brief read config and skip comments in stream
                 * @param stream stream
                 **/
                void readconfigandskipcomment( istream_type &stream )
                {
                    string_type str {};
                    size_type   dummy { 0 };
                    size_type   cmnt { 0 };

                    stream >> str;

                    if ( str.substr( 0, 5 ) != cvt( "flf2a" ) )
                    {
                        throw std::runtime_error( "flf2a not found !" );
                    }

                    str.erase( 0, 5 );

                    this->HardBlank = str.at( 0 ); // HardBlank

                    stream >> this->Height; // Height

                    stream >> dummy;

                    stream >> dummy;

                    stream >> dummy;

                    stream >> cmnt; // comment line

                    std::getline( stream, str );

                    for ( size_type i = 0; i < cmnt; i++ )
                    {
                        std::getline( stream, str );
                    }
                }

                /**
                 * @brief  returns next character in stream
                 * @return FIGcharacter
                 **/
                vector_type<string_type> nextcharacter( istream_type &stream )
                {
                    vector_type<string_type> ret {};
                    string_type              str {};

                    for ( size_type i = 1; i <= this->Height; )
                    {
                        std::getline( stream, str );

                        if ( str.find_last_of( '@' ) != string_type::npos )
                        {
                            ret.push_back( str.substr( 0, str.find_last_of( '@' ) ) );

                            if ( i == this->Height )
                            {
                                ret.back().pop_back();
                            }

                            ++i;
                        }
                    }

                    return ret;
                }

                string_type cvt( const std::string &str )
                {
                    return string_type { str.begin(), str.end() };
                }

                void justify( vector_type<string_type> &svec )
                {
                    size_type max { 0 };

                    for ( const auto &i : svec )
                    {
                        if ( max < i.size() )
                        {
                            max = i.size();
                        }
                    }

                    for ( auto &i : svec )
                    {
                        if ( i.size() < max )
                        {
                            size_type difference = max - i.size();
                            i += string_type( difference, ' ' );
                        }
                    }
                }
            };
        };

    } // namespace art

} // namespace srilakshmikanthanp

using namespace srilakshmikanthanp::art;

int main()
{
    anixt<anixt_untouched_style> myanixt;
    std::ifstream                flf_font;
    fontcvt<char>::figlettoanixt cvt;
    std::ofstream                json_font;
    std::string                  path;

    std::cout << "Copyright (c) 2020 Sri Lakshmi Kanthan P\n"
              << "This software is released under the MIT License.\n"
              << "https://opensource.org/licenses/MIT\n";

    do
    {
        flf_font.clear();
        std::cout << "\nEnter FIGLET Font File Path : ";
        std::cin >> path;
        flf_font.open( path );
    } while ( !flf_font.is_open() );

    do
    {
        json_font.clear();
        std::cout << "\nEnter anixt Font File path  : ";
        std::cin >> path;
        json_font.open( path );

    } while ( !json_font.is_open() );

    flf_font >> cvt;
    cvt.update();
    json_font << cvt;

    flf_font.close();
    json_font.close();

    myanixt.set_font( path );
    
    myanixt( "Font Created" );

    std::cout << myanixt.get_anixt_string();

    myanixt("Don't Forget");

    std::cout << myanixt.get_anixt_string();

    myanixt("To Change");

    std::cout << myanixt.get_anixt_string();

    myanixt("Shrink value!");

    std::cout << myanixt.get_anixt_string();

    myanixt( "Enjoy" );

    std::cout << myanixt.get_anixt_string();

    return 0;
}