#include "AzioniControllo.h"

AzioniControlloMC::AzioniControlloMC() {

    wchar_t userbuf[UNLEN + 1];
    DWORD usersize = UNLEN+1;
    BOOL status;

    status = GetUserName(userbuf, &usersize);
    if (!status) {
        perror("err:");

    }
    Win_username = QString::fromWCharArray(userbuf);
    Mc_path = "C:\\Users\\" + Win_username + "\\AppData\\Roaming\\.minecraft\\";

}

void AzioniControlloMC::renameMCVersions() {

    QString oldname = Mc_path+"versions";
    QString newname = Mc_path+"versions_renamed";

    int result = 0;

    // rename == 0 Renamed
    if (rename_dir.rename(oldname, newname)) {
        printf("Dir versions not in use!!");
        rename_dir.rename(newname, oldname);
        result = -1;
    }  
    else {
        printf("Dir versions in use, OK");
        result = 1;
    }
    oldname.clear();
    newname.clear();

    /*
    -1 : Bad
     0 : Error
     1 : Ok
    */

    //emit resultValue(result);


}
