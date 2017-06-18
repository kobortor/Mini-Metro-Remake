#pragma once
#include"button.h"
#include<string>

class map_button : public button {
public:
	map_button(int _x, int _y, int _wid, int _ht, std::string _display_name, std::string _map_file_name);

	//Draws the object onto the render target
	//Render state is never used, advanced shaders are out of the scope of this program
	//This is a library function
	void draw(sf::RenderTarget&, sf::RenderStates) const override;
	void on_click(int prevX, int prevY, int curX, int curY, bool isInitial) override;
	void on_release(int prevX, int prevY, int curX, int curY) override;
protected:
	std::string display_name;
	std::string map_file_name;
	bool isClicked = false;
	bool moved = false;
};