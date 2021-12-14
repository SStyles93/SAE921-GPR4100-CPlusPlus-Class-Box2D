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
    UserData();
    UserData(UserDataType type_);

    static const std::string UserDataTypeToString(UserDataType type_);

    UserDataType getUserDataType();
    signed long getLocalId();
    void setLocalId(signed long id_);

private:
    UserDataType m_type;
    signed long m_localId = -1;

};
