#include "LkLog.h"

#include "LkLog.h"
#include "LkUtil.h"
#include "LkSourceAbstract.h"
#include <QDateTime>

LkLog::LkLog()
	: m_logLevel(LkLogLevel::Trace)
	, m_enableCache(false)
	, m_log2Console(true)
	, m_log2File(false)
	, m_enablFILE(false)
	, m_enableLINE(false)
	, m_enableFUNTION(true)
	, m_enableColorPrint(true)
	, m_file(NULL)
	, m_buffer(NULL)
	, m_bufferLength(4096)
	, m_timeFormat("MM-dd hh:mm")
{
	m_filePath.sprintf("log/Linekong_%s.log"
		, QDateTime::currentDateTime().toString("MM_dd_hh_mm_ss").toStdString().c_str());
	m_buffer = new char[m_bufferLength];
}

LkLog::~LkLog()
{
	LkFree(m_file);
	LkFreeArray(m_buffer);
}

void LkLog::setLogLevel(int level)
{
	m_logLevel = level;
}

void LkLog::setEnableCache(bool enabled)
{
	m_enableCache = enabled;
}

void LkLog::setLog2Console(bool enabled)
{
	m_log2Console = enabled;
}

void LkLog::setLog2File(bool enabled)
{
	m_log2File = enabled;
	m_file = new QFile(m_filePath.c_str());
	if (!m_file->open(QIODevice::WriteOnly)) {
		return;
	}
}

void LkLog::setEnableFILE(bool enabled)
{
	m_enablFILE = enabled;
}

void LkLog::setEnableLINE(bool enabled)
{
	m_enableLINE = enabled;
}

void LkLog::setEnableFUNCTION(bool enabled)
{
	m_enableFUNTION = enabled;
}

void LkLog::setEnableColorPrint(bool enabled)
{
	m_enableColorPrint = enabled;
}

void LkLog::setTimeFormat(const LkString &fmt)
{
	m_timeFormat = fmt;
}

void LkLog::setFilePath(const LkString &path)
{
	m_filePath = path;
}

void LkLog::verbose(const char *file, muint16 line, const char *function
	, const char *tag, const char *fmt, ...)
{
	if (m_logLevel > LkLogLevel::Verbose) {
		return;
	}

	va_list ap;
	va_start(ap, fmt);
	log(LkLogLevel::Verbose, file, line, function, tag, fmt, ap);
	va_end(ap);
}

void LkLog::info(const char *file, muint16 line, const char *function
	, const char *tag, const char *fmt, ...)
{
	if (m_logLevel > LkLogLevel::Info) {
		return;
	}

	va_list ap;
	va_start(ap, fmt);
	log(LkLogLevel::Info, file, line, function, tag, fmt, ap);
	va_end(ap);
}

void LkLog::trace(const char *file, muint16 line, const char *function
	, const char *tag, const char *fmt, ...)
{
	if (m_logLevel > LkLogLevel::Trace) {
		return;
	}

	va_list ap;
	va_start(ap, fmt);
	log(LkLogLevel::Trace, file, line, function, tag, fmt, ap);
	va_end(ap);
}

void LkLog::warn(const char *file, muint16 line, const char *function
	, const char *tag, const char *fmt, ...)
{
	if (m_logLevel > LkLogLevel::Warn) {
		return;
	}

	va_list ap;
	va_start(ap, fmt);
	log(LkLogLevel::Warn, file, line, function, tag, fmt, ap);
	va_end(ap);
}

void LkLog::error(const char *file, muint16 line, const char *function
	, const char *tag, const char *fmt, ...)
{
	if (m_logLevel > LkLogLevel::Error) {
		return;
	}

	va_list ap;
	va_start(ap, fmt);
	log(LkLogLevel::Error, file, line, function, tag, fmt, ap);
	va_end(ap);
}

void LkLog::log(int level, const char *file, muint16 line, const char *function, const char *tag, const char *fmt, va_list ap)
{
	LkAutoLocker(m_mutex);

	const char *p;

	switch (level) {
	case LkLogLevel::Verbose:
		p = "verbose";
		break;
	case LkLogLevel::Info:
		p = "info";
		break;
	case LkLogLevel::Trace:
		p = "trace";
		break;
	case LkLogLevel::Warn:
		p = "warn";
		break;
	case LkLogLevel::Error:
		p = "error";
		break;
	default:
		p = "default";
		break;
	}

	LkString time = QDateTime::currentDateTime().toString(m_timeFormat.c_str()).toStdString();
	int size = 0;
	size += snprintf(m_buffer+size, m_bufferLength-size, "[%s][%d]", time.c_str(), 0);
	size += snprintf(m_buffer+size, m_bufferLength-size, "[%s]", p);

	if (m_enablFILE) {
		size += snprintf(m_buffer+size, m_bufferLength-size, "[%s]", file);
	}

	if (m_enableLINE) {
		size += snprintf(m_buffer+size, m_bufferLength-size, "[%d]", line);
	}

	if (m_enableFUNTION) {
		size += snprintf(m_buffer+size, m_bufferLength-size, "[%s]", function);
	}

	if (tag) {
		size += snprintf(m_buffer+size, m_bufferLength-size, "[%s]", tag);
	}

	size += vsnprintf(m_buffer+size, m_bufferLength-size, fmt, ap);

#ifdef Q_OS_WIN
	size += snprintf(m_buffer+size, m_bufferLength-size, "\r\n");
#else
	size += snprintf(m_buffer+size, m_bufferLength-size, "\n");
#endif

	// log to console
	if (m_log2Console && m_enableColorPrint) {
		if (level <= LkLogLevel::Trace) {
			printf("\033[0m%s", m_buffer);
		} else if (level == LkLogLevel::Warn) {
			printf("\033[33m%s\033[0m", m_buffer);
		} else if (level == LkLogLevel::Error){
			printf("\033[31m%s\033[0m", m_buffer);
		}
	} else if (m_log2Console && !m_enableColorPrint) {
		printf("%s", m_buffer);
	}

	// log to file
	if (m_log2File) {
		m_file->write(m_buffer, size);
		m_file->flush();
	}

	fflush(stdout);
}

LkLog *g_logCtx = new LkLog;
