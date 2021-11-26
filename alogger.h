#ifndef ALOGGER_H
#define ALOGGER_H

#include <spdlog/common.h>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_sinks.h>
#include <spdlog/sinks/null_sink.h>
#include <iostream>
#include <memory>
#include <bitset>
#include "stream_logger.h"

#ifdef APPNAME
const std::string infoLogPath = std::string("info_" ) + std::string(APPNAME);
const std::string errorLogPath = std::string("error_") + std::string(APPNAME);
#else
constexpr auto infoLogPath = "info";
constexpr auto errorLogPath = "error";
#endif

constexpr size_t infoLogFileSize = 1048576 * 5;
constexpr size_t errorLogFileSize = 1048576 * 5;
constexpr int rotationNumber = 5;
constexpr auto loggerName = "ALogger";

#define LOG(level, ...) if(::Alogging::ALogger::getInstance()) ::Alogging::ALogger::getInstance()->log(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, level, __VA_ARGS__);
#define INFO(...) LOG(::Alogging::ALogger::info, __VA_ARGS__);
#define WARN(...) LOG(::Alogging::ALogger::warn, __VA_ARGS__);
#define ERROR(...) LOG(::Alogging::ALogger::err, __VA_ARGS__);
#define DEBUG(...) LOG(::Alogging::ALogger::debug, __VA_ARGS__);
#define CRITICAL(...) LOG(::Alogging::ALogger::critical, __VA_ARGS__);

namespace Alogging {


class ALogger {
public:
    enum level{
        trace = SPDLOG_LEVEL_TRACE,
        debug = SPDLOG_LEVEL_DEBUG,
        info = SPDLOG_LEVEL_INFO,
        warn = SPDLOG_LEVEL_WARN,
        err = SPDLOG_LEVEL_ERROR,
        critical = SPDLOG_LEVEL_CRITICAL,
        off = SPDLOG_LEVEL_OFF,
        n_levels
    };

    template<typename FormatString, typename std::enable_if<fmt::is_compile_string<FormatString>::value, int>::type = 0, typename... Args>
    void log(spdlog::source_loc source, level lvl, const FormatString &fmt, Args&&...args )
    {
        if (m_consoleLogger && loggingModes.test(0)) { m_consoleLogger->log(source, static_cast<spdlog::level::level_enum>(lvl), fmt, std::forward<Args>(args)...); }
        if (m_defaultFileLogger && loggingModes.test(1)) { m_defaultFileLogger->log(source, static_cast<spdlog::level::level_enum>(lvl), fmt, std::forward<Args>(args)...);}
        if (m_errorFileLogger && loggingModes.test(2)) { m_errorFileLogger->log(source, static_cast<spdlog::level::level_enum>(lvl), fmt, std::forward<Args>(args)...);}
        if (m_nullLogger && loggingModes.test(3)) {}
        if (m_streamLogger && loggingModes.test(4)) {m_streamLogger->log(source, static_cast<spdlog::level::level_enum>(lvl), fmt, std::forward<Args>(args)...);}
    };

    template<typename... Args>
    void log(spdlog::source_loc source, level lvl, spdlog::string_view_t fmt, Args&&...args)
    {
        if (m_consoleLogger && loggingModes.test(0)) { m_consoleLogger->log(source, static_cast<spdlog::level::level_enum>(lvl), fmt, std::forward<Args>(args)...); }
        if (m_defaultFileLogger && loggingModes.test(1)) { m_defaultFileLogger->log(source, static_cast<spdlog::level::level_enum>(lvl), fmt, std::forward<Args>(args)...);}
        if (m_errorFileLogger && loggingModes.test(2)) { m_errorFileLogger->log(source, static_cast<spdlog::level::level_enum>(lvl), fmt, std::forward<Args>(args)...);}
        if (m_nullLogger && loggingModes.test(3)) {}
        if (m_streamLogger && loggingModes.test(4)) {m_streamLogger->log(source, static_cast<spdlog::level::level_enum>(lvl), fmt, std::forward<Args>(args)...);}
    }

    void switchConsoleLog(bool state)
    {
        state ? loggingModes.set(0, true) : loggingModes.set(0, false);
    }

    void switchNetwrokBroadcastingLog(bool state);

    void setLoggingLevel(ALogger::level lvl)
    {
        if(m_defaultFileLogger) m_defaultFileLogger->set_level(static_cast<spdlog::level::level_enum>(lvl));
        if(m_consoleLogger) m_consoleLogger->set_level(static_cast<spdlog::level::level_enum>(lvl));
    }

    level getLoggingLevel() { if (m_defaultFileLogger) return static_cast<level>(m_defaultFileLogger->level());}

    static ALogger *getInstance()
    {
        static ALogger* instance = nullptr;
        if (instance == nullptr) { instance = new ALogger(); }
        return instance;
    }

    std::bitset<8> getLoggingModes() const { return loggingModes; }
    /**
     * @brief setLoggingModes  Set bits to change modes of logging. Available logging modes are:
     * 0th bit -> Console logging
     * 1st bit -> Default logging
     * 2nd bit -> Error logging
     * 3rd bit -> Null logging
     * 4th bit -> Stream logging
     * @param value bitset for logging
     */
    void setLoggingModes(const std::bitset<8> &value) { loggingModes = value; }

private:

    //Logger types
    std::shared_ptr<spdlog::logger> m_defaultFileLogger;
    std::shared_ptr<spdlog::logger> m_errorFileLogger;
    std::shared_ptr<spdlog::logger> m_consoleLogger;
    std::shared_ptr<spdlog::logger> m_nullLogger;
    std::shared_ptr<spdlog::logger> m_streamLogger;
    std::shared_ptr<IStreamSocket> m_socket;
    //Bit set containing logging modes to be used
    std::bitset<8> loggingModes;

    ALogger()
    {
        m_socket = std::make_shared<IStreamSocket>(); // Dummy socket created
        loggingModes = std::bitset<8>(std::string("00011111"));
        m_defaultFileLogger = spdlog::rotating_logger_mt("infoLogger", infoLogPath, infoLogFileSize, rotationNumber);
        m_consoleLogger     = spdlog::stdout_logger_mt("consoleLogger");
        m_nullLogger        = spdlog::null_logger_mt("nullLogger");
        m_errorFileLogger   = spdlog::rotating_logger_mt("errorLogger", errorLogPath, errorLogFileSize, rotationNumber, false);
        m_errorFileLogger->set_level(spdlog::level::err);
        m_streamLogger      = spdlog::stream_logger_mt("streamLogger", m_socket);
    }
    ~ALogger();

};

}

#endif // ALOGGER_H
