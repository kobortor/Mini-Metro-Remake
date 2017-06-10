#pragma once
#include<SFML\Graphics\Drawable.hpp>
#include"clickable.h"
#include"map_button.h"
#include<vector>

class scrollable_menu_H : public sf::Drawable, public clickable {
public:
	scrollable_menu_H(int _y1, int _y2);
	void draw(sf::RenderTarget&, sf::RenderStates) const override;
	bool contained(int x, int y);
	void onClick(int prevX, int prevY, int curX, int curY, bool initClick) override;
	void onRelease(int prevX, int prevY, int curX, int curY) override;
	int y1, y2;

	const static int margin = 30;
	const static int padding = 20;
protected:
	std::vector<map_button> vec;
private:
};