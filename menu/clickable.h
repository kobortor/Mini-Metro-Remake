#pragma once

class clickable {
public:
	//default function is unclickable
	virtual bool contained(int x, int y);
	virtual ~clickable();
};