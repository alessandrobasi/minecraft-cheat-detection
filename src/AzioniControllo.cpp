#include "AzioniControllo.h"



AzioniControlloMC::AzioniControlloMC() {
    printf("classe creata\n");

    wchar_t userbuf[UNLEN + 1];
    DWORD usersize = UNLEN+1;
    BOOL status;

    status = GetUserName(userbuf, &usersize);
    if (!status) {
        perror("err:");
    }

    Win_username = QString::fromWCharArray(userbuf);
}

void AzioniControlloMC::renameMCVersions() {

    QString oldname = "C:\\Users\\"+ Win_username +"\\AppData\\Roaming\\.minecraft\\versions";

    QString newname = "C:\\Users\\" + Win_username +"\\AppData\\Roaming\\.minecraft\\versions_renamed";

    int result = 0;

    // rename == 0 Rinominato
    if (MoveFileW(oldname, newname) == 0) {
        printf("Dir versions not in use!!");
        MoveFileW(newname, oldname);
        result = -1;
    }  
    else {
        printf("Dir versions in use, OK");
        result = 1;
    }




}