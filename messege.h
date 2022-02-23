#pragma once
#include "user.h";

using namespace std;

class Messege
{
	const string from_;
	const string to_;
	const string text_;

public:
	Messege(const string& from, const string& to, const string& text)
		:from_(from), to_(to),text_(text) {}

	const string& getFrom() { return from_; }
	const string& getTo() { return to_; }
	const string& getText() { return text_; }
};
