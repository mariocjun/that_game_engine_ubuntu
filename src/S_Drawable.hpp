//
// Created by CIANDT\mariocj on 15/06/22.
//

#ifndef GAME_S_DRAWABLE_HPP
#define GAME_S_DRAWABLE_HPP

#include <map>
#include <memory>

#include "C_Drawable.hpp"
#include "Object.hpp"

class S_Drawable {
public:
    void Add(std::vector<std::shared_ptr<Object>> &object);

    void ProcessRemovals();

    void Draw(Window &window);

private:
    void Add(std::shared_ptr<Object> object);

    void Sort();

    std::vector<std::shared_ptr<Object>> drawables;

};


#endif //GAME_S_DRAWABLE_HPP
