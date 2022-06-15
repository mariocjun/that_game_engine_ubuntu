//
// Created by CIANDT\mariocj on 15/06/22.
//

#ifndef GAME_C_DRAWABLE_HPP
#define GAME_C_DRAWABLE_HPP

#include <SFML/Graphics.hpp>

#include "Window.hpp"

class C_Drawable {
public:
    C_Drawable();

    virtual ~C_Drawable();

    virtual void Draw(Window &window) = 0;

    void SetSortOrder(int order);

    int GetSortOrder() const;

private:
    int sortOrder;
};


#endif //GAME_C_DRAWABLE_HPP
