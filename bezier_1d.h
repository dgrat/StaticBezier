#pragma once

#include "glm_include.h"
#include "static_size.h"
#include "bernstein.h"

#include <array>


namespace detail {
	template <class T, class ARRAY_CTRL_PTS, size_t K>
	struct bezier_1d_helper {
		static glm::vec3 at_t(const ARRAY_CTRL_PTS &points, const T &t) {
			constexpr size_t n = static_size<0, ARRAY_CTRL_PTS>::value - 1; 	// length of the array minus one always equals: N ..
			const glm::vec3 tmp 
			= bernstein::polynomial<n, K>(t) * points.at(K) 					// current polynomial
			+ bezier_1d_helper<T, ARRAY_CTRL_PTS, K-1>::at_t(points, t); 		// recursion
			
			return tmp;
		}   
	};

	template <class T, class ARRAY_CTRL_PTS>
	struct bezier_1d_helper<T, ARRAY_CTRL_PTS, 0> {
		static glm::vec3 at_t(const ARRAY_CTRL_PTS &points, const T &t) {
			constexpr size_t n = static_size<0, ARRAY_CTRL_PTS>::value - 1; 	// length of the array minus one always equals: N ..
			return bernstein::polynomial<n, 0>(t) * points.at(0);
		}   
	};
};

template <class ARRAY_CTRL_PTS, class T>
glm::vec3 bezier(const ARRAY_CTRL_PTS &points, const T &t) {
	constexpr size_t id_lst_pt = static_size<0, ARRAY_CTRL_PTS>::value - 1;
	return detail::bezier_1d_helper<T, ARRAY_CTRL_PTS, id_lst_pt>::at_t(points, t);
}   

