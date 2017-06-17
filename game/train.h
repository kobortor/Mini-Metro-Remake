#pragma once
#include<SFML\Graphics.hpp>
#include"metro_line.h"
#include"passenger.h"

class train : public sf::Drawable {
public:
	train(metro_line *_home_line, station *_cur_stn);
	train(metro_line *_home_line, segment track);

	void draw(sf::RenderTarget&, sf::RenderStates) const override;

	//will return true once it can't find any more track to carry on
	bool is_dead();

	sf::Vector2f get_pos();
	void resize();

	//milliseconds of change
	void update(long long delta);

	int space_left();

	void add_passenger(passenger*);

	static float screen_size();
protected:
	friend class station;

	void reorg_passengers();

	const static float unit_ratio;
	float posX, posY;
	segment cur_track;
	float amnt_done;
	station* cur_stn;
	station* prv_stn;
	std::list<passenger*> passengers;

	//tries to find next path in metro line
	void seek();

	metro_line *home_line;
	long long delay_for;

	enum TRAIN_STATUS {
		TOWARDS_MID,
		TOWARDS_END,
		STOPPING,	//slight delay when entering station
		LOADING,	//loading and unloading passengers at station
		SEEKING,	//finding next station, must be done before leaving current station
		STARTING,	//slight delay before exiting station
		DEAD
	} status;
};