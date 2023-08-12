#include <iostream>
#include <fstream>

class LogCommand {
public:
    virtual ~LogCommand() = default;
    virtual void print(const std::string& message) {
        return;
    }
};

class DecoraterLgC : public LogCommand {
private:
    LogCommand* lgc_;
protected:
    DecoraterLgC(LogCommand* lgc) : lgc_(lgc) {}
};

class PrintLogCommand : public DecoraterLgC {
public:
    explicit PrintLogCommand(LogCommand* lgc) : DecoraterLgC(lgc) {}
    void print(const std::string& message) override {
        std::cout << message << std::endl;
    }
};

class SaveLogCommand : public DecoraterLgC {
public:
    explicit SaveLogCommand(LogCommand* lgc) : DecoraterLgC(lgc) {}
    void print(const std::string& message) override {
        std::ofstream out("Log.txt", std::ios::app);
        if (out.is_open()) {
            out << message << std::endl;
        }
    }
};

class LogCommand2 : public DecoraterLgC {
public:
    explicit LogCommand2(LogCommand* lgc) : DecoraterLgC(lgc) {}
    void print(LogCommand* lgc, const std::string& message) {
        lgc->print(message);
    }
};

int main()
{
    auto logCom = new PrintLogCommand(new LogCommand);
    auto save = new SaveLogCommand(new LogCommand);
    //logCom->print("Log");
    //                        // без класс LogCommand2 и функции void print(LogCommand& lgc, const std::string& message).
    //save->print("Log");

    auto two = new LogCommand2(new LogCommand);
    two->print(logCom, "Log check");
    two->print(save, "Log check");
}
