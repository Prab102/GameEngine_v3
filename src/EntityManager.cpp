#include "EntityManager.h"
#include <iostream>
#include <algorithm>


EntityManager::EntityManager(){}

void EntityManager::removeDeadEntities(EntityVec & vec)
{
    std::vector<std::shared_ptr<Entity>> bin2;
    EntityVec bin;

    for(auto e: vec){

        // std::remove_if(vec.begin(),vec.end(),e);
        if(!e->isActive())
        {
             bin.push_back(e);
        }
    }
    for(auto del :bin){
         std::vector<std::shared_ptr<Entity>>::iterator it;
         it = std::find(vec.begin(),vec.end(),del);

            if(it != vec.end()){
                vec.erase(it);
            }
    }
}
//updates after iteration so no iterator invalidation occurs
void EntityManager::update()
{
    // EntityVec  map_entities;
    for(auto e : m_entitiesToAdd){
        m_entities.push_back(e);

        if(m_entityMap.find(e->tag()) != m_entityMap.end()){
            //adds an entity if the map already has a spot for the entities
            m_entityMap[e->tag()].push_back(e);

        }
        else{
            //creates a key value pair in entitymap to store entity vectors
            m_entityMap[e->tag()] = EntityVec();
        }

    }

    m_entitiesToAdd.clear();

    removeDeadEntities(m_entities);

    for(auto& [tag,entityVec] : m_entityMap){
        removeDeadEntities(entityVec);
    }

}
//creates entities with a given tag
std::shared_ptr<Entity> EntityManager::addEntity(const std::string & tag)
{    
    auto entity = std::shared_ptr<Entity>(new Entity(m_totalEntities++,tag));
    m_entitiesToAdd.push_back(entity);
    return entity;
}

//gets all entities
const EntityVec & EntityManager::getEntities()
{
    return m_entities;
}
//gets all entities with a given tag
const EntityVec & EntityManager::getEntities(const std::string & tag)
{
    return m_entityMap[tag];
}

const EntityMap & EntityManager::getEntityMap()
{
    return m_entityMap;
}