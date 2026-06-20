#include "admin.cpp"

using namespace std;

void bersihkanLayar();
void jedaTampilan();

void dashboardUser()
{
    int subPilih = 0;
    int key;
    do
    {
        bersihkanLayar();
        cout << "\n";
        cout << "   ===============================================\n";
        cout << "   |                                             |\n";
        cout << "   |          D A S H B O A R D  U S E R         |\n";
        cout << "   |                                             |\n";
        cout << "   ===============================================\n";

        string menu[] = {"Lihat Barang", "Pesan Barang", "Logout"};
        for (int i = 0; i < 3; i++)
        {
            cout << endl
                 << "              " << (i == subPilih ? "\033[36m>> " : "   ") << menu[i] << "\033[0m" << endl;
        }
        key = _getch();
        if (key == 224)
        {
            key = _getch();
            if (key == 72)
                subPilih = (subPilih == 0) ? 3 : subPilih - 1;
            else if (key == 80)
                subPilih = (subPilih == 3) ? 0 : subPilih + 1;
        }
    } while (key != 13);

    switch (subPilih)
    {
    case 0:
        readBarang();
        dashboardUser();
        break;
    case 1:
        // menu pesan
        dashboardUser();
        break;
    case 2:
        spasi();
        cout << " Apakah anda yakin ingin logout ? (y/n) ";
        cin >> yesorno;

        if (yesorno == 'y' || yesorno == 'Y')
        {
            spasi();
            cout << " Logout berhasil!" << endl;
            lanjutTampilan();
            menuUtama();
        }
        else
            dashboardAdmin();
        break;
    }
}