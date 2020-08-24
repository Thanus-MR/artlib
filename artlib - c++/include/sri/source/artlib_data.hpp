#ifndef STRVEC
#define STRVEC

#include <string>
#include <vector>

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
         * @struct artlib_data
         * @brief  vector of string
         * @tparam String string_type
         * @tparam Alloc allocato type
         **/
        template <typename String, template <typename> typename Alloc>
        struct artlib_data : private std::vector<String, Alloc<String>>
        {
            using base        = std::vector<String, Alloc<String>>;
            using string_type = String;
            template <typename T>
            using alloc_type  = Alloc<T>;

            using typename base::allocator_type;
            using typename base::const_iterator;
            using typename base::const_pointer;
            using typename base::const_reference;
            using typename base::const_reverse_iterator;
            using typename base::difference_type;
            using typename base::iterator;
            using typename base::pointer;
            using typename base::reference;
            using typename base::reverse_iterator;
            using typename base::size_type;
            using typename base::value_type;

            using base::base;
            virtual ~artlib_data() = default;

            using base::operator=;
            using base::assign;
            using base::at;
            using base::get_allocator;
            using base::operator[];
            using base::back;
            using base::begin;
            using base::capacity;
            using base::cbegin;
            using base::cend;
            using base::clear;
            using base::data;
            using base::emplace;
            using base::empty;
            using base::end;
            using base::erase;
            using base::front;
            using base::insert;
            using base::max_size;
            using base::push_back;
            using base::rbegin;
            using base::rend;
            using base::reserve;
            using base::resize;
            using base::shrink_to_fit;
            using base::size;
            using base::swap;

            friend void swap( artlib_data &lhs, artlib_data &rhs )
            {
                lhs.swap( rhs );
            }
        };

    } // namespace art

} // namespace srilakshmikanthanp

#endif