#pragma once

//Written by and copyright Zachary Damato
//varConv.cpp is part of the zlib submodule

#include<iostream>
#include<sstream>
#include<string>
#include<stdlib.h>
#include<time.h>
#include<fstream>
#include<algorithm>
#include<vector>
#include<new>

using namespace std;

#ifdef ZLIB_USING_CINDER
#include "cinder/app/App.h"
#include "cinder/Text.h"
#include "cinder/app/App.h"
#include "cinder/Font.h"
#include "cinder/gl/Texture.h"
#include "cinder/gl/TextureFont.h"
#include "cinder/ImageIo.h"
#include "cinder/app/window.h"
#include "cinder/gl/gl.h"
#endif

#include "math.h"
#include "varTypes.h"
#include "varConv.h"

using namespace zlib;

stringstream convert;
string strOut;
float floatOut;
double doubleOut;
bool boolOut;

namespace zlib
{
	namespace conv
	{
		string toString(var::coord2 inp, bool multiLine)
		{
			if(multiLine == false)
			{
				return inp.toString();
			}
			else
			{
				return "x:" + toString(inp.x) + "\ny:" + toString(inp.y);
			}
		}

		string toString(var::color_RGB inp, bool multiLine)
		{
			if(multiLine == false)
			{
				return "r:" + toString(inp.R) + ", g" + toString(inp.G) + ", b" + toString(inp.B);
			}
			else
			{
				return "r:" + toString(inp.R) + "\ng" + toString(inp.G) + "\nb" + toString(inp.B);
			}
		}

		string toString(bool inp)
		{
			if(inp == true) return "true";
			else if(inp == false) return "false";
		}

		string toString(var::longTime time)
		{
			bool higherValue = false;		//True when a unit has been not 0, and therefore all below it must be displayed
			string ret = "";						//The output
			bool overrideAnd = true;

			//Processes a part of the formatted time.
			auto processSegment = [&ret, &higherValue, &overrideAnd] (int value, string name)
			{
				if(value != 0 || higherValue)
				{
					
					ret =  (!higherValue || overrideAnd ? "and " : "") + toString(value) + " " + name + (value == 1 ? "" : "s") + (!(!higherValue || overrideAnd) ? "," : "") + " " + ret;
					higherValue = true;
				}
			};
			processSegment(time.tm_year, "year");
			overrideAnd = false;
			processSegment(time.tm_mon, "month");
			processSegment(time.tm_mday, "day");
			processSegment(time.tm_hour, "hour");
			processSegment(time.tm_min, "minute");
			processSegment(time.tm_sec, "second");

			return ret;
		}


		string toLowercase(string & inp, bool changeArg)		//Coverts 'inp' to lowercase.  USES POINTERS TO CHANGE ARGUMENT VALUES WHEN 'changeArg' IS TRUE
		{
#ifdef __linux__
			auto loop = [](string & value)
			{
				for(unsigned i = 0; i < value.length(); i++)
				{
					value[i] = tolower(value[i]);
				}
			};
#endif
			string ret;
			if(changeArg)
			{
#ifndef __linux__
				transform(inp.begin(), inp.end(), inp.begin(), tolower);
#else
				loop(inp);
#endif
				return inp;
			}
			else
			{
#ifndef __linux__
				transform(inp.begin(), inp.end(), ret.begin(), tolower);
#else
				loop(ret);
#endif
			}
			return ret;
		}

		char toLowercase(char & inp, bool changeArg)				//Coverts 'inp' to lowercase.  USES POINTERS TO CHANGE ARGUMENT VALUES WHEN 'changeArg' IS TRUE
		{
			char ret;
			if(changeArg)
			{
				inp = tolower(inp);
				ret = inp;
			}
			else
			{
				ret = inp;
				ret = tolower(ret);
			}
			return ret;
		}


		string toUppercase(string & inp, bool changeArg)		//Coverts 'inp' to uppercase.  USES POINTERS TO CHANGE ARGUMENT VALUES WHEN 'changeArg' IS TRUE
		{
#ifdef __linux__
				auto loop = [](string & value)
			{
				for(unsigned i = 0; i < value.length(); i++)
				{
					value[i] = toupper(value[i]);
				}
			};
#endif
			string ret;
			if(changeArg)
			{
#ifndef __linux__
				transform(inp.begin(), inp.end(), inp.begin(), toupper);
#else
				loop(inp);
#endif
				return inp;
			}
			else
			{
#ifndef __linux__
				transform(inp.begin(), inp.end(), ret.begin(), toupper);
#else
				ret = inp;
				loop(ret);

#endif
			}
			return ret;
		}

		char toUppercase(char & inp, bool changeArg)				//Coverts 'inp' to uppercase.  USES POINTERS TO CHANGE ARGUMENT VALUES WHEN 'changeArg' IS TRUE
		{
			char ret;
			if(changeArg)
			{
				inp = toupper(inp);
				ret = inp;
			}
			else
			{
				ret = inp;
				ret = toupper(ret);
			}
			return ret;
		}


		bool isNum(string inp)
		{
			convert.clear();
			convert << inp;
			convert >> floatOut;
			if(convert.fail())
			{
				convert.clear();
				return false;
			}
			else
			{
				convert.clear();
				return true;
			}
		}

		bool isNum(char inp)
		{
			convert.clear();
			convert << inp;
			convert >> floatOut;
			if(convert.fail())
			{
				convert.clear();
				return false;
			}
			else
			{
				convert.clear();
				return true;
			}
		}


		double toNum(string inp)
		{
			convert.clear();
			convert << inp;
			convert >> doubleOut;
			if(convert.fail()) throw convertError::convertFailed;
			convert.clear();
			return doubleOut;
		}

		double toNum(char inp)
		{
			convert.clear();
			convert << inp;
			convert >> doubleOut;
			if(convert.fail()) throw convertError::convertFailed;
			convert.clear();
			return doubleOut;
		}

		string toHex(unsigned value)
		{
			//Borrowed in part from https://proprogramming.org/program-to-convert-decimal-to-hexadecimal-c/
			long int decimalNumber, remainder, quotient;
			int i = 1, j, temp;
			char hexadecimalNumber[100];

			quotient = value;

			while(quotient != 0)
			{
				temp = quotient % 16;

				//To convert integer into character
				if(temp < 10)
					temp = temp + 48;
				else
					temp = temp + 55;

				hexadecimalNumber[i++] = temp;
				quotient = quotient / 16;
			}

			//End of borrowed code

			//Convert the hex to a string
			string ret = "";
			//q starts at 1 because the array of 'hex' characters starts at 1, for unknown reasons.  I assume it's just a mistake on the original coder's part?
			for(unsigned q = 1; q < i; q++)
			{
				ret += char(hexadecimalNumber[q]);
			}
			return ret;
		}


		bool isBool(string inp)
		{
			if(inp == "true" || inp == "false") return true;
			else return false;
		}


		bool toBool(string inp)
		{
			if(inp == "true") return true;
			else if(inp == "false") return false;
			else return false;
		}

		bool toBool(double inp)
		{
			if(inp == 1) return true;
			else if(inp == 0) return false;
			else return false;
		}


#ifdef ZLIB_USING_CINDER
		var::coord2 toCoord2(glm::highp_vec2 coordinate)
		{
			return var::coord2(coordinate.x, coordinate.y);
		}
#endif


		double toDegrees(double radians)
		{
			return radians * 180 / math::pi;
		}

		double toRadians(double degrees)
		{
			return degrees * math::pi / 180;
		}
	}
}