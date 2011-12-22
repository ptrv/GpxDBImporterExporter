/*=======================================================
 Copyright (c) Peter Vasil, 2011
=======================================================*/

#ifndef _DATA_H_
#define _DATA_H_

class GpsData
{
	int gpsdataid;
	double latitude;
	double longitude;
	String time;
	double elevation;
	int segment;
	int user;
	int file;
	int location;

public:

	GpsData(){};
	~GpsData(){};

	const String getInsertList() const;

	void setGpsData(int gpsdataid_,
					double latitude_,
					double longitude_,
					String& time_,
					double elevation_,
					int segment_,
					int user_,
					int file_,
					int location_)
	{
		gpsdataid = gpsdataid_;
		latitude = latitude_;
		longitude = longitude_;
		time = time_;
		elevation = elevation_;
		segment = segment_;
		user = user_;
		file = file_;
		location = location_;
	}
	int getGpsDataId() const { return gpsdataid; }
	int getUser() const { return user; }
	const String& getTime() const { return time; }
	double getLatitude() const { return latitude; }
	double getLongitude() const { return longitude; }
	double getElevation() const { return elevation; }
	int getSegment() const { return segment; }
};

struct GpsLocation 
{
	int index;
	double longitude;
	double latitude;
	double radius;
	String city;
	String country;
};

struct GpsMinMax
{
	double minLat;
	double minLon;
	double maxLat;
	double maxLon;
};

#endif // _DATA_H_
