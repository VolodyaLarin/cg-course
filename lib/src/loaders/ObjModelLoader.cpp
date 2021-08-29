//
// Created by volodya on 29.08.2021.
//
#include <fstream>
#include <iostream>
#include <sstream>

#include "loaders/ObjModelLoader.h"

Model::UPtr ObjModelLoader::load(const std::string& filename, const IFactory<ICoord>& factory) {
    std::ifstream fin;
    fin.open(filename);

    if(!fin.is_open()) {
        throw std::exception();
    }

    std::vector<ICoord::Ptr> coords = {};
    std::vector<Polygon> polygons = {};

    while (!fin.eof()) {
        std::string lineHeader;
        std::getline(fin, lineHeader);

        std::stringstream str(lineHeader);

        std::string cmd;

        str >> cmd;

        if (cmd == "v" ){
            auto coord = factory.create();
            ICoord::type x,y,z;
            str >> x >> y >> z;

            coord->setX(x);
            coord->setY(y);
            coord->setZ(z);

            coords.emplace_back(std::move(coord));
        }else if ( cmd == "f") {
            std::vector<ICoord::Ptr> polygon = {};
            std::string vertexStr;
            while (std::getline(str, vertexStr, ' ')) {
                if (!vertexStr.length()) continue;
                std::stringstream vertexStream(vertexStr);
                int x;
                vertexStream >> x;
                polygon.push_back(coords[x - 1]);
            }
            polygons.emplace_back(Polygon(std::move(polygon)));
        }

    }

    return std::make_unique<Model>(std::move(polygons));
}
