#pragma once

#include <iostream>

#include "Graphics.hpp"
#include "EventHandler.hpp"
#include "EventQueue.hpp"

class derp : public EventHandler {
	// dummy test class ya dingus
	// fyerhealth

public:
	std::string str;
	derp(std::string str, EventQueue& queue) : 
		EventHandler(queue, {EventType::GUI_BUTTONCLICKED, EventType::GUI_TEXTENTERED}),
		str(str) 
	{}

	~derp() {
		std::cout << "Derp obj destroyed with string " << str << std::endl;
	}

};