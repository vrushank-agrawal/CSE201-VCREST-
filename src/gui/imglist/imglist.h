//
// Created by nhatv on 18 Nov 2021.
//

#ifndef VIDEO_EDITOR_BX23_IMGLIST_H
#define VIDEO_EDITOR_BX23_IMGLIST_H

#include <QListWidget>

class ImgList : public QListWidget
{
Q_OBJECT

public:
    explicit ImgList(int pieceSize = 50, QWidget *parent = nullptr);
    void addPiece(const QPixmap &pixmap, const QPoint &location);

    static QString puzzleMimeType() { return QStringLiteral("image/x-puzzle-piece"); }

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void startDrag(Qt::DropActions supportedActions) override;

    int m_PieceSize;
};


#endif //VIDEO_EDITOR_BX23_IMGLIST_H
