#ifndef STREAM_LOGGER_H
#define STREAM_LOGGER_H
#include <spdlog/spdlog.h>
#include <spdlog/sinks/base_sink.h>
#include <spdlog/details/null_mutex.h>
#include <spdlog/details/console_globals.h>
#include <spdlog/details/synchronous_factory.h>
#include <mutex>
#include "IStreamSocket.h"

namespace spdlog
{

namespace sinks
{

template<typename SMutex>
class stream_sink: public spdlog::sinks::base_sink<SMutex>{
public:
    stream_sink(const std::string& logger_name, std::shared_ptr<IStreamSocket> socket): m_streamSocket(socket){}
private:
    std::shared_ptr<IStreamSocket> m_streamSocket;
protected:
    void sink_it_(const spdlog::details::log_msg& msg) override
    {
        spdlog::memory_buf_t formatted;
        spdlog::sinks::base_sink<SMutex>::formatter_->format(msg, formatted);
        if (m_streamSocket) m_streamSocket->send(fmt::to_string(formatted));
    }

    void flush_() override
    {
        if (m_streamSocket)m_streamSocket->flush();
    }
};


using stream_sink_mt = stream_sink<std::mutex>;
using stream_sink_st = stream_sink<details::null_mutex>;

template<typename Factory = spdlog::synchronous_factory>
std::shared_ptr<spdlog::logger> stream_logger_mt(const std::string &logger_name);

template<typename Factory = spdlog::synchronous_factory>
std::shared_ptr<spdlog::logger> stream_logger_st(const std::string &logger_name);

} //namespace sinks

//Creator methods

inline std::shared_ptr<spdlog::logger> stream_logger_mt(const std::string &logger_name, std::shared_ptr<IStreamSocket> socket)
{
    auto sink = std::make_shared<::spdlog::sinks::stream_sink_mt>(logger_name, socket);
    auto new_logger = std::make_shared<spdlog::logger>(std::move(logger_name), std::move(sink));
    spdlog::details::registry::instance().initialize_logger(new_logger);
    return new_logger;
}

inline std::shared_ptr<spdlog::logger> stream_logger_st(const std::string &logger_name, std::shared_ptr<IStreamSocket> socket)
{
    auto sink = std::make_shared<::spdlog::sinks::stream_sink_mt>(logger_name, socket);
    auto new_logger = std::make_shared<spdlog::logger>(std::move(logger_name), std::move(sink));
    spdlog::details::registry::instance().initialize_logger(new_logger);
    return new_logger;
}

} // namespace spdlog

#endif // STREAM_LOGGER_H
