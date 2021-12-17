#pragma once

#include <string>

enum class UserDataType : char
{
    ROCKET = 'r',
    TRAIL = 't',
    LIMIT = 'l',
    NONE = 'n'
};

class UserData
{
public:

#pragma region CONSTRUCTOR

    UserData();
    UserData(UserDataType type_);

#pragma endregion
#pragma region GETTER/SETTER

    UserDataType getUserDataType();
    signed long getLocalId();
    void setLocalId(signed long id_);

#pragma endregion
    
    //static const std::string UserDataTypeToString(UserDataType type_);

private:
    UserDataType m_type;
    signed long m_localId = -1;

};
