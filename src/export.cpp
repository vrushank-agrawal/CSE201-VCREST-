//
// Created by nhatv on 2 Jan 2022.
//

#include "videoeditor.h"
#include "ui_VideoEditor.h"
#include "export.h"
#include <QFileDialog>
#include <QMessageBox>

void VideoEditor::writeVideo() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.setNameFilter("MP4 video (*.mp4)");
    std::string outputPath, videoPath = "./temp_media/1.mp4";
    if (dialog.exec()) {
        QString qOutputPath = dialog.selectedFiles()[0];
        if (qOutputPath.right(4) != ".mp4")
            qOutputPath.append(".mp4");
        outputPath = qOutputPath.toStdString();
    } else {
        return;
    }

    remove(outputPath.c_str());
    remove(videoPath.c_str());

    if (!resultVideo->writeVideo(videoPath, fourcc)) {
        QMessageBox errorMsg;
        errorMsg.setWindowTitle("Error");
        errorMsg.setText("Export is not supported on this platform");
        errorMsg.exec();
    }
    else {
        exp::merge_av(videoPath, ui->timeline->createAudio(), outputPath);
        remove(videoPath.c_str());
    }
}