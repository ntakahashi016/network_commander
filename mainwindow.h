#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "commandlist.h"
#include <iterator>
#include <iostream>
#include <process.h>
#include <QMainWindow>
#include <QFileDialog>
#include <QTextStream>
#include <QStringList>
#include <QStringListModel>

namespace Ui {
class MainWindow;
}

/*! \class MainWindow
 *  \brief Network-Commanderのメイン画面
 *  \author Takahashi Noriaki
 *  \version 0.0
 *  \date    2015
 *  \bug 不正なパラメータを入力した際の動作は不明。
 *  \todo 不正なパラメータ入力に対する例外処理を追加する。
 */

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //! コンストラクタ
    /*!
    * \param parent
    */
    explicit MainWindow(QWidget *parent = 0);
    //! デストラクタ
    ~MainWindow();

private slots:
    //! メニューバーのFile->Openが選択された時のスロット
    /*!
    * .csvファイルを前提とし、カンマ区切りでデータを読み込む
    */
    void on_OpenFileMenue_Selected();

    //! メニューバーのFile->Saveが選択された時のスロット
    /*!
    * .csvを前提とし、データをカンマ区切りでファイル出力する
    */
    void on_SaveFileMenue_Selected();

    //! ADDボタンがクリックされた時のスロット
    /*!
    * UIに入力されているパラメータをリストに追加する
    */
    void on_addBtn_clicked();

    //! Startボタンがクリックされた時のスロット
    /*!
    * リストにあるパラメータで順番にプログラムを実行する
    */
    void on_startBtn_clicked();

    //! コマンドファイルの選択ボタンがクリックされた時のスロット
    /*!
    * ダイアログで指定されたファイルパスをテキストエリアに入力する
    */
    void on_commandFileBtn_clicked();

    //! ログファイルの選択ボタンがクリックされた時のスロット
    /*!
    * ダイアログで指定されたファイルパスをテキストエリアに入力する
    */
    void on_logFileBtn_clicked();

    //! 実行プログラム名変更の有効チェックボックスがクリックされた時スロット
    /*!
    * 実行ファイル名テキストエリアの編集可否を変更する
    */
    void on_programTextEnableCheck_clicked();

    //! 実行マクロ名変更の有効チェックボックスがクリックされた時スロット
    /*!
    * 実行マクロ名テキストエリアと選択ボタンの編集可否を変更する
    */
    void on_macroTextEnableCheck_clicked();

    //! 実行マクロの選択ボタンがクリックされた時スロット
    /*!
    * ダイアログで指定されたファイルパスを実行マクロ名テキストエリアに入力する
    */
    void on_macroFileBtn_clicked();

    //! Clearボタンがクリックされた時のスロット
    /*!
    * リストの内容を破棄する
    */
    void on_clearBtn_clicked();

    //! 実行プログラム選択ボタンがクリックされた時のスロット
    /*!
    * ダイアログで指定されたファイルパスを実行プログラム名テキストエリアに入力する
    */
    void on_programFileBtn_clicked();

    //! SSH接続ボタンがクリックされた時のスロット
    /*!
    * 接続先の入力可否情報を更新する
    */
    void on_connectionBtnSSH_clicked();

    //! Telnet接続ボタンがクリックされた時のスロット
    /*!
    * 接続先の入力可否情報を更新する
    */
    void on_connectionBtnTelnet_clicked();

    //! Serial接続ボタンがクリックされた時のスロット
    /*!
    * 接続先の入力可否情報を更新する
    */
    void on_connectionBtnSerial_clicked();

    //! 接続方法をマクロで定義するボタンがクリックされた時のスロット
    /*!
    * 接続先の入力可否情報を更新する
    */
    void on_connectionBtnMacro_clicked();

private:
    Ui::MainWindow *ui;
    CommandList *commandList;
    enum Connection {SSH=1, Telnet, Serial, DependOnMacro};
    QVector<QString> commandListHeader;
    QVector<QString> commandParamNameList;
    QStringListModel programModel;
    QStringListModel macroModel;
    QStringListModel deviceModel;
    QStringListModel ipModel;
    QStringListModel comModel;
    QStringListModel usernameModel;
    QStringListModel passwordModel;
    QStringListModel commandFileModel;
    QStringListModel logFileModel;
    QStringListModel commentModel;

    //! 接続先の有効無効を設定する
    /*!
    * 接続先の種類を選択されている接続方法に応じて制限する
    */
    void setDestinationsEnable();
    QVector<QString> getParameters();
//    void setParametersModel(QVector<QStringListModel> *models, QVector<QStringList> *params);
    void setParametersModel(QVector<QStringList> params);
};

#endif // MAINWINDOW_H
