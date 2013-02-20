//
// BSONReader.h
//
// $Id$
//
// Library: MongoDB
// Package: MongoDB
// Module:  BSONReader
//
// Definition of the BSONReader class.
//
// Copyright (c) 2012, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
//
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//

#ifndef _MongoDB_BSONReader_included
#define _MongoDB_BSONReader_included

#include "Poco/MongoDB/MongoDB.h"
#include "Poco/BinaryReader.h"

namespace Poco {
namespace MongoDB {

class MongoDB_API BSONReader
	/// Class for reading BSON from a Poco::BinaryReader
{
public:
	BSONReader(const Poco::BinaryReader& reader) : _reader(reader)
		/// Constructor
	{
	}

	virtual ~BSONReader()
		/// Destructor
	{
	}

	template<typename T>
	void read(T& t)
		/// Reads the value from the reader. The default implementation uses the >> operator to
		/// the given argument. Special types can write their own version.
	{
		_reader >> t;
	}

	std::string readCString();
		/// Reads a cstring from the reader.
		/// A cstring is a string terminated with a 0x00.

private:

	Poco::BinaryReader _reader;
};

inline std::string BSONReader::readCString()
{
	std::string val;
	while(_reader.good())
	{
		char c;
		_reader >> c;
		if ( _reader.good() )
		{
			if (c == 0x00)
			{
				return val;
			}
			else
			{
				val += c;
			}
		}
	}
	return val;
}


}} // Namespace Poco::MongoDB

#endif //  _MongoDB_BSONReader_included