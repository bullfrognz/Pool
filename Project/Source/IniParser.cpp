//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   IniParser.cpp
//  Description :   Template for implementation (source) files
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

// Library Includes
#include <iostream>

// Local Includes

// This Include
#include "IniParser.h"

// Static Variables

// Static Function Prototypes

// Implementation

CIniParser::CIniParser()
{
	//Empty
}

CIniParser::~CIniParser()
{
	//m_FileStream.close();
}

void Trim(std::string& _string)
{
	while(true)
	{
		size_t WhiteSpacePos = _string.find(' ');
		
		if (WhiteSpacePos == std::string::npos)
		{
			WhiteSpacePos = _string.find('\t');
		}

		if (WhiteSpacePos != std::string::npos)
		{
			_string.erase( WhiteSpacePos , 1 );
			continue;
		}
		
		break;
	}
}

void ConvertLowerCase(std::string& _string)
{
	size_t stringLength = _string.length();

	for (size_t i = 0; i < stringLength; ++i)
	{
		if (_string[i] >= 'A' && _string[i] <= 'Z')
		{
			_string[i] = _string[i] + 32;
		}
	}
}

//std::queue<std::string> EmptyQueue;
bool
CIniParser::LoadIniFile(const char* _pcFileName)
{
	m_StrFileName = _pcFileName;

	m_FileStream.open( m_StrFileName );

	if (m_FileStream.is_open()) //File Opened
	{
		std::string strLine;
		std::string strGroup;

		std::map<std::string, std::string> mapGroupData;
		std::vector<std::string> vecGroupComments;
		
		while (!m_FileStream.eof())
		{	
			getline( m_FileStream , strLine );

			size_t CommentChar     = strLine.find( ';' );
			size_t BracketStartPos = strLine.find( '[' );
			size_t BracketEndPos   = strLine.find( ']' );
			size_t EqualPos        = strLine.find( '=' );

			if (CommentChar == 0)
			{
				vecGroupComments.push_back(strLine);
			}
			else if (BracketStartPos == 0 && BracketEndPos != std::string::npos) //Is Section
			{
				strGroup = strLine.substr( BracketStartPos + 1 , BracketEndPos -1 );

				InsertGroupComments(strGroup, vecGroupComments);
				vecGroupComments.clear();
			}
			else if (EqualPos != std::string::npos) //Is Data Field
			{
				std::string strKey	 = strLine.substr( 0 , EqualPos );
				std::string strValue = strLine.substr( EqualPos + 1, strLine.length() );
				
				InsertGroupData(strGroup, strKey, strValue);

				InsertGroupComments(strKey, vecGroupComments);
				vecGroupComments.clear();
			}
		}
	
		return true;
	}

	return false;
}

void
CIniParser::InsertGroupComments(std::string strOwner, std::vector<std::string> vecComments)
{
	Trim(strOwner);

	m_IniComments.insert( std::pair<std::string , std::vector<std::string> >(strOwner, vecComments) );
}

void
CIniParser::InsertGroupData(std::string strGroup, std::string strKey, std::string strValue)
{
	Trim(strKey);
	Trim(strValue);

	std::map< std::string , std::map<std::string,std::string> >::iterator IterGroup;
	IterGroup = m_IniData.find(strGroup);

	if (IterGroup == m_IniData.end())
	{
		std::map<std::string, std::string> mapValues;

		mapValues.insert( std::pair<std::string, std::string>(strKey, strValue) );

		m_IniData.insert( std::pair< std::string , std::map<std::string,std::string> >(strGroup, mapValues) );
	}
	else
	{
		m_IniData[strGroup].insert( std::pair<std::string, std::string>(strKey, strValue) );
	}
}


bool
CIniParser::AddValue(const char* _pcGroup, const char* _pcKey, const char* _pcValue)
{
	std::string strSection = _pcGroup;
	std::string strKey     = _pcKey;
	std::string strValue   = _pcValue;

	Trim(strSection);
	Trim(strKey);
	Trim(strValue);

	std::map< std::string , std::map<std::string,std::string> >::iterator IterData;
	IterData = m_IniData.find(strSection);

	if (IterData == m_IniData.end())
	{
		std::map<std::string,std::string> mapKeyData;
		mapKeyData.insert( std::pair<std::string, std::string>(strKey, strValue) );

		m_IniData.insert( std::pair< std::string , std::map<std::string,std::string> >(strSection, mapKeyData) );
	}
	else
	{
		m_IniData[strSection].insert( std::pair<std::string, std::string>(strKey, strValue) );
	}

	return (true);
}

bool
CIniParser::AddValue(const char* _pcSection, const char* _pcKey, const int _kiValue)
{
	char cBuffer[32];

	sprintf_s(cBuffer, 32, "%d", _kiValue);

	AddValue(_pcSection, _pcKey, cBuffer);

	return (true);
}

bool
CIniParser::CloseFile(bool _bSave)
{
	if (_bSave == true)
	{
		m_FileStream.clear();
		m_FileStream.close();
		m_FileStream.open(m_StrFileName, std::ios::out);
		m_FileStream.seekp(0);

		std::map< std::string , std::map<std::string,std::string> >::iterator IterGroups;
		std::map<std::string,std::string> mapKeyData;
		std::map<std::string,std::string>::iterator IterKeyData;

		std::map< std::string , std::vector<std::string> >::iterator IterComments;
		std::vector<std::string> vecComments;

		for (IterGroups = m_IniData.begin(); IterGroups != m_IniData.end(); ++ IterGroups)
		{
			std::string strGroup = (*IterGroups).first;
			
			IterComments = m_IniComments.find(strGroup);
			if (IterComments != m_IniComments.end())
			{
				vecComments = (*IterComments).second;

				while (!vecComments.empty())
				{
					m_FileStream << vecComments.front() << std::endl;
					vecComments.erase(vecComments.begin());
				}
			}

			m_FileStream << std::endl;
			m_FileStream << "[" << (*IterGroups).first << "]" << std::endl;
			m_FileStream << std::endl;

			mapKeyData = (*IterGroups).second;

			for (IterKeyData = mapKeyData.begin(); IterKeyData != mapKeyData.end(); ++ IterKeyData)
			{
				std::string strKey = (*IterKeyData).first;

				IterComments = m_IniComments.find(strKey);
				if (IterComments != m_IniComments.end())
				{
					vecComments = (*IterComments).second;

					while (!vecComments.empty())
					{
						m_FileStream << vecComments.front() << std::endl;
						vecComments.erase(vecComments.begin());
					}
				}

				m_FileStream << strKey << "\t= " << (*IterKeyData).second << std::endl;
			}
		}
		
	}

	m_FileStream.close();
	return true;
}


bool
CIniParser::GetValue(const char* _pcSelection, const char* _pcKey, std::string& _rstringValue)
{
	if (DoesDataExist(_pcSelection,_pcKey) == false)
	{
		return false;
	}

	_rstringValue = m_IniData[_pcSelection][_pcKey];

	return true;
}


bool
CIniParser::GetValue(const char* _pcSelection, const char* _pcKey, int& _riValue)
{
	if (DoesDataExist(_pcSelection,_pcKey) == false)
	{
		return false;
	}

	_riValue = atoi(m_IniData[_pcSelection][_pcKey].c_str());

	return true;
}


bool
CIniParser::GetValue(const char* _pcSelection, const char* _pcKey, float& _rfValue)
{
	if (DoesDataExist(_pcSelection,_pcKey) == false)
	{
		return false;
	}

	_rfValue = static_cast<float>(atof(m_IniData[_pcSelection][_pcKey].c_str()));

	return true;
}


bool
CIniParser::GetValue(const char* _pcSelection, const char* _pcKey, bool& _rbValue)
{
	if (DoesDataExist(_pcSelection,_pcKey) == false)
	{
		return false;
	}

	std::string strData = m_IniData[_pcSelection][_pcKey];

	ConvertLowerCase(strData);

	if (strData == "true" || strData == "on" || strData == "yes" || strData == "1" )
	{
		_rbValue = true;
		return true;
	}

	_rbValue = false;
	return false;
}

bool
CIniParser::DoesDataExist(const char* _kcSectionName, const char* _kcFieldName)
{
	std::map<std::string, std::map<std::string,std::string> >::iterator Iter;

	Iter = m_IniData.find(_kcSectionName);

	if (Iter != m_IniData.end())
	{
		std::map<std::string,std::string>::iterator Iter2;

		Iter2 = (Iter->second).find(_kcFieldName);

		if (Iter2 != Iter->second.end())
		{
			return (true);
		}
		else
		{
			return (false);
		}
	}

	return (false);
}