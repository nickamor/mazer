//
// Created by Nicholas Amor on 21/9/16.
//

using namespace std;

int
main(int argc, const char *argv[])
{
    auto args = ArgumentsParser(argc, argv);

    auto tasks = args.GetTasks();

    cout << tasks.size() << " tasks:" << endl;

    for (auto &task : tasks)
    {
        if (auto read = dynamic_pointer_cast<ReadFileTask>(task))
        {
            cout << "ReadFileTask: " << read->GetFilename() << endl;
        }

        if (auto write = dynamic_pointer_cast<WriteFileTask>(task))
        {
            cout << "WriteFileTask: " << write->GetFilename() << endl;
        }

        if (auto svg = dynamic_pointer_cast<WriteSvgTask>(task))
        {
            cout << "WriteSvgTask: " << svg->GetFilename() << endl;
        }

        if (auto generate = dynamic_pointer_cast<GenerateTask>(task))
        {
            cout << "GenerateTask: " << generate->GetSeed() << " " << generate->GetWidth() << " "
                 << generate->GetHeight() << endl;
        }

        if (auto help = dynamic_pointer_cast<HelpTask>(task))
        {
            cout << "HelpTask" << endl;
        }
    }
}
