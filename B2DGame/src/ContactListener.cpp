#include "ContactListener.h"

#include <iostream>

#include "game.h"
#include "UserData.h"


ContactListener::ContactListener(Game& game) : m_game(game)
{

}

void ContactListener::BeginContact(b2Contact* contact)
{
    //std::cout << "Contact Begin!" << std::endl;

    UserData* A_Data = reinterpret_cast<UserData*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
    UserData* B_Data = reinterpret_cast<UserData*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);

    //std::cout << "A Fixture : " << UserData::UserDataTypeToString(A_Data->getUserDataType()) << ":[id=" << A_Data->getLocalId() << "]" << std::endl;
    //std::cout << "B Fixture : " << UserData::UserDataTypeToString(B_Data->getUserDataType()) << ":[id=" << B_Data->getLocalId() << "]" << std::endl;

    if (A_Data->getUserDataType() == UserDataType::TRAIL || B_Data->getUserDataType() == UserDataType::TRAIL)
    {

        if (B_Data->getUserDataType() == UserDataType::ROCKET || A_Data->getUserDataType() == UserDataType::ROCKET)
        {
            if (A_Data->getUserDataType() == UserDataType::TRAIL)
            {
                m_game.DestroyTrail(A_Data->getLocalId());
            }
            else
            {
                m_game.DestroyTrail(B_Data->getLocalId());
            }
        }
        if (B_Data->getUserDataType() == UserDataType::LIMIT || A_Data->getUserDataType() == UserDataType::LIMIT)
        {
            //m_game.DestroyTrail(A_Data->getLocalId());
        }
    }

}

void ContactListener::EndContact(b2Contact* contact)
{
    //std::cout << "Contact End!" << std::endl;

    UserData* A_Data = reinterpret_cast<UserData*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
    UserData* B_Data = reinterpret_cast<UserData*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);

    //std::cout << "A Fixture : " << UserData::UserDataTypeToString(A_Data->getUserDataType()) << ":[id=" << A_Data->getLocalId() << "]" << std::endl;
    //std::cout << "B Fixture : " << UserData::UserDataTypeToString(B_Data->getUserDataType()) << ":[id=" << B_Data->getLocalId() << "]" << std::endl;

    if (A_Data->getUserDataType() == UserDataType::TRAIL || B_Data->getUserDataType() == UserDataType::TRAIL)
    {
        if (B_Data->getUserDataType() == UserDataType::ROCKET || A_Data->getUserDataType() == UserDataType::ROCKET)
        {
            m_game.SetDamageToRocket(5);
            std::cout << "Rocket lost 5 health" << std::endl;
            
        }
    }
}
