#pragma once
#include<string>
#include<SFML\Graphics.hpp>

namespace func {
	//Removes whitespace from either ends of [str]
	void trim(std::string &str);

	//if X is the angle between the 2 vectors, cross(A,B) gets |A| * |B| * sin(X)
	float cross(sf::Vector2f A, sf::Vector2f B);

	//if X is the angle between the 2 vectors, dot(A,B) gets |A| * |B| * cos(X)
	float dot(sf::Vector2f A, sf::Vector2f B);

	//Returns a vector pointing in the same direction of [V] with length 1
	//If [V] is the zero vector, then error
	sf::Vector2f normalize(sf::Vector2f V);

	//Returns the hypotenuse length of [V]
	float hypotf(sf::Vector2f V);
	
	//Finds the object in the range [begin, end) that has the location [ptr]
	//If found, returns the iterator, otherwise returns [end]
	template<class iter, class obj>
	iter find_iter(iter begin, iter end, obj *ptr) {
		while (begin != end) {
			if (&*begin == ptr) {
				return begin;
			}
			begin++;
		}
		return end;
	}

	//Draws a line with width from [begin] to [end] that is [wid] pixels wide and colored in [col], 
	//then adds 2 circles at the end to smooth out turns and avoid rough corners
	//The object is drawn to [targ]
	void draw_thick_line(sf::Vector2f begin, sf::Vector2f end, float wid, sf::Color col, sf::RenderTarget &targ);

	//Draws a ring around [center] from [inner_radius] to [outer_radius] with [num_points] points on both ends.
	//Radii are measured in pixels
	//the ring is colored [col] and is draw to [targ]
	void draw_ring(sf::Vector2f center, float inner_radius, float outer_radius, int num_points, sf::Color col, sf::RenderTarget& targ);

	//Draws a semi circle around [center] with a radius of [radius] from [begin_ang] to [end_ang] with [num_points] points around it, +1 in the center
	//[Radius] is measured in pixels
	//The semicircle is shaded [col] color and is drawn onto [targ]
	void draw_semi_circle(sf::Vector2f center, float radius, float begin_ang, float end_ang, int num_points, sf::Color col, sf::RenderTarget& targ);

	//Gets the shortest distance of [point] to a line starting at [begin] to [end]
	//There is no unit for the lines
	float dist_to_line(sf::Vector2f begin, sf::Vector2f end, sf::Vector2f point);

	//Gets the opposite color of [col], does not change the transparency
	sf::Color opposite_color(sf::Color col);
}