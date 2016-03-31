
/*
 * chewing-editor: Chewing userphrase editor
 * Copyright (C) 2014 Chewing Development Team

 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#pragma once

#include <memory>
#include <QDialog>

namespace Ui {
    class StatisticsDialog;
}

class StatisticsDialog final: public QDialog
{
    Q_OBJECT

public:
    explicit StatisticsDialog(QWidget *parent = 0);
    StatisticsDialog(const StatisticsDialog&) = delete;
    StatisticsDialog& operator=(const StatisticsDialog&) = delete;
    ~StatisticsDialog(); // = default;

    int insertData(QString phrase, QString bopomofo, int orig_freq, int max_freq, int user_freq);
private:
    QVector<QString> phrase_data;
    QVector<QString> bopomofo_data;
    QVector<double> orig_freq_data;
    QVector<double> max_freq_data;
    QVector<double> user_freq_data;
    void setupConnect();
    void setupChart();
    std::unique_ptr<Ui::StatisticsDialog> ui_;
};
