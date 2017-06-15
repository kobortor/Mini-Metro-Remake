#pragma once
#include<SFML\Graphics.hpp>
#include"station.h"

class station;
class train;

class passenger : public sf::Drawable {
public:
	passenger(station *_cur_stn, station::STATION_TYPE _type);
	void load_to(train *_cur_train);
	void unload_to(station *_cur_stn);

	void draw(sf::RenderTarget&, sf::RenderStates) const override;

	//gets the diameter of the icon on the screen
	static float icon_size();
	float posX, posY;
protected:
	enum {STATION, TRAIN} MODE;
	station::STATION_TYPE type;
	station* cur_stn;
	train *cur_train;
};