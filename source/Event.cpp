#include "../header/Event.h"

Event buildEvent(int typeEvent)
{
	Event event;
	event.currentEvent = typeEvent;
	
	return event;
}



bool isValidToActiEvent(Event & event , int currentRows)
{
	if(event.currentEvent == Event::RAND_PIECE_BLOCK)
		return currentRows >= Event::CONDITION_EVENT_BLOCK;
	if(event.currentEvent == Event::RAND_BOMB)
		return currentRows >= Event::CONDITION_EVENT_BOMB;
	if(event.currentEvent == Event::UPGRADE_SPEED)
		return currentRows >= Event::CONDITION_EVENT_UPDAGRADE_SPEED;
	
	return false;
	
}

void enqueueEvent(EventQueue * queue, Event event)
{	
	EventNode * newEvent = new EventNode;
	newEvent->event = event;
	newEvent->next = nullptr;
	if(queue->front == nullptr){
		queue->back = newEvent;
		queue->front = newEvent;
		return;
	}
	
	queue->front->next = newEvent;
	queue->front = newEvent;
}

EventNode * desqueEvent(EventQueue *& queue)
{	
	if(queue->back == nullptr)
		return nullptr;
	
	EventNode* save = queue->back;
	
	queue->back = queue->back->next;
	
	if(queue->back == nullptr)
		queue->front = nullptr;
	
	save->next = nullptr;
	
	
	return save;
}

EventNode * getBackToEventQueue(EventQueue * queue)
{
	if(queue == nullptr)
		return nullptr;
	
	return queue->back;
}


EventQueue * buildEventQueue()
{
	EventQueue * queue = new EventQueue;
	queue->back = nullptr;
	queue->front = nullptr;
		
	queue->currentRows = 0;
	
	enqueueEvent(queue , buildEvent(Event::RAND_BOMB));
	enqueueEvent(queue , buildEvent(Event::UPGRADE_SPEED));
	enqueueEvent(queue , buildEvent(Event::RAND_PIECE_BLOCK));

	return queue;
}

Event getNextEvent(EventQueue *& queue)
{
	if(queue == nullptr)
		queue = buildEventQueue();
	
	Event nextEvent = getBackToEventQueue(queue)->event;
	
	if(!isValidToActiEvent(nextEvent, queue->currentRows))
	   return buildEvent(Event::NONE);
	
	EventNode *  eventNode = desqueEvent(queue);
	Event event = buildEvent(Event::NONE);
	
	event = eventNode->event;

	enqueueEvent(queue , event);
	
	return event;
}

