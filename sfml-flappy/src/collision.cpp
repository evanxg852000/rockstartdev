
#include "./collision.hpp"
#include "./definitions.hpp"


namespace evansofts {

    Collision::Collision(){

    }

    bool Collision::CheckSpriteCollision(sf::Sprite s1, sf::Sprite s2){
        sf::Rect<float> r1 =s1.getGlobalBounds();
        sf::Rect<float> r2 =s2.getGlobalBounds();
        return r1.intersects(r2);
    }

    bool Collision::CheckSpriteCollision(sf::Sprite s1, float scale1, sf::Sprite s2, float scale2){
        s1.setScale(scale1, scale1);
        s2.setScale(scale2, scale2);

        sf::Rect<float> r1 =s1.getGlobalBounds();
        sf::Rect<float> r2 =s2.getGlobalBounds();
        return r1.intersects(r2);
    }

}