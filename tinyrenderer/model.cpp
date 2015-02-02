#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "model.h"

Model::Model(const char *filename) : verts_(), faces_(), textures_() {
    std::ifstream in;
    in.open (filename, std::ifstream::in);
    if (in.fail()) return;
    std::string line;
    while (!in.eof()) {
        std::getline(in, line);
        std::istringstream iss(line.c_str());
        char trash;
        if (!line.compare(0, 2, "v ")) {
            iss >> trash;
            Vec3f v;
            for (int i=0;i<3;i++) iss >> v[i];
            verts_.push_back(v);
        } else if (!line.compare(0, 2, "f ")) {
            std::vector<Vec3i> f;
            int itrash, idx, tIdx;
            iss >> trash;
			while (iss >> idx >> trash >> tIdx >> trash >> itrash) {
                idx--; // in wavefront obj all indices start at 1, not zero
				tIdx--;
				//Third is normal number, zero for now
				f.push_back(Vec3i(idx, tIdx, 0));
            }
            faces_.push_back(f);
        }
		else if (!line.compare(0, 3, "vt ")) {
			iss >> trash >> trash;
			Vec2f t;
			for (int i = 0; i<2; i++) iss >> t[i];
			textures_.push_back(t);
		}
    }
	std::cerr << "# v# " << verts_.size() << " f# " << faces_.size() << " vt# " << textures_.size() << std::endl;
}

Model::~Model() {
}

int Model::nverts() {
    return (int)verts_.size();
}

int Model::nfaces() {
    return (int)faces_.size();
}

std::vector<Vec3i> Model::face(int idx) {
    return faces_[idx];
}

Vec3f Model::vert(int i) {
    return verts_[i];
}

Vec2f Model::texture(int idx){
	return textures_[idx];
}

