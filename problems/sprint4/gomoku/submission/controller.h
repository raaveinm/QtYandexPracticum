#pragma once

#ifdef PRAC_TESTS
#include "../tests/model.h"
#include "../tests/view.h"
#else
#include "model.h"
#include "view.h"
#endif

class Controller {
public:
    Controller()
        : model_(),
          view_() {
        auto newGameCallback = [this](const size_t size_x, const size_t size_y) {
            model_.Reset(size_x, size_y);
            view_.SetupField(size_x, size_y);
            UpdateGame();
        };

        auto setMoveCallback = [this](const size_t x, const size_t y) {
            if (Symbol symbol = model_.DoMove(x, y); symbol != Symbol::kEmpty) {
                view_.UpdateCell(x, y, QString(static_cast<char>(symbol)));
            }
            UpdateGame();
        };

        view_.SetNewgameCallback(newGameCallback);
        view_.SetMoveCallback(setMoveCallback);
        model_.Reset(3, 3);
        view_.SetupField(3, 3);
        UpdateGame();
        view_.show();
    }

private:
    void UpdateGame();
    Model model_;
    View view_;
};

inline void Controller::UpdateGame() {
    const std::optional<Symbol> winner = model_.GetWinner();

    if (winner == std::nullopt) {
        Symbol next_player = model_.GetNextPlayer();
        view_.SetStatus(QString("Ход игрока ") + static_cast<char>(next_player));
        view_.SetStatusStyle(QString("black"), false);
    } else if (winner == Symbol::kEmpty) {
        view_.SetStatus(QString("Ничья"));
        view_.SetStatusStyle(QString("red"), true);
    } else {
        view_.SetStatus(QString("Выиграл ") + static_cast<char>(winner.value()));
        view_.SetStatusStyle(QString("green"), true);
        const auto& winner_path = model_.GetWinnerPath();
        for (const auto& cell : winner_path) {
            view_.SetCellStyle(cell.first, cell.second, QString("green"), true);
        }
    }
}
