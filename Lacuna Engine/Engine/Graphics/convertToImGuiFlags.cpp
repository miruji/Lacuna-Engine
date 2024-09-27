#include "convertToImGuiFlags.h"

int LE::convertToImGuiFlags(const std::string& styles) {
    // name -> style
    static const std::unordered_map<std::string, int> styleMap = {
        {"none", ImGuiWindowFlags_None},
        {"noTitleBar", ImGuiWindowFlags_NoTitleBar},
        {"noResize", ImGuiWindowFlags_NoResize},
        {"noMove", ImGuiWindowFlags_NoMove},
        {"noScroll", ImGuiWindowFlags_NoScroll},
        {"noScrollBar", ImGuiWindowFlags_NoScrollbar}, // noScrollBar, noScrollWithMouse
        {"noScrollWithMouse", ImGuiWindowFlags_NoScrollWithMouse},
        {"noCollapse", ImGuiWindowFlags_NoCollapse},
        {"alwaysAutoReisize", ImGuiWindowFlags_AlwaysAutoResize},
        {"noBackground", ImGuiWindowFlags_NoBackground},
        {"noSavedSettings", ImGuiWindowFlags_NoSavedSettings},
        {"noMouseInputs", ImGuiWindowFlags_NoMouseInputs},
        {"menuBar", ImGuiWindowFlags_MenuBar},
        {"horizontalScrollBar", ImGuiWindowFlags_HorizontalScrollbar},
        {"noFocusOnAppearing", ImGuiWindowFlags_NoFocusOnAppearing},
        {"noBringToFrontOnFocus", ImGuiWindowFlags_NoBringToFrontOnFocus},
        {"alwaysVerticalScrollBar", ImGuiWindowFlags_AlwaysVerticalScrollbar},
        {"alwaysHorizontalScrollBar", ImGuiWindowFlags_AlwaysHorizontalScrollbar},
        {"alwaysUseWindowPadding", ImGuiWindowFlags_AlwaysUseWindowPadding},
        {"noNavInputs", ImGuiWindowFlags_NoNavInputs},
        {"noNavFocus", ImGuiWindowFlags_NoNavFocus},
        {"unsaveDocument", ImGuiWindowFlags_UnsavedDocument},
        {"noDocking", ImGuiWindowFlags_NoDocking},
        {"noNav", ImGuiWindowFlags_NoNav}, // noNavInputs, noNavFocus
        {"noDecoration", ImGuiWindowFlags_NoDecoration}, // noTitleBar, noResize, noScrollbar, noCollapse
        {"noInputs", ImGuiWindowFlags_NoInputs}, // noMouseInputs, noNavInputs, noNavFocus
    };
    int resultFlags = 0;

    // Разбиваем строку по запятым
    size_t startPos = 0;
    size_t endPos = styles.find(',');
    while (endPos != std::string::npos) {
        // Извлекаем текущий стиль из подстроки
        std::string style = styles.substr(startPos, endPos - startPos);
        // Удаляем лишние пробелы в начале и конце строки
        style.erase(0, style.find_first_not_of(" \t\n\r\f\v"));
        style.erase(style.find_last_not_of(" \t\n\r\f\v") + 1);

        // Ищем стиль в словаре и добавляем соответствующий флаг к результату
        const auto& it = styleMap.find(style);
        if (it != styleMap.end()) {
            resultFlags |= it->second;
        }

        // Переходим к следующему стилю
        startPos = endPos + 1;
        endPos = styles.find(',', startPos);
    }

    // Обработка последнего стиля (или если строка содержит только один стиль)
    std::string style = styles.substr(startPos);
    style.erase(0, style.find_first_not_of(" \t\n\r\f\v"));
    style.erase(style.find_last_not_of(" \t\n\r\f\v") + 1);
    const auto& it = styleMap.find(style);
    if (it != styleMap.end()) {
        resultFlags |= it->second;
    }

    return resultFlags;
}