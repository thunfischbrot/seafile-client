#ifndef SEAFILE_CLIENT_FILE_BROWSER_PROGRESS_DIALOG_H
#define SEAFILE_CLIENT_FILE_BROWSER_PROGRESS_DIALOG_H

#include <QProgressDialog>
#include <QObject>
#include <QTimer>

#include "tasks.h"

class QProgressBar;
class QLabel;


class FileBrowserProgressDialog : public QProgressDialog {
    Q_OBJECT
public:
    FileBrowserProgressDialog(FileNetworkTask *task, QWidget *parent=0);
    ~FileBrowserProgressDialog();

    typedef enum {
        ActionRetry = 0,
        ActionSkip,
        ActionAbort,
    } ActionOnFailure;

public slots:
    void cancel();

private slots:
    void onProgressUpdate(qint64 processed_bytes, qint64 total_bytes);
    void onCurrentNameUpdate(QString current_name);
    void onTaskFinished(bool success);
    void initTaskInfo();
    void onOneFileUploadFailed(const QString& filename, bool single_file);
    void onQueryUpdate();
    void onQuerySuccess(const GetIndexProgressResult& result);
    ActionOnFailure retryOrSkipOrAbort(const QString& msg, bool single_file);

private:

    FileNetworkTask* task_;
    QLabel *description_label_;
    QLabel *more_details_label_;
    QProgressBar *progress_bar_;
    QUrl progress_url_;
    QString oid_;
    GetIndexProgressRequest *progress_request_;
    QTimer *index_progress_timer_;
};



#endif // SEAFILE_CLIENT_FILE_BROWSER_PROGRESS_DIALOG_H
