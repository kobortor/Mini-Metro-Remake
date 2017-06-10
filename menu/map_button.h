#pragma once
#include"button.h"
#include<string>

class map_button : public button {
public:
	map_button(int _x, int _y, int _wid, int _ht, std::string map_file_name);
	void draw(sf::RenderTarget&, sf::RenderStates) const override;
	void onClick(int prevX, int prevY, int curX, int curY) override;
	void onRelease(int prevX, int prevY, int curX, int curY) override;
protected:
	std::string tmp_name;
	bool isClicked = false;
};