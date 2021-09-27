#include "classes.h"
#include <iostream>
const char* Echo::get_noise() const
{
	return noise;
}

Echo::Echo(const char* speech) :noise(speech) {}

void Speaker::listen(const Echo& echo)
{

}

void Speaker::speak(const Room& room) const
{
	room.distribute(Echo("some noise"));
}

Speaker::Speaker(const char* name) :name(name) {}

Student::Student(const char* student_name) :name(student_name) {}
void Student::get_name() const
{
	std::cout << name;
}

Notebook::Notebook(unsigned int notebook_size) : size(notebook_size), empty_page(0)
{
	information = new const char* [size];
}

void Notebook::print() const
{
	for (int i = 0; i < empty_page; i++)
	{
		std::cout << information[i] << std::endl;
	}
}

void Bachelord::listen(const Echo& echo)
{
	if (notebook.size > notebook.empty_page)
	{
		notebook.information[notebook.empty_page] = echo.get_noise();
		++notebook.empty_page;
	}
}
Bachelord::Bachelord(const char* name, Notebook&& notebook) :Student(name), notebook(notebook) {}

const Notebook& Bachelord::get_notebook() const
{
	return notebook;
}

void Master::listen(const Echo& echo)
{
	memory.push_back(echo.get_noise());
}

Master::Master(const char* name) :Student(name) {}

void Room::let_participant(IListener* participant)
{
	participants.push_back(participant);
}

void Room::distribute(Echo&& echo) const
{
	for (IListener* listener : participants)
	{
		listener->listen(echo);
	}
}