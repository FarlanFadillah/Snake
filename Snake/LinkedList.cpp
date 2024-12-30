#include "LinkedList.h"

LinkedList::LinkedList()
{
	header = std::make_shared<Node>(Vec2(), nullptr, nullptr);
	trailer = std::make_shared<Node>(Vec2(), header, nullptr);
	header->setNext(trailer);
}

const size_t& LinkedList::size()
{
	return m_size;
}

bool LinkedList::isEmpty()
{
	return m_size <= 0;
}

std::shared_ptr<Node>& LinkedList::first()
{
	//if (isEmpty()) return header;
	return header->getNext();
}

std::shared_ptr<Node>& LinkedList::last()
{
	//if (isEmpty()) return trailer;
	return trailer->getPrev();
}

void LinkedList::addFirst(const Vec2& data)
{
	addBetween(data, header, header->getNext());
}

void LinkedList::addLast(const Vec2& data)
{
	addBetween(data, trailer->getPrev(), trailer);
}

const Vec2& LinkedList::removeFirst()
{
	if (isEmpty()) return Vec2();
	return remove(header->getNext());
}

const Vec2& LinkedList::removeLast()
{
	if (isEmpty()) return Vec2();
	return remove(trailer->getPrev());
}



void LinkedList::addBetween(const Vec2& data, const std::shared_ptr<Node> predecessor, const std::shared_ptr<Node> successor)
{
	auto newNode = std::make_shared<Node>(data, predecessor, successor);
	predecessor->setNext(newNode);
	successor->setPrev(newNode);
	m_size++;
}

const Vec2& LinkedList::remove(std::shared_ptr<Node> node)
{
	auto pred = node->getPrev();
	auto succ = node->getNext();

	pred->setNext(succ);
	succ->setNext(pred);
	m_size--;
	return node->getElement();
}
