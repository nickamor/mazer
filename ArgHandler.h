#ifndef __ARGHANDLER_H__
#define __ARGHANDLER_H__

#include <memory>
#include <vector>

class Task {
public:
	virtual ~Task() = 0;
	virtual void run() = 0;
    virtual bool isFinalTask();
};

class HelpTask : public Task {
	public:
	void run();
    bool isFinalTask();
};

class ArgHandler {
    std::vector<std::shared_ptr<Task> > tasks;
public:
	ArgHandler(int argc, char const *argv[]);

	std::vector<std::shared_ptr<Task> > getTasks();
};

#endif // !__ARGHANDLER_H__
