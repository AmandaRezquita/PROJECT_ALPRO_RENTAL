#include <iostream>
#include <string>
#include <cstdlib>
#include <conio.h>
#define BLUE "\033[34m"
#define RESET "\033[0m"
using namespace std;

const int MAX = 100;

struct Account
{
    string username;
    string password;
};

struct Barang
{
    string url;
    string nama;
    int harga;
    string deskripsi;
    bool available;
};

Account admin[1];
Account user[MAX];
Barang daftarBarang[MAX];
int jumlahUser = 2;
int pilihMenu = 0;
int jumlahBarang = 0;
int edit;
char yesorno;
string tempJenis, tempMerk, tempDeskripsi;

void dashboardAdmin();
void kelolaBarang();
void createBarang();
void readBarang();
void updateBarang();
void deleteBarang();

void inisialisasiDummyData()
{
    if (jumlahBarang == 0)
    {
        daftarBarang[0] = {
            "https://kenh14cdn.com/203336854389633024/2022/11/28/photo-17-1669604198602829180940.jpg",
            "Vario",
            150000,
            "Jenis     : Motor\n"
            "                   Merk      : Honda\n"
            "                   Catatan   : Tes",
            true};

        daftarBarang[1] = {
            "https://www.honda.ca/-/media/Brands/Honda/Models/CR-V/2026/04-Trims/BAP/EX-L/SRSM/MY26_CR-V_EXL_AWD_SRSM_3250x2400_Desktop_BAPColourSelector_01.png",
            "CRV",
            250000,
            "Jenis     : Mobil\n"
            "                   Merk      : Honda\n"
            "                   Catatan   : Tes",
            true};
        jumlahBarang = 2;
    }
}

void clearBuffer()
{
    cin.clear();
    cin.ignore(MAX, '\n');
}

void spasi()
{
    cout << endl
         << '\t' << "     ";
}

void bersihkanLayar()
{
    cout << "\033[2J\033[H";
    system("cls");
}

void jedaTampilan()
{
    cout << "\n>> Tekan ENTER untuk kembali...";
    _getch();
}

void lanjutTampilan()
{
    cout << "\n>> Tekan ENTER untuk lanjut...";
    _getch();
}

void dataAwal()
{
    admin[0].username = "admin";
    admin[0].password = "admin123";
    user[0].username = "user1";
    user[0].password = "123";
    user[1].username = "user2";
    user[1].password = "456";
}

void tampilkanVespa()
{
    cout << "\t                                        ,-~ |" << endl;
    cout << "\t     ________________                o==]___|" << endl;
    cout << "\t    |                |                \\ \\" << endl;
    cout << "\t    |________________|                /\\ \\" << endl;
    cout << "\t__  /  _,-----._     )             |  \\ \\." << endl;
    cout << "\t|_||/_-~         `.   /()          |  /|]_|_____" << endl;
    cout << "\t  |//             \\ |              \\/ /_-~     ~-_" << endl;
    cout << "\t  //________________||              / //__________\\" << endl;
    cout << "\t //__|______________| \\____________/ //___/-\\ \\~-_" << endl;
    cout << "\t((_________________/_-o___________/_//___/  /\\,\\  \\" << endl;
    cout << "\t |__/(  ((====)o===--~~                 (  ( (o/)  )" << endl;
    cout << "\t      \\  ``==' /                         \\  `--'  /" << endl;
    cout << "\t       `-.__,-'                           `-.__,-'" << endl;
}

bool cekAdmin(string u, string p)
{
    return (u == admin[0].username && p == admin[0].password);
}

bool cekUser(string u, string p)
{
    for (int i = 0; i < jumlahUser; i++)
    {
        if (u == user[i].username && p == user[i].password)
            return true;
    }
    return false;
}

bool cekUsername(string u)
{
    if (u == admin[0].username)
        return true;
    for (int i = 0; i < jumlahUser; i++)
    {
        if (u == user[i].username)
            return true;
    }
    return false;
}

void loginAdmin()
{
    bersihkanLayar();
    string u, p;
    cout << endl;
    tampilkanVespa();
    cout << '\n';
    cout << "     ===========================================================\n";
    cout << endl;
    cout << "       ";
    cout << "      L O G I N  S E B E G A I  A D M I N\n";
    cout << endl;
    cout << '\t' << "     ";
    cout << "Username : ";
    cin >> u;
    cout << endl;
    cout << '\t' << "     ";
    cout << "Password : ";
    cin >> p;
    if (cekAdmin(u, p))
    {
        cout << endl;
        cout << '\t' << "     ";
        cout << BLUE << "[Login Berhasil!]\n"
             << RESET
             << endl;
        lanjutTampilan();
        dashboardAdmin();
    }
    else
    {
        cout << endl;
        cout << '\t' << "     ";
        cout << "[Login Gagal!]\n"
             << endl;
        jedaTampilan();
    }
}

void loginUser()
{
    bersihkanLayar();
    string u, p;
    cout << endl;
    tampilkanVespa();
    cout << '\n';
    cout << "     ===========================================================\n";
    cout << endl;
    cout << "       ";
    cout << "      L O G I N  S E B E G A I  U S E R\n";
    cout << endl;
    cout << '\t' << "     ";
    cout << "Username : ";
    cin >> u;
    cout << endl;
    cout << '\t' << "     ";
    cout << "Password : ";
    cin >> p;
    if (cekUser(u, p))
    {
        cout << endl;
        cout << '\t' << "     ";
        cout << BLUE << "[Login Berhasil!]\n"
             << RESET << endl;
    }
    else
    {
        cout << endl;
        cout << '\t' << "     ";
        cout << "[Login Gagal!]\n"
             << endl;
    }
    jedaTampilan();
}

void registrasi()
{
    bersihkanLayar();
    string u, p, c;
    cout << endl;
    tampilkanVespa();
    cout << '\n';
    cout << "     ===========================================================\n";
    cout << endl;
    cout << "       ";
    cout << "      R E G I S T R A S I\n";
    cout << endl;
    cout << '\t' << "     ";
    cout << "Username : ";
    cin >> u;
    if (cekUsername(u))
    {
        cout << endl;
        cout << '\t' << "     ";
        cout << "[Username sudah terdaftar!]\n";
    }
    else
    {
        cout << endl;
        cout << '\t' << "     ";
        cout << "Password : ";
        cin >> p;
        cout << endl;
        cout << '\t' << "     ";
        cout << "Konfirmasi : ";
        cin >> c;
        if (p == c)
        {
            user[jumlahUser].username = u;
            user[jumlahUser].password = p;
            jumlahUser++;
            cout << endl;
            cout << '\t' << "     ";
            cout << "[Akun berhasil dibuat!]\n";
        }
        else
        {
            cout << endl;
            cout << '\t' << "     ";
            cout << "[Password tidak cocok!]\n";
        }
    }
    jedaTampilan();
}

void loginSubMenu()
{
    int key;
    int subPilih = 0;
    do
    {
        bersihkanLayar();
        cout << endl;
        tampilkanVespa();
        cout << '\n';
        cout << "     ===========================================================\n";
        cout << endl;
        cout << "       ";
        cout << "      L O G I N\n";
        string menu[] = {"Login Sebagai Admin", "Login Sebagai User", "Kembali"};
        for (int i = 0; i < 3; i++)
        {
            cout << endl;
            cout << '\t' << "     ";
            if (i == subPilih)
                cout << "\033[36m>> " << menu[i] << "\033[0m" << endl;
            else
                cout << "   " << menu[i] << endl;
        }
        key = _getch();
        if (key == 224)
        {
            key = _getch();
            if (key == 72)
                subPilih = (subPilih == 0) ? 2 : subPilih - 1;
            else if (key == 80)
                subPilih = (subPilih == 2) ? 0 : subPilih + 1;
        }
    } while (key != 13);

    if (subPilih == 0)
        loginAdmin();
    else if (subPilih == 1)
        loginUser();
}

void menuUtama()
{
    int key;
    do
    {
        bersihkanLayar();
        cout << endl;
        tampilkanVespa();
        cout << '\n';
        cout << "     ===========================================================\n";
        cout << endl;
        cout << "       ";
        cout << "      S I S T E M  R E N T A L  K E N D A R A A N      \n";
        string menu[] = {"Login", "Registrasi", "Keluar"};
        for (int i = 0; i < 3; i++)
        {
            cout << endl;
            cout << '\t' << "     ";

            if (i == pilihMenu)
                cout << "\033[36m>> " << menu[i] << "\033[0m" << endl;
            else
                cout << "   " << menu[i] << endl;
        }

        key = _getch();
        if (key == 224)
        {
            key = _getch();
            if (key == 72)
                pilihMenu = (pilihMenu == 0) ? 2 : pilihMenu - 1;
            else if (key == 80)
                pilihMenu = (pilihMenu == 2) ? 0 : pilihMenu + 1;
        }
    } while (key != 13);

    switch (pilihMenu)
    {
    case 0:
        loginSubMenu();
        menuUtama();
        break;
    case 1:
        registrasi();
        menuUtama();
        break;
    case 2:
        cout << "\nTerima Kasih!\n";
        break;
    }
}

int main()
{
    inisialisasiDummyData();
    dataAwal();
    menuUtama();
    return 0;
}