#pragma once
#include <vector>
class Echo;
class Speaker;
class Room;
class Bachelord;
class IListener
{
public:
	virtual void listen(const Echo& echo) = 0;
};

class Echo
{
	friend class Speaker;
public:
	const char* get_noise() const;
private:
	const char* noise;
	Echo(const char* speech);
};

class Speaker : public IListener
{
private:
	const char* name;
public:
	void listen(const Echo& echo) override;
	void speak(const Room& room) const;
	Speaker(const char* name);
};

class Student : public IListener
{
protected:
	const char* name;
	Student(const char* student_name);
public:
	void get_name() const;
};

class Notebook
{
	friend class Bachelord;
private:
	const char** information;
	unsigned int size;
	unsigned int empty_page;
public:
	void print() const;
	Notebook(unsigned int size);
};

class Bachelord : public Student
{
private:
	Notebook notebook;
public:
	const Notebook& get_notebook() const;
	void listen(const Echo& echo) override;
	Bachelord(const char* name, Notebook&& notebook);
};

class Master : public Student
{
private:
	std::vector<const char*> memory;
public:
	void listen(const Echo& echo) override;
	Master(const char* name);
};

class Room
{
public:
	std::vector<IListener*> participants;
	void let_participant(IListener* participant);
	void distribute(Echo&& echo) const;
};