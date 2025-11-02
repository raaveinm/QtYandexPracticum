#pragma once

#include <map>
#include <string>

struct Model {
    using Map = std::map<std::string, std::string>;
    Map items;
    Map::iterator iterator = items.begin();
};

static std::map<std::string, std::string> words {
        {"Book", "Книга"},
        {"Cinnamon", "Корица"},
        {"Cup", "Чашка"},
        {"Kettle", "Чайник"},
        {"Saucer", "Блюдце"},
        {"Sugar", "Сахар"},
        {"Tea", "Чай"},
        {"Teaspoon", "Чайная ложка"},
    };

static std::map<std::string, std::string> authors_and_books {
        {"Т. Пратчетт", "Плоский мир"},
        {"Р. Брэдбери", "Лёд и пламя"},
        {"Д. Адамс", "В основном безвредна"},
        {"Ф. Дик", "Солнечная лотерея"},
        {"А. и Б. Стругацкие", "Жук в муравейнике"},
        {"Ф. Кафка", "Превращение"},
    };