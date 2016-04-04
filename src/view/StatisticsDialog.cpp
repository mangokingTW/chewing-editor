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
    setupConnect();
}

StatisticsDialog::~StatisticsDialog()
{
}

void StatisticsDialog::setupConnect()
{
    connect(
        ui_.get()->buttonBox, SIGNAL(rejected()),
        this, SLOT(reject())
    );
}

void StatisticsDialog::plot(const Statistics* statistics)
{
QVector<QString> phrase_vec;
QVector<QString> bopomofo_vec(statistics->bopomofo_vec);

for( int i = 0 ; i < statistics->phrase_vec.size() ; i++ )
{
    phrase_vec << "" << statistics->phrase_vec[i]+" ("+statistics->bopomofo_vec[i]+")" << "" << "";
}

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
//max_freq_bar->moveAbove(orig_freq_bar);
//user_freq_bar->moveAbove(max_freq_bar);
 
// prepare x axis with country labels:
QVector<double> ticks;
QVector<QString> labels;

for( int i = 1 ; i <= phrase_vec.size()*3 ; i++ )
{
    ticks << i;
}

//labels << "USA" << "Japan" << "Germany" << "France" << "UK" << "Italy" << "Canada";
customPlot->xAxis->setAutoTicks(false);
//customPlot->xAxis->setAutoTicks(true);
customPlot->xAxis->setAutoTickLabels(false);
customPlot->xAxis->setTickVector(ticks);
customPlot->xAxis->setTickStep(9);
//customPlot->xAxis->setTickVectorLabels(labels);
customPlot->xAxis->setTickVectorLabels(phrase_vec);
customPlot->xAxis->setTickLabelRotation(60);
//customPlot->xAxis->setSubTickCount(0);
customPlot->xAxis->setTickLength(0, 1);
customPlot->xAxis->grid()->setVisible(true);
customPlot->xAxis->setRange(0, 24);
 
// prepare y axis:
customPlot->yAxis->setRange(0, *std::max_element(statistics->max_freq_vec.begin(), statistics->max_freq_vec.end()));
customPlot->yAxis->setPadding(5); // a bit more space to the left border
customPlot->yAxis->setLabel("Phrase frequency");
customPlot->yAxis->grid()->setSubGridVisible(true);
QPen gridPen;
gridPen.setStyle(Qt::SolidLine);
gridPen.setColor(QColor(0, 0, 0, 25));
customPlot->yAxis->grid()->setPen(gridPen);
gridPen.setStyle(Qt::DotLine);
customPlot->yAxis->grid()->setSubGridPen(gridPen);
 
//orig_freq_bar->setData(ticks, orig_freq_vec);
//max_freq_bar->setData(ticks, max_freq_vec);
//user_freq_bar->setData(ticks, user_freq_vec);
for(int i = 0 ; i < statistics->orig_freq_vec.size() ; i++ )
{
    orig_freq_bar->addData(i*4+1,statistics->orig_freq_vec[i]);
    max_freq_bar->addData(i*4+2,statistics->max_freq_vec[i]);
    user_freq_bar->addData(i*4+3,statistics->user_freq_vec[i]);
}

 
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
