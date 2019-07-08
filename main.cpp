#include <QApplication>

#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "ffd/bezier_generator.h"
#include "stl/stl_import.h"


int main(int argc, char** argv)
{    
    stl::format stl_handle("simple_boat5.stl");
    qDebug() << stl_handle.faces().size();
    
    stl::bbox b1 = stl_handle.estimate_bbox(stl_handle.faces());
    std::vector<stl::face> scaled = stl_handle.normalized(b1);
    qDebug() << b1._min.x << b1._min.y << b1._min.z;
    qDebug() << b1._max.x << b1._max.y << b1._max.z;
    
    stl::bbox b2 = stl_handle.estimate_bbox(scaled);
    qDebug() << b2._min.x << b2._min.y << b2._min.z;
    qDebug() << b2._max.x << b2._max.y << b2._max.z;

/*
	std::array<int, 4> ainp = {1,2,3,4};
	std::array<float, 4> afnp = {0.1,0.2,0.3,0.4};
	std::array<int, 4> ctrl = {1,2,3,4};
    
	qDebug() << "3D = walker (bezier function)";
	std::array<std::array<std::array<glm::vec3, 3>, 3>, 3> ctrl3d;

	bezier<3,3,3>(afnp, ctrl3d);
*/

	glm::vec3 ainp1 = {0.1, 0.2, 0.3};
    glm::vec2 ainp2 = {0.9, 0.2};
    glm::vec2 ainp3 = {1, 0.2};
    glm::vec2 ainp4 = {1.1, 0.2};
    glm::vec2 ainp5 = {10, 0.2};
    
    std::array<glm::vec2, 3> a1 = { glm::vec2(0.0, 0.0), glm::vec2(0.0, 0.5), glm::vec2(0.0, 1.0) };
    std::array<glm::vec2, 3> a2 = { glm::vec2(0.75, 0.0), glm::vec2(0.75, 0.5), glm::vec2(0.75, 1.0) };
    std::array<glm::vec2, 3> a3 = { glm::vec2(1.5, 0.0), glm::vec2(1.5, 0.5), glm::vec2(1.5, 1.0) };
    
	std::array<std::array<glm::vec2, 3>, 3> ctrl2d = { a1, a2, a3 };

    glm::vec2 out;
    out= bezier<3,3>(ainp1, ctrl2d);
    qDebug() << out.x << out.y;

    out = bezier<3,3>(ainp2, ctrl2d);
    qDebug() << out.x << out.y;
    
    out = bezier<3,3>(ainp3, ctrl2d);
    qDebug() << out.x << out.y;
    
    out = bezier<3,3>(ainp4, ctrl2d);
    qDebug() << out.x << out.y;
    
    out = bezier<3,3>(ainp5, ctrl2d);
    qDebug() << out.x << out.y;
    
    return 0;
}
