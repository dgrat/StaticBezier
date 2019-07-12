#pragma once

#include <vector>
#include <fstream>
#include <cassert>


namespace stl {
    #pragma pack(push, 1)
    struct face {
        glm::vec3 _norm;
        glm::vec3 _vert_1;
        glm::vec3 _vert_2;
        glm::vec3 _vert_3;
        uint16_t _attribute = 0;
    };
    #pragma pack(pop)

    struct bbox {
        glm::vec3 _min;
        glm::vec3 _max;
    
        float scale() const;
        glm::vec3 offset() const;
    };

    //! Estimates global factor to scale the whole model to 0 < x < 1
    float bbox::scale() const {
        float max(-FLT_MAX);
        glm::vec3 dif = _max - _min;
        
        for(int i = 0; i < 3; i++) {
            max = dif[i] > max ? dif[i] : max;
        }
        return 1.f / max;
    }

    //! Estimates offset to scale the whole model to 0 <= x <= 1
    glm::vec3 bbox::offset() const {
        return _min * (-1.f);
    }

    class format {
        // small check to guarantee sanity
        static_assert(sizeof(face) == sizeof(glm::vec3) * sizeof(float) + sizeof(uint16_t), "size mismatch: face not compatible with stl format");
       
        uint8_t _header[80] = { 0 };
        std::vector<face> _faces;
       
        public:
            format() = default;
            format(const std::string &file);
            
            bool load(const std::string &filename);
            const std::vector<face> &faces() const;
           
           
            //! estimates the bbox
            bbox estimate_bbox(const std::vector<face> &) const;
            //! Scaled down to 0 <= x <= 1
            std::vector<face> normalized(const bbox &) const;
           
            // operator overload to access face
            face& operator[](std::size_t idx) { return _faces[idx]; }
            const face& operator[](std::size_t idx) const { return _faces[idx]; }
    };
    
    std::vector<face> format::normalized(const bbox &b) const {  
        const float scale = b.scale();
        const glm::vec3 offs = b.offset();
        
        std::vector<face> res;    
        for(face f : _faces) {
            glm::vec3 v1 = (f._vert_1 + offs) * scale;
            glm::vec3 v2 = (f._vert_2 + offs) * scale;
            glm::vec3 v3 = (f._vert_3 + offs) * scale;
            res.push_back( { f._norm, v1, v2, v3 } );
        }
        
        return res;
    }
    
    bbox format::estimate_bbox(const std::vector<face> &faces) const {
        glm::vec3 min(FLT_MAX);
        glm::vec3 max(-FLT_MAX);
        
        for(auto face : faces) {
            min.x = face._vert_1.x < min.x ? face._vert_1.x : min.x;
            min.y = face._vert_1.y < min.y ? face._vert_1.y : min.y;
            min.z = face._vert_1.z < min.z ? face._vert_1.z : min.z;
            
            min.x = face._vert_2.x < min.x ? face._vert_2.x : min.x;
            min.y = face._vert_2.y < min.y ? face._vert_2.y : min.y;
            min.z = face._vert_2.z < min.z ? face._vert_2.z : min.z;
            
            min.x = face._vert_3.x < min.x ? face._vert_3.x : min.x;
            min.y = face._vert_3.y < min.y ? face._vert_3.y : min.y;
            min.z = face._vert_3.z < min.z ? face._vert_3.z : min.z;
            
            max.x = face._vert_1.x > max.x ? face._vert_1.x : max.x;
            max.y = face._vert_1.y > max.y ? face._vert_1.y : max.y;
            max.z = face._vert_1.z > max.z ? face._vert_1.z : max.z;
            
            max.x = face._vert_2.x > max.x ? face._vert_2.x : max.x;
            max.y = face._vert_2.y > max.y ? face._vert_2.y : max.y;
            max.z = face._vert_2.z > max.z ? face._vert_2.z : max.z;
            
            max.x = face._vert_3.x > max.x ? face._vert_3.x : max.x;
            max.y = face._vert_3.y > max.y ? face._vert_3.y : max.y;
            max.z = face._vert_3.z > max.z ? face._vert_3.z : max.z;
        }
        return { min, max };
    }
   
    format::format(const std::string &file) {
        if(!load(file)) {
            qDebug() << "Failed loading file";
        }
    }
   
    bool format::load(const std::string &filename) {        
        std::ifstream ifs;
        ifs.open (filename.c_str(), std::ios::in | std::ios::binary);
       
        if(!ifs.is_open()) return false;
       
        // read header
        ifs.read(reinterpret_cast<char *>(&_header[0]), 80);
        // read number of faces
        size_t num_faces = 0;
        ifs.read(reinterpret_cast<char *>(&num_faces), 4);
        // read the faces
        _faces.resize(num_faces);
        ifs.read(reinterpret_cast<char *>(&_faces[0]), num_faces*sizeof(face));
       
        ifs.close();
        return true;
    }
   
    const std::vector<face> &format::faces() const {
        return _faces;
    }
};
