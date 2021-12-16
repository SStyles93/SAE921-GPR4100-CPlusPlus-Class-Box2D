#include "userData.h"

#pragma region CONSTRUCTOR

UserData::UserData()
{
	m_type = UserDataType::NONE;
}
UserData::UserData(UserDataType type_) : m_type(type_)
{
	m_localId = -1;
}

#pragma endregion
#pragma region GETTER/SETTER

UserDataType UserData::getUserDataType()
{
	return m_type;
}
void UserData::setLocalId(signed long id_)
{
	m_localId = id_;
}
signed long UserData::getLocalId()
{
	return m_localId;
}

#pragma endregion

const std::string UserData::UserDataTypeToString(UserDataType type_)
{

	switch (type_)
	{
	case UserDataType::TRAIL:
		return "TRAIL";
		break;
	case UserDataType::ROCKET:
		return "ROCKET";
		break;
	case UserDataType::LIMIT:
		return "LIMIT";
		break;
	case UserDataType::NONE:
		return "NONE";
		break;
	default:
		break;
	}
}

