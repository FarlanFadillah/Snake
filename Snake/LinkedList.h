#pragma once
#include "Node.h"
class LinkedList
{
private:
	std::shared_ptr<Node> header;
	std::shared_ptr<Node> trailer;
	size_t					m_size = 0;
	
	void addBetween(const Vec2& data, const std::shared_ptr<Node> predecessor, const std::shared_ptr<Node> successor);
	const Vec2& remove(std::shared_ptr<Node> node);
public:
	LinkedList();

	const size_t& size();
	bool isEmpty();
	std::shared_ptr<Node>& first();
	std::shared_ptr<Node>& last();
	void addFirst(const Vec2& data);
	void addLast(const Vec2& data);
	const Vec2& removeFirst();
	const Vec2& removeLast();

};

