#pragma once
#include<SFML\Graphics.hpp>
#include"metro_line.h"
#include"passenger.h"

class train : public sf::Drawable, public resizable {
public:

	//The line that this train runs on
	//What station the train should start at
	train(metro_line *_home_line, station *_cur_stn);

	//The line that this train runs on
	//Which piece of track the train originally starts at
	train(metro_line *_home_line, segment track);

	//Draws the object onto the render target
	//Render state is never used, advanced shaders are out of the scope of this program
	//This is a library function
	void draw(sf::RenderTarget&, sf::RenderStates) const override;

	//will return true once it can't find any more track to carry on and should be deleted
	//false otherwise
	bool is_dead();

	//Gets the position of the train (in pixels position)
	sf::Vector2f get_pos();

	//Overridden
	void resize(sf::Vector2f, sf::IntRect) override;

	//Updates the station
	//[delta] is the number of milliseconds since last update
	void update(long long delta);

	//Adds the passenger onto the train
	void add_passenger(passenger*);

	//Unload all passengers that stop or transfer at this station
	void unload(station *stn);

	//Returns the size of the train on the screen in pixels
	static float screen_size();

	//Returns the number of passengers on the train
	int get_num_passengers();

	//returns the distance travelled by the train in relative units per millisecond
	static float get_speed();

	//Gets the metro_line that the train runs on
	metro_line* get_home_line();

	//the the train to drop off all passengers at the next station, and go to the scrapyard afterwards
	void mark_for_death();

	//Returns true if marked for death, false otherwise
	bool is_marked_for_death();

	//Is the train highlighted?
	//If true, the train is within the "kill radius" of the delete button and should display a warning X
	bool highlighted = false;
protected:
	//Reorganizes the passengers in the train to fit a certain pattern
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