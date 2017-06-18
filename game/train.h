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

	void add_passenger(passenger*);

	void unload(station *stn);

	static float screen_size();

	int num_passengers();

	//returns the distance travelled by the train in relative units per millisecond
	static float get_speed();

	metro_line* get_home_line();

	void mark_for_death();

	bool is_marked_for_death();

	bool highlighted = false;
protected:
	void reorg_passengers();

	float posX, posY;
	float prvX, prvY;
	segment cur_track;
	float amnt_done;
	station* cur_stn;
	station* prv_stn;
	std::list<passenger*> passengers;

	//tries to find next path in metro line
	void seek();

	sf::Color color;
	metro_line *home_line;
	long long delay_for;

	bool marked_for_death = false;
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