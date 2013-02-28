// Copyright 2013, Zaoqibu Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Zaoqibu Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Author: vwarship@163.com (Junjian Wang)
//
// The Optical Character Recognition (OCR Style)

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMap>
#include <QMainWindow>
#include <QPrinter>
#include <QProgressDialog>
#include <QKeyEvent>

QT_BEGIN_NAMESPACE
class QAction;
class QLabel;
class QMenu;
class QScrollArea;
class QScrollBar;
class ImageView;
class QGraphicsScene;
class QTextEdit;
class QToolButton;
class QActionGroup;
class QButtonGroup;
class QComboBox;
class QProgressDialog;
class OCREngineAgent;
class OCRThread;
QT_END_NAMESPACE

#include <QMessageBox>
class OCRProgressDialog : public QProgressDialog
{
    Q_OBJECT

public:
    explicit OCRProgressDialog(QWidget *parent = 0, Qt::WindowFlags flags = 0)
        : QProgressDialog(parent, flags)
    {
    }

protected:
    void keyPressEvent(QKeyEvent *event)
    {
        if(event->key() == Qt::Key_Escape)
            event->ignore();
    }
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();

    static QStringList availableOCRLanguages();

private slots:
    void scan();
    void open();
    void screenshot();
    void save();
    void print();

    void zoomIn();
    void zoomOut();
    void zoomToWindow();
    void resetZoom();

    void deskew();
    void grayscale();

    void ocr();
    void downloadOCRLanguageData();

    void about();

    void onTimerScreenshot();

    void pointerGroupClicked(int pointerType);
    void selectedLanguage(QAction* action);
    void selectedOcrLanguage(QAction* action);
    void selectedOcrLanguageWithIndex(int curIndex);
    void selectedOcrPageSegMode(QAction* action);
    void setOcrResult(QString text);

private://action
    void createActions();
    void createFileActions();
    void createViewActions();
    void createAdjustmentActions();
    void createOcrActions();
    void createLangActions();
    void createWindowActions();
    void createHelpActions();

private://menu
    void createMenus();
    void createFileMenus();
    void createViewMenus();
    void createAdjustmentMenus();
    void createOcrMenus();
    void createOcrLanguagesMenu();
    void createOcrPageSegModesMenu();
    void createLanguageMenus();
    void createWindowMenus();
    void createHelpMenus();

private:
    void initProgressDialog();
    void createToolbars();
    void createStatusBar();

    QIcon createIcon(const QString &filename) const;
    QToolButton* createToolButton(const QString &text, const QString &iconFilename);

    void updateActions();
    void updateOCRLanguagesAction();
    void updateOCRLanguagesComboBox();

    void setCentralWidgetWithImageView();
    void createDockWindows();
    void createDockWindowWithOcrResult();

    int findSelectedOcrLanguageIndex(QAction* action);
    int findCurrentSelectedOcrLanguageIndex();

    void showImage(const QPixmap &pixmap);
    QString selectedRectImageFilename();
    void saveScreenshot(QPixmap &pixmap);

    void loadImage();
    void imageDeskew();
    void imageGrayscale();

private:
    OCREngineAgent *m_ocrEngineAgent;

    QPixmap _pixmap;
    ImageView *imageView;

    QString m_filename;

#ifndef QT_NO_PRINTER
    QPrinter printer;
#endif

private:
    //action
    //QAction *scanAction;
    QAction *openAction;
    QAction *screenshotAction;
    QAction *saveAction;
    QAction *printAction;
    QAction *exitAction;

    QAction *zoomInAction;
    QAction *zoomOutAction;
    QAction *zoomToWindowAction;
    QAction *resetZoomAction;

    QAction *deskewAction;
    QAction *grayscaleAction;

    QAction *ocrAction;
    QAction *downloadOCRLanguageDataAction;
    QActionGroup *ocrLanguagesActionGroup;
    QActionGroup *ocrPageSegModesActionGroup;
    QMap<int, QAction*> ocrLanguageActions;

    QActionGroup *languagesActionGroup;

    QAction *aboutAction;

    QButtonGroup *pointerTypeButtonGroup;
    QToolButton *moveImageToolButton;
    QToolButton *rectSelectionToolButton;

    //menu
    QMenu *fileMenu;
    QMenu *viewMenu;
    QMenu *adjustmentMenu;
    QMenu *ocrMenu;
    QMenu *ocrLanguagesMenu;
    QMenu *ocrPageSegModesMenu;
    QMenu *languagesMenu;
    QMenu *windowMenu;
    QMenu *helpMenu;

    QToolBar *toolbar;
    QComboBox *ocrLanguagesComboBox;

    QTextEdit *ocrResultWindow;

    OCRProgressDialog *progressDlg;

    static const QString m_screenshotFilename;

private:
    enum PointerType
    {
        ptMove = 1,
        ptSelection
    };

};

#endif //MAINWINDOW_H
