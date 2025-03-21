#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeySequence>
#include <QMenuBar>
#include <QToolBar>
#include <QAction>
#include <QPlainTextEdit>
#include <QLabel>
#include <QString>
#include <QFileDialog>
#include "FindDialog.h"
#include "ReplacDialog.h"
#include <QSharedPointer>

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QPlainTextEdit mainEditor;
    QLabel statusLbl;
    QString m_filePath;
    bool m_isTextChanged;
    QSharedPointer<FindDialog> m_FindDlg;
    QSharedPointer<ReplacDialog> m_ReplaceDlg;

    MainWindow();
    MainWindow(const MainWindow&);
    MainWindow& operator= (const MainWindow&);
    bool construct();

    bool initMenuBar();
    bool initToolBar();
    bool initStatusBar();
    bool initMainEditor();

    bool initFileMenu(QMenuBar* mb);
    bool initEditMenu(QMenuBar* mb);
    bool initFormatMenu(QMenuBar* mb);
    bool initViewMenu(QMenuBar* mb);
    bool initHelpMenu(QMenuBar* mb);

    bool initFileToolItem(QToolBar* tb);
    bool initEditToolItem(QToolBar* tb);
    bool initFormatToolItem(QToolBar* tb);
    bool initViewToolItem(QToolBar* tb);

    bool makeAction(QAction* &action, const QString text, const QKeySequence& shortcut);
    bool makeAction(QAction* &action, const QString tip, const QString icon);

    QString showFileDialog(QFileDialog::AcceptMode mode, QString title);
    void showErrorMessage(QString message);
    int showQuesstionMessage(QString message);
    QString saveCurrentData(QString path = "");
    void preEditorChanged();
    void openFileToEdit(QString path);
    QAction* findMenuBarAction(QString text);
    QAction* findToolBarAction(QString text);
    void updateActionState(const QString& actionText, bool checked);

private slots:
    void onFileNew();
    void onFileOpen();
    void onFileSave();
    void onFileSaveAs();
    void onEditDelete();
    void onEditFind();
    void onEditReplce();
    void onEditGoto();
    void onEditExit();
    void onViewStatusBar();
    void onViewToolBar();
    void onTextChanged();
    void onCopyAvailable(bool available);
    void onUndoAvailable(bool available);
    void onRedoAvailable(bool available);
    void onCursorPositionChanged();

protected:
    void closeEvent(QCloseEvent* e);
    void dragEnterEvent(QDragEnterEvent* e);
    void dropEvent(QDropEvent* e);
public:
    static MainWindow* NewInstance();
    ~MainWindow();
};
#endif // MAINWINDOW_H
