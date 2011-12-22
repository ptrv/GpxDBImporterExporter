/*=======================================================
 Copyright (c) Peter Vasil, 2011
 =======================================================*/

#include "FileImporter.h"
#include "Data.h"
#include "DBConnector.h"
#include "HelperFunctions.h"

FileImporter::FileImporter(const String& dbPath, const File& xmlFile, int user, bool checkMd5, bool checkDuplicate)
:
ThreadWithProgressWindow("GPX Import", true, false),
m_xmlFile(xmlFile),
m_dbPath(dbPath),
m_user(user),
m_checkMd5(checkMd5),
m_checkDuplicate(checkDuplicate)
{
}

FileImporter::FileImporter(const String& dbPath, const std::vector<File>& xmlFiles, int user, bool checkMd5, bool checkDuplicate)
:
ThreadWithProgressWindow("GPX Import", true, false),
m_xmlFile(String::empty),
m_xmlFiles(xmlFiles),
m_dbPath(dbPath),
m_user(user),
m_checkMd5(checkMd5),
m_checkDuplicate(checkDuplicate)
{
}

FileImporter::~FileImporter()
{
}

void FileImporter::setXmlFile(const File& xmlFile)
{
	m_xmlFile = xmlFile;
}

const String& FileImporter::getStatus() const
{
	return m_status;
}

void FileImporter::run()
{
    for(unsigned int fileNum = 0; fileNum < m_xmlFiles.size(); ++fileNum)
    {
	XmlDocument* xmlDoc = new XmlDocument(m_xmlFiles[fileNum]);
	XmlElement* xmlRootElem = xmlDoc->getDocumentElement();
	setProgress(0.0);
	if (xmlRootElem != NULL)
	{
		std::vector<GpsData> gpsDataVec;
		DBConnector* dbCon = new DBConnector(m_dbPath);
		dbCon->setupDbConnection();
		int lastFileId = -1;
		if (!dbCon->getLastId(lastFileId, "file"))
		{
			std::cout << "lastFileId = " << lastFileId << std::endl;
		}
		++lastFileId;
		MD5 md5hash(m_xmlFiles[fileNum]);
		DBG_VAL(md5hash.toHexString());
		bool res;
		DBG_VAL(m_checkMd5);
		if (m_checkMd5)
		{
			res = dbCon->checkIfFileExists(md5hash.toHexString());
		}
		else
		{
			res = false;
		}
		if (!res)
		{
			dbCon->insertFileName(lastFileId, m_xmlFiles[fileNum].getFileName(), md5hash.toHexString());

			int progressNumMax = 0;
			int numTrk = 0;

			setStatusMessage("Parsing XML file...");
			forEachXmlChildElementWithTagName(*xmlRootElem, child, "trk")
			{
				forEachXmlChildElementWithTagName(*child, subchild, "trkseg")
				{
					forEachXmlChildElementWithTagName(*subchild, subsubchild, "trkpt")
					{
						++progressNumMax;
					}
				}
			}
			double progressNum = 1.0/progressNumMax;
			int gpsdataid = -1;
			dbCon->getLastId(gpsdataid, "gpsdata");
			int segment = 0;
			dbCon->getLastSegmentId(segment, m_user);
			DBG_VAL(segment);
			// -----------------------------------------------------------------------------
			// get locations from database
			// -----------------------------------------------------------------------------
			std::vector<GpsLocation> locations;
			dbCon->getGpsLocations(locations);
			// -----------------------------------------------------------------------------
			forEachXmlChildElementWithTagName(*xmlRootElem, child, "trk")
			{
				forEachXmlChildElementWithTagName(*child, subchild, "trkseg")
				{
					++segment;
					forEachXmlChildElementWithTagName(*subchild, subsubchild, "trkpt")
					{
						GpsData gpsData;

						++gpsdataid;

						double lat = subsubchild->getDoubleAttribute("lat");
						double lon = subsubchild->getDoubleAttribute("lon");
						double ele = (subsubchild->getChildElementAllSubText("ele", "0.0")).getDoubleValue();
						String trkpttime = subsubchild->getChildElementAllSubText("time", String::empty);
						++numTrk;
						int loc = Helper::findLocation(locations, lon, lat);

						gpsData.setGpsData(gpsdataid,
										   (float)lat,
										   (float)lon,
										   trkpttime,
										   ele,
										   segment,
										   m_user,
										   lastFileId,
										   (loc == 0 ? 1: loc));

						gpsDataVec.push_back(gpsData);

						setProgress(progressNum * numTrk);
					}
				}
			}
			dbCon->beginTransaction();
			setStatusMessage("Inserting into database...");
			setProgress(0.0);
			int gpsVecSize = gpsDataVec.size();
			for (int i = 0; i < gpsVecSize; ++i) {
				if (m_checkDuplicate)
				{
					if (!dbCon->checkIfGpsDataExsist(gpsDataVec[i].getTime(), gpsDataVec[i].getUser()))
					{
						dbCon->insertGpsData(gpsDataVec[i]);
					}
				}
				else
				{
					dbCon->insertGpsData(gpsDataVec[i]);
				}
				setProgress( (double)i / gpsVecSize);
			}
			dbCon->commitTransaction();
			m_status = String::empty;
			m_status << "File imported: " << m_xmlFile.getFileName() << " !";
		}
		else
		{
			m_status = "File already exists!";
		}
		dbCon->closeDbConnection();
	}
	delete xmlRootElem;
	delete xmlDoc;
    }
}
