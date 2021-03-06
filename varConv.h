#pragma once

//Written by and copyright Zachary Damato
//varConv.h is part of the zlib submodule

#include<string>
#include<time.h>
#include<sstream>

using namespace std;

#include "varTypes.h"

using namespace zlib;

namespace zlib
{
	namespace conv
	{
		enum class convertError
		{
			convertFailed,
		};

		template<class T>
		string toString(T inp)
		{
			stringstream convert;
			string out;
			
			convert.clear();
			convert << inp;

			convert >> out;
			if(convert.fail()) throw convertError::convertFailed;
			return out;
		}

		string toString(var::coord2 inp, bool multiLine = true);
		string toString(var::color_RGB inp, bool multiLine = true);
		string toString(bool inp);
		string toString(var::longTime time);	//Leaves off values if they are 0, starting from years down to the smallest value that is not 0.  (At minimum, 0 seconds will be returned)
		
		string toLowercase(string & inp, bool changeArg = true);	//Coverts 'inp' to lowercase.  USES POINTERS TO CHANGE ARGUMENT VALUES WHEN 'changeArg' IS TRUE
		char toLowercase(char & inp, bool changeArg = false);		//Coverts 'inp' to lowercase.  USES POINTERS TO CHANGE ARGUMENT VALUES WHEN 'changeArg' IS TRUE

		string toUppercase(string & inp, bool changeArg = true);	//Coverts 'inp' to uppercase.  USES POINTERS TO CHANGE ARGUMENT VALUES WHEN 'changeArg' IS TRUE
		char toUppercase(char & inp, bool changeArg = false);		//Coverts 'inp' to uppercase.  USES POINTERS TO CHANGE ARGUMENT VALUES WHEN 'changeArg' IS TRUE

		bool isNum(string inp);
		bool isNum(char inp);

		double toNum(string inp);
		double toNum(char inp);

		string toHex(unsigned value);

		bool isBool(string inp);

		bool toBool(string inp);
		bool toBool(double inp);

#ifdef ZLIB_USING_CINDER
		var::coord2 toCoord2(glm::highp_vec2 coordinate);
#endif

		double toDegrees(double radians);
		double toRadians(double degrees);
	}
}
