#include "ComponentSpace.hpp"

using namespace std;

namespace ci {
ComponentSpace::ComponentSpace() :
    Component(-1),
    navMesh(nullptr)
{}

ComponentSpace::ComponentSpace(mun::Table& t) :
    Component(t.get<int>("level", -1))
{
    if (this->level > 10) {
        vector<sf::Vector2f> pts = {
            sf::Vector2f(0, 0),
            sf::Vector2f(35, 0),
            sf::Vector2f(35, 70),
            sf::Vector2f(55, 70),
            sf::Vector2f(55, 0),
            sf::Vector2f(75, 0),
            sf::Vector2f(75, 50),
            sf::Vector2f(100, 50),
            sf::Vector2f(100, 60),
            sf::Vector2f(75, 60),
            sf::Vector2f(75, 110),
            sf::Vector2f(100, 110),
            sf::Vector2f(100, 140),
            sf::Vector2f(55, 140),
            sf::Vector2f(55, 110),
            sf::Vector2f(0, 110)
        };
        for (auto& v : pts) {
            v *= 3.0f;
        }
        this->navMesh = make_unique<NavMesh>(pts);
    } else {
        this->navMesh = nullptr;
    }
}

ComponentSpace::ComponentSpace(mun::Table&& t) :
    Component(t.get<int>("level", -1))
{
    if (this->level > 10) {
        vector<sf::Vector2f> pts = {
            sf::Vector2f(0, 0),
            sf::Vector2f(35, 0),
            sf::Vector2f(35, 70),
            sf::Vector2f(55, 70),
            sf::Vector2f(55, 0),
            sf::Vector2f(75, 0),
            sf::Vector2f(75, 50),
            sf::Vector2f(100, 50),
            sf::Vector2f(100, 60),
            sf::Vector2f(75, 60),
            sf::Vector2f(75, 110),
            sf::Vector2f(100, 110),
            sf::Vector2f(100, 140),
            sf::Vector2f(55, 140),
            sf::Vector2f(55, 110),
            sf::Vector2f(0, 110)
        };
        for (auto& v : pts) {
            v *= 3.0f;
        }
        this->navMesh = make_unique<NavMesh>(pts);
    } else {
        this->navMesh = nullptr;
    }
}

}

