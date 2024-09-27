#include "Import.h"
using namespace LE;

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
Import::ImportFile::ImportFile(std::string path, std::string type, std::string name)
	: path(std::move(path)), type(std::move(type)), name(std::move(name))
{
}
Import::ImportFile::ImportFile()
	: path("?"), type("?"), name("?")
{
}
Import::ImportFile::~ImportFile()
{
}
Import::ImportFile& Import::ImportFile::getEmpty()
{
	static ImportFile emptyImport;
	return emptyImport;
}
// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
Import::Import()
{
}
Import::~Import()
{
}
mi Import::searchImport(const std::vector<ImportFile>& importFiles, const std::string& name)
{
	for_er(i, 0, i < importFiles.size(), i++, importFiles[i].name == name, i);
	return std::numeric_limits<mi>::max(); // or throw an exception
}
Import::ImportFile& Import::getImport(std::vector<ImportFile>& importFiles, std::string name)
{
	mi index = searchImport(importFiles, name);
	if (index != -1) return importFiles[index];
	else             return ImportFile::getEmpty();
}
void Import::deleteImport(std::vector<ImportFile>& importFiles, std::string name)
{
	mi index = searchImport(importFiles, name);
	if (index != -1) importFiles.erase(importFiles.begin()+index);
}