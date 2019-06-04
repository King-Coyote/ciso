#pragma once

#include "SFML/Graphics.hpp"
#include "luavm/Table.hpp"
#include "luavm/State.hpp"
#include "GuiObject.hpp"
#include "ResourceManager.hpp"
#include "StyleMap.hpp"

namespace ci {

class Panel : public GuiObject {
public:
    Panel(
        mun::Table&,
        mun::State&,
        StyleMap&,
        ResourceManager&
    );

    sf::Vector2f getGlobalPos() override;
    sf::Vector2f getLocalPos() override;
protected:
    void renderDrawables(float dt, sf::RenderTarget& window) override;
    void updateDrawables(float dt) override;
    void setDrawablesPosition(const sf::Vector2f& position) override;
    void applyStyle(const GuiStyle& style) override;
    bool pointInBounds(float x, float y) override;

    sf::RectangleShape background;
};

}
