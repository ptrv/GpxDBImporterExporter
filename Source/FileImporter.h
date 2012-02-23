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
	FileImporter(const String& dbPath, const File& xmlFile, int user,
			bool checkMd5, bool checkDuplicate, const char boundingsType);
	FileImporter(const String& dbPath, const Array<File>& xmlFiles, int user,
			bool checkMd5, bool checkDuplicate, const char boundingsType);
	~FileImporter();

	void run();
	void setXmlFile(const File& xmlFile);
	const String& getStatus() const;
private:

	File m_xmlFile;
	Array<File> m_xmlFiles;
	String m_dbPath;
	String m_status;
	int m_user;
	bool m_checkMd5;
	bool m_checkDuplicate;
	char m_boundingsType;
};

#endif // _FILE_IMPORTER_H_
