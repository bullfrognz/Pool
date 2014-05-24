//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   IniParser
//  Description :   Template for decoration (header) file
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

#pragma once

#ifndef __IGFEB11_IG220_INIPARSER_H__
#define __IGFEB11_IG220_INIPARSER_H__

// Library Includes
#include <map>
#include <vector>
#include <string>
#include <fstream>

// Local Includes

// Types

// Constants

// Prototypes


class CIniParser
{
    // Member Functions
public:
	 CIniParser();
	~CIniParser();

	bool LoadIniFile(const char* _pcFileName);

	void InsertGroupComments(std::string strGroup, std::vector<std::string> vecComments);
	void InsertGroupData(std::string strOwner, std::string strKey, std::string strValue);

	bool CloseFile(bool _bSave = true);

	bool AddValue(const char* _pcSection, const char* _pcKey, const char* _pcValue);
	bool AddValue(const char* _pcSection, const char* _pcKey, const int _kiValue);

	bool GetValue(const char* _pcSelection, const char* _pcKey, std::string& _rstringValue);
	bool GetValue(const char* _pcSelection, const char* _pcKey, int& _riValue);
	bool GetValue(const char* _pcSelection, const char* _pcKey, float& _rfValue);
	bool GetValue(const char* _pcSelection, const char* _pcKey, bool& _rbValue);

	bool DoesDataExist(const char* _kcSectionName, const char* _kcFieldName);

protected:

private:
	CIniParser(const CIniParser& _kr);
	CIniParser& operator= (const CIniParser& _kr);

    // Member Variables
public:

protected:

private:
	std::map< std::string , std::map<std::string,std::string> > m_IniData;
	std::map< std::string , std::vector<std::string> > m_IniComments;

	const char* m_StrFileName;
	std::fstream m_FileStream;

};

#endif // __IGFEB11_IG220_INIPARSER_H__
