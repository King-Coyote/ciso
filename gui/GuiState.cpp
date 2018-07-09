#include "GuiState.hpp"

/*
    GUISTATE_DISABLED = 0,
    GUISTATE_ENABLED,
    GUISTATE_HOVER,
    GUISTATE_CLICKED,
    GUISTATE_UNCLICKED
*/

namespace ci {

GuiStateType GuiState::transitionMouseMove(bool mouseIsInside) {
    switch (this->state) {
    case GUISTATE_ENABLED: {
        if (mouseIsInside) {
            return GUISTATE_HOVER;
        }
        break;
    }
    case GUISTATE_CLICKED: {
        if (!mouseIsInside) {
            return GUISTATE_UNCLICKED;
        }
        break;
    }
    case GUISTATE_UNCLICKED: {
        if (mouseIsInside) {
            return GUISTATE_CLICKED;
        }
        break;
    }
    default:
        return GUISTATE_ENABLED;
    }
    return GUISTATE_ENABLED;
}

GuiStateType GuiState::transitionMousePressed(bool mouseIsInside) {
    switch (this->state) {
    case GUISTATE_HOVER: {
        return GUISTATE_CLICKED;
        break;
    }
    default:
        return GUISTATE_ENABLED;
    }
    return GUISTATE_ENABLED;
}

GuiStateType GuiState::transitionMouseReleased(bool mouseIsInside) {
    switch (this->state) {
    case GUISTATE_CLICKED: {
        return GUISTATE_ENABLED;
        break;
    }
    case GUISTATE_UNCLICKED: {
        return GUISTATE_ENABLED;
        break;
    }
    default:
        return GUISTATE_ENABLED;
    }
    return GUISTATE_ENABLED;
}

GuiStateType GuiState::getState() {
    return this->state;
}

}