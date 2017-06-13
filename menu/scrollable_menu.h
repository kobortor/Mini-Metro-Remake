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
	void on_click(int prevX, int prevY, int curX, int curY, bool initClick) override;
	void on_release(int prevX, int prevY, int curX, int curY) override;

	//recalculates the size of the object depending on the size of the new window
	void resize();
	int y1, y2;

	const static int margin = 30;
	const static int padding = 20;
protected:
	std::vector<map_button> vec;
private:
};