#include <QApplication>

#include "bezier_generator.h"


int main(int argc, char** argv)
{    

	std::array<int, 4> ainp = {1,2,3,4};
	std::array<float, 4> afnp = {0.1,0.2,0.3,0.4};
	std::array<int, 4> ctrl = {1,2,3,4};

/*
	qDebug() << "1D = 1x4";
	detail::Iterate<0>::Dim<4>::ID<3>::run(ainp);
	detail::Iterate<0>::Dim<4>::ID<2>::run(ainp);
	detail::Iterate<0>::Dim<4>::ID<1>::run(ainp);
	detail::Iterate<0>::Dim<4>::ID<0>::run(ainp);

	qDebug() << "2D = 2x2";
	detail::Iterate<1>::Dim<2,2>::ID<0,0>::run(ainp);
	detail::Iterate<1>::Dim<2,2>::ID<0,1>::run(ainp);
	detail::Iterate<1>::Dim<2,2>::ID<1,0>::run(ainp);
	detail::Iterate<1>::Dim<2,2>::ID<1,1>::run(ainp);
	
	qDebug() << "2D = walker";
	std::array<std::array<int, 2>, 2> ctrl2d = { 0 };
	helper::Dim<2,2>::run(ainp, ctrl2d, all_indexes<2,2>::type{});
	*/
	qDebug() << "3D = walker (bezier function)";
	std::array<std::array<std::array<glm::vec3, 3>, 3>, 3> ctrl3d;
	//std::array<std::array<std::array<float, 3>, 3>, 3> ctrl3d { 0.1 };
	bezier<3,3,3>(afnp, ctrl3d);
	
    return 0;
}
