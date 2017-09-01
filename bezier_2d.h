#pragma once

#include "glm_include.h"
#include "static_size.h"
#include "bernstein.h"

#include <array>


namespace detail {
	template <class T, class ARRAY_CTRL_PTS, size_t K1, size_t K2>
	struct bezier_2d_helper {
		static glm::vec3 at_t(const ARRAY_CTRL_PTS &points, const T &s, const T &t) {
			constexpr size_t n1 = static_size<0, ARRAY_CTRL_PTS>::value - 1;
			constexpr size_t n2 = static_size<1, ARRAY_CTRL_PTS>::value - 1;

			qDebug() << n1 << K1 << ";" << n2 << K2;
			const glm::vec3 tmp 
			= bernstein::polynomial<n1, K1>(s)
			* bernstein::polynomial<n2, K2>(t) 
			* points[K1][K2]
			+ bezier_2d_helper<T, ARRAY_CTRL_PTS, K1-1, K2>::at_t(points, s, t);

			return tmp;
		}   
	};
	
	template <class T, class ARRAY_CTRL_PTS, size_t K2>
	struct bezier_2d_helper<T, ARRAY_CTRL_PTS, 0, K2> {
		static glm::vec3 at_t(const ARRAY_CTRL_PTS &points, const T &s, const T &t) {
			constexpr size_t n1 = static_size<0, ARRAY_CTRL_PTS>::value - 1;
			constexpr size_t n2 = static_size<1, ARRAY_CTRL_PTS>::value - 1;

			qDebug() << n1 << 0 << ";" << n2 << K2;
			const glm::vec3 tmp 
			= bernstein::polynomial<n1, 0>(s)
			* bernstein::polynomial<n2, K2>(t) 
			* points[0][K2]
			+ bezier_2d_helper<T, ARRAY_CTRL_PTS, n1, K2-1>::at_t(points, s, t);
			
			return tmp;
		}   
	};
	
	template <class T, class ARRAY_CTRL_PTS>
	struct bezier_2d_helper<T, ARRAY_CTRL_PTS, 0, 0> {
		static glm::vec3 at_t(const ARRAY_CTRL_PTS &points, const T &s, const T &t) {
			constexpr size_t n1 = static_size<0, ARRAY_CTRL_PTS>::value - 1;
			constexpr size_t n2 = static_size<1, ARRAY_CTRL_PTS>::value - 1;
			
			qDebug() << n1 << 0 << ";" << n2 << 0;
			const glm::vec3 tmp 
			= bernstein::polynomial<n1, 0>(s)
			* bernstein::polynomial<n2, 0>(t) 
			* points[0][0];
			
			return tmp;
		}   
	};
};

template <class ARRAY_CTRL_PTS, class T>
glm::vec3 bezier_2d(const ARRAY_CTRL_PTS &points, const T &s, const T &t) {
	constexpr size_t width = static_size<0, ARRAY_CTRL_PTS>::value - 1;
	constexpr size_t height = static_size<1, ARRAY_CTRL_PTS>::value - 1;
	return detail::bezier_2d_helper<T, ARRAY_CTRL_PTS, width, height>::at_t(points, s, t);
}   
