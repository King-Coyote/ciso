#pragma once

#include "SFML/Graphics.hpp"
#include "GuiObject.hpp"
#include "ResourceManager.hpp"

namespace ci {

class ToolTip : public GuiObject {
public:
    ToolTip(
        mun::Table& t,
        mun::State& s,
        StyleMap& styleMap,
        ResourceManager& resourceManager
    );

    sf::Vector2f getGlobalPos() override;
    sf::Vector2f getLocalPos() override;
private:
    void renderDrawables(float dt, sf::RenderTarget& window) override;
    void updateDrawables(float dt) override;
    void setDrawablesPosition(const sf::Vector2f& position) override;
    void applyStyle(const GuiStyle& style) override;
};

}
