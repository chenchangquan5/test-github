#include "settingsdialog.h"
#include "ui_settingsdialog.h"

#include <QSettings>
#include <QFileDialog>

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);

    m_initPath = "./../MusicPlayerV1.55/config.ini";

    read("Path", "SongPath", m_songPath);
    read("Path", "LyricPath", m_lyricPath);
    //当两组read()写在下面两行程序的后面，再重新编译时，路径在le_songPath和le_lyricPath中不再显示

    ui->le_songPath->setText(m_songPath);
    ui->le_lyricPath->setText(m_lyricPath);
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::slotCloseSettingsDialog(void)
{
    this->close();
}

void SettingsDialog::on_pb_songPath_clicked()
{
    m_songPath = QFileDialog::getExistingDirectory(this);
    ui->le_songPath->setText(m_songPath);
}

void SettingsDialog::on_pb_lyricPath_clicked()
{
    m_lyricPath = QFileDialog::getExistingDirectory(this);
    ui->le_lyricPath->setText(m_lyricPath);
}

void SettingsDialog::on_pb_save_clicked()
{
    emit signalChangePath(ui->le_songPath->text(), ui->le_lyricPath->text());

    write("Path", "SongPath", ui->le_songPath->text());
    write("Path", "LyricPath", ui->le_lyricPath->text());
}

bool SettingsDialog::write(QString group, QString key, QString value)
{
    if(m_initPath.isEmpty() || key.isEmpty())
    {
        return false;
    }else
    {
        QSettings config(m_initPath, QSettings::IniFormat);

        config.beginGroup(group);
        config.setValue(key, value);
        config.endGroup();

        return true;
    }
}

bool SettingsDialog::read(QString group, QString key, QString &value)
{
    value.clear();
    if(m_initPath.isEmpty() || key.isEmpty())
    {
        return false;
    }else
    {
        QSettings config(m_initPath, QSettings::IniFormat);

        value = config.value(group + "/" + key).toString();

        return true;
    }
}

QString SettingsDialog::getSongPath(void) const
{
    return m_songPath;
}

QString SettingsDialog::getLyricPath(void) const
{
    return m_lyricPath;
}
