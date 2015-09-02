#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Fileメニュー選択時のアクションを接続
    connect(ui->actionOpen_File, SIGNAL(triggered()),this, SLOT(on_OpenFileMenue_Selected()));
    connect(ui->actionSave_File, SIGNAL(triggered()),this, SLOT(on_SaveFileMenue_Selected()));
    // 接続方法ボタンの初期設定
    ui->connectionBtnGr->setId(ui->connectionBtnSSH,    MainWindow::SSH);
    ui->connectionBtnGr->setId(ui->connectionBtnTelnet, MainWindow::Telnet);
    ui->connectionBtnGr->setId(ui->connectionBtnSerial, MainWindow::Serial);
    ui->connectionBtnGr->setId(ui->connectionBtnMacro,  MainWindow::DependOnMacro);
    setDestinationsEnable();
    // コマンドリストの初期設定
    commandListHeader << "program" << "macro" << "device" << "connectin" << "destination" << "username" << "password" << "commandFilename" << "logFileName" << "logAppendFlag" << "comment";
    commandList = new CommandList(ui->commandListTable, &commandListHeader);
    // 実行コマンドのパラメータ順序設定
    commandParamNameList << "program" << "macro" << "connectin" << "destination" << "username" << "password" << "commandFilename" << "logFileName" << "logAppendFlag";
    // パラメータリスト(編集可能なコンボボックス)
    ui->programBox->setLineEdit(ui->programText);
    ui->programBox->setModel(&programModel);
    ui->macroBox->setLineEdit(ui->macroText);
    ui->macroBox->setModel(&macroModel);
    ui->deviceBox->setLineEdit(ui->deviceText);
    ui->deviceBox->setModel(&deviceModel);
    ui->ipBox->setLineEdit(ui->ipText);
    ui->ipBox->setModel(&ipModel);
    ui->comBox->setLineEdit(ui->comText);
    ui->comBox->setModel(&comModel);
    ui->usernameBox->setLineEdit(ui->usernameText);
    ui->usernameBox->setModel(&usernameModel);
    ui->passwordBox->setLineEdit(ui->passwordText);
    ui->passwordBox->setModel(&passwordModel);
    ui->commandFileBox->setLineEdit(ui->commandFileText);
    ui->commandFileBox->setModel(&commandFileModel);
    ui->logFileBox->setLineEdit(ui->logFileText);
    ui->logFileBox->setModel(&logFileModel);
    ui->commentBox->setLineEdit(ui->commentText);
    ui->commentBox->setModel(&commentModel);
    // 実行プログラムの初期設定
    ui->programText->setText("ttpmacro");
    ui->programBox->setEnabled(ui->programTextEnableCheck->isChecked());
    ui->programFileBtn->setEnabled(ui->programTextEnableCheck->isChecked());
    // 実行マクロの初期設定
    ui->macroText->setText("./Network-Commander.ttl");
    ui->macroBox->setEnabled(ui->macroTextEnableCheck->isChecked());
    ui->macroFileBtn->setEnabled(ui->macroTextEnableCheck->isChecked());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_OpenFileMenue_Selected()
{
    QString filename = QFileDialog::getOpenFileName(this,"Open setting file");
    QFile fp(filename);
    ui->messageText->setPlainText("Open File [" + filename + "]");
    if (fp.open(QFile::ReadOnly | QFile::Truncate)) {
        QTextStream ifs(&fp);
        // ヘッダーのみ別処理
        if(!ifs.atEnd()) {
            QVector<QString> record;
            QStringList line = ifs.readLine().split(',');
            while(!line.isEmpty()) {
                record.append(line.takeFirst());
            }
            // 現状では読み飛ばしとする
            // targetList->setHeader(&record);
        }
        // ヘッダー以降のデータの処理
        while(!ifs.atEnd()) {
            QVector<QString> record;
            QStringList line = ifs.readLine().split(',');
            while(!line.isEmpty()) {
                record.append(line.takeFirst());
            }
            commandList->add_to_List(&record);
        }
    }
}

void MainWindow::on_SaveFileMenue_Selected()
{
    QString filename = QFileDialog::getSaveFileName(this,"Save setting file");
    ui->messageText->setPlainText("Save File [" + filename + "]");
    QFile fp(filename);
    if (fp.open(QFile::WriteOnly | QFile::Truncate)) {
        QTextStream ofs(&fp);
        QStringList strList;
        // ヘッダー出力
        strList = commandListHeader.toList();
        ofs << strList.join(",") << "\n";
        // データ出力
        for(int row = 0; row < ui->commandListTable->rowCount(); ++row) {
            strList.clear();
            for(int col = 0; col < ui->commandListTable->columnCount(); ++col) {
                strList << ui->commandListTable->item(row, col)->text();
            }
            ofs << strList.join(",") << "\n";
        }
        fp.close();
    }
}

//void MainWindow::setParametersModel(QVector<QStringListModel> *models, QVector<QStringList> *params)
void MainWindow::setParametersModel(QVector<QStringList> params)
{
//    for(int i = 0; i < models->length(); i++) {
//        models->at(i).setStringList(params->at(i));
//    }
    QString str;
    str = ui->programText->text();
    programModel.setStringList(params[0]);
    ui->programText->setText(str);
    str = ui->macroText->text();
    macroModel.setStringList(params[1]);
    ui->macroText->setText(str);
    str = ui->deviceText->text();
    deviceModel.setStringList(params[2]);
    ui->deviceText->setText(str);
    switch (ui->connectionBtnGr->checkedId()) {
    case MainWindow::SSH:
    case MainWindow::Telnet:
        str = ui->ipText->text();
        ipModel.setStringList(params[4]);
        ui->ipText->setText(str);
        break;
    case MainWindow::Serial:
        str = ui->comText->text();
        comModel.setStringList(params[4]);
        ui->comText->setText(str);
        break;
    default:
        break;
    }
    str = ui->usernameText->text();
    usernameModel.setStringList(params[5]);
    ui->usernameText->setText(str);
    str = ui->passwordText->text();
    passwordModel.setStringList(params[6]);
    ui->passwordText->setText(str);
    str = ui->commandFileText->text();
    commandFileModel.setStringList(params[7]);
    ui->commandFileText->setText(str);
    str = ui->logFileText->text();
    logFileModel.setStringList(params[8]);
    ui->logFileText->setText(str);
    str = ui->commentText->text();
    commentModel.setStringList(params[10]);
    ui->commentText->setText(str);
}

QVector<QString> MainWindow::getParameters()
{
    QVector<QString> paramVector;
    paramVector << ui->programText->text();
    paramVector << ui->macroText->text();
    paramVector << ui->deviceText->text();
    paramVector << ui->connectionBtnGr->checkedButton()->text();
    // 接続先は接続方法によって選択する
    switch (ui->connectionBtnGr->checkedId()){
    case MainWindow::SSH:
    case MainWindow::Telnet:
        paramVector << ui->ipText->text();
        break;
    case MainWindow::Serial:
        paramVector << ui->comText->text();
        break;
    default:
        paramVector << "undefined";
        break;
    }
    paramVector << ui->usernameText->text();
    paramVector << ui->passwordText->text();
    paramVector << ui->commandFileText->text();
    paramVector << ui->logFileText->text();
    paramVector << (ui->logAppendCheck->isChecked() ? "True" : "False");
    paramVector << ui->commentText->text();
    return paramVector;
}

void MainWindow::on_addBtn_clicked()
{
    QVector<QString> paramVector;
    paramVector = getParameters();
    // リストに追加
    commandList->add_to_List(&paramVector);
    // 各入力欄の入力候補に追加
    QVector<QStringList> params;
//    QVector<QStringListModel> models;
//    models << programModel << macroModel << deviceModel << ipModel << usernameModel << passwordModel << commandFileModel << logFileModel << commentModel;
    for(int col = 0; col < commandList->columnCount(); col++) {
        params.append(commandList->getColumnSet(commandList->getHeader()->at(col)).toList());
    }
    setParametersModel(params);
//    setParametersModel(&models,&params);
    // テキストエリアに表示
    QStringList paramList;
    for(int col = 0; col < paramVector.length(); col++) {
        paramList.append("[" + commandListHeader[col] + "] " + paramVector[col]);
    }
    ui->messageText->setPlainText("[Added a command to the List]\n");
    ui->messageText->setPlainText(ui->messageText->toPlainText() + paramList.join('\n'));
}

void MainWindow::on_startBtn_clicked()
{
    QStringList commandLineStringList;
    // コマンド一覧から全ての行のコマンドを取得する
    for (int i = 0; i < commandList->length(); i++) {
        commandLineStringList << commandList->getCommand(i,commandParamNameList);
    }
    // 各コマンドを逐次実行する
    ui->messageText->setPlainText("[Start command list execution]\n");
    for(int i = 0; i < commandLineStringList.length(); i++) {
        const QString commandLineString = commandLineStringList[i] + '\n';
        QString strNum;
        ui->messageText->setPlainText(ui->messageText->toPlainText() + "[command " + strNum.setNum(i+1) + "]\n");
        ui->messageText->setPlainText(ui->messageText->toPlainText() + commandLineString);
        // デバッグモード時はコマンドを実行しない
        if (!ui->debugModeCheck->isChecked()) {
            system(commandLineString.toStdString().c_str());
        }
    }
    ui->messageText->setPlainText(ui->messageText->toPlainText() + "[Finished]\n");
}

void MainWindow::on_commandFileBtn_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,"Command file");
    ui->commandFileText->setText(filename);
}

void MainWindow::on_logFileBtn_clicked()
{
    QString filename = QFileDialog::getSaveFileName(this,"Log file");
    ui->logFileText->setText(filename);
}

void MainWindow::on_programTextEnableCheck_clicked()
{
    bool checkStatus = ui->programTextEnableCheck->isChecked();
    ui->programBox->setEnabled(checkStatus);
    ui->programFileBtn->setEnabled(checkStatus);
}

void MainWindow::on_macroTextEnableCheck_clicked()
{
    bool checkStatus = ui->macroTextEnableCheck->isChecked();
    ui->macroBox->setEnabled(checkStatus);
    ui->macroFileBtn->setEnabled(checkStatus);
}

void MainWindow::on_macroFileBtn_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,"Macro file");
    ui->macroText->setText(filename);
}

void MainWindow::on_clearBtn_clicked()
{
    commandList->clear_List();
    ui->messageText->setPlainText("List has cleard");
}

void MainWindow::on_programFileBtn_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,"Macro file");
    ui->programText->setText(filename);
}

void MainWindow::setDestinationsEnable()
{
    switch (ui->connectionBtnGr->checkedId()) {
    case MainWindow::SSH:
    case MainWindow::Telnet:
        ui->ipBox->setEnabled(true);
        ui->comBox->setEnabled(false);
        break;
    case MainWindow::Serial:
        ui->ipBox->setEnabled(false);
        ui->comBox->setEnabled(true);
        break;
    default:
        ui->ipBox->setEnabled(false);
        ui->comBox->setEnabled(false);
        break;
    }
}

void MainWindow::on_connectionBtnSSH_clicked()
{
    setDestinationsEnable();
}

void MainWindow::on_connectionBtnTelnet_clicked()
{
    setDestinationsEnable();
}

void MainWindow::on_connectionBtnSerial_clicked()
{
    setDestinationsEnable();
}

void MainWindow::on_connectionBtnMacro_clicked()
{
    setDestinationsEnable();
}

