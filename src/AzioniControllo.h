#pragma once
#include <QObject>
#include <stdio.h>
#include <Windows.h>
#include <winbase.h>
#include <Lmcons.h>
#include <string>

class AzioniControlloMC : public QObject {

	Q_OBJECT

public:
	AzioniControlloMC();

private:
	QString Win_username;
	

public slots:
	void renameMCVersions();
};