/*=======================================================
 Copyright (c) Peter Vasil, 2011
=======================================================*/

#ifndef _FILE_IMPORTER_H_
#define _FILE_IMPORTER_H_

#include "includes.h"
#include "MainComponent.h"

class FileImporter : public ThreadWithProgressWindow
{
public:
	FileImporter(const String& dbPath, const File& xmlFile, int user, bool checkMd5, bool checkDuplicate);
	FileImporter(const String& dbPath, const std::vector<File>& xmlFiles, int user, bool checkMd5, bool checkDuplicate);
	~FileImporter();

	void run();
	void setXmlFile(const File& xmlFile);
	const String& getStatus() const;
private:

//	int findLocation(const std::vector<GpsLocation>& locations, const double lon, const double lat);
//	bool isInCircle(const double centreX,
//					const double centreY,
//					const double radius,
//					const double lon,
//					const double lat);
	File m_xmlFile;
	std::vector<File> m_xmlFiles;
	String m_dbPath;
	String m_status;
	int m_user;
	bool m_checkMd5;
	bool m_checkDuplicate;
};

#endif // _FILE_IMPORTER_H_
