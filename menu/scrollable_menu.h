#pragma once
#include<SFML\Graphics\Drawable.hpp>
#include"clickable.h"
#include"map_button.h"
#include<vector>

class scrollable_menu_H : public sf::Drawable, public clickable {
public:
	scrollable_menu_H(int _y1, int _y2);

	//Draws the object onto the render target
	//Render state is never used, advanced shaders are out of the scope of this program
	//This is a library function
	void draw(sf::RenderTarget&, sf::RenderStates) const override;
	bool contained(int x, int y);
	void on_click(int prevX, int prevY, int curX, int curY, bool initClick) override;
	void on_release(int prevX, int prevY, int curX, int curY) override;

	//recalculates the size of the object depending on the size of the new window
	void resize();

	//y1 is the y coordinate of the top of the window
	//y2 is the y coordinate of the top of the window
	int y1, y2;

	//Unfortunately it is impossible to find a value that works for all windows
	//Since each window size is unique and no data has been loaded yet, I just picked what worked for most windows
	const static int margin = 30;
	const static int padding = 20;
protected:
	std::vector<map_button> buttons;
private:
};