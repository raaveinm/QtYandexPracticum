//
// Created by Kirill "Raaveinm" on 10/25/25.
//

#pragma once

#include <vector>
#include <string>

struct Model {
    using container = std::vector<std::string>;
    container items;
    container::iterator iterator = items.begin();
};

static std::vector<std::string> days_of_week = {
    "Понедельник",
    "Вторник",
    "Среда",
    "Четверг",
    "Пятница",
    "Суббота",
    "Воскресенье"
};

static std::vector<std::string> months_of_year = {
    "Январь",
    "Февраль",
    "Март",
    "Апрель",
    "Май",
    "Июнь",
    "Июль",
    "Август",
    "Сентябрь",
    "Октябрь",
    "Ноябрь",
    "Декабрь"
};