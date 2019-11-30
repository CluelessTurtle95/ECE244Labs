/*
 * This file was developed for the Fall 2018 instance of ECE244 at the University of Toronto.
 * Creator: Matthew J. P. Walker
 */


#include <galaxy-explorer/AsteroidsObserver.hpp>

void AsteroidsObserver::onAsteroidInRange(Asteroid asteroid) {
    asteroid_list.insertAfter(asteroid_list.beforeEnd() , asteroid);
}

void AsteroidsObserver::onAsteroidUpdate(Asteroid asteroid) {
    AsteroidListItem * tmp = asteroid_list.begin();
    AsteroidListItem * before_tmp = asteroid_list.beforeBegin();
    while(tmp != nullptr)
    {
        if(tmp->getData().getID() == asteroid.getID())
        {
            asteroid_list.eraseAfter(before_tmp);
            asteroid_list.insertAfter(before_tmp, asteroid);
            break;
        }
        before_tmp = tmp;
        tmp = tmp->getNext();
    }
}

void AsteroidsObserver::onAsteroidOutOfRange(Asteroid asteroid) {
    AsteroidListItem * tmp = asteroid_list.begin();
    AsteroidListItem * before_tmp = asteroid_list.beforeBegin();
    while(tmp != nullptr)
    {
        if(tmp->getData().getID() == asteroid.getID())
        {
            asteroid_list.eraseAfter(before_tmp);
            break;
        }
        before_tmp = tmp;
        tmp = tmp->getNext();
    }
}

void AsteroidsObserver::onAsteroidDestroy(Asteroid asteroid) {
    onAsteroidOutOfRange(asteroid);
}
