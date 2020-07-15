#pragma once
#include <QObject>
#include <stdio.h>
#include <Windows.h>
#include <winbase.h>
#include <Lmcons.h>
#include <string>
#include <QDir>
#include <QMetaType>

class AzioniControlloMC : public QObject {

	Q_OBJECT

public:
	AzioniControlloMC();
	
private:
	QString Win_username;
	QString Mc_path;
	QDir rename_dir;

	

public slots:
	void renameMCVersions();
	//AzioniControlloMC();

signals:
	void resultValue(int result);
};