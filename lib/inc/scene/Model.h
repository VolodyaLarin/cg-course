/**
 * Project Untitled
 */


#ifndef _MODEL_H
#define _MODEL_H

#include "BaseSceneObject.h"
#include "Polygon.h"


class Model: public BaseSceneObject {
public:
    using iterator = std::vector<Polygon>::iterator;
    using const_iterator = std::vector<Polygon>::const_iterator;

    explicit Model(std::vector<Polygon>&& polygons);

    iterator begin();
    iterator end();

    [[nodiscard]] const_iterator begin() const;
    [[nodiscard]] const_iterator end() const;

    [[nodiscard]] const_iterator cbegin() const;
    [[nodiscard]] const_iterator cend() const;

    [[nodiscard]] SceneObjectType getType() const override;

    void accept(IVisitor &visitor) override;


private: 
    std::vector<Polygon> _polygons;
};

#endif //_MODEL_H