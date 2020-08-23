///@file anixt_config.hpp

/**
 * Copyright (c) 2020 Sri Lakshmi Kanthan P
 * 
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
 */

#ifndef ANIXTCONFIG_HEADER
#define ANIXTCONFIG_HEADER

#include "artlib_data.hpp"
#include "memory"
#include "ostream"
#include "string"
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
         * @class  anixt_config
         * @brief  This class contains most of alias and anixt configurations
         *         used by the anixt.
         * @tparam CharT  char_type
         * @tparam SizeT  size_type, defaults to size_t
         * @tparam Traits traits_type, defaults to std::char_traits<CharT>
         * @tparam Alloc  alloc_type, defaults to std::allocator
         **/
        template <typename CharT,
                  typename SizeT                     = size_t,
                  typename Traits                    = std::char_traits<CharT>,
                  template <typename> typename Alloc = std::allocator>
        struct anixt_config
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
             * @struct anixt_letter
             * @brief  anixt letter type
             **/
            struct anixt_letter : artlib_data<string_type, alloc_type>
            {
                using base = artlib_data<string_type, alloc_type>;
                using base::base;
            };

            /**
             * @struct anixt_string
             * @brief  anixt string type
             **/
            struct anixt_string : artlib_data<string_type, alloc_type>
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
             * 
             * level_2 can be use use style untouched, fitted, smushed
             **/
            enum class shrink : size_type
            {
                level_0 = 0,
                level_1 = 1,
                level_2 = 2
            };

            /**
             * @brief Holds Hardblank of font
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

            anixt_config()                           = default;
            anixt_config( const anixt_config & )     = default;
            anixt_config( anixt_config && ) noexcept = default;
            ~anixt_config()                          = default;

            anixt_config &operator=( const anixt_config & ) = default;
            anixt_config &operator=( anixt_config && ) noexcept = default;

            /**
             * @brief clears the configuraton,
             *        sets HardBlank to 0,
             *        Height to 0,
             *        Shrink to level_0
             **/
            void clear() noexcept
            {
                this->HardBlank = 0;
                this->Height    = 0;
                this->Shrink    = shrink::level_0;
            }

            /**
             * @brief swaps two anixt_config
             * @param obj object to swap
             **/
            void swap( anixt_config &obj ) noexcept
            {
                using std::swap;
                swap( this->HardBlank, obj.HardBlank );
                swap( this->Height, obj.Height );
                swap( this->Shrink, obj.Shrink );
            }

            /**
             * @brief prints anixt_letter to stream
             * @param stream outputstream
             * @param al     anixt_letter object
             * @return reference to stream
             **/
            friend std::basic_ostream<CharT, Traits> &
            operator<<( std::basic_ostream<CharT, Traits> &stream,
                        const anixt_letter &               al )
            {
                stream << std::endl;
                for ( const auto &str : al )
                {
                    stream << str << std::endl;
                }
                return stream;
            }

            /**
             * @brief prints anixt_string to stream
             * @param stream outputstream
             * @param as  anixt_string object
             * @return reference to stream
             **/
            friend std::basic_ostream<CharT, Traits> &
            operator<<( std::basic_ostream<CharT, Traits> &stream,
                        const anixt_string &               as )
            {
                stream << std::endl;
                for ( const auto &str : as )
                {
                    stream << str << std::endl;
                }
                return stream;
            }
        };

        /**
         * @brief swap two anixt_config
         * @param lhs object one to swap
         * @param rhs object two to swap
         **/
        template <typename CharT, typename SizeT, typename Traits,
                  template <typename> typename Alloc>
        void swap( anixt_config<CharT, SizeT, Traits, Alloc> &lhs,
                   anixt_config<CharT, SizeT, Traits, Alloc> &rhs ) noexcept
        {
            lhs.swap( rhs );
        }

    } // namespace art

} // namespace sri

#endif