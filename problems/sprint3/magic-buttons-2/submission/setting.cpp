#include "setting.h"
#include "ui_setting.h"
#include <prac/QInputDialog>

Setting::Setting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Setting)
{
    ui->setupUi(this);

    setWindowFlags(Qt::WindowStaysOnTopHint);

    for (const auto& action : actions_) {
        ui->cb_action->addItem(action.name);
    }

    ui->cb_action->addItem("Открыть URL");
    ui->cb_action->addItem("Открыть папку");
}

Setting::~Setting() {
    delete ui;
}

void Setting::on_pb_save_clicked() {
    auto index = ui->cb_action->currentIndex();
    const size_t pre_defined_actions_count = actions_.size();
    if (index < 0) {
        return;
    }

    size_t current_index = static_cast<size_t>(index);

    if (current_index < pre_defined_actions_count) {
        emit signalSetAction(current_button_idx_, actions_[current_index].name, actions_[current_index].action);
        ui->cb_action->setCurrentIndex(0);
        this->close();
    }
    else if (current_index == pre_defined_actions_count) {
        QString user_input = prac::QInputDialog::getText(this, "Введите URL", "URL:");
        if (!user_input.isEmpty()) {
            std::function<void()> action = [user_input]() {
                OpenCustomUrl(user_input);
            };
            emit signalSetAction(current_button_idx_, "URL: " + user_input, action);
            ui->cb_action->setCurrentIndex(0);
            this->close();
        }
    }
    else if (current_index == pre_defined_actions_count + 1) {
        QString user_input = prac::QInputDialog::getText(this, "Введите путь к папке", "Путь:");
        if (!user_input.isEmpty()) {
            std::function<void()> action = [user_input]() {
                OpenCustomDirectory(user_input);
            };
            emit signalSetAction(current_button_idx_, "Папка: " + user_input, action);
            ui->cb_action->setCurrentIndex(0);
            this->close();
        }
    }
}
