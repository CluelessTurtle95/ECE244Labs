#include <galaxy-explorer/AsteroidList.hpp>


AsteroidListItem::AsteroidListItem() {
	this->next = nullptr;
	this->data = nullptr;
}

AsteroidListItem::AsteroidListItem(Asteroid a) {
    this->next = nullptr;
    this->data = new Asteroid(a);
}

AsteroidListItem::~AsteroidListItem() {
    delete data;
}

AsteroidList::AsteroidList()
{
    head.setNext(nullptr);
}

AsteroidList::AsteroidList(const AsteroidList& src)
{
    const AsteroidListItem * current = src.begin();
    AsteroidListItem * saver = beforeBegin();
    AsteroidListItem * newNext;
    Asteroid * tmp;
    while(current != nullptr)
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
    clear();
	// The functions in this class are listed in a suggested order of implementation,
	// except for this one and the copy constructor (because you should put all your constructors together).
}

void AsteroidList::pushFront(Asteroid e) {
    AsteroidListItem * newItem = new AsteroidListItem(e);
    newItem->setNext(head.getNext());
    beforeBegin()->setNext(newItem);
}

Asteroid& AsteroidList::front() {
	return  (begin()->getData());
}

const Asteroid& AsteroidList::front() const {
	return  (begin()->getData());
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
	return &head;
}

const AsteroidListItem* AsteroidList::beforeBegin() const {
	return &head;
}

AsteroidListItem* AsteroidList::begin() {
	return head.getNext();
}

const AsteroidListItem* AsteroidList::begin() const {
	return head.getNext();
}

AsteroidListItem* AsteroidList::beforeEnd() {
    int sz = size();
    AsteroidListItem * current = (AsteroidListItem *)&head;
    for(int i = 0 ;i < sz ; i++)
        current = current->getNext();
    return current;
}

const AsteroidListItem* AsteroidList::beforeEnd() const {
    int sz = size();
    AsteroidListItem * current = (AsteroidListItem *)&head;
    for(int i = 0 ;i < sz ; i++)
        current = current->getNext();
    return current;
}

AsteroidListItem* AsteroidList::end() {
	return nullptr;
}

const AsteroidListItem* AsteroidList::end() const {
	return nullptr;
}

AsteroidListItem* AsteroidList::insertAfter(AsteroidListItem* prev, Asteroid e) {
    AsteroidListItem * saver = prev->getNext();
    AsteroidListItem * p = new AsteroidListItem(e);
    prev->setNext(p);
    p->setNext(saver);
    return p;
}

AsteroidListItem* AsteroidList::insertAfter(AsteroidListItem* prev, const AsteroidList& others) {
    AsteroidList* newCopies = new AsteroidList(others);
    AsteroidListItem* firstnew = newCopies->begin();
    if (firstnew == nullptr)
        return prev;
    AsteroidListItem * saver = prev->getNext();
    AsteroidListItem* lastnew = firstnew;
    
    prev->setNext(firstnew);
    while(lastnew->getNext() != nullptr)
        lastnew = lastnew->getNext();
    lastnew->setNext(saver);
    return lastnew;
}

AsteroidListItem* AsteroidList::eraseAfter(AsteroidListItem* prev) {
    AsteroidListItem * saver = prev->getNext();
    prev->setNext(prev->getNext()->getNext());
    delete saver;
    return prev->getNext();
}

void AsteroidList::clear() {
    AsteroidListItem * current = begin();
    AsteroidListItem * tmp = nullptr;
    while(current != nullptr)
    {
        tmp = current;
        current = current->getNext();
        delete tmp;
    }
    head.setNext(nullptr);
}

AsteroidList& AsteroidList::operator=(const AsteroidList& src) {
    if(this==&src) 
        return *this;
    clear();
    insertAfter(&head, src);
    return *this;
}
