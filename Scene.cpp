#include "Scene.hpp"
#include "Gui.hpp"

Scene::Scene() {
	this->font.loadFromFile("pala.ttf");
}

void Scene::update(const float dt) {

	Gui::Button(100.0f, 100.0f, 10.0f,10.0f);
	Gui::Text("GET FUKT", 200.0f, 200.0f, this->font, 24);

}

void Scene::draw() {



}

Scene::~Scene() {

}