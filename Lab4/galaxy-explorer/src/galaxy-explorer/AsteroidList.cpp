#include <galaxy-explorer/AsteroidList.hpp>


AsteroidListItem::AsteroidListItem() {
	this->next = nullptr;
	this->data = nullptr;
}

AsteroidListItem::AsteroidListItem(Asteroid a) {
	this->next = nullptr;
	this->data = &a;
}

AsteroidListItem::~AsteroidListItem() {
    delete data;
    delete next; // Not sure about this
}

AsteroidList::AsteroidList()
{
    //head = AsteroidListItem();
}

AsteroidList::AsteroidList(const AsteroidList& src)
{
    AsteroidListItem * current = (AsteroidListItem *)src.head.getNext();
    AsteroidListItem * saver = & head;
    AsteroidListItem * newNext;
    Asteroid * tmp;
    while(current->hasNext())
    {
        tmp = new Asteroid(current->getData());
        newNext = new AsteroidListItem(*tmp);
        saver->setNext(newNext);
        saver = newNext;
        
        current = current->getNext();
        
    }
    
	// The functions in this class are listed in a suggested order of implementation,
	// except for this one and the destructor (because you should put all your constructors together).
}

AsteroidList::~AsteroidList() {
    AsteroidListItem * current;
    if(head.hasNext())
    {
        current = head.getNext();
        delete current;
    }
	// The functions in this class are listed in a suggested order of implementation,
	// except for this one and the copy constructor (because you should put all your constructors together).
}

void AsteroidList::pushFront(Asteroid e) {
    AsteroidListItem * newItem = new AsteroidListItem(e);
    newItem->setNext(head.getNext());
    head.setNext(newItem);
}

Asteroid& AsteroidList::front() {
	return *(Asteroid*)&head.getNext()->getData();
}

const Asteroid& AsteroidList::front() const {
	return *(const Asteroid*)&head.getNext()->getData();
}

bool AsteroidList::isEmpty() const {
	return !head.hasNext();
}

int AsteroidList::size() const {
    int sz = 0 ; 
    AsteroidListItem * current = (AsteroidListItem *)head.getNext();
    while (current != nullptr)
    {
        current = current->getNext();
        sz++;
    }
    return sz;
}

AsteroidListItem* AsteroidList::beforeBegin() {
	return nullptr;
}

const AsteroidListItem* AsteroidList::beforeBegin() const {
	return nullptr;
}

AsteroidListItem* AsteroidList::begin() {
	return nullptr;
}

const AsteroidListItem* AsteroidList::begin() const {
	return nullptr;
}

AsteroidListItem* AsteroidList::beforeEnd() {
	return nullptr;
}

const AsteroidListItem* AsteroidList::beforeEnd() const {
	return nullptr;
}

AsteroidListItem* AsteroidList::end() {
	return nullptr;
}

const AsteroidListItem* AsteroidList::end() const {
	return nullptr;
}

AsteroidListItem* AsteroidList::insertAfter(AsteroidListItem* prev, Asteroid e) {
	return nullptr;
}

AsteroidListItem* AsteroidList::insertAfter(AsteroidListItem* prev, const AsteroidList& others) {
	return nullptr;
}

AsteroidListItem* AsteroidList::eraseAfter(AsteroidListItem* prev) {
	return nullptr;
}

void AsteroidList::clear() {
}

AsteroidList& AsteroidList::operator=(const AsteroidList& src) {
	return *(AsteroidList*)nullptr;
}
