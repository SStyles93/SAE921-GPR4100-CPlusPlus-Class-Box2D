#include "game.h"
#include "Managers/contactListener.h"
#include "Managers/userData.h"


ContactListener::ContactListener(Game& game) : m_game(game)
{

}

void ContactListener::BeginContact(b2Contact* contact)
{

    UserData* A_Data = reinterpret_cast<UserData*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
    UserData* B_Data = reinterpret_cast<UserData*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);

    //Gets the UserData and compares it to the second one
    if (A_Data->getUserDataType() == UserDataType::TRAIL || B_Data->getUserDataType() == UserDataType::TRAIL)
    {

        if (B_Data->getUserDataType() == UserDataType::ROCKET || A_Data->getUserDataType() == UserDataType::ROCKET)
        {
            if (A_Data->getUserDataType() == UserDataType::TRAIL || B_Data->getUserDataType() == UserDataType::TRAIL)
            {
                m_game.DestroyTrail(A_Data->getLocalId());
            }
        }
        if (B_Data->getUserDataType() == UserDataType::LIMIT || A_Data->getUserDataType() == UserDataType::LIMIT)
        {
            m_game.DestroyTrail(A_Data->getLocalId());
            m_game.DestroyTrail(B_Data->getLocalId());
        }
    }
}

void ContactListener::EndContact(b2Contact* contact)
{
    UserData* A_Data = reinterpret_cast<UserData*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
    UserData* B_Data = reinterpret_cast<UserData*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);

    if (A_Data->getUserDataType() == UserDataType::TRAIL || B_Data->getUserDataType() == UserDataType::TRAIL)
    {
        if (B_Data->getUserDataType() == UserDataType::ROCKET || A_Data->getUserDataType() == UserDataType::ROCKET)
        {
            m_game.SetDamageToRocket(25);
        }
    }
}
