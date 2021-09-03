#include "FileDiagnostics.h"



namespace aricanli {
	namespace general {
		namespace tools {
			FileDiagnostics::FileDiagnostics(const char* fileAdress) noexcept : m_ifs{ fileAdress } {
				open();
			}
			FileDiagnostics::~FileDiagnostics() {
				if (isOpen())
					closeFile();
			}
			bool FileDiagnostics::isOpen() const {
				return m_ifs.is_open();
			}
			void FileDiagnostics::closeFile() {
				m_ifs.close();
			}
			void FileDiagnostics::open() {
				if (isOpen())
					m_lines.assign((std::istreambuf_iterator<char>(m_ifs)), std::istreambuf_iterator<char>());
				else
					throw FileDiagonsticsException{ "FileDiagnostics::open() : File cannot open." };
			}
			std::vector<std::string> FileDiagnostics::getContests() const {
				return m_lineOfString;
			}
			std::string FileDiagnostics::getLines() const {
				return m_lines;
			}
			void FileDiagnostics::split(char t_delim) {
				std::stringstream ss(m_lines);
				std::string item;

				while (getline(ss, item, t_delim))
					m_lineOfString.push_back(item);

			}
			int FileDiagnostics::fileLength() {
				if (m_ifs) {
					m_ifs.seekg(0, m_ifs.end);
					m_fileLength = m_ifs.tellg();
					m_ifs.seekg(0, m_ifs.beg);
					return m_fileLength;
				}
				else
					throw FileDiagonsticsException{ "Error in fileLength : file can not open" };
			}

			void FileDiagnostics::parseWithSize(size_t t_size) {
				if (isOpen() && m_lines.size() > 0) {
					size_t t_strSize = stringSize();
					size_t t_count = t_strSize / t_size;

					if (t_strSize > t_count * t_size)
						t_count++;

					for (size_t i = 0; i < fileLength(); i += t_size) {
						m_lineOfString.push_back(m_lines.substr(i, t_size));
					}
				}
				else
					throw FileDiagonsticsException{ "Error in parseWithSize()" };

			}
			void FileDiagnostics::searchbyKey(const std::string& key, const std::string& path) {
				std::vector<std::string> tmp;
				for (const auto& vec : m_lineOfString) {
					if (vec.find(key) != std::string::npos)
						tmp.push_back(vec);
				}
				writeFile(path, tmp);
			}
			void FileDiagnostics::searchbyDateTime(const std::string& first, const std::string& end, const std::string& path) {
				std::vector<std::string> tmp;
				std::regex rgx("\\d\\d:\\d\\d:\\d\\d");
				std::smatch m;
				for (const auto& vec : m_lineOfString) {
					if (std::regex_search(vec, m, rgx)) {
						auto pos = m.position(0);
						auto date = vec.substr(pos, pos + 2);

						if (date > first && date < end)
							tmp.push_back(vec);
					}
				}
				writeFile(path, tmp);
			}
			void FileDiagnostics::writeFile(const std::string& t_extensionName, const std::vector<std::string>& t_vecOfStr) {
				std::string pathName = t_extensionName;
				m_ofs.open(pathName, std::ios::out | std::ios::app);
				for (int i = 0; i < t_vecOfStr.size(); i++) {
					m_ofs.write(t_vecOfStr[i].c_str(), t_vecOfStr[i].size());
					m_ofs << "\n";
				}
				m_ofs.close();
			}
			std::vector<std::string> FileDiagnostics::parseWithDelimiter(char t_delim) {
				split(t_delim);
				return m_lineOfString;
			}
			size_t FileDiagnostics::stringSize() const {
				return m_lines.size();
			}
		}
	}
}