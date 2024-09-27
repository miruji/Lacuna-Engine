#pragma once
#include <iostream>
#include <vector>

#include "../Type/mi.h"

namespace LE
{
	//
	class Import 
	{
	private:

	public:
		struct ImportFile
		{
			std::string path, name, type;

			ImportFile(std::string path, std::string type, std::string name);
			ImportFile();
			~ImportFile();

			static ImportFile& getEmpty();
		};

		Import();
		~Import();

		mi searchImport(const std::vector<ImportFile>& importFiles, const std::string& name);
		ImportFile& getImport(std::vector<ImportFile>& importFiles, std::string name);
		void deleteImport(std::vector<ImportFile>& importFiles, std::string name);

		std::vector<ImportFile> objects;
		std::vector<ImportFile> scenes;

		std::vector<ImportFile> textures;
		std::vector<ImportFile> animations; 
		std::vector<ImportFile> fonts;
		std::vector<ImportFile> shaders;

		std::vector<ImportFile> sounds;
	};
}