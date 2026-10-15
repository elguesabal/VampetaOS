/*
  + -------------------------------------------------------------------------- +
  |  o o o                                                          VAMPETAOS  |
  + -------------------------------------------------------------------------- +
  |                                                                            |
  |  elguesabal@VampetaOS:~$ pwd                                               |
  |  /Sd/Sd.hpp                                                                |
  |                                                                            |
  + -------------------------------------------------------------------------- +
*/

#ifndef SD_H
#define SD_H

#include "../VampetaOS.hpp"
#include "../System/System.hpp"

#define SCK		GPIO_NUM_40
#define MISO	GPIO_NUM_39
#define MOSI	GPIO_NUM_14
#define CS		GPIO_NUM_12

/**
 * @author elguesabal
 * @brief CLASSE RESPONSAVEL POR GERENCIAR O CARTAO DE MEMORIA
*/
class Sd {
	public:
		/**
		 * @author elguesabal
		 * @brief GUARDA NOME E SE E UM DIRETORIO (USADO PARA LISTAGEM DE DIRETORIO)
		*/
		struct DirectoryEntry {
			std::string	name;
			bool 		isDirectory;
		};

	public:
		// /Sd/sd.cpp
		static bool							init_sd(void);
		static bool							init(void);

		// /Sd/directory.cpp
		static bool							exist_dir(const char *path);
		static bool							create_dir(const char *path);
		static bool							remove_dir(const char *path);
		static bool							delete_dir(const char *path);
		static std::vector<DirectoryEntry>	list_dir(const char *path);

		// /Sd/file.cpp
		static bool							exist_file(const char *path);
		static off_t						size_file(const char *path);
		static bool							create_file(const char *path);
		static bool							create_file(const char *path, const char *content);
		static bool							write_file_truncate(const char *path, const char *content);
		static bool							write_file_append(const char *path, const char *content);
		static bool							read_file(const char *path, std::string &content);
		static bool							delete_file(const char *path);

		// /Sd/config.cpp
		static std::string					get_config(const char *path, const char *name);
		static bool							set_config(const char *path, const char *name, const char *value);
};

#endif