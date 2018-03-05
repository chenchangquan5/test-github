#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

signals:
    void signalChangePath(QString songPath, QString lyricPath);

public slots:
    void slotCloseSettingsDialog(void);

public:
    explicit SettingsDialog(QWidget *parent = 0);
    ~SettingsDialog();

    QString getSongPath(void) const;
    QString getLyricPath(void) const;

private slots:
    void on_pb_songPath_clicked();
    void on_pb_lyricPath_clicked();
    void on_pb_save_clicked();

private:
    Ui::SettingsDialog *ui;

    QString m_initPath;

    QString m_songPath;
    QString m_lyricPath;

    bool read(QString group, QString key, QString &value);
    bool write(QString group, QString key, QString value);
};

#endif // SETTINGSDIALOG_H
