#include "rel_button.h"
#include"../game/main_game.h"

rel_button::rel_button(float _rel_wid, float _rel_ht) :
	button(1,1), relX(0), relY(0), relWid(_rel_wid), relHt(_rel_ht) {
}

rel_button::rel_button(float _relX, float _relY, float _rel_wid, float _rel_ht):
	button(1,1), relX(_relX), relY(_relY), relWid(_rel_wid), relHt(_rel_ht) {
}

void rel_button::resize() {
	auto bounds = main_game::get_window_bounds();
	auto rel_bounds = main_game::get_relative_bounds();
	setPos(bounds.left + relX / rel_bounds.x * bounds.width, bounds.top + relY / rel_bounds.y * bounds.height);
	setSize(relWid / rel_bounds.x * bounds.width, relHt / rel_bounds.y * bounds.height);
}
