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

#include "StatisticsDialog.h"
#include "UserphraseModel.h"
#include "ui_StatisticsDialog.h"
#include "qcustomplot.h"

StatisticsDialog::StatisticsDialog(QWidget *parent)
    :QDialog{parent}
    ,ui_{new Ui::StatisticsDialog}
{
    ui_.get()->setupUi(this);
    setupChart();
    setupConnect();
}

StatisticsDialog::~StatisticsDialog()
{
}

void StatisticsDialog::setupConnect()
{
    connect(
        ui_.get()->buttonBox, SIGNAL(accepted()),
        this, SLOT(accept())
    );

    connect(
        ui_.get()->buttonBox, SIGNAL(rejected()),
        this, SLOT(reject())
    );
}

void StatisticsDialog::setupChart()
{
insertData("安安","a",1,2,3);
insertData("你好","b",1,2,3);
insertData("謝謝","c",1,2,3);
insertData("運動員","d",1,2,3);
insertData("喔","e",1,2,3);
QCustomPlot *customPlot = ui_->customPlot;
// create empty bar chart objects:
QCPBars *user_freq_bar = new QCPBars(customPlot->xAxis, customPlot->yAxis);
QCPBars *max_freq_bar = new QCPBars(customPlot->xAxis, customPlot->yAxis);
QCPBars *orig_freq_bar = new QCPBars(customPlot->xAxis, customPlot->yAxis);
customPlot->addPlottable(user_freq_bar);
customPlot->addPlottable(max_freq_bar);
customPlot->addPlottable(orig_freq_bar);
// set names and colors:
QPen pen;
pen.setWidthF(1.2);
orig_freq_bar->setName("Original frequency");
pen.setColor(QColor(255, 131, 0));
orig_freq_bar->setPen(pen);
orig_freq_bar->setBrush(QColor(255, 131, 0, 50));
max_freq_bar->setName("Maximun frequency");
pen.setColor(QColor(1, 92, 191));
max_freq_bar->setPen(pen);
max_freq_bar->setBrush(QColor(1, 92, 191, 50));
user_freq_bar->setName("User frequency");
pen.setColor(QColor(150, 222, 0));
user_freq_bar->setPen(pen);
user_freq_bar->setBrush(QColor(150, 222, 0, 70));
// stack bars ontop of each other:
max_freq_bar->moveAbove(orig_freq_bar);
user_freq_bar->moveAbove(max_freq_bar);
 
// prepare x axis with country labels:
QVector<double> ticks;
QVector<QString> labels;

ticks << 1 << 2 << 3 << 4 << 5 << 6 << 7;
//labels << "USA" << "Japan" << "Germany" << "France" << "UK" << "Italy" << "Canada";
customPlot->xAxis->setAutoTicks(false);
//customPlot->xAxis->setAutoTicks(true);
customPlot->xAxis->setAutoTickLabels(false);
customPlot->xAxis->setTickVector(ticks);
//customPlot->xAxis->setTickVectorLabels(labels);
customPlot->xAxis->setTickVectorLabels(phrase_data);
customPlot->xAxis->setTickLabelRotation(60);
customPlot->xAxis->setSubTickCount(0);
customPlot->xAxis->setTickLength(0, 4);
customPlot->xAxis->grid()->setVisible(true);
customPlot->xAxis->setRange(0, 8);
 
// prepare y axis:
customPlot->yAxis->setRange(0, 10.5);
customPlot->yAxis->setPadding(5); // a bit more space to the left border
customPlot->yAxis->setLabel("Phrase frequency");
customPlot->yAxis->grid()->setSubGridVisible(true);
QPen gridPen;
gridPen.setStyle(Qt::SolidLine);
gridPen.setColor(QColor(0, 0, 0, 25));
customPlot->yAxis->grid()->setPen(gridPen);
gridPen.setStyle(Qt::DotLine);
customPlot->yAxis->grid()->setSubGridPen(gridPen);
 
orig_freq_bar->setData(ticks, orig_freq_data);
max_freq_bar->setData(ticks, max_freq_data);
user_freq_bar->setData(ticks, user_freq_data);
 
// setup legend:
customPlot->legend->setVisible(true);
customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
customPlot->legend->setBrush(QColor(255, 255, 255, 200));
QPen legendPen;
legendPen.setColor(QColor(130, 130, 130, 200));
customPlot->legend->setBorderPen(legendPen);
QFont legendFont = font();
legendFont.setPointSize(10);
customPlot->legend->setFont(legendFont);
customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}

int StatisticsDialog::insertData(QString phrase, QString bopomofo, int orig_freq, int max_freq, int user_freq)
{
    phrase_data << phrase;
    bopomofo_data << bopomofo;
    orig_freq_data << orig_freq;
    max_freq_data << max_freq;
    user_freq_data << user_freq;
    return 1;
}
