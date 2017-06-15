#pragma once
#include<SFML\Graphics.hpp>

class station;
class train;

class passenger : public sf::Drawable {
public:
	passenger(station *_cur_stn);
	void load_to(train *_cur_train);
	void unload_to(station *_cur_stn);

	void draw(sf::RenderTarget&, sf::RenderStates) const override;
protected:
	enum {STATION, TRAIN} MODE;
	station* cur_stn;
	train *cur_train;
};