//
// Created by nhatv on 24 Nov 2021.
//

#ifndef VIDEO_EDITOR_BX23_TEMP_H
#define VIDEO_EDITOR_BX23_TEMP_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class temp; }
QT_END_NAMESPACE

class temp : public QWidget {
Q_OBJECT

public:
    explicit temp(QWidget *parent = nullptr);

    ~temp() override;

private:
    Ui::temp *ui;
};


#endif //VIDEO_EDITOR_BX23_TEMP_H
