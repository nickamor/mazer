#ifdef __ARGHANDLER_H__
#define __ARGHANDLER_H__

class Task {
public:
	virtual Task() = 0;
	virtual ~Task() = 0;
	virtual void run() = 0;
    virtual bool isFinalTask();
};

class HelpTask : public Task {
	public:
	override void run();
    override bool isFinalTask();
}

class ArgHandler {
	po::options_description desc("Allowed options");
public:
	ArgHandler(int argc, char const *argv[]);
};

#endif // !__ARGHANDLER_H__
