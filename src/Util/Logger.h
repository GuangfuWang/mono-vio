#ifndef MONO_VIO_LOGGER_H
#define MONO_VIO_LOGGER_H

#include <QString>
#include <QDateTime>
#include <stdexcept>
#include "TypeDef.h"

#ifdef GF_WINDOWS

#include <windows.h>

#endif

#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wformat-security"
#endif
namespace gf {

///note: differentiate windows system and others.
    enum LogColor {
        Reset = 0,
        Bold,
        Unbold,
        FrontBlack,
        FrontRed,
        FrontGreen,
        FrontYellow,
        FrontBlue,
        FrontPurple,
        FrontCyan,
        FrontWhite,
        BackBlack,
        BackRed,
        BackGreen,
        BackYellow,
        BackBlue,
        BackPurple,
        BackCyan,
        BackWhite,
        TypeCount
    };

    static const char *logCommands[] = {
            "\033[0m",
            "\033[1m",
            "\033[2m",
            "\033[30m",
            "\033[31m",
            "\033[32m",
            "\033[33m",
            "\033[34m",
            "\033[35m",
            "\033[36m",
            "\033[37m",
            "\033[40m",
            "\033[41m",
            "\033[42m",
            "\033[43m",
            "\033[44m",
            "\033[45m",
            "\033[46m",
            "\033[47m",
    };

    enum LogType {
        Debug = 0,
        Info  = 2,
        Warn  = 3,
        Error = 4,
        Fatal = 5
    };

    enum LogChannel {
        TERMINAL,
        FILE
    };

    static const char *logColorConsole[] = {
            logCommands[Reset],
            logCommands[FrontBlack],
            logCommands[FrontGreen],
            logCommands[FrontYellow],
            logCommands[FrontRed],
            logCommands[FrontRed]
    };

    class Logger {
    public:
        template<class... Types>
        static void Debug(const QString &msg, const Types &... args) {
#ifdef GF_LINUX
            QString
        msgT = logColorConsole[LogType::Debug] + QDateTime::currentDateTime().toString("[yyyy-MM-dd, hh:mm:ss] ") + msg;
#elif defined(GF_WINDOWS)
            QString msgT = QDateTime::currentDateTime().toString("[yyyy-MM-dd, hh:mm:ss, Debug]") + msg;
#else
#error "Not support yet!"
#endif

            int size_s = std::snprintf(nullptr,
                                       0,
                                       msgT.toStdString().c_str(), args ...) + 1; // Extra space for '\0'
            if (size_s <= 0) { throw std::runtime_error("Error during formatting."); }
            auto size = static_cast<size_t>( size_s );
            auto buf  = createUniqueRef<char[]>(size);
            std::snprintf(buf.get(), size, msgT.toStdString().c_str(), args ...);
            printf(buf.get());
            printf("\n");
        }

        template<class... Types>
        static void Warning(const QString &msg, const Types &... args) {
#ifdef GF_LINUX
            QString
        msgT = logColorConsole[LogType::Warn] + QDateTime::currentDateTime().toString("[yyyy-MM-dd, hh:mm:ss] ") + msg;
#elif defined(GF_WINDOWS)
            HANDLE                     hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
            WORD                       saved_attributes;

            /* Save current attributes */
            GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
            saved_attributes = consoleInfo.wAttributes;

            SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
            QString msgT = QDateTime::currentDateTime().toString("[yyyy-MM-dd, hh:mm:ss, Warn]") + msg;
#endif
            int size_s = std::snprintf(nullptr,
                                       0,
                                       msgT.toStdString().c_str(), args ...) + 1; // Extra space for '\0'
            if (size_s <= 0) { throw std::runtime_error("Error during formatting."); }
            auto size = static_cast<size_t>( size_s );
            auto buf  = createUniqueRef<char[]>(size);
            std::snprintf(buf.get(), size, msgT.toStdString().c_str(), args ...);

            printf(buf.get());
#ifdef GF_WINDOWS
            /* Restore original attributes */
            SetConsoleTextAttribute(hConsole, saved_attributes);
#endif
            printf("\n");
        }

        template<class... Types>
        static void Info(const QString &msg, const Types &... args) {
#ifdef GF_LINUX
            QString
        msgT = logColorConsole[LogType::Info] + QDateTime::currentDateTime().toString("[yyyy-MM-dd, hh:mm:ss] ") + msg;
#elif defined(GF_WINDOWS)
            HANDLE                     hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
            WORD                       saved_attributes;

            /* Save current attributes */
            GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
            saved_attributes = consoleInfo.wAttributes;

            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
            QString msgT = QDateTime::currentDateTime().toString("[yyyy-MM-dd, hh:mm:ss, Info]: ") + msg;
#endif
            int size_s = std::snprintf(nullptr,
                                       0,
                                       msgT.toStdString().c_str(), args ...) + 1; // Extra space for '\0'
            if (size_s <= 0) { throw std::runtime_error("Error during formatting."); }
            auto size = static_cast<size_t>( size_s );
            auto buf  = createUniqueRef<char[]>(size);
            std::snprintf(buf.get(), size, msgT.toStdString().c_str(), args ...);

            printf(buf.get());
#ifdef GF_WINDOWS
            /* Restore original attributes */
            SetConsoleTextAttribute(hConsole, saved_attributes);
#endif
            printf("\n");
        }

        template<class... Types>
        static void Error(const QString &msg, const Types &... args) {
#ifdef GF_LINUX
            QString
        msgT = logColorConsole[LogType::Error] + QDateTime::currentDateTime().toString("[yyyy-MM-dd, hh:mm:ss] ") + msg;
#elif defined(GF_WINDOWS)
            HANDLE                     hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
            WORD                       saved_attributes;

            /* Save current attributes */
            GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
            saved_attributes = consoleInfo.wAttributes;

            SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
            QString msgT = QDateTime::currentDateTime().toString("[yyyy-MM-dd, hh:mm:ss, Error]") + msg;
#endif
            int size_s = std::snprintf(nullptr,
                                       0,
                                       msgT.toStdString().c_str(), args ...) + 1; // Extra space for '\0'
            if (size_s <= 0) { throw std::runtime_error("Error during formatting."); }
            auto size = static_cast<size_t>( size_s );
            auto buf  = createUniqueRef<char[]>(size);
            std::snprintf(buf.get(), size, msgT.toStdString().c_str(), args ...);

            printf(buf.get());
#ifdef GF_WINDOWS
            /* Restore original attributes */
            SetConsoleTextAttribute(hConsole, saved_attributes);
#endif
            printf("\n");
        }

        template<class... Types>
        static void Fatal(const QString &msg, const Types &... args) {
#ifdef GF_LINUX
            QString
        msgT = logColorConsole[LogType::Fatal] + QDateTime::currentDateTime().toString("[yyyy-MM-dd, hh:mm:ss] ") + msg;
#elif defined(GF_WINDOWS)
            HANDLE                     hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
            WORD                       saved_attributes;

            /* Save current attributes */
            GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
            saved_attributes = consoleInfo.wAttributes;

            SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
            QString msgT = QDateTime::currentDateTime().toString("[yyyy-MM-dd, hh:mm:ss, Fatal]") + msg;
#endif
            int size_s = std::snprintf(nullptr,
                                       0,
                                       msgT.toStdString().c_str(), args ...) + 1; // Extra space for '\0'
            if (size_s <= 0) { throw std::runtime_error("Error during formatting."); }
            auto size = static_cast<size_t>( size_s );
            auto buf  = createUniqueRef<char[]>(size);
            std::snprintf(buf.get(), size, msgT.toStdString().c_str(), args ...);

            printf(buf.get());
#ifdef GF_WINDOWS
            /* Restore original attributes */
            SetConsoleTextAttribute(hConsole, saved_attributes);
#endif
            printf("\n");
            abort();
        }

        static void SetLogChannel(const LogChannel &ch = LogChannel::TERMINAL, const QString &str = "") {
            if (str.length() == 0) {
                QString temp = QDateTime::currentDateTime().toString("[yyyy-MM-dd, hh:mm:ss, Info]: ") +
                        "Your log file is empty, log info will output to terminal by default.";
                printf(temp.toStdString().c_str());
                return;
            }
            if (ch == LogChannel::FILE && str.length() > 0) {
                mLogFile       = str;
                mLogToFileFlag = true;
            }
        }

    private:
        static QString mLogFile;
        static bool    mLogToFileFlag;
    };


}
QString gf::Logger::mLogFile       = "";
bool    gf::Logger::mLogToFileFlag = false;
using Logger = gf::Logger;
#ifdef __GNUC__
#ifndef GF_DEBUG
#define GF_DEBUG(MSG, ...)  Logger::Debug(MSG, ##__VA_ARGS__)
#endif
#ifndef GF_WARN
#define GF_WARN(MSG, ...)  Logger::Warnning(MSG, ##__VA_ARGS__)
#endif
#ifndef GF_INFO
#define GF_INFO(MSG, ...)  Logger::Info(MSG, ##__VA_ARGS__)
#endif
#ifndef GF_ERROR
#define GF_ERROR(MSG, ...) Logger::Error(MSG,##__VA_ARGS__)
#endif
#ifndef GF_FATAL
#define GF_FATAL(MSG, ...) Logger::Fatal(MSG,##__VA_ARGS__)
#endif
#elif defined(_MSC_VER)
#ifndef GF_DEBUG
#define GF_DEBUG(MSG, ...)  Logger::Debug(MSG, __VA_ARGS__)
#endif
#ifndef GF_WARN
#define GF_WARN(MSG, ...)  Logger::Warning(MSG, __VA_ARGS__)
#endif
#ifndef GF_INFO
#define GF_INFO(MSG, ...)  Logger::Info(MSG, __VA_ARGS__)
#endif
#ifndef GF_ERROR
#define GF_ERROR(MSG, ...) Logger::Error(MSG,__VA_ARGS__)
#endif
#ifndef GF_FATAL
#define GF_FATAL(MSG, ...) Logger::Fatal(MSG,__VA_ARGS__)
#endif
#endif


#endif //MONO_VIO_LOGGER_H
