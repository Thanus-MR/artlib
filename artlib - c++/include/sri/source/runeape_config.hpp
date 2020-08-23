/// @file runepe_config.hpp

/**
 * Copyright (c) 2020 Sri Lakshmi Kanthan P
 * 
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
 **/

#ifndef RUNEAPE_CONFIG
#define RUNEAPE_CONFIG

#include "memory"
#include "ostream"
#include "string"
#include "strvec.hpp"
#include "type_traits"
#include "vector"

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
         * @class  runeape_config
         * @brief  this class contains most of alias and runeape_config
         * @tparam CharT, char_type
         * @tparam SizeT, size_type
         * @tparam Traits, traits_type, defaults to std::char_traits<CharT>
         **/
        template <typename CharT,
                  typename SizeT                     = size_t,
                  typename Traits                    = std::char_traits<CharT>,
                  template <typename> typename Alloc = std::allocator>
        struct runeape_config
        {
            using char_type   = CharT;
            using size_type   = SizeT;
            using traits_type = Traits;
            template <typename T>
            using alloc_type  = Alloc<T>;
            using string_type = std::basic_string<CharT, Traits, Alloc<CharT>>;
            template <typename T>
            using vector_type = std::vector<T, Alloc<T>>;

            /**
             * @struct runeape_image
             * @brief  runeape image type
             **/
            struct runeape_image : artlib_data<string_type, alloc_type>
            {
                using base = artlib_data<string_type, alloc_type>;
                using base::base;
            };

            /**
             * @brief shrink level
             * 
             * level_0 can be use style untouched
             * 
             * level_1 can be use style untouched, fitted
             **/
            enum class shrink
            {
                level_0 = 0,
                level_1 = 1
            };

            /**
             * @brief Holds Hardblank of gallery
             **/
            char_type HardBlank;
            /**
             * @brief Holds Height of font
             **/
            size_type Height;
            /**
             * @brief stores shrink level
             *        see @ref shrink
             **/
            shrink Shrink;

            runeape_config()                             = default;
            runeape_config( const runeape_config & )     = default;
            runeape_config( runeape_config && ) noexcept = default;
            ~runeape_config()                            = default;

            runeape_config &operator=( const runeape_config & ) = default;
            runeape_config &operator=( runeape_config && ) noexcept = default;

            /**
             * @brief clears the configuraton,
             *        sets HardBlank to 0,
             *        Height to 0,
             *        Shrink to level_0
             **/
            void clear()
            {
                this->HardBlank = 0;
                this->Height    = 0;
                this->Shrink    = shrink::level_0;
            }

            /**
             * @brief swaps two objects
             * @param obj object to swap
             **/
            void swap( runeape_config &obj )
            {
                using std::swap;
                swap( this->HardBlank, obj.HardBlank );
                swap( this->Height, obj.Height );
                swap( this->Shrink, obj.Shrink );
            }

            /**
             * @brief prints runeape_image to stream
             * @param stream outputstream
             * @param ri  runeape_image object
             * @return reference to stream
             **/
            friend std::basic_ostream<CharT, Traits> &
            operator<<( std::basic_ostream<CharT, Traits> &stream,
                        const runeape_image &              ri )
            {
                stream << std::endl;
                for ( const auto &str : ri )
                {
                    stream << str << std::endl;
                }
                return stream;
            }
        };

        /**
         * @brief swap two runeape_config
         * @param lhs object one to swap
         * @param rhs object two to swap
         **/
        template <typename CharT, typename SizeT, typename Traits,
                  template <typename> typename Alloc>
        void swap( runeape_config<CharT, SizeT, Traits, Alloc> &lhs,
                   runeape_config<CharT, SizeT, Traits, Alloc> &rhs )
        {
            lhs.swap( rhs );
        }

    } // namespace art

} // namespace sri

#endif