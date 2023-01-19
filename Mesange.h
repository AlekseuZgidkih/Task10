#pragma once

class Mesange {

private:

	string _to;
	string _from;
	string _text;

public:
	int countMesanges = 0;
	Mesange(const string& to, const string& from, const string& text) :_to(to), _from(from), _text(text) {}

	string& getTo() { return _to; }
	string& getFrom() { return _from; }
	string& getText() { return _text; }

};
