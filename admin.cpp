#include "umum.cpp"
using namespace std;

void bersihkanLayar();
void jedaTampilan();

void dashboardAdmin()
{
    int subPilih = 0;
    int key;
    do
    {
        bersihkanLayar();
        cout << "\n";
        cout << "   ===============================================\n";
        cout << "   |                                             |\n";
        cout << "   |        D A S H B O A R D  A D M I N         |\n";
        cout << "   |                                             |\n";
        cout << "   ===============================================\n";

        string menu[] = {"Data Barang", "Logout"};
        for (int i = 0; i < 2; i++)
        {
            cout << endl
                 << "            " << (i == subPilih ? "\033[36m>> " : "   ") << menu[i] << "\033[0m" << endl;
        }
        key = _getch();
        if (key == 224)
        {
            key = _getch();
            if (key == 72 || key == 80)
                subPilih = (subPilih == 0) ? 1 : 0;
        }
    } while (key != 13);

    if (subPilih == 0)
    {
        
    }
    else
    {
        spasi();
        cout << "  Apakah anda yakin ingin logout ? (y/n) ";
        cin >> yesorno;

        if (yesorno == 'y' || yesorno == 'Y')
        {
            spasi();
            cout << "  Logout berhasil!" << endl;
            lanjutTampilan();
            menuUtama();
        }
        else
            dashboardAdmin();
    }
}