/****************************************************************************
**
** Copyright (C) 2009-2010 TECHNOGERMA Systems France and/or its subsidiary(-ies).
** Contact: Technogerma Systems France Information (contact@technogerma.fr)
**
** This file is part of the CAMP library.
**
** CAMP is free software: you can redistribute it and/or modify
** it under the terms of the GNU Lesser General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
** 
** CAMP is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU Lesser General Public License for more details.
** 
** You should have received a copy of the GNU Lesser General Public License
** along with CAMP.  If not, see <http://www.gnu.org/licenses/>.
**
****************************************************************************/


#ifndef CAMP_DETAIL_ISSMARTPOINTER_HPP
#define CAMP_DETAIL_ISSMARTPOINTER_HPP


#include <camp/detail/yesnotype.hpp>
#include <boost/utility/enable_if.hpp>
#include <type_traits>

namespace camp
{
namespace detail
{
/**
 * \brief Utility class which tells at compile-time if a type T is a smart pointer to a type U
 *
 * To detect a smart pointer type, we check using SFINAE if T implements an operator -> returning a U*
 */
template <typename T, typename U>
struct IsSmartPointer
{
    enum {value = (!std::is_pointer<T>::value && !std::is_same<T, U>::value) };
};

} // namespace detail

} // namespace camp


namespace boost
{
/**
 * \brief Specialization of boost::get_pointer for all smart pointer types (const version)
 *
 * This function is specialized for every type T for which IsSmartPointer<T> is true. It makes
 * the stored value available for all boost algorithms (especially for boost::bind).
 */
template <template <typename> class T, typename U>
U* get_pointer(const T<U>& obj, typename enable_if<camp::detail::IsSmartPointer<T<U>, U> >::type* = 0)
{
    return obj.get();
}

/**
 * \brief Specialization of boost::get_pointer for all smart pointer types (non-const version)
 *
 * This function is specialized for every type T for which IsSmartPointer<T> is true. It makes
 * the stored value available for all boost algorithms (especially for boost::bind).
 */
template <template <typename> class T, typename U>
U* get_pointer(T<U>& obj, typename enable_if<camp::detail::IsSmartPointer<T<U>, U> >::type* = 0)
{
    return obj.get();
}

} // namespace boost


#endif // CAMP_DETAIL_ISSMARTPOINTER_HPP
