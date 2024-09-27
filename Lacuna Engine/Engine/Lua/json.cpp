#include "json.h"

LE::jsonFile::jsonFile(const std::string& FilePath)
{
    this->FilePath = FilePath;
}
LE::jsonFile::~jsonFile()
{
}
bool LE::jsonFile::checkExistence(const char* Array, const char* CheckName)
{
    // Load the scene JSON file
    FILE* file = fopen(FilePath.c_str(), "r");
    if (!file) {
        std::cerr << "Error: Cannot open scene file " << FilePath << "\n";
        return false;
    }

    // Parse the JSON data
    cJSON* root = cJSON_Parse( freadAll(file).c_str() );
    if (!root) {
        std::cerr << "Error: Cannot parse scene JSON data" << "\n";
        fclose(file);
        return false;
    }

    // Check if the "objects" array exists
    cJSON* objects_array = cJSON_GetObjectItem(root, Array);
    if (!objects_array) {
        std::cerr << "Error: Cannot find \"objects\" array in the scene JSON data" << "\n";
        cJSON_Delete(root);
        fclose(file);
        return false;
    }

    // Check if the object with the given name exists in the "objects" array
    bool object_found = false;
    cJSON* object = NULL;
    cJSON_ArrayForEach(object, objects_array) {
        cJSON* name = cJSON_GetObjectItem(object, "name");
        if (name && cJSON_IsString(name) && strcmp(name->valuestring, CheckName) == 0) {
            object_found = true;
            break;
        }
    }

    // Clean up
    cJSON_Delete(root);
    fclose(file);

    return object_found;
}
int LE::jsonFile::getCount(const char* Array)
{
    // Открытие файла
    std::ifstream file(FilePath);
    if (!file.is_open())
    {
        return -1;
    }
    // Чтение файла в строку
    std::string str((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();

    // Разбор JSON-строки с помощью cJSON
    cJSON* root = cJSON_Parse(str.c_str());
    if (!root)
    {
        std::cerr << "Error parsing JSON string" << std::endl;
        return -1;
    }

    // Запись параметра "num" каждого элемента в int вектор и сортировка вектора по возрастанию
    std::vector<int> nums;
    cJSON* objects = cJSON_GetObjectItemCaseSensitive(root, Array);
    cJSON* object = nullptr;
    cJSON_ArrayForEach(object, objects)
    {
        cJSON* num = cJSON_GetObjectItemCaseSensitive(object, "num");
        nums.emplace_back(num->valueint);
    }
    cJSON_Delete(root);
    std::sort(nums.begin(), nums.end());

    // Поиск следующего свободного числа в последовательности
    int count = 0;
    for (int i = 0; i < nums.size(); i++)
    {
        if (nums[i] != i)
        {
            count = i;
            break;
        }
        count = i + 1;
    }
    return count;
}
cJSON* LE::jsonFile::createObject(const std::vector<std::string>& Values) // no func/arrays/child objects
{
    cJSON* output = cJSON_CreateObject();

    std::cout << "!!!: " << Values.size() << "\n";
    for (const auto& element : Values)
    {
        // Разбиваем строку на name и value
        std::istringstream iss(element);
        std::string name, value;
        std::getline(iss, name, ':');
        std::getline(iss, value);

        // Удаляем пробелы в начале и конце value
        value.erase(0, value.find_first_not_of(" "));
        value.erase(value.find_last_not_of(" ") + 1);

        // Если значение содержит квадратные скобки, значит это массив
        if (value.front() == '[' && value.back() == ']')
        {
            // Удаляем скобки
            value.erase(value.begin()); // удаляем символ '['
            value.erase(value.end()-1); // удаляем символ ']'

            // Разбиваем массив на элементы
            std::vector<std::string> array_elements;
            std::string array_element;
            for (size_t i = 0; i < value.size(); i++)
            {
                if (i+1 >= value.size())
                {
                    array_element += value[i];
                    array_elements.emplace_back(array_element);
                }
                else
                if (value[i] == ',' && value[i+1] == ' ')
                {
                    array_elements.emplace_back(array_element);
                    array_element.clear();
                    i++;
                }
                else
                    array_element += value[i];
            }

            // Создаем cJSON массив и добавляем в объект по имени
            cJSON* array = cJSON_CreateArray();
            for (const auto& array_element : array_elements) {
                cJSON_AddItemToArray(array, cJSON_CreateString(array_element.c_str()));
            }

            cJSON_AddItemToObject(output, name.c_str(), array);
            //std::cout << "!array" << "\n";
        }
        else
        {
            // Добавляем name и value в JSON-объект
            cJSON_AddStringToObject(output, name.c_str(), value.c_str());
            //std::cout << "!value" << "\n";
        }
    }
    return output;
}
bool LE::jsonFile::addObjectTo(const std::string& To, const std::vector<std::string>& Values)
{
    if (!Created) return false;
    cJSON* D = getData(FilePath);

    // Add the new object to array
    cJSON* objects_array = cJSON_GetObjectItem(D, To.c_str());
    if (!objects_array) {
        std::cerr << "Error: Cannot find \""<<To<<"\" array in JSON data\n";
        return false;
    }

    cJSON* new_object = createObject(Values);
    cJSON_AddNumberToObject(new_object, "num", getCount("objects"));
    cJSON_AddItemToArray(objects_array, new_object);

    // Save the updated JSON data back to the file
    FILE* F = fopen(FilePath.c_str(), "r+");
    fseek(F, 0, SEEK_SET);
    char* updated_json_data = cJSON_PrintBuffered(D, 4096, true);
    fwrite(updated_json_data, 1, strlen(updated_json_data), F);
    fclose(F);

    // Clean up
    free(updated_json_data);
    return true;
}
cJSON* LE::jsonFile::getData(const std::string& FilePath)
{
    // load JSON file
    FILE* F = fopen(FilePath.c_str(), "r+");
    if (!F) {
        std::cerr << "Error: Cannot open file: "<<FilePath<<"\n";
        return nullptr;
    }

    // parse JSON data
    cJSON* D = cJSON_Parse(freadAll(F).c_str());
    if (!D) {
        std::cerr << "Error: Cannot parse JSON data\n";
        fclose(F);
        return nullptr;
    }

    fclose(F);
    return D;
}
std::string LE::jsonFile::getName(const std::string& Name)
{
    if (!Created) return "";
    cJSON* D = getData(FilePath);

    cJSON* name_json = cJSON_GetObjectItemCaseSensitive(D, Name.c_str());
    if (!cJSON_IsString(name_json))
    {
        std::cerr << "Error: Name is not a string\n";
        return "";
    }
    std::string name(name_json->valuestring);
    return name;
}
std::vector<cJSON*> LE::jsonFile::getArray(const std::string& Name)
{
    if (!Created) return {};
    cJSON* D = getData(FilePath);

    cJSON* objects = cJSON_GetObjectItem(D, Name.c_str());
    int num_objects = cJSON_GetArraySize(objects);
    std::vector<cJSON*> object_list;
    object_list.reserve(num_objects);

    cJSON* object = nullptr;
    for (int i = 0; i < num_objects; ++i)
    {
        object = cJSON_GetArrayItem(objects, i);
        if (object)
            object_list.emplace_back(object);
    }
    return object_list;
}
std::string LE::freadAll(FILE* file)
{
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    std::string buffer(file_size, ' ');
    fread(buffer.data(), 1, file_size, file);
    return buffer;
}
bool LE::createJSON(const std::string& FilePath, const std::string& Data)
{
    cJSON* root = cJSON_Parse(Data.c_str());
    if (root == nullptr)
    {
        std::cerr << "Error parsing JSON string: "<<cJSON_GetErrorPtr()<<"\n";
        return false;
    }

    std::ofstream outfile(FilePath);
    if (!outfile.is_open())
    {
        std::cerr << "Error opening file: "<<FilePath<<"\n";
        cJSON_Delete(root);
        return false;
    }

    char* json = cJSON_Print(root);
    outfile << json;
    free(json);
    outfile.close();
    cJSON_Delete(root);
    return true;
}
LE::jsonFile LE::getJSON(const std::string& FilePath, std::string Data)
{
    size_t T = (Data.size() ? 1 : 0);

    if (!fileExist(FilePath) && T != 0)
    {
        if (!createJSON(FilePath, Data))
            return jsonFile();
    }
    return jsonFile(FilePath);
}