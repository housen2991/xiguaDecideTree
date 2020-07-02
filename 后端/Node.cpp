#include "Node.h"
Node::Node() {
	attribute = " ";
	leafType = " ";
	Value = 0;
}
string Node::getArr()
{
	return attribute;
}
string  Node::getleafType()
{
	return this->leafType;
}
Node::~Node()
{
}