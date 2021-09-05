#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <regex>

namespace aricanli {
	namespace general{
		namespace tools {
			class FileDiagonsticsException : public std::exception {
			public:
				explicit FileDiagonsticsException(const char* message) noexcept : m_message(message) {}
				explicit FileDiagonsticsException(const std::string& message) noexcept : m_message(message) {}
				virtual ~FileDiagonsticsException() noexcept {}

				virtual const char* what() const noexcept {
					return m_message.c_str();
				}
			protected:
				std::string m_message{ "Invalid Parser Query" };
			};

			class FileDiagnostics {
			public:
				explicit FileDiagnostics() noexcept = delete;
				explicit FileDiagnostics(const char* fileAdress) noexcept;
				explicit FileDiagnostics(const FileDiagnostics&) noexcept = delete;
				FileDiagnostics& operator=(const FileDiagnostics&) = delete;
				virtual ~FileDiagnostics() noexcept;

				virtual void open();
				virtual std::string getLines() const;
				virtual bool isOpen() const;
				virtual int fileLength();

				void writeOptions(const std::string& , const std::string& , char delim = '\n');
				virtual void searchbyKey(const std::string&);
				void searchbyDateTime(const std::string&, const std::string&);
				virtual void parseWithSize(size_t);
				virtual std::vector<std::string> parseWithDelimiter(char delim);
				virtual std::vector<std::string> getContests() const;
			protected:
				void writeFile(const std::vector<std::string>&);
				virtual void closeFile();
				void split(char t_delim);
				size_t stringSize() const;
			private:
				std::string m_lines;
				std::string m_extensionName;
				std::ifstream m_ifs;
				std::ofstream m_ofs;
				std::size_t m_fileLength;
				std::vector<std::string> m_lineOfString;

			};
		}
	}
}
